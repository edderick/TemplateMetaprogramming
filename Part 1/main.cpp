#include "expr.h"
#include "stdio.h"

// COMP6035 Coursework 2: Template Metaprogramming.
// Part I -- Expression Templates
//
// Author: Edward Seabrook      Date: 5th May 2014
//
// This code aims to fullfill this specification:
//
// Write a main() method that builds an expression as a type and evaluate it at
// some integer input value.  Print the results to standard out.

int main() {
    printf("\nCOMP6035 Coursework 2: Template Metaprogramming. \n"
            "Part I -- Expression Templates\n"
            "\nEvaluating expression x + (x-2) * (x-3), with x = 5 \n\n");

    //Based on operator precedence (BODMAS), the expression is
    //interpreted as x + ((x-2) * (x-3))
    typedef ADD<X, MULT<SUB<X, LIT<2> >, SUB<X, LIT<3> > > > Expr;
    Expr expr;
    printf("Answer = %d\n\n", expr.eval(5));

    return 0;
}
