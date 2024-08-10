#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <windows.h>
#include <windowsx.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <map>
#include "TemplatesStruct.h"

#define CSUNIT 100.0
#define IDPG 0
#define IDPL 1
#define IDPL0 2
#define IDPL1 3
#define IDLN 4
#define IDLN0 5
#define MAXDEPTH 5000

#define SELECTNONE 0
#define SELECTPOINT 1
#define SELECTLINE 2
#define SELECTPOLYLINE 3
#define SELECTOBJECT 4

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct DLL_EXPORT
{
    long l, t, r, b;
}csRECT;

// madification 07/06/2024
/*typedef struct DLL_EXPORT
{
    int r, g, b;
}csRGB;*/

typedef struct DLL_EXPORT
{
    unsigned char r, g, b;
    double a;
}csRGBA, csRGB;

typedef struct DLL_EXPORT
{
    int h, s, l;
}csHSL;

typedef struct DLL_EXPORT
{
    double x, y, z, lightF;
    UINT idObj, idPoint;
} csPOINT3F;

typedef struct DLL_EXPORT
{
    double x, y, depth, lightF;
    UINT idObj, idPoint;
} csPOINT2F;

/*typedef struct
{
    int iObject, szObject;
    int defObjInc, defElInc, defDatInc;
    int*iElement,*szElement;
    int**iData,**szData;
}csMAT3PARAMS;*/

typedef struct DLL_EXPORT
{
    csPOINT2F A;
    csPOINT2F B;
    double XYCOEF, XZCOEF;
    void getXYDCoef()
    {
        double dx=A.depth-B.depth, dy=A.x-B.x;
        if(dx==0) dx=1;
        //if(dy==0) dy=1;
        XYCOEF = dy/dx;
    }
    void getXZDCoef()
    {
        double dx=A.depth-B.depth, dz=A.y-B.y;
        if(dx==0) dx=1;
        //if(dz==0) dz=1;
        XZCOEF = dz/dx;
    }
} csVECT2F;

typedef struct DLL_EXPORT
{
    csPOINT3F A;
    csPOINT3F B;
    double YZCOEF, XYCOEF, XZCOEF;
    /*void getYZDCoef(double thickness)
    {
        if(A.z==B.z) A.z++;
        if(A.y==B.y) A.y++;
        YZCOEF = (A.z-B.z)/(A.z-B.z);

    }
    void getXYDCoef(double thickness)
    {
        if(A.x==B.x) A.x++;
        if(A.y==B.y) A.y++;
        XYCOEF = (A.y-B.y)/(A.x-B.x);
    }
    void getXZDCoef(double thickness)
    {
        if(A.z==B.z) A.z++;
        if(A.x==B.x) A.x++;
        XZCOEF = (A.z-B.z)/(A.x-B.x);
    }*/
    void getYZDCoef()
    {
        double dy=A.y-B.y;
        if(dy==0) dy=1;
        YZCOEF = (A.z-B.z)/dy;

    }
    void getXYDCoef()
    {
        double dx=A.x-B.x;
        if(dx==0) dx=1;
        XYCOEF = (A.y-B.y)/dx;
        //XYCOEF = (A.y*fabs(A.x-MVP)-B.y*fabs(B.x-MVP))/DIV/dx;
    }
    void getXZDCoef()
    {
        double dx=A.x-B.x;
        if(dx==0) dx=1;
        XZCOEF = (A.z-B.z)/dx;
        //XZCOEF = (A.z*fabs(A.x-MVP)-B.z*fabs(B.x-MVP))/DIV/dx;
    }
}csVECT3F;

typedef struct DLL_EXPORT
{
    double dec, rad, cs, sn, tg;
} csANGLEF;

typedef struct DLL_EXPORT
{
    csANGLEF ax;
    csANGLEF ay;
    csANGLEF az;
} csANGLE3F;

typedef struct DLL_EXPORT
{
    csPOINT3F pos3f;
    csPOINT2F pos2f;
    csRGB color;
    double ray;
    double intensity;
    csPOINT3F pos3f2;
} csLIGHT;

typedef struct DLL_EXPORT
{
    double k0, k1, k2, k3, k4, k5;
}csCOEFS;

typedef struct DLL_EXPORT
{
    csPOINT3F *p3Table;
    int length, iLength;
    void init(int size);
    void insertEnd(csPOINT3F point3);
    void insertBegin(csPOINT3F point3);
    void insertAt(csPOINT3F point3, int position);
    void insertTableAt(csPOINT3F* point3, int position, int len);
    void insertTablePartAt(int position, csPOINT3F* point3, int begin, int len);
    void set(int idPoint, csPOINT3F point3);
    void deleteEnd();
    void deleteBegin();
    void deleteAt(int position);
    void deleteTableAtBegining(int len);
    void deleteTableAt(int position, int len);
    void print(int i);
    void printAll();
    void clear();
}csPPOINT3F;

typedef struct DLL_EXPORT
{
    csPOINT2F*p2Table;
    int length, iLength;
    void init(int size);
    void insertEnd(csPOINT2F point2);
    void insertBegin(csPOINT2F point2);
    void insertAt(csPOINT2F point2, int position);
    void insertTableAt(csPOINT2F* point2, int position, int len);
    void insertTablePartAt(int position, csPOINT2F* point2, int begin, int len);
    void set(int idPoint, csPOINT2F point2);
    void deleteEnd();
    void deleteBegin();
    void deleteAt(int position);
    void deleteTableAt(int position, int len);
    void print(int i);
    void printAll();
    void clear();
}csPPOINT2F;


typedef struct DLL_EXPORT
{
    struct csLIST<int> IDType;
    struct csLIST<int> IDObject;
    struct csLIST<int> IDElement;
    struct csLIST<int> IDPoint;
}csIDENTIFIERS;

typedef struct csLIST<double> csLFLOATLIST;
typedef struct csLIST<int> csINTLIST;
typedef struct csLIST<csRGB> csRGBLIST;
typedef struct csDATABASE<csPOINT3F> csP3DATA;
typedef struct csDATABASE<csRGB> csRGBDATA;
typedef std::map<int, HDC> MHDC;
typedef std::map<int, MHDC> MMHDC;
typedef std::map<int, HBITMAP> MHBITMAP;
typedef std::map<int, MHBITMAP> MMHBITMAP;
typedef std::map<int, POINT> MPOINT;
typedef std::map<int, RECT> MRECT;
typedef std::map<int, double> MDOUBLE;
typedef std::map<int, int> MINT;
typedef std::map<int, unsigned int> MLEN;
typedef std::map<int, char> MCHAR;
typedef std::map<int, char*> MPCHAR;
typedef std::map<int, BOOL> MBOOL;
typedef std::map<int, csPOINT2F> MCSPOINT2F;
typedef std::map<int, csPOINT3F> MCSPOINT3F;
typedef std::map<int, MCSPOINT3F> MMCSPOINT3F;
typedef std::map<int, MMCSPOINT3F> MMMCSPOINT3F;
typedef std::map<int, csVECT2F> MCSVECT2F;
typedef std::map<int, csVECT3F> MCSVECT3F;
typedef std::map<int, csRGB> MCSRGB;
typedef std::map<int, csCOEFS> MCSCOEFS;
typedef std::map<int, csANGLE3F> MCSANGLE3F;

void DLL_EXPORT csf_getMinMaxInt(int in0, int in1, int& outMax, int& outMin);
void DLL_EXPORT csf_printPoint3f(csPOINT3F p3);
csRGB DLL_EXPORT csTint2(csRGB color, csRGB target, float fraction);
void DLL_EXPORT csf_getMinMaxPoint3(csPPOINT3F p3list, csPOINT3F& ptmax, csPOINT3F& ptmin, int beg, int end);
COLORREF DLL_EXPORT TintInverse(csRGB color, csRGB target, float fraction);
double DLL_EXPORT csf_getDepthFromX2(csVECT2F vect2, double pt2_x);
double DLL_EXPORT csf_getDepthFromY2(csVECT2F vect2, double pt2_y);
void DLL_EXPORT csf_getMinMax(csPOINT2F p1,csPOINT2F p2,csPOINT2F& pmin,csPOINT2F& pmax);
bool DLL_EXPORT arePoint3Equals(csPOINT3F pt31, csPOINT3F pt32);
bool DLL_EXPORT arePoint2Equals(csPOINT3F pt21, csPOINT3F pt22);
double DLL_EXPORT square(double d);
double DLL_EXPORT csf_getZeroLength3f(csPOINT3F csp3);
double DLL_EXPORT csf_getLength2fv(csVECT2F vect2);
double DLL_EXPORT csf_getLength3fv(csVECT3F vect3);
double DLL_EXPORT csf_getLength2fp(csPOINT2F p1,  csPOINT2F p2);
double DLL_EXPORT csf_getLength3fp(csPOINT3F p1,  csPOINT3F p2);
csRGB DLL_EXPORT csTint(csRGB color, csRGB target, float fraction);
double DLL_EXPORT csf_getDepthFromY(csVECT3F vect3, double pt2_y);
double DLL_EXPORT csf_getDepthFromX(csVECT3F vect3, double pt2_x);
void DLL_EXPORT csf_Vect2FromVect3(csVECT2F& csv2, csVECT3F csv3);
void DLL_EXPORT csf_Point2FromPoint3(csPOINT2F& csp2, csPOINT3F csp3, csANGLEF csa);
double DLL_EXPORT absd(double d);
csRGB DLL_EXPORT hsl_to_rgb(csHSL hsl);
csHSL DLL_EXPORT rgb_to_hsl(csRGB rgb);
int DLL_EXPORT light_from_rgb(csRGB rgb);
void DLL_EXPORT get_min_max_point(POINT* plist, int len, POINT& ptmax, POINT& ptmin);
COLORREF DLL_EXPORT Tint(csRGB color, csRGB target, float fraction);
COLORREF DLL_EXPORT Tint2(csRGB color, csRGB target, float fraction);
double DLL_EXPORT csf_degToRad(double deg);
double DLL_EXPORT csf_radToDeg(double rad);
csPOINT2F p2Rot(csPOINT2F pt, csPOINT2F pc, double ang);
csPOINT2F p2RotZero(csPOINT2F pt, double ang);
#ifdef __cplusplus
}
#endif


#endif // STRUCTURES_H_INCLUDED
