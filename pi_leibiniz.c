#include <stdio.h>

//Uses the Leibniz series to calculate pi

double pi_leibiniz (int n);

double pi_leibiniz (int n)
{
    double term = 0.;
    int s = 1;

    for (int i = 0; i < n; i++)
    {
        double nterm = 4. * s / (2. * i + 1);

        s = -s;
        term = term + nterm;
    }
    return term;
}

