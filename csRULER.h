#ifndef CSRULER_H
#define CSRULER_H
#include "genStruct.h"
#include "csUNITS.h"

#define CS_RULER_HORIZONTAL 0
#define CS_RULER_VERTICAL 1

#define CS_RULER_TEXT_UNDER 0
#define CS_RULER_TEXT_OVER 1

#define MILLIMETER 1
#define CENTIMETER 10
#define DECIMETER 100
#define METER 1000

class csRULER
{
    public:
        csRULER(SIZE size = {1000,20}, bool _style = CS_RULER_TEXT_UNDER, double first = 0, double outdx=5, 
        unsigned unit=METER, unsigned dx=5, unsigned DX=5);
        HDC getDC();
        SIZE getSize();
        POINT getPos();
        bool getOrientation();
        void place(HDC dc, POINT p);
        virtual ~csRULER();
        RECT idMaskRect = {0};

    protected:

    private:
        SIZE size;
        POINT pos;
        bool orient, style;
        double first, outdx;
        unsigned unit, dx, DX;
        csDC rulerDC;

        csRGBA bkgCol, brdCol, linesCol1, linesCol2, textCol;
        unsigned l1, l2;
        HFONT hf;

};

#endif // CSRULER_H
