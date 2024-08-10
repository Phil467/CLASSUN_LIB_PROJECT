#ifndef CSCONTAINER_H
#define CSCONTAINER_H
#include "csSURFACE.h"
#include "resources.h"

#define CS_SYNC_CHILD 0
#define CS_SYNC_FRIEND_AS_CHILD 1
#define CS_SYNC_FRIEND 2

#define LLT_CLING_PROPORTIONAL 1
#define LLT_NO_CLING_PROPORTIONAL 2
#define LLT_NO_CLING_LINKED_XPOS 3
#define LLT_CLING_LINKED_XPOS 4
#define LLT_NO_CLING_NO_LINKED_XPOS 5
#define LLT_CLING_NO_LINKED_XPOS 6

#define TLT_CLING_PROPORTIONAL_YPOS 1
#define TLT_NO_CLING_PROPORTIONAL_YPOS 2
#define TLT_NO_CLING_LINKED_YPOS 3
#define TLT_CLING_LINKED_YPOS 4
#define TLT_NO_CLING_NO_LINKED_YPOS 5
#define TLT_CLING_NO_LINKED_YPOS 6

#define RLT_PROPORTIONAL_WIDTH 1
#define RLT_LINKED_WIDTH 2
#define RLT_NO_LINKED_WIDTH 3

#define CNTR_DISPOSITION_VERTICAL 0
#define CNTR_DISPOSITION_HORIZONTAL 1

#define BLT_PROPORTIONAL_HEIGHT 1
#define BLT_LINKED_HEIGHT 2
#define BLT_NO_LINKED_HEIGHT 3

#define GLINK_POSITION 1
#define GLINK_SIZE 2

#define CSA_LEFT 1
#define CSA_TOP 2
#define CSA_RIGHT 3
#define CSA_BOTTOM 4
#define CSA_NW 5
#define CSA_NE 6
#define CSA_SW 7
#define CSA_SE 8
#define CSA_MOVE 9

#define CS_AAF_HIDE_CNTR 0
#define CS_AAF_SHOW_CNTR 1

#define CS_CXSCREEN GetSystemMetrics(SM_CXSCREEN)
#define CS_CYSCREEN GetSystemMetrics(SM_CYSCREEN)


void defFunction(csARGS);

typedef struct
{
    csLIST<HWND>                                            CNTLIST;
    csLIST<HWND>                                            CNTPARLIST;
    csLIST<RECT>                                            CNTRECT;
    csLIST<RECT>                                            CNTRECT_SAVED;
    csLIST<RECT>                                            CNTCLRECT;
    csLIST<RECT>                                            CNTCLWRECT;
    csLIST<RECT>                                            CNTCLWRECT_SAVED;
    csLIST<csSURFACE>                                       CTX;
    csLIST<HDC>                                             CNTDC;
    csLIST<bool>                                            CNTALLOWDRAW;
    csLIST<bool>                                            CNTDRAWSIGNAL;
    csLIST<csPOINT2F>                                       CNTDRAWPOINTS;
    csLIST<int>                                             CNTDRAWTYPE;
    csLIST<csLINK_TYPE>                                     lkt;
    csLIST<int>                                             CNTPARID;
    csLIST<float>                                           CNTOLDZOOMFACTOR;
    csLIST<csDC_METRICS*>                                   DCMETRICS;
    csLIST<bool>                                            LOCKLINK;
    csLIST<csLIST<int>>                                     IDCNTLEFTLINK;
    csLIST<csLIST<int>>                                     IDCNTTOPLINK;
    csLIST<csLIST<int>>                                     IDCNTRIGHTLINK;
    csLIST<csLIST<int>>                                     IDCNTBOTTOMLINK;
    csLIST<bool>                                            LEFTLINKSIGNAL;
    csLIST<bool>                                            TOPLINKSIGNAL;
    csLIST<bool>                                            RIGHTLINKSIGNAL;
    csLIST<bool>                                            BOTTOMLINKSIGNAL;
    csLIST<bool>                                            SHOWWINDOWSIGNAL;
    csLIST<bool>                                            HIDEWINDOWSIGNAL;
    csLIST<bool>                                            MOUSEHOVERSIGNAL;
    csLIST<int>                                             MOUSEHOVERCOUNT;
    csLIST<int>                                             MOUSELEAVECOUNT;//----NOUVEAU
    csLIST<int>                                             CLICKGRADIENTCOUNT;
    csLIST<int>                                             AUTOTRANSCOUNT;
    csLIST<int>                                             TIMEREVENTFUNCCOUNT;
    csLIST<csLIST<int>>                                     EXTUNLOCKINGCNT;
    csLIST<csLIST<int>>                                     EXTHIDECNT;
    csLIST<RECT>                                            CATCHLASTGEOMETRY;
    csLIST<HWND>                                            CATCHLASTPARENT;
    csLIST<bool>                                            CNTCREATION;
    csLIST<bool>                                            WAITANIMEENDSIN;
    csLIST<bool>                                            WAITANIMEENDSOUT;
    csLIST<csCNTR_PARAMS*>                                  cp;
    csLIST<bool>                                            CNTBORDERCLICKED;
    csLIST<bool>                                            CNTHITALLOW;
    csLIST<bool>                                            FOCUSOFF;
    csLIST<int>                                             REFRESHCOUNT;/**************nouveau*******/
    csLIST<csLIST<csDC>>                                    MHGRADIENTDC;
    csLIST<csDC>                                            DCLOCK;
    csLIST<char*>                                           ClassName;


    csLIST<int>                                           ID;
    csLIST<int>                                           DESTROY_GROUP;
    //int                                                   DESTROY_ID;
    int                                                   DESTROY_ITER, CAPTIONER;
    int                                                   REID_ITER, IDFOCUS, IDFOCUS_OLD;
    HWND                                                  HWNDCAPTURE, HWNDFOCUS, HWNDFOCUS_OLD;
    csLIST<RECT>                                          NORMAL_CNTRECT;
    //POINT                                                 PHOOK_LBTNDOWN;
    bool                                                  BHOOK_LBUTNDOWN_POPUP;
    csLIST<bool>                                          MAXIMAZED_CNT;
    bool                                                   CONTROL_KEY_DOWN, SHIFT_KEY_DOWN, ALT_KEY_DOWN;

    //long                    CNTITER;
    LRESULT                                     Lresult;    // controlling cursor type
    bool                                        captionControl; //catching WM_LBUTTONDOWN and WM_LBUTTONUP
    bool                                        LBTN_CONTROL; //catching WM_LBUTTONUP and WM_LBUTTONDOWN
    bool                                        NCLBTN_CONTROL; //catching WM_NCLBUTTONUP and WM_NCLBUTTONDOWN
    int                                         CURSOR_TYPE;
    int                                         CNTID;
    POINT                                       phit, phit0, TRACKING_POINT, TRACKING_POINT2, lbtndownPoint;
    POINT                                       TIMER_POINT;
    int                                         EXTRA_TRACKING_VALUE_X, TIMER_HWND_ID;
    int                                         EXTRA_TRACKING_VALUE_Y;
    int                                         CURRENT_HITTEST_AREA;
    bool                                        GMOVE=0;
    csLIST<csLIST<void(*)(csARGS)> >             GROUPED_EVENTS_FUNC;
    csLIST<csLIST<csARGS> >                      GROUPED_EVENTS_ARGS;

    void (*defaultFunction)(csARGS);
    void getContId(HWND Cont)
    {
        int m=CNTLIST.size();
        for(long i=0; i<m; i++)
        {
            if(CNTLIST[i]==Cont)
            {
                CNTID=i;
                break;
            }
        }
    }
    int getContId2(HWND Cont)
    {
        int id=0, n=CNTLIST.size();
        for(long i=0; i<n; i++)
        {
            if(CNTLIST[i]==Cont)
            {
                id=i;
                break;
            }
        }
        return id;
    }
    HWND getHandle(int id)
    {
        return CNTLIST[id];
    }
    int*idPtr(int id)
    {
        int i=0;
        int n = ID.size();
        for(i=0; i<n; i++)
        {
            if(id == ID[i])
            {
                break;
            }
        }
        return &ID[i];
    }
} csCNTR_VARS;

class csCONTAINER
{
public:
    csCONTAINER();
    virtual ~csCONTAINER();
    int csCNT_newContainer(int idp, csCNTR_PARAMS& CntParams);
    HWND csc_getContainer(int id);
    csSURFACE* csc_getSurface(int id);
    void csc_setSurface(csSURFACE* srf, int id);
    void directDrawing(int id, int formType);
protected:

private:
};


template<class T> void deleteListList(int id, csLIST<csLIST<T>> list)
{
    for(int i=0; i<list.size(); i++)
        list.clear();
    list.deleteAt(id);
}
template<class T> void deletePointerList(int id, csLIST<T*> list)
{
    if(list[id])
        free(list[id]);
    list.deleteAt(id);
}
template<class T> csLIST<T> csNewList()
{
    csLIST<T> list;
    return list;
}
template<class T> T csNewClassObj()
{
    T ClassObj;
    return ClassObj;
}

void csMouseLeaveHide(int id, int alphaMin);
HWND csHWND(int id);
csCNTR_PARAMS* csPARAMS(int id);
RECT& csWRECT(int id);
RECT& csWRECT_S(int id);
RECT& csCLRECT(int id);
RECT& csCLRECT_S(int id);
RECT& csUPDATECLRECT(int id);
RECT& csUPDATECLRECT_S(int id);
RECT& csUPDATEWRECT(int id);
RECT& csUPDATEWRECT_S(int id);
csSURFACE& csCTX(int id);
void csSetFocus(int id);
void csSetFocus(HWND hwnd);


void destroyContainer_Init(csARGS Args);
csLIST<int> getCntChilds(int id);
void destroyContainerVars(int i);
void destroyContainer_clearVars();

void csSetRegionCombiner(csARGS Args);
void csCombineRegion(csARGS Args);//size,move
void csApplyRegion(csARGS Args);//size,move

void csSetTransparency(int id, int trVal);

void initContParams(csCNTR_PARAMS& cscp);
void csSetBackgroundColor(int id, csRGBA color);
void csSetBackgroundImage(int id, char*path, csSIZE size={(unsigned)CS_CXSCREEN,(unsigned)CS_CYSCREEN});
void csShareBackground(int idSrc, int idDest, csSIZE sizeDest);
void csSetImageGradients(int id, csBKG_MOUSEHOVER_GRADIENT mhg);
RECT rectInParentRef(int id);
RECT rectInParentRef(int id, RECT r);
HWND csf_createFrame(HWND& hpar, int id, RECT r, csRGBA bkg, bool  show,WNDPROC proc);
LRESULT CALLBACK ContainerProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT resizingContainer(HWND hwnd, UINT msg, LPARAM lp, int id);
void initContainer(HWND hwnd, UINT msg, WPARAM wParam, int id);
void paint(HWND hwnd, UINT msg, int id);
void eraseBKG(HWND hwnd, UINT msg, int id);
void directDraw(HWND hwnd, UINT msg, int id);
void mouseWheel(HWND hwnd, UINT msg, WPARAM wp, int id);
void linkGeometry(HWND hwnd, UINT msg, int id);
void moveContainer(HWND hwnd, UINT msg, WPARAM wp, int id);
void containerFollowsMouse(HWND hwnd, UINT msg, int id);
void mouseHoverLeave(HWND hwnd, UINT msg, int id);
void MouseHoverColorGradient(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, int id);
void autoTransformation(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, int id);
void cntEventsFunction(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, int id);
void cntTimerEventFunction(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, int id);
bool catchCnt(HWND hwnd, UINT msg, int id);
void ImageGradient(HWND hwnd, UINT msg, int id);
void autoMoveFade(HWND hwnd, UINT msg, int id);
void autoAlphaFade(HWND hwnd, UINT msg, int id);
bool blockedWithinPar(HWND hwnd, UINT msg, int id);
void MouseHoverPopup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, int id);
#endif // CSCONTAINER_H

