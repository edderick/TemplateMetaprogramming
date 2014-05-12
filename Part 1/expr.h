#ifndef EXPR_H
#define EXPR_H

// COMP6035 Coursework 2: Template Metaprogramming. 
// Part I -- Expression Templates
// 
// Author: Edward Seabrook      Date: 5th May 2014
//
// These templates are written to adhere to this specification: 
//
// Write C++ templates which allow you to use types to represent integer
// arithmetic expressions over the four basic operations (addition,
// subtraction, multiplication, integer division), a single variable, and
// integer literals, for instance: 
//
//                      x + (x-2) * (x-3) 
//
// For the purposes of Parts 1 and 2 we refer to the single variable as x.  
//
// The types representing the expressions should contain a function named
// ‘eval’ that provides code for evaluating the expression. This function
// should accept an integer parameter that will be used as the value for the
// single variable x.  


//Handles Variables 
struct X {
    //Evaluates the expression, x is the variable
    static inline int eval(int x) {
        return x;
    };
};

//Handles literals (constants)
template<int C> 
struct LIT {
    //Evaluates the expression, x is the variable
    static inline int eval(int x) {
        return C;
    };
};

//Handles addition
//L is the left subexpression
//R is the right subexpression
template<class L, class R> 
struct ADD {
    //Evaluates the expression, x is the variable
    static inline int eval(int x) {
        return L::eval(x) + R::eval(x);
    };
};

//Handles multiplication
//L is the left subexpression
//R is the right subexpression
template<class L, class R> 
struct MULT {
    //Evaluates the expression, x is the variable
    static inline int eval(int x) {
        return L::eval(x) * R::eval(x);
    };
};

//Handles subtraction
//L is the left subexpression
//R is the right subexpression
template<class L, class R>
struct SUB {
    //Evaluates the expression, x is the variable
    static inline int eval(int x) {
        return L::eval(x) - R::eval(x);
    };
};

//Handles integer division -- remainders are discarded
//L is the left subexpression
//R is the right subexpression
template<class L, class R>
struct DIV {
    //Evaluates the expression, x is the variable
    static inline int eval(int x) {
        return L::eval(x) / R::eval(x);
    };
};

#endif
