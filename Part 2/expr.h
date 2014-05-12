#ifndef EXPR_H
#define EXPR_H

#include <exception>
#include <stdio.h>

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

//Exception to be thrown if bounds do not hold for input.
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
private: 
    //x[a, b] * x[c, d]
    static const int a = L::LOWER;
    static const int b = L::UPPER;
    static const int c = R::LOWER;
    static const int d = R::UPPER;
  
    //Calculate minimun value for expression
    static const int min_a = (a*c < a*d) ? a*c : a*d;
    static const int min_b = (b*c < b*d) ? b*c : b*d;
    static const int MIN = (min_a < min_b) ? min_a : min_b;
    
    //Calculate maximum value for expression
    static const int max_a = (a*c > a*d) ? a*c : a*d;
    static const int max_b = (b*c > b*d) ? b*c : b*d;
    static const int MAX = (max_a > max_b) ? max_a : max_b;

public: 
    enum {
        LOWER = MIN,
        UPPER = MAX
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
private:
    //x[a, b] / x[c, d]
    static const int a = L::LOWER;
    static const int b = L::UPPER;
    // if c or d is zero, round to the closest |1| to prevent x/0
    static const int c = (R::LOWER == 0) ? 1 : R::LOWER;
    static const int d = (R::UPPER == 0) ? -1: R::UPPER;

    // Calculate minimum value for expression
    static const int min_a = (a/c < a/d) ? a/c : a/d;
    static const int min_b = (b/c < b/d) ? b/c : b/d;
    static const int min_ab = (min_a < min_b) ? min_a : min_b;
    static const int min_neg = (c <= -1 && d >= -1) ? ((min_ab < -b) ? min_ab : -b) : min_ab;
    static const int MIN = (c <= 1 && d >= 1) ? ((min_neg <  a) ? min_neg :  a) : min_neg;

    // Calculate maximum value for expression
    static const int max_a = (a/c > a/d) ? a/c : a/d;
    static const int max_b = (b/c > b/d) ? b/c : b/d;
    static const int max_ab = (max_a > max_b) ? max_a : max_b;
    static const int max_neg = (c <= -1 && d >= -1) ? ((max_ab > -a) ? max_ab : -a) : max_ab;
    static const int MAX = (c <= 1 && d >=1) ? ((max_neg > b) ? max_neg :  b) : max_neg;

public: 
    enum {
        LOWER = MIN,
        UPPER = MAX
    };
    //Evaluates the expression, x is the variable
    static inline int eval(int x) {
        return L::eval(x) / R::eval(x);
    };
};


#endif
