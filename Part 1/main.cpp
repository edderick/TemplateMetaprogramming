#include <stdio.h>
#include <stdlib.h>

#include "expr.h"

// COMP6035 Coursework 2: Template Metaprogramming.
// Part I -- Expression Templates
//
// Author: Edward Seabrook      Date: 5th May 2014
//
// This code aims to fullfill this specification:
//
// Write a main() method that builds an expression as a type and evaluate it at
// some integer input value.  Print the results to standard out. 

//Keeps track of whether of not all tests so far have passed
bool all_passed = true;

//Prints the header to the table of test results 
void print_header() {
    printf("%-27s%-10s%-10s%-10s%-10s\n", 
            "Equation", "X val", "Expected", "Actual", "Passed");
}

//Prints out the results of the test case 
//If there was a failure it also sets all_passed to false
void print_test(const char* equation, int x, int expected, int actual) {
    printf("%-27s%-10d%-10d%-10d%-10s\n", 
            equation, 
            x, 
            expected, 
            actual, 
            (expected == actual) ? "Y" : "N");
    
    if (expected != actual) 
        all_passed = false;
}



int main() {
    printf("\nCOMP6035 Coursework 2: Template Metaprogramming. \n"
            "Part I -- Expression Templates\n"
            "\nEvaluating expression x + (x-2) * (x-3), with x = 5 \n\n");

    //Based on operator precedence (BODMAS), the expression is
    //interpreted as x + ((x-2) * (x-3))
    typedef ADD<X, MULT<SUB<X, LIT<2> >, SUB<X, LIT<3> > > > Expr;
    Expr expr;
    printf("Answer = %d\n\n", expr.eval(5));
    
    
    printf("******* BEGIN EXTENSIVE TESTING *******\n\n");
    print_header();

    //Test single variable
    X var;
    print_test("x", 1, 1, var.eval(1));

    //Test single literal
    LIT<2> c;
    print_test("2", 0, 2, c.eval(0));


    //==ADDITION TEST CASES==

    //Test single addition, both variables
    ADD<X, X> add;
    print_test("x + x", 1, 2, add.eval(1));

    //Test single addition, one literal, one variable
    ADD<X, LIT<3> > add2;
    print_test("x + 3", 2, 5, add2.eval(2));

    //Test single addition, one variable, one literal
    ADD<LIT<4>, X> add3;
    print_test("4 + x", 3, 7, add3.eval(3));
   
    //Test single addition, two literals
    ADD<LIT<1>, LIT<1> > add4;
    print_test("1 + 1", 0, 2, add4.eval(0));
    
    //Test Multiple addtion, literals
    ADD<ADD<LIT<1>, LIT<1> >, LIT<1> > add5;
    print_test("(1 + 1) + 1", 0, 3, add5.eval(0));

    //Test multiple addtion, variables
    ADD<X, ADD<X, X> > add6;
    print_test("x + (x + x)", 2, 6, add6.eval(2));

    //Test multiple addtion, variables and literals 
    ADD<ADD<LIT<1>, X>, ADD<X, LIT<1> > > add7;
    print_test("(1 + x) + (x + 1)", 2, 6, add7.eval(2));


    //==MULTIPLICATION TEST CASES==

    //Test single multiplication, both variables
    MULT<X, X> mult;
    print_test("x * x", 2, 4, mult.eval(2));

    //Test single multiplication, one literal, one variable
    MULT<X, LIT<3> > mult2;
    print_test("x * 3", 2, 6, mult2.eval(2));

    //Test single multiplication, one variable, one literal
    MULT<LIT<4>, X> mult3;
    print_test("4 * x", 3, 12, mult3.eval(3));
   
    //Test single multiplication, two literals
    MULT<LIT<5>, LIT<4> > mult4;
    print_test("5 * 4", 0, 20, mult4.eval(0));
    
    //Test Multiple multiplication, literals
    MULT<MULT<LIT<1>, LIT<2> >, LIT<3> > mult5;
    print_test("(1 * 2) * 3", 0, 6, mult5.eval(0));

    //Test multiple multiplication, variables
    MULT<X, MULT<X, X> > mult6;
    print_test("x * (x * x)", 2, 8, mult6.eval(2));

    //Test multiple multiplication, variables and literals 
    MULT<MULT<LIT<2>, X>, MULT<X, LIT<3> > > mult7;
    print_test("(2 * x) * (x * 3)", 2, 24, mult7.eval(2));


    //==SUBTRACTION TEST CASES==

    //Test single subtraction, both variables
    SUB<X, X> sub;
    print_test("x - x", 2, 0, sub.eval(2));

    //Test single subtraction, one literal, one variable
    SUB<X, LIT<3> > sub2;
    print_test("x - 3", 2, -1, sub2.eval(2));

    //Test single subtraction, one variable, one literal
    SUB<LIT<4>, X> sub3;
    print_test("4 - x", 3, 1, sub3.eval(3));
   
    //Test single subtraction, two literals
    SUB<LIT<5>, LIT<4> > sub4;
    print_test("5 - 4", 0, 1, sub4.eval(0));
    
    //Test Multiple subtraction, literals
    SUB<SUB<LIT<1>, LIT<2> >, LIT<3> > sub5;
    print_test("(1 - 2) - 3", 0, -4, sub5.eval(0));

    //Test multiple subtraction, variables
    SUB<X, SUB<X, X> > sub6;
    print_test("x - (x - x)", 2, 2, sub6.eval(2));

    //Test multiple subtraction, variables and literals 
    SUB<SUB<LIT<2>, X>, SUB<X, LIT<3> > > sub7;
    print_test("(2 - x) - (x - 3)", 2, 1, sub7.eval(2));


    //==DIVISION TEST CASES==

    //Test single division, both variables
    DIV<X, X> div;
    print_test("x / x", 2, 1, div.eval(2));

    //Test single division, one literal, one variable
    DIV<X, LIT<3> > div2;
    print_test("x / 3", 9, 3, div2.eval(9));

    //Test single division, one variable, one literal
    DIV<LIT<4>, X> div3;
    print_test("4 / x", 3, 1, div3.eval(3));
   
    //Test single division, two literals
    DIV<LIT<20>, LIT<4> > div4;
    print_test("20 / 4", 0, 5, div4.eval(0));
    
    //Test Multiple division, literals
    DIV<DIV<LIT<20>, LIT<2> >, LIT<5> > div5;
    print_test("(20 / 2) / 5", 0, 2, div5.eval(0));

    //Test multiple division, variables
    DIV<X, DIV<X, X> > div6;
    print_test("2 / (2 / 2)", 2, 2, div6.eval(2));

    //Test multiple division, variables and literals 
    DIV<DIV<LIT<2>, X>, DIV<X, LIT<2> > > div7;
    print_test("(8 / x) / (x / 2)", 4, 1, div7.eval(2));

    //--DIVIDE BY ZERO TEST CASES--
    // Theses test cases must be commented out if not in use, 
    // otherwise they will cause a compiler error
    
    //Test literal divide by zero
    /* 
    DIV<LIT<2>, LIT<0> > div0_1;
    print_test("2 / 0", 0, 0, div0_1.eval(0));
    */

    //Test simple divide by zero
    /*
    DIV<X, LIT<0> > div0_2;
    print_test("X / 0", 2, 0, div0_1.eval(2));
    */

    //Test Divide by zero, result of division
    /*
    DIV<LIT<20>, DIV<LIT<2> , LIT<5> > > div0_3;
    print_test("20 / (2 / 5)", 0, 0, div0_1.eval(0));
    */

    //==MIXED TEST CASES==

    //Test all combined 
    SUB<LIT<1>, MULT<DIV<ADD<LIT<7>, X> , LIT<3> > , X> > all;
    print_test("1 - (((7 + x) / 3) * x)", 2, -5, all.eval(2));

    // Print a summary of success
    if(all_passed) 
        printf("\nAll tests passed successfully :)\n\n");
    else 
        printf("\nThere were problems with some of the tests!\n\n");

    //Competed succesfully, return 0
    return 0;
}
