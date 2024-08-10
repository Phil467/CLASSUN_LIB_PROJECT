#ifndef GENSTRUCT_H_INCLUDED
#define GENSTRUCT_H_INCLUDED
#define _WIN32_WINNT   0x0501
#include <windows.h>
#include <windowsx.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#define CAPTION_DIRECTION_NONE  0
#define CAPTION_DIRECTION_ALL   1
#define CAPTION_DIRECTION_X   2
#define CAPTION_DIRECTION_Y   3

#define GRADIENT_TYPE_NONE   0
#define CS_GRAD_COLOR   1
#define CS_GRAD_IMAGE   2
#define CS_GRAD_IMAGE_COLOR   3
#define CS_GRAD_BOTH   4

#define CS_EB_TP_TOPLEFT 0 //editbox title position
#define CS_EB_TP_TOPRIGHT 1
#define CS_EB_TP_BOTTOMLEFT 2
#define CS_EB_TP_BOTTOMRIGHT 3
#define CS_EB_TP_LEFT 4
#define CS_EB_TP_RIGHT 5


#define CS_TA_TOP_LEFT 0
#define CS_TA_CENTER_LEFT 1
#define CS_TA_BOTTOM_LEFT 2

#define CS_TA_TOP_CENTER 3
#define CS_TA_CENTER 4
#define CS_TA_BOTTOM_CENTER 5

#define CS_TA_TOP_RIGHT 6
#define CS_TA_CENTER_RIGHT 7
#define CS_TA_BOTTOM_RIGHT 8

/*#define IMAGE_TRANSFORM_NONE   0
#define IMAGE_TRANSFORM_ROTATION   1
#define IMAGE_TRANSFORM_TRANSLATION   2*/

#define AUTO_TRANSF_LENGTH   1
#define AUTO_TRANSF_RECT   2

typedef struct
{
    int i;
    void*arg;
}csVOID_ARG;

class csARGS
{
public:
    csARGS(unsigned int nArgs=0);
    void* getArg(unsigned int i);
    void  setArg(unsigned int i, void*arg);
    //void  setArg_int(unsigned int i, int& arg);
    void  setArg_int(unsigned int i, int arg);
    void setArgNumber(unsigned int nbArgs);
    void  setProcParams(HWND* hwnd, UINT* msg, WPARAM* wp, LPARAM* lp, int* id);
    void setId(void*id);
    void setHwnd(void*hwnd);
    void* getHwnd();
    void* getMessage();
    void* getWParam();
    void* getLParam();
    void* getLID();
    void  makeArgs(...);
    void  makeArgs2(void**args, int nbArgs);
    void  freeArgs();
    int getArgNumber();
   // ~csARGS(){free(Args); Args=0;};
    operator HWND()
    {
        return *((HWND*)Args[0]);
    };
    operator UINT()
    {
        return *((UINT*)Args[1]);
    };
    operator WPARAM()
    {
        return *((WPARAM*)Args[2]);
    };
    operator LPARAM()
    {
        return *((LPARAM*)Args[3]);
    };
    operator int()
    {
        return *((int*)Args[4]);
    };
    void* operator[](unsigned int i)
    {
        return Args[i+5];
    };
    void operator=(csVOID_ARG va)
    {
        Args[va.i+5]=va.arg;
    };
    operator int*()
    {
        return ((int*)Args[4]);
    };
    /*operator int&()
    {
        int a = *((int*)Args[4]);
        return a;
    };*/

private:
    void** Args;
    int nbArgs;
};

typedef struct
{
    csLIST<void(*)(csARGS)> LBUTTONDOWN;
    csLIST<csARGS> LBUTTONDOWN_ARGS;
    csLIST<void(*)(csARGS)> NCLBUTTONDOWN;
    csLIST<csARGS> NCLBUTTONDOWN_ARGS;
    csLIST<void(*)(csARGS)> RBUTTONDOWN;
    csLIST<csARGS> RBUTTONDOWN_ARGS;
    csLIST<void(*)(csARGS)> NCRBUTTONDOWN;
    csLIST<csARGS> NCRBUTTONDOWN_ARGS;
    csLIST<void(*)(csARGS)> MBUTTONDOWN;
    csLIST<csARGS> MBUTTONDOWN_ARGS;
    csLIST<void(*)(csARGS)> NCMBUTTONDOWN;
    csLIST<csARGS> NCMBUTTONDOWN_ARGS;
    csLIST<void(*)(csARGS)> LBUTTONUP;
    csLIST<csARGS> LBUTTONUP_ARGS;
    csLIST<void(*)(csARGS)> NCLBUTTONUP;
    csLIST<csARGS> NCLBUTTONUP_ARGS;
    csLIST<void(*)(csARGS)> RBUTTONUP;
    csLIST<csARGS> RBUTTONUP_ARGS;
    csLIST<void(*)(csARGS)> NCRBUTTONUP;
    csLIST<csARGS> NCRBUTTONUP_ARGS;
    csLIST<void(*)(csARGS)> MBUTTONUP;
    csLIST<csARGS> MBUTTONUP_ARGS;
    csLIST<void(*)(csARGS)> NCMBUTTONUP;
    csLIST<csARGS> NCMBUTTONUP_ARGS;
    csLIST<void(*)(csARGS)> LBUTTONDBLCLK;
    csLIST<csARGS> LBUTTONDBLCLK_ARGS;
    csLIST<void(*)(csARGS)> NCLBUTTONDBLCLK;
    csLIST<csARGS> NCLBUTTONDBLCLK_ARGS;
    csLIST<void(*)(csARGS)> RBUTTONDBLCLK;
    csLIST<csARGS> RBUTTONDBLCLK_ARGS;
    csLIST<void(*)(csARGS)> NCRBUTTONDBLCLK;
    csLIST<csARGS> NCRBUTTONDBLCLK_ARGS;
    csLIST<void(*)(csARGS)> MBUTTONDBLCLK;
    csLIST<csARGS> MBUTTONDBLCLK_ARGS;
    csLIST<void(*)(csARGS)> NCMBUTTONDBLCLK;
    csLIST<csARGS> NCMBUTTONDBLCLK_ARGS;
    csLIST<void(*)(csARGS)> MOUSEMOVE;
    csLIST<csARGS> MOUSEMOVE_ARGS;
    csLIST<void(*)(csARGS)> MOUSEHOVER;
    csLIST<csARGS> MOUSEHOVER_ARGS;
    csLIST<void(*)(csARGS)> MOUSELEAVE;
    csLIST<csARGS> MOUSELEAVE_ARGS;
    csLIST<void(*)(csARGS)> MOUSEWHEEL;
    csLIST<csARGS> MOUSEWHEEL_ARGS;
    csLIST<void(*)(csARGS)> MOVE;
    csLIST<csARGS> MOVE_ARGS;
    csLIST<void(*)(csARGS)> SIZE;
    csLIST<csARGS> SIZE_ARGS;
    csLIST<void(*)(csARGS)> SETFOCUS;
    csLIST<csARGS> SETFOCUS_ARGS;
    csLIST<void(*)(csARGS)> CREATE;
    csLIST<csARGS> CREATE_ARGS;
    csLIST<void(*)(csARGS)> DESTROY;
    csLIST<csARGS> DESTROY_ARGS;
    csLIST<void(*)(csARGS)> TIMER;
    csLIST<csARGS> TIMER_ARGS;
    csLIST<void(*)(csARGS)> NCHITTEST;
    csLIST<csARGS> NCHITTEST_ARGS;
    csLIST<void(*)(csARGS)> ERASEBKGND;
    csLIST<csARGS> ERASEBKGND_ARGS;
    csLIST<void(*)(csARGS)> KEYUP;
    csLIST<csARGS> KEYUP_ARGS;
    csLIST<void(*)(csARGS)> KEYDOWN;
    csLIST<csARGS> KEYDOWN_ARGS;
    csLIST<void(*)(csARGS)> SYSCOMMAND;
    csLIST<csARGS> SYSCOMMAND_ARGS;
} csCNT_EVENTS_FUNC;

typedef struct
{
    unsigned int width;
    unsigned int height;
} csSIZE;
typedef struct
{
    int width;
    int height;
} csSIZE2;

typedef struct
{
    HDC dc;
    HBITMAP hbmp;
    BITMAP bm;
} csBMP;

typedef struct
{
    HDC dc;
    HBITMAP hbmp;
    csSIZE sz;
} csDC;

HDC csLoadImage(char*path, csSIZE2 size, SIZE*retSize=0);
typedef struct
{
    HDC dc;
    SIZE sz;
    POINT pos;
    bool show=1, transparentHDC=0;
    COLORREF oddColor;
    void LoadImage(char*_path,csSIZE2 _sz)
    {
        SIZE _retSz;
        dc = csLoadImage(_path,_sz,&_retSz);
        if(_sz.width < 0 || _sz.height < 0)
        {
            sz = _retSz;
        }
        else
        {
            sz = {_sz.width, _sz.height};
        }
    }
} csEXTERN_HDC;

typedef struct
{
    unsigned int r : 8;
    unsigned int g : 8;
    unsigned int b : 8;
    unsigned int a : 8;
} csCOLOR;

typedef struct
{
    float xr=0, yr=0, cxr=1.0, cyr=1.0;
    int x, y;
}csRATIO;

typedef struct
{
    POINT center;
    float zoomFactor;
    float xposFactor, yposFactor, cxFactor, cyFactor;
    int cxDc, cyDc;
} csDC_METRICS;


typedef struct
{
    int x, y;
    float cfx, cfy;
} csDWG_TRANSFORM_PARAMS;


typedef struct
{
    float xc, yc, cxc, cyc, xtranspose, ytranspose;
} csSIZING_PARAMS;

typedef struct
{
    short LeftLinkType ;
    short TopLinkType;
    short RightLinkType ;
    short BottomLinkType ;
} csLINK_TYPE;

typedef struct
{
    bool AllowCursorTracking;
    RECT geometry;
    int SYS_COORD_HWND_ID;
} csCURSOR_TRACKING;

typedef struct
{
    int GradientType;
    csRGBA Color1;
    csRGBA Color2;
    csRGBA HightLightColor;
    float HightLightLevel;
    float ZoomLevel;
    char* Image1;
    char* Image2;
    csSIZE Size;
    POINT Position;
    unsigned int GradientNumber;
    unsigned int TimeStep;
    float ImageRotationAngle;
    RECT validArea;
} csBKG_MOUSEHOVER_GRADIENT;

typedef struct
{
    int GradientType;
    csRGBA Color;
    char* Image;
    unsigned int GradientNumber;
    unsigned int TimeStep;
} csBKG_CLICK_GRADIENT;

typedef struct
{
    float v0, ang, g, cosa, tana;
    void Init()
    {
        cosa = cos(3.14159*ang/180);
        float sina = sin(3.14159*ang/180);
        tana = sina/cosa;
    }
    float Get(float t,float Tmax, float DX, float Xmin)
    {
        return DX*(3-2*t/Tmax)*t*t/(Tmax*Tmax) + Xmin;
    }
} csPOS_FUNC;

typedef struct
{
    int Type;
    RECT InitialRect;
    RECT FinalRect;
    int Time;
    int Count;
    bool Start;
    csPOS_FUNC PosFunc;
    csPOS_FUNC SizeFunc;
    RECT InstRect;
    bool EmergencyStop;
    bool waitUntilAnimEnds;
    HWND Range = HWND_TOP;
    bool Update = 0;
} csAUTO_TRANSFORMATION;

typedef struct
{
    bool Lockable;
    bool Locked;
    bool LockingActivated;
    bool ExternalUnlocking;//utile pour les boutons en groupes
    csRGBA LockingColor;
    char* LockingImagePath;
    bool ExtBool;
} csLOCKED_MODE;

typedef struct
{
    short n, colorScale;
    bool raised, staired;
    float sharp=1.0;
} csBORDER_GRADIENT;


typedef struct
{
    unsigned int AccelCaptureTime;
    float FadeOutTime;
    int Count;
    int Count1=0, Count2=0;
    float AxDT_x;
    float AxDT_y;
    POINT p[5];
    bool Activate;
    int GetX(float t)
    {
        float e = (FadeOutTime+1)*(FadeOutTime+1);
        float a = (AxDT_x)/(1-1/e);
        float V0 = -a/e;
        return a*(1-1/(t+1))+V0*t;
        //return (int)5;
    }
    int GetY(float t)
    {
        float e = (FadeOutTime+1)*(FadeOutTime+1);
        float a = (AxDT_y)/(1-1/e);
        float V0 = -a/e;
        return a*(1-1/(t+1))+V0*t;
        //return (int)5;
    }
} csAUTO_TRANSFORMATION_FADE_OUT;

typedef struct
{
    float FadeTime;
    int Count;
    BYTE AlphaMin;
    bool Activate;
    bool State;
    bool ShowHide;
    RECT Geometry;
    bool SetGeometry;
    BYTE GetAlpha(float t)
    {
        float e = (FadeTime+1)*(FadeTime+1);
        float a = float(255)/((1-1/(FadeTime+1)-FadeTime/e));
        float V0 = -a/e;
        //std::cout<<"alpha = "<<(int)a*(1-1/(t+1))+V0*t<<"\n";
        return (BYTE)(a*(1-1/(t+1))+V0*t);
    }
} csAUTO_ALPHA_FADE;

typedef struct csHWND_GEOMETRIC_LINK csHWND_GEOMETRIC_LINK;
struct csHWND_GEOMETRY_LINK
{
    int idhwndLeft;
    int idhwndTop;
    int idhwndRight;
    int idhwndBottom;
    short LeftLinkEvent_source;
    short TopLinkEvent_source;
    short RightLinkEvent_source ;
    short BottomLinkEvent_source ;
    short LeftLinkEvent_target;
    short TopLinkEvent_target;
    short RightLinkEvent_target ;
    short BottomLinkEvent_target ;
    double LeftLinkEvent_coef;
    double TopLinkEvent_coef;
    double RightLinkEvent_coef;
    double BottomLinkEvent_coef;
    csHWND_GEOMETRY_LINK()
    {
        LeftLinkEvent_source=0;
        LeftLinkEvent_target=0;
        LeftLinkEvent_coef = 1;
        TopLinkEvent_coef = 1;
        RightLinkEvent_coef = 1;
        BottomLinkEvent_coef = 1;
    }
    void init()
    {
        LeftLinkEvent_source=0;
        LeftLinkEvent_target=0;
        TopLinkEvent_source=0;
        TopLinkEvent_target=0;
        RightLinkEvent_source=0;
        RightLinkEvent_target=0;
        BottomLinkEvent_source=0;
        BottomLinkEvent_target=0;
        LeftLinkEvent_coef = 1;
        TopLinkEvent_coef = 1;
        RightLinkEvent_coef = 1;
        BottomLinkEvent_coef = 1;
    }
};

typedef struct
{
    RECT  TextRect;
    char* Text;
    char* Font;
    SIZE  FontSize;
    bool  Italic;
    bool  Underline;
    int   Orientation;
    DWORD  Bold;
    DWORD  Charset;
    csRGB  Color;
} csTEXT;

typedef struct
{
    bool bTLeft,bMLeft,bBLeft, bLTop,bMTop, bRTop;
    bool bTRight,bMRight,bBRight, bLBottom, bMBottom,bRBottom;
    bool bOther;
}csPOS_BOOL;

typedef struct 
{
    int x;
    float a;
    int b;
}csGEOMETRY_LINK_PARAMS;

typedef struct 
{
    int id;
    csGEOMETRY_LINK_PARAMS l, t, r, b;
    bool  Update=0;
    int Flag = SWP_NOZORDER;
    HWND ZOrder = HWND_TOP;
}csGLP4;

typedef struct
{
    csLIST<int> Ids;
    csLIST<RECT> Geometry;
    csLIST<csPOS_BOOL> Bpos;
    unsigned int Delay;
    unsigned MouseHoverCount;
    unsigned MouseLeaveCount;
    bool Lock;
}csMH_SHOW_CNT;

typedef struct
{
    bool AddEditBox;
    char* DefText;
    csTEXT Title;
    csTEXT String;
    int TitlePosition;
    int Style;
    int TitleWidth;
    COLORREF EditModeBkgColor;
    COLORREF EditModeTextColor;
    COLORREF BorderColor;
    COLORREF LineColor;
    HWND EditBoxHandle;
    HFONT Hfont_Title;
    HFONT Hfont_String;
    LPSIZE lps;
    HBRUSH hbr;
    bool CreateSignal;
    bool WithControlers;
    bool WithDestroyer;
} csEDITBOX_PARAMS;

typedef struct csCNTR_PARAMS csCNTR_PARAMS;
struct csCNTR_PARAMS
{
    bool MinMaxStyle;
    bool HTLeft;
    bool HTRight;
    bool HTTop;
    bool HTBottom;
    bool HTCorner;
    int HTMask;
    int CaptionDirection;
    int CaptionDirection_pos;
    int  SizingAreaLength;
    int  CaptionAreaLength;
    int  CaptionAreaPos;
    HCURSOR Cursor;
    SIZE MaxTrackSize;
    SIZE MinTrackSize;
    SIZE MaxSize;
    POINT MaxPos;
    bool ClingToParent;
    bool RedrawWhenResize;
    int  Transparency;
    float  DcZoomIncrement;
    HCURSOR Curs;
    bool Show;//18...
    RECT Geometry;
    char* BackgroundImage;
    csSIZE BackgroundImageSizes;
    csRGBA BackgroundColor;
    int SameBackgroundCnt;
    int BorderWidth;
    csRGBA BorderColor;
    csSIZE DCSizes;
    bool MouseLeaveRemoveBkg;
    bool MouseLeaveTransparency;
    csLOCKED_MODE LockedMode;
    csSIZING_PARAMS SizingParams;
    csTEXT Title;
    int TitleAlign;
    HINSTANCE Hinstance;
    bool AllowXMinMaxTrackPosition;
    int XMinTrackPosition;
    int XMaxTrackPosition;
    bool AllowYMinMaxTrackPosition;
    int YMinTrackPosition;
    int YMaxTrackPosition;
    bool BlockedWithinParent;
    int XMinTrackPosition_extra;
    int YMinTrackPosition_extra;
    unsigned int MouseHoverTime;
    csMH_SHOW_CNT MouseHoverShowCnt;
    csCURSOR_TRACKING CursorTracking;
    csHWND_GEOMETRY_LINK GeometryLink;
    csBKG_MOUSEHOVER_GRADIENT MHGradient;
    csBKG_CLICK_GRADIENT ClkGradient;
    int SameDesignAs;
    csAUTO_TRANSFORMATION AutoTransform;
    csAUTO_TRANSFORMATION_FADE_OUT AutoTransformFadeOut;
    csAUTO_ALPHA_FADE AutoAlphaFade;
    csCNT_EVENTS_FUNC CntEventsFunc;
    RECT RectCatchCnt;
    csEDITBOX_PARAMS EditBox;
    int ColorFilter;

//    csCNTR_PARAMS()
//    {
//        GeometryLink.init();
//    }
};

typedef struct
{
    csSIZING_PARAMS sp;
    bool verticalScrollBar;
    int minSrollLength;
    int thickness;
    int centralBarLength;
    int sideBarLength;
    int* containerToScroll;
    int containerNumber;
    bool containersDisposition;
    int scrollIncrement;
    csRGBA scrollColor;
    csRGBA centralBarColor;
    csRGBA sideBarColor;
    csRGBA sideBarArrowColor;
    csRGBA containerColor;
    int scrollTransparency;
    int sideBarTransparency;
    int centralBarTransparency;
    int containerTransparency;
    char*scrollBackImageDesign;
    char*sideBarBackImageDesign;
    char*centralBarBackImageDesign;
    csRGBA scrollAnimColor;
    csRGBA centralBarAnimColor;
    csRGBA sideBarAnimColor;
    csRGBA sideBarArrowAnimColor;
    int frameNumber;
    int mSeconds;
    int arrowType;
    HINSTANCE Hinstance;
    csDC_METRICS* dcm;
    bool scrollAction;

} csSCROLL_PARAMS;

int hauteurBarreDeTache();

bool csSetAction(int id, UINT message, void(*fx)(csARGS), int nbArgs,...);
bool csSetAction(int id, UINT message, void(*fx)(csARGS), csARGS& Args);
bool csSetGroupedAction(int id, void(*f)(csARGS), csARGS args);
csBMP csBitmapFromFile(char*path, BITMAPINFO*bmi);
//HDC csLoadImage(char*path, csSIZE2 size, SIZE*retSize=0);
csBMP csBitmap(csSIZE sz, BITMAPINFO*bmi);
csDC csNewDC(csSIZE sz);
csDC csNewCompatibleDC(HDC hdc, csSIZE sz, COLORREF bkgCol);
BITMAPINFO csSetBMI(csSIZE sz);

void csFreeDC(csDC dc);
void freeBMP(csBMP bmp);
csDC csGetImgBits(char*path,csSIZE sz);
BYTE interpByte(char b1, char b2, char b3, char b4,float dx, float dy);
csLIST<csDC> getImageGradients(char*path1,char*path2, csSIZE sz, unsigned int n, float rotAng=0, float zoom=0,
                           csRGBA bkgColor={0}, csRGBA teint={0} , float teintLevel=0.0);
csLIST<csDC> getImgColGrad(char*path,csRGBA colRem, csSIZE sz, BYTE transl, unsigned int n);
void csBmpToCntSurface(char*path,csSIZE sz, HDC dc);
void drawCntTitle(csTEXT Title, HDC dc);
void drawCntTitle2(HWND hwnd, HDC dc, csTEXT& Title, RECT r, int textAlign=TA_TOP|TA_CENTER);
//-------------------------------------------------------------------
void initCopyText(HWND hwnd);
char* getTextFromClipBoard(HWND hwnd);
void copyStringToClipBoard(HWND hwnd, char* str);
void createGroup(RECT rpos, HDC& wDc, HFONT hf, COLORREF col[2], char*title, int pos, UINT msg);
void mwfunc(HWND*hedit, HWND hbtn, UINT msg, LPARAM lp);
void createEdit(HWND hwnd,UINT msg, int id);
long colorEdit(UINT msg, WPARAM wp, int id);
void EditBoxDesign(int id, HDC wDc);
void manageEditBox(HWND hwnd, UINT msg, int id);
LPSIZE csTextExtent(int idCnt, HFONT font, char*text);
LPSIZE textExtent2(HDC dc, HFONT font, char*text);

int  csGetAdjustedFontSizeX(int xSize);
int  csGetAdjustedFontSizeY(int ySize);

csGLP4* csGLP4_PTR(csGLP4 glp);
void csGeometryLink(int* idp, int n, csGLP4** glp);
void csGeometryLink(int* idp, int n, ...);
void csSelfGeometrySetting(csARGS Args);
void csGLPParentSizing(csARGS Args);

#endif // GENSTRUCT_H_INCLUDED
