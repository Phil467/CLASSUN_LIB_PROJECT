#include "csBUTTON.h"

extern csCNTR_PARAMS cscp;
extern csCNTR_VARS cv;
extern HINSTANCE* Hinst;
extern csCONTAINER csc;

csTEXTBUTTON::csTEXTBUTTON(int id_parent, const char*text, RECT geometry, bool lockable)
{
    if(geometry.right!=0 && geometry.bottom!=0)
    {
        create(id_parent, text, geometry, lockable);
    }
}

void csTEXTBUTTON::create(int id_parent, const char*text, RECT geometry, bool lockable)
{
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    cscp.Geometry= geometry;
    cscp.DCSizes={(unsigned int)geometry.right+2, (unsigned int)geometry.bottom+2};
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.Transparency=0;
    cscp.SizingParams= {0,0,0,0};
    //cscp.BackgroundColor= {100,110,10};
    cscp.BackgroundColor= {55,50,50};
    cscp.BorderWidth= 1;
    cscp.BorderColor= {60,60,60};
    cscp.MouseLeaveRemoveBkg = 1;
    cscp.TitleAlign=CS_TA_CENTER;
    cscp.Title.Text=(char*)text;
    cscp.Title.Bold=1;
    cscp.Title.FontSize= {15,0};
    cscp.Title.Font=/*"Arial black";//*//*"Bauhaus 93"*/"lucida calligraphy";
    cscp.Title.Color={220,220,220};
    //cscp.GeometryLink.LeftLinkEvent_target = GLINK_SIZE;
    //cscp.GeometryLink.LeftLinkEvent_source = GLINK_SIZE;
    //cscp.GeometryLink.idhwndLeft = h1;
    //cscp.CursorTracking.AllowCursorTracking = 1;
    //cscp.CursorTracking.CntRelativePosition = {0,30};
    //cscp.CursorTracking.SYS_COORD_HWND_ID = h1;
    cscp.MHGradient.GradientType = CS_GRAD_COLOR;
    cscp.MHGradient.GradientNumber = 2;
    cscp.MHGradient.TimeStep = 2;
    cscp.MHGradient.Color1 = {70,70,70};
    cscp.MHGradient.Color2 = {50,50,50};
    cscp.MouseHoverTime = 2;
    cscp.ClkGradient.GradientType = CS_GRAD_COLOR;
    cscp.ClkGradient.GradientNumber = 2;
    cscp.ClkGradient.TimeStep = 2;
    cscp.ClkGradient.Color = {90,90,90};
    cscp.LockedMode.Lockable = lockable;
    id = csc.csCNT_newContainer(id_parent, cscp);
}

int csTEXTBUTTON::setColors(csRGBA bkg, csRGBA text, csRGBA mouseOver1,csRGBA mouseOver2,
                            csRGBA click, csRGBA borders, int brdWidth, bool remBkg)
{
    cv.cp[id]->Title.Color = {text.r, text.g, text.b};
    cv.cp[id]->MHGradient.Color1 = mouseOver1;
    cv.cp[id]->MHGradient.Color2 = mouseOver2;
    cv.cp[id]->ClkGradient.Color = click;
    cv.cp[id]->BackgroundColor = bkg;
    cv.cp[id]->MouseLeaveRemoveBkg = remBkg;
    cv.cp[id]->BorderColor = borders;

    HDC hdc = GetDC(cv.CNTLIST[id]);
    cv.CTX[id].deleteDCS();
    cv.CTX[id].initSurfaceDesign(hdc, cv.cp[id]->BackgroundColor, cv.cp[id]->Geometry);
}

csTEXTBUTTON::~csTEXTBUTTON()
{
    //dtor
}

int csTEXTBUTTON::getId()
{
    return id;
}

int* csTEXTBUTTON::getIdPtr()
{
    return &id;
}

csCNTR_PARAMS* csTEXTBUTTON::getParams()
{
    return cv.cp[id];
}


int textButton(csCNTR_PARAMS& cscp, int idp, char*Text, csRGB tcol, RECT geometry, csLOCKED_MODE lm)
{
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    cscp.Geometry= geometry;
    cscp.DCSizes={(unsigned int)geometry.right+2, (unsigned int)geometry.bottom+2};
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.Transparency=0;
    cscp.SizingParams= {0,0,0,0};
    cscp.BackgroundColor= {100,110,10};
    cscp.BorderWidth= 1;
    cscp.BorderColor= {60,60,60};
    //cscp.BackgroundColor= {60,60,60};
    cscp.MouseLeaveRemoveBkg = 1;
    cscp.TitleAlign=CS_TA_CENTER;
    cscp.Title.Text=Text;
    cscp.Title.Bold=0;
    cscp.Title.FontSize= {15,0};
    cscp.Title.Font=/*"Arial black";//*//*"Bauhaus 93"*/"lucida calligraphy";
    cscp.Title.Color=tcol;
    //cscp.GeometryLink.LeftLinkEvent_target = GLINK_SIZE;
    //cscp.GeometryLink.LeftLinkEvent_source = GLINK_SIZE;
    //cscp.GeometryLink.idhwndLeft = h1;
    //cscp.CursorTracking.AllowCursorTracking = 1;
    //cscp.CursorTracking.CntRelativePosition = {0,30};
    //cscp.CursorTracking.SYS_COORD_HWND_ID = h1;
    cscp.MHGradient.GradientType = CS_GRAD_COLOR;
    cscp.MHGradient.GradientNumber = 3;
    cscp.MHGradient.TimeStep = 3;
    cscp.MHGradient.Color1 = {50,25,10};
    cscp.MHGradient.Color2 = {50,50,50};
    cscp.MouseHoverTime = 3;
    cscp.ClkGradient.GradientType = CS_GRAD_COLOR;
    cscp.ClkGradient.GradientNumber = 3;
    cscp.ClkGradient.TimeStep = 3;
    cscp.ClkGradient.Color = {60,60,10};
    cscp.LockedMode = lm;
    return csc.csCNT_newContainer(idp, cscp);
}
int textButton2(csCNTR_PARAMS& cscp, int idp, char*Text, csRGB tcol, RECT geometry, csLOCKED_MODE lm, SIZE dcSize)
{
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    cscp.Geometry= geometry;
    if(!dcSize.cx && !dcSize.cy)
        cscp.DCSizes={(unsigned int)geometry.right+2, (unsigned int)geometry.bottom+2};
    else
        cscp.DCSizes = {dcSize.cx+2, dcSize.cy+2};
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.Transparency=0;
    cscp.SizingParams= {0,0,0,0};
    cscp.BackgroundColor= {60,60,70};
    cscp.BorderWidth= 1;
    cscp.BorderColor= {0,0,0};
    //cscp.BackgroundColor= {60,60,60};
    cscp.MouseLeaveRemoveBkg = 0;
    cscp.TitleAlign=CS_TA_CENTER;
    cscp.Title.Text=Text;
    cscp.Title.Bold=FW_BOLD;
    cscp.Title.FontSize= {14,5};
    cscp.Title.Font=/*"Arial black";//*//*"Bauhaus 93"*/"Arial";
    cscp.Title.Color=tcol;
    //cscp.GeometryLink.LeftLinkEvent_target = GLINK_SIZE;
    //cscp.GeometryLink.LeftLinkEvent_source = GLINK_SIZE;
    //cscp.GeometryLink.idhwndLeft = h1;
    //cscp.CursorTracking.AllowCursorTracking = 1;
    //cscp.CursorTracking.CntRelativePosition = {0,30};
    //cscp.CursorTracking.SYS_COORD_HWND_ID = h1;
    cscp.MHGradient.GradientType = CS_GRAD_COLOR;
    cscp.MHGradient.GradientNumber = 3;
    cscp.MHGradient.TimeStep = 3;
    cscp.MHGradient.Color1 = {60,60,60};
    cscp.MHGradient.Color2 = {30,30,30};
    cscp.MouseHoverTime = 3;
    cscp.ClkGradient.GradientType = CS_GRAD_COLOR;
    cscp.ClkGradient.GradientNumber = 3;
    cscp.ClkGradient.TimeStep = 3;
    cscp.ClkGradient.Color = {90,90,90};
    cscp.LockedMode = lm;
    return csc.csCNT_newContainer(idp, cscp);
}

int imgButton(csCNTR_PARAMS& cscp, int idp, char*path1, char*path2, char*path3,
              RECT geometry, RECT margings, csRGBA color, int SameDesignCnt, bool remColor)
{
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    cscp.Geometry= geometry;
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.BackgroundColor= color;
    cscp.DCSizes={(unsigned int)geometry.right, (unsigned int)geometry.bottom};
    cscp.Transparency = 0;
    cscp.BackgroundImageSizes= {(unsigned int)geometry.right,(unsigned int)geometry.bottom};
    cscp.MouseLeaveRemoveBkg= remColor;
    cscp.LockedMode.Lockable = 1;
    cscp.LockedMode.LockingImagePath = path3;
    cscp.MHGradient.Image1 = path1;
    cscp.MHGradient.Image2 = path2;
    cscp.MHGradient.GradientType = CS_GRAD_IMAGE;
    cscp.MHGradient.Position = {margings.left,margings.top};
    cscp.MHGradient.Size = {(unsigned int)geometry.right-margings.right,(unsigned int)geometry.bottom-margings.bottom};
    cscp.MHGradient.GradientNumber = 5;
    cscp.MHGradient.TimeStep = 2;
    cscp.MHGradient.ZoomLevel = 0.1;
    cscp.ClkGradient.GradientType=CS_GRAD_IMAGE;
    cscp.SameDesignAs = SameDesignCnt;
    int id= csc.csCNT_newContainer(idp, cscp);
    return id;
}
int imgButton2(csCNTR_PARAMS& cscp, int idp, char*path1, char*path2, char*path3,
              RECT geometry, RECT margings, csRGBA color, int SameDesignCnt, bool remColor)
{
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    cscp.Geometry= geometry;
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.BackgroundColor= color;
    cscp.DCSizes={(unsigned int)geometry.right, (unsigned int)geometry.bottom};
    cscp.Transparency = 0;
    cscp.BackgroundImageSizes= {(unsigned int)geometry.right,(unsigned int)geometry.bottom};
    cscp.MouseLeaveRemoveBkg= remColor;
    cscp.LockedMode.Lockable = 1;
    cscp.LockedMode.LockingImagePath = path3;
    cscp.MHGradient.Image1 = path1;
    cscp.MHGradient.Image2 = path2;
    cscp.MHGradient.GradientType = CS_GRAD_IMAGE;
    cscp.MHGradient.Position = {margings.left,margings.top};
    cscp.MHGradient.Size = {(unsigned int)geometry.right-margings.right,(unsigned int)geometry.bottom-margings.bottom};
    cscp.MHGradient.GradientNumber = 5;
    cscp.MHGradient.TimeStep = 2;
    cscp.MHGradient.ImageRotationAngle = 30;
    cscp.MHGradient.HightLightColor = {200,0,0};
    cscp.MHGradient.HightLightLevel = 0.3;
    cscp.MHGradient.ZoomLevel = 0.1;
    cscp.ClkGradient.GradientType=CS_GRAD_IMAGE;
    cscp.SameDesignAs = SameDesignCnt;
    int id= csc.csCNT_newContainer(idp, cscp);
    return id;
}

int staticCnt(csCNTR_PARAMS& cscp, int idp, char*title, RECT geometry)
{
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    cscp.Geometry= geometry;
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.Transparency=0;
    cscp.SizingParams= {0,0,0,0};
    cscp.BackgroundColor= {20,30,30};
    cscp.BorderWidth= 1;
    //cscp.BorderColor= {70,70,70};
    cscp.BorderColor= {20,20,20};
    cscp.MouseLeaveRemoveBkg = 0;
    cscp.TitleAlign=CS_TA_TOP_CENTER;
    cscp.Title.Text=title;
    cscp.Title.Bold=1;
    cscp.Title.FontSize= {20,0};
    cscp.Title.Font="Arial black";//"Bauhaus 93";
    cscp.Title.Color= {200,200,200};
    cscp.MHGradient.GradientType = CS_GRAD_COLOR;
    cscp.MHGradient.GradientNumber = 3;
    cscp.MHGradient.TimeStep = 3;
    cscp.MHGradient.Color1 = {30,40,40};
    cscp.MHGradient.Color2 = {20,30,30};
    cscp.MouseHoverTime = 3;
    return csc.csCNT_newContainer(idp, cscp);
}

int staticCnt2(csCNTR_PARAMS& cscp, int idp, char*title, csRGBA color, RECT geometry, bool show, float mhgradientLevel, SIZE dcSize)
{
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    cscp.Geometry= geometry;
    cscp.MinMaxStyle=0;
    cscp.ClingToParent=1;
    cscp.Show=show;
    cscp.Transparency=0;
    cscp.BackgroundColor= color;
    cscp.DCSizes={dcSize.cx, dcSize.cy};
    cscp.BorderWidth= 1;
    //cscp.BorderColor= {40,40,40};
    cscp.BorderColor= {20,20,20};
    cscp.MouseLeaveRemoveBkg = 0;
    cscp.Title.Text=title;
    //cscp.Title.Bold=FW_BOLD;
    //cscp.Title.FontSize= {14,5};
    cscp.Title.Font=/*"Arial black";//*//*"Bauhaus 93"*/"Arial";
    cscp.TitleAlign=CS_TA_TOP_CENTER;
    if(mhgradientLevel)
    {
        cscp.MHGradient.GradientType = CS_GRAD_COLOR;
        cscp.MHGradient.GradientNumber = 3;
        cscp.MHGradient.TimeStep = 3;
        cscp.MHGradient.Color1 = csTint(color, {255,255,255},mhgradientLevel);
        cscp.MHGradient.Color2 = color;
        cscp.MouseHoverTime = 3;
    }

    return csc.csCNT_newContainer(idp, cscp);
}


void messagesTransfer(csARGS Args);
void csSetRulersTrackers(int* _id, csRGBA color, int witdh, int length, bool x1, bool x2, bool y1, bool y2)
{
    int id = *_id;
    cv.CTX[id].idTrackerX1 = 0;
    cv.CTX[id].idTrackerX2 = 0;
    cv.CTX[id].idTrackerY1 = 0;
    cv.CTX[id].idTrackerY2 = 0;
    if(x1)
    {
        cv.CTX[id].idTrackerX1 = csf_alloc2<int>(1,
        staticCnt2(cscp, id, "", color,{0,0,witdh, length},1));
        cv.CTX[*(cv.CTX[id].idTrackerX1)].setCntBorder(color,1);
        SetWindowLong(cv.CNTLIST[*(cv.CTX[id].idTrackerX1)],GWL_EXSTYLE,
        GetWindowLong(cv.CNTLIST[*(cv.CTX[id].idTrackerX1)], GWL_EXSTYLE)|WS_EX_TRANSPARENT);

        csARGS args(1);
        args.makeArgs(_id);
        csSetGroupedAction(*cv.CTX[id].idTrackerX1, messagesTransfer,args);
    }
    if(x2)
    {
        cv.CTX[id].idTrackerX2 = csf_alloc2<int>(1,
        staticCnt2(cscp, id, "", color,{0,0,witdh, length},1));
        cv.CTX[*(cv.CTX[id].idTrackerX2)].setCntBorder(color,1);
        SetWindowLong(cv.CNTLIST[*(cv.CTX[id].idTrackerX2)],GWL_EXSTYLE,
        GetWindowLong(cv.CNTLIST[*(cv.CTX[id].idTrackerX2)], GWL_EXSTYLE)|WS_EX_TRANSPARENT);

        csARGS args(1);
        args.makeArgs(_id);
        csSetGroupedAction(*cv.CTX[id].idTrackerX2, messagesTransfer,args);
    }
    if(y1)
    {
        cv.CTX[id].idTrackerY1 = csf_alloc2<int>(1,
        staticCnt2(cscp, id, "", color,{0,0,length, witdh},1));
        cv.CTX[*(cv.CTX[id].idTrackerY1)].setCntBorder(color,1);
        SetWindowLong(cv.CNTLIST[*(cv.CTX[id].idTrackerY1)],GWL_EXSTYLE,
        GetWindowLong(cv.CNTLIST[*(cv.CTX[id].idTrackerY1)], GWL_EXSTYLE)|WS_EX_TRANSPARENT);

        csARGS args(1);
        args.makeArgs(_id);
        csSetGroupedAction(*cv.CTX[id].idTrackerY1, messagesTransfer,args);

    }
    if(y2)
    {
        cv.CTX[id].idTrackerY2 = csf_alloc2<int>(1,
        staticCnt2(cscp, id, "", color,{0,0,length, witdh},1));
        cv.CTX[*(cv.CTX[id].idTrackerY2)].setCntBorder(color,1);
        SetWindowLong(cv.CNTLIST[*(cv.CTX[id].idTrackerY2)],GWL_EXSTYLE,
        GetWindowLong(cv.CNTLIST[*(cv.CTX[id].idTrackerY2)], GWL_EXSTYLE)|WS_EX_TRANSPARENT);

        csARGS args(1);
        args.makeArgs(_id);
        csSetGroupedAction(*cv.CTX[id].idTrackerY2, messagesTransfer,args);
    }





    /*SetTimer(cv.CNTLIST[*(cv.CTX[id].idTrackerX1)],0,12,0);
    SetTimer(cv.CNTLIST[*(cv.CTX[id].idTrackerX2)],0,16,0);
    SetTimer(cv.CNTLIST[*(cv.CTX[id].idTrackerY1)],0,12,0);
    SetTimer(cv.CNTLIST[*(cv.CTX[id].idTrackerY2)],0,16,0);*/

    /*SetParent(cv.CNTLIST[*(cv.CTX[id].idTrackerX1)],0);
    SetParent(cv.CNTLIST[*(cv.CTX[id].idTrackerX2)],0);
    SetParent(cv.CNTLIST[*(cv.CTX[id].idTrackerY1)],0);
    SetParent(cv.CNTLIST[*(cv.CTX[id].idTrackerY2)],0);*/
}

void messagesTransfer(csARGS Args)
{
    UINT msg = (UINT)Args;
    if(msg == WM_KEYDOWN)
    {
        SendMessage(csHWND(*(int*)Args[0]), WM_KEYDOWN,(WPARAM)Args,(LPARAM)Args);
    }
    if(msg == WM_KEYUP)
    {
        SendMessage(csHWND(*(int*)Args[0]), WM_KEYUP,(WPARAM)Args,(LPARAM)Args);
    }
}
