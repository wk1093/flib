#pragma once
#include <cstdio>
#include <cstdint>
#include <cmath>

// fraction classes
// frac {n, d} = n / d
// fract {n, d, p} = (n / d) * 10^p
// fracti {n, np, d, dp} = (n * 10^np) / (d * 10^dp)
// fracti has a bigger range but is slower, and uses more memory
// fract is a good middle ground
// frac is the fastest and uses the least memory, but has the smallest range
// fracti has the most operators

class frac {
private:
    int32_t num; // numerator
    int32_t den; // denominator

public:
    frac(int32_t n, int32_t d) {
        num = n;
        den = d;
        simplify();
    }
    frac(int32_t n) {
        num = n;
        den = 1;
        simplify();
    }
    frac() {
        num = 0;
        den = 1;
        simplify();
    }
    frac(float f) {
        num = f * 1000000;
        den = 1000000;
        simplify();
    }
    frac(double d) {
        num = d * 1000000;
        den = 1000000;
        simplify();
    }
    frac simplify() {
        if (den == 0) {
            printf("Warning: denominator is 0, answer is undefined.\n");
            return *this;
        }
        if (den < 0) {
            num *= -1;
            den *= -1;
        }
        int32_t a = num;
        int32_t b = den;
        int32_t c;
        while (a != 0) {
            c = a;
            a = b % a;
            b = c;
        }
        num /= b;
        den /= b;
        return *this;
    }
    frac operator+(frac f) {
        frac r;
        r.num = num * f.den + den * f.num;
        r.den = den * f.den;
        return r.simplify();
    }
    frac operator-(frac f) {
        frac r;
        r.num = num * f.den - den * f.num;
        r.den = den * f.den;
        return r.simplify();
    }
    frac operator*(frac f) {
        frac r;
        r.num = num * f.num;
        r.den = den * f.den;
        return r.simplify();
    }
    frac operator/(frac f) {
        frac r;
        r.num = num * f.den;
        r.den = den * f.num;
        return r.simplify();
    }
    frac operator+=(frac f) {
        num = num * f.den + den * f.num;
        den = den * f.den;
        return simplify();
    }
    frac operator-=(frac f) {
        num = num * f.den - den * f.num;
        den = den * f.den;
        return simplify();
    }
    frac operator*=(frac f) {
        num = num * f.num;
        den = den * f.den;
        return simplify();
    }
    frac operator/=(frac f) {
        num = num * f.den;
        den = den * f.num;
        return simplify();
    }
    frac operator=(frac f) {
        num = f.num;
        den = f.den;
        return *this;
    }
    frac operator=(int32_t l) {
        num = l;
        den = 1;
        return *this;
    }
    frac operator=(float f) {
        num = f * 1000000;
        den = 1000000;
        simplify();
        return *this;
    }
    frac operator=(double d) {
        num = d * 1000000;
        den = 1000000;
        simplify();
        return *this;
    }
    bool operator==(frac f) {
        return num == f.num && den == f.den;
    }
    bool operator!=(frac f) {
        return num != f.num || den != f.den;
    }
    bool operator>(frac f) {
        return num * f.den > den * f.num;
    }
    bool operator<(frac f) {
        return num * f.den < den * f.num;
    }
    bool operator>=(frac f) {
        return num * f.den >= den * f.num;
    }
    bool operator<=(frac f) {
        return num * f.den <= den * f.num;
    }
    void frcPrint() {
        simplify();
        printf("%ld/%ld\n", num, den);
    }
    void decPrint() {
        simplify();
        printf("%f\n", (double)num / (double)den);
    }

    operator float() {
        return (float)num / (float)den;
    }

    operator double() {
        return (double)num / (double)den;
    }

    operator int32_t() {
        return num / den;
    }


};

class fract {
private:
    int32_t num; // numerator
    int32_t den; // denominator
    int8_t power; // power of 10 frac = num / den * 10^power

public:
    fract(int32_t n, int32_t d) {
        num = n;
        den = d;
        power = 0;
        simplify();
    }
    fract(int32_t n) {
        num = n;
        den = 1;
        power = 0;
        simplify();
    }
    fract() {
        num = 0;
        den = 1;
        power = 0;
        simplify();
    }
    fract(float f) {
        num = f * 1000000;
        den = 1000000;
        power = 0;
        simplify();
    }
    fract(double d) {
        num = d * 1000000;
        den = 1000000;
        power = 0;
        simplify();
    }
    fract simplify() {
        if (den == 0) {
            printf("Warning: denominator is 0, answer is undefined.\n");
            return *this;
        }
        if (den < 0) {
            num *= -1;
            den *= -1;
        }
        int32_t a = num;
        int32_t b = den;
        int32_t c;
        while (a != 0) {
            c = a;
            a = b % a;
            b = c;
        }
        num /= b;
        den /= b;
        
        while (den % 10 == 0) {
            den /= 10;
            power--;
        }
        while(num % 10 == 0 && num != 0) {
            num /= 10;
            power++;
        }
        return *this;
    }
    fract operator+(fract f) {
        fract r;
        r.num = num * f.den + den * f.num;
        r.den = den * f.den;
        r.power = power;
        return r.simplify();
    }
    fract operator-(fract f) {
        fract r;
        r.num = num * f.den - den * f.num;
        r.den = den * f.den;
        r.power = power;
        return r.simplify();
    }
    fract operator*(fract f) {
        fract r;
        r.num = num * f.num;
        r.den = den * f.den;
        r.power = power + f.power;
        return r.simplify();
    }
    fract operator/(fract f) {
        fract r;
        r.num = num * f.den;
        r.den = den * f.num;
        r.power = power - f.power;
        return r.simplify();
    }
    fract operator+=(fract f) {
        num = num * f.den + den * f.num;
        den = den * f.den;
        return simplify();
    }
    fract operator-=(fract f) {
        num = num * f.den - den * f.num;
        den = den * f.den;
        return simplify();
    }
    fract operator*=(fract f) {
        num = num * f.num;
        den = den * f.den;
        power += f.power;
        return simplify();
    }
    fract operator/=(fract f) {
        num = num * f.den;
        den = den * f.num;
        power -= f.power;
        return simplify();
    }
    fract operator=(fract f) {
        num = f.num;
        den = f.den;
        power = f.power;
        return *this;
    }
    fract operator=(int32_t l) {
        num = l;
        den = 1;
        power = 0;
        return *this;
    }
    fract operator=(float f) {
        num = f * 1000000;
        den = 1000000;
        power = 0;
        simplify();
        return *this;
    }
    fract operator=(double d) {
        num = d * 1000000;
        den = 1000000;
        power = 0;
        simplify();
        return *this;
    }
    bool operator==(fract f) {
        return num == f.num && den == f.den && power == f.power;
    }
    bool operator!=(fract f) {
        return num != f.num || den != f.den || power != f.power;
    }
    bool operator>(fract f) {
        return num * f.den * pow(10, power - f.power) > den * f.num;
    }
    bool operator<(fract f) {
        return num * f.den * pow(10, power - f.power) < den * f.num;
    }
    bool operator>=(fract f) {
        return num * f.den * pow(10, power - f.power) >= den * f.num;
    }
    bool operator<=(fract f) {
        return num * f.den * pow(10, power - f.power) <= den * f.num;
    }
    fract operator++() {
        num += den;
        return *this;
    }
    fract operator++(int) {
        fract r = *this;
        num += den;
        return r;
    }
    fract operator--() {
        num -= den;
        return *this;
    }
    fract operator--(int) {
        fract r = *this;
        num -= den;
        return r;
    }
    fract operator-() {
        num *= -1;
        return *this;
    }
    fract operator+() {
        return *this;
    }
    fract operator^(int32_t p) {
        fract r = *this;
        for (int32_t i = 1; i < p; i++) {
            r *= *this;
        }
        return r;
    }
    fract operator^(fract f) {
        fract r = *this;
        for (int32_t i = 1; i < f.num; i++) {
            r *= *this;
        }
        return r;
    }
    fract operator^(float f) {
        fract r = *this;
        for (int32_t i = 1; i < f; i++) {
            r *= *this;
        }
        return r;
    }
    fract operator^(double d) {
        fract r = *this;
        for (int32_t i = 1; i < d; i++) {
            r *= *this;
        }
        return r;
    }
    fract operator^=(int32_t p) {
        fract r = *this;
        for (int32_t i = 1; i < p; i++) {
            r *= *this;
        }
        return r;
    }

    operator frac() {
        return frac(num, den) * (frac)pow(10, power);
    }
    operator float() {
        return (float)num / (float)den * pow(10, power);
    }
    operator double() {
        return (double)num / (double)den * pow(10, power);
    }

    void frcPrint() {
        simplify();
        printf("%ld/%ld*10^%d\n", num, den, power);
    }
    void decPrint() {
        simplify();
        printf("%f\n", (double)num / (double)den * pow(10, power));
    }

        



};

class fracti {
private:
    int32_t num; // numerator
    int32_t den; // denominator
    int8_t pownum; // power of 10 frac = (num * 10^pownum) / (den * 10^powden)
    int8_t powden;

public:
    fracti(int32_t n, int32_t d) {
        num = n;
        den = d;
        pownum = 0;
        powden = 0;
        simplify();
    }
    fracti(int32_t n) {
        num = n;
        den = 1;
        pownum = 0;
        powden = 0;
        simplify();
    }
    fracti() {
        num = 0;
        den = 1;
        pownum = 0;
        powden = 0;
        simplify();
    }
    fracti(float f) {
        num = f * 1000000;
        den = 1000000;
        pownum = 0;
        powden = 0;
        simplify();
    }
    fracti(double d) {
        num = d * 1000000;
        den = 1000000;
        pownum = 0;
        powden = 0;
        simplify();
    }
    fracti simplify() {
        if (den == 0) {
            printf("Warning: denominator is 0, answer is undefined.\n");
            return *this;
        }
        if (den < 0) {
            num *= -1;
            den *= -1;
        }
        int32_t a = num;
        int32_t b = den;
        int32_t c;
        while (a != 0) {
            c = a;
            a = b % a;
            b = c;
        }
        num /= b;
        den /= b;
        
        while (den % 10 == 0) {
            den /= 10;
            powden--;
        }
        while(num % 10 == 0 && num != 0) {
            num /= 10;
            pownum++;
        }
        return *this;
    }
    fracti operator+(fracti f) {
        fracti r;
        r.num = num * f.den + den * f.num;
        r.den = den * f.den;
        r.pownum = pownum;
        r.powden = powden;
        return r.simplify();
    }
    fracti operator-(fracti f) {
        fracti r;
        r.num = num * f.den - den * f.num;
        r.den = den * f.den;
        r.pownum = pownum;
        r.powden = powden;
        return r.simplify();
    }
    fracti operator*(fracti f) {
        fracti r;
        r.num = num * f.num;
        r.den = den * f.den;
        r.pownum = pownum + f.pownum;
        r.powden = powden + f.powden;
        return r.simplify();
    }
    fracti operator/(fracti f) {
        fracti r;
        r.num = num * f.den;
        r.den = den * f.num;
        r.pownum = pownum - f.pownum;
        r.powden = powden - f.powden;
        return r.simplify();
    }
    fracti operator+=(fracti f) {
        num = num * f.den + den * f.num;
        den = den * f.den;
        return simplify();
    }
    fracti operator-=(fracti f) {
        num = num * f.den - den * f.num;
        den = den * f.den;
        return simplify();
    }
    fracti operator*=(fracti f) {
        num = num * f.num;
        den = den * f.den;
        pownum += f.pownum;
        powden += f.powden;
        return simplify();
    }
    fracti operator/=(fracti f) {
        num = num * f.den;
        den = den * f.num;
        pownum -= f.pownum;
        powden -= f.powden;
        return simplify();
    }
    fracti operator=(fracti f) {
        num = f.num;
        den = f.den;
        pownum = f.pownum;
        powden = f.powden;
        return *this;
    }
    fracti operator=(int32_t n) {
        num = n;
        den = 1;
        pownum = 0;
        powden = 0;
        return *this;
    }
    fracti operator=(float f) {
        num = f * 1000000;
        den = 1000000;
        pownum = 0;
        powden = 0;
        simplify();
        return *this;
    }
    fracti operator=(double d) {
        num = d * 1000000;
        den = 1000000;
        pownum = 0;
        powden = 0;
        simplify();
        return *this;
    }
    bool operator==(fracti f) {
        return num * f.den * pow(10, pownum - f.pownum) == den * f.num * pow(10, powden - f.powden);
    }
    bool operator!=(fracti f) {
        return num * f.den * pow(10, pownum - f.pownum) != den * f.num * pow(10, powden - f.powden);
    }
    bool operator>(fracti f) {
        return num * f.den * pow(10, pownum - f.pownum) > den * f.num * pow(10, powden - f.powden);
    }
    bool operator<(fracti f) {
        return num * f.den * pow(10, pownum - f.pownum) < den * f.num * pow(10, powden - f.powden);
    }
    bool operator>=(fracti f) {
        return num * f.den * pow(10, pownum - f.pownum) >= den * f.num * pow(10, powden - f.powden);
    }
    bool operator<=(fracti f) {
        return num * f.den * pow(10, pownum - f.pownum) <= den * f.num * pow(10, powden - f.powden);
    }
    fracti operator++() {
        num += den;
        return *this;
    }
    fracti operator++(int) {
        fracti r = *this;
        num += den;
        return r;
    }
    fracti operator--() {
        num -= den;
        return *this;
    }
    fracti operator--(int) {
        fracti r = *this;
        num -= den;
        return r;
    }
    fracti operator-() {
        num *= -1;
        return *this;
    }
    fracti operator+() {
        return *this;
    }
    fracti operator!() {
        int32_t t = num;
        num = den;
        den = t;
        return *this;
    }
    fracti operator~() {
        num *= -1;
        return *this;
    }
    fracti operator^(int32_t n) {
        num = pow(num, n);
        den = pow(den, n);
        pownum *= n;
        powden *= n;
        return *this;
    }
    fracti operator^(fracti f) {
        num = pow(num, f.num);
        den = pow(den, f.den);
        pownum *= f.num;
        powden *= f.den;
        return *this;
    }
    fracti operator^(float f) {
        num = pow(num, f);
        den = pow(den, f);
        pownum *= f;
        powden *= f;
        return *this;
    }
    fracti operator^(double d) {
        num = pow(num, d);
        den = pow(den, d);
        pownum *= d;
        powden *= d;
        return *this;
    }
    fracti operator^(long double ld) {
        num = pow(num, ld);
        den = pow(den, ld);
        pownum *= ld;
        powden *= ld;
        return *this;
    }
    fracti operator^=(int32_t n) {
        num = pow(num, n);
        den = pow(den, n);
        pownum *= n;
        powden *= n;
        return *this;
    }
    fracti operator^=(fracti f) {
        num = pow(num, f.num);
        den = pow(den, f.den);
        pownum *= f.num;
        powden *= f.den;
        return *this;
    }
    fracti operator^=(float f) {
        num = pow(num, f);
        den = pow(den, f);
        pownum *= f;
        powden *= f;
        return *this;
    }
    fracti operator^=(double d) {
        num = pow(num, d);
        den = pow(den, d);
        pownum *= d;
        powden *= d;
        return *this;
    }
    fracti operator^=(long double ld) {
        num = pow(num, ld);
        den = pow(den, ld);
        pownum *= ld;
        powden *= ld;
        return *this;
    }
    fracti operator%(int32_t n) {
        num = num % (n * den);
        return *this;
    }
    fracti operator%(fracti f) {
        num = num % (f.num * den);
        den = den % (f.den * num);
        return *this;
    }
    fracti operator%=(int32_t n) {
        num = num % (n * den);
        return *this;
    }

    fracti operator%=(fracti f) {
        num = num % (f.num * den);
        den = den % (f.den * num);
        return *this;
    }
    fracti operator*(int32_t n) {
        num *= n;
        return *this;
    }
    fracti operator*(fracti f) {
        num *= f.num;
        den *= f.den;
        pownum += f.pownum;
        powden += f.powden;
        return *this;
    }
    fracti operator*(float f) {
        num *= f;
        pownum += f;
        return *this;
    }
    fracti operator*(double d) {
        num *= d;
        pownum += d;
        return *this;
    }
    fracti operator*(long double ld) {
        num *= ld;
        pownum += ld;
        return *this;
    }
    fracti operator*=(int32_t n) {
        num *= n;
        return *this;
    }
    fracti operator*=(fracti f) {
        num *= f.num;
        den *= f.den;
        pownum += f.pownum;
        powden += f.powden;
        return *this;
    }
    fracti operator*=(float f) {
        num *= f;
        pownum += f;
        return *this;
    }
    fracti operator*=(double d) {
        num *= d;
        pownum += d;
        return *this;
    }
    fracti operator*=(long double ld) {
        num *= ld;
        pownum += ld;
        return *this;
    }
    fracti operator/(int32_t n) {
        den *= n;
        return *this;
    }
    fracti operator/(fracti f) {
        num *= f.den;
        den *= f.num;
        pownum -= f.powden;
        powden -= f.pownum;
        return *this;
    }
    fracti operator/(float f) {
        den *= f;
        powden -= f;
        return *this;
    }
    fracti operator/(double d) {
        den *= d;
        powden -= d;
        return *this;
    }
    fracti operator/(long double ld) {
        den *= ld;
        powden -= ld;
        return *this;
    }
    fracti operator/=(int32_t n) {
        den *= n;
        return *this;
    }
    fracti operator/=(fracti f) {
        num *= f.den;
        den *= f.num;
        pownum -= f.powden;
        powden -= f.pownum;
        return *this;
    }
    fracti operator/=(float f) {
        den *= f;
        powden -= f;
        return *this;
    }
    fracti operator/=(double d) {
        den *= d;
        powden -= d;
        return *this;
    }
    fracti operator/=(long double ld) {
        den *= ld;
        powden -= ld;
        return *this;
    }
    fracti operator+(int32_t n) {
        num += n * den;
        return *this;
    }
    fracti operator+(fracti f) {
        num = num * f.den + f.num * den;
        den *= f.den;
        pownum += f.pownum;
        powden += f.powden;
        return *this;
    }
    fracti operator+(float f) {
        num += f * den;
        pownum += f;
        return *this;
    }
    fracti operator+(double d) {
        num += d * den;
        pownum += d;
        return *this;
    }
    fracti operator+(long double ld) {
        num += ld * den;
        pownum += ld;
        return *this;
    }
    fracti operator+=(int32_t n) {
        num += n * den;
        return *this;
    }
    fracti operator+=(fracti f) {
        num = num * f.den + f.num * den;
        den *= f.den;
        pownum += f.pownum;
        powden += f.powden;
        return *this;
    }
    fracti operator+=(float f) {
        num += f * den;
        pownum += f;
        return *this;
    }
    fracti operator+=(double d) {
        num += d * den;
        pownum += d;
        return *this;
    }
    fracti operator+=(long double ld) {
        num += ld * den;
        pownum += ld;
        return *this;
    }
    fracti operator-(int32_t n) {
        num -= n * den;
        return *this;
    }
    fracti operator-(fracti f) {
        num = num * f.den - f.num * den;
        den *= f.den;
        pownum += f.pownum;
        powden += f.powden;
        return *this;
    }
    fracti operator-(float f) {
        num -= f * den;
        pownum += f;
        return *this;
    }
    fracti operator-(double d) {
        num -= d * den;
        pownum += d;
        return *this;
    }
    fracti operator-(long double ld) {
        num -= ld * den;
        pownum += ld;
        return *this;
    }
    fracti operator-=(int32_t n) {
        num -= n * den;
        return *this;
    }
    fracti operator-=(fracti f) {
        num = num * f.den - f.num * den;
        den *= f.den;
        pownum += f.pownum;
        powden += f.powden;
        return *this;
    }

    operator fract() {
        return (fract)num / (fract)den * (fract)pow(10, pownum - powden);
    }
    operator float() {
        return (float)num / (float)den * (float)pow(10, pownum - powden);
    }
    operator double() {
        return (double)num / (double)den * (double)pow(10, pownum - powden);
    }
    operator long double() {
        return (long double)num / (long double)den * (long double)pow(10, pownum - powden);
    }
    operator frac() {
        return (frac)num / (frac)den * (frac)pow(10, pownum - powden);
    }

    void frcPrint() {
        if (pownum > 0) {
            if (powden > 0) {
                printf("%d * 10^%d / %d * 10^%d\n", num, pownum, den, powden);
            } else {
                printf("%d * 10^%d / %d\n", num, pownum, den);
            }
        } else {
            if (powden > 0) {
                printf("%d / %d * 10^%d\n", num, den, powden);
            } else {
                printf("%d / %d\n", num, den);
            }
        }
    }
    void decPrint() {
        printf("%f\n", (double)num / (double)den * pow(10, pownum - powden));
    }

};
