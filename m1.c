#include <stdio.h>
#include <math.h>

#include "timer.h"
#include "pi_funs.h"

double pi_leibiniz (int n);
double pi_bbp (int n);
int adjust_rep_count (int n, double z, double x, double y);

int main (void)
{
    int i2 = 1;
    double tol = .000001;
    double abserr;
    double pi;

    printf ("Leibniz Series Method of Calculating Pi:\n\n");
    printf ("   Terms        Value                   Error\n");

    /*Determines the number of terms required to calculate pi within an error of     * 10^-6 using the leibniz series method
     */

    do
    {
        pi = pi_leibiniz (i2);
        abserr = fabs (pi - M_PI);
        printf ("%8d     %20.15f    %20.15f\n", i2, pi, abserr);
        i2 *= 2;
    }
    while (abserr > tol);

    printf ("\n\n");

    int i1 = 1;
    double abserr1;
    double pi1;

    printf ("Bailey-Borwein-Plouffe Series Method of Calculating Pi:\n\n");
    printf ("   Terms        Value                   Error\n");

    /*Determines the number of terms required to calculate pi within an error of     * 10^-6 using the bbp series method
     */

    do
    {
        pi1 = pi_bbp (i1);
        abserr1 = fabs (pi1 - M_PI);
        printf ("%8d     %20.15f    %20.15f\n", i1, pi1, abserr1);
        i1 *= 2;
    }
    while (abserr1 > tol);
    printf ("\n\n");

    double time;
    double time1;
    double time2;
    int j;
    double tmax = 2;
    double tmin = 1;
    int count = 1000;

    printf ("Timing the BBP Series Method:\n\n");
    printf ("   Time/Iteration          Total Time           Iterations\n");
    do
    {

        timer_start ();

        for (j = 0; j < count; j++)
        {
            pi_bbp (i1);
        }

        //adjust count such that cpu time is between tmin and tmax

        time = timer_stop ();
        time1 = time / ((double) count);
        printf (" %10.2f usec         %10.6f sec      %10d\n", time1 * 1.e6,
            time, count);
        count = adjust_rep_count ((int) count, time, tmin, tmax);

    }
    while ((time > tmax) || (time < tmin));
    printf ("\n\n");

    count = 1000;

    printf ("Timing the Leibniz Series Method:\n\n");
    printf ("   Time/Iteration          Total Time           Iterations\n");
    do
    {

        timer_start ();

        for (j = 0; j < count; j++)
        {
            pi_leibiniz (i2);
        }

        time = timer_stop ();

        //adjust count such that cpu time is between tmin and tmax

        time2 = time / ((double) count);
        printf (" %10.2f usec         %10.6f sec      %10d\n", time2 * 1.e6,
            time, count);
        count = adjust_rep_count ((int) count, time, tmin, tmax);

    }
    while ((time > tmax) || (time < tmin));
    printf ("\n\n");
    double q = time2 / time1;

    printf ("Speed up Factor: %10.2f\n\n", q);
}
