#include "types.hpp"
#include <memory>

// Binding strengths for castable numeric values
int binding_strength(type_ptr tp){
    Type::Kind kind = tp->kind;
    switch (kind) {
        case Type::Kind::GENERIC : return 0;
        case Type::Kind::Char : return 1;
        case Type::Kind::Int : return 2;
        case Type::Kind::Long : return 3;
        case Type::Kind::Float : return 4;
        case Type::Kind::Double : return 5;
        default : return -1;
    }
}

// Casts a type to the strongest binding if castable

// struct types by definition are only equivalent to each other
// list types can be cast if underlying values are castable
// enum types are never castable

// If a cast is impossible returns nullptr
type_ptr TypeSystem::cast_strongest(type_ptr a, type_ptr b){
    if (a->kind == Type::Kind::Nil && b->kind == Type::Kind::Struct) return b;
    if (b->kind == Type::Kind::Nil && a->kind == Type::Kind::Struct) return a;

    // recursively cast for list types (UNUSED)
    if (a->kind == Type::Kind::List && b->kind == Type::Kind::List){
        auto al = std::static_pointer_cast<ListType>(a);
        auto bl = std::static_pointer_cast<ListType>(b);

        auto elem = cast_strongest(al->elem, bl->elem);
        if (!elem) return nullptr;
        
        return list_type(elem);
    }
    int bind_a = binding_strength(a);
    int bind_b = binding_strength(b);

    // generic types
    if (bind_a == 0) return b;
    if (bind_b == 0) return a;

    // non comparable types
    if (bind_a < 0 || bind_b < 0) return nullptr;
    if (bind_a > bind_b) return a;
    return b;
}

// Returns fixed type if type_ptr castable is castable to fixed type
// otherwise returns nullptr
type_ptr TypeSystem::cast_fixed(type_ptr fix, type_ptr castable){
    if (fix == cast_strongest(fix, castable) || type_equal(fix, castable)) return fix;
    return nullptr;
}

bool TypeSystem::type_equal(type_ptr a, type_ptr b){
    if (a == b) return true;
    // generics can morph any type
    if (a->kind == Type::Kind::GENERIC || b->kind == Type::Kind::GENERIC) return true;
    if (a->kind != b->kind) return false;
    if (a->kind == Type::Kind::List){
        auto al = std::static_pointer_cast<ListType>(a);
        auto bl = std::static_pointer_cast<ListType>(b);
        return type_equal(al->elem, bl->elem);
    }
    if (a->kind == Type::Kind::Struct || a->kind == Type::Kind::Enum){
        auto al = std::static_pointer_cast<NominalType>(a);
        auto bl = std::static_pointer_cast<NominalType>(b);
        return al->name == bl->name;
    }
    if (a->kind == Type::Kind::Func){ // TODO : SUBTYPE FUNCTIONS I REALLY CBA RN
        auto al = std::static_pointer_cast<FuncType>(a);
        auto bl = std::static_pointer_cast<FuncType>(b);

        if (al->args.size() != bl->args.size()) return false;
        for (int i = 0; i < al->args.size(); i++){
            if (!type_equal(al->args[i], bl->args[i])) return false;
        }
        return type_equal(al->ret, bl->ret);
    }
    return true;
}