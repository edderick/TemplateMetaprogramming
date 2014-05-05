#ifndef EXPR_H
#define EXPR_H

#include <exception>

// COMP6035 Coursework 2: Template Metaprogramming. 
// Part II -- Bounds
// 
// Author: Edward Seabrook      Date: 5th May 2014
//
// Extend your expression templates from Part 1 to allow each Expression type
// to carry with it a lower and upper bound for the possible values the
// expression could evaluate to. Of course, this depends on the range of values
// for the single variable x. 
//
// We will assume that the bounds on the input are statically known, and
// therefore you should parameterise the template type for representing the
// variable expressions on a type BOUNDS. The type BOUNDS itself should be a
// template parameterised on two integer values: the lower and upper values of
// the range for x.
//
// Modify the eval function to throw an exception in case the input for x is
// not in the specified input range.

struct OutOfBoundsException: public std::exception { 
    int upper, lower, var;
    OutOfBoundsException(int lo, int hi, int x) {
        upper = hi; lower = lo; var = x;
    }
    virtual const char* what() const throw()
    { 
        char* buffer = new char[50];
        snprintf(buffer, 50,
                "The variable x=%d does not fall within the bounds (%d, %d).", 
                var, lower, upper);
        return buffer;
    } 
};

//Holds the upper and lower bounds of an expression
template<int L, int U>
struct BOUNDS {
    enum {
        LOWER = L,
        UPPER = U
    };
};


//Handles Variables 
template<class B> 
struct X {
    enum {
        LOWER = B::LOWER, 
        UPPER = B::UPPER
    };
    //Evaluates the expression, x is the variable
    static inline int eval(int x) {
        if ((x > B::UPPER) || (x < B::LOWER)) {
            throw new OutOfBoundsException(B::LOWER, B::UPPER, x); 
        }
        return x;
    };
};

//Handles literals (constants)
template<int C> 
struct LIT {
    enum {
        LOWER = C, 
        UPPER = C
    };
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
    enum {
        LOWER = L::LOWER + R::LOWER,
        UPPER = L::UPPER + R::UPPER
    };
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
    enum {
        LOWER = L::LOWER * R::LOWER,
        UPPER = L::UPPER * R::UPPER
    };
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
    enum {
        LOWER = L::LOWER - R::LOWER,
        UPPER = L::UPPER - R::UPPER
    };
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
    enum {
        LOWER = L::LOWER / R::LOWER,
        UPPER = L::UPPER / R::UPPER
    };
    //Evaluates the expression, x is the variable
    static inline int eval(int x) {
        return L::eval(x) / R::eval(x);
    };
};


#endif
