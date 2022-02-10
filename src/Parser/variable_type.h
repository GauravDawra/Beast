#pragma once

/*
This unit defines the MULTI_TYPE macro for various types an expression 
can hold. All the functions like add, multiply etc are defined here and 
implemented in the adjoining variable_type.cpp
*/

#include <variant>
#include <string>

// The enumeration type and variant should have the same 
// order of typenames for consistency in code.
enum type {
    INT = 0,
    STRING
};

#define MULTI_TYPE std::variant<int, std::string>

// #define CHECK_TYPE(a, b) if(a.index() != b.index()) \
//     throw std::runtime_error("wrong type of variables");

// class MultiType { // in the future
// public:
//     enum type {
//         INT = 0,
//         STRING
//     };
//     MultiType operator+ (const MultiType& other) const;
// private:

// };

#define CHECK_TYPE(a, b) a.index() == b.index()

std::ostream& operator<< (std::ostream& os, const MULTI_TYPE& a);
MULTI_TYPE add(const MULTI_TYPE&, const MULTI_TYPE&);
MULTI_TYPE multiply(const MULTI_TYPE&, const MULTI_TYPE&);
MULTI_TYPE divide(const MULTI_TYPE&, const MULTI_TYPE&);
MULTI_TYPE subtract(const MULTI_TYPE&, const MULTI_TYPE&);
std::string toString(const MULTI_TYPE&);