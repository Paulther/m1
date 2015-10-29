#include <stdio.h>
#include <math.h>

#include "timer.h"
#include "pi_funs.h"
#include "adjust.c"
#include "timer.c"

double pi_leibiniz (int n);

double pi_bbp (int n);

int  main(void)
{
    int i2 = 1;
    double tol = .000001;
    double abserr;
    double pi;
    do
    {
        pi = pi_leibiniz (i2);
        abserr = fabs (pi - M_PI);
        printf("%8d     %20.15f    %20.15f\n", i2 , pi, abserr);
        i2 *= 2;
    }
    while (abserr > tol);

    printf("\n\n");

    int i1 = 1;
    double abserr1;
    double pi1;
    do
    {
        pi1 = pi_bbp (i1);
        abserr1 = fabs (pi1 - M_PI);
        printf("%8d     %20.15f    %20.15f\n", i1 , pi1, abserr1);
        i1 *= 2;
    }
    while (abserr1 > tol);
    printf("\n\n");

    double time;
    double time1;
    int j;
    double tmax = 2;
    double tmin = 1;
    int count =  1000;
    do  
    {
          
          timer_start ();
          
          for ( j = 0; j < count; j++)
          {
               pi_bbp(i1);          
          }
      
          time = timer_stop ();
          time1 = time /((double) count);
          printf( " %10.2f usec         %10.6f sec      %10d\n", time1 * 1.e6,                      time, count);
          count = adjust_rep_count ((int) count, time, tmin, tmax);
       
    }
    while ((time > tmax) || (time < tmin));
    printf("\n\n");

    count =  1000;
    do  
    {
          
          timer_start ();
          
          for ( j = 0; j < count; j++)
          {
               pi_leibiniz(i2);          
          }
      
          time = timer_stop ();
          time1 = time /((double) count);
          printf( " %10.2f usec         %10.6f sec      %10d\n", time1 * 1.e6,                      time, count);
          count = adjust_rep_count ((int) count, time, tmin, tmax);
       
    }
    while ((time > tmax) || (time < tmin));
}
                                                       
double pi_leibiniz (int n)
{
    double term = 0.;
    int s;
    for (int i = 0; i < n; i++)
    {
       if ( i % 2 == 0)
       {
           s = 1;
       }
       else
       {
           s = -1;
       }
       double  nterm = 4.*s/(2.*i+1);
       term = term + nterm;
    }
return term;
} 

double pi_bbp (int n)
{
    double term = 0.;
    double nterm;
    double d = 0;
    double f = 16;
    for (int i = 0;  i < n; i++)
    {
        f = (1. / 16.) * f;
        d = 8. * ((double) i);
        nterm = f*((4./(d + 1.)) - (2./(d + 4.)) - (1./ (d + 5.)) -                             (1./(d + 6.)));
        term = nterm + term;
    }
return term;
}
