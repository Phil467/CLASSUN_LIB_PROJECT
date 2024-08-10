#include "DefaultCont.h"
#include "csCONTAINER.h"

extern csCNTR_VARS cv;
MSG Messages, pmsg;
BOOL SCROLL_SIGNAL=0, SCROLL_SIGNAL_2=0;
HWND TRACKED_HWND;
/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the Messages */
    {
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for Messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

HWND csf_createFrame(HWND& hpar, int id, RECT r, csRGBA bkg, bool  show, WNDPROC proc)
{
    HINSTANCE hThisInstance=(HINSTANCE)GetWindowLongPtr(hpar, GWLP_HINSTANCE);
    HWND hwnd;               /* This is the handle for our window */
    WNDCLASSEX wincl;        /* Data structure for the windowclassNameclass */

    char* className=csf_alloc<char>(15);
    sprintf(className, "frame_%d%", id);
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = className;
    wincl.lpfnWndProc = proc;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground =CreateSolidBrush(RGB(bkg.r, bkg.g, bkg.b));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
    {
        return 0;
    }

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0 /*WS_EX_LAYERED*/,                   /* Extended possibilites for variation */
               className,         /* Classname */
               "",       /* Title Text */
               WS_POPUP|WS_CHILD, /* default window */
               r.left,       /* Windows decides the position */
               r.top,       /* where the window ends up on the screen */
               r.right,                 /* The programs width */
               r.bottom,                 /* and height in pixels */
               hpar,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );
    ShowWindow(hwnd, show);
    return hwnd;
}

int csf_close()
{
    RECT r=cv.cp[0]->Geometry;
    MoveWindow(cv.CNTLIST[0], r.left+1, r.top+1, r.right-1, r.bottom-1, 1);
    MoveWindow(cv.CNTLIST[0], r.left, r.top, r.right, r.bottom, 1);
    for(int i=0; i<cv.CNTLIST.size(); i++)
        ShowWindow(cv.CNTLIST[i], cv.cp[i]->Show);
    /* Run the message loop. It will run until GetMessage() returns 0 */

    HHOOK setHook();
    HHOOK mhook = setHook();

    while (GetMessage (&Messages, NULL, 0, 0))
    {
        /* Translate virtual-key Messages into character Messages */
        TranslateMessage(&Messages);
        if(Messages.message==WM_LBUTTONDOWN||Messages.message==WM_NCLBUTTONDOWN||
                Messages.message==WM_LBUTTONDBLCLK||Messages.message==WM_NCLBUTTONDBLCLK)
        {
            TRACKED_HWND=Messages.hwnd;
            if(cv.CURRENT_HITTEST_AREA != 0)
            for (int i=0; i<cv.CNTLIST.size(); i++)
            {
                GetWindowRect(cv.CNTLIST[i], &cv.CNTRECT_SAVED[i]);
                //GetClientRect(cv.CNTLIST[i], &cv.CNTCLWRECT[i]);
                GetClientRect(cv.CNTLIST[i], &cv.CNTCLWRECT_SAVED[i]);
            }
            GetCursorPos(&cv.TRACKING_POINT);
        }
        if(Messages.message==WM_MOUSEMOVE||Messages.message==WM_NCMOUSEMOVE)
        {
            if(Messages.wParam==MK_LBUTTON)
            {
                SCROLL_SIGNAL=1;
                SCROLL_SIGNAL_2=1;
                GetCursorPos(&cv.TRACKING_POINT2);
            }
            else
                SCROLL_SIGNAL_2=0;
            
        }
        if(Messages.message==WM_TIMER && cv.CNTRECT[0].right)
        {
            GetCursorPos(&cv.TIMER_POINT);
            //cv.TIMER_HWND_ID = cv.getContId2(Messages.hwnd);
        }
        if(Messages.message==WM_LBUTTONDOWN)
            cv.LBTN_CONTROL = 1;
        if(Messages.message==WM_LBUTTONUP)
            {
                cv.LBTN_CONTROL = 0;
            }
        if(Messages.message==WM_NCLBUTTONDOWN)
            {cv.NCLBTN_CONTROL = 1;std::cout<<"nc down\n";}
        if(Messages.message==WM_MOUSEMOVE || Messages.message==WM_NCMOUSEMOVE)
            {cv.NCLBTN_CONTROL = 0;}
        /* Send message to WindowProcedure */
        DispatchMessage(&Messages);
    }

    UnhookWindowsHookEx(mhook);
    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return Messages.wParam;
}


int hauteurBarreDeTache()
{
    HWND tTrayHwnd = FindWindow("Shell_TrayWnd", NULL);
    RECT tTrayRect;

    GetWindowRect(tTrayHwnd, &tTrayRect);
    return int(tTrayRect.bottom-tTrayRect.top);
}


void initLists(int n)
{
    cv.CNTLIST.init(n);
    cv.CNTPARLIST.init(n);
    cv.CNTRECT.init(n);
    cv.CNTRECT_SAVED.init(n);
    cv.CNTCLRECT.init(n);
    cv.CNTCLWRECT.init(n);
    cv.CNTCLWRECT_SAVED.init(n);
    cv.CTX.init(n);
    cv.CNTDC.init(n);
    cv.lkt.init(n);
    cv.CNTPARID.init(n);
    cv.CNTOLDZOOMFACTOR.init(n);

    cv.LOCKLINK.init(n);
    cv.LEFTLINKSIGNAL.init(n);
    cv.TOPLINKSIGNAL.init(n);
    cv.RIGHTLINKSIGNAL.init(n);
    cv.BOTTOMLINKSIGNAL.init(n);
    cv.SHOWWINDOWSIGNAL.init(n);
    cv.HIDEWINDOWSIGNAL.init(n);
    cv.MOUSEHOVERSIGNAL.init(n);
    cv.MOUSEHOVERCOUNT.init(n);
    cv.CLICKGRADIENTCOUNT.init(n);
    cv.AUTOTRANSCOUNT.init(n);
    cv.TIMEREVENTFUNCCOUNT.init(n);
    cv.CATCHLASTGEOMETRY.init(n);
    cv.CATCHLASTPARENT.init(n);
    cv.CNTCREATION.init(n);
    cv.CNTBORDERCLICKED.init(n);
    cv.CNTHITALLOW.init(n);
    cv.DCLOCK.init(n);
    cv.ClassName.init(n);
}


LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode>=0)
    {
        if(wParam == WM_RBUTTONDOWN)
        {
            POINT p={0,0};
            GetCursorPos(&p);
            std::cout<<"Point : {"<<p.x<<","<<p.y<<"}"<<std::endl;
        }
        if(wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN)
        {
            //GetCursorPos(&cv.PHOOK_LBTNDOWN);
            cv.BHOOK_LBUTNDOWN_POPUP = 1;
        }
    }
    return CallNextHookEx(0,nCode,wParam,lParam);
}

HHOOK setHook()
{
    LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
    HHOOK mhook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, 0, 0);
    return mhook;
}