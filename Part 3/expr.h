#ifndef EXPR_H
#define EXPR_H

#include <exception>

// COMP6035 Coursework 2: Template Metaprogramming. 
// Part III -- Multiple Variables 
// 
// Author: Edward Seabrook      Date: 5th May 2014
//
// Modify your expression templates from Part 2 to allow for multiple variables in the expression. Each 
// occurrence of a variable expression can be considered as the unique variable named x, y, z, ... For 
// example 
//
//                                      x + (x-2) * (x-3) 
//
// would be considered as 
//
//                                   x  + (y - 2) * (z - 3). 
//
// Modify the eval function to accept an array of integer values and evaluate each variable according to the 
// corresponding position in the input array. For instance, in the above example variable z should evaluate 
// to the 3rd value of the input array. 
//
// Note that each variable expression should be parameterised on a BOUNDS type so that there may be 
// different bounds for each variable. 

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
    //Evaluates the expression, x is the array of variables
    //This function should be used by external callers.
    static inline int eval(int x[]) {
        if ((x[0] > B::UPPER) || (x[0] < B::LOWER)) {
            throw new OutOfBoundsException(B::LOWER, B::UPPER, x[0]); 
        }
        return x[0];
    };

    // Evaluates the expression, x is the array of variables, i is the array
    // index. A reference has been used for i because the index is incremented
    // after use.
    //This function should be used by other binary operator classes
    static inline int eval(int x[], int &i) {
        if ((x[i] > B::UPPER) || (x[i] < B::LOWER)) {
            throw new OutOfBoundsException(B::LOWER, B::UPPER, x[0]); 
        }
        return x[i++]; //Return x[i], and then increment i
    };

};


//Handles literals (constants)
template<int C> 
struct LIT {
    enum {
        LOWER = C, 
        UPPER = C
    };

    //Evaluates the expression, x is the array of variables
    //This function should be used by external callers.
    static inline int eval(int x[]) {
        return C;
    };

    //Evaluates the expression, x is the array of variables, i is the array index
    //This function should be used by other binary operator classes
    static inline int eval(int x[], int &i) {
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
    //Evaluates the expression, x is the array of variables
    //This function should be used by external callers.
    static inline int eval(int x[]) {
        int i = 0;
        return L::eval(x, i) + R::eval(x, i);
    };
    
    static inline int eval(int x[], int &i) {
        return L::eval(x, i) + R::eval(x, i);
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

    //Evaluates the expression, x is the array of variables
    //This function should be used by external callers.
    static inline int eval(int x[]) {
        int i = 0;
        return L::eval(x, i) * R::eval(x, i);
    };

    //Evaluates the expression, x is the array of variables, i is the array index
    //This function should be used by other binary operator classes
    static inline int eval(int x[], int &i) {
        return L::eval(x, i) * R::eval(x, i);
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

    //Evaluates the expression, x is the array of variables
    //This function should be used by external callers.
    static inline int eval(int x[]) {
        int i = 0;
        return L::eval(x, i) - R::eval(x, i);
    };

    //Evaluates the expression, x is the array of variables, i is the array index
    //This function should be used by other binary operator classes
    static inline int eval(int x[], int &i) {
        return L::eval(x, i) - R::eval(x, i);
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

    //Evaluates the expression, x is the array of variables
    //This function should be used by external callers.
    static inline int eval(int x[]) {
        int i = 0; 
        return L::eval(x) / R::eval(x);
    };
    
    //Evaluates the expression, x is the array of variables, i is the array index
    //This function should be used by other binary operator classes
    static inline int eval(int x[], int &i) {
        return L::eval(x, i) / R::eval(x);
    }
};


#endif
