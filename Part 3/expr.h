#ifndef EXPR_H
#define EXPR_H

#include <exception>
#include <limits>

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
    int upper, lower, var, index;
    OutOfBoundsException(int lo, int hi, int x, int i) {
        upper = hi; lower = lo; var = x; index = i;
    }
    virtual const char* what() const throw()
    { 
        char* buffer = new char[50];
        snprintf(buffer, 50,
                "The variable x_%d = %d does not fall within the bounds (%d, %d).", 
                var, index, lower, upper);
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
    //All other operators classes are defined as public to allow access to _eval
    template<class FRIEND_T1, class FREIND_T2> friend struct ADD;
    template<class FRIEND_T1, class FREIND_T2> friend struct MULT;
    template<class FRIEND_T1, class FREIND_T2> friend struct DIV;
    template<class FRIEND_T1, class FREIND_T2> friend struct SUB;
    template<int FRIEND_T1> friend struct LIT;
    template<class FRIEND_T1> friend struct X;

    enum {
        LOWER = B::LOWER, 
        UPPER = B::UPPER,
        L_NUM = 1,
        R_NUM = 0
    };
    //Evaluates the expression, x is the array of variables
    //This function should be used by external callers.
    static inline int eval(int x[]) {
        if ((x[0] > B::UPPER) || (x[0] < B::LOWER)) {
            throw new OutOfBoundsException(B::LOWER, B::UPPER, x[0], 0); 
        }
        return x[0];
    };

private:
    // Evaluates the expression, x is the array of variables, i is the array
    // index. A reference has been used for i because the index is incremented
    // after use.
    //This function should be used by other binary operator classes
    template<int I>
    static inline int _eval(int x[]) {
        if ((x[I] > B::UPPER) || (x[I] < B::LOWER)) {
            throw new OutOfBoundsException(B::LOWER, B::UPPER, x[I], I); 
        }
        return x[I]; //Return x[i], and then increment i
    };
};


//Handles literals (constants)
template<int C> 
struct LIT {
    //All other operators classes are defined as public to allow access to _eval
    template<class FRIEND_T1, class FREIND_T2> friend struct ADD;
    template<class FRIEND_T1, class FREIND_T2> friend struct MULT;
    template<class FRIEND_T1, class FREIND_T2> friend struct DIV;
    template<class FRIEND_T1, class FREIND_T2> friend struct SUB;
    template<int FRIEND_T1> friend struct LIT;
    template<class FRIEND_T1> friend struct X;

    enum {
        LOWER = C, 
        UPPER = C,
        L_NUM = 0,
        R_NUM = 0
    };

    //Evaluates the expression, x is the array of variables
    //This function should be used by external callers.
    static inline int eval(int x[]) {
        return C;
    };
private:
    //Evaluates the expression, x is the array of variables, i is the array index
    //This function should be used by other binary operator classes
    template<int I>
    static inline int _eval(int x[]) {
        return C;
    };
};

//Handles addition
//L is the left subexpression
//R is the right subexpression
template<class L, class R> 
struct ADD {
    //All other operators classes are defined as public to allow access to _eval
    template<class FRIEND_T1, class FREIND_T2> friend struct ADD;
    template<class FRIEND_T1, class FREIND_T2> friend struct MULT;
    template<class FRIEND_T1, class FREIND_T2> friend struct DIV;
    template<class FRIEND_T1, class FREIND_T2> friend struct SUB;
    template<int FRIEND_T1> friend struct LIT;
    template<class FRIEND_T1> friend struct X;

    enum {
        LOWER = L::LOWER + R::LOWER,
        UPPER = L::UPPER + R::UPPER,
        L_NUM = L::L_NUM + L::R_NUM,
        R_NUM = R::L_NUM + R::R_NUM
    };
    //Evaluates the expression, x is the array of variables
    //This function should be used by external callers.
    static inline int eval(int x[]) {
        int i = 0;
        return L:: template _eval<0>(x) + R:: template _eval<L_NUM>(x);
    };
private:   
    template <int I>
    static inline int _eval(int x[]) {
        return L:: template _eval<I>(x) + R:: template _eval<L_NUM + I>(x);
    };
};


//Handles mulitplication
//L is the left subexpression
//R is the right subexpression
template<class L, class R> 
struct MULT {
private:
    template <int I>
    static inline int _eval(int x[]) {
        return L:: template _eval<I>(x) * R:: template _eval<L_NUM + I>(x);
    };

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

    //All other operators classes are defined as public to allow access to _eval
    template<class FRIEND_T1, class FREIND_T2> friend struct ADD;
    template<class FRIEND_T1, class FREIND_T2> friend struct MULT;
    template<class FRIEND_T1, class FREIND_T2> friend struct DIV;
    template<class FRIEND_T1, class FREIND_T2> friend struct SUB;
    template<int FRIEND_T1> friend struct LIT;
    template<class FRIEND_T1> friend struct X;

public:
    enum {
        LOWER = L::LOWER * R::LOWER,
        UPPER = L::UPPER * R::UPPER,
        L_NUM = L::L_NUM + L::R_NUM,
        R_NUM = R::L_NUM + R::R_NUM
    };
    //Evaluates the expression, x is the array of variables
    //This function should be used by external callers.
    static inline int eval(int x[]) {
        int i = 0;
        return L:: template _eval<0>(x) * R:: template _eval<L_NUM>(x);
    };
};

//Handles subtraction
//L is the left subexpression
//R is the right subexpression
template<class L, class R> 
struct SUB {

    //All other operators classes are defined as public to allow access to _eval
    template<class FRIEND_T1, class FREIND_T2> friend struct ADD;
    template<class FRIEND_T1, class FREIND_T2> friend struct MULT;
    template<class FRIEND_T1, class FREIND_T2> friend struct DIV;
    template<class FRIEND_T1, class FREIND_T2> friend struct SUB;
    template<int FRIEND_T1> friend struct LIT;
    template<class FRIEND_T1> friend struct X;

    enum {
        LOWER = L::LOWER - R::LOWER,
        UPPER = L::UPPER - R::UPPER,
        L_NUM = L::L_NUM + L::R_NUM,
        R_NUM = R::L_NUM + R::R_NUM
    };
    //Evaluates the expression, x is the array of variables
    //This function should be used by external callers.
    static inline int eval(int x[]) {
        int i = 0;
        return L:: template _eval<0>(x) - R:: template _eval<L_NUM>(x);
    };
private:    
    template <int I>
    static inline int _eval(int x[]) {
        return L:: template _eval<I>(x) - R:: template _eval<L_NUM + I>(x);
    };
};

//Handles division
//L is the left subexpression
//R is the right subexpression
template<class L, class R> 
struct DIV {
private:   
    template <int I>
    static inline int _eval(int x[]) {
        return L:: template _eval<I>(x) / R:: template _eval<L_NUM + I>(x);
    };

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

    //All other operators classes are defined as public to allow access to _eval
    template<class FRIEND_T1, class FREIND_T2> friend struct ADD;
    template<class FRIEND_T1, class FREIND_T2> friend struct MULT;
    template<class FRIEND_T1, class FREIND_T2> friend struct DIV;
    template<class FRIEND_T1, class FREIND_T2> friend struct SUB;
    template<int FRIEND_T1> friend struct LIT;
    template<class FRIEND_T1> friend struct X;

public: 
    enum {
        LOWER = (R::LOWER == 0) ? 0 : L::LOWER / R::LOWER,
        UPPER = (R::UPPER == 0) ? std::numeric_limits<int>::max() : L::UPPER / R::UPPER,
        L_NUM = L::L_NUM + L::R_NUM,
        R_NUM = R::L_NUM + R::R_NUM
    };
    //Evaluates the expression, x is the array of variables
    //This function should be used by external callers.
    static inline int eval(int x[]) {
        int i = 0;
        return L:: template _eval<0>(x) / R:: template _eval<L_NUM>(x);
    };
};

#endif
