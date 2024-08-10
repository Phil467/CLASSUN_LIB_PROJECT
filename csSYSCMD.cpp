#include "csSYSCMD.h"

extern csCNTR_PARAMS cscp;
extern csCNTR_VARS cv;

csSYSCMD::csSYSCMD()
{
    //ctor
}

csSYSCMD::~csSYSCMD()
{
    //dtor
}


void showHideCnt(csARGS Args)
{
    int id = *((int*)Args[0]);
    cv.cp[id]->AutoAlphaFade.Activate=1;
    //std::cout<<(char*)Args[1];
}

void cntshow(csARGS Args)
{
    int id = int(Args);
    static int count = 0;
    static int a = 0;
    static RECT r = cv.CNTRECT[id];
    static int mx = 20;
    static int mn = 10;
    if(count > mn && count <= mx)
    {
        a+=22;
        SetLayeredWindowAttributes(HWND(Args), 0, a-1, LWA_ALPHA);
        SetWindowPos(HWND(Args),0,r.left, r.top-a/8, 0,0,SWP_NOSIZE);
        count++;
    }
    else if (count == mx+1)
    {
        SetLayeredWindowAttributes(HWND(Args), 0, 255, LWA_ALPHA);
    }
    else if (count > mx)
    {

    }
    else
    {
        count++;
        //std::cout<<count<<"\n";
    }
}

/*************************************************************/
void holdingLbtn(csARGS Args)
{
    if(GetAsyncKeyState(VK_LBUTTON)<0 && cv.HWNDCAPTURE==(HWND)Args)
        std::cout<< "holding left mouse button\n";
}
/*************************************************************/
void closeCnt(csARGS Args)
{
    int id = *(int*)Args[0];
    HWND hwnd = cv.CNTLIST[id];
    SendMessage(hwnd, WM_DESTROY, 0, 0);
}
/*----------------------------------------------------*/
void minimizeCntInit(csARGS Args)
{
    int id = *(int*)Args[0];
    GetWindowRect(cv.CNTLIST[id], &cv.CNTRECT[id]);
    GetWindowRect(cv.CNTLIST[id], &cv.CNTRECT_SAVED[id]);
    cv.cp[id]->AutoAlphaFade.SetGeometry = 1;
    cv.cp[id]->AutoAlphaFade.Geometry = {0,200,0,0};
    cv.cp[id]->AutoAlphaFade.FadeTime = 8;
    cv.cp[id]->AutoAlphaFade.AlphaMin = 0;
    cv.cp[id]->AutoAlphaFade.State = 0;
    cv.cp[id]->AutoAlphaFade.Count = 0;
    cv.cp[id]->AutoAlphaFade.Activate = 1;

    *(int*)Args[1] = cv.cp[id]->AutoAlphaFade.FadeTime;
}

void minimizeCntEnd(csARGS Args)
{
    int id = *(int*)Args[0];
    int* delay = (int*)Args[1];

    if(*delay > 0)
    {
        if(*delay == 1)
        {
            ShowWindow(cv.CNTLIST[id],SW_MINIMIZE);
            SetLayeredWindowAttributes(cv.CNTLIST[id], 0, (100-cv.cp[id]->Transparency)*255/100, LWA_ALPHA);
            cv.cp[id]->AutoAlphaFade.SetGeometry = 0;
            cv.cp[id]->AutoAlphaFade.Geometry = {0,0,0,0};
            cv.cp[id]->AutoAlphaFade.AlphaMin = 20; // reinitialize to the value used to repos the cnt
            cv.cp[id]->AutoAlphaFade.State = 0;
            cv.cp[id]->AutoAlphaFade.Count = 0;
            cv.cp[id]->AutoAlphaFade.Activate = 0;
        }
        (*delay)--;
    }

}

void minimizeCnt(int idmin, int& client)
{
    int*delay = csf_alloc2<int>(1,0);
    csARGS args(2);
    args.makeArgs(&client, delay);
    csSetAction(idmin, WM_LBUTTONUP, minimizeCntInit, args);
    csSetAction(idmin, WM_TIMER, minimizeCntEnd, args);
}

void restoreCntInit(csARGS Args)
{
    int id = int(Args);
    //if(WPARAM(Args) == SC_RESTORE)
    {
        std::cout<<"jhkj\n";
        /*cv.cp[id]->AutoAlphaFade.State = 1;
        cv.cp[id]->AutoAlphaFade.Count = cv.cp[id]->AutoAlphaFade.FadeTime;
        cv.cp[id]->AutoAlphaFade.Activate = 1;*/
        //cv.CTX[id].autoUpdate = 1;
    }
}

void restoreCnt(int client)
{
    //csSetAction(client, WM_SYSCOMMAND, restoreCntInit,0);
}

/*-------------------------------------------------*/
void closeApp(csARGS Args)
{
    HWND hwnd = (HWND)Args;
    SendMessage(hwnd, WM_DESTROY, 0, 0);
    PostQuitMessage(0);
}
void destroyCnt(csARGS Args)
{
    int target = *(int*)Args[0];
    HWND hwnd = (HWND)Args;
    SendMessage(hwnd, WM_DESTROY, 0, 0);
    SendMessage(csHWND(target), WM_DESTROY, 0, 0);
}

void hideCnt(csARGS Args)
{
    int target = *(int*)Args[0];
    std::cout<<target<<" target\n";
    csPARAMS(target)->Show = 0;
}




int* csAddAppCloser(int idp, RECT geometry, RECT marg)
{
    char*btnclose1="img\\app\\Sys\\close1.bmp";
    char*btnclose2="img\\app\\Sys\\close2.bmp";
    csRGBA btn_color = {15,15,15};
    int *btnclose = csf_alloc2<int>(1,0);
    *btnclose = imgButton(cscp, idp, btnclose1, btnclose2,0, geometry,marg, btn_color);
    csSetAction(*btnclose, WM_LBUTTONUP, closeApp, 0);

    return btnclose;
}

int* csAddDestroyer(int idp, int*idTarget, RECT geometry, RECT marg)
{
    char*btnclose1="img\\app\\Sys\\close1.bmp";
    char*btnclose2="img\\app\\Sys\\close2.bmp";
    csRGBA btn_color = {15,15,15};
    int *btndestroy = csf_alloc2<int>(1,0);
    *btndestroy = imgButton(cscp, idp, btnclose1, btnclose2,0, geometry,marg, btn_color);
    csSetAction(*btndestroy, WM_LBUTTONUP, destroyCnt, 1, *idTarget);

    return btndestroy;
}

int* csAddHider(int idp, int* idTarget, RECT geometry, RECT marg)
{
    char*btnclose1="img\\app\\Sys\\close11.bmp";
    char*btnclose2="img\\app\\Sys\\close2.bmp";
    csRGBA btn_color = {15,15,15};
    int *btnhide = csf_alloc2<int>(1,0);
    *btnhide = imgButton(cscp, idp, btnclose1, btnclose2,0, geometry,marg, btn_color);
    csSetAction(*btnhide, WM_LBUTTONUP, hideCnt, 1, idTarget);

    return btnhide;
}
