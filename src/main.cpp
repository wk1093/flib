#include "flib/flib.hpp"
#include <cstdio>

int main(void) {
    // fracti can be replaced with fract or frac and the answers will be identical
    // The internal workings are different, and some are faster and slower, and some will not work with bigger numbers.
    fracti a(20000, 300);
    fracti b(10000, 200);
    fracti c = a * b;
    c.frcPrint();
    c.decPrint();
    
}
