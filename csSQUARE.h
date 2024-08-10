#ifndef CSSQUARE_H
#define CSSQUARE_H
#include "genStruct.h"
#include "csCONTAINER.h"
#include "csBUTTON.h"

typedef struct
{
    int id;
    int x, y, cx, cy;
    int nCol, nRow;
}csSQUARE_DATA;


class csSQUARE: public csLIST<csSQUARE_DATA>
{
    public:
        csSQUARE(int _minSizeX=50, int _maxSizeX=100, int _sizeY=15,
                POINT _marg={2,2}, SIZE _offset={2,2}) : csLIST<csSQUARE_DATA>::csLIST()
        {
            minSizeX = _minSizeX;
            maxSizeX = _maxSizeX;
            marg = _marg;
            offset = _offset;
            sizeY = _sizeY;
        };

        void init(int idp, RECT geometry={300,300});
        void organize();
        void newItem(int nx, int ny);

        csCNTR_PARAMS* operator()()
        {
            return &_cscp;
        };

    private:
        int id;
        int nx;
        int minSizeX, maxSizeX, sizeY;
        POINT marg;
        SIZE offset;
        csCNTR_PARAMS _cscp;
};


#endif // CSSQUARE_H
