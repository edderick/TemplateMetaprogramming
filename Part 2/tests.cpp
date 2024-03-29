#include <stdio.h>
#include <stdlib.h>

#include "expr.h"

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
}
