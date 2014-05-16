#include "stdio.h"

// This file shows how it would be possible to use template specialisation to
// calculate the bounds on a division.  This example could be simplified and
// duplicated for use on multiplication bounds 

template<int L, int U>
struct BOUNDS {
    enum {
        LOWER = L,
        UPPER = U
    };
};

template<class B>
struct X {
    enum {
        LOWER = B::LOWER,
        UPPER = B::UPPER,
    };
    static inline int eval(int x) {
        if ((x > B::UPPER) || (x < B::LOWER)) {
            printf("Fail\n");
        }
        return x;
    };
};

template <int X>
struct Positive {
    enum {
        VAL = X,
    };
};

template <int X>
struct Negative {
    enum {
        VAL = X,
    };
};

template<bool> struct CASE;

// Default case, should never be used
template<int a, int b, int c, int d, class = CASE<true> >
struct BOUNDS_CALC
{
    enum {
        LOWER = 0,
        UPPER = 0,
    };
};

// Bound[+ve, +ve] / Bound[+ve, +ve]
template<int a, int b, int c, int d>
struct BOUNDS_CALC<a, b, c, d, CASE<(a >= 0 && b > 0 && c > 0 && d > 0)> >
{
    enum {
        LOWER = a / d,
        UPPER = b / c
    };
};

// Bound[+ve, +ve] / Bound[-ve, +ve]
template<int a, int b, int c, int d>
struct BOUNDS_CALC<a, b, c, d, CASE<(a >= 0 && b > 0 && c < 0 && d > 0)> >
{
    enum {
        LOWER = b / -1,
        UPPER = b / 1
    };
};

// Bound[+ve, +ve] / Bound[-ve, -ve]
template<int a, int b, int c, int d>
struct BOUNDS_CALC<a, b, c, d, CASE<(a >= 0 && b > 0 && c < 0 && d < 0)> >
{
    enum {
        LOWER = b / d,
        UPPER = a / c
    };
};


// Bound[-ve, +ve] / Bound[+ve, +ve]
template<int a, int b, int c, int d>
struct BOUNDS_CALC<a, b, c, d, CASE<(a < 0 && b > 0 && c > 0 && d > 0)> >
{
    enum {
        LOWER = a / c,
        UPPER = b / c
    };
};

// Bound[-ve, +ve] / Bound[-ve, +ve]
template<int a, int b, int c, int d>
struct BOUNDS_CALC<a, b, c, d, CASE<(a < 0 && b > 0 && c < 0 && d > 0)> >
{
    static const int abs_a = (a > 0) ? a : -a;
    static const int abs_b = (b > 0) ? b : -b;

    enum {
        LOWER = (abs_b > abs_a) ? (b / -1) : (a / 1),
        UPPER = (abs_b > abs_a) ? (b / 1) : (a / -1)
    };
};

// Bound[-ve, +ve] / Bound[-ve, -ve]
template<int a, int b, int c, int d>
struct BOUNDS_CALC<a, b, c, d, CASE<(a < 0 && b > 0 && c < 0 && d < 0)> >
{
    enum {
        LOWER = b / d,
        UPPER = a / d
    };
};


// Bound[-ve, -ve] / Bound[+ve, +ve]
template<int a, int b, int c, int d>
struct BOUNDS_CALC<a, b, c, d, CASE<(a < 0 && b <= 0 && c > 0 && d > 0)> >
{
    enum {
        LOWER = a / c,
        UPPER = b / d
    };
};

// Bound[-ve, -ve] / Bound[-ve, +ve]
template<int a, int b, int c, int d>
struct BOUNDS_CALC<a, b, c, d, CASE<(a < 0 && b <= 0 && c < 0 && d > 0)> >
{
    enum {
        LOWER = a / 1,
        UPPER = a / -1
    };
};

// Bound[-ve, -ve] / Bound[-ve, -ve]
template<int a, int b, int c, int d>
struct BOUNDS_CALC<a, b, c, d, CASE<(a < 0 && b <= 0 && c < 0 && d < 0)> >
{
    enum {
        LOWER = b / c,
        UPPER = a / d
    };
};

template<class L, class R>
struct DIV {

    static const int a = L::LOWER;
    static const int b = L::UPPER;
    static const int c = (R::LOWER == 0) ? 1 : R::LOWER;
    static const int d = (R::UPPER == 0) ? -1: R::UPPER;

    typedef BOUNDS_CALC<a,b,c,d>  BOUND;

    enum {
        LOWER = BOUND::LOWER,
        UPPER = BOUND::UPPER,
    };
    static inline int eval(int x) {
        //int i = 0;
        return L::eval(x) / R::eval(x);
    };


};
