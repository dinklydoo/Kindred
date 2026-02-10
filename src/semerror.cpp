#include "semerror.hpp"
#include <iostream>

static TypeSystem& type_s = TypeSystem::instance();

std::string kind_to_string(Type::Kind kind){
    switch(kind){
        case Type::Kind::Enum : { return "enum"; }
        case Type::Kind::Struct : { return "struct"; }
        case Type::Kind::Func : { return "function"; }
        default : return "variable";
    }
}

std::string type_to_string(type_ptr type){
    switch (type->kind){
        case Type::Kind::Nominal :
        case Type::Kind::Struct :
        case Type::Kind::Enum : {
            auto temp = std::static_pointer_cast<NominalType>(type);
            return temp->name;
        };
        case Type::Kind::Func : {
            auto temp = std::static_pointer_cast<FuncType>(type);
            std::string ftype = "(";
            for (type_ptr atype : temp->args){
                ftype += type_to_string(atype) + ',';
            }
            ftype += ")->" + type_to_string(temp->ret);
            return ftype;
        }
        case Type::Kind::List : {
            auto temp = std::static_pointer_cast<ListType>(type);
            std::string ltype = "[";
            ltype += type_to_string(temp->elem);
            ltype += ']';
            return ltype;
        }
        case Type::Kind::Bool : return "bool";
        case Type::Kind::Char : return "char";
        case Type::Kind::Int : return "int";
        case Type::Kind::Long : return "long";
        case Type::Kind::Float : return "float";
        case Type::Kind::Double : return "double";
        default : return "T";
    }
}

void ErrorList::push_error(std::string msg, SemanticError::Kind kind, Source& loc){
    errors.push_back(SemanticError{kind, loc, msg});
}

void ErrorList::redef_error(std::string label, type_ptr def, Source& loc){
    std::string def_type = kind_to_string(def->kind);
    push_error(
        "Redefinition of " + label + " conflicts with prior " + def_type + " definition",
        SemanticError::Kind::REDEF, loc
    );
}

void ErrorList::type_error(std::string message, ExpNode& node){
    push_error(message, SemanticError::Kind::TYPE, node.location);
    node.resolved_type = type_s.error_type();
}

void ErrorList::access_error(std::string message, ExpNode& node){
    push_error(message, SemanticError::Kind::ACCESS, node.location);
    node.resolved_type = type_s.error_type();
}

void ErrorList::arg_error(std::string message, ExpNode& node){
    push_error(message, SemanticError::Kind::ARG, node.location);
    node.resolved_type = type_s.error_type();
}

void ErrorList::undef_error(std::string message, ExpNode& node){
    push_error(message, SemanticError::Kind::UNDEF, node.location);
    node.resolved_type = type_s.error_type();
}

void ErrorList::reference_error(std::string label, type_ptr def, ExpNode& node){
    Type::Kind defined = def->kind;
    std::string def_str = kind_to_string(defined);

    Type::Kind referenced = node.resolved_type->kind;
    std::string ref_str = kind_to_string(referenced);
    push_error(
        "Reference to '" + label + "' as '" + ref_str + "' conflicts with prior definition as '" + def_str + "'",
        SemanticError::Kind::REF, node.location
    );
    node.resolved_type = type_s.error_type();
}

void ErrorList::inexh_error(std::string message, ExpNode& node){
    push_error(
        message, SemanticError::Kind::INEXHAUSTIVE, node.location
    );
    node.resolved_type = type_s.error_type();
}

void ErrorList::main_error(Source& loc){
    push_error(
        "Program entry function 'main' is undefined", 
        SemanticError::Kind::MAIN, loc
    );
}

void ErrorList::report_errors(){
    if (errors.size() > 0){
        std::cout 
        << "======================================================================================================================================================\n"
        << "ERROR LOG: \n"
        << "======================================================================================================================================================\n";
        for (auto err : errors){
            std::cout << "Error (line: "+std::to_string(err.location.line)+" col: "+
            std::to_string(err.location.col)+"): "<< err.message << std::endl;
        }
        std::cerr << std::endl; // flush buffer
        exit(1);
    }
}

void WarningList::push_warning(std::string msg, SemanticWarning::Kind kind, Source& loc){
    warnings.push_back(SemanticWarning{kind, loc, msg});
};

void WarningList::unreach_warning(std::string msg, Source& loc){
    push_warning(msg, SemanticWarning::Kind::UNREACHABLE, loc);
};

void WarningList::postdecl_warning(std::string name, Type::Kind k, DeclNode& node){
    push_warning(
        "Useless declaration of "+kind_to_string(k)+" '"+name+"' after main declaration", 
        SemanticWarning::Kind::POSTDECL, node.location
    );
};

void WarningList::report_warnings(){
    if (warnings.size() > 0){
        std::cout 
        << "======================================================================================================================================================\n"
        << "WARNING LOG: \n"
        << "======================================================================================================================================================\n";
        for (auto war : warnings){
            std::cout << "Warning (line: "+std::to_string(war.location.line)+" col: "+
            std::to_string(war.location.col)+"): "<< war.message << std::endl;
        }
        std::cout << std::endl;
        return;
    }
}