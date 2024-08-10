#include "csUNITS.h"
#include <math.h>

#define EX 0.08181919084
#define EX2 EX*EX
#define EX4 EX2*EX2
#define EX6 EX2*EX2*EX2
#define K 0.9996

csUNITS::csUNITS()
{
    //ctor
}

csUNITS::~csUNITS()
{
    //dtor
}

double csDedToRad(double angle)
{

    return (angle*3.1415926535/180);
}

double err = 1804.5;

csGEO_COORDS csGeoToUTM(double ldce, double ldcn, bool unit, bool emisph)
{
    csGEO_COORDS llc = {0,0};
    double v, a, s, t, c,lat, n0, e,n,A = 6378.137, e0 = 500;

    if(emisph == 0)
        n0 = 10000;
    else n0 = 0;

    lat= csDedToRad(ldcn);
    v = 1/sqrt(1-EX2*sin(lat)*sin(lat));
    a = csDedToRad(ldce-(int(ldce)-int(ldce)%6+3))*cos(lat);
    s = (1-EX2/4-3*EX4/64-5*EX6/256)*lat-
      (3*EX2/8+3*EX4/32+45*EX6/1024)*sin(2*lat)+
      (15*EX4/256+45*EX6/1024)*sin(4*lat)-
      (35*EX6/3072)*sin(6*lat);
    t = tan(lat)*tan(lat);
    c = (EX2)*cos(lat)*cos(lat)/(1-EX2);

    e = e0+K*A*v*(a+(1-t+c)*pow(a,3)/6+(5-18*t+t*t)*pow(a,5)/120);
    n = n0+K*A*(s+v*tan(lat)*(a*a/2+(5-t+9*c+4*c*c)*pow(a,4)/24+(61-58*t+t*t)
                            *pow(a,6)/720));

    if (unit == 0) {e = e*1000; n = n*1000+err;};
    llc.lon = e;
    llc.lat = n + err/1000;
    return llc;
}