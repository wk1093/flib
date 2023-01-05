#include "flib/flib.hpp"
#include <cstdio>

int main(void) {
    fracti a(20000, 300);
    fracti b(10000, 200);
    fracti c = a * b;
    c.frcPrint();
    c.decPrint();
    
}