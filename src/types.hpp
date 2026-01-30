#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
//#include <iostream>

struct Type {
    enum class Kind {
        Bool, Char, Int, Long, Float, Double,
        List, Func, Struct, Enum, Nominal, 
        ERROR, GENERIC // error and unit types
    };
    Kind kind;
    explicit Type(Kind k) : kind(k) {}
    virtual ~Type() = default;
};

using type_ptr = std::shared_ptr<Type>;
struct Field;

// Primitives
struct BoolType   : Type { BoolType()   : Type(Kind::Bool) {} };
struct CharType   : Type { CharType()   : Type(Kind::Char) {} };
struct IntType    : Type { IntType()    : Type(Kind::Int) {} };
struct LongType   : Type { LongType()   : Type(Kind::Long) {} };
struct FloatType  : Type { FloatType()  : Type(Kind::Float) {} };
struct DoubleType : Type { DoubleType() : Type(Kind::Double) {} };

// erraneous type
struct ErrorType : Type { ErrorType() : Type(Kind::ERROR) {} };
struct GenericType : Type { GenericType() : Type(Kind::GENERIC) {} };

// Structural types
struct ListType : Type {
    type_ptr elem;
    explicit ListType(type_ptr e) : Type(Kind::List), elem(e) {}
};

struct FuncType : Type {
    std::vector<type_ptr> args;
    type_ptr ret;
    explicit FuncType(std::vector<type_ptr> a, type_ptr r)
        : Type(Kind::Func), args(std::move(a)), ret(std::move(r)) {}
};

// Nominal types
struct NominalType : Type {
    std::string name;
    std::vector<Field> fields;
    bool defined = false;
    explicit NominalType(Kind k, std::string name) : Type(k), name(name) {}
};

using nominal_ptr = std::shared_ptr<NominalType>;

struct TypeSystem {
    // singleton type system
    static TypeSystem& instance() {
        static TypeSystem ts;
        return ts;
    }

    type_ptr bool_type()   { return primitive_type<BoolType>(); }
    type_ptr char_type()   { return primitive_type<CharType>(); }
    type_ptr int_type()    { return primitive_type<IntType>(); }
    type_ptr long_type()   { return primitive_type<LongType>(); }
    type_ptr float_type()  { return primitive_type<FloatType>(); }
    type_ptr double_type() { return primitive_type<DoubleType>(); }
    type_ptr error_type() { return primitive_type<ErrorType>(); }
    type_ptr generic_type() { return primitive_type<GenericType>(); }

    type_ptr list_type(type_ptr elem) {
        auto it = list_cache.find(elem);
        if (it != list_cache.end()) {
            return it->second;
        }
        auto t = std::make_shared<ListType>(elem);
        list_cache[elem] = t;
        return t;
    }

    type_ptr func_type(std::vector<type_ptr> args, type_ptr ret) {
        FuncKey key{ret, args};
        auto it = func_cache.find(key);
        if (it != func_cache.end()) {
            return it->second;
        }
        auto t = std::make_shared<FuncType>(args, ret);
        func_cache[key] = t;
        return t;
    }

    // check if nominal type exists
    nominal_ptr find_nominal(const std::string& name){
        auto it = nominal_cache.find(name);
        if (it != nominal_cache.end()){
            return it->second;
        }
        return nullptr;
    }

    nominal_ptr nominal_type(const std::string& name){
        auto it = nominal_cache.find(name);
        if (it != nominal_cache.end()){
            return it->second;
        }
        nominal_ptr nt = std::make_shared<NominalType>(Type::Kind::Nominal, name);
        nominal_cache.emplace(name, nt);
        return nt;
    }

    type_ptr declare_struct(const std::string& name, std::vector<Field>& fields){
        nominal_ptr t = nominal_type(name); // forward declare regardless
        if (t->defined){
            // defined -> error
        }
        t->kind = Type::Kind::Struct;
        t->fields = fields;
        t->defined = true;
        return t;
    }

    type_ptr declare_enum(const std::string& name){
        nominal_ptr t = nominal_type(name); // forward declare regardless
        if (t->defined){
            // defined -> error
        }
        t->kind = Type::Kind::Enum;
        t->defined = true;
        return t;
    }

private:
    TypeSystem() = default; // singleton

    // primitive temp
    template<typename T>
    type_ptr primitive_type() {
        static type_ptr t = std::make_shared<T>();
        return t;
    }

    struct FuncKey {
        type_ptr ret;
        std::vector<type_ptr> args;

        bool operator==(const FuncKey& o) const { return ret==o.ret && args==o.args; }
    };

    struct FuncKeyHash {
        std::size_t operator()(const FuncKey& k) const {
            size_t h = std::hash<const Type*>{}(k.ret.get());
            for (auto& a : k.args) h ^= std::hash<const Type*>{}(a.get()) + 0x9e3779b9 + (h<<6) + (h>>2);
            return h;
        }
    };

    /*
        Type Caching:
            - list types identifiable via elem type
            - func types identifiable via arg/ret type
            - struct/elem nominally typed
    */
    std::unordered_map<type_ptr, type_ptr> list_cache;
    std::unordered_map<FuncKey, type_ptr, FuncKeyHash> func_cache;
    std::unordered_map<std::string, nominal_ptr> nominal_cache;
};