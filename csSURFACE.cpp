#include "csSURFACE.h"
#include "csCONTAINER.h"

extern csCNTR_VARS cv;

csRGBA csTint(csRGBA src, csRGBA tinter, float level)
{
    float l = 1.0 - level;
    csRGBA rsrc = {0};
    rsrc.b = uchar(int(src.b*l + level*tinter.b));
    rsrc.g = uchar(int(src.g*l + level*tinter.g));
    rsrc.r = uchar(int(src.r*l + level*tinter.r));
    return rsrc;
}

void csRaise(int id, int level, float sharp, bool l, bool t, bool r, bool b)
{
    cv.CTX[id].borderGradientColor = cv.cp[id]->BackgroundColor;
    if(l) cv.CTX[id].brdGrad_left = {level,5,1,1,sharp};
    if(t) cv.CTX[id].brdGrad_top = {level,5,1,1,sharp};
    if(r) cv.CTX[id].brdGrad_right = {level,5,1,1,sharp};
    if(b) cv.CTX[id].brdGrad_bottom = {level,5,1,1,sharp};
}

void csDig(int id, int level, float sharp, bool l, bool t, bool r, bool b)
{
    cv.CTX[id].borderGradientColor = cv.cp[id]->BackgroundColor;
    if(l) cv.CTX[id].brdGrad_left = {level,5,1,1,sharp};
    if(t) cv.CTX[id].brdGrad_top = {level,5,0,1,sharp};
    if(r) cv.CTX[id].brdGrad_right = {level,5,0,1,sharp};
    if(b) cv.CTX[id].brdGrad_bottom = {level,5,0,1,sharp};
}


csSURFACE::csSURFACE(int _id)
{
    IDG=0;
    scdc=GetDC(0);
    bZoom=0;
    GDC=hMemDC=BKGIMGDC=hdc=0;
    GBMP=m_hBitmap=0;
    smx=GetSystemMetrics(SM_CXSCREEN);
    smy=GetSystemMetrics(SM_CYMAXIMIZED);
    dcm.cxDc=smx;
    dcm.cyDc=smy;
    dcm.zoomFactor=1.0;
    dcm.xposFactor=0.0;
    dcm.yposFactor=0.0;
    dcm.cxFactor=1.0;
    dcm.cyFactor=1.0;
    dcm.center= {0,0};
    RPAINT= {0,0,smx,smy};
    OBJECT_TYPE_NUMBER=1;

    gbi.bmiHeader.biSize = sizeof(gbi.bmiHeader);
    gbi.bmiHeader.biWidth = smx;
    gbi.bmiHeader.biHeight = -smy;
    gbi.bmiHeader.biPlanes = 1;
    gbi.bmiHeader.biBitCount = 32;
    gbi.bmiHeader.biCompression = BI_RGB;
    gbi.bmiHeader.biSizeImage = (smx) * 4 * (smy);
    gbi.bmiHeader.biClrUsed = 0;
    gbi.bmiHeader.biClrImportant = 0;

    gbi2=gbi;

    SPI.init(OBJECT_TYPE_NUMBER);
    SPO.init(OBJECT_TYPE_NUMBER);
    SCO.init(OBJECT_TYPE_NUMBER);
    SCI.init(OBJECT_TYPE_NUMBER);
    THK.init(OBJECT_TYPE_NUMBER);
    CHAROBJ.init(OBJECT_TYPE_NUMBER);
    CHAROBJCOL.init(OBJECT_TYPE_NUMBER);
    CHAROBJPOS.init(OBJECT_TYPE_NUMBER);
    CHAROBJFONT.init(OBJECT_TYPE_NUMBER);
    CHAROBJBLANK.init(OBJECT_TYPE_NUMBER);
    ALPHA.init(OBJECT_TYPE_NUMBER);

    csLIST<long> l;
    l.init(10);
    VALUE.init(5);
    VALUE.insertEnd(l);

    csLIST<int> lci;
    lci.init(10);
    CHAROBJINDEX.init(5);
    CHAROBJINDEX.insertEnd(lci);

    pt_realtime[0] = {0,0}; pt_realtime[1] = {0,0}; dwgSurfPos = {0,0};

    id = (int*)malloc(sizeof(int));
    *id = _id;

    extbmp.bm.bmBits=0;
    updatePolygons = 0;
    enableShowingPolygonSelected = 0;
    updatePolygons = 0;
    polygonSelectionColor = RGB(255,255,0);
    activePolygonId = 0;
    activeDwgObject = 0;
    extbmi = {0};
    extbmp = {0};
    extDwg = 0;
    idMap = 0;
    currDtp = {0,0,1,1};
    drawActDwg = 0;
    drawPolygonVrt = 0;

    rulerX1 = rulerX2 = rulerY1 = rulerY2 = 0;
    idTrackerX1=0; idTrackerX2=0; idTrackerY1=0; idTrackerY2=0;

    updateAfterStretching = 0;
    updateAfterStretching = csf_alloc2<bool>(1,0);
}

void csSURFACE::addRulers(bool x1, bool x2, bool y1, bool y2)
{

    if(x1)
    {
        csRULER rx1({CS_CXSCREEN, 20}, CS_RULER_TEXT_OVER);
        rulerX1 = csf_alloc2<csRULER>(1,rx1);
    }
    if(x2)
    {
        csRULER rx2({CS_CXSCREEN, 20});
        rulerX2 = csf_alloc2<csRULER>(1,rx2);
    }
    if(y1)
    {
        csRULER ry1({20, CS_CYSCREEN}, CS_RULER_TEXT_OVER);
        rulerY1 = csf_alloc2<csRULER>(1,ry1);
    }
    if(y2)
    {
        csRULER ry2({20, CS_CYSCREEN});
        rulerY2 = csf_alloc2<csRULER>(1,ry2);
    }

    /*csRGBA* color = csf_alloc2<csRGBA>(1,{255,255,50});

    void rulerTracker_(csARGS Args);
    csSetAction(*id,WM_MOUSEMOVE,rulerTracker_,5,rulerX1, rulerX2, rulerY1, rulerY2, color);*/

}

void csSURFACE::addRulersTrackers()
{
    void rulerTracker_timer(csARGS Args);
    void rulerTracker_CanvMouseMove(csARGS Args);
    void rulerTracker_CanvMouseHover(csARGS Args);
    void rulerTracker_CanvMouseLeave(csARGS Args);

    POINT *p = csf_alloc2<POINT>(1,{0,0});
    bool *signalX1 = csf_alloc2<bool>(1,0);
    bool *signalX2 = csf_alloc2<bool>(1,0);
    bool *signalY1 = csf_alloc2<bool>(1,0);
    bool *signalY2 = csf_alloc2<bool>(1,0);

    if(idTrackerX1)
    {
        csSetAction(*idTrackerX1,WM_TIMER,rulerTracker_timer,4,signalX1,p,rulerX1,id);
    }
    if(idTrackerX2)
    {
        csSetAction(*idTrackerX2,WM_TIMER,rulerTracker_timer,4,signalX2,p,rulerX2,id);
    }
    if(idTrackerY1)
    {
        csSetAction(*idTrackerY1,WM_TIMER,rulerTracker_timer,4,signalY1,p,rulerY1,id);
    }
    if(idTrackerY2)
    {
        csSetAction(*idTrackerY2,WM_TIMER,rulerTracker_timer,4,signalY2,p,rulerY2,id);
    }
   if(*idTrackerX1 || *idTrackerX2 || *idTrackerY1 || *idTrackerY2)
    {
        csSetAction(*id,WM_MOUSEMOVE,rulerTracker_CanvMouseMove,9,signalX1,signalX2,signalY1,signalY2,
        idTrackerX1,idTrackerX2,idTrackerY1,idTrackerY2,p);

        //les foctions suivantes introduisent un bug, car rafraichissent le canevas, l'objet
        //actif n'est plus selectionne;
        csARGS args(4);
        args.makeArgs(idTrackerX1,idTrackerX2,idTrackerY1,idTrackerY2);
        csSetAction(*id,WM_MOUSEHOVER,rulerTracker_CanvMouseHover,args);
        csSetAction(*id,WM_MOUSELEAVE,rulerTracker_CanvMouseLeave,args);
    }
}

void csSURFACE::setCnt(int _id)
{
    *id = _id;
}

void csSURFACE::setIdMask(int _idMask)
{
    idMask = _idMask;
}

csSURFACE::~csSURFACE()
{
    //dtor
}

csDC_METRICS* csSURFACE::getDCMetrics()
{
    return &dcm;
}

void csSURFACE::setDCXPosition(float x)
{
    dcm.xposFactor=x;
}

HDC csSURFACE::getDC()
{
    return DCdraw;
}
HDC csSURFACE::getGDC()
{
    return GDC;
}
void csSURFACE::setDCYPosition(float y)
{
    dcm.yposFactor=y;
}

void csSURFACE::setDCZoomWidth(int cx)
{
    dcm.cxDc=cx;
}

void csSURFACE::setDCZoomHeight(int cy)
{
    dcm.cyDc=cy;
}
int csSURFACE::getDCZoomWidth()
{
    return dcm.cxDc;
}

int csSURFACE::getDCZoomHeight()
{
    return dcm.cyDc;
}

float csSURFACE::getDCZoomXPosition()
{
    return dcm.xposFactor;
}
float csSURFACE::getDCZoomYPosition()
{
    return dcm.yposFactor;
}

void csSURFACE::setZoomParams(csDC_METRICS zp)
{
    dcm=zp;
}
int csSURFACE::getDCWidth()
{
    return smx;
}
int csSURFACE::getDCHeight()
{
    return smy;
}

void csSURFACE::stretchable(bool smooth, SIZE _sz)
{
    SIZE sz;
    if(_sz.cx == 0 || _sz.cy == 0)
        sz = {cv.cp[*id]->Geometry.right, cv.cp[*id]->Geometry.bottom};
    else
        sz = _sz;
    cv.CTX[*id].stretch = 1;
    cv.CTX[*id].setBlitSize(sz);

    if(smooth)
    {
        bool*sizeMsg = csf_alloc2<bool>(1,0);
        void stretchingFromSize(csARGS Args);
        csARGS args(2);
        args.makeArgs(sizeMsg, updateAfterStretching);
        csSetAction(*id, WM_SIZE, stretchingFromSize, args);
        csSetAction(*id, WM_TIMER, fastStretchingFunction, args);
    }
    else
    {
        void update_sizing(csARGS Args);
        csSetAction(*id, WM_SIZE, update_sizing, 0);
    }
}

void update_sizing(csARGS Args)
{
    InvalidateRect((HWND)Args,0,1);
}

bool* csSURFACE::getUpdateAfterStretchingBool()
{
    return updateAfterStretching;
}

int csSURFACE::getgdiLineThickness(int idLine)
{
    return GDI_THICK[idLine];
}
int csSURFACE::setCntBorder(csRGBA color, int width)
{
    BRD = color;
    BORDERWIDTH = width;
    if(BKGPEN)
        DeletePen(BKGPEN);
    BKGPEN = CreatePen(PS_SOLID,BORDERWIDTH,RGB(BRD.r,BRD.g,BRD.b));
    InvalidateRect(cv.CNTLIST[*id],0,1);
}
int csSURFACE::setFocusBorderColor(csRGBA color)
{
    if(BKGPEN)
        DeletePen(BKGPEN);
    BKGPEN = CreatePen(PS_SOLID,BORDERWIDTH,RGB(color.r,color.g,color.b));
    InvalidateRect(cv.CNTLIST[*id],0,1);
}
int csSURFACE::resetBorderColor()
{
    if(BKGPEN)
        DeletePen(BKGPEN);
    BKGPEN = CreatePen(PS_SOLID,BORDERWIDTH,RGB(BRD.r,BRD.g,BRD.b));
    InvalidateRect(cv.CNTLIST[*id],0,1);
}

void csSURFACE::initialize()
{
    SPI.newObject(IDG);
    SPO.newObject(IDG);
    SCO.newObject(IDG);

    SPI.newElement2(IDG, 0, 1);
    SPO.newElement2(IDG, 0, 1);
    SCO.newElement2(IDG, 0, 1);

    SPI.InsertDataAtEnd3(IDG, 0, 0, {0}, 5);
    SPO.InsertDataAtEnd3(IDG, 0, 0, {0}, 5);
    SPI.InsertDataAtEnd3(IDG, 0, 0, {RPAINT.right,0}, 5);
    SPO.InsertDataAtEnd3(IDG, 0, 0, {RPAINT.right,0}, 5);
    SPI.InsertDataAtEnd3(IDG, 0, 0, {RPAINT.right,RPAINT.bottom}, 5);
    SPO.InsertDataAtEnd3(IDG, 0, 0, {RPAINT.right,RPAINT.bottom}, 5);
    SPI.InsertDataAtEnd3(IDG, 0, 0, {0,RPAINT.bottom}, 5);
    SPO.InsertDataAtEnd3(IDG, 0, 0, {0,RPAINT.bottom}, 5);
    SPI.InsertDataAtEnd3(IDG, 0, 0, {0}, 5);
    SPO.InsertDataAtEnd3(IDG, 0, 0, {0}, 5);
    SCO.InsertDataAtEnd3(IDG, 0, 0, BKG, 1);
}

void csSURFACE::begining(HDC& hDc, csRGBA& bkgcol, RECT& clientRect)
{
    rclient=clientRect;
    RPAINT= {0,0,smx, smy};
    hdc=hDc;
    BKG=bkgcol;
    GDC=CreateCompatibleDC(0);
    GBMP=CreateCompatibleBitmap(hdc, RPAINT.right,RPAINT.bottom);
    SelectBitmap(GDC,GBMP);
    HBRUSH hb = CreateSolidBrush(RGB(BKG.r,BKG.g,BKG.b));
    HPEN hp = CreatePen(PS_SOLID,0,0);
    Rectangle(GDC, 0, 0, smx, smy);
    DeleteBrush(hb);
    DeletePen(hp);
    /*if(BKGIMGDC)
    {
        backImageDesign(char*path, csRGBA conv, csRGB colToRemove);
        TransparentBlt(hMemDC, 0,0, smx, smy, BKGIMGDC,
                   0, 0, bm.bmWidth,bm.bmHeight,RGB(colToRem.r, colToRem.g, colToRem.b));
                    //DrawStateA(hMemDC,NULL,NULL,(long)BKIMGBM,NULL,0,0,0,0,DST_BITMAP);
    }
    else*/
    BitBlt(hdc, 0,0, smx, smy, GDC, 0, 0, SRCCOPY);
}

/******************************* UTILISEES ***********************************************************************************/
HDC csSURFACE::createDC(HDC hdc)
{
    DeleteDC(DCdraw);
    DeleteBitmap(BMPdraw);
    DCdraw=CreateCompatibleDC(0);
    BMPdraw=CreateCompatibleBitmap(hdc, dwgSurfSize.cx,dwgSurfSize.cy);
    SelectBitmap(DCdraw,BMPdraw);
    SelectBrush(DCdraw,BKGBRUSH);
    SelectPen(DCdraw,BKGPEN);
    Rectangle(DCdraw, 0, 0, dwgSurfSize.cx,dwgSurfSize.cy);
    return DCdraw;
}

HDC csSURFACE::redrawBackground()
{
    DeleteDC(DCdraw);
    DeleteBitmap(BMPdraw);
    DCdraw=CreateCompatibleDC(0);
    BMPdraw=CreateCompatibleBitmap(hdc, dwgSurfSize.cx,dwgSurfSize.cy);
    SelectBitmap(DCdraw,BMPdraw);
    SelectBrush(DCdraw,BKGBRUSH);
    SelectPen(DCdraw,BKGPEN);
    Rectangle(DCdraw, 0, 0, dwgSurfSize.cx,dwgSurfSize.cy);

    if(cv.cp[*id]->BackgroundImage)
        csBmpToCntSurface(cv.cp[*id]->BackgroundImage,cv.cp[*id]->BackgroundImageSizes, DCdraw);
    return DCdraw;
}

void csSURFACE::initSurfaceDesign(HDC& hDc, csRGBA& bkgcol, RECT& clientRect, csRGBA brdCol, int brdWidth)
{
    rclient=clientRect;
    if(clientRect.right == 0 || clientRect.bottom == 0)
    {
        RPAINT= {0,0,CS_CXSCREEN, CS_CYSCREEN};
        dwgSurfSize = {CS_CXSCREEN, CS_CYSCREEN};
        blitSize = dwgSurfSize;
    }
    else
    {
        RPAINT=clientRect;
        dwgSurfSize = {clientRect.right, clientRect.bottom};
        blitSize = dwgSurfSize;
    }
    hdc=hDc;
    BKG=bkgcol;
    BRD=brdCol;
    BORDERWIDTH = brdWidth;
    GDC=CreateCompatibleDC(0);
    GBMP=CreateCompatibleBitmap(hdc, RPAINT.right,RPAINT.bottom);
    SelectBitmap(GDC,GBMP);
    DCdraw=CreateCompatibleDC(0);
    SetStretchBltMode(DCdraw, HALFTONE);
    BMPdraw=CreateCompatibleBitmap(hdc, dwgSurfSize.cx,dwgSurfSize.cy);
    //SetStretchBltMode(DCdraw, HALFTONE);
    SelectBitmap(DCdraw,BMPdraw);
    DCbkg=CreateCompatibleDC(0);
    BMPbkg=CreateCompatibleBitmap(hdc, RPAINT.right,RPAINT.bottom);
    SelectBitmap(DCbkg,BMPbkg);
    BKGBRUSH = CreateSolidBrush(RGB(BKG.r,BKG.g,BKG.b));
    BKGPEN = CreatePen(PS_SOLID,BORDERWIDTH,RGB(BRD.r,BRD.g,BRD.b));
    SelectBrush(DCdraw,BKGBRUSH);
    SelectPen(DCdraw,BKGPEN);
    Rectangle(DCdraw, 0, 0, dwgSurfSize.cx,dwgSurfSize.cy);
    /*if(BKGIMGDC)
    {
        backImageDesign(char*path, csRGBA conv, csRGB colToRemove);
        TransparentBlt(hMemDC, 0,0, smx, smy, BKGIMGDC,
                   0, 0, bm.bmWidth,bm.bmHeight,RGB(colToRem.r, colToRem.g, colToRem.b));
                    //DrawStateA(hMemDC,NULL,NULL,(long)BKIMGBM,NULL,0,0,0,0,DST_BITMAP);
    }
    else*/
    //BitBlt(hdc, 0,0, smx, smy, GDC, 0, 0, SRCCOPY);
    BitBlt(hdc, 0,0, RPAINT.right, RPAINT.bottom, GDC, 0, 0, SRCCOPY);
}

void csSURFACE::newgdiLine(csLIST<POINT> pts, COLORREF color, int thick, int style)
{
    GDILINE.insertEnd(pts) ;
    GDI_LINECOLOR.insertEnd(color);
    GDI_STYLE.insertEnd(style);
    GDI_THICK.insertEnd(thick);
}
void csSURFACE::newgdiEmptyLine(COLORREF color, int thick, int style)
{
    csLIST<POINT> pts;
    GDILINE.insertEnd(pts) ;
    GDI_LINECOLOR.insertEnd(color);
    GDI_STYLE.insertEnd(style);
    GDI_THICK.insertEnd(thick);
}

void csSURFACE::newgdiLinePoint(int idLine, POINT pt)
{
    GDILINE[idLine].insertEnd(pt);
}

void csSURFACE::setgdiLinePoint(int idLine, int idPoint, POINT pt)
{
    GDILINE[idLine][idPoint] = pt;
}

void csSURFACE::deletegdiLinePoint(int idLine, int idPoint)
{
    GDILINE[idLine].deleteAt(idPoint);
}

void csSURFACE::deletegdiLine(int idLine)
{
    GDILINE[idLine].clear();

    if(GDILINE.size()>1)
    {
        GDILINE.deleteAt(idLine);
        GDI_LINECOLOR.deleteAt(idLine);
        GDI_STYLE.deleteAt(idLine);
        GDI_THICK.deleteAt(idLine);
    }
    /*else
    {
        GDILINE.clear();;
        GDI_LINECOLOR.clear();;
        GDI_STYLE.clear();;
        GDI_THICK.clear();
    }*/
}

csLIST<POINT> csSURFACE::getgdiLine(int idLine)
{
    return GDILINE[idLine];
}

POINT csSURFACE::getgdiLinePoint(int idLine, int idPoint)
{
    return GDILINE[idLine][idPoint];
}

int csSURFACE::getgdiLineSize(int idLine)
{
    return GDILINE[idLine].size();
}

int csSURFACE::getgdiLineNum()
{
    return GDILINE.size();
}

void csSURFACE::drawgdiLine()
{
    int sz = GDILINE.size();
    for(int i = 0; i<sz; i++)
    {
        HPEN hp = CreatePen(GDI_STYLE[i],GDI_THICK[i],GDI_LINECOLOR[i]);
        SelectPen(GDC,hp);
        Polyline(GDC, (const POINT*)GDILINE[i].getTable(), GDILINE[i].size());
        DeletePen(hp);
    }
    //Polyline(GDC, GDILINE[i].getTable(), GDILINE[i].size());
}

HPEN csSURFACE::getBackgroundPen()
{
    return BKGPEN;
}
HBRUSH csSURFACE::getBackgroundBrush()
{
    return BKGBRUSH;
}

int csSURFACE::getIdMask()
{
    return idMask;
}
void csSURFACE::deleteDCS()
{
    DeleteDC(GDC);
    DeleteDC(DCdraw);
    DeleteDC(DCbkg);
    DeleteBitmap(BMPdraw);
    DeleteBitmap(BMPbkg);
    DeleteBitmap(GBMP);
    DeleteBrush(BKGBRUSH);
    DeletePen(BKGPEN);
}

void csSURFACE::setDwgSurfSize(SIZE sz)
{
    csDC cdc = csNewDC({sz.cx, sz.cy});
    SetStretchBltMode(cdc.dc, HALFTONE);
    StretchBlt(cdc.dc, 0,0, sz.cx, sz.cy, DCdraw, 0,0, dwgSurfSize.cx, dwgSurfSize.cy, SRCCOPY);
    DeleteDC(DCdraw);
    DeleteBitmap(BMPdraw);
    dwgSurfSize = sz;
    DCdraw = cdc.dc;
    BMPdraw = cdc.hbmp;

    if(extDwg)
    {
        initExtDwg();
        createIDSMap();
    }
}

SIZE csSURFACE::getDwgSurfSize()
{
    //return dwgSurfSize;
    return blitSize; // a modifier ...
}

void csSURFACE::setBlitSize(SIZE sz)
{
    blitSize = sz;
}

SIZE csSURFACE::getBlitSize()
{
    return blitSize;
}


void csSURFACE::setGDCSizes(SIZE size)
{
    RPAINT.right=size.cx;
    RPAINT.bottom = size.cy;
    deleteDCS();
    initSurfaceDesign(hdc, BKG, RPAINT, BRD, BORDERWIDTH);
    if(cv.cp[*id]->BackgroundImage)
        csBmpToCntSurface(cv.cp[*id]->BackgroundImage,cv.cp[*id]->BackgroundImageSizes, DCdraw);

    if(extDwg)
    {
        initExtDwg();
        createIDSMap();
    }

}

SIZE csSURFACE::getGDCSizes()
{
    return {RPAINT.right, RPAINT.bottom};
}

void csSURFACE::setBkgBrush(csRGBA c)
{
    DeleteBrush(BKGBRUSH);
    BKGBRUSH = CreateSolidBrush(RGB(c.r,c.g,c.b));
    InvalidateRect(cv.CNTLIST[*id],0,1);
}

void csSURFACE::setStretchingRatio(csRATIO ratio)
{
    stretchRatio = ratio;
}

void csSURFACE::drawSurfaceBKG()
{
    RECT r=cv.CNTRECT[*id];
    SelectBrush(DCbkg,BKGBRUSH);
    int dx = r.right-r.left, dy = r.bottom-r.top;
    if(!cv.cp[*id]->BackgroundImage)
    {
        PatBlt(DCbkg,0,0, dx, dy, PATCOPY);
        BitBlt(GDC,0,0, RPAINT.right, RPAINT.bottom, DCbkg,0,0, SRCCOPY);
        //TransparentBlt(GDC,dwgSurfPos.x,dwgSurfPos.y, RPAINT.right, RPAINT.bottom, DCdraw,0,0,
                   //RPAINT.right, RPAINT.bottom, RGB(BKG.r, BKG.g, BKG.b));
    }
    else
    {
        PatBlt(GDC,0,0, dx, dy, PATCOPY);
        //StretchBlt(GDC,dwgSurfPos.x,dwgSurfPos.y, RPAINT.right, RPAINT.bottom, DCdraw,0,0,
                   //RPAINT.right, RPAINT.bottom, SRCCOPY);
    }

    if(updatePolygons)
    {

        //if(activeDwgObject == CS_DWGTYPE_POLYGON)
        {
            initExtDwg();
            createIDSMap();
            BitBlt(extbmp.dc,0,0, dwgSurfSize.cx, dwgSurfSize.cy, DCdraw,0,0, SRCCOPY);
            int n = CSPOLYGON.size();
            for(int i = 0; i<n; i++)
            {
                //csPolygon2(CSPOLYGON[i], PLG[i].color, i);
                polygonDwgFromMask(CSPOLYGON[i], PLG[i].color, i);
            }
        }

        if(drawPolygonVrt && CSPOLYGON.size())
        {
            int id = activePolygonId;
            int n = CSPOLYGON[id].size();
            csCIRCLE_PARAMS ccp;
            ccp.fillColor = PLG[id].vrtColor;
            ccp.inRay = PLG[id].vrt_inRay;
            ccp.outRay = PLG[id].vrt_outRay;
            //std::cout<<activePolygonId<<" actpol\n";
            for(int i = 0; i<n; i++)
            {
                ccp.center = {CSPOLYGON[id][i].x, CSPOLYGON[id][i].y};
                polygonEdgeDwg(ccp, id);
            }
        }

        BitBlt(DCdraw,0,0, dwgSurfSize.cx, dwgSurfSize.cy, extbmp.dc,0,0, SRCCOPY);
        //updatePolygons = 0; // sera annule lors du dessein des points
    }
    //endExtDwg();
    drawgdiLine();

    //if(!cv.cp[*id]->BackgroundImage)
    {
        //TransparentBlt(GDC,dwgSurfPos.x,dwgSurfPos.y, RPAINT.right, RPAINT.bottom, DCdraw,0,0,
                   //RPAINT.right, RPAINT.bottom, RGB(BKG.r, BKG.g, BKG.b));
        if(cv.cp[*id]->MouseLeaveRemoveBkg)
        {
            TransparentBlt(GDC,0,0, RPAINT.right, RPAINT.bottom, DCdraw,-dwgSurfPos.x,-dwgSurfPos.y,
                   blitSize.cx, blitSize.cy, RGB(BKG.r, BKG.g, BKG.b));
        }
        else
        {
            if(*updateAfterStretching)
            {
                //std::cout<<" update \n";
                SetStretchBltMode(GDC, HALFTONE);
                *updateAfterStretching = 0;
            }
            else
            {
                SetStretchBltMode(GDC, COLORONCOLOR);
            }

            if(xcentering)
            {
                int x = 0;
                /*if(dx > blitSize.cx)
                    int x = (dx - blitSize.cx)/2;*/
                StretchBlt(GDC,dwgSurfPos.x+x,dwgSurfPos.y, blitSize.cx, blitSize.cy, DCdraw,0,0,
                    dwgSurfSize.cx, dwgSurfSize.cy, SRCCOPY);
            }
            else if(stretch)
            {
                int a = (dx-stretchRatio.x), b = (dy-stretchRatio.y);
                StretchBlt(GDC,stretchRatio.xr*a+stretchRatio.x, stretchRatio.yr*b + stretchRatio.y,
                            stretchRatio.cxr*a, stretchRatio.cyr*b, DCdraw,0,0,
                    blitSize.cx, blitSize.cy, SRCCOPY);
            }
            else
            {
                if(!(cv.cp[*id]->MHGradient.GradientType == CS_GRAD_COLOR)) // cette partie n'est pas utile pour de simples conteneurs
                    BitBlt(GDC,dwgSurfPos.x,dwgSurfPos.y, blitSize.cx, blitSize.cy, DCdraw,0,0,SRCCOPY);
            }
        }
    }

    /*else
    {
        //StretchBlt(GDC,dwgSurfPos.x,dwgSurfPos.y, RPAINT.right, RPAINT.bottom, DCdraw,0,0,
                  // RPAINT.right, RPAINT.bottom, SRCCOPY);
        StretchBlt(GDC,0,0, RPAINT.right, RPAINT.bottom, DCdraw,-dwgSurfPos.x,-dwgSurfPos.y,
                   blitSize.cx, blitSize.cy, SRCCOPY);
    }*/

    int n_ext = extHDC.size();
    for(int i=0; i<n_ext; i++)
    {
        if(extHDC[i].show)
        {
            if(extHDC[i].transparentHDC)
            TransparentBlt(GDC,extHDC[i].pos.x,extHDC[i].pos.y, extHDC[i].sz.cx, extHDC[i].sz.cy,
                            extHDC[i].dc,0,0,extHDC[i].sz.cx, extHDC[i].sz.cy,extHDC[i].oddColor);
            else
            BitBlt(GDC,extHDC[i].pos.x,extHDC[i].pos.y, extHDC[i].sz.cx, extHDC[i].sz.cy, extHDC[i].dc,0,0,SRCCOPY);
        }
    }
    if(!updatePolygons)
    {
        drawActiveObject();
        //BitBlt(GDC,dwgSurfPos.x,dwgSurfPos.y,  RPAINT.right, RPAINT.bottom, extbmp.dc,0,0, SRCCOPY);
        StretchBlt(GDC,0,0, RPAINT.right, RPAINT.bottom, extbmp.dc,-dwgSurfPos.x,-dwgSurfPos.y,
                   blitSize.cx, blitSize.cy, SRCCOPY);
        //BitBlt(GDC,0,0, RPAINT.right, RPAINT.bottom, extbmp.dc,-dwgSurfPos.x,-dwgSurfPos.y, SRCCOPY);
    }
    showSelectedPolygonFunc();

    if(updatePolygons)
        updatePolygons = 0;

    if(rulerX1)
        rulerX1->place(GDC,{dwgSurfPos.x,0});
    if(rulerX2)
        rulerX2->place(GDC,{dwgSurfPos.x,cv.CNTRECT[idMask].bottom-cv.CNTRECT[*id].top-rulerRelativePosY-rulerX2->getSize().cy});
    if(rulerY1)
        rulerY1->place(GDC,{0,dwgSurfPos.y});
    if(rulerY2)
        rulerY2->place(GDC,{cv.CNTRECT[idMask].right-cv.CNTRECT[*id].left-rulerRelativePosX-rulerY2->getSize().cx, dwgSurfPos.y});

    //std::cout<<"id paint " <<*id<<"  "<<"\n";
    if(BORDERWIDTH)
    {
        SelectPen(GDC,BKGPEN);
        POINT p[5];
        int mid = BORDERWIDTH/2;
        p[0] = {mid,mid};
        p[1] = {dx-BORDERWIDTH, mid};
        p[2] = {dx-BORDERWIDTH, dy-BORDERWIDTH};
        p[3] = {mid, dy-BORDERWIDTH};
        p[4] = {mid,mid};
        Polyline(GDC, (const POINT*)p, 5);

        drawGradBrd(dx, dy);
    }
}

void csSURFACE::drawPolygonVertices(bool b)
{
    drawPolygonVrt = b;
}

bool csSURFACE::arePolygonVerticesDrawn()
{
    return drawPolygonVrt;
}

void csSURFACE::updateSurface(HWND hwnd,csTEXT Title)
{
    RECT r = {0,0,cv.CNTCLWRECT[*id].right, cv.CNTCLWRECT[*id].bottom};
    drawCntTitle2(hwnd, GDC, Title, cv.CNTCLWRECT[*id], cv.cp[*id]->TitleAlign);
    EditBoxDesign(*id, GDC);
    BitBlt(hdc, 0,0, RPAINT.right, RPAINT.bottom, GDC, 0, 0, SRCCOPY);
}

void csSURFACE::updateSurface_copy(HWND hwnd,HDC hdc, csSIZE sz, HDC GDC, csTEXT Title)
{
    RECT r = {0,0,cv.CNTCLWRECT[*id].right, cv.CNTCLWRECT[*id].bottom};
    drawCntTitle2(hwnd, GDC, Title, cv.CNTCLWRECT[*id], cv.cp[*id]->TitleAlign);
    EditBoxDesign(*id, GDC);
    BitBlt(hdc, 0,0, sz.width, sz.height, GDC, 0, 0, SRCCOPY);
}

void csSURFACE::setDwgSurfPos(POINT pos)
{
    dwgSurfPos = pos;
}
POINT csSURFACE::getDwgSurfPos()
{
    return dwgSurfPos;
}


void csSURFACE::createIDSMap()
{
    if(idMap)
    {
        for(int j = 0; j<dwgSurfSize.cy; j++)
        {
            free(idMap[j]);
        }
        free(idMap);
        idMap = 0;
    }

    idMap = csf_alloc<unsigned*>(dwgSurfSize.cy);
    for(int j = 0; j<dwgSurfSize.cy; j++)
    {
        idMap[j] = csf_alloc2<unsigned>(dwgSurfSize.cx,0);
    }
}

void csSURFACE::initExtDwg()
{
    extDwg = 1;
    extbmi = csSetBMI({dwgSurfSize.cx, dwgSurfSize.cy});
    if(!extbmp.bm.bmBits)
    {
        extbmp = csBitmap({dwgSurfSize.cx, dwgSurfSize.cy}, &extbmi);

    }
    else
    {
        freeBMP(extbmp);
        extbmp = csBitmap({dwgSurfSize.cx, dwgSurfSize.cy}, &extbmi);
    }

    SetStretchBltMode(extbmp.dc, HALFTONE);
    BitBlt(extbmp.dc,0,0, dwgSurfSize.cx, dwgSurfSize.cy, DCdraw,0,0, SRCCOPY);
    GetDIBits(extbmp.dc,extbmp.hbmp,0,extbmp.bm.bmHeight,extbmp.bm.bmBits,&extbmi,DIB_RGB_COLORS);
}

void csSURFACE::endExtDwg()
{
    if(extDwg)
    {
        BitBlt(GDC,dwgSurfPos.x,dwgSurfPos.y, dwgSurfSize.cx, dwgSurfSize.cy, extbmp.dc,0,0, SRCCOPY);
        /*HDC dc = GetDC(0);
        BitBlt(dc,0,0, dwgSurfSize.cx, dwgSurfSize.cy, extbmp.dc,0,0, SRCCOPY);
        ReleaseDC(0,dc);*/

    }
}

void csSURFACE::showSelectedPolygon()
{
    enableShowingPolygonSelected = 1;
}

void csSURFACE::showSelectedPolygonFunc()
{
    if(enableShowingPolygonSelected)
    {
        initExtDwg();
        //BitBlt(extbmp.dc,0,0, dwgSurfSize.cx, dwgSurfSize.cy, DCdraw,0,0, SRCCOPY);
        int n = CSPOLYGON.size(), i=activePolygonId;
        if(i < CSPOLYGON.size())
        {
            int n = CSPOLYGON[i].size();
            POINT t[n];
            for(int j=0; j<n; j++)
                t[j] = {CSPOLYGON[i][j].x+dwgSurfPos.x, CSPOLYGON[i][j].y+dwgSurfPos.y};

            HPEN pen = CreatePen(0,PLG[i].edgeThickness+4, polygonSelectionColor);
            SelectPen(GDC,pen);
            Polyline(GDC, (const POINT*)t, n);
            DeletePen(pen);
        }
    }
    //BitBlt(GDC,dwgSurfPos.x,dwgSurfPos.y,  dwgSurfSize.cx, dwgSurfSize.cy, extbmp.dc,0,0, SRCCOPY);
    enableShowingPolygonSelected = 0;
}

void csSURFACE::setActiveDwgObject(int _activeDwgObject)
{
    activeDwgObject = _activeDwgObject;
}
void csSURFACE::setActivePolygonId(int _activePolygonId)
{
    activePolygonId = _activePolygonId;
}
int csSURFACE::getActiveDwgObject()
{
    return activeDwgObject;
}
int csSURFACE::getActivePolygonId()
{
    return activePolygonId;
}

csDWG_TRANSFORM_PARAMS* csSURFACE::getPolygonDwgTransformParams(int i)
{
    return &PLG[i].plgTr;
}
csPOLYGON_PARAMS2* csSURFACE::getPolygonParams(int i)
{
    return &PLG[i];
}

void csSURFACE::setActiveDwgTransformParams(csDWG_TRANSFORM_PARAMS dtp)
{
    if(activeDwgObject == CS_DWGTYPE_POLYGON)
        PLG[activePolygonId].plgTr = dtp;
}

void csSURFACE::drawActiveAboveAll(bool b)
{
    drawActDwg = b;
}

void csSURFACE::drawActiveObject()
{
    if(drawActDwg)
    {
        if(activeDwgObject == CS_DWGTYPE_POLYGON)
        {
            initExtDwg();
            BitBlt(extbmp.dc,0,0, dwgSurfSize.cx, dwgSurfSize.cy, DCdraw,0,0, SRCCOPY);
            int i = activePolygonId;
            if(i < CSPOLYGON.size())
            {
                HBRUSH hb = CreateSolidBrush(RGB(PLG[i].color.r, PLG[i].color.g, PLG[i].color.b));
                HPEN hp = CreatePen(0,0,0);
                SelectBrush(extbmp.dc,hb);
                SelectPen(extbmp.dc,hp);
                int n = CSPOLYGON[i].size();
                POINT p[n];
                for(int j=0; j<n; j++)
                {
                    p[j] = {CSPOLYGON[i][j].x*PLG[i].plgTr.cfx+PLG[i].plgTr.x,
                     CSPOLYGON[i][j].y*PLG[i].plgTr.cfy+PLG[i].plgTr.y};
                }
                Polygon(extbmp.dc,p, n);
                DeleteBrush(hb);
                DeletePen(hp);
                //csPolygon(CSPOLYGON[i], PLG[i].color, i, PLG[i].plgTr);
            }
        }
        //BitBlt(GDC,dwgSurfPos.x,dwgSurfPos.y, dwgSurfSize.cx, dwgSurfSize.cy, extbmp.dc,0,0, SRCCOPY);
    }
}
void csSURFACE::validateActiveDwg()
{
    if(activeDwgObject == CS_DWGTYPE_POLYGON)
    {
        initExtDwg();
        BitBlt(extbmp.dc,0,0, dwgSurfSize.cx, dwgSurfSize.cy, DCdraw,0,0, SRCCOPY);
        int i = activePolygonId;
        if(i < CSPOLYGON.size() && i>0)
        {
            polygonDwgFromMask(CSPOLYGON[i], PLG[i].color, i);

            //csPolygon(CSPOLYGON[n], CSPOLYGON_COLOR[n], n, plgTr[n]);
        }
    }
    BitBlt(DCdraw,0,0, dwgSurfSize.cx, dwgSurfSize.cy, extbmp.dc,0,0, SRCCOPY);
}
void csSURFACE::updatePolygonsDwg()
{
    updatePolygons = 1;
}

void csSURFACE::newPolygon(csRGBA color, int thk, csRGBA edgeColor)
{
    csLIST<POINT> plg;
    CSPOLYGON.insertEnd(plg);

    csPOLYGON_PARAMS2 ppar;
    ppar.color = color;
    ppar.edgeColor = edgeColor;
    ppar.edgeThickness = thk;
    ppar.plgTr = {0,0,1,1};
    ppar.vrt_inRay = 2;
    ppar.vrt_outRay = 6;
    ppar.vrtColor = {100,100,100};

    PLG.insertEnd(ppar);
}

void csSURFACE::newPolygonPoint(int id, POINT p)
{
    CSPOLYGON[id].insertEnd(p);
}

void csSURFACE::setPolygonPoint(int id, int pos, POINT p)
{
    CSPOLYGON[id][pos]=p;
}
void csSURFACE::deletePolygonPoint(int id, int pos)
{
    CSPOLYGON[id].deleteAt(pos);
}

void csSURFACE::setPolygonRange(int from, int to)
{
    CSPOLYGON.move(from, to);
    PLG.move(from, to);
}

void csSURFACE::duplicate(int src, int pos)
{
    CSPOLYGON.duplicatePointList(src, pos);
    PLG.duplicate(src, pos);
}

void csSURFACE::insertPolygonPoint(int id, int pos, POINT p)
{
    CSPOLYGON[id].insertAt(p,pos);
}
void csSURFACE::deletePolygon(int id)
{
    if(id>=0 && id < CSPOLYGON.size())
    {
        CSPOLYGON[id].clear();

        if(CSPOLYGON.size()>1)
        {
            CSPOLYGON.deleteAt(id);
            PLG.deleteAt(id);
        }
        else if(CSPOLYGON.size()==1)
        {
            CSPOLYGON.clear();
            PLG.clear();
        }
    }
}

int csSURFACE::getPolygonsNum()
{
    return CSPOLYGON.size();
}

int csSURFACE::getPolygonSize(int id)
{
    return CSPOLYGON[id].size();
}
csLIST<POINT> csSURFACE::getPolygon(int id)
{
    return CSPOLYGON[id];
}
POINT csSURFACE::getPolygonPoint(int id, int pos)
{
    return CSPOLYGON[id][pos];
}

double getAngle(int dx, int dy)
{
    double ang = 0;
    double pi = 3.141596;
    if(dx == 0)
    {
        if(dy > 0)
            ang = pi/2;
        else
            ang = -pi/2;
    }
    else
    {
        ang = atan(dy/dx);
        if(dx < 0)
        {
            ang += pi;
        }
    }
    return ang;
}

double getSign(double d)
{
    return d/abs(d);
}

int getSign2(int dy)
{
    int sign;
    if(dy > 0)
        sign = 1;
    else
        sign = -1;
    return sign;
}

RECT csSURFACE::getDwgRect(csLIST<POINT> pts)
{
    int xmin = pts[0].x, xmax = pts[0].y, ymin = pts[0].y, ymax = pts[0].y;
    int n = pts.size();

    POINT *p = pts.getTable();

    for(int i=1; i<n; i++)
    {
        if(p[i].x < xmin) xmin = p[i].x;
        if(p[i].x > xmax) xmax = p[i].x;
        if(p[i].y < ymin) ymin = p[i].y;
        if(p[i].y > ymax) ymax = p[i].y;
    }
    return  {xmin, ymin, xmax-xmin, ymax-ymin};
}

void csSURFACE::polygonDwgFromMask(csLIST<POINT> pts, csRGBA color, int plgId)
{
    RECT r = getDwgRect(pts);
    csSIZE sz= {r.right, r.bottom};
    BITMAPINFO bmi = csSetBMI(sz);
    csBMP mask = csBitmap(sz, &bmi);
    COLORREF c = RGB(255,255,255);
    HPEN hp = CreatePen(0,0,c);
    HBRUSH hb = CreateSolidBrush(c);

    int n = pts.size();
    POINT p[n];
    for(int i=0; i<n; i++)
    {
        p[i] = {pts[i].x-r.left, pts[i].y-r.top};
    }

    SelectPen(mask.dc,hp);
    SelectBrush(mask.dc,hb);
    Polygon(mask.dc, p, n);

    GetDIBits(mask.dc,mask.hbmp,0,mask.bm.bmHeight,mask.bm.bmBits,&bmi,DIB_RGB_COLORS);

    uchar*str_mask = (uchar*)mask.bm.bmBits;
    uchar*str = (uchar*)extbmp.bm.bmBits;
    int pos, mpos, ii,jj;

    int a = r.left+r.right, b = r.top+r.bottom;
    int xmx = (a<dwgSurfSize.cx)?r.right:dwgSurfSize.cx-r.left;
    int ymx = (b<dwgSurfSize.cy)?r.bottom:dwgSurfSize.cy-r.top;
    int xmn = (r.left<0)?-r.left:0;
    int ymn = (r.top<0)?-r.top:0;
    float f0=color.a/100.0, f = (1.0-f0);

    for(int j=ymn; j<ymx; j++)
    {
        for(int i=xmn; i<xmx; i++)
        {
            mpos = (i + j*r.right)*4;
            ii = i+r.left;
            jj = j+r.top;
            pos = (ii + jj*dwgSurfSize.cx)*4;

            if((int)str_mask[mpos]!=0)
            {//std::cout<<"546 ";
                str[pos] = uchar(int(str[pos]*f0 + f*color.b));
                str[pos+1] = uchar(int(str[pos+1]*f0 + f*color.g));
                str[pos+2] = uchar(int(str[pos+2]*f0 + f*color.r));
                unsigned a = (unsigned)CS_DWGTYPE_POLYGON;
                idMap[jj][ii] = (a<<28)|(unsigned(plgId+1));
            }
        }
    }

    DeletePen(hp);
    DeleteBrush(hb);
    freeBMP(mask);

    SetDIBits(extbmp.dc, extbmp.hbmp, 0, extbmp.bm.bmHeight, str,&extbmi, DIB_RGB_COLORS);

}

void csSURFACE::csPolygon(csLIST<POINT> pts, csRGBA color, int plgId, csDWG_TRANSFORM_PARAMS dtp)
{
    int n = pts.size();
    int n1 = n-1;
    POINT vect2[n1][2];  // Pour stocker les arêtes
    double a[n1]; // Pour stocker les coefficients directeurs des arêtes
    int xstab0[n1]; // Pour stocker les parties entieres des abscisses calculées
    int xstab[n1]; // Pour stocker les parties entieres des abscisses calculées
    int ids[n1]; // Pour stocker les indices des lignes dont les solutions sont valides
    double xstabd[n1]; // Pour stocker les parties decimales des abscisses calculées, pour le lissage des bordures
    int last_sol=0;
    int last_len=0;

    unsigned ny = dwgSurfSize.cy;
    unsigned ymin = pts[0].y*dtp.cfy + dtp.y;
    unsigned ymax = pts[0].y*dtp.cfy + dtp.y;
    int i = 0;
    //GetDIBits(extbmp.dc,extbmp.hbmp,0,extbmp.bm.bmHeight,extbmp.bm.bmBits,&extbmi,DIB_RGB_COLORS);
    uchar*str = (uchar*)extbmp.bm.bmBits;
    for(int p=1; p<n; p+=1)
    {
        vect2[i][1] = {pts[p].x*dtp.cfx + dtp.x, pts[p].y*dtp.cfy + dtp.y};
        vect2[i][0] = {pts[p-1].x*dtp.cfx + dtp.x, pts[p-1].y*dtp.cfy + dtp.y};

        if (vect2[i][1].y < ymin)
            ymin = vect2[i][1].y;

        if (vect2[i][1].y > ymax)
            ymax = vect2[i][1].y;

        double dx = vect2[i][0].x-vect2[i][1].x;
        double dy = vect2[i][0].y-vect2[i][1].y;

        if (dx == 0)
        {   if (dy > 0)
                a[i] = INT_MAX;
            else
                a[i] = -INT_MAX;
        }
        else
        {
            a[i] = dy/dx;
        }
        i += 1;
    }

    if (ymin < 0)
        ymin = 0;
    else if (ymin >= ny)
        ymin = ny-1;
    if (ymax < 0)
        ymax = 0;
    else if (ymax >= ny)
        ymax = ny-1;

    double xsol = 0;
    int n2 = n1-1;
    int ym = ymax+1;
    for (int j = ymin; j < ym; j+=1)
    {
        int al = 0;
        for (int k=0; k<n1; k++)
        {
            if (a[k] == 0 )
            {
                if(j==vect2[k][0].y)
                {
                    xstab0[al] = vect2[k][0].x;
                    xstab0[al+1] = vect2[k][1].x;
                            //xstabd[al] = 0;
                    ids[al] = k;
                    if(k>0)
                        ids[al+1] = k-1;
                    else ids[al+1] = n1-1;
                    al+=2;
                }
            }

            else if (a[k] == -INT_MAX || a[k] == INT_MAX)
            {
                if ((j <= vect2[k][0].y && j >= vect2[k][1].y) ||
                    (j >= vect2[k][0].y && j <= vect2[k][1].y))
                {

                    xstab0[al] = vect2[k][0].x;
                    //xstabd[al] = 0;
                    ids[al] = k;
                    al += 1;
                }
            }
            else
            {
                double xsol = (j-vect2[k][0].y)/a[k] + vect2[k][0].x;

                if((xsol<=vect2[k][0].x && xsol>=vect2[k][1].x) ||
                    (xsol>=vect2[k][0].x && xsol<=vect2[k][1].x))
                {

                        xstab0[al] = int(xsol);
                        ids[al] = k;
                        //xstabd[al] = xsol-xstab[al];
                        al += 1;
                }
            }
        }

        if(/* al%2==1 &&   */al>=3)
        {
        //
            last_sol = xstab0[al-2];
            int first_sol = ids[al-1];
            int sol1 = xstab0[0];


            //std::cout<<vect2[ids[k]][0].y<<","<<vect2[ids[k1]][1].y<<","<<j<<" sign\n";
            //std::cout<<dy1<<","<<dy2<<","<<j<<" sign\n";
            //std::cout<<"\nentree al == "<<al<<"  ";
            int total=0;
            int begin=0;
            if(xstab0[al-2]==xstab0[al-1] && abs(ids[al-2]-ids[al-1])==1)
            if(getSign2(int(j-vect2[ids[al-2]][0].y)) != getSign2(int(j-vect2[ids[al-1]][1].y))
            ||getSign2(int(j-vect2[ids[al-2]][1].y)) != getSign2(int(j-vect2[ids[al-1]][0].y)) )
            {
                //std::cout<<"j = "<<j<<" : debut 1, al = "<< al <<"   ";
                total++;
            }

            //std::cout<<xstab0[0] <<"   "<<xstab0[1]<<"   "<<xstab0[2]<<"   "<<xstab0[3]<<"\n";
            if(xstab0[al-1]==xstab0[0]) //ici abs(ids[al-1]-ids[0]) > 1
            {
                if(getSign2(int(j-vect2[ids[al-1]][0].y)) != getSign2(int(j-vect2[ids[0]][1].y)) ||
                getSign2(int(j-vect2[ids[al-1]][1].y)) != getSign2(int(j-vect2[ids[0]][0].y)))
                {
                    //std::cout<<"debut 2, al = "<< al <<"   ";
                    //begin++;
                    total++;
                }
            }

            if(xstab0[0]==xstab0[1] && abs(ids[0]-ids[1])==1)
            {
            //std::cout<<j-vect2[ids[0]][0].y <<"   "<<j-vect2[ids[1]][1].y<<"\n";
                int dy1 = (j-vect2[ids[0]][0].y);
                int dy2 = ((j-vect2[ids[1]][1].y));
                if(getSign2(dy1) != getSign2(dy2)||
                getSign2(int(j-vect2[ids[0]][1].y)) != getSign2(int(j-vect2[ids[1]][0].y)))
                {
                    //std::cout<<"debut 3, al = "<< al <<"   ";
                    begin++;
                    for(int k=begin; k<al; k++)
                    {
                        xstab0[k-begin]=xstab0[k];
                        ids[k-begin]=ids[k];
                    }
                    total++;
                }
            }
            al-=total;
            //std::cout<<" == "<<al<<"  ";
        }

        /*for (int l=0; l<al; l++)
        {
            for (int k=l+1; k<al; k++)
            {
                if (xstab0[l] > xstab0[k])
                {
                    int t = xstab0[l];
                    xstab0[l] = xstab0[k];
                    xstab0[k] = t;

                    t = ids[l];
                    ids[l] = ids[k];
                    ids[k] = t;
                    //double d = xstabd[k];
                    //xstabd[k] = xstabd[k+1];
                    //xstabd[k+1] = d;
                }
            }
        }*/
        for (int l=0; l<al; l++)
        {
            for (int k=1; k<al; k++)
            {
                int k1=k-1;
                if (xstab0[k1] > xstab0[k])
                {
                    int t = xstab0[k1];
                    xstab0[k1] = xstab0[k];
                    xstab0[k] = t;

                    t = ids[k1];
                    ids[k1] = ids[k];
                    ids[k] = t;
                    //double d = xstabd[k];
                    //xstabd[k] = xstabd[k+1];
                    //xstabd[k+1] = d;
                }
            }
        }

        if(al%2==1)
        {

            int t=0;
            int iid[n1];
            for (int k=1; k<al; k++)
            {
                int k1=k-1;
                if(xstab0[k]==xstab0[k1] && abs(ids[k]-ids[k1])==1)
                {
                //std::cout<<j-vect2[ids[0]][0].y <<"   "<<j-vect2[ids[1]][1].y<<"\n";
                    int dy1 = j-vect2[ids[k1]][0].y;
                    int dy2 = j-vect2[ids[k]][1].y;
                    if(getSign2(dy1) != getSign2(dy2)||
                    getSign2(int(j-vect2[ids[k1]][1].y)) != getSign2(int(j-vect2[ids[k]][0].y)))
                    {
                        //std::cout<<"debut 3, al = "<< al <<"   ";
                        iid[t]=k;
                        t++;
                    }
                }
                //xstab0[k-t]=xstab0[k];
                //ids[k-t]=ids[k];
            }
            bool bt=0;
            for (int k=0, k2=0; k<al; k++)
            {
                for(int l=0; l<t; l++)
                {
                    if(iid[l]==k)
                    {//std::cout<<j<<" k supprime"<<"\n";;
                        bt = 1;
                        break;
                    }
                }
                if(bt)
                    bt=0;
                else
                {
                    xstab0[k2]=xstab0[k];
                    ids[k2]=ids[k];
                    k2++;
                }
            }
            al-=t;
            //std::cout<<j<<" : sol 3 , t = "<<t<<"\n";;

            if(al%2==1)
            {
                std::cout<<j<<" : merde !";
                for (int k=0, t=0; k<al; k++)
                {
                    if(xstab0[k]==last_sol && t==0)
                        t++;
                    xstab0[k] = xstab0[k+t];
                }
                al--;
            }
            //}
        }



        // lissage des bordures
        /*for (int k=0; k<al; k++)
        {
            double f=(1.0-xstabd[k]);

            int x1 = xstab[k]-1, x2 = xstab[k]+1;
            if(x1>0)
            {
                int pos = (x1 + j*dwgSurfSize.cx)*4;
                str[pos] = str[pos]*xstabd[k] + color.b*f;
                str[pos+1] = str[pos+1]*xstabd[k] + color.g*f;
                str[pos+2] = str[pos+2]*xstabd[k] + color.r*f;
            }
            if(x2<dwgSurfSize.cx)
            {
                int pos = (x2 + j*dwgSurfSize.cx)*4;
                str[pos] = str[pos]*f + color.b*xstabd[k];
                str[pos+1] = str[pos+1]*f + color.g*xstabd[k];
                str[pos+2] = str[pos+2]*f + color.r*xstabd[k];
            }

        }*/

        for (int V=0; V<al; V+=2)
        {
            int m=xstab0[V+1]+1;
            for (int U=xstab0[V]; U<m; U++)
            {
                int pos = (U+j*dwgSurfSize.cx)*4;
                //if(idMap[j][U]<=plgId)
                {
                    str[pos] = color.b;
                    str[pos+1] = color.g;
                    str[pos+2] = color.r;
                }
            }
        }
    }

    SetDIBits(extbmp.dc, extbmp.hbmp, 0, extbmp.bm.bmHeight, str,&extbmi, DIB_RGB_COLORS);
}


void csSURFACE::csPolygon2(csLIST<POINT> pts, csRGBA color, int plgId)
{
    int n = pts.size();
    int n1 = n-1;
    POINT vect2[n1][2];  // Pour stocker les arêtes
    double a[n1]; // Pour stocker les coefficients directeurs des arêtes
    int xstab0[n1]; // Pour stocker les parties entieres des abscisses calculées
    int xstab[n1]; // Pour stocker les parties entieres des abscisses calculées
    int ids[n1]; // Pour stocker les indices des lignes dont les solutions sont valides
    double xstabd[n1]; // Pour stocker les parties decimales des abscisses calculées, pour le lissage des bordures
    int last_sol=0;
    int last_len=0;

    csDWG_TRANSFORM_PARAMS dtp = PLG[plgId].plgTr;

    unsigned ny = dwgSurfSize.cy;
    unsigned ymin = pts[0].y*dtp.cfy + dtp.y;
    unsigned ymax = pts[0].y*dtp.cfy + dtp.y;
    int i = 0;
    //GetDIBits(extbmp.dc,extbmp.hbmp,0,extbmp.bm.bmHeight,extbmp.bm.bmBits,&extbmi,DIB_RGB_COLORS);
    uchar*str = (uchar*)extbmp.bm.bmBits;
    for(int p=1; p<n; p+=1)
    {
        vect2[i][1] = {pts[p].x*dtp.cfx + dtp.x, pts[p].y*dtp.cfy + dtp.y};
        vect2[i][0] = {pts[p-1].x*dtp.cfx + dtp.x, pts[p-1].y*dtp.cfy + dtp.y};

        if (vect2[i][1].y < ymin)
            ymin = vect2[i][1].y;

        if (vect2[i][1].y > ymax)
            ymax = vect2[i][1].y;

        double dx = vect2[i][0].x-vect2[i][1].x;
        double dy = vect2[i][0].y-vect2[i][1].y;

        if (dx == 0)
        {   if (dy > 0)
                a[i] = INT_MAX;
            else
                a[i] = -INT_MAX;
        }
        else
        {
            a[i] = dy/dx;
        }
        i += 1;
    }

    if (ymin < 0)
        ymin = 0;
    else if (ymin >= ny)
        ymin = ny-1;
    if (ymax < 0)
        ymax = 0;
    else if (ymax >= ny)
        ymax = ny-1;

    double xsol = 0;
    int n2 = n1-1;
    int ym = ymax+1;
    for (int j = ymin; j < ym; j+=1)
    {
        int al = 0;
        for (int k=0; k<n1; k++)
        {
            if (a[k] == 0 )
            {
                if(j==vect2[k][0].y)
                {
                    xstab0[al] = vect2[k][0].x;
                    xstab0[al+1] = vect2[k][1].x;
                            //xstabd[al] = 0;
                    ids[al] = k;
                    if(k>0)
                        ids[al+1] = k-1;
                    else ids[al+1] = n1-1;
                    al+=2;
                }
            }

            else if (a[k] == -INT_MAX || a[k] == INT_MAX)
            {
                if ((j <= vect2[k][0].y && j >= vect2[k][1].y) ||
                    (j >= vect2[k][0].y && j <= vect2[k][1].y))
                {

                    xstab0[al] = vect2[k][0].x;
                    //xstabd[al] = 0;
                    ids[al] = k;
                    al += 1;
                }
            }
            else
            {
                double xsol = (j-vect2[k][0].y)/a[k] + vect2[k][0].x;

                if((xsol<=vect2[k][0].x && xsol>=vect2[k][1].x) ||
                    (xsol>=vect2[k][0].x && xsol<=vect2[k][1].x))
                {

                        xstab0[al] = int(xsol);
                        ids[al] = k;
                        //xstabd[al] = xsol-xstab[al];
                        al += 1;
                }
            }
        }

        if(/* al%2==1 &&   */al>=3)
        {
        //
            last_sol = xstab0[al-2];
            int first_sol = ids[al-1];
            int sol1 = xstab0[0];


            //std::cout<<vect2[ids[k]][0].y<<","<<vect2[ids[k1]][1].y<<","<<j<<" sign\n";
            //std::cout<<dy1<<","<<dy2<<","<<j<<" sign\n";
            //std::cout<<"\nentree al == "<<al<<"  ";
            int total=0;
            int begin=0;
            if(xstab0[al-2]==xstab0[al-1] && abs(ids[al-2]-ids[al-1])==1)
            if(getSign2(int(j-vect2[ids[al-2]][0].y)) != getSign2(int(j-vect2[ids[al-1]][1].y))
            ||getSign2(int(j-vect2[ids[al-2]][1].y)) != getSign2(int(j-vect2[ids[al-1]][0].y)) )
            {
                //std::cout<<"j = "<<j<<" : debut 1, al = "<< al <<"   ";
                total++;
            }

            //std::cout<<xstab0[0] <<"   "<<xstab0[1]<<"   "<<xstab0[2]<<"   "<<xstab0[3]<<"\n";
            if(xstab0[al-1]==xstab0[0]) //ici abs(ids[al-1]-ids[0]) > 1
            {
                if(getSign2(int(j-vect2[ids[al-1]][0].y)) != getSign2(int(j-vect2[ids[0]][1].y)) ||
                getSign2(int(j-vect2[ids[al-1]][1].y)) != getSign2(int(j-vect2[ids[0]][0].y)))
                {
                    //std::cout<<"debut 2, al = "<< al <<"   ";
                    //begin++;
                    total++;
                }
            }

            if(xstab0[0]==xstab0[1] && abs(ids[0]-ids[1])==1)
            {
            //std::cout<<j-vect2[ids[0]][0].y <<"   "<<j-vect2[ids[1]][1].y<<"\n";
                int dy1 = (j-vect2[ids[0]][0].y);
                int dy2 = ((j-vect2[ids[1]][1].y));
                if(getSign2(dy1) != getSign2(dy2)||
                getSign2(int(j-vect2[ids[0]][1].y)) != getSign2(int(j-vect2[ids[1]][0].y)))
                {
                    //std::cout<<"debut 3, al = "<< al <<"   ";
                    begin++;
                    for(int k=begin; k<al; k++)
                    {
                        xstab0[k-begin]=xstab0[k];
                        ids[k-begin]=ids[k];
                    }
                    total++;
                }
            }
            al-=total;
            //std::cout<<" == "<<al<<"  ";
        }

        /*for (int l=0; l<al; l++)
        {
            for (int k=l+1; k<al; k++)
            {
                if (xstab0[l] > xstab0[k])
                {
                    int t = xstab0[l];
                    xstab0[l] = xstab0[k];
                    xstab0[k] = t;

                    t = ids[l];
                    ids[l] = ids[k];
                    ids[k] = t;
                    //double d = xstabd[k];
                    //xstabd[k] = xstabd[k+1];
                    //xstabd[k+1] = d;
                }
            }
        }*/
        for (int l=0; l<al; l++)
        {
            for (int k=1; k<al; k++)
            {
                int k1=k-1;
                if (xstab0[k1] > xstab0[k])
                {
                    int t = xstab0[k1];
                    xstab0[k1] = xstab0[k];
                    xstab0[k] = t;

                    t = ids[k1];
                    ids[k1] = ids[k];
                    ids[k] = t;
                    //double d = xstabd[k];
                    //xstabd[k] = xstabd[k+1];
                    //xstabd[k+1] = d;
                }
            }
        }

        if(al%2==1)
        {

            int t=0;
            int iid[n1];
            for (int k=1; k<al; k++)
            {
                int k1=k-1;
                if(xstab0[k]==xstab0[k1] && abs(ids[k]-ids[k1])==1)
                {
                //std::cout<<j-vect2[ids[0]][0].y <<"   "<<j-vect2[ids[1]][1].y<<"\n";
                    int dy1 = j-vect2[ids[k1]][0].y;
                    int dy2 = j-vect2[ids[k]][1].y;
                    if(getSign2(dy1) != getSign2(dy2)||
                    getSign2(int(j-vect2[ids[k1]][1].y)) != getSign2(int(j-vect2[ids[k]][0].y)))
                    {
                        //std::cout<<"debut 3, al = "<< al <<"   ";
                        iid[t]=k;
                        t++;
                    }
                }
                //xstab0[k-t]=xstab0[k];
                //ids[k-t]=ids[k];
            }
            bool bt=0;
            for (int k=0, k2=0; k<al; k++)
            {
                for(int l=0; l<t; l++)
                {
                    if(iid[l]==k)
                    {//std::cout<<j<<" k supprime"<<"\n";;
                        bt = 1;
                        break;
                    }
                }
                if(bt)
                    bt=0;
                else
                {
                    xstab0[k2]=xstab0[k];
                    ids[k2]=ids[k];
                    k2++;
                }
            }
            al-=t;
            //std::cout<<j<<" : sol 3 , t = "<<t<<"\n";;

            if(al%2==1)
            {
                std::cout<<j<<" : merde !";
                for (int k=0, t=0; k<al; k++)
                {
                    if(xstab0[k]==last_sol && t==0)
                        t++;
                    xstab0[k] = xstab0[k+t];
                }
                al--;
            }
            //}
        }



        // lissage des bordures
        /*for (int k=0; k<al; k++)
        {
            double f=(1.0-xstabd[k]);

            int x1 = xstab[k]-1, x2 = xstab[k]+1;
            if(x1>0)
            {
                int pos = (x1 + j*dwgSurfSize.cx)*4;
                str[pos] = str[pos]*xstabd[k] + color.b*f;
                str[pos+1] = str[pos+1]*xstabd[k] + color.g*f;
                str[pos+2] = str[pos+2]*xstabd[k] + color.r*f;
            }
            if(x2<dwgSurfSize.cx)
            {
                int pos = (x2 + j*dwgSurfSize.cx)*4;
                str[pos] = str[pos]*f + color.b*xstabd[k];
                str[pos+1] = str[pos+1]*f + color.g*xstabd[k];
                str[pos+2] = str[pos+2]*f + color.r*xstabd[k];
            }

        }*/

        for (int V=0; V<al; V+=2)
        {
            int m=xstab0[V+1]+1;
            for (int U=xstab0[V]; U<m; U++)
            {
                int pos = (U+j*dwgSurfSize.cx)*4;
                str[pos] = color.b;
                str[pos+1] = color.g;
                str[pos+2] = color.r;
                unsigned a = (unsigned)CS_DWGTYPE_POLYGON;
                idMap[j][U] = (a<<28)|(unsigned(plgId+1));
            }
        }
    }

    SetDIBits(extbmp.dc, extbmp.hbmp, 0, extbmp.bm.bmHeight, str,&extbmi, DIB_RGB_COLORS);
}

void csSURFACE::polygonEdgeDwg(csCIRCLE_PARAMS c, int plgId)
{
    float calcRay, f1=c.fillColor.a/100, f2=1-f1;
    int intRay, dx, dy, smx = dwgSurfSize.cx, smy = dwgSurfSize.cy, pos;
    uchar* str = (uchar*)extbmp.bm.bmBits;
    int ptType = CS_DWGTYPE_POLYGON_EDGE;
    for(int j=-c.outRay; j<=c.outRay; j++)
    for(int i=-c.outRay; i<=c.outRay; i++)
    {
        calcRay=sqrt(i*i+j*j);
        intRay=(int)calcRay;
        if(intRay<(int)c.outRay&&(int)c.inRay<intRay)
        {

            dx=(i+c.center.x);
            dy=(j+c.center.y);
            if(dx<smx && dy<smy && dx>0 && dy>0)
            {
                pos=(dy*smx+dx)*4;
                str[pos] = uchar(int(str[pos]*f1 + f2*c.fillColor.b));
                str[pos+1] = uchar(int(str[pos+1]*f1 + f2*c.fillColor.b));
                str[pos+2] = uchar(int(str[pos+2]*f1 + f2*c.fillColor.b));
                idMap[dy][dx] = (ptType<<28)|(unsigned(plgId+1));

            }
        }
        else if(intRay==(int)c.outRay)
        {
            dx=(i+c.center.x);
            dy=(j+c.center.y);
            float fl=calcRay-intRay, f0, f;
            if(dx<smx && dy<smy && dx>0 && dy>0)
            {
                pos=(dy*smx+dx)*4;
                if((f0=fl+c.fillColor.a)>1.0) f0=1;
                f = 1.0-f0;
                str[pos] = uchar(int(str[pos]*f0 + f*c.fillColor.b));
                str[pos+1] = uchar(int(str[pos+1]*f0 + f*c.fillColor.b));
                str[pos+2] = uchar(int(str[pos+2]*f0 + f*c.fillColor.b));
                idMap[dy][dx] = (ptType<<28)|(unsigned(plgId+1));
            }
        }
        else if(intRay==(int)c.inRay)
        {
            dx=(i+c.center.x);
            dy=(j+c.center.y);
            float fl=calcRay-intRay, f0, f;
            if(dx<smx && dy<smy && dx>0 && dy>0)
            {
                pos=(dy*smx+dx)*4;
                if((f0=fl+c.fillColor.a)>1.0) f0=1;
                f = 1.0-f0;
                str[pos] = uchar(int(str[pos]*f0 + f*c.fillColor.b));
                str[pos+1] = uchar(int(str[pos+1]*f0 + f*c.fillColor.b));
                str[pos+2] = uchar(int(str[pos+2]*f0 + f*c.fillColor.b));
                idMap[dy][dx] = (ptType<<28)|(unsigned(plgId+1));
            }
        }
    }
    SetDIBits(extbmp.dc, extbmp.hbmp, 0, extbmp.bm.bmHeight, str,&extbmi, DIB_RGB_COLORS);
}

unsigned csSURFACE::getDwgId(int i, int j, int& type)
{
    std::cout<<idMap[j][i]<<" map j i \n";
    unsigned idd = (idMap[j][i] & 0xfffffff);
    type = int(idMap[j][i]>>28);
    return idd-1;
}

unsigned csSURFACE::getPolygonEdgeId(int plgId, int i, int j)
{
    int n = CSPOLYGON[plgId].size();
    POINT *t = CSPOLYGON[plgId].getTable();
    unsigned ptId=0, r = sqrt(pow(t[0].x - i,2) + pow(t[0].y - j,2)), a;
    for(int i=1; i<n; i++)
    {
        a = sqrt(pow(t[i].x - i,2) + pow(t[i].y - j,2));
        if(a < r)
        {
            r = a;
            ptId = i;
        }
    }

    return ptId;
}

void csSURFACE::drawGradBrd(int dx, int dy)
{
    HPEN hp;
    //csRGBA c = BKG;
    csRGBA c = borderGradientColor;
    if(!c.r && !c.g && !c.b)
    {
        c = BRD;
    }

    POINT pt[2];
    int j;
    if(brdGrad_left.n)
    {
        int cs=brdGrad_left.colorScale, n = brdGrad_left.n;
        float p = brdGrad_left.sharp;
        if(brdGrad_left.raised)
        {
            if(brdGrad_left.staired)
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r-j,c.g-j,c.b-j));
                SelectPen(GDC,hp);
                pt[0] = {i, i};
                pt[1] = {i, dy-i};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
            else
            for(int i=0; i<n; i++,j-=cs*p)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r-j,c.g-j,c.b-j));
                SelectPen(GDC,hp);
                pt[0] = {i, 0};
                pt[1] = {i, dy};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
        }
        else
        {
            float j=cs*n*p;
            if(brdGrad_bottom.staired)
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r+j,c.g+j,c.b+j));
                SelectPen(GDC,hp);
                pt[0] = {i, i};
                pt[1] = {i, dy-2*i};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
            else
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r+j,c.g+j,c.b+j));
                SelectPen(GDC,hp);
                pt[0] = {i, 0};
                pt[1] = {i, dy};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
        }
    }
    if(brdGrad_top.n)
    {
        int cs=brdGrad_top.colorScale, n = brdGrad_top.n;
        float p = brdGrad_top.sharp;
        if(brdGrad_top.raised)
        {
            if(brdGrad_top.staired)
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r-j,c.g-j,c.b-j));
                SelectPen(GDC,hp);
                pt[0] = {i,i};
                pt[1] = {dx-i, i};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
            else
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r-j,c.g-j,c.b-j));
                SelectPen(GDC,hp);
                pt[0] = {0,i};
                pt[1] = {dx, i};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
        }
        else
        {
            if(brdGrad_top.staired)
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r+j,c.g+j,c.b+j));
                SelectPen(GDC,hp);
                pt[0] = {i,i};
                pt[1] = {dx-i, i};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
            else
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r+j,c.g+j,c.b+j));
                SelectPen(GDC,hp);
                pt[0] = {0,i};
                pt[1] = {dx, i};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
        }
    }
    if(brdGrad_right.n)
    {
        int cs=brdGrad_right.colorScale, n = brdGrad_right.n;
        float p = brdGrad_right.sharp;
        if(brdGrad_right.raised)
        {
            if(brdGrad_right.staired)
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r-j,c.g-j,c.b-j));
                SelectPen(GDC,hp);
                pt[0] = {dx-i-1, i};
                pt[1] = {dx-i-1, dy-i};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
            else
            for(int i=0; i<n; i++,j-=cs*p)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r-j,c.g-j,c.b-j));
                SelectPen(GDC,hp);
                pt[0] = {dx-i-1, 0};
                pt[1] = {dx-i-1, dy};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
        }
        else
        {
            float j=cs*n*p;
            if(brdGrad_bottom.staired)
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r+j,c.g+j,c.b+j));
                SelectPen(GDC,hp);
                pt[0] = {dx-i-1, i};
                pt[1] = {dx-i-1, dy-i};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
            else
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r+j,c.g+j,c.b+j));
                SelectPen(GDC,hp);
                pt[0] = {dx-i-1, 0};
                pt[1] = {dx-i-1, dy};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
        }
    }
    if(brdGrad_bottom.n)
    {
        int cs=brdGrad_bottom.colorScale, n = brdGrad_bottom.n;
        float p = brdGrad_bottom.sharp;
        if(brdGrad_bottom.raised)
        {
            if(brdGrad_bottom.staired)
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r-j,c.g-j,c.b-j));
                SelectPen(GDC,hp);
                pt[0] = {i,dy-i-1};
                pt[1] = {dx-i, dy-i-1};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
            else
            for(int i=0; i<n; i++,j-=cs*p)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r-j,c.g-j,c.b-j));
                SelectPen(GDC,hp);
                pt[0] = {0,dy-i-1};
                pt[1] = {dx, dy-i-1};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
        }
        else
        {
            float j=cs*n*p;
            if(brdGrad_bottom.staired)
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r+j,c.g+j,c.b+j));
                SelectPen(GDC,hp);
                pt[0] = {i,dy-i-1};
                pt[1] = {dx-i, dy-i-1};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
            else
            for(int i=0; i<n; i++)
            {
                j=cs*pow((n-i-1),p);
                hp = CreatePen(0,1,RGB(c.r+j,c.g+j,c.b+j));
                SelectPen(GDC,hp);
                pt[0] = {0,dy-i-1};
                pt[1] = {dx, dy-i-1};
                Polyline(GDC, (const POINT*)pt, 2);
                DeletePen(hp);
            }
        }
    }
}
/******************************* FIN UTILISEES ***********************************************************************************/


void csSURFACE::ending()
{
    BitBlt(hdc, 0, 0, RPAINT.right,RPAINT.bottom, GDC, 0, 0, SRCCOPY);
    DeleteBitmap(GBMP);
    DeleteDC(GDC);
}

void csSURFACE::redrawSignal(bool& b)
{
    if(b)
    {
        DeleteDC(hMemDC);
        DeleteBitmap(m_hBitmap);
        b=0;
    }
}

void csSURFACE::redraw_csBackground()
{
    DeleteDC(hMemDC);
    hMemDC=0;
    DeleteBitmap(m_hBitmap);
    m_hBitmap=0;

}

void csSURFACE::delete_last_csForm()
{
    DeleteDC(hMemDC);
    DeleteBitmap(m_hBitmap);
}

void csSURFACE::backImageDesign(char*path, csRGBA conv, csRGB colToRemove)
{
    BKIMGBM=(HBITMAP)LoadImage(NULL,path,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObjectA((HGDIOBJ)BKIMGBM,sizeof(bm),(PVOID)&bm);
    int szx=(bm.bmWidth>smx)?bm.bmWidth:smx;
    int szy=(bm.bmHeight>smy)?bm.bmHeight:smy;
    BKGIMGDC=CreateCompatibleDC(0);
    HDC dc=GetDC(0);
    HBITMAP hbm = CreateCompatibleBitmap(dc, szx, szy);
    SelectBitmap(BKGIMGDC,hbm);
    DrawStateA(BKGIMGDC,NULL,NULL,
               (long long)BKIMGBM,NULL,0,0,0,0,DST_BITMAP);
    colToRem=colToRemove;
    ReleaseDC(0,dc);
    if(conv.a)
    {
        long lval=0,nCount=0;
        char* buf = (char *) malloc(szx * 4 * szy);
        int bRes = GetDIBits(BKGIMGDC, hbm, 0, szy, buf, &gbi, DIB_RGB_COLORS);
        for (int j=0; j<bm.bmHeight; j++)
        {
            for (int i=0; i<bm.bmWidth; i++)
            {
                nCount=(j*szx+i)*4;
                memcpy(&lval, &buf[nCount], 4);
                lval=Tint({GetRValue(lval),GetGValue(lval),GetBValue(lval)},
                {conv.b,conv.g,conv.r},
                conv.a);
                memcpy(&buf[nCount], &lval, 4);
            }
        }
        SetDIBits(BKGIMGDC, hbm, 0, bRes, buf,  &gbi, DIB_RGB_COLORS);
        free(buf);
    }
    DeleteBitmap(hbm);
}

int csSURFACE::csBackground(long& lVal, long& nCount, char*& buf, csRGBA col, char* DEPTH)
{
    long l=-MAXLONG;
    for (int j=0; j<smy; j++)
    {
        for (int i=0; i<smx; i++)
        {

            lVal = RGB(col.b, col.g, col.r);
            memcpy(&buf[nCount], &lVal, 4);
            memcpy(&DEPTH[nCount], &l, 4);
            nCount+=4;
        }
    }
    nCount=0;
    return 0;
}

void csResizeUpdateClient(int idp, int& idc)
{
    void ruc(csARGS Args);
    csSetAction(idp,WM_SIZE,ruc,1,&idc);
    //csSetAction(idp,WM_MOVE,ruc,1,&idc);
}

void ruc(csARGS Args)
{
    int idc = *(int*)Args[0];
    cv.CTX[idc].autoUpdate = 1;
    SendMessage(cv.CNTLIST[idc],WM_TIMER,0,0);
}

void rulerTracker_(csARGS Args)
{
    csRULER rulerX1 = *(csRULER*)Args[0];
    csRULER rulerX2 = *(csRULER*)Args[1];
    csRULER rulerY1 = *(csRULER*)Args[2];
    csRULER rulerY2 = *(csRULER*)Args[3];
    csRGBA color = *(csRGBA*)Args[4];
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(HWND(Args), &p);
    int id = (int)Args;
    HDC dc = cv.CTX[id].getDC();
    HPEN hp = CreatePen(0,1,RGB(color.r,color.g,color.b));
    SelectPen(dc,hp);
    //MoveWindow(HWND(Args), p.x, ruler.getPos().y, 1, ruler.getSize().cy,1);
    RECT r = {0, 0, rulerX1.getSize().cy, rulerX1.getSize().cy};
    POINT pts[2];
    pts[0] = {p.x,r.top}; pts[1]={1+p.x,rulerX1.getSize().cy};
    Polyline(dc,(const POINT*)pts, 2);
    InvalidateRect(cv.CNTLIST[id],&r,1);

    r = {0, rulerX2.getPos().y, rulerX2.getSize().cy, rulerX2.getSize().cy+rulerX2.getPos().y};
    pts[0] = {p.x,rulerX2.getPos().y}; pts[1]={1+p.x,rulerX2.getSize().cy+rulerX2.getPos().y};
    Polyline(dc,(const POINT*)pts, 2);
    InvalidateRect(cv.CNTLIST[id],&r,1);

    DeletePen(hp);

    //MoveWindow(HWND(Args), ruler.getPos().x, p.y, ruler.getSize().cx, 1,1);

}

void rulerTracker_timer(csARGS Args)
{
    bool *signal = (bool*)Args[0];
    if(*signal)
    {
        POINT p = *(POINT*)Args[1];
        csRULER ruler = *(csRULER*)Args[2];
        int idcanv = *(int*)Args[3];
        //RECT r = cv.CNTRECT[idcanv];
        if (ruler.getOrientation() == 0)
        {
            //MoveWindow(HWND(Args), p.x+r.left, ruler.getPos().y+r.top, 1, ruler.getSize().cy,0);
            //MoveWindow(HWND(Args), p.x, ruler.getPos().y, 1, ruler.getSize().cy,0);
            SetWindowPos(HWND(Args), HWND_TOP, p.x, ruler.getPos().y, 0, 0,SWP_NOSIZE|SWP_NOZORDER);
        }
        else
        {
            //MoveWindow(HWND(Args), ruler.getPos().x, p.y, ruler.getSize().cx, 1,0);
            SetWindowPos(HWND(Args),HWND_TOP, ruler.getPos().x, p.y, 0, 0,SWP_NOSIZE|SWP_NOZORDER);
        }
        *signal = 0;
    }
}

void rulerTracker_CanvMouseMove(csARGS Args)
{
    POINT *p = (POINT*)Args[8];
    bool *signalX1 = (bool*)Args[0];
    bool *signalX2 = (bool*)Args[1];
    bool *signalY1 = (bool*)Args[2];
    bool *signalY2 = (bool*)Args[3];
    int *idRulerX1 = (int*)Args[4];
    int *idRulerX2 = (int*)Args[5];
    int *idRulerY1 = (int*)Args[6];
    int *idRulerY2 = (int*)Args[7];
    GetCursorPos(p);
    ScreenToClient(HWND(Args), p);
        //std::cout<<0<< " fhgfh\n";
    if(idRulerX1)
    {
        *signalX1 = 1;
        SendMessage(cv.CNTLIST[*idRulerX1], WM_TIMER,0,0);
    }
    if(idRulerX2)
    {
        //*signalX2 = 1;
        //SendMessage(cv.CNTLIST[*idRulerX2], WM_TIMER,0,0);
    }
    if(idRulerY1)
    {
        *signalY1 = 1;
        SendMessage(cv.CNTLIST[*idRulerY1], WM_TIMER,0,0);
    }
    if(idRulerY2)
    {
        //*signalY2 = 1;
        //SendMessage(cv.CNTLIST[*idRulerY2], WM_TIMER,0,0);
    }

}

void rulerTracker_CanvMouseHover(csARGS Args)
{
    int *idRulerX1 = (int*)Args[0];
    int *idRulerX2 = (int*)Args[1];
    int *idRulerY1 = (int*)Args[2];
    int *idRulerY2 = (int*)Args[3];

    int idCanv = int(Args);

    if(idRulerX1)
        cv.cp[*idRulerX1]->Show = 1;
    if(idRulerX2)
        cv.cp[*idRulerX2]->Show = 1;
    if(idRulerY1)
        cv.cp[*idRulerY1]->Show = 1;
    if(idRulerY2)
        cv.cp[*idRulerY2]->Show = 1;

    /*if(idRulerX1 && cv.CNTPARID[idRulerX1] != idCanv)
    {
        SetParent(cv.CNTLIST[idRulerX1], (HWND)Args);
        cv.CNTPARID[idRulerX1] = idCanv;
    }
    if(idRulerX2 && cv.CNTPARID[idRulerX2] != idCanv)
    {
        SetParent(cv.CNTLIST[idRulerX2], (HWND)Args);
        cv.CNTPARID[idRulerX2] = idCanv;
    }
    if(idRulerY1 && cv.CNTPARID[idRulerY1] != idCanv)
    {
        SetParent(cv.CNTLIST[idRulerY1], (HWND)Args);
        cv.CNTPARID[idRulerY1] = idCanv;
    }
    if(idRulerY2 && cv.CNTPARID[idRulerY2] != idCanv)
    {
        SetParent(cv.CNTLIST[idRulerY2], (HWND)Args);
        cv.CNTPARID[idRulerY2] = idCanv;
    }*/

}


void rulerTracker_CanvMouseLeave(csARGS Args)
{
    int *idRulerX1 = (int*)Args[0];
    int *idRulerX2 = (int*)Args[1];
    int *idRulerY1 = (int*)Args[2];
    int *idRulerY2 = (int*)Args[3];

    int idCanv = int(Args);

    if(idRulerX1)
        cv.cp[*idRulerX1]->Show = 0;
    if(idRulerX2)
        cv.cp[*idRulerX2]->Show = 0;
    if(idRulerY1)
        cv.cp[*idRulerY1]->Show = 0;
    if(idRulerY2)
        cv.cp[*idRulerY2]->Show = 0;
}

void stretchingFromSize(csARGS Args)
{
    bool* sizeMsg = (bool*)Args[0];
    *sizeMsg = 1;
}

void fastStretchingFunction(csARGS Args)
{
    bool* sizeMsg = (bool*)Args[0];
    bool* updateAfterStretching = (bool*)Args[1];
    static int maxCount = 3, count = 0;

    if(*sizeMsg)
    {
        if(count < maxCount)
        {
            count++;
        }
        else
        {
            count = 0;
            *sizeMsg = 0;
            *updateAfterStretching = 1;
            InvalidateRect(HWND(Args),0,1);
        }
    }
}
