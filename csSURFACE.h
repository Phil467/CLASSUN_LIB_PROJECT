#ifndef CSSURFACE_H
#define CSSURFACE_H
#define WINVER 0x0500///transparentblt
#include "genStruct.h"
#include <list>

#define D2F_HORIZONTAL_POLY 0
#define D2F_VERTICAL_POLY   1
#define D2F_POLYLINE        2
#define D2F_JOINTLINE       3
#define D2F_POLYLINE_PEAKED 4
#define D2F_POLYGON         5
#define D2F_POLYGON_BORDER  6

#define D2F_CIRCLE          7
#define D2F_ARC             8
#define D2F_ELLIPSE         9
#define D2F_ELLIPSE_ARC     10

#define D2F_TEXT            11

#define CS_DWGTYPE_POLYGON 1
#define CS_DWGTYPE_POINT 2
#define CS_DWGTYPE_POLYGON_EDGE 3
#define CS_DWGTYPE_IMAGE 4
#define CS_DWGTYPE_POLYLINE 5

#define RAD_TO_GRAD_FACTOR  63.6619772


#include "csRULER.h"

typedef struct
{
    csPOINT2F* pPoints;
    csRGBA* pColors;
    int* pThickness;
    int length;
    int vertex;
    int ray;
    int ray0;
    csPOINT2F center;
    int formType;
    long value;
} cs2DFORM_PARAMS;

typedef struct
{
    csPOINT2F* pPoints;
    csRGBA* pColors;
    int* pThickness;
    int length;
    int lineType;
    long value;
} csJOINTLINE_PARAMS;

typedef struct
{
    csPOINT2F* pPoints;
    csRGBA color;
    int thickness;
    int length;
    int lineType;
    long value;
} csPOLYLINE_PARAMS;

typedef struct
{
    csPOINT2F* pPoints;
    csRGBA pColor;
    csRGBA pLineColor;
    int lineThickness;
    int length;
    long value;
} csPOLYGON_PARAMS;

typedef struct
{
    csRGBA color;
    csRGBA edgeColor;
    csRGBA vrtColor;
    int edgeThickness;
    RECT r;
    int group : 16;
    int vrt_inRay;
    int vrt_outRay;
    bool showVertices;
    bool showPolygon;
    csDWG_TRANSFORM_PARAMS plgTr;
} csPOLYGON_PARAMS2;

typedef struct
{
    csPOINT2F center;
    int outRay;
    int inRay;
    csRGBA fillColor;
    double greatAngle, smallAngle;
    long value;

} csCIRCLE_PARAMS;

typedef struct
{
    csPOINT2F center;
    int xRay, yRay;
    int thickness;
    csRGBA fillColor;
    double greatAngle, smallAngle;

    double inSill, outSill;
    double inDegradedFact, outDegradedFact;
    double marging;

    int ellipseType;
    long value;

} csELLIPSE_PARAMS;

typedef struct
{
    char*Text;
    csPOINT2F Geometry;
    double rotationAngle;
    double transparency;
    int range;
    long value;

} csTEXTZONE_PARAMS;


typedef unsigned char uchar;

class csSURFACE
{
public:
    csSURFACE(int id=0);
    virtual ~csSURFACE();
    int Paint();
    void delete_last_csForm();
    void redraw_csBackground();
    void redrawSignal(bool& b);
    void ending();
    void begining(HDC& hDc, csRGBA& bkgcol, RECT& clientRect);
    void backImageDesign(char*path, csRGBA conv, csRGB colToRemove);
    void initSurfaceDesign(HDC& hDc, csRGBA& bkgcol, RECT& clientRect, csRGBA brdCol={0}, int brdWidth=0);
    HDC redrawBackground();
    void setBkgBrush(csRGBA c);
    void drawSurfaceBKG();
    void updateSurface(HWND hwnd, csTEXT Title);
    void updateSurface_copy(HWND hwnd,HDC hdc, csSIZE sz, HDC GDC, csTEXT Title);
    void deleteDCS();
    int resetBorderColor();
    int setFocusBorderColor(csRGBA color);

    void drawCircle(csCIRCLE_PARAMS& crp);
    void drawEllipse(csELLIPSE_PARAMS& elp);
    void drawPolygon(csPOLYGON_PARAMS& pgp);
    void drawJointline(csJOINTLINE_PARAMS& jlp);
    void drawPolyline(csPOLYLINE_PARAMS& plp);
    void drawText(csTEXTZONE_PARAMS& tzp);
    void setDCXPosition(float x);
    void setDCYPosition(float y);
    void setDCZoomWidth(int cx);
    void setDCZoomHeight(int cy);
    void setZoomParams(csDC_METRICS zp);
    void enableZoom();
    void refreshDataBase();
    HDC getDC();
    HDC getGDC();
    HDC createDC(HDC hdc);
    int getDCWidth();
    int getDCZoomWidth();
    int getDCHeight();
    int getDCZoomHeight();
    float getDCZoomXPosition();
    float getDCZoomYPosition();
    csDC_METRICS* getDCMetrics();
    void newgdiLine(csLIST<POINT> pts, COLORREF color, int thick, int style);
    void newgdiEmptyLine(COLORREF color, int thick, int style);
    void newgdiLinePoint(int idLine, POINT pt);
    void setgdiLinePoint(int idLine, int idPoint, POINT pt);
    void deletegdiLine(int idLine);
    void deletegdiLinePoint(int idLine, int idPoint);
    csLIST<POINT> getgdiLine(int idLine);
    POINT getgdiLinePoint(int idLine, int idPoint);
    int getgdiLineSize(int idLine);
    int getgdiLineNum();
    void setDwgSurfPos(POINT pos);
    POINT getDwgSurfPos();
    SIZE getGDCSizes();
    void setGDCSizes(SIZE size);
    int getgdiLineThickness(int idLine);
    int setCntBorder(csRGBA color, int width);
    void setCnt(int id);
    HPEN getBackgroundPen();
    HBRUSH getBackgroundBrush();
    void initExtDwg();
    void endExtDwg();
    void csPolygon(csLIST<POINT> pts, csRGBA color, int plgId, csDWG_TRANSFORM_PARAMS dtp={0,0,1,1});
    void csPolygon2(csLIST<POINT> pts, csRGBA color, int plgId);
    void drawActiveObject();
    void setActiveDwgObject(int _activeDwgObject);
    void setActivePolygonId(int _activePolygonId);
    void newPolygon(csRGBA color, int edge=0, csRGBA edgeColor={0});
    void newPolygonPoint(int id, POINT p);
    void setPolygonRange(int from, int to);
    void duplicate(int src, int pos);
    int getPolygonsNum();
    int getPolygonSize(int id);
    int getActiveDwgObject();
    int getActivePolygonId();
    void setPolygonPoint(int id, int pos, POINT p);
    void deletePolygonPoint(int id, int pos);
    void deletePolygon(int id);
    csLIST<POINT> getPolygon(int id);
    POINT getPolygonPoint(int id, int pos);
    void insertPolygonPoint(int id, int pos, POINT p);
    void validateActiveDwg();
    void updatePolygonsDwg();
    void showSelectedPolygon();
    void createIDSMap();
    unsigned getDwgId(int i, int j, int& type);
    void setActiveDwgTransformParams(csDWG_TRANSFORM_PARAMS dtp);
    void drawActiveAboveAll(bool b);
    RECT getDwgRect(csLIST<POINT> pts);
    csDWG_TRANSFORM_PARAMS *getPolygonDwgTransformParams(int i);

    void polygonDwgFromMask(csLIST<POINT> pts, csRGBA color, int plgId);
    void polygonEdgeDwg(csCIRCLE_PARAMS c,int plgId);
    void drawPolygonVertices(bool b);
    bool arePolygonVerticesDrawn();
    unsigned getPolygonEdgeId(int plgId, int i, int j);
    csPOLYGON_PARAMS2 *getPolygonParams(int i);

    void setIdMask(int idMask);
    int getIdMask();

    void addRulers(bool x1=1, bool x2=1, bool y1=1, bool y2=1);
    void addRulersTrackers();

    void setDwgSurfSize(SIZE sz);
    SIZE getDwgSurfSize();
    void setBlitSize(SIZE sz);
    void setStretchingRatio(csRATIO ratio);
    SIZE getBlitSize();
    void stretchable(bool smooth=0, SIZE _sz={0});
    bool* getUpdateAfterStretchingBool();

    int lastPolygonId = -1;
    int idMask = 0, hScrollBarId=0, vScrollBarId=0;
    int rulerRelativePosX = 0;
    int rulerRelativePosY = 0;
    csRULER*rulerX1=0, *rulerX2=0, *rulerY1=0, *rulerY2=0;
    int* idTrackerX1=0, *idTrackerX2=0, *idTrackerY1=0, *idTrackerY2=0;
    bool autoUpdate = 0;
    bool xcentering = 0;
    SIZE imageSize = {0};
    csRGBA borderGradientColor = {0};

    csBORDER_GRADIENT brdGrad_left = {0};
    csBORDER_GRADIENT brdGrad_top = {0};
    csBORDER_GRADIENT brdGrad_right = {0};
    csBORDER_GRADIENT brdGrad_bottom = {0};
    csLIST<csEXTERN_HDC> extHDC;

protected:
    csCIRCLE_PARAMS cparFromPoint2f(csPOINT2F& pdat, csPOINT2F& pcenter, csRGBA& col);
    csELLIPSE_PARAMS eparFromPoint2f(csPOINT2F& pdat, csPOINT2F& pdat0, csPOINT2F& pcenter, csRGBA& col);
    int getIndex(int idobj);
    int csBackground(long& lVal, long& nCount, char*& buf, csRGBA col, char* DEPTH);
    void initialize();
    void copyBits();
    void drawgdiLine();
    void showSelectedPolygonFunc();
    void drawGradBrd(int dx, int dy);
private:
    HDC GDC, hMemDC, hdc, scdc, DCbkg, DCdraw;
    HBITMAP GBMP, m_hBitmap, BMPbkg, BMPdraw;
    char *buf;
    csDATABASE<csPOINT2F> SPI, SPO;
    csDATABASE<csRGBA> SCO, SCI;
    csDATABASE<char*> CHAROBJ;
    csDATABASE<HFONT> CHAROBJFONT;
    csDATABASE<csRGB> CHAROBJCOL;
    csDATABASE<csRECT>  CHAROBJPOS;
    csDATABASE<int>  CHAROBJBLANK;
    csDATABASE<double>  ALPHA;
    csDATABASE<int> THK;
    csLIST<int> OTYPE;
    csLIST<csLIST<long>> VALUE;
    csLIST<csLIST<int>> CHAROBJINDEX;
    csLIST<HDC> RASTERDC;
    HDC BKGIMGDC;
    HBITMAP BKIMGBM;
    HBRUSH BKGBRUSH;
    HPEN BKGPEN;
    unsigned int BORDERWIDTH;
    csRGBA BRD;
    BITMAP bm;
    csRGB  colToRem;
    RECT RPAINT, rclient;
    int smx, smy, OBJECT_TYPE_NUMBER, IDG;
    BITMAPINFO gbi, gbi2;
    POINT ptdc[2];
    csVECT2F vect2;
    csVECT3F vect3;
    csPOINT2F pt0, pt;
    csANGLE3F ANG;
    csRGBA BKG;
    csDC_METRICS dcm;
    bool bZoom;
    int* id;
    
    csLIST<csLIST<POINT> > GDILINE;
    csLIST<RECT> GDIRECTANGLE;
    csLIST<int> GDI_THICK;
    csLIST<int> GDI_STYLE;
    csLIST<COLORREF> GDI_COLOR;
    csLIST<COLORREF> GDI_LINECOLOR;

    COLORREF polygonSelectionColor;

    POINT dwgSurfPos, pt_realtime[2];
    csLIST<csLIST<POINT> > CSPOLYGON;
    csLIST<csPOLYGON_PARAMS2> PLG;
    csLIST<POINT> activePolygon;
    csDWG_TRANSFORM_PARAMS currDtp;
    int activeDwgObject, activePolygonId;
    char** dibchr;
    bool extDwg, drawActDwg;
    BITMAPINFO extbmi;
    csBMP extbmp;
    unsigned **idMap;
    bool drawPolygonVrt;
    bool updatePolygons, enableShowingPolygonSelected;
    csRATIO stretchRatio;

    SIZE dwgSurfSize, blitSize;
    bool stretch=0;
    bool* updateAfterStretching;
};

csRGBA csTint(csRGBA src, csRGBA tinter, float level);
void csRaise(int id, int level, float sharp, bool l, bool t, bool r, bool b);
void csDig(int id, int level, float sharp, bool l, bool t, bool r, bool b);
double getSign(int d);
double getAngle(int dx, int dy);
double getSign2(double dy);
void csf_staticPolygon(csPOINT2F** pts, csRGB**cols, int length1, int length2, HDC dc, HBITMAP hbm, int szx, int szy);
void csf_staticPolyline(csPOINT2F** pts, int** thk, csRGB**cols, int length1, int length2, HDC dc, HBITMAP hbm, int szx, int szy);
void csResizeUpdateClient(int idp, int& idc);
void fastStretchingFunction(csARGS Args);
#endif // CSSURFACE_H
