#include "complex_num.h"

complex_num::complex_num(double r, double i) : r(r), i(i) {
}

complex_num complex_num::operator +(complex_num w){
    complex_num z;
    z.r = r + w.r;
    z.i = i + w.i;
    return z;
}

complex_num complex_num::operator -(complex_num w){
    complex_num z;
    z.r = r - w.r;
    z.i = i - w.i;

    return z;
}

complex_num complex_num::operator *(complex_num w){
    complex_num z;
    z.r = (r * w.r - i * w.i);
    z.i = (r * w.i + i * w.r);
    return z;
}

complex_num complex_num::operator /(complex_num w){
    complex_num z;
    
    double a = r;
    double b = i;
    double c = w.r;
    double d = w.i;

    z.r = (a * c + b * d) / (c * c + d * d);
    z.i = (b * c - a * d) / (c * c + d * d);

    return z;
}

void complex_num::print(std::ostream &os){
    if(i >= 0)
        os << r << " + " << i << "i";
    else
        os << r << " - " << -1 * i << "i";
}