#include "csSQUARE.h"
extern csCNTR_VARS cv;
extern csCNTR_PARAMS cscp;
extern csCONTAINER csc;

void csSQUARE::init(int idp, RECT geometry)
{
    _cscp = cscp;
    id = staticCnt2(cscp, idp, "Colors", {50,50,50}, geometry,1);
}

void csSQUARE::newItem(int nx, int ny)
{
    csSQUARE_DATA data;
    _cscp.Geometry = {0};
    data.id = csc.csCNT_newContainer(id, _cscp);
    csLIST<csSQUARE_DATA>::insertEnd(data);
}

void csSQUARE::organize()
{
    RECT r = cv.CNTCLWRECT[id];
    int n = size();
    if(n > 0)
    {
        int xtlen = minSizeX + offset.cx;
        nx = r.right-2*marg.x;
    }
    else
     std::cout<<"csSQUARE::organize() : no Item !\n";

}
