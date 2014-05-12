#include <stdio.h>
#include <stdlib.h>

#include "expr.h"

// COMP6035 Coursework 2: Template Metaprogramming.
// Part III -- Multiple Variables
//
// Author: Edward Seabrook      Date: 5th May 2014
//
// This code aims to fullfill this specification:
//
// Modify your example in main() to provide a number of example input arrays and store the results of 
// evaluation in an array called outputs. 
int main() {
    printf("\nCOMP6035 Coursework 2: Template Metaprogramming. \n"
            "Part III -- Multiple Variables\n");

    int inputs[10][10];
    int outputs[10];

    for (int i = 0; i < 10; i++) { 
        for (int j = 0; j < 10; j++) {
            inputs[i][j] = (j + 1); 
        }
    }
    
    // x
    X<BOUNDS<0, 10> > ex_1;
    outputs[0] = ex_1.eval(inputs[0]);
    printf("Example 1 Answer: %d Expected: %d\n", outputs[0], 1);

    // x + y
    ADD<X<BOUNDS<0, 10> >, X<BOUNDS<0, 10> > > ex_2; 
    outputs[1] = ex_2.eval(inputs[1]);
    printf("Example 2 Answer: %d Expected: %d\n", outputs[1], 1 + 2);
    
    // (x0 + x1) + (x2 + x3)
    ADD<ADD<X<BOUNDS<0, 10> >, X<BOUNDS<0, 10> > >, ADD<X<BOUNDS<0, 10> >, X<BOUNDS<0, 10> > > >  ex_3; 
    outputs[2] = ex_3.eval(inputs[2]);
    printf("Example 3 Answer: %d Expected: %d\n", outputs[2], (1 + 2) + (3 + 4));
    
    // x + (y + z)
    ADD<X<BOUNDS<0, 10> >, ADD<X<BOUNDS<0, 10> >, X<BOUNDS<0, 10> > > >  ex_4; 
    outputs[3] = ex_4.eval(inputs[3]);
    printf("Example 4 Answer: %d Expected: %d\n", outputs[3], 1 + (2 + 3));
    
    // (x0 + x1) * (x2 + x3)
    MULT<ADD<X<BOUNDS<0, 10> >, X<BOUNDS<0, 10> > >, ADD<X<BOUNDS<0, 10> >, X<BOUNDS<0, 10> > > >  ex_5; 
    outputs[4] = ex_5.eval(inputs[4]);
    printf("Example 5 Answer: %d Expected: %d\n", outputs[4], (1 + 2) * (3 + 4));

    // (x - y)
    SUB<X<BOUNDS<0, 10> >, X<BOUNDS<0, 10> > > ex_6;
    outputs[5] = ex_6.eval(inputs[5]);
    printf("Example 6 Answer: %d Expected: %d\n", outputs[5], (1 - 2));


    // x  + (y - 2) * (z - 3)
    ADD<X<BOUNDS<0, 10> >, MULT<SUB<X<BOUNDS<0, 10> >, LIT<2> >, SUB<X<BOUNDS<0, 10> >, LIT<3> >  > > ex_7;
    outputs[6] = ex_7.eval(inputs[6]);
    printf("Example 7 Answer: %d Expected: %d\n", outputs[6], 1 + (2 - 2) * (3 - 3));
   
    // (((x0 + x1) * 3) / (x2 - x3 + x4) + (x5 * (x6 + x7)))  * 9
    MULT<
        ADD<
            DIV<
                MULT<
                    ADD<X<BOUNDS<0,10> >, X<BOUNDS<0,10> > >,
                    LIT<3>
                >,
                SUB<
                    X<BOUNDS<0,10> >,
                    ADD<X<BOUNDS<0,10> >, X<BOUNDS<0,10> > >
                >
            >,
            MULT<
                X<BOUNDS<0,10> >,
                ADD<X<BOUNDS<0,10> >, X<BOUNDS<0,10> > >
            >
        >,
        LIT<9> 
    > ex_8;
    outputs[7] = ex_8.eval(inputs[7]);
    printf("Example 8 Answer: %d Expected: %d\n", outputs[7], (1 - 2));

    // (5 + (5 + x))
    ADD<LIT<5>, ADD<LIT<5> , X<BOUNDS<0, 10> > > > ex_9;
    outputs[8] = ex_9.eval(inputs[8]);
    printf("Example 9 Answer: %d Expected: %d\n", outputs[8], (5 + (5 + 1)));
    // (X + (5 + Y))
    ADD<X<BOUNDS<0, 10> >, ADD<LIT<5>, X<BOUNDS<0,10> > > > ex_10;
    outputs[9] = ex_10.eval(inputs[9]);
    printf("Example 10 Answer: %d Expected: %d\n", outputs[9], (1  + (5 + 2)));
    //Competed succesfully, return 0
    return 0;
}
