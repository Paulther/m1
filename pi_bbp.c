#include <stdio.h>

// Uses the BBP method to calculate pi

double pi_bbp (int n);

double pi_bbp (int n)
{
    double term = 0.;
    double nterm;
    double d = 0;
    double f = 16;

    for (int i = 0; i < n; i++)
    {
        f = (1. / 16.) * f;
        d = 8. * ((double) i);
        nterm =
            f * ((4. / (d + 1.)) - (2. / (d + 4.)) - (1. / (d + 5.)) -
            (1. / (d + 6.)));
        term = nterm + term;
    }
    return term;
}
 
