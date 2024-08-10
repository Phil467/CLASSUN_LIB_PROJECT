#include "csCONTAINER.h"
extern csCNTR_VARS cv;

void csSetRegionCombiner(csARGS Args)
{
    static RGNDATA* pData;
    static HGLOBAL hData;
    int nbReg = *(int*)Args[2];
    hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(RGNDATAHEADER) + (sizeof(RECT) * nbReg));
    pData = (RGNDATA *)GlobalLock(hData);
    pData->rdh.dwSize = sizeof(RGNDATAHEADER);
    pData->rdh.iType = RDH_RECTANGLES;
    pData->rdh.nCount = pData->rdh.nRgnSize = 0;
    SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);
    Args.setArg(0,(void*)pData);
    Args.setArg(1,(void*)&hData);

}

void csCreateRectRegion(csARGS Args)
{
    RECT r = *(RECT*)Args[1];
    static HRGN reg=0;
    reg=CreateRectRgn(r.left,r.top,r.right,r.bottom);
    Args.setArg(0,(void*)&reg);
}
void csCreateRoundRectRegion(csARGS Args)
{
    RECT r = *(RECT*)Args[1];
    SIZE s = *(SIZE*)Args[2];
    static HRGN reg=0;
    reg=CreateRoundRectRgn(r.left,r.top,r.right,r.bottom, s.cx, s.cy);
    Args.setArg(0,(void*)&reg);
}
void csCreateEllipticRegion(csARGS Args)//create
{
    RECT r = *(RECT*)Args[1];
    static HRGN reg=0;
    reg=CreateEllipticRgn(r.left,r.top,r.right,r.bottom);
    Args.setArg(0,(void*)&reg);
}

void csCreatePolygonalRegion(csARGS Args)
{
    POINT* polyreg = (POINT*)Args[1];
    int len = *(int*)Args[2];
    static HRGN reg=0;
    reg=CreatePolygonRgn((const POINT*)polyreg,len,ALTERNATE);
    Args.setArg(0,(void*)&reg);
}

void csCombineRegion(csARGS Args)//size,move
{
    //RGNDATA* pData = (RGNDATA*)Args[1];
    HRGN* reg = (HRGN*)Args[2];
    int nbReg= *(int*)Args[3];
    int combType= *(int*)Args[4];
    int id = (int)Args;
    static HRGN mreg = 0;
    RECT r=cv.CNTRECT[id];
    /*********************************************/
    static RGNDATA* pData;
    static HGLOBAL hData;
    //int nbReg = *(int*)Args[2];
    hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(RGNDATAHEADER) + (sizeof(RECT) * nbReg));
    pData = (RGNDATA *)GlobalLock(hData);
    pData->rdh.dwSize = sizeof(RGNDATAHEADER);
    pData->rdh.iType = RDH_RECTANGLES;
    pData->rdh.nCount = pData->rdh.nRgnSize = 0;
    SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);
    /**************************************************/
    if(mreg)
        DeleteRgn(mreg);
    std::cout<<nbReg;
    mreg = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * nbReg), pData);
    CombineRgn(mreg, reg[0],reg[1], combType);
    if(nbReg>2)
        for(int i=0; i<nbReg; i++)
            CombineRgn(mreg, mreg,reg[i], combType);
    SetRectRgn(mreg,0,0,r.right-r.left,r.bottom-r.top);
    Args.setArg(0,(void*)&mreg);
}

void csInvertRegion(csARGS Args)//size,move
{
    int id = (int)Args;
    HRGN reg = *(HRGN*)Args[0];
    HDC hdc = cv.CTX[id].getDC();
    InvertRgn(hdc, reg);
}

void csApplyRegion(csARGS Args)//size,move
{
    HWND hwnd=(HWND)Args;
    HRGN mreg = *(HRGN*)Args[0];
    SetWindowRgn(hwnd,mreg,1);
}

/*void csFillRegion(int id,ZCOL col, UINT msg)
{
    if(msg==WM_PAINT)
    {   hbrs=CreateSolidBrush(col);
        FillRgn(hdc, mreg[id],hbrs);
        DeleteBrush(hbrs);
    }
}*/

