#include "variable_type.h"
#include "scanner.h"
#include "parser.hpp"
#include <iostream>

std::ostream& operator<< (std::ostream& os, const MULTI_TYPE& a) {
    if(a.index() == 0) {
        os << std::get<0>(a);
    }
    else {
        os << std::get<1>(a);
    }
    return os;
}

MULTI_TYPE add(const MULTI_TYPE& a, const MULTI_TYPE& b) {
    if (!CHECK_TYPE(a,b)) std::cout << "not same type" << std::endl;
    // return std::get<a.index()>(a) + std::get<b.index()>(b);
    if(a.index() == 0) {
        return {std::get<0>(a) + std::get<0>(b)};
    }
    else {
        return {std::get<1>(a) + std::get<1>(b)};
    }
}

MULTI_TYPE multiply(const MULTI_TYPE& a, const MULTI_TYPE& b) {
    // TODO: multiplication of string and int
    if (a.index() == type::STRING || b.index() == type::STRING)
        std::cout << "strings cannot be multiplied" << std::endl;
    
    return {std::get<type::INT>(a) * std::get<type::INT>(b)};
}

MULTI_TYPE divide(const MULTI_TYPE& a, const MULTI_TYPE& b) {
    if (a.index() == type::STRING || b.index() == type::STRING)
        std::cout << "strings cannot be divided" << std::endl;

    return {std::get<type::INT>(a) / std::get<type::INT>(b)};
    
}

MULTI_TYPE subtract(const MULTI_TYPE& a, const MULTI_TYPE& b) {
    if (a.index() == type::STRING || b.index() == type::STRING)
        std::cout << "strings cannot be subtracted" << std::endl;

    return {std::get<type::INT>(a) - std::get<type::INT>(b)};
}

std::string toString(const MULTI_TYPE& val) {
    if (val.index() == type::STRING) {
        return std::get<type::STRING>(val);
    }
    else {
        return std::to_string(std::get<type::INT>(val));
    }
}
