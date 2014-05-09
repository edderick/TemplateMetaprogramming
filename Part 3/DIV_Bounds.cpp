#include "stdio.h"

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

template<class L, class R>
struct DIV {

    static const int a = L::LOWER;
    static const int b = L::UPPER;
    static const int c = (R::LOWER == 0) ? 1 : R::LOWER;
    static const int d = (R::UPPER == 0) ? -1: R::UPPER;

    static const int lower_pppp = ((a >= 0) && (b > 0) && (c > 0) && (d > 0))
            ? a / d
            : 0;

    static const int lower_ppnp = ((a >= 0) && (b > 0) && (c < 0) && (d > 0))
            ? b / -1
            : 0;

    static const int lower_ppnn = ((a >= 0) && (b > 0) && (c < 0) && (d < 0))
            ? b / d
            : 0;

    static const int lower_nppp = ((a < 0) && (b < 0) && (c > 0) && (d > 0))
            ? a / c
            : 0;

    static const int lower_npnp = ((a < 0) && (b > 0) && (c < 0) && (d > 0))
            ? (((b < 0) ? -b : b) > (a < 0) ? -a : a) ? b / -1 : b / d
            : 0;

    static const int lower_npnn = ((a < 0) && (b >= 0) && (c < 0) && (d < 0))
            ? b / d
            : 0;

    static const int lower_nnpp = ((a < 0) && (b <= 0) && (c > 0) && (d > 0))
            ? a / c
            : 0;

    static const int lower_nnnp = ((a < 0) && (b <= 0) && (c < 0) && (d > 0))
            ? a / 1
            : 0;

    static const int lower_nnnn = ((a < 0) && (b <= 0) && (c < 0) && (d < 0))
            ? b / c
            : 0;

    static const int upper_pppp = ((a >= 0) && (b > 0) && (c > 0) && (d > 0))
            ? b / c
            : 0;

    static const int upper_ppnp = ((a >= 0) && (b > 0) && (c < 0) && (d > 0))
            ? b / 1
            : 0;

    static const int upper_ppnn = ((a >= 0) && (b > 0) && (c < 0) && (d < 0))
            ? a / c
            : 0;

    static const int upper_nppp = ((a < 0) && (b < 0) && (c > 0) && (d > 0))
            ? b / c
            : 0;

    static const int upper_npnp = ((a < 0) && (b > 0) && (c < 0) && (d > 0))
            ? (((b < 0) ? -b : b) > (a < 0) ? -a : a) ? a / -1 : a / d
            : 0;

    static const int upper_npnn = ((a < 0) && (b >= 0) && (c < 0) && (d < 0))
            ? a / d
            : 0;

    static const int upper_nnpp = ((a < 0) && (b <= 0) && (c > 0) && (d > 0))
            ? b / d
            : 0;

    static const int upper_nnnp = ((a < 0) && (b <= 0) && (c < 0) && (d > 0))
            ? a / -1
            : 0;

    static const int upper_nnnn = ((a < 0) && (b <= 0) && (c < 0) && (d < 0))
            ? a / d
            : 0;
    
    enum {
        LOWER = lower_pppp + lower_ppnp + lower_ppnn + lower_nppp + lower_npnp 
              + lower_npnn + lower_nnpp + lower_nnnp + lower_nnnn,

        UPPER = upper_pppp + upper_ppnp + upper_ppnn + upper_nppp + upper_npnp 
              + upper_npnn + upper_nnpp + upper_nnnp + upper_nnnn,
    };
    static inline int eval(int x) {
        int i = 0;
        return L::eval(x) / R::eval(x);
    };
};

int main () {

    DIV<X<BOUNDS<20,30> >, X<BOUNDS<5, 10> > > x;
    x.eval(1);

    printf("LOWER: %d\n", x.LOWER);
    printf("UPPER: %d\n", x.UPPER);
}
