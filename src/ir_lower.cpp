#include "ir_lower.hpp"
#include "ast.hpp"
#include "types.hpp"
#include <fstream>
#include <iostream>
#include <memory>

using namespace ir;

int type_to_size(Type::Kind kind){
    switch (kind){
        case (Type::Kind::Bool) :
        case (Type::Kind::Char) : return 1;
        case (Type::Kind::Float) :
        case (Type::Kind::Enum) : // default enum to uint conversion
        case (Type::Kind::Int) : return 4;
        case (Type::Kind::Double) :
        case (Type::Kind::Struct) :
        case (Type::Kind::List) :
        case (Type::Kind::Long) : return 8;
        default : return -1; // no hit
    }
}

void IR_Lowerer::lower(ModuleNode& node){
    generate_struct_file();
    node.accept(*this);
    close_struct_file();
}

void IR_Lowerer::generate_struct_file(){
    std::ofstream classfile("./sys_lib/struct_gen.c", std::ios::trunc);
    // set include paths
    classfile << "#include \"mem.h\"\n#include \"structs.h\"\n\n";
    return;
}

void IR_Lowerer::close_struct_file(){
    std::ofstream classfile("./sys_lib/struct_gen.c", std::ios::app);
    classfile << "static struct_layout STRUCT_DATA[] {\n";
    for (int i = 0; i < structInfo.struct_count(); i++){
        classfile << "\tSTRUCT_"<<i+1<<"_LAYOUT,\n";
    }
    classfile << "};\n";
}

void IR_Lowerer::visit( ModuleNode& node){
    identifier.push_scope();
    for (auto& d : node.decl){
        d->accept(*this);
    }
    identifier.pop_scope();
}

void IR_Lowerer::visit( StructDecl& node){
    int alignment = 0;
    structInfo.add_struct(node.name, node.fields);

    std::vector<Field>& fields = node.fields;
    for (Field& f : fields){
        alignment = std::max(alignment, type_to_size(f.type->kind));
    }
    int offset = 0;
    int payload_size;
    std::vector<std::pair<std::string, int>> layout;
    for (Field& f : fields){
        int size = type_to_size(f.type->kind);
        if (offset % size) offset += size - (offset % size);

        payload_size = size + offset;
        
        std::string type;
        switch (f.type->kind){
            case (Type::Kind::Struct) : type = "STRUCT"; break;
            case (Type::Kind::List) : type = "LIST"; break;
            default : type = "LITERAL";
        }
        layout.push_back({type, offset});
        
        offset += size;
    }
    if (payload_size % alignment) payload_size += alignment - (payload_size % alignment);

    int struct_no = structInfo.struct_count();

    std::ofstream classfile("./sys_lib/struct_gen.c", std::ios::app);
    classfile << "static struct_layout STRUCT_" << struct_no << "_LAYOUT = {\n"
    << "\t.payload_size = "<<payload_size<<",\n"
    <<"\t.field_count = "<<fields.size()<<",\n"
    <<"\t.fields = {\n";
    for (auto& p : layout){
        classfile << "\t\t{.type="<<p.first<<", .offset="<<p.second<<"},\n";
    }
    classfile << "\t}\n};\n";
}

void IR_Lowerer::visit( EnumDecl& node ){
    structInfo.add_enum(node.name, node.evar);
}

void IR_Lowerer::visit( FuncDecl& node){
    
}