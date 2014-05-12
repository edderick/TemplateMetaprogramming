#include "expr.h"
#include "stdio.h"

// COMP6035 Coursework 2: Template Metaprogramming.
// Part II -- Bounds
//
// Author: Edward Seabrook      Date: 5th May 2014
//
// This code aims to fullfill this specification:
//
// Now modify your example in main() to build the expression based on a known
// range for the input values for x.
//
// Print to standard out the calculated bounds for the output from the
// expression before printing the result of the evaluation.
//
// For example, suppose that the bounds on variable x 0 <= x <= 5. Let us write
// this concisely as x_{0,5}.  Consider a sample expression with a variable
// that carries these bounds:
//
//                          (x_{0,5} + 3) * ( x_{0,5} + 5)
//
// Then we can calculate the bounds on the whole expression above as follows:
//
//                  3 <= x_{0,5} + 3 <= 8 and 5 <= x_{0,5} + 5 <= 10
//
// Consequently we have that
//
//                    15 <= ( x_{0,5} + 3 ) * ( x_{0,5} + 5 ) <= 80
//
// That is, the bounds for the above expression would be (15,80) if the bounds
// on x were (0,5).

int main() {
    printf("\nCOMP6035 Coursework 2: Template Metaprogramming. \n"
            "Part I -- Expression Templates\n"
            "\nEvaluating expression (x[0,5] + 3) * (x[0,5] + 5), with x = 3 \n\n");

    // Equation  (x_{0,5} + 3) * ( x_{0,5} + 5) should have bounds 15-80 
    typedef MULT<
            ADD<X<BOUNDS<0, 5> >, LIT<3> >, 
            ADD<X<BOUNDS<0, 5> >, LIT<5> > 
        > Expr;
    Expr expr;

    printf("Answer = %d, Lower Bound: %d, Upper bound: %d\n\n", 
            expr.eval(3), expr.LOWER, expr.UPPER);

    return 0;
}
