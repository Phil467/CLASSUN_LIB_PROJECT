#include "csCONTAINER.h"
#define UOI_TIMERPROC_EXCEPTION_SUPPRESSION 7
/*hf=CreateFont(20,8,0, 0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                          OUT_OUTLINE_PRECIS, CLIP_MASK, DEFAULT_QUALITY,
                          VARIABLE_PITCH, TEXT("Bell MT"));*/




csCNTR_VARS cv;
static int TIMER_ID = 0;
extern bool SCROLL_SIGNAL_2;
int ID_GEOMETRY = 0;//**************************************ATTENTION

void initContParams(csCNTR_PARAMS& cscp)
{
    cscp= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
          };
    cscp.AutoTransform= {0,{0,0,0,0},0,0,0,0};
    cscp.GeometryLink.init();
    cscp.SameBackgroundCnt = -1;
    cscp.ColorFilter = 0;
    cscp.TitleAlign = CS_TA_TOP_CENTER;
    cscp.Title.TextRect = {0};
    cscp.Title.Font = "book antiqua";
    cscp.Title.Bold = 1;
    cscp.Title.FontSize = {16};
}

void csSetBackgroundColor(int id, csRGBA color)
{
    cv.cp[id]->BackgroundColor = color;
    cv.cp[id]->MHGradient.Color2 = color;
    cv.CTX[id].setBkgBrush(color);
    cv.CTX[id].redrawBackground();
}

HWND csHWND(int id)
{
    return cv.CNTLIST[id];
}

csCNTR_PARAMS* csPARAMS(int id)
{
    return cv.cp[id];
}

RECT& csWRECT(int id)
{
    return cv.CNTRECT[id];
}
RECT& csWRECT_S(int id)
{
    return cv.CNTRECT_SAVED[id];
}
RECT& csCLRECT(int id)
{
    return cv.CNTCLWRECT[id];
}
RECT& csCLRECT_S(int id)
{
    return cv.CNTCLWRECT_SAVED[id];
}
RECT& csUPDATECLRECT(int id)
{
    GetClientRect(csHWND(id), &csCLRECT(id));
    return cv.CNTCLWRECT[id];
}
RECT& csUPDATECLRECT_S(int id)
{
    GetClientRect(csHWND(id), &csCLRECT_S(id));
    return cv.CNTCLWRECT_SAVED[id];
}
RECT& csUPDATEWRECT(int id)
{
    GetWindowRect(csHWND(id), &csWRECT(id));
    return cv.CNTRECT[id];
}
RECT& csUPDATEWRECT_S(int id)
{
    GetWindowRect(csHWND(id), &csWRECT_S(id));
    return cv.CNTRECT_SAVED[id];
}

csSURFACE& csCTX(int id)
{
    return cv.CTX[id];
}

void csSetFocus(int id)
{
    cv.HWNDFOCUS_OLD = cv.HWNDFOCUS;
    cv.IDFOCUS_OLD = cv.IDFOCUS;
    cv.IDFOCUS = id;
    cv.HWNDFOCUS = csHWND(id);
    SetFocus(csHWND(id));
    SendMessage(csHWND(id), WM_MOUSEHOVER,0,0);
    //SendMessage(cv.HWNDFOCUS_OLD, WM_MOUSELEAVE,0,0);
}
void csSetFocus(HWND hwnd)
{
    cv.HWNDFOCUS_OLD = cv.HWNDFOCUS;
    cv.IDFOCUS_OLD = cv.IDFOCUS;
    cv.IDFOCUS = cv.getContId2(hwnd);
    SetFocus(hwnd);
    cv.HWNDFOCUS = hwnd;

    
    SendMessage(hwnd, WM_MOUSEHOVER,0,0);
    //SendMessage(cv.HWNDFOCUS_OLD, WM_MOUSELEAVE,0,0);
}
void csMouseLeaveHide(int id, int alphaMin)
{
    cv.cp[id]->AutoAlphaFade.Geometry = {0,0,0,0};
    cv.cp[id]->AutoAlphaFade.FadeTime = 8;
    cv.cp[id]->AutoAlphaFade.AlphaMin = alphaMin;
    cv.cp[id]->AutoAlphaFade.State = CS_AAF_HIDE_CNTR;
    cv.cp[id]->AutoAlphaFade.SetGeometry = 0;
    cv.cp[id]->MouseLeaveTransparency = 1;
    SendMessage(cv.CNTLIST[id],WM_MOUSELEAVE,0,0);
}

void csSetBackgroundImage(int id, char*path, csSIZE size)
{
    if(path && id<cv.CNTLIST.size())
    {
        cv.cp[id]->BackgroundImage = path;
        cv.cp[id]->BackgroundImageSizes = size;
        HDC hdc = GetDC(cv.CNTLIST[id]);
        RECT r = {0,0,size.width,size.height};
        cv.CTX[id].deleteDCS();
        cv.CTX[id].initSurfaceDesign(hdc, cv.cp[id]->BackgroundColor, r);
        csBmpToCntSurface(cv.cp[id]->BackgroundImage,cv.cp[id]->BackgroundImageSizes, cv.CTX[id].getDC());
        SendMessage(cv.CNTLIST[id],WM_ERASEBKGND,0,0);
        //ReleaseDC(cv.CNTLIST[id], hdc);
        /*int BORDERWIDTH = cv.cp[id]->BorderWidth; BORDERWIDTH=10;
        if(BORDERWIDTH)
        {
            RECT r=cv.cp[id]->Geometry; 
            int dx = r.right, dy = r.bottom;
            HPEN hp = CreatePen(0,BORDERWIDTH,RGB(254,255,255));
            SelectPen(cv.CTX[id].getDC(),hp);
            POINT p[5];
            int mid = BORDERWIDTH/2;
            p[0] = {mid,mid};
            p[1] = {dx-BORDERWIDTH, mid};
            p[2] = {dx-BORDERWIDTH, dy-BORDERWIDTH};
            p[3] = {mid, dy-BORDERWIDTH};
            p[4] = {mid,mid};
            Polyline(cv.CTX[id].getDC(), (const POINT*)p, 5);
            DeletePen(hp);
        }*/

    }
    else
    {
        std::cout<<"csSetBackgroundImage : Wrong Path !\n";
    }
}

void csShareBackground(int idSrc, int idDest, csSIZE sizeDest)
{
    csCNTR_PARAMS* cp = cv.cp[idDest];
    cp->SameBackgroundCnt = idSrc;
    cp->DCSizes = sizeDest;
}

void csSetImageGradients(int id, csBKG_MOUSEHOVER_GRADIENT mhg)
{
    bool b=0;
    if(mhg.Image1 && mhg.Image2)
    {
        for(int i=0; i<cv.MHGRADIENTDC[id].size(); i++)
        {
            DeleteDC(cv.MHGRADIENTDC[id][i].dc);
            DeleteBitmap(cv.MHGRADIENTDC[id][i].hbmp);
        }
        cv.MHGRADIENTDC[id].clear() ;
        cv.MHGRADIENTDC[id] = getImageGradients(mhg.Image1,
                                             mhg.Image2,
                                             mhg.Size,
                                             mhg.GradientNumber,
                                             mhg.ImageRotationAngle,
                                             mhg.ZoomLevel,
                                             cv.cp[id]->BackgroundColor,
                                             mhg.HightLightColor,
                                             mhg.HightLightLevel);
        b=1;
    }
    else if((mhg.Image1 && !mhg.Image2)
                ||(!mhg.Image1 && mhg.Image2))
    {
        char*path = (mhg.Image1)?mhg.Image1:mhg.Image2;
        cv.MHGRADIENTDC[id].clear() ;
        cv.MHGRADIENTDC[id] = getImgColGrad(path,
                                            mhg.Color1,
                                            mhg.Size,
                                            0,
                                            mhg.GradientNumber);
        b=1;
    }

    if(b)
    {
        /*if(cv.cp[id]->MHGradient.GradientType==CS_GRAD_COLOR)
        {
            std::cout<<id<<" gradient \n";
            cv.cp[id]->MHGradient.GradientType = CS_GRAD_BOTH;
        }
        else if(cv.cp[id]->MHGradient.GradientType==0)*/
            cv.cp[id]->MHGradient.GradientType = CS_GRAD_IMAGE;
    }
}

csCONTAINER::csCONTAINER()
{
    //cv.CNTHITBOOL.init(8);
    //cv.CNTDC.init();
    cv.CURSOR_TYPE=-1;
}

csLIST<csCNTR_PARAMS*> getCntParamsPointer()
{
    return cv.cp;
}

csCONTAINER::~csCONTAINER()
{
    //dtor
}


void csCONTAINER::directDrawing(int id, int formType)
{
    if(cv.CNTALLOWDRAW.size()-1 < id)
    {
        cv.CNTALLOWDRAW.insertEnd(1);
        cv.CNTDRAWTYPE.insertEnd(formType);

    }
    else
    {
        cv.CNTALLOWDRAW[id]=1;
        cv.CNTDRAWTYPE[id]=formType;
    }
}

void csSetTransparency(int id, int trVal)
{
    cv.cp[id]->Transparency = trVal;
    SetLayeredWindowAttributes(cv.CNTLIST[id], 0, (100-cv.cp[id]->Transparency)*255/100, LWA_ALPHA);
}


void defFunction(csARGS)
{
    return ;
}

int csCONTAINER::csCNT_newContainer(int idp, csCNTR_PARAMS& CntParams)
{
    int i=cv.CNTLIST.size();
    HWND ContPar;
    HINSTANCE hThisInstance;
    
    cv.CNTCLWRECT_SAVED += CntParams.Geometry;
    cv.DCLOCK += (csDC){0};
    cv.CNTOLDZOOMFACTOR += 0;
    cv.DCMETRICS += (csDC_METRICS*){0};
    cv.IDCNTLEFTLINK += csNewList<int>();
    cv.IDCNTTOPLINK += csNewList<int>();
    cv.IDCNTRIGHTLINK += csNewList<int>();
    cv.IDCNTBOTTOMLINK += csNewList<int>();
    if(!CntParams.SameDesignAs)
    {
        if(CntParams.MHGradient.Image1 && CntParams.MHGradient.Image2)
        {
            cv.MHGRADIENTDC += getImageGradients(CntParams.MHGradient.Image1,
                                             CntParams.MHGradient.Image2,
                                             CntParams.MHGradient.Size,
                                             CntParams.MHGradient.GradientNumber,
                                             CntParams.MHGradient.ImageRotationAngle,
                                             CntParams.MHGradient.ZoomLevel,
                                             CntParams.BackgroundColor,
                                             CntParams.MHGradient.HightLightColor,
                                             CntParams.MHGradient.HightLightLevel);
            if(CntParams.MHGradient.GradientType!=CS_GRAD_BOTH)
                CntParams.MHGradient.GradientType = CS_GRAD_IMAGE;
        }
        else if((CntParams.MHGradient.Image1 && !CntParams.MHGradient.Image2)
                ||(!CntParams.MHGradient.Image1 && CntParams.MHGradient.Image2))
        {
            char*path = (CntParams.MHGradient.Image1)?CntParams.MHGradient.Image1:CntParams.MHGradient.Image2;
            cv.MHGRADIENTDC += getImgColGrad(path,
                                             CntParams.MHGradient.Color1,
                                             CntParams.MHGradient.Size,
                                             0,
                                             CntParams.MHGradient.GradientNumber);
            CntParams.MHGradient.GradientType = CS_GRAD_IMAGE_COLOR;
        }
        else
        {
            cv.MHGRADIENTDC += csNewList<csDC>();
        }

        if(CntParams.LockedMode.LockingImagePath)
        {
            cv.DCLOCK[i] = csGetImgBits(CntParams.LockedMode.LockingImagePath,
                                {CntParams.MHGradient.Size.width,
                                CntParams.MHGradient.Size.height});
        }
    }
    else
    {
        cv.MHGRADIENTDC += csNewList<csDC>();
    }
//std::cout<<"init"<<"\n";
    if(i>0)
    {
        if(idp<0)
            std::cout<<"negative id : "<<idp<<"\n";
        else if(idp>=i)
            std::cout<<"out of range : " << idp << "\nrange is : "<< i <<"\n";
        else
        {
            ContPar=cv.CNTLIST[idp];
            hThisInstance=(HINSTANCE)GetWindowLongPtr(ContPar, GWLP_HINSTANCE);
        }
    }
    else
    {
        ContPar=0;
        hThisInstance=CntParams.Hinstance;
    }

    if(cv.CNTALLOWDRAW.size()-1 < i)
    {
        cv.CNTALLOWDRAW += 0;
        cv.CNTDRAWSIGNAL += 0;
        cv.CNTDRAWTYPE += D2F_POLYLINE;
        //std::cout<<i;
    }

    if(!CntParams.BorderWidth)
        CntParams.BorderColor = CntParams.BackgroundColor;
    if(!CntParams.MouseHoverTime)
        CntParams.MouseHoverTime = 10;
    csCNTR_PARAMS*cntp=(csCNTR_PARAMS*)malloc(sizeof(csCNTR_PARAMS));
    *cntp=CntParams;
    cv.cp += cntp;
    cv.CNTCLRECT += CntParams.Geometry;
    cv.CNTCLWRECT += CntParams.Geometry;


    cv.SHOWWINDOWSIGNAL += 0;
    cv.HIDEWINDOWSIGNAL += 0;
    cv.MOUSEHOVERCOUNT += 0;
    cv.MOUSELEAVECOUNT += 0;
    cv.WAITANIMEENDSIN += 0;
    cv.WAITANIMEENDSOUT += 0;
    cv.MOUSEHOVERSIGNAL += 0;
    cv.AUTOTRANSCOUNT += INT_MAX;
    cv.CLICKGRADIENTCOUNT += INT_MAX;
    cv.CATCHLASTGEOMETRY += (RECT){0};
    cv.NORMAL_CNTRECT += (RECT){0};
    cv.CNTCREATION += 1;
    cv.TIMEREVENTFUNCCOUNT += 0;
    cv.REFRESHCOUNT += 0;
    cv.MAXIMAZED_CNT += 0;
    cv.EXTUNLOCKINGCNT += csNewList<int>();
    cv.EXTHIDECNT += csNewList<int>();
    cv.FOCUSOFF += 0;

    RECT rw, rw2;
    cv.CNTRECT += rw;
    cv.CNTRECT_SAVED += rw2;

    //csRGBA c = CntParams.BackgroundColor;
    //SetLayeredWindowAttributes(hwnd, RGB(c.r,c.g,c.b), 0, LWA_COLORKEY);

    csLIST<void(*)(csARGS)> funcList;
    cv.GROUPED_EVENTS_FUNC += funcList;
    csLIST<csARGS> argList;
    cv.GROUPED_EVENTS_ARGS += argList;


    char* cln=csf_alloc<char>(15);
    sprintf(cln, "cont_%d%", i);
    cv.ClassName += cln;
    HWND hwnd;               /* This is the handle for our window */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = cv.ClassName[i];
    wincl.lpfnWndProc = ContainerProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    char*path="img\\app\\icon1.ico";
    wincl.hIcon = LoadIconW (NULL, (LPCWSTR)MAKEINTRESOURCE(MAINICON));
    wincl.hIconSm = LoadIcon (NULL, MAKEINTRESOURCE(MAINICON));
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    //csRGB col=cv.cp[i].BackgroundColor;
    wincl.hbrBackground = 0; //(HBRUSH) CreateSolidBrush(RGB(col.r, col.g, col.b));

    DWORD style=WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_MAXIMIZE|WS_MINIMIZE;
    /*if(!CntParams.MinMaxStyle)
        style=0;*/
    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;
    RECT r=cv.cp[i]->Geometry;
    /* The class is registered, let's create the program*/

    hwnd = CreateWindowEx (
               WS_EX_LAYERED,                   /* Extended possibilites for variation */
               cv.ClassName[i],         /* Classname */
               cv.cp[i]->Title.Text,       /* Title Text */
               WS_POPUP|WS_CHILD|style, /* default window */
               r.left,       /* Windows decides the position */
               r.top,       /* where the window ends up on the screen */
               r.right+2,                 /* The programs width */
               r.bottom+2,                 /* and height in pixels */
               ContPar,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    HDC hdc = GetDC(hwnd);
    cv.CNTDC += hdc;
    cv.CNTLIST += hwnd;
    cv.CNTPARLIST += ContPar;
    cv.CNTPARID += idp;
    cv.LOCKLINK += 0;
    ShowWindow(hwnd,1);
    SetLayeredWindowAttributes(hwnd, 0, (100-cv.cp[i]->Transparency)*255/100, LWA_ALPHA);

    if(cv.CTX.size()-1 < i)
    {
        csSURFACE cspa(i);
        if(CntParams.SameBackgroundCnt <= -1)
        {
            RECT rdraw = {0,0,CntParams.BackgroundImageSizes.width,CntParams.BackgroundImageSizes.height};//transformed to max rect if {0,0,0,0}
            if(CntParams.DCSizes.width!=0 && CntParams.DCSizes.height !=0)
                rdraw = {0,0,CntParams.DCSizes.width,CntParams.DCSizes.height};
            cspa.initSurfaceDesign(hdc, CntParams.BackgroundColor, rdraw, CntParams.BorderColor, CntParams.BorderWidth);
        }
        cv.CTX += cspa;
        cv.CNTALLOWDRAW += 0;
        cv.CNTDRAWSIGNAL += 0;
        cv.CNTDRAWTYPE += D2F_POLYLINE;
    }

    if(CntParams.GeometryLink.LeftLinkEvent_target!=0)
    {
        cv.IDCNTLEFTLINK[CntParams.GeometryLink.idhwndLeft].insertEnd(i);
        cv.LEFTLINKSIGNAL += 0;
    }
    if(CntParams.GeometryLink.TopLinkEvent_target!=0)
    {
        cv.IDCNTTOPLINK[CntParams.GeometryLink.idhwndTop].insertEnd(i);
        cv.TOPLINKSIGNAL += 0;
    }
    if(CntParams.GeometryLink.RightLinkEvent_target!=0)
    {
        cv.IDCNTRIGHTLINK[CntParams.GeometryLink.idhwndRight].insertEnd(i);
        cv.RIGHTLINKSIGNAL += 0;
    }
    if(CntParams.GeometryLink.BottomLinkEvent_target!=0)
    {
        cv.IDCNTBOTTOMLINK[CntParams.GeometryLink.idhwndBottom].insertEnd(i);
        cv.BOTTOMLINKSIGNAL += 0;
    }
    
    if(cv.cp[i]->ClingToParent)
    {
        SetParent(hwnd, ContPar);
        cv.CATCHLASTPARENT += ContPar;
    }
    else
        cv.CATCHLASTPARENT += 0;

    cv.ID += i;
    return i;
}

HWND csCONTAINER::csc_getContainer(int id)
{
    if(id>0&&id<cv.CNTLIST.size())
        return cv.CNTLIST[id];
    else return 0;
}

csSURFACE* csCONTAINER::csc_getSurface(int id)
{
    return &cv.CTX[id];
}

void csCONTAINER::csc_setSurface(csSURFACE* srf, int id)
{
    if(cv.CTX.size()-1 < id)
    {
        cv.CTX.insertEnd(*srf);
    }
    else
        cv.CTX[id]=*srf;
}

extern int HWNDSIZING; // useless 
extern MSG Messages;
LRESULT CALLBACK ContainerProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    /*if(cv.HWNDCAPTURE==cv.CNTLIST[0])
    {
        if(hwnd == cv.HWNDCAPTURE)
        {
            LRESULT lr=0;
            initContainer                        (hwnd, message, 0);
            lr=resizingContainer            (hwnd, message,lParam, 0);
            if(lr) return lr;
            moveContainer(hwnd, message, wParam, 0);
            mouseHoverLeave(hwnd, message, 0);
        }
    }*/
    
    /*else if(cv.HWNDCAPTURE==cv.CNTLIST[HWNDSIZING])
    {std::cout<<"sdfsdfsdf \n";
        if(hwnd == cv.CNTLIST[HWNDSIZING])
        {
            LRESULT lr=0;
            initContainer                        (hwnd, message, 0);
            lr=resizingContainer            (hwnd, message,lParam, 0);
            if(lr) return lr;
            moveContainer(hwnd, message, wParam, 0);
            mouseHoverLeave(hwnd, message, 0);
        }
    }*/
    //else
    { 
        LRESULT lr=0;
        int id = cv.getContId2(hwnd);
        initContainer                        (hwnd, message, wParam,id);
        lr=resizingContainer            (hwnd, message,lParam, id);
        if(lr) return lr;
        moveContainer(hwnd, message, wParam, id);
        mouseWheel           (hwnd, message,wParam, id);
        eraseBKG(hwnd, message, id);
        //linkGeometry(hwnd, message, id);
        //containerFollowsMouse(hwnd, message, id);
        mouseHoverLeave(hwnd, message, id);
        MouseHoverPopup(hwnd, message, wParam, lParam, id);
        MouseHoverColorGradient(hwnd, message, wParam, lParam, id);
        autoTransformation(hwnd, message, wParam, lParam, id);
        bool catchingArea = catchCnt(hwnd, message, id);
        if((cv.cp[id]->AutoTransformFadeOut.AccelCaptureTime
                && cv.cp[id]->AutoTransformFadeOut.FadeOutTime)
                /*&& !catchingArea*/)//hors de la zone de capture
            autoMoveFade(hwnd, message, id);
        cntTimerEventFunction(hwnd, message, wParam, lParam, id);
        autoAlphaFade(hwnd, message, id);
        blockedWithinPar(hwnd, message,id);
        cntEventsFunction(hwnd, message, wParam, lParam, id);
        createEdit(hwnd,message, id);
        int r=colorEdit(message, wParam, id);
        if (r) return r;
        manageEditBox(hwnd, message, id);

    }
    return DefWindowProc        (hwnd, message, wParam, lParam);
}

void initContainer(HWND hwnd, UINT msg, WPARAM wParam, int id)
{
    if(msg==WM_CREATE)
    {
        bool *bsecurity = (bool*)malloc(sizeof(bool));
        *bsecurity = 0;
        SetUserObjectInformationW(GetCurrentProcess(),
        UOI_TIMERPROC_EXCEPTION_SUPPRESSION,(void*)bsecurity, sizeof(bool));
        SetTimer(hwnd, 0,30,0);

        
        GetWindowRect(hwnd, &cv.CNTRECT[id]);
        GetWindowRect(hwnd, &cv.CNTRECT[id]);
        GetClientRect(hwnd, &cv.CNTCLWRECT[id]);
        GetClientRect(hwnd, &cv.CNTCLWRECT_SAVED[id]);

        cv.HWNDFOCUS = hwnd;

        TIMER_ID++;
    }
    if(msg==WM_NCLBUTTONUP||msg==WM_LBUTTONUP)
    {
        if(cv.cp[cv.CNTPARID[id]]->ColorFilter)
        {
            SetWindowPos(hwnd, HWND_TOP, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
            SetWindowPos(cv.CNTLIST[cv.cp[cv.CNTPARID[id]]->ColorFilter], HWND_TOP, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
        }
        else
            SetWindowPos(hwnd, HWND_TOP, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
    }
    if(msg==WM_NCLBUTTONDOWN||msg==WM_LBUTTONDOWN)
    {
        SetWindowPos(cv.CNTLIST[0], HWND_TOP, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
    }
    if(msg==WM_KEYDOWN)
    {
        if(wParam == VK_CONTROL)
            cv.CONTROL_KEY_DOWN = 1;
        else if(wParam == VK_SHIFT)
            cv.SHIFT_KEY_DOWN = 1;
        else if(wParam == MK_ALT)
            cv.SHIFT_KEY_DOWN = 1;

        if(wParam == VK_RETURN)
        {
            SendMessage(hwnd, WM_MOUSEHOVER,0,0);
            SendMessage(hwnd, WM_LBUTTONDOWN,0,0);
            SendMessage(hwnd, WM_LBUTTONUP,0,0);
        }
    }
    if(msg==WM_KEYUP)
    {
        if(wParam == VK_CONTROL)
            cv.CONTROL_KEY_DOWN = 0;
        else if(wParam == VK_SHIFT)
            cv.SHIFT_KEY_DOWN = 0;
        else if(wParam == MK_ALT)
            cv.SHIFT_KEY_DOWN = 0;
        
        if(wParam == VK_RETURN)
        {
            SendMessage(hwnd, WM_MOUSEHOVER,0,0);
            SendMessage(hwnd, WM_LBUTTONDOWN,0,0);
            SendMessage(hwnd, WM_LBUTTONUP,0,0);
            SendMessage(hwnd, WM_TIMER,0,0);
            //SendMessage(hwnd, WM_MOUSELEAVE,0,0);
            HWND hChild1 = GetWindow(hwnd, GW_CHILD);
            if(hChild1)
            {//std::cout<<"id child : "<<id<<"\n";
                csSetFocus(hChild1);
            }
        }
            
        else if(wParam == VK_TAB && !cv.SHIFT_KEY_DOWN && !cv.CONTROL_KEY_DOWN)
        {
            HWND hnext = GetWindow(hwnd, GW_HWNDNEXT);
            if(hnext)
            {
                csSetFocus(hnext);
            }
            else if((hnext = GetWindow(hwnd, GW_HWNDFIRST)))
            {
                csSetFocus(hnext);
            }
        }
        else if(wParam == VK_TAB && cv.SHIFT_KEY_DOWN && !cv.CONTROL_KEY_DOWN)
        {
            HWND hprev = GetWindow(hwnd, GW_HWNDPREV);
            if(hprev)
            {
                csSetFocus(hprev);
            }
            else if((hprev = GetWindow(hwnd, GW_HWNDLAST)))
            {
                csSetFocus(hprev);
            }
        }
        else if(wParam == VK_TAB && !cv.SHIFT_KEY_DOWN && cv.CONTROL_KEY_DOWN)
        {
            HWND hpar = GetParent(hwnd);
            if(hpar)
            {
                csSetFocus(hpar);
            }
        }
    }
    if(msg == WM_MOUSEMOVE)
    {
        if(wParam == MK_LBUTTON && cv.MAXIMAZED_CNT[id] == 1)
        {
            SendMessage(hwnd, WM_LBUTTONDBLCLK, 0,0);
        }
        /*if(cv.CTX[id].rulerX1 || cv.CTX[id].rulerX2 || 
           cv.CTX[id].rulerY1 || cv.CTX[id].rulerY2)
        {
            InvalidateRect(hwnd,0,1);
        }*/
    }
    if(/*msg==WM_MOUSEMOVE||msg==WM_NCMOUSEMOVE||*/
            msg==WM_NCLBUTTONDOWN||msg==WM_LBUTTONDOWN||
            msg==WM_NCLBUTTONDOWN||msg==WM_LBUTTONDOWN||
            msg==WM_RBUTTONDOWN||msg==WM_NCRBUTTONDOWN||
            msg==WM_RBUTTONDBLCLK||msg==WM_NCRBUTTONDBLCLK/*||
            msg==WM_MOUSEWHEEL||msg==WM_SIZE||msg==WM_MOVE||msg==WM_NCHITTEST*/)// attention ------------
    {
        //SetWindowPos(cv.CNTLIST[0],HWND_TOP,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOREDRAW);
        csSetFocus(id);
    }
    else if(msg == WM_SIZE)
    {
        if(cv.cp[id]->ColorFilter)
        {
            SendMessage(cv.CNTLIST[cv.cp[id]->ColorFilter],WM_TIMER,0,0);
        }
        //InvalidateRect(hwnd, 0,1);
    }
    else if(msg==WM_LBUTTONDBLCLK)
    {
        if(cv.cp[id]->MinMaxStyle == 1)
        {
            if(cv.CURRENT_HITTEST_AREA == CSA_MOVE)
            {
                if(cv.MAXIMAZED_CNT[id] == 0)
                {
                    
                    cv.MAXIMAZED_CNT[id] = 1;
                    GetWindowRect(hwnd, &cv.NORMAL_CNTRECT[id]);
                    if(id != 0)
                        cv.NORMAL_CNTRECT[id] = rectInParentRef(id, cv.NORMAL_CNTRECT[id]);
                    RECT r = cv.NORMAL_CNTRECT[id];
                    //std::cout<<"normal rect : "<<r.left<<","<<r.top<<","<<r.right<<","<<r.bottom<<" --1\n";
                    SIZE msz = cv.cp[id]->MaxSize;
                    int asz = cv.cp[id]->SizingAreaLength;
                    /*cv.cp[id]->AutoTransform.InitialRect=r;
                    cv.cp[id]->AutoTransform.FinalRect={-asz,-asz,msz.cx+asz*2,msz.cy+asz*2};
                    cv.cp[id]->AutoTransform.Time=5;
                    cv.cp[id]->AutoTransform.Type=AUTO_TRANSF_RECT;
                    cv.AUTOTRANSCOUNT[id] = 0;*/
                    MoveWindow(hwnd,-asz, -asz, msz.cx+asz*2, msz.cy+asz*2, 1);
                    InvalidateRect(hwnd,0,1);
                }
                else
                {
                    //SendMessage(hwnd, WM_SIZE,0,0);
                    //ShowWindow(hwnd,SW_NORMAL);
                    RECT r = cv.NORMAL_CNTRECT[id];
                    //SIZE msz = cv.cp[id]->MaxSize;
                    //int asz = cv.cp[id]->SizingAreaLength;
                    /*cv.cp[id]->AutoTransform.InitialRect={-asz,-asz,msz.cx+asz*2,msz.cy+asz*2};
                    cv.cp[id]->AutoTransform.FinalRect= r;
                    cv.cp[id]->AutoTransform.Time=5;
                    cv.cp[id]->AutoTransform.Type=AUTO_TRANSF_RECT;
                    cv.AUTOTRANSCOUNT[id] = 0;*/
                    
                    MoveWindow(hwnd,r.left, r.top, r.right-r.left, r.bottom-r.top, 1);
                    InvalidateRect(hwnd,0,1);

                    cv.MAXIMAZED_CNT[id] = 0;
                }
                SendMessage(hwnd, WM_SIZE, 0 ,0);
            }
        }
    }
    else if(msg==WM_TIMER)
    {
        GetCursorPos(&cv.phit0);
        GetWindowRect(hwnd, &cv.CNTRECT[id]);//---------------------------------------------attention-----------
        if(cv.cp[id]->Show)
        {
            if(!cv.SHOWWINDOWSIGNAL[id])
            {
                ShowWindow(hwnd, 1);
                cv.SHOWWINDOWSIGNAL[id] = 1;
                cv.HIDEWINDOWSIGNAL[id] = 0;
            }
        }
        else
        {
            if(!cv.HIDEWINDOWSIGNAL[id])
            {
                ShowWindow(hwnd, 0);
                cv.SHOWWINDOWSIGNAL[id] = 0;
                cv.HIDEWINDOWSIGNAL[id] = 1;
            }
        }
        /********** evite les conteneurs noirs ou non rafraichis au demarrage******/
        if(!cv.REFRESHCOUNT[id])
        {
            if(IsWindowVisible(hwnd))
            {
                InvalidateRect(hwnd,0,1);
                cv.REFRESHCOUNT[id]=1;
            }
        }
        /**************************** positionnent des regles si presentes*/
        
        if(cv.CTX[id].autoUpdate)
        {
            InvalidateRect(hwnd,0,1);
            cv.CTX[id].autoUpdate = 0;
        }

        /********************* identifier le conteneur ayant le focus *****************************/
        if(cv.HWNDFOCUS == hwnd)
        {
            if(cv.FOCUSOFF[id] == 0)
            {
                cv.CTX[id].setFocusBorderColor({80,80,10});
                cv.HWNDFOCUS_OLD = cv.HWNDFOCUS;
                cv.FOCUSOFF[id] = 1;
            }
        }
        else 
        {
            if(cv.FOCUSOFF[id])
            {
                cv.CTX[id].resetBorderColor();
                cv.FOCUSOFF[id] = 0;
            }
        }
    }
    else if(msg==WM_DESTROY)
    {
        KillTimer(cv.CNTLIST[id],id);
        //destroyContainer(id);
        DestroyWindow(cv.CNTLIST[id]);
    }
}

LRESULT resizingContainer(HWND hwnd, UINT msg, LPARAM lp, int id)
{
    static HCURSOR hc=LoadCursor(0,IDC_ARROW);
    static RECT rc, rw;
    int len, cpos, clen;
    LRESULT lr=0;
    POINT p;
    //static bool bmove;

    if(msg==WM_SIZE||msg==WM_MOVE)
    {
        GetWindowRect(hwnd, &rw);
        cv.CNTRECT[id]=rw;
    }
    if(msg==WM_SIZE)
    {
        GetClientRect(hwnd, &rc);
        cv.CNTCLWRECT[id]=rc;
        if(cv.cp[id]->RedrawWhenResize)
            SendMessage(hwnd,WM_ERASEBKGND,0,0);
    }
    if(msg==WM_MOVE)
    {
        cv.GMOVE=1;
    }
    else if(msg==WM_NCHITTEST&&!SCROLL_SIGNAL_2)
    {
        rc=cv.CNTCLWRECT[id];
        GetCursorPos(&cv.phit);
        ScreenToClient(hwnd,&cv.phit);
        p=cv.phit;
        clen=cv.cp[id]->CaptionAreaLength;
        cpos=cv.cp[id]->CaptionAreaPos;
        len=cv.cp[id]->SizingAreaLength;

        if(cv.cp[id]->CaptionDirection)
        {
            if((cpos==0&&p.x>=len&&p.x<clen+len&&p.y>=len&&p.y<rc.bottom-len)||
                    (cpos==1&&p.x>=len&&p.x<rc.right-len&&p.y>=len&&p.y<clen+len) ||
                    (cpos==2&&p.x>=rc.right-len-clen&&p.x<rc.right-len&&p.y>=len&&p.y<rc.bottom-len)||
                    (cpos==3&&p.x>=len&&p.x<rc.right-len&&p.y>=rc.bottom-clen-len&&p.y<rc.bottom-len))
            {
                //lr=(LRESULT)HTCAPTION;
                lr=(LRESULT)HTCLIENT;
                cv.CURSOR_TYPE=1;
                cv.CURRENT_HITTEST_AREA = CSA_MOVE;
                HWNDSIZING = 0;
            }
        }
        if(cv.cp[id]->HTLeft)
        {
            if(p.x>=0&&p.x<len&&p.y>=len&&p.y<rc.bottom-len)
            {
                lr=(LRESULT)(HTLEFT);
                cv.CURSOR_TYPE=2;
                cv.CURRENT_HITTEST_AREA = CSA_LEFT;
                //std::cout<<cv.CURRENT_HITTEST_AREA<<" id "<< id <<" iuyuyi \n";
                HWNDSIZING = id;
            }
        }
        if(cv.cp[id]->HTTop)
        {
            if(p.x>=len&&p.x<rc.right-len&&p.y>=0&&p.y<len)
            {
                lr=(LRESULT)HTTOP;
                cv.CURSOR_TYPE=3;
                cv.CURRENT_HITTEST_AREA = CSA_TOP;
                HWNDSIZING = id;
            }
        }
        if(cv.cp[id]->HTRight)
        {
            if(p.x>=rc.right-len&&p.x<rc.right&&p.y>=len&&p.y<rc.bottom-len)
            {
                lr=(LRESULT)HTRIGHT;
                cv.CURSOR_TYPE=2;
                cv.CURRENT_HITTEST_AREA = CSA_RIGHT;
                HWNDSIZING = id;
            }
        }
        if(cv.cp[id]->HTBottom)
        {
            if(p.x>=len&&p.x<rc.right-len&&p.y>=rc.bottom-len&&p.y<rc.bottom)
            {
                lr=(LRESULT)HTBOTTOM;
                cv.CURSOR_TYPE=3;
                cv.CURRENT_HITTEST_AREA = CSA_BOTTOM;
                HWNDSIZING = id;
            }
        }
        if(cv.cp[id]->HTCorner)
        {
            if(p.x>=0&&p.x<len&&p.y>=0&&p.y<len)
            {
                lr=(LRESULT)HTTOPLEFT;
                cv.CURSOR_TYPE=4;
                cv.CURRENT_HITTEST_AREA = CSA_NW;
                HWNDSIZING = id;
            }
            if(p.x>=rc.right-len&&p.x<rc.right&&p.y>=0&&p.y<len)
            {
                lr=(LRESULT)HTTOPRIGHT;
                cv.CURSOR_TYPE=5;
                cv.CURRENT_HITTEST_AREA = CSA_NE;
                HWNDSIZING = id;
            }
            if(p.x>=0&&p.x<len&&p.y>=rc.bottom-len&&p.y<rc.bottom)
            {
                lr=(LRESULT)HTBOTTOMLEFT;
                cv.CURSOR_TYPE=5;
                cv.CURRENT_HITTEST_AREA = CSA_SW;
                HWNDSIZING = id;
            }
            if(p.x>=rc.right-len&&p.x<rc.right&&p.y>=rc.bottom-len&&p.y<rc.bottom)
            {
                lr=(LRESULT)HTBOTTOMRIGHT;
                cv.CURSOR_TYPE=4;
                cv.CURRENT_HITTEST_AREA = CSA_SE;
                HWNDSIZING = id;
            }
            //cv.
        }
        if((cpos==0&&p.x>=len+clen&&p.x<rc.right-len&&p.y>=len&&p.y<rc.bottom-len)||
                (cpos==1&&p.x>=len&&p.x<rc.right-len&&p.y>=len+clen&&p.y<rc.bottom-len) ||
                (cpos==2&&p.x>=len&&p.x<rc.right-clen-len&&p.y>=len&&p.y<rc.bottom-len)||
                (cpos==3&&p.x>=len&&p.x<rc.right-len&&p.y>=len&&p.y<rc.bottom-clen-len))
        //if(cv.CURRENT_HITTEST_AREA)
        {
            if(!cv.cp[id]->HTMask)
            {
                cv.CURRENT_HITTEST_AREA = 0;
                lr=(LRESULT)HTCLIENT;
                cv.CURSOR_TYPE=0;
                HWNDSIZING = 0;
            }
            else
            {
                HWNDSIZING = id; 
                // toute la zone client renverra l'un de ces messages
                if(cv.cp[id]->HTMask == CSA_LEFT)
                {
                    lr=(LRESULT)(HTLEFT);
                    cv.CURSOR_TYPE=2;
                    cv.CURRENT_HITTEST_AREA = CSA_LEFT;
                }
                else if(cv.cp[id]->HTMask == CSA_TOP)
                {
                    lr=(LRESULT)(HTTOP);
                    cv.CURSOR_TYPE=3;
                    cv.CURRENT_HITTEST_AREA = CSA_TOP;
                }
                else if(cv.cp[id]->HTMask == CSA_RIGHT)
                {
                    lr=(LRESULT)(HTRIGHT);
                    cv.CURSOR_TYPE=2;
                    cv.CURRENT_HITTEST_AREA = CSA_RIGHT;
                }
                else if(cv.cp[id]->HTMask == CSA_BOTTOM)
                {
                    lr=(LRESULT)(HTRIGHT);
                    cv.CURSOR_TYPE=3;
                    cv.CURRENT_HITTEST_AREA = CSA_BOTTOM;
                }
                HWNDSIZING = id;
            }
        }
        //lr=(LRESULT)HTCLIENT;
    }
    else if(msg==WM_SETCURSOR&&!SCROLL_SIGNAL_2)
    {
        if(cv.CURSOR_TYPE==0)
        {
            if(cv.cp[id]->Cursor)
                hc=SetCursor(cv.cp[id]->Cursor);
            else
                hc=SetCursor(LoadCursor(0,IDC_ARROW));
        }
        if(cv.CURSOR_TYPE==1)
            hc=SetCursor(LoadCursor(0,IDC_SIZEALL));
        if(cv.CURSOR_TYPE==2)
            hc=SetCursor(LoadCursor(0,IDC_SIZEWE));
        if(cv.CURSOR_TYPE==3)
            hc=SetCursor(LoadCursor(0,IDC_SIZENS));
        if(cv.CURSOR_TYPE==4)
            hc=SetCursor(LoadCursor(0,IDC_SIZENWSE));
        if(cv.CURSOR_TYPE==5)
            hc=SetCursor(LoadCursor(0,IDC_SIZENESW));
        lr=(LRESULT)hc;
    }
    else if(msg==WM_GETMINMAXINFO)
    {
        MINMAXINFO *mmi=(MINMAXINFO*)lp;
        //std::cout<<HWND(lp);
        if(cv.cp[id]->MaxTrackSize.cx>0)
            mmi->ptMaxTrackSize.x=cv.cp[id]->MaxTrackSize.cx;
        else if(cv.cp[id]->MaxTrackSize.cx<0)
        {
            mmi->ptMaxTrackSize.x=cv.CNTCLWRECT[cv.CNTPARID[id]].right
                                  -(cv.CNTRECT[cv.CNTPARID[id]].right - cv.CNTRECT[id].right)
                                  +cv.cp[id]->MaxTrackSize.cx;
        }
        if(cv.cp[id]->MaxTrackSize.cy>0)
            mmi->ptMaxTrackSize.y=cv.cp[id]->MaxTrackSize.cy;
        else if(cv.cp[id]->MaxTrackSize.cy<0)
        {
            mmi->ptMaxTrackSize.y=cv.CNTCLWRECT[cv.CNTPARID[id]].bottom
                                  -(cv.CNTRECT[cv.CNTPARID[id]].bottom - cv.CNTRECT[id].bottom)
                                  +cv.cp[id]->MaxTrackSize.cy;
        }

        mmi->ptMinTrackSize.x=cv.cp[id]->MinTrackSize.cx;
        mmi->ptMinTrackSize.y=cv.cp[id]->MinTrackSize.cy;
        if(cv.cp[id]->MaxSize.cx>0)

            mmi->ptMaxSize.x=cv.cp[id]->MaxSize.cx;
        if(cv.cp[id]->MaxSize.cy>0)
            mmi->ptMaxSize.y=cv.cp[id]->MaxSize.cy;

    }
    return lr;
}

void moveContainer(HWND hwnd, UINT msg, WPARAM wp, int id)
{
    static POINT pos = {0};
    static bool b = 0, b1 = 0, b2 = 0, b3 = 0;
    static int idc = 0, a = 2;
    if(msg == WM_LBUTTONDBLCLK)
    {
        if(cv.CAPTIONER && id == cv.CAPTIONER)
        {   
            b3 = 1;// eliminer le bug lie au double clic
            cv.CURRENT_HITTEST_AREA = CSA_MOVE;
            SendMessage(cv.CNTLIST[idc],WM_LBUTTONDBLCLK,0,0);
        }
    }
    else if(msg==WM_LBUTTONDOWN)
    {
        cv.HWNDCAPTURE = hwnd;
        GetCursorPos(&cv.lbtndownPoint);
        SetCapture(hwnd);

    }
    /*else if(msg == WM_NCLBUTTONUP)
    {
        RECT r = cv.CNTRECT[id];
        if(cv.cp[id]->CaptionAreaPos == 0 && r.top < 0)
        {
            if(cv.cp[id]->ClingToParent)
                SetWindowPos(hwnd, HWND_TOP, r.left, 0, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
            else
            {
                r = rectInParentRef(id, r);
                SetWindowPos(hwnd, HWND_TOP, r.left, 0, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
            }
        }
    }*/
    else if(msg==WM_LBUTTONUP)
    {

        cv.HWNDCAPTURE = hwnd;
        ReleaseCapture();

        RECT r = cv.CNTRECT[id];

        if(cv.CAPTIONER && id == cv.CAPTIONER && b2)
        {
            POINT pt;
            GetCursorPos(&pt);


            SetWindowPos(cv.CNTLIST[idc],HWND_TOP,r.left, r.top, r.right-r.left,
                        r.bottom-r.top,SWP_NOSIZE);

            cv.cp[cv.CAPTIONER]->Show = 0;
            SetWindowPos(hwnd,HWND_TOP,pt.x-a, 
                        pt.y-a, 1+2*a,1+2*a,SWP_NOZORDER|SWP_SHOWWINDOW);
            cv.cp[cv.CAPTIONER]->Show = 1;
            csSetTransparency(id, 97);
            SetWindowPos(hwnd,HWND_TOP,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);

            cv.cp[idc]->AutoAlphaFade.FadeTime = 3;
            cv.cp[idc]->AutoAlphaFade.AlphaMin = 20;
            cv.cp[idc]->AutoAlphaFade.State = 1;
            cv.cp[idc]->AutoAlphaFade.Count = cv.cp[idc]->AutoAlphaFade.FadeTime;
            cv.cp[idc]->AutoAlphaFade.Activate = 1;
            b2 = 0;

            
        }


    }
    else if (msg==WM_MOUSEMOVE)
    {
        if(cv.CAPTIONER && id != cv.CAPTIONER && cv.CURRENT_HITTEST_AREA == CSA_MOVE)
        {
            if(b3)
            {
                b3 = 0;
            }
            else
            {
                idc = id;
                POINT ptc;
                GetCursorPos(&ptc);
                SetWindowPos(cv.CNTLIST[cv.CAPTIONER],HWND_TOP,ptc.x-a,ptc.y-a,1+2*a,1+2*a,SWP_NOREDRAW);
            }
        }
        if(wp == MK_LBUTTON)
        {
            if(cv.CAPTIONER && id == cv.CAPTIONER)
            {
                if(b3)
                {
                    b3 = 0;
                }
                else
                {
                    if(!b2)
                    {
                        RECT r = cv.CNTRECT[idc];
                        int dx = r.right-r.left, dy = r.bottom-r.top;
                        csSetTransparency(id, 40);
                        SetWindowPos(hwnd,HWND_TOP,r.left, r.top, dx, dy,SWP_NOZORDER);
                        
                        cv.cp[idc]->AutoAlphaFade.FadeTime = 8;
                        cv.cp[idc]->AutoAlphaFade.AlphaMin = 20;
                        cv.cp[idc]->AutoAlphaFade.State = 0;
                        cv.cp[idc]->AutoAlphaFade.Count = 0;
                        cv.cp[idc]->AutoAlphaFade.Activate = 1;
                        b2 = 1;
                    }
                    b1 = 1;
                    SendMessage(hwnd,WM_TIMER,0,0);
                }
            }
            else
            {
                if(cv.CURRENT_HITTEST_AREA == CSA_MOVE && id == 0)
                {
                    RECT rhwnd_s = cv.CNTRECT_SAVED[id];
                    POINT p=cv.TRACKING_POINT2, pt=cv.TRACKING_POINT;
                    int dx = p.x-pt.x;
                    int dy = p.y-pt.y;
                    int xpos = rhwnd_s.left + dx + cv.EXTRA_TRACKING_VALUE_X;
                    int ypos = rhwnd_s.top + dy + cv.EXTRA_TRACKING_VALUE_Y;
                    SetWindowPos(hwnd,HWND_DESKTOP,xpos,ypos,0,0,SWP_NOSIZE);
                }
                else if(cv.CURRENT_HITTEST_AREA == CSA_MOVE && id != 0)
                {
                    int idp = cv.CNTPARID[id];
                    RECT rwp_s = cv.CNTRECT[idp];
                    RECT rhwnd_s = cv.CNTRECT_SAVED[id];
                    if(cv.cp[id]->ClingToParent)
                    {
                        rhwnd_s.left -= rwp_s.left;
                        rhwnd_s.right -= rwp_s.left;
                        rhwnd_s.top -= rwp_s.top;//interressant avec rwp
                        rhwnd_s.bottom -= rwp_s.top;//interressant avec rwp
                    }
                    RECT rchwnd=cv.CNTCLWRECT[id];
                    POINT p=cv.TRACKING_POINT2, pt=cv.TRACKING_POINT;
                    int dx = p.x-pt.x;
                    int dy = p.y-pt.y;
                    int xpos = rhwnd_s.left + dx + cv.EXTRA_TRACKING_VALUE_X;
                    int ypos = rhwnd_s.top + dy + cv.EXTRA_TRACKING_VALUE_Y;
                    //SetWindowPos(hwnd,HWND_DESKTOP,xpos,ypos,0,0,SWP_NOSIZE);
                    if(cv.cp[id]->CaptionDirection == CAPTION_DIRECTION_ALL)
                    {

                        if(cv.cp[id]->AllowXMinMaxTrackPosition && !cv.cp[id]->AllowYMinMaxTrackPosition)
                        {
                            if(xpos < cv.cp[id]->XMinTrackPosition)
                                SetWindowPos(hwnd,0,cv.cp[id]->XMinTrackPosition, ypos,0,0,SWP_NOSIZE|SWP_NOREDRAW);
                            else if(xpos > cv.cp[id]->XMaxTrackPosition)
                                SetWindowPos(hwnd,0,cv.cp[id]->XMaxTrackPosition, ypos,0,0,SWP_NOSIZE|SWP_NOREDRAW);
                            else
                                SetWindowPos(hwnd,0,xpos,ypos,0,0,SWP_NOSIZE|SWP_NOREDRAW);
                        }
                        else if(cv.cp[id]->AllowYMinMaxTrackPosition && !cv.cp[id]->AllowXMinMaxTrackPosition)
                        {
                            if(ypos < cv.cp[id]->YMinTrackPosition)
                                SetWindowPos(hwnd,0,xpos,cv.cp[id]->YMinTrackPosition,0,0,SWP_NOSIZE|SWP_NOREDRAW);
                            else if(ypos > cv.cp[id]->YMaxTrackPosition)
                                SetWindowPos(hwnd,0,xpos,cv.cp[id]->YMaxTrackPosition,0,0,SWP_NOSIZE|SWP_NOREDRAW);
                            else
                                SetWindowPos(hwnd,0,xpos,ypos,0,0,SWP_NOSIZE|SWP_NOREDRAW);
                        }
                        else if(cv.cp[id]->AllowXMinMaxTrackPosition && cv.cp[id]->AllowYMinMaxTrackPosition)
                        {
                            if(xpos < cv.cp[id]->XMinTrackPosition)
                            {
                                if(ypos < cv.cp[id]->YMinTrackPosition)
                                    SetWindowPos(hwnd,0,cv.cp[id]->XMinTrackPosition,cv.cp[id]->YMinTrackPosition,0,0,SWP_NOSIZE);
                                else if(ypos > cv.cp[id]->YMaxTrackPosition)
                                    SetWindowPos(hwnd,0,cv.cp[id]->XMinTrackPosition,cv.cp[id]->YMaxTrackPosition,0,0,SWP_NOSIZE);
                                else
                                    SetWindowPos(hwnd,0,cv.cp[id]->XMinTrackPosition,ypos,0,0,SWP_NOSIZE);
                            }
                            else if(xpos > cv.cp[id]->XMaxTrackPosition)
                            {
                                if(ypos < cv.cp[id]->YMinTrackPosition)
                                    SetWindowPos(hwnd,0,cv.cp[id]->XMaxTrackPosition,cv.cp[id]->YMinTrackPosition,0,0,SWP_NOSIZE);
                                else if(ypos > cv.cp[id]->YMaxTrackPosition)
                                    SetWindowPos(hwnd,0,cv.cp[id]->XMaxTrackPosition,cv.cp[id]->YMaxTrackPosition,0,0,SWP_NOSIZE);
                                else
                                    SetWindowPos(hwnd,0,cv.cp[id]->XMaxTrackPosition,ypos,0,0,SWP_NOSIZE);
                            }
                            else
                            {
                                if(ypos < cv.cp[id]->YMinTrackPosition)
                                    SetWindowPos(hwnd,0,xpos,cv.cp[id]->YMinTrackPosition,0,0,SWP_NOSIZE);
                                else if(ypos > cv.cp[id]->YMaxTrackPosition)
                                    SetWindowPos(hwnd,0,xpos,cv.cp[id]->YMaxTrackPosition,0,0,SWP_NOSIZE);
                                else
                                    SetWindowPos(hwnd,0,xpos,ypos,0,0,SWP_NOSIZE);
                            }
                        }
                        else
                        {
                            SetWindowPos(hwnd,HWND_TOP,xpos,ypos,0,0,SWP_NOSIZE);
                            /*pos = {xpos,ypos};
                            b = 1;
                            SendMessage(hwnd,WM_TIMER,0,0);*/
                        //GetWindowRect(hwnd, &cv.CNTRECT[id]);
                        }
                    }
                    else if(cv.cp[id]->CaptionDirection == CAPTION_DIRECTION_X)
                    {
                        if(cv.cp[id]->AllowXMinMaxTrackPosition)
                        {
                            if(xpos < cv.cp[id]->XMinTrackPosition)
                                SetWindowPos(hwnd,0,cv.cp[id]->XMinTrackPosition, cv.cp[id]->CaptionDirection_pos,
                                            0,0,SWP_NOSIZE);
                            else if(xpos > cv.cp[id]->XMaxTrackPosition)
                                SetWindowPos(hwnd,0,cv.cp[id]->XMaxTrackPosition, cv.cp[id]->CaptionDirection_pos,
                                            0,0,SWP_NOSIZE);
                            else
                                SetWindowPos(hwnd,0,xpos, cv.cp[id]->CaptionDirection_pos,
                                            0,0,SWP_NOSIZE);
                        }
                        else
                            SetWindowPos(hwnd,0,xpos, cv.cp[id]->CaptionDirection_pos,
                                        0,0,SWP_NOSIZE);
                    }
                    else if(cv.cp[id]->CaptionDirection == CAPTION_DIRECTION_Y)
                    {
                        if(cv.cp[id]->AllowYMinMaxTrackPosition)
                        {
                            if(ypos < cv.cp[id]->YMinTrackPosition)
                                SetWindowPos(hwnd,0,cv.cp[id]->CaptionDirection_pos,cv.cp[id]->YMinTrackPosition,
                                            0,0,SWP_NOSIZE);
                            else if(ypos > cv.cp[id]->YMaxTrackPosition)
                                SetWindowPos(hwnd,0, cv.cp[id]->CaptionDirection_pos,cv.cp[id]->YMaxTrackPosition,
                                            0,0,SWP_NOSIZE);
                            else
                                SetWindowPos(hwnd,0, cv.cp[id]->CaptionDirection_pos,ypos,
                                            0,0,SWP_NOSIZE);
                        }
                        else
                            SetWindowPos(hwnd,0, cv.cp[id]->CaptionDirection_pos,ypos,
                                        0,0,SWP_NOSIZE);
                    }
                }
            }
        }
    }

    if(msg == WM_TIMER)
    {
        if(id == cv.CAPTIONER && cv.CAPTIONER != 0)
        {
            if(b1)
            {
                POINT p=cv.TRACKING_POINT2, pt=cv.TRACKING_POINT;
                RECT rhwnd_s = cv.CNTRECT[idc];
                int dx = p.x-pt.x;
                int dy = p.y-pt.y;
                int xpos = rhwnd_s.left + dx + cv.EXTRA_TRACKING_VALUE_X;
                int ypos = rhwnd_s.top + dy + cv.EXTRA_TRACKING_VALUE_Y;
                SetWindowPos(hwnd,HWND_TOP,xpos,ypos,0,0,SWP_NOSIZE|SWP_NOREDRAW|SWP_NOZORDER);
                b1 = 0;
            }
        }
    }

}

void containerFollowsMouse(HWND hwnd, UINT msg, int id)
{
    if (msg==WM_TIMER)
    {
        if(cv.cp[id]->CursorTracking.AllowCursorTracking)
        {
            //int idc = cv.cp[id]->CursorTracking.SYS_COORD_HWND_ID;
            //if(cv.CNTLIST.size()>=idc)
            {
                POINT p = cv.TIMER_POINT;
                //ScreenToClient(cv.CNTLIST[idc], &p);
                SetWindowPos(hwnd,0,p.x+cv.cp[id]->CursorTracking.geometry.left,
                             p.y+cv.cp[id]->CursorTracking.geometry.top,
                             cv.cp[id]->CursorTracking.geometry.right,
                             cv.cp[id]->CursorTracking.geometry.bottom,SWP_NOZORDER);
            }
        }
    }
}

void mouseHoverLeave(HWND hwnd, UINT msg, int id)
{
    if(msg==WM_MOUSEMOVE)
    {
        if (!cv.MOUSEHOVERSIGNAL[id] /*&& ((cv.cp[id]->MHGradient.GradientType!=GRADIENT_TYPE_NONE)
                                         ||cv.cp[id]->MouseHoverShowCnt.size())*/)
        {
            // start tracking if we aren't already
            TRACKMOUSEEVENT tme;
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_HOVER | TME_LEAVE;
            tme.hwndTrack = hwnd;
            tme.dwHoverTime = cv.cp[id]->MouseHoverTime;
            cv.MOUSEHOVERSIGNAL[id] = TrackMouseEvent(&tme);
            cv.MOUSEHOVERCOUNT[id] = 0;
        }
    }

    else if(msg==WM_MOUSEHOVER)
    {
        //int max_count = cv.cp[id]->MHGradient.GradientNumber*cv.cp[id]->MHGradient.TimeStep
                        //+ cv.cp[id]->MouseHoverTime;
        //SetTimer(hwnd, 0,1,0);
        cv.MOUSEHOVERSIGNAL[id] = FALSE; // tracking now cancelled
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = hwnd;
        //cv.MOUSEHOVERCOUNT[id] = 0;
        cv.MOUSEHOVERSIGNAL[id] = TrackMouseEvent(&tme);
        /*if(!cv.WAITANIMEENDSOUT[id])
        {
            cv.MOUSELEAVECOUNT[id] = 0;
        }*/
        csMH_SHOW_CNT m = cv.cp[id]->MouseHoverShowCnt;
        if(m.Delay)
        {
            cv.cp[id]->MouseHoverShowCnt.MouseHoverCount = cv.cp[id]->MouseHoverShowCnt.Delay;
            cv.cp[id]->MouseHoverShowCnt.MouseLeaveCount = 0;
        }

        if(cv.cp[id]->MouseLeaveTransparency)
        {
            cv.cp[id]->AutoAlphaFade.State = CS_AAF_SHOW_CNTR;
            cv.cp[id]->AutoAlphaFade.Count = cv.cp[id]->AutoAlphaFade.FadeTime;
            cv.cp[id]->AutoAlphaFade.Activate = 1;
        }
        cv.MOUSEHOVERCOUNT[id] = 0;
    }

    else if(msg==WM_MOUSELEAVE)
    {
        cv.MOUSEHOVERSIGNAL[id] = FALSE; // tracking now cancelled
        //cv.MOUSEHOVERCOUNT[id] = 0;
        cv.MOUSELEAVECOUNT[id] = 0;

        csMH_SHOW_CNT m = cv.cp[id]->MouseHoverShowCnt;
        if(m.Delay)
        {
            for(int i=0; i<m.Geometry.size(); i++)
            {
                cv.cp[id]->MouseHoverShowCnt.Geometry[i].left = cv.CNTRECT[i].left;
                cv.cp[id]->MouseHoverShowCnt.Geometry[i].top = cv.CNTRECT[i].top;
            }
            cv.cp[id]->MouseHoverShowCnt.MouseHoverCount = 0;
            cv.cp[id]->MouseHoverShowCnt.MouseLeaveCount = cv.cp[id]->MouseHoverShowCnt.Delay*2;
        }

        if(cv.HWNDCAPTURE == cv.CNTLIST[0])
            cv.HWNDCAPTURE = 0;
        HWNDSIZING = 0;
        cv.CURRENT_HITTEST_AREA = 0;

        if(cv.cp[id]->MouseLeaveTransparency)
        {
            cv.cp[id]->AutoAlphaFade.State = CS_AAF_HIDE_CNTR;
            cv.cp[id]->AutoAlphaFade.Count = 0;
            cv.cp[id]->AutoAlphaFade.Activate = 1;
        }
    }
}

void MouseHoverPopup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, int id)
{
    if(msg == WM_TIMER)
    {
        csMH_SHOW_CNT m = cv.cp[id]->MouseHoverShowCnt;
        if(m.Delay)
        {
            if(cv.cp[id]->MouseHoverShowCnt.MouseHoverCount>0)
            {
                if(cv.cp[id]->MouseHoverShowCnt.MouseHoverCount==1)
                {
                    RECT r = cv.CNTRECT[id]; //in desktop coords
                    RECT rc = cv.CNTCLWRECT[id]; //in desktop coords
                    char*t = cv.cp[id]->Title.Text;
                    for(int i = 0; i<m.Ids.size(); i++)
                    {
                        HWND w=cv.CNTLIST[m.Ids[i]];
                        RECT r1=m.Geometry[i]; //sizes
                        csPOS_BOOL b=m.Bpos[i];

                        int L = (b.bTLeft|b.bBLeft|b.bMLeft)*(r.left-r1.right)
                                +(b.bLTop|b.bLBottom)*(r.left)+(b.bRTop|b.bRBottom)*(r.right-r1.right)
                                +(b.bTRight|b.bBRight|b.bMRight)*(r.right) + b.bOther*r1.left
                                +(b.bMBottom|b.bMTop)*(r.left+(rc.right-r1.right)/2);
                        int T = (b.bLTop|b.bRTop|b.bMTop)*(r.top-r1.bottom)+
                                (b.bTRight|b.bTLeft)*(r.top)+(b.bBRight|b.bBLeft)*(r.bottom-r1.bottom)
                                +(b.bRBottom|b.bLBottom|b.bMBottom)*(r.bottom) + b.bOther*r1.top
                                +(b.bMLeft|b.bMRight)*(r.top+(rc.bottom-r1.bottom)/2);

                        int j = m.Ids[i];
                        cv.cp[j]->Title.Text = t;
                        if(IsWindowVisible(w))
                        //if(cv.cp[m.Ids[i]]->Show)
                        {
                            RECT rp = cv.CNTRECT[j];

                            SetWindowPos(w,0,rp.left,rp.top,r1.right, r1.bottom,SWP_SHOWWINDOW);
                            InvalidateRect(w,0,1);
                            cv.cp[j]->AutoTransform.InitialRect=rp;
                            cv.cp[j]->AutoTransform.FinalRect={L-rp.left,T-rp.top,0,0};
                            cv.cp[j]->AutoTransform.Time=3;
                            cv.cp[j]->AutoTransform.Type=AUTO_TRANSF_LENGTH;
                            //cv.cp[id]->MouseHoverShowCnt.Geometry[i].left = L;
                            //cv.cp[id]->MouseHoverShowCnt.Geometry[i].top = T;
                            cv.AUTOTRANSCOUNT[j] = 0;
                        }
                        else
                        {
                            /*int aafmove = 30;
                            SetWindowPos(w,0,L,T,r1.right,r1.bottom,SWP_SHOWWINDOW);
                            cv.CNTRECT_SAVED[j]={L,T,r1.right,r1.bottom};
                            cv.cp[j]->AutoAlphaFade.Geometry = {0,0,0,0};
                            cv.cp[j]->AutoAlphaFade.FadeTime = 8;
                            cv.cp[j]->AutoAlphaFade.AlphaMin = 50;
                            cv.cp[j]->AutoAlphaFade.ShowHide = 1;
                            cv.cp[j]->AutoAlphaFade.State = CS_AAF_SHOW_CNTR;
                            cv.cp[j]->AutoAlphaFade.Activate = 1;*/
                            SetWindowPos(w,0,L,T,r1.right,r1.bottom,SWP_SHOWWINDOW);
                        }
                    }
                    //cv.BHOOK_LBUTNDOWN_POPUP = 1;
                }
                cv.cp[id]->MouseHoverShowCnt.MouseHoverCount--;
            }
            if(cv.cp[id]->MouseHoverShowCnt.MouseLeaveCount>0)
            {
                RECT r, r1;
                if(cv.cp[id]->MouseHoverShowCnt.MouseLeaveCount==cv.cp[id]->MouseHoverShowCnt.Delay*2-2)
                {
                    //entre cette condition et la suivante, il y'a un espce de temps pendant lequel
                    //la fenetre peut se deplacer. Dans cas il ne faut pa la masquer.
                    for(int i = 0; i<m.Ids.size(); i++)
                    {
                        GetWindowRect(cv.CNTLIST[m.Ids[i]],&r1);
                        cv.cp[id]->MouseHoverShowCnt.Geometry[i].left=r1.left;
                        cv.cp[id]->MouseHoverShowCnt.Geometry[i].top=r1.top;
                    }
                }
                if(cv.cp[id]->MouseHoverShowCnt.MouseLeaveCount==1)
                {
                    POINT p=cv.TIMER_POINT;
                    for(int i = 0; i<m.Ids.size(); i++)
                    {
                        r = cv.cp[id]->MouseHoverShowCnt.Geometry[i];
                        GetWindowRect(cv.CNTLIST[m.Ids[i]],&r1);

                        if((r1.left==r.left && r1.top==r.top) &&
                            !(PtInRect(&r1,p)&& cv.cp[id]->MouseHoverShowCnt.Lock))
                            ShowWindow(cv.CNTLIST[m.Ids[i]],SW_HIDE);
                            //cv.cp[m.Ids[i]]->Show = 0;
                    }
                }
                cv.cp[id]->MouseHoverShowCnt.MouseLeaveCount--;
            }

        }

    }
}

void MouseHoverColorGradient(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, int id)
{
    //------------ Clk Gragient -----------------
    static int pid=0;
    static BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    if(msg == WM_LBUTTONDOWN)
    {//std::cout<<id<<"\n";
        if(cv.cp[id]->ClkGradient.GradientType==CS_GRAD_COLOR &&
                cv.cp[id]->ClkGradient.TimeStep)
        {
            csRGBA c3=cv.cp[id]->ClkGradient.Color;
            HBRUSH brush = CreateSolidBrush(RGB(c3.r, c3.g, c3.b));
            //SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)brush);
            //InvalidateRect(hwnd,0,1);
            cv.CTX[id].setBkgBrush(c3);
            SendMessage(hwnd,WM_ERASEBKGND,0,0);
        }
        else if(cv.cp[id]->ClkGradient.GradientType==CS_GRAD_IMAGE &&
                    (!cv.cp[id]->LockedMode.Lockable))
        {
            cv.MOUSEHOVERSIGNAL[id] = 1;
            cv.MOUSEHOVERCOUNT[id] = 0;
        }
    }
    else if(msg == WM_LBUTTONUP)
    {
        POINT p;
        GetCursorPos(&p); // verifier que le point n'est pas hors du cadre du conteneur
        if(PtInRect(&cv.CNTRECT[id], p))
        {
            if(cv.cp[id]->ClkGradient.GradientType==CS_GRAD_COLOR &&
                    cv.cp[id]->ClkGradient.TimeStep)
            {
                cv.CLICKGRADIENTCOUNT[id] = 0;
            }
            if(cv.cp[id]->LockedMode.Lockable)
            {
                if(cv.cp[id]->LockedMode.Locked)
                {
                    if((!cv.cp[id]->LockedMode.ExternalUnlocking) || (!cv.EXTUNLOCKINGCNT[id].size()))
                    {
                        cv.cp[id]->LockedMode.Locked = 0;
                        cv.cp[id]->LockedMode.LockingActivated = 0;
                    }
                }
                else
                {
                    //cv.cp[id]->LockedMode.Locked = 1;
                    cv.cp[id]->LockedMode.Locked = 1;
                    cv.cp[id]->LockedMode.LockingActivated = 1;
                    if(cv.cp[id]->LockedMode.LockingImagePath)
                    {
                        int id0 = id;
                        if(cv.cp[id]->SameDesignAs) id0 = cv.cp[id]->SameDesignAs;
                        HDC dc=cv.CTX[id].getDC();
                        csDC bdc = cv.DCLOCK[id0];
                        BitBlt(dc,cv.cp[id0]->MHGradient.Position.x,cv.cp[id0]->MHGradient.Position.y,
                            bdc.sz.width,bdc.sz.height,
                            bdc.dc,0,0,SRCCOPY);
                        SendMessage(hwnd,WM_ERASEBKGND,0,0);
                    }
                    int*t = (cv.EXTUNLOCKINGCNT[id].getTable());
                    if(t)
                    {
                        int n = cv.EXTUNLOCKINGCNT[id].size();
                        std::cout<<n<<" -- n\n";
                        for(int i=0; i<n; i++)
                        {
                            if(t[i] != id)
                            {
                                cv.cp[t[i]]->LockedMode.Locked = 0;
                                cv.cp[t[i]]->LockedMode.LockingActivated = 0;
                                SendMessage(cv.CNTLIST[t[i]],WM_ERASEBKGND,0,0);
                                if(cv.EXTHIDECNT[t[i]].size() && cv.EXTHIDECNT[id].size() /*&& IsWindowVisible(cv.CNTLIST[cv.EXTHIDECNT[id][0]])*/)
                                {
                                    for(int j=0; j<cv.EXTHIDECNT[t[i]].size(); j++)
                                    {
                                        //cv.cp[cv.EXTHIDECNT[t[i]][j]]->Show = 0;
                                        int k = cv.EXTHIDECNT[t[i]][j];
                                        GetWindowRect(cv.CNTLIST[k],&cv.CNTRECT_SAVED[k]);
                                        cv.cp[k]->AutoAlphaFade.FadeTime = 8;
                                        cv.cp[k]->AutoAlphaFade.AlphaMin = 100;
                                        cv.cp[k]->AutoAlphaFade.State = 0;
                                        cv.cp[k]->AutoAlphaFade.Count = 0;
                                        cv.cp[k]->AutoAlphaFade.SetGeometry = 1;
                                        cv.cp[k]->AutoAlphaFade.Geometry = {0,50,0,0};
                                        cv.cp[k]->AutoAlphaFade.ShowHide = 1;
                                        cv.cp[k]->AutoAlphaFade.Activate = 1;
                                        //InvalidateRect(cv.CNTLIST[k],0,1);
                                    }
                                }
                            }
                            else
                            {
                                if(cv.EXTHIDECNT[id].size()&&!IsWindowVisible(cv.CNTLIST[cv.EXTHIDECNT[id][0]]))
                                {
                                    for(int j=0; j<cv.EXTHIDECNT[id].size(); j++)
                                    {
                                        int k = cv.EXTHIDECNT[id][j];
                                        //cv.cp[k]->Show = 1;
                                        GetWindowRect(cv.CNTLIST[k],&cv.CNTRECT_SAVED[k]);
                                        cv.cp[k]->AutoAlphaFade.FadeTime = 8;
                                        cv.cp[k]->AutoAlphaFade.AlphaMin = 100;
                                        cv.cp[k]->AutoAlphaFade.State = 1;
                                        cv.cp[k]->AutoAlphaFade.Count = cv.cp[k]->AutoAlphaFade.FadeTime;
                                        cv.cp[k]->AutoAlphaFade.SetGeometry = 1;
                                        cv.cp[k]->AutoAlphaFade.Geometry = {0,-50,0,0};
                                        cv.cp[k]->AutoAlphaFade.ShowHide = 1;
                                        cv.cp[k]->AutoAlphaFade.Activate = 1;
                                        //InvalidateRect(cv.CNTLIST[k],0,1);
                                    }
                                }
                            }
                        }
                    }
                }
                //evite le clignotement apres le clic
                unsigned int GradientNumber=cv.cp[id]->MHGradient.GradientNumber;
                unsigned int TimeStep=cv.cp[id]->MHGradient.TimeStep;
                unsigned int mx = GradientNumber*TimeStep+1;
                cv.MOUSEHOVERCOUNT[id] = mx;

            }
        }
    }
    //------------------------------------------------------
    else if(msg == WM_TIMER)
    {
        /************************* NE CONCERNE PAS CETTE PROCEDURE ********************************/
        if(cv.CNTCREATION[id])
        {
            if(cv.cp[id]->BackgroundImage)
            {
                //csBmpToCntSurface(cv.cp[id]->BackgroundImage,cv.cp[id]->BackgroundImageSizes, cv.CTX[id].getDC());
            }
            else if(cv.cp[id]->SameBackgroundCnt > -1)
            {
                int i = cv.cp[id]->SameBackgroundCnt;
                csSIZE dcs = cv.cp[id]->DCSizes, dcs1 = cv.cp[id]->DCSizes;
                SetStretchBltMode(cv.CTX[id].getDC(),HALFTONE);
                StretchBlt(cv.CTX[id].getDC(),0,0, dcs.width, dcs.height, cv.CTX[i].getDC(),0,0,dcs1.width, dcs1.height,0);
            }
            //drawCntTitle(cv.cp[id]->Title, cv.CTX[id].getDC());
            RECT r=cv.cp[id]->Geometry;
            //ShowWindow(hwnd,1);
            SetWindowPos(hwnd, HWND_TOP, 0, 0, r.right, r.bottom, SWP_NOMOVE|SWP_NOZORDER);
            ShowWindow(hwnd,cv.cp[id]->Show);
            //SendMessage(hwnd,WM_MOUSEMOVE,0,0);

            int n = cv.cp[id]->CntEventsFunc.CREATE.size();
            pid=id;
            for(int i=0; i<n; i++)
            {
                cv.cp[id]->CntEventsFunc.CREATE_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
                (*(cv.cp[id]->CntEventsFunc.CREATE[i]))( cv.cp[id]->CntEventsFunc.CREATE_ARGS[i] );
            }
            //csRGBA col = cv.cp[id]->BackgroundColor;
            //UpdateLayeredWindow(hwnd,0,0,0,0,0,RGB(col.r,col.g,col.b),&bf,0);
            cv.CNTCREATION[id]=0;
        }
        /******************************************************************************************/

        if((cv.cp[id]->MHGradient.GradientType==CS_GRAD_COLOR) &&
                    (!cv.cp[id]->LockedMode.Locked))
        {
            unsigned int GradientNumber=cv.cp[id]->MHGradient.GradientNumber;
            unsigned int TimeStep=cv.cp[id]->MHGradient.TimeStep;
            unsigned int mx = GradientNumber*TimeStep;
            if(cv.MOUSEHOVERSIGNAL[id] &&
                    cv.MOUSEHOVERCOUNT[id] <= mx)
            {
                cv.WAITANIMEENDSIN[id]=1;
                csRGBA c1=cv.cp[id]->MHGradient.Color2;
                csRGBA c2=cv.cp[id]->MHGradient.Color1;
                //std::cout<<(int)c2.r<<" unlocked\n";
                csRGBA c3;
                float f = float(cv.MOUSEHOVERCOUNT[id])/mx;
                c3.r = (unsigned int)(c2.r*f + c1.r*(1.0-f));
                c3.g = (unsigned int)(c2.g*f + c1.g*(1.0-f));
                c3.b = (unsigned int)(c2.b*f + c1.b*(1.0-f));
                cv.CTX[id].setBkgBrush(c3);
                SendMessage(hwnd,WM_ERASEBKGND,0,0);
                if(cv.MOUSEHOVERCOUNT[id] == mx)
                {
                    cv.WAITANIMEENDSIN[id]=0;
                }
                cv.MOUSEHOVERCOUNT[id]++;

            }
            else if(!cv.MOUSEHOVERSIGNAL[id] &&
                    cv.MOUSELEAVECOUNT[id] <= mx)
            {
                cv.WAITANIMEENDSOUT[id]=1;
                csRGBA c1=cv.cp[id]->MHGradient.Color2;
                csRGBA c2=cv.cp[id]->MHGradient.Color1;
                if(cv.cp[id]->LockedMode.ExtBool)
                    c2 = cv.cp[id]->LockedMode.LockingColor;
                csRGBA c3;
                float f = float(cv.MOUSELEAVECOUNT[id])/mx;
                c3.r = (unsigned int)(c1.r*f + c2.r*(1.0-f));
                c3.g = (unsigned int)(c1.g*f + c2.g*(1.0-f));
                c3.b = (unsigned int)(c1.b*f + c2.b*(1.0-f));

                cv.CTX[id].setBkgBrush(c3);
                if(cv.MOUSELEAVECOUNT[id] == mx)
                {
                    if(cv.cp[id]->MouseLeaveRemoveBkg)
                        cv.CTX[id].setBkgBrush(cv.cp[id]->BackgroundColor);
                    cv.WAITANIMEENDSOUT[id]=0;
                    if(cv.cp[id]->LockedMode.ExtBool)
                        cv.cp[id]->LockedMode.ExtBool=0;
                    //SetTimer(hwnd, 0,100,0);
                }
                SendMessage(hwnd,WM_ERASEBKGND,0,0);
                cv.MOUSELEAVECOUNT[id]++;
            }
        }
        else if((cv.cp[id]->MHGradient.GradientType==CS_GRAD_IMAGE
                ||cv.cp[id]->MHGradient.GradientType==CS_GRAD_IMAGE_COLOR)&&
                    (!cv.cp[id]->LockedMode.Locked))
        {
            int id0 = id;/************ problem ici ******************/
            if(cv.cp[id]->SameDesignAs) id0 = cv.cp[id]->SameDesignAs;
            unsigned int GradientNumber=cv.cp[id0]->MHGradient.GradientNumber;
            unsigned int TimeStep=cv.cp[id0]->MHGradient.TimeStep;
            unsigned int mx = (GradientNumber-1)*TimeStep;
            if(cv.MOUSEHOVERSIGNAL[id] &&
                    cv.MOUSEHOVERCOUNT[id] <= mx)
            {
                cv.WAITANIMEENDSIN[id]=1;
                int i = cv.MOUSEHOVERCOUNT[id]/TimeStep;
                HDC dc=cv.CTX[id].getDC();
                //csRGBA c=cv.cp[id0]->BackgroundColor;
                BitBlt(dc,cv.cp[id0]->MHGradient.Position.x,cv.cp[id0]->MHGradient.Position.y,
                       cv.MHGRADIENTDC[id0][i].sz.width,cv.MHGRADIENTDC[id0][i].sz.height,
                       cv.MHGRADIENTDC[id0][i].dc,0,0,SRCCOPY);
                //InvalidateRect(hwnd,0,1);
                SendMessage(hwnd,WM_ERASEBKGND,0,0);
                if(cv.MOUSEHOVERCOUNT[id] == mx)
                    cv.WAITANIMEENDSIN[id]=0;
                cv.MOUSEHOVERCOUNT[id]++;
            }
            else if(!cv.MOUSEHOVERSIGNAL[id] &&
                    cv.MOUSELEAVECOUNT[id] <= mx)
            {
                cv.WAITANIMEENDSOUT[id]=1;
                int i = cv.MOUSELEAVECOUNT[id]/TimeStep;
                int n=GradientNumber-1-i;
                HDC dc=cv.CTX[id].getDC();
                //std::cout<<cv.MHGRADIENTDC[id0][n].dc<<"\n";
                BitBlt(dc,cv.cp[id0]->MHGradient.Position.x,cv.cp[id0]->MHGradient.Position.y,
                       cv.MHGRADIENTDC[id0][n].sz.width,cv.MHGRADIENTDC[id0][n].sz.height,
                       cv.MHGRADIENTDC[id0][n].dc,0,0,SRCCOPY);
                /*csRGBA c=cv.cp[id0]->BackgroundColor;
                TransparentBlt(dc,cv.cp[id0]->MHGradient.Position.x,cv.cp[id0]->MHGradient.Position.y,
                       cv.MHGRADIENTDC[id0][n].sz.width,cv.MHGRADIENTDC[id0][n].sz.height,
                       cv.MHGRADIENTDC[id0][n].dc,0,0,cv.MHGRADIENTDC[id0][n].sz.width,
                       cv.MHGRADIENTDC[id0][n].sz.height,RGB(c.r,c.g,c.b));*/
                //InvalidateRect(hwnd,0,1);
                SendMessage(hwnd,WM_ERASEBKGND,0,0);
                if(cv.MOUSELEAVECOUNT[id] == mx)
                {
                    cv.WAITANIMEENDSOUT[id]=0;
                    //SetTimer(hwnd, 0,100,0);
                }
                cv.MOUSELEAVECOUNT[id]++;
            }
        }

        unsigned int GradientNumber2=cv.cp[id]->ClkGradient.GradientNumber;
        unsigned int TimeStep2=cv.cp[id]->ClkGradient.TimeStep;
        unsigned int mx2 = GradientNumber2*TimeStep2;
        if((cv.cp[id]->ClkGradient.GradientType==CS_GRAD_COLOR || cv.cp[id]->ClkGradient.GradientType==CS_GRAD_BOTH) &&
                cv.CLICKGRADIENTCOUNT[id] < mx2)
        {
            RECT r = cv.CNTRECT[id];
            POINT p;
            GetCursorPos(&p);
            //csRGBA c2=cv.cp[id]->BackgroundColor;
            csRGBA c2=cv.cp[id]->MHGradient.Color2;
            if(cv.cp[id]->MHGradient.GradientType==CS_GRAD_COLOR/* &&
                    PtInRect(&r,p)*/)
            {
                if(cv.cp[id]->LockedMode.Lockable && cv.cp[id]->LockedMode.Locked)
                    c2=cv.cp[id]->LockedMode.LockingColor;
                else
                    c2 = cv.cp[id]->MHGradient.Color1;
            }
            csRGBA c1=cv.cp[id]->ClkGradient.Color;
            csRGBA c3;
            float f = float(cv.CLICKGRADIENTCOUNT[id])/mx2;
            c3.r = (unsigned int)(c2.r*f + c1.r*(1.0-f));
            c3.g = (unsigned int)(c2.g*f + c1.g*(1.0-f));
            c3.b = (unsigned int)(c2.b*f + c1.b*(1.0-f));
            cv.CTX[id].setBkgBrush(c3);
            SendMessage(hwnd,WM_ERASEBKGND,0,0);
            //DeleteBrush(brush); //-----------------------attention--------------
            cv.CLICKGRADIENTCOUNT[id]++;
            if(cv.CLICKGRADIENTCOUNT[id]==mx2)
            {
                if(cv.cp[id]->LockedMode.Lockable && cv.cp[id]->LockedMode.Locked)
                {
                    cv.CTX[id].setBkgBrush(cv.cp[id]->LockedMode.LockingColor);
                    SendMessage(hwnd,WM_ERASEBKGND,0,0);
                    //cv.cp[id]->LockedMode.Locked = 0;
                }
            }
        }
        /*else if(cv.cp[id]->ClkGradient.GradientType==CS_GRAD_IMAGE &&
                cv.CLICKGRADIENTCOUNT[id] < mx2 && cv.CLICKGRADIENTCOUNT[id] >= 0)
        {
            RECT r = cv.CNTRECT[id];
            POINT p;
            GetCursorPos(&p);
            //csRGBA c2=cv.cp[id]->BackgroundColor;
            csRGBA c2=cv.cp[id]->MHGradient.Color2;
            int i = cv.CLICKGRADIENTCOUNT[id]/(mx2-TimeStep2);

            HDC dc=cv.CTX[id].getDC();
            BitBlt(dc,0,0,cv.MHGRADIENTDC[id][i].sz.width,cv.MHGRADIENTDC[id][i].sz.height,
                   cv.MHGRADIENTDC[id][i].dc,0,0,SRCCOPY);
            SendMessage(hwnd,WM_ERASEBKGND,0,0);

            if(cv.cp[id]->MHGradient.GradientType==CS_GRAD_COLOR &&
                    PtInRect(&r,p))
                cv.CLICKGRADIENTCOUNT[id]++;
            else cv.CLICKGRADIENTCOUNT[id]--;

        }*/
    }
}

RECT rectInParentRef(int id)
{
    RECT rw = cv.CNTRECT_SAVED[id], rwp;
    if(cv.cp[id]->ClingToParent)//-pour un changement de parent, verifier ce parametre-----------
    {
        rwp=cv.CNTRECT[cv.CNTPARID[id]];
        rw.left-=rwp.left;
        rw.top-=rwp.top;
        rw.right-=rwp.left;
        rw.bottom-=rwp.top;
    }
    return rw;
}

RECT rectInParentRef(int id, RECT r)
{
    RECT rw = r, rwp;
    if(cv.cp[id]->ClingToParent)//-pour un changement de parent, verifier ce parametre-----------
    {
        rwp=cv.CNTRECT[cv.CNTPARID[id]];
        rw.left-=rwp.left;
        rw.top-=rwp.top;
        rw.right-=rwp.left;
        rw.bottom-=rwp.top;
    }
    return rw;
}

void autoTransformation(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, int id)
{
    if(msg == WM_TIMER && !cv.cp[id]->AutoTransform.EmergencyStop)
    {
        //RECT rw = rectInParentRef(id);
        if(cv.cp[id]->AutoTransform.Type==AUTO_TRANSF_LENGTH)
        {
            unsigned int Time=cv.cp[id]->AutoTransform.Time;
            //unsigned int Count=cv.cp[id]->AutoTransform.Count;//nombre de fois que l'action est sollicitee
            if(cv.AUTOTRANSCOUNT[id] <= Time)
            {
                RECT rw = cv.cp[id]->AutoTransform.InitialRect;
                RECT r = cv.cp[id]->AutoTransform.FinalRect;
                float t = cv.AUTOTRANSCOUNT[id];

                csPOS_FUNC pf = cv.cp[id]->AutoTransform.PosFunc;
                int x = pf.Get(t, Time, r.left, rw.left);
                int y = pf.Get(t, Time, r.top, rw.top);
                int cx = pf.Get(t, Time, r.right, rw.right-rw.left);
                int cy = pf.Get(t, Time, r.bottom, rw.bottom-rw.top);
//std::cout<<id<<"{"<<r.right<<"}  ";

                if(cv.AUTOTRANSCOUNT[id]<Time)
                    SetWindowPos(hwnd,cv.cp[id]->AutoTransform.Range, x, y, cx, cy, SWP_NOZORDER);
                else 
                {
                    SetWindowPos(hwnd,cv.cp[id]->AutoTransform.Range, rw.left+r.left, rw.top+r.top,
                    rw.right-rw.left+r.right, rw.bottom-rw.top+r.bottom,SWP_NOZORDER);
                    //std::cout<<id<<"{"<<r.right<<"}  ";
                }
                if(cv.cp[id]->AutoTransform.Update)
                    InvalidateRect(hwnd, 0,1);
                cv.AUTOTRANSCOUNT[id]++;
                cv.cp[id]->AutoTransform.waitUntilAnimEnds=1;
            }
            else
            {
                cv.cp[id]->AutoTransform.waitUntilAnimEnds=0;//nouveau----=1  -----------------------
                //std::cout<<545;
            }
        }
        else if(cv.cp[id]->AutoTransform.Type==AUTO_TRANSF_RECT)
        {
            unsigned int Time=cv.cp[id]->AutoTransform.Time;
            //unsigned int Count=cv.cp[id]->AutoTransform.Count;//nombre de fois que l'action est sollicitee
            if(cv.AUTOTRANSCOUNT[id] <= Time)
            {
                RECT rw = cv.cp[id]->AutoTransform.InitialRect;
                RECT r = cv.cp[id]->AutoTransform.FinalRect;
                float t = cv.AUTOTRANSCOUNT[id];

                csPOS_FUNC pf = cv.cp[id]->AutoTransform.PosFunc;
                int x = pf.Get(t, Time, r.left-rw.left, rw.left);
                int y = pf.Get(t, Time, r.top-rw.top, rw.top);
                int cx = pf.Get(t, Time, r.right-rw.right, rw.right);
                int cy = pf.Get(t, Time, r.bottom-rw.bottom, rw.bottom);
//std::cout<<cx<<"  ";
                if(cv.AUTOTRANSCOUNT[id] == Time)
                {
                    SetWindowPos(hwnd,cv.cp[id]->AutoTransform.Range, r.left, r.top, 
                                    r.right-r.left, r.bottom-r.top, SWP_NOZORDER);
                }
                else
                    SetWindowPos(hwnd, cv.cp[id]->AutoTransform.Range ,x, y, cx, cy, SWP_NOZORDER);
                
                if(cv.cp[id]->AutoTransform.Update)
                    InvalidateRect(hwnd, 0,1);

                cv.AUTOTRANSCOUNT[id]++;
                cv.cp[id]->AutoTransform.waitUntilAnimEnds=1;
            }
            else
            {
                cv.cp[id]->AutoTransform.waitUntilAnimEnds=0;//nouveau----=1  -----------------------
            }
        }
    }

}

bool blockedWithinPar(HWND hwnd, UINT msg, int id)
{
    if(msg==WM_TIMER && cv.cp[id]->BlockedWithinParent)
    {
        int idp = cv.CNTPARID[id];
        RECT rp = cv.CNTRECT[idp], r = cv.CNTRECT[id];
        cv.cp[id]->AllowXMinMaxTrackPosition=1;
        if(cv.cp[id]->XMinTrackPosition_extra)
        {
            cv.cp[id]->XMinTrackPosition = -(r.right-r.left)+cv.cp[id]->XMinTrackPosition_extra;
            cv.cp[id]->XMaxTrackPosition = (rp.right-rp.left)-cv.cp[id]->XMinTrackPosition_extra;
        }
        else
        {
            cv.cp[id]->XMinTrackPosition = 0;
            cv.cp[id]->XMaxTrackPosition = (rp.right-rp.left)-(r.right-r.left);
        }
        cv.cp[id]->AllowYMinMaxTrackPosition=1;
        if(cv.cp[id]->YMinTrackPosition_extra)
        {
            cv.cp[id]->YMinTrackPosition = -(r.bottom-r.top)+cv.cp[id]->YMinTrackPosition_extra;
            cv.cp[id]->YMaxTrackPosition = (rp.bottom-rp.top)-cv.cp[id]->YMinTrackPosition_extra;
        }
        else
        {
            cv.cp[id]->YMinTrackPosition = 0;
            cv.cp[id]->YMaxTrackPosition = (rp.bottom-rp.top)-(r.bottom-r.top);
        }
    }
}

bool catchCnt(HWND hwnd, UINT msg, int id)
{
    static bool activate=0;
    static RECT r;
    static HWND hf, hpar;
    static int idf, idp;
    if(msg==WM_LBUTTONDOWN)
    {
        cv.captionControl=1;
    }

    else if(msg == WM_TIMER)
    {
        r=cv.cp[id]->RectCatchCnt;
        if(r.right && r.bottom)
        {
            hf = GetFocus();
            idf = cv.getContId2(hf);
            RECT rwf = cv.CNTRECT[idf];
            RECT rw = cv.CNTRECT[id];
            r.left = rw.left;
            r.top = rw.top;
            r.right += rw.left;
            r.bottom += rw.bottom;

            POINT p;
            GetCursorPos(&p);

            if(PtInRect(&r,p) && PtInRect(&rwf,p) && (hf!=hwnd))
            {
                activate = 1;
                hpar = hwnd;
                idp = id;
                if(cv.captionControl)
                    SetLayeredWindowAttributes(hf,0,100,LWA_ALPHA);
            }
            else
            {
                activate = 0;
                SetLayeredWindowAttributes(hf,0,255,LWA_ALPHA);
            }
        }
    }
    else if (msg == WM_LBUTTONUP)
    {
        if(activate)
        {
            RECT r2=cv.cp[idp]->RectCatchCnt;
            RECT rp = cv.CNTRECT[idp];
            RECT rf = cv.CNTRECT[idf];
            if(cv.CATCHLASTPARENT[idf] != cv.CNTLIST[idp])
                cv.CATCHLASTGEOMETRY[idf] = cv.CNTRECT_SAVED[idf];
            cv.CATCHLASTPARENT[idf] = cv.CNTLIST[idp];
            if(cv.cp[idf]->ClingToParent==0)
                cv.CATCHLASTPARENT[idf]=0;

            cv.CNTRECT_SAVED[idf]=rf;//actualiser
            //SetParent(hf,hpar);
            //MoveWindow(hf,r2.left,r2.top, r2.right, r2.bottom, 1);

            cv.cp[idf]->ClingToParent = 1;
            cv.CNTPARID[idf] = idp;
            SetLayeredWindowAttributes(hf,0,255,LWA_ALPHA);

            cv.cp[idf]->AutoTransform.Type = AUTO_TRANSF_LENGTH;
            cv.cp[idf]->AutoTransform.Time = 10;
            cv.cp[idf]->AutoTransform.FinalRect = {r2.left-(rf.left-rp.left),
                                              r2.top-(rf.top-rp.top),
                                              r2.right-(rf.right-rf.left),
                                              r2.bottom-(rf.bottom-rf.top)
                                             };
            cv.cp[idf]->AutoTransform.PosFunc = {1,2.2};
            cv.cp[idf]->AutoTransform.SizeFunc = {1,2.2};
            cv.AUTOTRANSCOUNT[id] = 0;
            SetParent(hf,hpar);
        }
        cv.captionControl=0;
    }
    return activate;
}

void autoAlphaFade(HWND hwnd, UINT msg, int id)
{
    if(msg==WM_TIMER && cv.cp[id]->AutoAlphaFade.Activate==1)
    {
        int time = cv.cp[id]->AutoAlphaFade.FadeTime;
        BYTE AlphaMin = cv.cp[id]->AutoAlphaFade.AlphaMin;
        bool state = cv.cp[id]->AutoAlphaFade.State;
        RECT r = cv.CNTRECT_SAVED[id];
        if(cv.cp[id]->AutoAlphaFade.SetGeometry && GetParent(hwnd)!=0)
            r=rectInParentRef(id);
        if(cv.cp[id]->AutoAlphaFade.Count <= time && state==0)
        {
            float t =  cv.cp[id]->AutoAlphaFade.Count;
            float rat = t/time;
            //BYTE alpha = cv.cp[id]->AutoAlphaFade.GetAlpha(t);
            //std::cout<<"alpha = "<<(int)alpha<<"\n";
            SetLayeredWindowAttributes(hwnd, 0, AlphaMin+(255-AlphaMin)*(1.0-rat), LWA_ALPHA);
            //InvalidateRect(hwnd,0,1);
            if(cv.cp[id]->AutoAlphaFade.SetGeometry)
            {
                RECT rg = cv.cp[id]->AutoAlphaFade.Geometry;
                MoveWindow(hwnd,rg.left*rat+r.left,rg.top*rat+r.top,rg.right*rat+r.right-r.left,rg.bottom*rat+r.bottom-r.top,1);
            }

            cv.cp[id]->AutoAlphaFade.Count++;

            if(cv.cp[id]->AutoAlphaFade.Count == time)
            {
                SetLayeredWindowAttributes(hwnd, 0, AlphaMin, LWA_ALPHA);
                if(cv.cp[id]->AutoAlphaFade.ShowHide)
                {
                    ShowWindow(hwnd,0);
                    cv.cp[id]->AutoAlphaFade.State = 1;
                }
                cv.cp[id]->AutoAlphaFade.Activate = 0;

                if(cv.cp[id]->AutoAlphaFade.SetGeometry)
                    MoveWindow(hwnd,r.left,r.top,r.right-r.left,r.bottom-r.top,1);
                //InvalidateRect(hwnd,0,1);
            }
        }
        //else
        else if(cv.cp[id]->AutoAlphaFade.Count >= 0  && state==1) // nouveau
        {
            float t =  cv.cp[id]->AutoAlphaFade.Count;
            RECT rg = cv.cp[id]->AutoAlphaFade.Geometry;
            
            if(cv.cp[id]->AutoAlphaFade.Count == time)
            {
                SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
                if(cv.cp[id]->AutoAlphaFade.ShowHide)
                {
                    if(cv.cp[id]->AutoAlphaFade.SetGeometry)
                        SetWindowPos(hwnd,HWND_TOP,rg.left+r.left,rg.top+r.top,rg.right+r.right-r.left,rg.bottom+r.bottom-r.top,SWP_DRAWFRAME);
                    ShowWindow(hwnd,1);
                }
            }
            //BYTE alpha = cv.cp[id]->AutoAlphaFade.GetAlpha(t);
            float rat = t/time;
            SetLayeredWindowAttributes(hwnd, 0, AlphaMin+(255-AlphaMin)*(1.0-rat), LWA_ALPHA);
            //InvalidateRect(hwnd,0,1);

            if(cv.cp[id]->AutoAlphaFade.SetGeometry)
                SetWindowPos(hwnd,HWND_TOP,rg.left*rat+r.left,rg.top*rat+r.top,rg.right*rat+r.right-r.left,rg.bottom*rat+r.bottom-r.top,SWP_DRAWFRAME);

            if(cv.cp[id]->AutoAlphaFade.Count == 0)
            {
                cv.cp[id]->AutoAlphaFade.Activate = 0;
                if(cv.cp[id]->AutoAlphaFade.ShowHide)
                    cv.cp[id]->AutoAlphaFade.State = 0;
                if(cv.cp[id]->AutoAlphaFade.SetGeometry)
                    SetWindowPos(hwnd,HWND_TOP,r.left,r.top,r.right-r.left,r.bottom-r.top,SWP_DRAWFRAME);
                //InvalidateRect(hwnd,0,1);
            }
            cv.cp[id]->AutoAlphaFade.Count--;
        }
    }
}

void autoMoveFade(HWND hwnd, UINT msg, int id)
{

    if(msg==WM_LBUTTONDOWN)
    {
        if(cv.CURRENT_HITTEST_AREA == CSA_MOVE)
        {
            cv.cp[id]->AutoTransformFadeOut.Activate=1;
            GetCursorPos(&(cv.cp[id]->AutoTransformFadeOut.p[3]));
            cv.cp[id]->AutoTransformFadeOut.Count = cv.cp[id]->AutoTransformFadeOut.FadeOutTime+10;
            cv.cp[id]->AutoTransformFadeOut.AxDT_x = 0;
            cv.cp[id]->AutoTransformFadeOut.AxDT_y = 0;
            cv.cp[id]->AutoTransformFadeOut.p[0] = {0,0};
            cv.cp[id]->AutoTransformFadeOut.p[1] = {0,0};
            cv.cp[id]->AutoTransformFadeOut.p[2] = {0,0};
            cv.cp[id]->AutoTransformFadeOut.Count1=0;
            cv.cp[id]->AutoTransformFadeOut.Count2=0;
        }
    }

    else if(msg==WM_LBUTTONUP)
    {
        if(cv.cp[id]->AutoTransformFadeOut.Activate)
        {
            GetCursorPos(&(cv.cp[id]->AutoTransformFadeOut.p[4]));
            cv.cp[id]->AutoTransformFadeOut.Activate=0;
            cv.CNTRECT_SAVED[id] = cv.CNTRECT[id];
            cv.cp[id]->AutoTransformFadeOut.Count = 0;
        }
    }

    else if(msg == WM_TIMER)
    {
        if(cv.cp[id]->AutoTransformFadeOut.Activate)
        {
            if(cv.cp[id]->AutoTransformFadeOut.Count1%cv.cp[id]->AutoTransformFadeOut.AccelCaptureTime==0)
            {
                GetCursorPos(&(cv.cp[id]->AutoTransformFadeOut.p[cv.cp[id]->AutoTransformFadeOut.Count2]));
                cv.cp[id]->AutoTransformFadeOut.Count2++;
                if(cv.cp[id]->AutoTransformFadeOut.Count2==3)
                {
                    POINT p0 = cv.cp[id]->AutoTransformFadeOut.p[0];
                    POINT p1 = cv.cp[id]->AutoTransformFadeOut.p[1];
                    POINT p2 = cv.cp[id]->AutoTransformFadeOut.p[2];
                    cv.cp[id]->AutoTransformFadeOut.AxDT_x = fabs(float(p2.x-2*p1.x+p0.x));
                    cv.cp[id]->AutoTransformFadeOut.AxDT_y = fabs(float(p2.y-2*p1.y+p0.y));
                    cv.cp[id]->AutoTransformFadeOut.Count2=0;
                }
            }
            cv.cp[id]->AutoTransformFadeOut.Count1++;

            unsigned int Time=cv.cp[id]->AutoTransformFadeOut.FadeOutTime;
            if(cv.cp[id]->AutoTransformFadeOut.Count <= Time)
            {
                RECT rw = rectInParentRef(id);
                float t = cv.cp[id]->AutoTransformFadeOut.Count;

                int dx=cv.cp[id]->AutoTransformFadeOut.p[4].x-cv.cp[id]->AutoTransformFadeOut.p[3].x;
                int dy=cv.cp[id]->AutoTransformFadeOut.p[4].y-cv.cp[id]->AutoTransformFadeOut.p[3].y;
                if(dx==0) dx=1;
                if(dy==0) dy=1;
                int x = 5*abs(dx)*cv.cp[id]->AutoTransformFadeOut.GetX(t)/dx;
                int y = 5*abs(dy)*cv.cp[id]->AutoTransformFadeOut.GetY(t)/dy;
                //int cx = cv.cp[id]->AutoTransformFadeOut.Get(t, Time, r.right, rw.right-rw.left);
                //int cy = cv.cp[id]->AutoTransformFadeOut.Get(t, Time, r.bottom, rw.bottom-rw.top);
                int xpos = x+rw.left;
                int ypos = y+rw.top;

                if(cv.cp[id]->XMinTrackPosition && (xpos<cv.cp[id]->XMinTrackPosition))
                    xpos = cv.cp[id]->XMinTrackPosition;
                if(cv.cp[id]->XMaxTrackPosition && (xpos>cv.cp[id]->XMaxTrackPosition))
                    xpos = cv.cp[id]->XMaxTrackPosition;

                if(cv.cp[id]->YMinTrackPosition && (ypos<cv.cp[id]->YMinTrackPosition))
                    ypos = cv.cp[id]->YMinTrackPosition;
                if(cv.cp[id]->YMaxTrackPosition && (ypos>cv.cp[id]->YMaxTrackPosition))
                    ypos = cv.cp[id]->YMaxTrackPosition;

                if(cv.cp[id]->CaptionDirection==CAPTION_DIRECTION_X)
                    SetWindowPos(hwnd,HWND_TOP,xpos, cv.cp[id]->CaptionDirection_pos, 0,0, SWP_NOSIZE);
                else if(cv.cp[id]->CaptionDirection==CAPTION_DIRECTION_Y)
                    SetWindowPos(hwnd,HWND_TOP,cv.cp[id]->CaptionDirection_pos, ypos, 0,0, SWP_NOSIZE);
                else
                    SetWindowPos(hwnd,HWND_TOP,xpos, ypos, 0,0, SWP_NOSIZE);
                //SetWindowPos(hwnd,HWND_TOP,xpos, ypos, 0,0, SWP_NOSIZE);
                //std::cout<<x<<","<<y<<"\n";
                cv.cp[id]->AutoTransformFadeOut.Count++;
            }
        }
    }
}

void mouseWheel(HWND hwnd, UINT msg, WPARAM wp, int id)
{
    /*if(msg==WM_LBUTTONDBLCLK||msg==WM_LBUTTONDOWN||
            msg==WM_RBUTTONDBLCLK||msg==WM_RBUTTONDOWN)
    {
        if(cv.cp[id]->DcZoomIncrement>0.0)
        {
            if(cv.CNTOLDZOOMFACTOR[id]!=cv.DCMETRICS[id]->zoomFactor)
            {
                cv.CNTOLDZOOMFACTOR[id]=cv.DCMETRICS[id]->zoomFactor;
                //cv.CTX[id].refreshDataBase();
                SendMessage(hwnd, WM_PAINT,0,0);
            }
        }
    }
    else if(msg==WM_MOUSEMOVE)
    {
        if(cv.cp[id]->DcZoomIncrement>0.0)
        {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);
            cv.DCMETRICS[id]->center=pt;
        }
    }
    else*/ 
    if(msg==WM_MOUSEWHEEL)
    {
        int speed = 20;
        if(GET_WHEEL_DELTA_WPARAM(wp)<0)
        {   
            int idMask = cv.CTX[id].getIdMask();
            //std::cout<<idMask<<"   idmask\n";
            if(idMask)
            {
                RECT rm = cv.CNTRECT[idMask], r = cv.CNTRECT[id];
                SIZE dcsize = cv.CTX[id].getDwgSurfSize();
                POINT dcpos = cv.CTX[id].getDwgSurfPos();
                if(GetAsyncKeyState(VK_CONTROL))
                {
                    int len = r.left+dcpos.x+dcsize.cx;
                    if(len-speed/4>rm.right)
                    {
                        cv.CTX[id].setDwgSurfPos({dcpos.x-speed,dcpos.y});
                        
                    }
                    else if(dcpos.x<0)
                    {
                        cv.CTX[id].setDwgSurfPos({rm.right-dcsize.cx-r.left,dcpos.y});
                    }
                    if(cv.CTX[id].hScrollBarId)
                        SendMessage(cv.CNTLIST[cv.CTX[id].hScrollBarId],WM_TIMER,0,0);
                    if(cv.CTX[id].vScrollBarId)
                        SendMessage(cv.CNTLIST[cv.CTX[id].vScrollBarId],WM_TIMER,0,0);
                }
                else if(GetAsyncKeyState(VK_SHIFT))
                {
                    int len = r.top+dcpos.y+dcsize.cy;
                    if(len-speed/4>rm.bottom)
                    {
                        cv.CTX[id].setDwgSurfPos({dcpos.x,dcpos.y-speed});
                    }
                    else if(dcpos.y<0)
                    {
                        cv.CTX[id].setDwgSurfPos({dcpos.x,rm.bottom-dcsize.cy-r.top});
                    }
                    if(cv.CTX[id].hScrollBarId)
                        SendMessage(cv.CNTLIST[cv.CTX[id].hScrollBarId],WM_TIMER,0,0);
                    if(cv.CTX[id].vScrollBarId)
                        SendMessage(cv.CNTLIST[cv.CTX[id].vScrollBarId],WM_TIMER,0,0);
                }
                InvalidateRect(hwnd,0,1);
            }

            /*if(cv.DCMETRICS[id]->zoomFactor+cv.cp[id]->DcZoomIncrement<=2.0)
            {
                cv.DCMETRICS[id]->zoomFactor+=cv.cp[id]->DcZoomIncrement;
            }*/
        }
        else
        {
            int idMask = cv.CTX[id].getIdMask();
            if(idMask)
            {
                RECT rm = cv.CNTRECT[idMask], r = cv.CNTRECT[id];
                SIZE dcsize = cv.CTX[id].getDwgSurfSize();
                POINT dcpos = cv.CTX[id].getDwgSurfPos();
                if(GetAsyncKeyState(VK_CONTROL))
                {
                    int len = r.left+dcpos.x;
                    if(len+speed<std::max(r.left,rm.left))
                    {
                        cv.CTX[id].setDwgSurfPos({dcpos.x+speed,dcpos.y});
                    }
                    else
                    {
                        cv.CTX[id].setDwgSurfPos({0,dcpos.y});
                    }
                }
                else if(GetAsyncKeyState(VK_SHIFT))
                {
                    int len = r.top+dcpos.y;
                    if(len+speed<std::max(r.top,rm.top))
                    {
                        cv.CTX[id].setDwgSurfPos({dcpos.x,dcpos.y+speed});
                    }
                    else
                    {
                        cv.CTX[id].setDwgSurfPos({dcpos.x,0});
                    }
                }
                InvalidateRect(hwnd,0,1);
            }
            /*if(cv.DCMETRICS[id]->zoomFactor-cv.cp[id]->DcZoomIncrement>0.0)
                cv.DCMETRICS[id]->zoomFactor-=cv.cp[id]->DcZoomIncrement;*/
        }
    }
}

void linkGeometry(HWND hwnd, UINT msg, int id)
{
    //int this_id=0;
    if (msg == WM_NCLBUTTONDOWN||msg == WM_LBUTTONDOWN)
    {
        cv.LOCKLINK[ID_GEOMETRY] = 0;//*****************************************attention, cas id=0
        cv.LOCKLINK[id] = 1;
        csLIST<int> lst = cv.IDCNTLEFTLINK[id];
        int n = lst.size();
        GetWindowRect(hwnd, &cv.CNTRECT_SAVED[id]);
        std::cout<<"old hwnd id : "<<ID_GEOMETRY<<"\n";
        std::cout<<"new hwnd id : "<<id<<"\n";

        for (int i = 0; i<n; i++)
        {
            //GetWindowRect(cv.CNTLIST[lst[i]], &cv.CNTRECT_SAVED[lst[i]]);
            cv.LEFTLINKSIGNAL[lst[i]] = 1;
        }

        lst = cv.IDCNTTOPLINK[id];
        n = lst.size();
        for (int i = 0; i<n; i++)
        {
            //GetWindowRect(cv.CNTLIST[lst[i]], &cv.CNTRECT_SAVED[lst[i]]);// defaultCont.cpp
            cv.TOPLINKSIGNAL[lst[i]] = 1;
        }

        lst = cv.IDCNTRIGHTLINK[id];
        n = lst.size();
        for (int i = 0; i<n; i++)
        {
            //GetWindowRect(cv.CNTLIST[lst[i]], &cv.CNTRECT_SAVED[lst[i]]);
            cv.RIGHTLINKSIGNAL[lst[i]] = 1;
        }

        lst = cv.IDCNTBOTTOMLINK[id];
        n = lst.size();
        for (int i = 0; i<n; i++)
        {
            //GetWindowRect(cv.CNTLIST[lst[i]], &cv.CNTRECT_SAVED[lst[i]]);
            cv.BOTTOMLINKSIGNAL[lst[i]] = 1;
        }

        ID_GEOMETRY = id;
    }
    if (msg==WM_SIZE || msg==WM_MOVE)
    {
        //int id = cv.getContId2(hwnd);
        csLIST<int> lst = cv.IDCNTLEFTLINK[id];
        int n = lst.size();
        //std::cout<<id<<"  n = "<<n<<"\n";
        for (int i = 0; i<n; i++)
        {
            if(cv.LOCKLINK[lst[i]]==0)//eviter les boucle infinie, en cas de liaison reciproque
                cv.LEFTLINKSIGNAL[lst[i]] = 1;
        }

        lst = cv.IDCNTTOPLINK[id];
        n = lst.size();
        for (int i = 0; i<n; i++)
        {
            if(cv.LOCKLINK[lst[i]]==0)
                cv.TOPLINKSIGNAL[lst[i]] = 1;
        }

        lst = cv.IDCNTRIGHTLINK[id];
        n = lst.size();
        for (int i = 0; i<n; i++)
        {
            if(cv.LOCKLINK[lst[i]]==0)
                cv.RIGHTLINKSIGNAL[lst[i]] = 1;
        }

        lst = cv.IDCNTBOTTOMLINK[id];
        n = lst.size();
        for (int i = 0; i<n; i++)
        {
            if(cv.LOCKLINK[lst[i]]==0)
                cv.BOTTOMLINKSIGNAL[lst[i]] = 1;
        }
    }

    if (msg == WM_TIMER)
    {
        //int id = cv.getContId2(hwnd);
        csHWND_GEOMETRY_LINK GeometryLink = cv.cp[id]->GeometryLink;
        int idp = cv.CNTPARID[id];
        RECT rwp = cv.CNTRECT[idp];
        RECT rwp_s = cv.CNTRECT_SAVED[idp];
        RECT rhwnd_s = cv.CNTRECT_SAVED[id];
        if(cv.cp[id]->ClingToParent)
        {
            rhwnd_s.left -= rwp_s.left;
            rhwnd_s.right -= rwp_s.left;
            rhwnd_s.top -= rwp_s.top;//interressant avec rwp
            rhwnd_s.bottom -= rwp_s.top;//interressant avec rwp
        }
        if(GeometryLink.LeftLinkEvent_target != 0 && cv.LEFTLINKSIGNAL[id])//attention...
        {
            cv.LEFTLINKSIGNAL[id] = 0;
            int idl = GeometryLink.idhwndLeft;
            HWND hlinkLeft = cv.CNTLIST[idl];
            RECT rhwndleft_s = cv.CNTRECT_SAVED[idl];
            RECT rhwndleft = cv.CNTRECT[idl];

            int dx = rhwnd_s.left;

            if(GeometryLink.LeftLinkEvent_target == GLINK_POSITION)
            {
                if(GeometryLink.LeftLinkEvent_source == GLINK_POSITION
                        && rhwndleft.left != rhwndleft_s.left)
                {
                    dx += (rhwndleft.left-rhwndleft_s.left)*GeometryLink.LeftLinkEvent_coef;
                    //std::cout<<rhwnd_s.top<<"\n";
                    MoveWindow(hwnd,dx, rhwnd_s.top, rhwnd_s.right-rhwnd_s.left, rhwnd_s.bottom-rhwnd_s.top, 1);
                }
                else if(GeometryLink.LeftLinkEvent_source == GLINK_SIZE
                        && rhwndleft.right != rhwndleft_s.right)
                {
                    dx += (rhwndleft.right-rhwndleft.left-rhwndleft_s.right+rhwndleft_s.left)
                          *GeometryLink.LeftLinkEvent_coef;
                    MoveWindow(hwnd,dx, rhwnd_s.top, rhwnd_s.right-rhwnd_s.left, rhwnd_s.bottom-rhwnd_s.top, 1);
                }

            }
            else if(GeometryLink.LeftLinkEvent_target == GLINK_SIZE)
            {
                if(GeometryLink.LeftLinkEvent_source == GLINK_POSITION
                        && rhwndleft.left != rhwndleft_s.left)
                {
                    dx = (rhwndleft.left-rhwndleft_s.left)*GeometryLink.LeftLinkEvent_coef;
                    MoveWindow(hwnd,rhwnd_s.left+dx, rhwnd_s.top, rhwnd_s.right-rhwnd_s.left - dx, rhwnd_s.bottom-rhwnd_s.top, 1);
                }

                else if(GeometryLink.LeftLinkEvent_source == GLINK_SIZE
                        && rhwndleft.right != rhwndleft_s.right)
                {
                    dx = (rhwndleft.right-rhwndleft.left-rhwndleft_s.right+rhwndleft_s.left)
                         *GeometryLink.LeftLinkEvent_coef;
                    MoveWindow(hwnd,rhwnd_s.left-dx, rhwnd_s.top, rhwnd_s.right-rhwnd_s.left + dx,
                               rhwnd_s.bottom-rhwnd_s.top, 1);
                }
            }
        }
        if(GeometryLink.TopLinkEvent_target != 0 && cv.TOPLINKSIGNAL[id])
        {
            cv.TOPLINKSIGNAL[id] = 0;
            int idt = GeometryLink.idhwndTop;
            HWND hlinkTop = cv.CNTLIST[idt];
            RECT rhwndtop_s = cv.CNTRECT_SAVED[idt];
            RECT rhwndtop = cv.CNTRECT[idt];
            int dy = rhwnd_s.top;

            if(GeometryLink.TopLinkEvent_target == GLINK_POSITION)
            {
                if(GeometryLink.TopLinkEvent_source == GLINK_POSITION
                        && rhwndtop.top != rhwndtop_s.top)
                {
                    dy += (rhwndtop.top-rhwndtop_s.top)*GeometryLink.TopLinkEvent_coef;
                    //std::cout<<rhwnd_s.top<<"\n";
                    MoveWindow(hwnd,rhwnd_s.left,dy, rhwnd_s.right-rhwnd_s.left, rhwnd_s.bottom-rhwnd_s.top, 1);
                }
                else if(GeometryLink.TopLinkEvent_source == GLINK_SIZE
                        && rhwndtop.bottom != rhwndtop_s.bottom)
                {
                    dy += (rhwndtop.bottom-rhwndtop.top-rhwndtop_s.bottom+rhwndtop_s.top)
                          *GeometryLink.TopLinkEvent_coef;
                    MoveWindow(hwnd,rhwnd_s.left, dy, rhwnd_s.right-rhwnd_s.left, rhwnd_s.bottom-rhwnd_s.top, 1);
                }

            }
            else if(GeometryLink.TopLinkEvent_target == GLINK_SIZE)
            {
                if(GeometryLink.TopLinkEvent_source == GLINK_POSITION
                        && rhwndtop.top != rhwndtop_s.top)
                {
                    dy = (rhwndtop.top-rhwndtop_s.top)*GeometryLink.TopLinkEvent_coef;
                    MoveWindow(hwnd,rhwnd_s.left, rhwnd_s.top+dy, rhwnd_s.right-rhwnd_s.left, rhwnd_s.bottom-rhwnd_s.top-dy, 1);
                }

                else if(GeometryLink.TopLinkEvent_source == GLINK_SIZE
                        && rhwndtop.bottom != rhwndtop_s.bottom)
                {
                    dy = (rhwndtop.bottom-rhwndtop.top-rhwndtop_s.bottom+rhwndtop_s.top)
                         *GeometryLink.TopLinkEvent_coef;
                    MoveWindow(hwnd,rhwnd_s.left, rhwnd_s.top-dy, rhwnd_s.right-rhwnd_s.left,
                               rhwnd_s.bottom-rhwnd_s.top+dy, 1);
                }
            }
        }
        if(GeometryLink.RightLinkEvent_target != 0 && cv.RIGHTLINKSIGNAL[id])//attention...
        {
            cv.RIGHTLINKSIGNAL[id] = 0;
            int idr = GeometryLink.idhwndRight;
            HWND hlinkRight = cv.CNTLIST[idr];
            RECT rhwndright_s = cv.CNTRECT_SAVED[idr];
            RECT rhwndright = cv.CNTRECT[idr];

            int dx = rhwnd_s.left;

            if(GeometryLink.RightLinkEvent_target == GLINK_POSITION)
            {
                if(GeometryLink.RightLinkEvent_source == GLINK_POSITION
                        && rhwndright.left != rhwndright_s.left)
                {
                    dx += (rhwndright.left-rhwndright_s.left)*GeometryLink.RightLinkEvent_coef;
                    //std::cout<<rhwnd_s.top<<"\n";
                    MoveWindow(hwnd,dx, rhwnd_s.top, rhwnd_s.right-rhwnd_s.left+dx, rhwnd_s.bottom-rhwnd_s.top, 1);
                }
                else if(GeometryLink.RightLinkEvent_source == GLINK_SIZE
                        && rhwndright.right != rhwndright_s.right)
                {
                    dx += (rhwndright.right-rhwndright.left-rhwndright_s.right+rhwndright_s.left)
                          *GeometryLink.RightLinkEvent_coef;
                    MoveWindow(hwnd,dx, rhwnd_s.top, rhwnd_s.right-rhwnd_s.left, rhwnd_s.bottom-rhwnd_s.top, 1);
                }

            }
            else if(GeometryLink.RightLinkEvent_target == GLINK_SIZE)
            {
                if(GeometryLink.RightLinkEvent_source == GLINK_POSITION
                        && rhwndright.left != rhwndright_s.left)
                {
                    dx = (rhwndright.left-rhwndright_s.left)*GeometryLink.RightLinkEvent_coef;
                    MoveWindow(hwnd,rhwnd_s.left, rhwnd_s.top, rhwnd_s.right-rhwnd_s.left - dx, rhwnd_s.bottom-rhwnd_s.top, 1);
                }

                else if(GeometryLink.RightLinkEvent_source == GLINK_SIZE
                        && rhwndright.right != rhwndright_s.right)
                {
                    dx = (rhwndright.right-rhwndright.left-rhwndright_s.right+rhwndright_s.left)
                         *GeometryLink.RightLinkEvent_coef;
                    MoveWindow(hwnd,rhwnd_s.left, rhwnd_s.top, rhwnd_s.right-rhwnd_s.left + dx,
                               rhwnd_s.bottom-rhwnd_s.top, 1);
                }
            }
        }
        if(GeometryLink.BottomLinkEvent_target != 0 && cv.BOTTOMLINKSIGNAL[id])
        {
            cv.BOTTOMLINKSIGNAL[id] = 0;
            int idb = GeometryLink.idhwndBottom;
            HWND hlinkBottom = cv.CNTLIST[idb];
            RECT rhwndbottom_s = cv.CNTRECT_SAVED[idb];
            RECT rhwndbottom = cv.CNTRECT[idb];
            int dy = rhwnd_s.top;

            if(GeometryLink.BottomLinkEvent_target == GLINK_POSITION)
            {
                if(GeometryLink.BottomLinkEvent_source == GLINK_POSITION
                        && rhwndbottom.top != rhwndbottom_s.top)
                {
                    dy += (rhwndbottom.top-rhwndbottom_s.top)*GeometryLink.BottomLinkEvent_coef;
                    //std::cout<<rhwnd_s.top<<"\n";
                    MoveWindow(hwnd,rhwnd_s.left,dy, rhwnd_s.right-rhwnd_s.left, rhwnd_s.bottom-rhwnd_s.top+dy, 1);
                }
                else if(GeometryLink.BottomLinkEvent_source == GLINK_SIZE
                        && rhwndbottom.bottom != rhwndbottom_s.bottom)
                {
                    dy += (rhwndbottom.bottom-rhwndbottom.top-rhwndbottom_s.bottom+rhwndbottom_s.top)
                          *GeometryLink.BottomLinkEvent_coef;
                    MoveWindow(hwnd,rhwnd_s.left, dy, rhwnd_s.right-rhwnd_s.left, rhwnd_s.bottom-rhwnd_s.top, 1);
                }

            }
            else if(GeometryLink.BottomLinkEvent_target == GLINK_SIZE)
            {
                if(GeometryLink.BottomLinkEvent_source == GLINK_POSITION
                        && rhwndbottom.top != rhwndbottom_s.top)
                {
                    dy = (rhwndbottom.top-rhwndbottom_s.top)*GeometryLink.BottomLinkEvent_coef;
                    MoveWindow(hwnd,rhwnd_s.left, rhwnd_s.top, rhwnd_s.right-rhwnd_s.left, rhwnd_s.bottom-rhwnd_s.top-dy, 1);
                }

                else if(GeometryLink.BottomLinkEvent_source == GLINK_SIZE
                        && rhwndbottom.bottom != rhwndbottom_s.bottom)
                {
                    dy = (rhwndbottom.bottom-rhwndbottom.top-rhwndbottom_s.bottom+rhwndbottom_s.top)
                         *GeometryLink.BottomLinkEvent_coef;
                    MoveWindow(hwnd,rhwnd_s.left, rhwnd_s.top, rhwnd_s.right-rhwnd_s.left,
                               rhwnd_s.bottom-rhwnd_s.top+dy, 1);
                }
            }
        }

    }
}

void cntTimerEventFunction(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, int id)
{
    static int pid=0;
    if(msg==WM_TIMER && cv.CNTRECT[0].right)
    {
        int n = cv.cp[id]->CntEventsFunc.TIMER.size();
        pid = id;
        if(cv.TIMEREVENTFUNCCOUNT[id]<n)
        {
            int i = cv.TIMEREVENTFUNCCOUNT[id];
            cv.cp[id]->CntEventsFunc.TIMER_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.TIMER[i]))( cv.cp[id]->CntEventsFunc.TIMER_ARGS[i] );
        }
        else
            cv.TIMEREVENTFUNCCOUNT[id]=-1;

        cv.TIMEREVENTFUNCCOUNT[id]++;
    }
}

LRESULT nchittestEventFunction(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, int id)
{
    static int pid=0;
    static int lr = (LRESULT)HTCLIENT;
    if(msg==WM_NCHITTEST)
    {
        int n = cv.cp[id]->CntEventsFunc.NCHITTEST.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.NCHITTEST_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.NCHITTEST[i]))( cv.cp[id]->CntEventsFunc.NCHITTEST_ARGS[i] );
            if(cv.cp[id]->CntEventsFunc.NCHITTEST_ARGS[i].getArgNumber()>5)
            {
                //cv.Lresult = *(LRESULT*)cv.cp[id]->CntEventsFunc.NCHITTEST_ARGS[i][5];
            }
        }
    }
}

void cntEventsFunction(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, int id)
{
    static int pid=0;
    if(msg==WM_LBUTTONUP)
    {
        int n = cv.cp[id]->CntEventsFunc.LBUTTONUP.size();
        RECT r = cv.CNTRECT[id];
        //GetWindowRect(hwnd,&r);
        POINT p;
        GetCursorPos(&p);
        pid = id;
        if(PtInRect(&r,p))
        {
            for(int i=0; i<n; i++)
            {
                cv.cp[id]->CntEventsFunc.LBUTTONUP_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam, &pid);
                (*(cv.cp[id]->CntEventsFunc.LBUTTONUP[i]))( cv.cp[id]->CntEventsFunc.LBUTTONUP_ARGS[i] );
            }
        }
    }
    else if(msg==WM_RBUTTONUP)
    {
        int n = cv.cp[id]->CntEventsFunc.RBUTTONUP.size();
        RECT r = cv.CNTRECT[id];
        POINT p;
        GetCursorPos(&p);
        pid = id;
        if(PtInRect(&r,p))
        {
            for(int i=0; i<n; i++)
            {
                cv.cp[id]->CntEventsFunc.RBUTTONUP_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
                (*(cv.cp[id]->CntEventsFunc.RBUTTONUP[i]))( cv.cp[id]->CntEventsFunc.RBUTTONUP_ARGS[i] );
            }
        }
    }
    else if(msg==WM_MBUTTONUP)
    {
        int n = cv.cp[id]->CntEventsFunc.MBUTTONUP.size();
        RECT r = cv.CNTRECT[id];
        POINT p;
        GetCursorPos(&p);
        pid = id;
        if(PtInRect(&r,p))
        {
            for(int i=0; i<n; i++)
            {
                cv.cp[id]->CntEventsFunc.MBUTTONUP_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
                (*(cv.cp[id]->CntEventsFunc.MBUTTONUP[i]))( cv.cp[id]->CntEventsFunc.MBUTTONUP_ARGS[i] );
            }
        }
    }
    else if(msg==WM_LBUTTONDOWN)
    {
        int n = cv.cp[id]->CntEventsFunc.LBUTTONDOWN.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.LBUTTONDOWN_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.LBUTTONDOWN[i]))( cv.cp[id]->CntEventsFunc.LBUTTONDOWN_ARGS[i] );
        }
    }
    else if(msg==WM_NCLBUTTONDOWN)
    {std::cout<<"WM_NCLBUTTONDOWN, id : "<<id<<"\n";
        int n = cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN[i]))( cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN_ARGS[i] );
        }
    }
    else if(msg==WM_RBUTTONDOWN)
    {
        int n = cv.cp[id]->CntEventsFunc.RBUTTONDOWN.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.RBUTTONDOWN_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.RBUTTONDOWN[i]))( cv.cp[id]->CntEventsFunc.RBUTTONDOWN_ARGS[i] );
        }
    }
    else if(msg==WM_NCRBUTTONDOWN)
    {
        int n = cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN[i]))( cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN_ARGS[i] );
        }
    }
    else if(msg==WM_MBUTTONDOWN)
    {
        int n = cv.cp[id]->CntEventsFunc.MBUTTONDOWN.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.MBUTTONDOWN_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.MBUTTONDOWN[i]))( cv.cp[id]->CntEventsFunc.MBUTTONDOWN_ARGS[i] );
        }
    }
    else if(msg==WM_LBUTTONDBLCLK)
    {
        int n = cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK[i]))( cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK_ARGS[i] );
        }
    }
    else if(msg==WM_RBUTTONDBLCLK)
    {
        int n = cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK[i]))( cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK_ARGS[i] );
        }
    }
    else if(msg==WM_MBUTTONDBLCLK)
    {
        int n = cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK[i]))( cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK_ARGS[i] );
        }
    }

    else if(msg==WM_MOUSEMOVE)
    {
        int n = cv.cp[id]->CntEventsFunc.MOUSEMOVE.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.MOUSEMOVE_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.MOUSEMOVE[i]))( cv.cp[id]->CntEventsFunc.MOUSEMOVE_ARGS[i] );
        }
    }
    else if(msg==WM_MOUSEHOVER)
    {
        int n = cv.cp[id]->CntEventsFunc.MOUSEHOVER.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.MOUSEHOVER_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.MOUSEHOVER[i]))( cv.cp[id]->CntEventsFunc.MOUSEHOVER_ARGS[i] );
        }
    }
    else if(msg==WM_MOUSELEAVE)
    {
        int n = cv.cp[id]->CntEventsFunc.MOUSELEAVE.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.MOUSELEAVE_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.MOUSELEAVE[i]))( cv.cp[id]->CntEventsFunc.MOUSELEAVE_ARGS[i] );
        }
    }
    else if(msg==WM_MOUSEWHEEL)
    {
        int n = cv.cp[id]->CntEventsFunc.MOUSEWHEEL.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.MOUSEWHEEL_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.MOUSEWHEEL[i]))( cv.cp[id]->CntEventsFunc.MOUSEWHEEL_ARGS[i] );
        }
    }
    else if(msg==WM_SIZE)
    {
        int n = cv.cp[id]->CntEventsFunc.SIZE.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.SIZE_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.SIZE[i]))( cv.cp[id]->CntEventsFunc.SIZE_ARGS[i] );
        }
    }
    else if(msg==WM_MOVE)
    {
        int n = cv.cp[id]->CntEventsFunc.MOVE.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.MOVE_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.MOVE[i]))( cv.cp[id]->CntEventsFunc.MOVE_ARGS[i] );
        }
    }
    else if(msg==WM_DESTROY)
    {
        int n = cv.cp[id]->CntEventsFunc.DESTROY.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.DESTROY_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.DESTROY[i]))( cv.cp[id]->CntEventsFunc.DESTROY_ARGS[i] );
        }
    }
    else if(msg==WM_ERASEBKGND)
    {
        int n = cv.cp[id]->CntEventsFunc.ERASEBKGND.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.ERASEBKGND_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.ERASEBKGND[i]))( cv.cp[id]->CntEventsFunc.ERASEBKGND_ARGS[i] );
        }
    }
    else if(msg==WM_KEYUP)
    {
        pid = id; 
        int n = cv.cp[pid]->CntEventsFunc.KEYUP.size();
        std::cout<<"Keyup id : "<<id<<"\n";
        for(int i=0; i<n; i++)
        {
            cv.cp[pid]->CntEventsFunc.KEYUP_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[pid]->CntEventsFunc.KEYUP[i]))( cv.cp[pid]->CntEventsFunc.KEYUP_ARGS[i] );
        }
        
    }
    else if(msg==WM_KEYDOWN)
    {
        int n = cv.cp[id]->CntEventsFunc.KEYDOWN.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.KEYDOWN_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.KEYDOWN[i]))( cv.cp[id]->CntEventsFunc.KEYDOWN_ARGS[i] );
        }
    }
    else if(msg==WM_SYSCOMMAND)
    {
        int n = cv.cp[id]->CntEventsFunc.SYSCOMMAND.size();
        pid = id;
        for(int i=0; i<n; i++)
        {
            cv.cp[id]->CntEventsFunc.SYSCOMMAND_ARGS[i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (*(cv.cp[id]->CntEventsFunc.SYSCOMMAND[i]))( cv.cp[id]->CntEventsFunc.SYSCOMMAND_ARGS[i] );
        }
    }

    if(msg == WM_TIMER || msg == WM_MOUSEMOVE || msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || 
        msg == WM_LBUTTONDBLCLK || msg == WM_RBUTTONDBLCLK || msg == WM_LBUTTONUP ||
        msg == WM_NCLBUTTONDOWN || msg == WM_NCRBUTTONDOWN || 
        msg == WM_NCLBUTTONUP || msg == WM_NCRBUTTONUP || 
        msg == WM_MOUSELEAVE || msg == WM_MOUSEHOVER || 
        msg == WM_KEYUP || msg == WM_KEYDOWN || msg == WM_CHAR || msg == WM_SIZE)
    {
        pid = id;
        int n = cv.GROUPED_EVENTS_ARGS[id].size();
        for(int i=0; i<n; i++)
        {
            cv.GROUPED_EVENTS_ARGS[id][i].setProcParams(&hwnd,&msg,&wParam,&lParam,&pid);
            (cv.GROUPED_EVENTS_FUNC[id][i])(cv.GROUPED_EVENTS_ARGS[id][i]);
        }
    }
}


void eraseBKG(HWND hwnd, UINT msg, int id)
{
    if (msg == WM_ERASEBKGND)
    {   
        if(cv.cp[id]->SameBackgroundCnt != -1)
        {
            HDC dc = GetDC(hwnd);
            int id1 = cv.cp[id]->SameBackgroundCnt;
            cv.CTX[id].updateSurface_copy(hwnd,dc, cv.cp[id1]->DCSizes, cv.CTX[id1].getGDC(), cv.cp[id]->Title);
            ReleaseDC(hwnd, dc);
        }
        else
        {
            cv.CTX[id].drawSurfaceBKG();
            cv.CTX[id].updateSurface(hwnd,cv.cp[id]->Title);
        }
        /****************************************************************/
        if(cv.cp[id]->MouseLeaveRemoveBkg)
        {
            unsigned int GradientNumber=cv.cp[id]->MHGradient.GradientNumber;
            unsigned int TimeStep=cv.cp[id]->MHGradient.TimeStep;
            unsigned int mx = GradientNumber*TimeStep;
            if(!cv.MOUSEHOVERSIGNAL[id] &&
                    cv.MOUSELEAVECOUNT[id]>=mx)
            {
                csRGBA col=cv.cp[id]->BackgroundColor;
                SetLayeredWindowAttributes(hwnd, RGB(col.r,col.g,col.b), 0, LWA_COLORKEY);
            }
        }
        /****************************************************************/
    }
}
