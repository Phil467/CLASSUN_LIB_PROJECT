#ifndef CSSCROLLBAR_H
#define CSSCROLLBAR_H

#include <csBUTTONGRID.h>
#include <utlFx.h>

#define CS_SBAR_SURFACE 1
#define CS_SBAR_CONTAINER 2
#define CS_SBAR_HORIZONTAL 0
#define CS_SBAR_VERTICAL 1

class csSCROLLBAR
{
    public:
        typedef struct
        {
            float before, after;
        }csSB_PROPORTION;
        
        csSCROLLBAR(int idp=0, RECT geometry={0}, int sctype = CS_SBAR_SURFACE, bool orientation=CS_SBAR_HORIZONTAL);
        void init(int idp=0, RECT geometry={0}, int sctype = CS_SBAR_SURFACE, bool orientation=CS_SBAR_HORIZONTAL);
        virtual ~csSCROLLBAR();
        int getId();
        int* getIdPtr();
        void setClient(int idc, int idMask);
        csCNTR_PARAMS* getParams();
        void mouseLeaveHide(int alphaMin=10);
        void setPosition(float pos);
        void setScrollColors(csRGBA c1, csRGBA c2);

    protected:

    private:
    int* scType;
    int* idp, *idc;
    int* id, *idMask, idscroll;
    bool* orient;
    csSB_PROPORTION* prp;
    int*tLength;
    csLIST<RECT> rcs;
    csLIST<csLIST<HDC>> cloths;
    csLIST<csLIST<csRGBA>> colors;
    float *value, *value0, *scval;
    int *hmarg, *vmarg, *width, *rectSelect, *mhId;
    SIZE* szzoom, *oldClientSize;
    POINT *oldClientPos;
    csARGS Args;
};

csSCROLLBAR csAddHScrollBar(int* idp, int* idClient=0, int* idMask=0, int autoHideIntensity=5);
csSCROLLBAR csAddVScrollBar(int* idp, int* idClient=0, int* idMask=0, int autoHideIntensity=5);
#endif // CSSCROLLBAR_H
