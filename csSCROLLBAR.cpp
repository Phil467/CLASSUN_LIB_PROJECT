#include "csSCROLLBAR.h"


extern csCNTR_VARS cv;
extern csCNTR_PARAMS cscp;
void resize(csARGS Args);
void lbtnDown(csARGS Args);
void mouseMove(csARGS Args);
void mouseLeave_(csARGS Args);
void timer_(csARGS Args);
void lbtnup_(csARGS Args);

csSCROLLBAR::csSCROLLBAR(int idp, RECT geometry, int sctype, bool orientation)
{
    init(idp, geometry, sctype, orientation);
}


csCNTR_PARAMS* csSCROLLBAR::getParams()
{
    return cv.cp[*id];
}

void csSCROLLBAR::setScrollColors(csRGBA c1, csRGBA c2)
{
    colors[2][0] = c1;
    colors[2][0] = c2;

    if(Args.getArgNumber())
    {
        Args.setArg(1, colors.getTable());
    }
}

void csSCROLLBAR::init(int _idp, RECT geometry, int _sctype, bool orientation)
{
    //idp = csf_alloc2<int>(1,_idp);
    id = csf_alloc2<int>(1,0);
    idc = csf_alloc2<int>(1,0);
    idMask = csf_alloc2<int>(1,0);
    if(orientation == CS_SBAR_HORIZONTAL)
        width = csf_alloc2<int>(1,geometry.bottom);
    else
        width = csf_alloc2<int>(1,geometry.right);
    orient = csf_alloc2<bool>(1,orientation);
    scType = csf_alloc2<int>(1,_sctype);
    tLength = csf_alloc2<int>(1,0);
    hmarg = csf_alloc2<int>(1,1);;
    vmarg = csf_alloc2<int>(1,1);
    rectSelect = csf_alloc2<int>(1,-1);
    mhId = csf_alloc2<int>(1,0);
    value = csf_alloc2<float>(1,0.5);
    value0 = csf_alloc2<float>(1,0.5);
    scval = csf_alloc2<float>(1,0.2);
    szzoom = csf_alloc2<SIZE>(1,{200,100});
    oldClientPos = csf_alloc2<POINT>(1,{0,0});
    oldClientSize = csf_alloc2<SIZE>(1,{0,0});

    //if(orientation == CS_SBAR_HORIZONTAL)
    {
        rcs.insertEnd({*hmarg,*vmarg,*width-*hmarg,*width-*vmarg});
        rcs.insertEnd({rcs[0].right,*vmarg,rcs[0].right,*width-*vmarg});
        rcs.insertEnd({rcs[1].right,*vmarg,rcs[1].right+szzoom->cx+(szzoom->cy)/2,*width-*vmarg});
        rcs.insertEnd({rcs[2].right,*vmarg,geometry.right-*width-*hmarg,*width-*vmarg});
        rcs.insertEnd({rcs[3].right,*vmarg,geometry.right-*hmarg,*width-*vmarg});

    }
    colors += csNewList<csRGBA>();
    colors += csNewList<csRGBA>();
    colors += csNewList<csRGBA>();
    colors += csNewList<csRGBA>();

    goto dark;

    light:
    {
        colors[0].insertEnd({150,150,15});
        colors[0].insertEnd({150,150,150});
        colors[0].insertEnd({240,240,240});
        colors[0].insertEnd({150,150,150});
        colors[0].insertEnd({150,150,15});

        colors[1].insertEnd({150,150,15});
        colors[1].insertEnd({150,150,150});
        colors[1].insertEnd({240,240,240});
        colors[1].insertEnd({150,150,150});
        colors[1].insertEnd({150,150,15});

        colors[2].insertEnd({200,200,30});
        colors[2].insertEnd({180,180,180});
        colors[2].insertEnd({255,255,255});
        colors[2].insertEnd({180,180,180});
        colors[2].insertEnd({200,200,30});

        colors[3].insertEnd({200,200,30});
        colors[3].insertEnd({180,180,180});
        colors[3].insertEnd({30,30,30});
        colors[3].insertEnd({180,180,180});
        colors[3].insertEnd({200,200,30});
    }

    dark:
    {
        colors[0].insertEnd({200,200,30});
        colors[0].insertEnd({70,70,70});
        colors[0].insertEnd({30,30,30});
        colors[0].insertEnd({70,70,70});
        colors[0].insertEnd({200,200,30});

        colors[1].insertEnd({150,150,15});
        colors[1].insertEnd({80,80,80});
        colors[1].insertEnd({35,35,35});
        colors[1].insertEnd({80,80,80});
        colors[1].insertEnd({150,150,15});

        colors[2].insertEnd({30,30,30});
        colors[2].insertEnd({50,50,50});
        colors[2].insertEnd({55,55,55});
        colors[2].insertEnd({50,50,50});
        colors[2].insertEnd({200,200,30});

        colors[3].insertEnd({200,200,30});
        colors[3].insertEnd({180,180,180});
        colors[3].insertEnd({30,30,30});
        colors[3].insertEnd({180,180,180});
        colors[3].insertEnd({200,200,30});
    }


    *id = staticCnt2(cscp, _idp, "", {30,30,30},geometry,1);
    cv.CTX[*id].setCntBorder({10,10,10}, 1);
    if(orientation == CS_SBAR_HORIZONTAL)
        cv.cp[*id]->Cursor = LoadCursor(0,IDC_SIZEWE);
    else
        cv.cp[*id]->Cursor = LoadCursor(0,IDC_SIZENS);
//std::cout<<"frtydtrdtdtdtd----------\n";

    bool*block = csf_alloc2<bool>(1,0);

    Args.setArgNumber(19);
    Args.makeArgs(rcs.getTable(), colors.getTable(), value, value0, hmarg, vmarg, 
                    width, szzoom, orient, tLength, rectSelect, mhId, scval, idc, 
                    scType, idMask, block, oldClientPos, oldClientSize);
    csSetAction(*id, WM_SIZE, resize, Args);
    csSetAction(*id, WM_LBUTTONDOWN, lbtnDown, Args);
    csSetAction(*id, WM_LBUTTONUP, lbtnup_, Args);
    csSetAction(*id, WM_MOUSEMOVE, mouseMove, Args);
    csSetAction(*id, WM_MOUSELEAVE, mouseLeave_, Args);
    csSetAction(*id, WM_TIMER, timer_, Args);
}

int csSCROLLBAR::getId()
{
    return *id;
}
int* csSCROLLBAR::getIdPtr()
{
    return id;
}

void csSCROLLBAR::setPosition(float pos)
{
    if(*idc && *idMask)
    {
        if(*orient == CS_SBAR_HORIZONTAL)
        {
            int totalLengthScrollable = cv.CTX[*idc].getDwgSurfSize().cx;
            int hiddenPart = cv.CNTRECT[*idc].left+totalLengthScrollable-cv.CNTRECT[*idMask].right;
            POINT p = cv.CTX[*idc].getDwgSurfPos();
            if(hiddenPart > 0)
            {
                int xpos = -pos*hiddenPart;
                //std::cout<<"xpos = "<<xpos<<"\n";
                cv.CTX[*idc].setDwgSurfPos({xpos, p.y});
            }
            
        }
        else
        {
            int totalLengthScrollable = cv.CTX[*idc].getDwgSurfSize().cy;
            int hiddenPart = cv.CNTRECT[*idc].top+totalLengthScrollable-cv.CNTRECT[*idMask].bottom;
            POINT p = cv.CTX[*idc].getDwgSurfPos();
            if(hiddenPart > 0)
            {
                int ypos = -pos*hiddenPart;
                cv.CTX[*idc].setDwgSurfPos({p.x, ypos});
            }
            
        }
    }
    else
    {
        *value0 = *value = pos; 
    }
}

void csSCROLLBAR::mouseLeaveHide(int alphaMin)
{
    getParams()->AutoAlphaFade.Geometry = {0,0,0,0};
    getParams()->AutoAlphaFade.FadeTime = 8;
    getParams()->AutoAlphaFade.AlphaMin = alphaMin;
    getParams()->AutoAlphaFade.State = CS_AAF_HIDE_CNTR;
    getParams()->AutoAlphaFade.SetGeometry = 0;
    getParams()->MouseLeaveTransparency = 1;
    SendMessage(cv.CNTLIST[*id],WM_MOUSELEAVE,0,0);
}
void csSCROLLBAR::setClient(int _idc, int _idMask)
{
    *idc = _idc;
    *idMask = _idMask;
    if(*scType == CS_SBAR_SURFACE)
    {
        *oldClientPos = cv.CTX[*idc].getDwgSurfPos();
    }
}

void resize(csARGS Args)
{
    int id = int(Args);
    RECT*rcs = (RECT*)Args[0];
    csLIST<csRGBA>* colors = (csLIST<csRGBA>*)Args[1];
    float* value = (float*)Args[2];
    float* value0 = (float*)Args[3];
    int hmarg = *(int*)Args[4];
    int vmarg = *(int*)Args[5];
    int width = *(int*)Args[6];
    SIZE* szzoom = (SIZE*)Args[7];
    bool orientation = *(bool*)Args[8];
    float *scval = (float*)Args[12];

    
    int idc = *(int*)Args[13];
    int scType = *(int*)Args[14];
    int idMask = *(int*)Args[15];
    bool *block = (bool*)Args[16]; // bloque une partie du code pour des receptions venant wm_mouseMouve

    SIZE sz={0};
    //csSizeSyncDelta(int(Args), sz);
    RECT r = cv.CNTCLWRECT[id];

    //SIZE*oldClientSize = (SIZE*)Args[18];
//oldClientSize->cy = cv.CTX[idc].getDwgSurfSize().cy;
//std::cout<<"5555555\n";
    if(orientation == CS_SBAR_HORIZONTAL)
    {
        if(idMask && idc && !*block)
        {
            int visiblePart = cv.CNTRECT[idMask].right-cv.CNTRECT[idc].left;
            if(scType == CS_SBAR_SURFACE)
            {
                int totalLengthScrollable = cv.CTX[idc].getDwgSurfSize().cx;
                *scval = float(visiblePart)/totalLengthScrollable;
                
                int cx = (totalLengthScrollable-visiblePart);
                POINT pos = cv.CTX[idc].getDwgSurfPos();
                int hiddenPart = abs(pos.x);
                int diff = totalLengthScrollable-hiddenPart+cv.CNTRECT[idc].left - cv.CNTRECT[idMask].right;
                if(diff < 0)
                {
                    hiddenPart += diff; // puisque hiddenPart est positif
                    cx = (totalLengthScrollable-visiblePart+diff);
                    cv.CTX[idc].setDwgSurfPos({pos.x-diff, pos.y});
                }

                if(cx <= 0)
                {
                    *value = *value0 = 0;
                    *scval = 1;
                }
                else
                {
                    *value = float(hiddenPart)/cx;
                    *value0 = *value;
                }

            }
        }

        int a = r.right - (hmarg + width)*2;
        szzoom->cx = ceil(a**scval);
        int tlen = a - szzoom->cx;
        *(int*)Args[9] = tlen;
        rcs[1] = {rcs[0].right,vmarg,rcs[0].right+tlen**value,width-vmarg};
        rcs[2] = {rcs[1].right,vmarg,rcs[1].right+szzoom->cx/*+(szzoom->cy)/2*/,width-vmarg};
        rcs[3] = {rcs[2].right,vmarg,r.right-width-hmarg,width-vmarg};
        rcs[4] = {rcs[3].right,vmarg,r.right-hmarg,width-vmarg};
    }
    else
    {
        if(idMask && idc && !*block)
        {
            int visiblePart = cv.CNTRECT[idMask].bottom-cv.CNTRECT[idc].top;
            if(scType == CS_SBAR_SURFACE)
            {
                int totalLengthScrollable = cv.CTX[idc].getDwgSurfSize().cy;
                *scval = float(visiblePart)/totalLengthScrollable;

                int cy = (totalLengthScrollable-visiblePart);
                POINT pos = cv.CTX[idc].getDwgSurfPos();
                int hiddenPart = abs(pos.y);
                int diff = totalLengthScrollable-hiddenPart+cv.CNTRECT[idc].top - cv.CNTRECT[idMask].bottom;
                if(diff < 0)
                {
                    hiddenPart += diff; // puisque hiddenPart est positif
                    cy = (totalLengthScrollable-visiblePart+diff);
                    cv.CTX[idc].setDwgSurfPos({pos.x, pos.y-diff});
                }
                if(cy <= 0)
                {
                    *value = *value0 = 0;
                    *scval = 1;
                }
                else
                {
                    *value = float(hiddenPart)/cy;
                    *value0 = *value;
                }
                
            }
        }

        int a = r.bottom - (vmarg + width)*2;
        szzoom->cx = ceil(a**scval);
        int tlen = a - szzoom->cx;
        *(int*)Args[9] = tlen;
        rcs[1] = {hmarg,rcs[0].bottom,width-hmarg,rcs[0].bottom+tlen**value};
        rcs[2] = {hmarg, rcs[1].bottom,width-hmarg,rcs[1].bottom+szzoom->cx/*+(szzoom->cy)/2*/};
        rcs[3] = {hmarg,rcs[2].bottom,width-hmarg,r.bottom-width-vmarg};
        rcs[4] = {hmarg,rcs[3].bottom,width-hmarg,r.bottom-vmarg};
    }

    //HDC dc = cv.CTX[id].redrawBackground();
    HDC dc = cv.CTX[id].getDC();
    for(int i=0; i<5; i++)
    {
        csRGBA col = colors[0][i];
        HBRUSH hb = CreateSolidBrush(RGB(col.r, col.g, col.b));
        HPEN hp = CreatePen(0,0,RGB(col.r+10, col.g+10, col.b+10));
        SelectBrush(dc,hb);
        SelectBrush(dc,hp);
        Rectangle(dc,rcs[i].left, rcs[i].top, rcs[i].right, rcs[i].bottom);
        DeleteBrush(hb);
        DeleteBrush(hp);
    }
    InvalidateRect(HWND(Args), 0,1);
    
    *block = 0; // vaut 1 pour une reception (sendmessage) venant de wm_mouseMouve
}

void lbtnDown(csARGS Args)
{
    RECT*rcs = (RECT*)Args[0];
    float* value = (float*)Args[2];
    float* value0 = (float*)Args[3];
    int* rectSelect = (int*)Args[10];
    *value0 = *value;
    
    POINT p1 = cv.TRACKING_POINT;
    ScreenToClient(cv.CNTLIST[int(Args)], &p1);
    if(PtInRect(&rcs[1], p1) || PtInRect(&rcs[2], p1) || PtInRect(&rcs[3], p1))
        *rectSelect = 1;
    else if(PtInRect(&rcs[2], p1))
        *rectSelect = 2;
    else if(PtInRect(&rcs[0], p1))
        *rectSelect = 0;
    else if(PtInRect(&rcs[4], p1))
        *rectSelect = 4;
    else 
        *rectSelect = -1;
}

void mouseMove(csARGS Args)
{
    RECT*rcs = (RECT*)Args[0];
    int tlen = *(int*)Args[9];
    float* value = (float*)Args[2];
    float* value0 = (float*)Args[3];
    bool orientation = *(bool*)Args[8];
    int rectSelect = *(int*)Args[10];
    int* mhId = (int*)Args[11];
    csLIST<csRGBA>* colors = (csLIST<csRGBA>*)Args[1];
    POINT*oldClientPos = (POINT*)Args[17];

    int idc = *(int*)Args[13];
    int scType = *(int*)Args[14];
    int idMask = *(int*)Args[15];

    bool *block = (bool*)Args[16];
    *block = 1;

    POINT p2;
    GetCursorPos(&p2);
    ScreenToClient(cv.CNTLIST[int(Args)], &p2);
    POINT p1 = cv.TRACKING_POINT;
    ScreenToClient(cv.CNTLIST[int(Args)], &p1);

    /*int mh = *mhId;
    for(int i=0; i<5; i++)
    {
        if(PtInRect(&rcs[i], p2))
        {
            if(*mhId != i)
            {
                colors[0][i] = colors[2][i];
                if(*mhId != -1)
                    colors[0][*mhId] = colors[1][*mhId];
                *mhId = i;
            }
            break;
        }
    }

    if(*mhId != mh)
            SendMessage(HWND(Args),WM_SIZE,0,0);*/

    if(WPARAM(Args) == 1 && cv.HWNDCAPTURE == HWND(Args))
    {
        float *scval = (float*)Args[12];
        if(rectSelect == 1 && *scval < 1 /*si le scroller n'occupe pas tout l'espace*/)
        {
            if(orientation == CS_SBAR_HORIZONTAL)
                *value = *value0 + float(p2.x-p1.x)/tlen;
            else
                *value = *value0 + float(p2.y-p1.y)/tlen;
            if(*value<0.0) *value = 0;
            if(*value>1.0) *value = 1.0;

            if(idc && idMask)
            {
                if(scType == CS_SBAR_SURFACE)
                {
                    if(orientation == CS_SBAR_HORIZONTAL)
                    {
                        int d = cv.CNTRECT[idMask].right-cv.CNTRECT[idc].left;
                        int cx = (cv.CTX[idc].getDwgSurfSize().cx-d);
                        if (cx < 0) cx = 0;
                        int len = ceil(*value*cx);
                        cv.CTX[idc].setDwgSurfPos({-len, cv.CTX[idc].getDwgSurfPos().y});
                        *oldClientPos = cv.CTX[idc].getDwgSurfPos();
                        InvalidateRect(cv.CNTLIST[idc],0,1);
                    }
                    else
                    {
                        int d = cv.CNTRECT[idMask].bottom-cv.CNTRECT[idc].top;
                        int cy = (cv.CTX[idc].getDwgSurfSize().cy-d);
                        if (cy < 0) cy = 0;
                        int len = ceil(*value*cy);
                        cv.CTX[idc].setDwgSurfPos({cv.CTX[idc].getDwgSurfPos().x, -len});
                        *oldClientPos = cv.CTX[idc].getDwgSurfPos();
                        InvalidateRect(cv.CNTLIST[idc],0,1);
                    }
                }
            }

            SendMessage(HWND(Args),WM_SIZE,0,0);
        }
    }
    //SendMessage(HWND(Args),WM_SIZE,0,0);
    //InvalidateRect(HWND(Args), 0,1);
    
}

void mouseLeave_(csARGS Args)
{
    csLIST<csRGBA>* colors = (csLIST<csRGBA>*)Args[1];
    int* mhId = (int*)Args[11];
    //if(*mhId != -1)
    colors[0][*mhId] = colors[1][*mhId];
    *mhId = -1;
    SendMessage(HWND(Args),WM_SIZE,0,0);
}

void lbtnup_(csARGS Args)
{
    
    float* value = (float*)Args[2];
    float* value0 = (float*)Args[3];
    *value0 = *value;
}

void timer_(csARGS Args)
{
    int idc = *(int*)Args[13];
    int scType = *(int*)Args[14];
    //float* value = (float*)Args[2];
    //float* value0 = (float*)Args[3];
    bool orientation = *(bool*)Args[8];
    POINT*oldClientPos = (POINT*)Args[17];
    SIZE*oldClientSize = (SIZE*)Args[18];
    //int idMask = *(int*)Args[15];
    //bool *block = (bool*)Args[16];

    if(scType == CS_SBAR_SURFACE)
    {
        if(orientation == CS_SBAR_HORIZONTAL)
        { 
            if(oldClientPos->x != cv.CTX[idc].getDwgSurfPos().x)
            {
                oldClientPos->x = cv.CTX[idc].getDwgSurfPos().x;
                SendMessage((HWND)Args,WM_SIZE,0,0);
            }
            else if(oldClientSize->cx != cv.CTX[idc].getDwgSurfSize().cx)
            {
                int idMask = *(int*)Args[15];
                float* value = (float*)Args[2];
                float* value0 = (float*)Args[3];
                float *scval = (float*)Args[12];
                if(cv.CTX[idc].getDwgSurfSize().cx < cv.CNTCLWRECT[idMask].right)
                {
                    *value = *value0 = 0;
                    *scval = 1;
                }
                oldClientSize->cx = cv.CTX[idc].getDwgSurfSize().cx;
            }
        }
        else if(orientation == CS_SBAR_VERTICAL)
        {
            if(oldClientPos->y != cv.CTX[idc].getDwgSurfPos().y)
            {
                oldClientPos->y = cv.CTX[idc].getDwgSurfPos().y;
                SendMessage((HWND)Args,WM_SIZE,0,0);
            }
            else if(oldClientSize->cy != cv.CTX[idc].getDwgSurfSize().cy) // superflux, modifer
            {   //std::cout<<"hey00000\n";
                int idMask = *(int*)Args[15];
                float* value = (float*)Args[2];
                float* value0 = (float*)Args[3];
                float *scval = (float*)Args[12];
                if(cv.CTX[idc].getDwgSurfSize().cy < cv.CNTCLWRECT[idMask].bottom)
                {
                    *value = *value0 = 0;
                    *scval = 1;
                    //InvalidateRect((HWND)Args,0,1); // renvoie une boucle infinie ... pourquoi ????
                }
                oldClientSize->cy = cv.CTX[idc].getDwgSurfSize().cy;
            }
        }
    }
}

csSCROLLBAR::~csSCROLLBAR()
{
    //dtor
}


void smoothScrolling(csARGS Args);

csSCROLLBAR csAddHScrollBar(int* idp, int* idClient, int* idMask, int autoHideIntensity)
{
    RECT r = cv.CNTCLWRECT[*idp];
    int*idc = idClient;
    if(!idc) idc = idp;
    csSCROLLBAR hscroll(*idp, {0,r.bottom-10,r.right,10});
    if(idMask)
    {
        cv.CTX[*idc].idMask = *idMask;
        hscroll.setClient(*idc,*idMask);
    }
    else
    {
        cv.CTX[*idc].idMask = *idp;
        hscroll.setClient(*idc,*idp);
    }
    hscroll.mouseLeaveHide(autoHideIntensity);
    SetTimer(cv.CNTLIST[hscroll.getId()],0,18,0);
    csSetAction(*idc,WM_MOUSEWHEEL,smoothScrolling,1,hscroll.getIdPtr());

    cv.CTX[*idc].hScrollBarId = hscroll.getId(); //rafraichit le scrollBar a partir de MouseWheel
    return hscroll;
}
csSCROLLBAR csAddVScrollBar(int* idp, int* idClient, int* idMask, int autoHideIntensity)
{
    RECT r = cv.CNTCLWRECT[*idp];
    int*idc = idClient;
    if(!idc) idc = idp;
    csSCROLLBAR vscroll(*idp, {r.right-10,0,10,r.bottom}, 1, CS_SBAR_VERTICAL);
    if(idMask)
    {
        cv.CTX[*idc].idMask = *idMask;
        vscroll.setClient(*idc,*idMask);
    }
    else
    {
        cv.CTX[*idc].idMask = *idp;
        vscroll.setClient(*idc,*idp);
    }
    vscroll.mouseLeaveHide(autoHideIntensity);
    SetTimer(cv.CNTLIST[vscroll.getId()],0,18,0);
    csSetAction(*idc,WM_MOUSEWHEEL,smoothScrolling,1,vscroll.getIdPtr());
    cv.CTX[*idc].vScrollBarId = vscroll.getId();
    return vscroll;
}

void smoothScrolling(csARGS Args)
{
    int idSb = *(int*)Args[0];
    SendMessage(cv.CNTLIST[idSb], WM_TIMER,0,0);

}
