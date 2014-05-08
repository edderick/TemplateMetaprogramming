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

//Keeps track of whether of not all tests so far have passed
bool all_passed = true;

//Prints the header to the table of test results 
void print_header() {
    printf("%-20s%-12s%-12s%-12s%-12s\n", 
            "Equation", "In Bounds", "Ex. Bounds", "Ac. Bounds", "Passed");
}

struct TestDetails {
    int in_lo;
    int in_hi;
    int expected_lo;
    int expected_hi;
    int actual_lo;
    int actual_hi;
};

//Prints out the results of the test case 
//If there was a failure it also sets all_passed to false
void print_test(const char* equation, TestDetails td) {
    bool bounds_match = ((td.expected_lo == td.actual_lo) 
                        && (td.expected_hi == td.actual_hi));
    
    printf("%-20s(%3d, %3d)  (%3d, %3d)  (%3d, %3d)     %-12s\n", 
            equation, 
            td.in_lo, td.in_hi, 
            td.expected_lo, td.expected_hi,
            td.actual_lo, td.actual_hi,
            (bounds_match) ? "Y" : "N");
    
    if (!bounds_match)  
        all_passed = false;
}



int main() {
    int a[] = {1, 3, 2, 4};

    //X<BOUNDS<0, 10> > x;
    //ADD<X<BOUNDS<0, 10> >, X<BOUNDS<0, 10> > > x; 

    MULT<ADD<X<BOUNDS<0, 10> >, X<BOUNDS<0, 10> > >, ADD<X<BOUNDS<0, 10> >, X<BOUNDS<0, 10> > > >  x; 

    printf("Answer: %d Expected: %d\n", x.eval(a), (1 + 3) * (2 + 4));

    /*
    printf("\nCOMP6035 Coursework 2: Template Metaprogramming. \n"
            "Part I -- Expression Templates\n"
            "\nEvaluating expression x + (x-2) * (x-3), with x = 5 \n\n");

    // Equation  (x_{0,5} + 3) * ( x_{0,5} + 5) should have bounds 15-80 
    typedef MULT<
            ADD<X<BOUNDS<0, 5> >, LIT<3> >, 
            ADD<X<BOUNDS<0, 5> >, LIT<5> > 
        > Expr;
    Expr expr;

    
    printf("Answer = %d, Lower Bound: %d, Upper bound: %d\n\n", 
            expr.eval(3), expr.LOWER, expr.UPPER);
    
    printf("******* BEGIN EXTENSIVE TESTING *******\n\n");
    print_header();

    //Single variable
    X<BOUNDS<0, 10> > x;
    TestDetails test_0 = {.in_lo = 0, .in_hi = 10, 
                      .expected_lo = 0, .expected_hi = 10, 
                      .actual_lo = x.LOWER, .actual_hi = x.UPPER};
    print_test("x", test_0);
    
    //Single literal 
    LIT<5> c;
    TestDetails test_1 = {.in_lo = 5, .in_hi = 5, 
                      .expected_lo = 5, .expected_hi = 5, 
                      .actual_lo = c.LOWER, .actual_hi = c.UPPER};
    print_test("5", test_1);

    //Simple additon, literal and variable
    ADD<LIT<5>, X<BOUNDS<0,10> > >  add;
    TestDetails test_2 = {.in_lo = 0, .in_hi = 10, 
                      .expected_lo = (0 + 5), .expected_hi = (10 + 5), 
                      .actual_lo = add.LOWER, .actual_hi = add.UPPER};
    print_test("x + 5", test_2);

    //Simple addition, two variables
    ADD<X<BOUNDS<0,10> >, X<BOUNDS<0,10> > >  add2;
    TestDetails test_3 = {.in_lo = 0, .in_hi = 10, 
                      .expected_lo = (0 + 0), .expected_hi = (10 + 10), 
                      .actual_lo = add2.LOWER, .actual_hi = add2.UPPER};
    print_test("x + x", test_3);


    // Print a summary of success
    if(all_passed) 
        printf("\nAll tests passed successfully :)\n\n");
    else 
        printf("\nThere were problems with some of the tests!\n\n");

    //Competed succesfully, return 0
    return 0;
    */
}
