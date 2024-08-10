#include "csBUTTON_GROUP.h"


extern csCNTR_PARAMS cscp;
extern csCNTR_VARS cv;
extern HINSTANCE* Hinst;
extern csCONTAINER csc;
extern MSG Messages;

void frameButton_btnup(csARGS Args);
void frameButton_size(csARGS Args);
void viewSideBtnOn(csARGS Args);
void viewSideBtnOff(csARGS Args);
void holdOnPrevBtn(csARGS Args);
void holdOnNextBtn(csARGS Args);
void dblclickOnPrevBtn(csARGS Args);
void dblclickOnNextBtn(csARGS Args);
void unlock(csARGS Args);
void SideBtnPos(csARGS Args);
void pos_timer(csARGS Args);
void normalMove(csARGS Args);
void send_lbtnDown(csARGS Args);
void send_lbtnUp(csARGS Args);
void receive_mouseMove(csARGS Args);
void receive_lbtnDown(csARGS Args);

void makePrison(csARGS Args);
void smoothMove(csARGS Args);
void autoHideSideButtons(csARGS Args);

void csReachFirst(csARGS Args);
void csReachLast(csARGS Args);

void popup_life(csARGS Args);
void onClic(csARGS Args);

csTEXTBUTTON_GROUP::csTEXTBUTTON_GROUP(int id_parent, RECT geometry, bool orientation)
{
    if((geometry.right != 0) && (geometry.bottom != 0))
    {
        init(id_parent, geometry, orientation);
    }

}

/*void csTEXTBUTTON_GROUP::init(int orientation)
{

}*/

void csTEXTBUTTON_GROUP::init(int id_parent, RECT geometry, bool orientation)
{
//     if(!orient)
//         init(orientation);
    orient = 0;
    marg = 0;
    totalLength = 0;
    sideBtnLength = 0;
    moverLen = 0;
    defaultBtnLength = 0;
    idc1 = 0;
    idc2 = 0;
    idc3 = 0;
    idS1 = 0;
    idS2 = 0;
    inc = 0;
    hold = 0;
    popup = 0;
    popupdelay = 0;
    lbtndown1 = 0;
    lbtndown2 = 0;
    marg3 = 0;

    marg3 = csf_alloc2<int>(1,2);
    orient = csf_alloc2<bool>(1,orientation);
    marg = csf_alloc2<int>(1, 1);
    totalLength = csf_alloc2<int>(1, *marg);
    sideBtnLength = csf_alloc2<int>(1,10);
    moverLen = csf_alloc<int>(1);
    defaultBtnLength = csf_alloc2<int>(1, 100);
    idc1 = csf_alloc<int>(1);
    idc2 = csf_alloc<int>(1);
    idc3 = csf_alloc<int>(1);
    idS1 = csf_alloc<int>(1);
    idS2 = csf_alloc<int>(1);
    inc = csf_alloc2<int>(1,12);
    hold = csf_alloc<bool>(1);
    popup = csf_alloc<int>(1);
    popupdelay = csf_alloc<unsigned>(1);
    lbtndown1 = csf_alloc<bool>(1);
    lbtndown2 = csf_alloc2<bool>(1,1);


    *orient = orientation;
    geom1 = geometry;
    RECT geomS1, geomS2;
    int xmarging = 0, ymarging = 0;
    if(orientation == CS_BG_HORIZONTAL)
    {
        geom2 = {*sideBtnLength+*marg, *marg, geom1.right-2*(*marg+*sideBtnLength), geom1.bottom-*marg*2};
        geomS1 = {*marg, *marg, *sideBtnLength, geom1.bottom-*marg*2};
        geomS2 = {geom1.right-*marg-*sideBtnLength, *marg, *sideBtnLength, geom1.bottom-*marg*2};
        xmarging = *marg+*sideBtnLength+10;
        ymarging = *marg+geom1.bottom;
    }
    else
    {
        geom2 = {*marg, *sideBtnLength+*marg, geom1.right-*marg*2, geom1.bottom-2*(*marg+*sideBtnLength)};
        geomS1 = {*marg, *marg, geom1.right-*marg*2, *sideBtnLength};
        geomS2 = {*marg, geom1.bottom-*marg-*sideBtnLength, geom1.right-*marg*2, *sideBtnLength};
        ymarging = *marg+*sideBtnLength+10;
        xmarging = *marg+geom1.right;
    }

    *idc1 = staticCnt2(cscp, id_parent, "", {30,30,30}, geom1,1);
    cv.cp[*idc1]->MinTrackSize = {geom1.right/2,geom1.bottom};
    cv.cp[*idc1]->CaptionDirection = CAPTION_DIRECTION_ALL;
    cv.cp[*idc1]->AllowXMinMaxTrackPosition = 1;
    cv.cp[*idc1]->XMinTrackPosition = 1;
    cv.cp[*idc1]->YMaxTrackPosition = 1;
    //csSetAction(id_parent, WM_SIZE, makePrison, 3, idc1, xmarging, ymarging);

    *idc2 = staticCnt2(cscp, *idc1, "", {10,20,20}, {geom2.left, geom2.top, geom2.right, geom2.bottom},1);
    //*idc3 = staticCnt2(cscp, *idc2, "", {10,20,40}, {2,2,96,21},1);

    if(*orient == CS_BG_HORIZONTAL)
        *idc3 = staticCnt2(cscp, *idc2, "", {30,30,30}, {0,*marg3,0,csCLRECT(*idc1).bottom-(*marg-*marg3)*2},1);
    else
        *idc3 = staticCnt2(cscp, *idc2, "", {30,30,30}, {*marg3,0,csCLRECT(*idc1).right-(*marg-*marg3)*2,0},1);


    cv.cp[*idc2]->AutoTransform.Type=AUTO_TRANSF_LENGTH;
    cv.cp[*idc2]->AutoTransform.Time=5;
    cv.cp[*idc2]->MouseLeaveRemoveBkg = 1;
    cv.cp[*idc3]->AutoTransform.Type=AUTO_TRANSF_LENGTH;
    cv.cp[*idc3]->AutoTransform.Time=5;
    //csSetBackgroundImage(idc1,"img\\bkg1.bmp",{(unsigned)CS_CXSCREEN,25});
    //csSetBackgroundImage(idc2,"img\\bkg1.bmp",{(unsigned)CS_CXSCREEN,25});

    cv.cp[*idc3]->AutoTransform.Time = 10;
    cv.cp[*idc3]->AutoTransform.Type = AUTO_TRANSF_LENGTH;
    side1.create(*idc1, "", geomS1, 0);
    side2.create(*idc1, "", geomS2, 0);

    if(*orient == CS_BG_VERTICAL)
    {
        side1.getParams()->Title.Orientation = -900;
        side2.getParams()->Title.Orientation = -900;
        int m = *sideBtnLength/2;
        side1.getParams()->Title.TextRect = {m,m-2};
        side2.getParams()->Title.TextRect = {m,m-2};
        path1 = "img\\app\\up_31.bmp";
        path2 = "img\\app\\down_31.bmp";
       // csSetBackgroundImage(side1.getId(),path1,{geomS1.right,geomS1.bottom});
       // csSetBackgroundImage(side2.getId(),path2,{geomS1.right,geomS1.bottom});
    }
    else
    {
        path1 = "img\\app\\prev_31.bmp";
        path2 = "img\\app\\next_31.bmp";
       // csSetBackgroundImage(side1.getId(),path1,{geomS1.right,geomS1.bottom});
       // csSetBackgroundImage(side2.getId(),path2,{geomS1.right,geomS1.bottom});
    }
    side1.getParams()->Title.Font = "Arial";
    side2.getParams()->Title.Font = "Arial";
    side1.getParams()->Title.Color = {80,80,80};
    side2.getParams()->Title.Color = {80,80,80};
    side1.getParams()->BackgroundColor = {50,50,50};
    side2.getParams()->BackgroundColor = {50,50,50};
    side1.getParams()->MouseLeaveRemoveBkg = 0;
    side2.getParams()->MouseLeaveRemoveBkg = 0;
    side1.getParams()->AutoTransform.Type=AUTO_TRANSF_LENGTH;
    side1.getParams()->AutoTransform.Time=5;
    side2.getParams()->AutoTransform.Type=AUTO_TRANSF_LENGTH;
    side2.getParams()->AutoTransform.Time=5;

    mhg.Image1 = path1;
    mhg.Image2 = path1;
    mhg.Position = {0,0};
    mhg.Size = {geomS1.right,geomS1.bottom};
    mhg.GradientNumber = 5;
    mhg.TimeStep = 2;
    mhg.ImageRotationAngle = 0;
    mhg.HightLightColor = {100,100,0};
    mhg.HightLightLevel = 0.3;
    mhg.ZoomLevel = 0.4;

    *idS1 = side1.getId();
    *idS2 = side2.getId();

    csSetImageGradients(*idS1, mhg);
    mhg.Image1 = path2;
    mhg.Image2 = path2;
    csSetImageGradients(*idS2, mhg);

    SendMessage(cv.CNTLIST[*idS1], WM_ERASEBKGND, 0,0);
    SendMessage(cv.CNTLIST[*idS2], WM_ERASEBKGND, 0,0);

    csSetAction(*idS1, WM_LBUTTONDOWN, viewSideBtnOn, 5, orient, idc2, idc3, inc, hold);
    csSetAction(*idS1, WM_LBUTTONDBLCLK, dblclickOnPrevBtn, cv.cp[*idS1]->CntEventsFunc.LBUTTONDOWN_ARGS[0]);
    csSetAction(*idS1, WM_LBUTTONUP, viewSideBtnOff, cv.cp[*idS1]->CntEventsFunc.LBUTTONDOWN_ARGS[0]);
    csSetAction(*idS2, WM_LBUTTONDOWN, viewSideBtnOn, cv.cp[*idS1]->CntEventsFunc.LBUTTONDOWN_ARGS[0]);
    csSetAction(*idS2, WM_LBUTTONDBLCLK, dblclickOnNextBtn, cv.cp[*idS1]->CntEventsFunc.LBUTTONDOWN_ARGS[0]);
    csSetAction(*idS2, WM_LBUTTONUP, viewSideBtnOff, cv.cp[*idS1]->CntEventsFunc.LBUTTONDOWN_ARGS[0]);
    csSetAction(*idS1, WM_TIMER, holdOnPrevBtn, cv.cp[*idS1]->CntEventsFunc.LBUTTONDOWN_ARGS[0]);//car lbtndown2 == prev == 0
    csSetAction(*idS2, WM_TIMER, holdOnNextBtn, cv.cp[*idS1]->CntEventsFunc.LBUTTONDOWN_ARGS[0]);
    csSetAction(*idS1, WM_MOUSEWHEEL, holdOnPrevBtn, cv.cp[*idS1]->CntEventsFunc.LBUTTONDOWN_ARGS[0]);
    csSetAction(*idS2, WM_MOUSEWHEEL, holdOnNextBtn, cv.cp[*idS1]->CntEventsFunc.LBUTTONDOWN_ARGS[0]);

    csSetAction(*idS1, WM_RBUTTONDBLCLK, csReachFirst, 3, idc2, idc3, orient);
    csSetAction(*idS2, WM_RBUTTONDBLCLK, csReachLast, 3, idc2, idc3, orient);

    RECT* rs1 = csf_alloc2<RECT>(1,{0});
    RECT* rs2 = csf_alloc2<RECT>(1,{0});
    RECT* rc2 = csf_alloc2<RECT>(1,{0});

    csSetAction(*idc1, WM_SIZE, SideBtnPos, 12, sideBtnLength, marg, idc2, idS1, idS2, moverLen, orient, rs1,rs2,rc2, idc3, marg3);
    csSetAction(*idS1, WM_TIMER, pos_timer, 1, rs1);
    csSetAction(*idS2, WM_TIMER, pos_timer, 1, rs2);
    csSetAction(*idc2, WM_TIMER, pos_timer, 1, rc2);
    //csSetAction(*idc1, WM_SIZE, frameButton_size, 3, idc2, idc3, orient);

    /*bshow = (bool*)malloc(sizeof(bool));
    *bshow = 0;
    csSetAction(*idc1, WM_SIZE, autoHideSideButtons, 9, idc2, idc3, idS1, idS2, marg, moverLen, sideBtnLength, orient, bshow);*/
    // if(*orient == CS_BG_HORIZONTAL)
    // csGeometryLink(idc1, 2, csGLP4_PTR(csGLP4{*idS2, {*sideBtnLength+*marg,1.0,0}, {0,0,*marg}, {0,0,*sideBtnLength}, {0,0,geomS1.bottom}}),
    //                         csGLP4_PTR(csGLP4{*idc2, {0,0,*sideBtnLength+*marg+*moverLen}, {0,0,*marg}, {2*(*sideBtnLength+*marg)+*moverLen,1.0,0}, {0,0,geomS1.bottom}}));
    btnargs.setArgNumber(3);
    btnargs.makeArgs( idc2, idc3, orient);

    SetTimer(csHWND(*idS1),0,10,0);
    SetTimer(csHWND(*idS2),0,10,0);
    SetTimer(csHWND(*idc2),0,10,0);

}

void csTEXTBUTTON_GROUP::setBackgroundImage(char*path, csSIZE size)
{
    //cv.cp[*idc3]->MouseLeaveRemoveBkg = 1;
    //csSetBackgroundImage(*idc2,path);
    cv.cp[*idc3]->DCSizes = size;
    csSetBackgroundImage(*idc3,path, size);
}

void csTEXTBUTTON_GROUP::setMarging(int marging)
{
    *marg = marging;

    mhg.Image1 = path1;
    mhg.Image2 = path1;

    RECT r = csCLRECT(*idc1);
    if(*orient == CS_BG_HORIZONTAL)
    {
        mhg.Size = {*sideBtnLength,r.bottom-2*marging};
        csCLRECT(*idc3).bottom = r.bottom - 2*(marging+*marg3);
    }
    else
    {
        mhg.Size = {r.right-2*marging, *sideBtnLength};
        csCLRECT(*idc3).right = r.right - 2*(marging+*marg3);
    }
    //SetWindowPos(csHWND(*idc3),0,r.left,r.top,r.right, r.bottom,SWP_NOZORDER);
    csUPDATEWRECT_S(*idc3);
    csUPDATEWRECT(*idc3);

    *idS1 = side1.getId();
    *idS2 = side2.getId();

    csSetImageGradients(*idS1, mhg);
    mhg.Image1 = path2;
    mhg.Image2 = path2;
    csSetImageGradients(*idS2, mhg);

    SendMessage(cv.CNTLIST[*idS1], WM_ERASEBKGND, 0,0);
    SendMessage(cv.CNTLIST[*idS2], WM_ERASEBKGND, 0,0);
}

void csTEXTBUTTON_GROUP::setC3Marging(int marging)
{
    if(*orient == CS_BG_HORIZONTAL)
    {
        csCLRECT(*idc3).bottom += *marg3 - marging;
        SetWindowPos(csHWND(*idc3),0,0,0,csCLRECT(*idc3).right, csCLRECT(*idc3).bottom,SWP_NOMOVE|SWP_NOZORDER);
    }
    else
    {
        csCLRECT(*idc3).right += *marg3 - marging;
        SetWindowPos(csHWND(*idc3),0,0,0,csCLRECT(*idc3).right, csCLRECT(*idc3).bottom,SWP_NOMOVE|SWP_NOZORDER);
    }
    *marg3 = marging;
}

void csTEXTBUTTON_GROUP::setBorderColor(csRGBA color)
{
    cv.cp[*idc1]->BackgroundColor = color;
    cv.CTX[*idc1].setBkgBrush(cv.cp[*idc1]->BackgroundColor);
}

int csTEXTBUTTON_GROUP::getID()
{
    return *idc1;
}
int* csTEXTBUTTON_GROUP::getIDPtr()
{
    return idc1;
}

void csTEXTBUTTON_GROUP::movable(int moverThickness, bool _smoothMove)
{
    cv.cp[*idc1]->CaptionAreaLength = moverThickness;
    *moverLen = moverThickness;
    cv.cp[*idc1]->CaptionAreaPos = 3;
    cv.cp[*idc1]->CaptionDirection = CAPTION_DIRECTION_ALL;
    if(*orient == CS_BG_HORIZONTAL)
    {
        capt.create(*idc1,"|",{*marg,*marg,moverThickness,geom1.bottom-2**marg},0);
        SetWindowPos(cv.CNTLIST[side1.getId()],HWND_TOP,*marg+moverThickness, *marg, 0,0,SWP_NOSIZE|SWP_NOREDRAW);
        SetWindowPos(cv.CNTLIST[side2.getId()],HWND_TOP,geom2.right+geom2.left, *marg, 0,0,SWP_NOSIZE|SWP_NOREDRAW);
    }
    else
    {
        RECT r = {*marg,*marg,geom1.right-*marg*2, moverThickness};
        capt.create(*idc1,"|",r,0);
        capt.getParams()->Title.Orientation = -900;
        capt.getParams()->Title.Orientation = -900;
        int m = moverThickness/2;
        capt.getParams()->Title.TextRect = {m,m-2};
        capt.getParams()->Title.TextRect = {m,m-2};
        SetWindowPos(cv.CNTLIST[side1.getId()],HWND_TOP,*marg, *marg+moverThickness, 0,0,SWP_NOSIZE|SWP_NOREDRAW);
        SetWindowPos(cv.CNTLIST[side2.getId()],HWND_TOP,*marg,geom2.bottom+geom2.top, 0,0,SWP_NOSIZE|SWP_NOREDRAW);
    }

    SetWindowPos(cv.CNTLIST[*idc2],HWND_BOTTOM,*marg+moverThickness+*sideBtnLength, *marg, geom1.right-2*(*marg+*sideBtnLength)-moverThickness,csCLRECT(*idc2).bottom,SWP_NOREDRAW);
    SetWindowPos(cv.CNTLIST[*idc1],HWND_BOTTOM,geom1.left, geom1.top, geom1.right+10,geom1.bottom,SWP_NOREDRAW);
    //SetWindowPos(cv.CNTLIST[*idc1],0,geom1.left, geom1.top, geom1.right,geom1.bottom,SWP_NOREDRAW);
    int id = capt.getId();
    cv.cp[id]->Title.Font = "Arial";
    cv.cp[id]->Title.Bold = 1;
    cv.cp[id]->Cursor = (LoadCursor(0,IDC_SIZEALL));
    //csRGBA c = cv.cp[id]->BackgroundColor;
    //cv.cp[id]->Title.Color = {c.r+10,c.g+10,c.b+10};
    //cv.cp[id]->MouseLeaveRemoveBkg = 0;
    capt.getParams()->MHGradient.Color1 = side1.getParams()->MHGradient.Color1;
    capt.getParams()->MHGradient.Color2 = side1.getParams()->MHGradient.Color2;
    capt.getParams()->ClkGradient.Color = side1.getParams()->ClkGradient.Color;
    csARGS arg(1);
    arg.makeArgs((void*)idc1);
    if(_smoothMove)
        csSetAction(id, WM_TIMER, smoothMove, arg);
    else
        csSetAction(id, WM_MOUSEMOVE, normalMove, arg);
}

csTEXTBUTTON csTEXTBUTTON_GROUP::getMover()
{
    return capt;
}
csTEXTBUTTON csTEXTBUTTON_GROUP::getButton(int id)
{
    return btns[id];
}

void csTEXTBUTTON_GROUP::setMouseTrackingColors(csRGBA c_track1, csRGBA c_track2, csRGBA c_click, csRGBA c_lock)
{
    int n = btns.size();
    for(int i=0; i<n; i++)
    {
        btns[i].getParams()->MHGradient.Color1 = c_track1;
        btns[i].getParams()->MHGradient.Color2 = c_track2;
        btns[i].getParams()->ClkGradient.Color = c_click;
        btns[i].getParams()->LockedMode.LockingColor = c_lock;
    }
    side1.getParams()->MHGradient.Color1 = c_track1;
    side1.getParams()->MHGradient.Color2 = c_track2;
    side1.getParams()->ClkGradient.Color = c_click;
    side2.getParams()->MHGradient.Color1 = c_track1;
    side2.getParams()->MHGradient.Color2 = c_track2;
    side2.getParams()->ClkGradient.Color = c_click;

}

void csTEXTBUTTON_GROUP::resizable(int thickness)
{
    cv.cp[*idc1]->SizingAreaLength = thickness;
}
void csTEXTBUTTON_GROUP::resizable_left()
{
    cv.cp[*idc1]->HTLeft = 1; //cv.CURRENT_HITTEST_AREA == CSA_RIGHT
}
void csTEXTBUTTON_GROUP::resizable_top()
{
    cv.cp[*idc1]->HTTop = 1; //cv.CURRENT_HITTEST_AREA == CSA_RIGHT
}
void csTEXTBUTTON_GROUP::resizable_right()
{
    cv.cp[*idc1]->HTRight = 1; //cv.CURRENT_HITTEST_AREA == CSA_RIGHT
}
void csTEXTBUTTON_GROUP::resizable_bottom()
{
    cv.cp[*idc1]->HTBottom = 1; //cv.CURRENT_HITTEST_AREA == CSA_RIGHT
}

RECT csTEXTBUTTON_GROUP::getGeometry()
{
    return geom1;
}
RECT* csTEXTBUTTON_GROUP::getGeometryPtr()
{
    return &geom1;
}

void csTEXTBUTTON_GROUP::newButton(const char*title, int length, bool lockable,SIZE fontSize)
{
    int len = length;
    char*fontName="Bahnschrift Light";
    if(length == 0)
        len = *defaultBtnLength;
    else if(length == -1)
    {
        HFONT font = CreateFont(fontSize.cx,fontSize.cy, 0, 0, 0,0,0, 0,0,0,0,0,0, (LPCSTR)fontName);
        LPSIZE lps=csTextExtent(*idc3,font,(char*)title);
        len = lps->cx+20;
        std::cout<<len<<" -----------------------\n";
        //free(lps);

    }
    if(*orient == CS_BG_HORIZONTAL)
    {
        MoveWindow(cv.CNTLIST[*idc3],0,*marg3,*totalLength+len, csCLRECT(*idc3).bottom,1);
        csTEXTBUTTON btn(*idc3, title, {*totalLength,*marg+2, len, csCLRECT(*idc3).bottom-4}, lockable);
        btns.insertEnd(btn);
        btn.getParams()->MHGradient.Color2 = cv.cp[*idc2]->BackgroundColor;
        btn.getParams()->Title.Font = fontName;
        btn.getParams()->Title.Color = {200,200,200};
        btn.getParams()->Title.Bold = 0;
        btn.getParams()->Title.FontSize = fontSize;
        //csBmpToCntSurface("img/circle2.bmp", {20,20}, cv.CTX[btn.getId()].getDC());
        csSetAction(btn.getId(), WM_LBUTTONUP, frameButton_btnup, btnargs);
        //cv.cp[*idc1]->MaxTrackSize = {*totalLength + len, GetSystemMetrics(SM_CXSCREEN)};

    }
    else
    {
        MoveWindow(cv.CNTLIST[*idc3],*marg3,0, csCLRECT(*idc3).right,*totalLength+len,1);
        csTEXTBUTTON btn(*idc3, title, {*marg+2,*totalLength, csCLRECT(*idc3).right-4, len}, lockable);
        btns.insertEnd(btn);
        btn.getParams()->MHGradient.Color2 = cv.cp[*idc2]->BackgroundColor;
        btn.getParams()->Title.Font = fontName;
        btn.getParams()->Title.Color = {200,200,200};
        btn.getParams()->Title.Bold = 0;
        btn.getParams()->Title.FontSize = fontSize;
        csSetAction(btn.getId(), WM_LBUTTONUP, frameButton_btnup, btnargs);
        //cv.cp[*idc1]->MaxTrackSize = {GetSystemMetrics(SM_CYSCREEN), *totalLength + len};
    }

    *totalLength += len;

}

int csTEXTBUTTON_GROUP::getIDC3()
{
    return *idc3;
}
int* csTEXTBUTTON_GROUP::getIDC3Ptr()
{
    return idc3;
}
int csTEXTBUTTON_GROUP::getIDS1()
{
    return *idS1;
}
int* csTEXTBUTTON_GROUP::getIDC2Ptr()
{
    return idc2;
}
int csTEXTBUTTON_GROUP::getIDC2()
{
    return *idc2;
}
int csTEXTBUTTON_GROUP::getIDS2()
{
    return *idS2;
}

bool csTEXTBUTTON_GROUP::getOrientation()
{
    return *orient;
}

void csTEXTBUTTON_GROUP::setTotalLength(int len)
{
    *totalLength = len;
}

void csTEXTBUTTON_GROUP::setPopupCnt(int idpupop)
{
    *popup = idpupop;
}

void csTEXTBUTTON_GROUP::connectAll()
{
    int n = btns.size();
    args.setArgNumber(1);
    //active = btns[0].getId();
    pactive = btns[0].getIdPtr();
    args.makeArgs(pactive);
    for(int i=0; i<n; i++)
    {
        btns[i].getParams()->LockedMode.Lockable = 1;
        btns[i].getParams()->LockedMode.ExternalUnlocking = 1;
        btns[i].getParams()->LockedMode.Locked = 0;
        csSetAction(btns[i].getId(),WM_LBUTTONUP,unlock, args);
    }
}

void csTEXTBUTTON_GROUP::setActive(int gid)
{
    active = btns[gid].getId();
    btns[gid].getParams()->LockedMode.Locked=1;
    //SendMessage(cv.CNTLIST[active], WM_MOUSEMOVE,0,0);
    //SendMessage(cv.CNTLIST[active], WM_LBUTTONUP,0,MAKELPARAM(0,0));
}

void csTEXTBUTTON_GROUP::setPopupDelay(unsigned delay)
{
    *popupdelay = delay;
}

void csTEXTBUTTON_GROUP::removeBackground()
{
    //cv.cp[*idc3]->MHGradient.Color1=cv.cp[*idc3]->BackgroundColor;
    //cv.cp[*idc3]->MHGradient.Color2=cv.cp[*idc3]->BackgroundColor;
    //cv.cp[*idc2]->MHGradient.Color1=cv.cp[*idc2]->BackgroundColor;
    //cv.cp[*idc2]->MHGradient.Color2=cv.cp[*idc2]->BackgroundColor;
    //cv.cp[*idc1]->MHGradient.Color1=cv.cp[*idc1]->BackgroundColor;
    //cv.cp[*idc1]->MHGradient.Color2=cv.cp[*idc1]->BackgroundColor;

    //setMouseTrackingColors({30,30,30},{20,20,20},{40,40,40},{56,50,50});
    cv.cp[*idc3]->MouseLeaveRemoveBkg=1;
    cv.cp[*idc2]->MouseLeaveRemoveBkg=1;
    cv.cp[*idc1]->MouseLeaveRemoveBkg=1;
}

void csTEXTBUTTON_GROUP::setC3Size(int length, int marging)
{
    if(marging > -1)
        *marg3 = marging;
    if(length > -1)
        *totalLength = length;
    cv.cp[*idc3]->AutoTransform.InitialRect = {0,*marg3,*totalLength,csCLRECT(*idc1).bottom-2*(*marg3+*marg)};
    cv.cp[*idc3]->AutoTransform.FinalRect = {0,0,0,0};
    cv.AUTOTRANSCOUNT[*idc3] = 0;
}

void csTEXTBUTTON_GROUP::create()
{
    if(*orient == CS_BG_HORIZONTAL)
    {
        cv.cp[*idc3]->AutoTransform.InitialRect = {0,*marg3,*totalLength,csCLRECT(*idc3).bottom};
        cv.cp[*idc3]->AutoTransform.FinalRect = {0,0,0,0};
        cv.AUTOTRANSCOUNT[*idc3] = 0;
        if(*popup)
        {
            RECT r=cv.cp[*popup]->Geometry;
            for(int i=0; i<btns.size(); i++)
            {
                getButton(i).getParams()->MouseHoverShowCnt.Ids.insertEnd(*popup);
                getButton(i).getParams()->MouseHoverShowCnt.Geometry.insertEnd(r);
                getButton(i).getParams()->MouseHoverShowCnt.Bpos.insertEnd({0,0,0,0,0,0,0,0,0,1});
                getButton(i).getParams()->MouseHoverShowCnt.Delay = *popupdelay;
                getButton(i).getParams()->MouseHoverShowCnt.Lock = 1;
                csSetAction(btns[i].getId(), WM_LBUTTONUP, onClic, 1, popup);
            }

            csSetAction(*popup, WM_TIMER, popup_life, 2, btns.getTable(), btns.sizePtr());
        }
    }
    else
    {
        cv.cp[*idc3]->AutoTransform.InitialRect = {*marg3,0,csCLRECT(*idc3).right,*totalLength};
        cv.cp[*idc3]->AutoTransform.FinalRect = {0,0,0,0};
        cv.AUTOTRANSCOUNT[*idc3] = 0;
    }
}

/*********************************************************************************************************/

void viewSideBtnOn(csARGS Args)
{
    *(bool*)Args[4] = 1;
}
void viewSideBtnOff(csARGS Args)
{
    *(bool*)Args[4] = 0;
}


/*************************************************************/
void holdOnPrevBtn(csARGS Args)
{
    //if((GetAsyncKeyState(VK_LBUTTON)<0 && cv.HWNDCAPTURE==(HWND)Args)
        //|| (GET_WHEEL_DELTA_WPARAM(WPARAM(Args))>0))
    {
        if((*(bool*)Args[4] || (GET_WHEEL_DELTA_WPARAM(WPARAM(Args))<0)) && cv.HWNDCAPTURE==(HWND)Args)
        {
            bool orient = *(bool*)Args[0];
            int idc2 = *(int*)Args[1];
            int idc3 = *(int*)Args[2];
            int inc = *(int*)Args[3];
            RECT r1 = cv.CNTRECT[idc2], r2 = cv.CNTRECT[idc3];
            RECT r = {r2.left-r1.left,r2.top-r1.top,r2.right-r1.left,r2.bottom-r1.top};
            if(orient == CS_BG_HORIZONTAL)
            {
                int dx = r2.left-r1.left;
                if((dx<0))
                {
                    MoveWindow(cv.CNTLIST[idc3],r.left+inc,r.top,r.right-r.left, r.bottom-r.top,0);
                }
                else if((dx>0))
                {
                    cv.cp[idc3]->AutoTransform.InitialRect = r;
                    cv.cp[idc3]->AutoTransform.FinalRect = {-dx,0,0,0};
                    cv.AUTOTRANSCOUNT[idc3] = 0;
                }
            }
            else
            {
                int dy = r2.top-r1.top;
                if(dy<0)
                {
                    MoveWindow(cv.CNTLIST[idc3],r.left,r.top+inc,r.right-r.left, r.bottom-r.top,0);
                }
                else if(dy>0)
                {
                    cv.cp[idc3]->AutoTransform.InitialRect = r;
                    cv.cp[idc3]->AutoTransform.FinalRect = {0,-dy,0,0};
                    cv.AUTOTRANSCOUNT[idc3] = 0;
                }
            }
        }
    }
}

/*************************************************************/
void holdOnNextBtn(csARGS Args)
{
    //if((GetAsyncKeyState(VK_LBUTTON)<0 && cv.HWNDCAPTURE==(HWND)Args)
        //|| )
    {
        if((*(bool*)Args[4] || (GET_WHEEL_DELTA_WPARAM(WPARAM(Args))>0)) && cv.HWNDCAPTURE==(HWND)Args)
        {
            bool orient = *(bool*)Args[0];
            int idc2 = *(int*)Args[1];
            int idc3 = *(int*)Args[2];
            int inc = *(int*)Args[3];
            RECT r1 = cv.CNTRECT[idc2], r2 = cv.CNTRECT[idc3];
            RECT r = {r2.left-r1.left,r2.top-r1.top,r2.right-r1.left,r2.bottom-r1.top};
            if(orient == CS_BG_HORIZONTAL)
            {
                if((r2.right>r1.right))
                {//std::cout<<idc3;
                    MoveWindow(cv.CNTLIST[idc3],r.left-inc,r.top,r.right-r.left, r.bottom-r.top,0);
                }
                else if(r2.right<r1.right && r2.left<r1.left)
                {
                    cv.cp[idc3]->AutoTransform.InitialRect = r;
                    cv.cp[idc3]->AutoTransform.FinalRect = {r1.right-r2.right,0,0,0};
                    cv.AUTOTRANSCOUNT[idc3] = 0;
                }
            }
            else
            {
                if((r2.bottom>r1.bottom))
                {
                    MoveWindow(cv.CNTLIST[idc3],r.left,r.top-inc,r.right-r.left, r.bottom-r.top,0);
                }
                else if(r2.bottom<r1.bottom && r2.top<r1.top)
                {
                    cv.cp[idc3]->AutoTransform.InitialRect = r;
                    cv.cp[idc3]->AutoTransform.FinalRect = {0,r1.bottom-r2.bottom,0,0};
                    cv.AUTOTRANSCOUNT[idc3] = 0;
                }
            }
        }
    }
}

void dblclickOnPrevBtn(csARGS Args)
{
    bool orient = *(bool*)Args[0];
    int idc2 = *(int*)Args[1];
    int idc3 = *(int*)Args[2];
    int inc = *(int*)Args[3] * 5;
    RECT r1 = cv.CNTRECT[idc2], r2 = cv.CNTRECT[idc3];
    RECT r = {r2.left-r1.left,r2.top-r1.top,r2.right-r1.left,r2.bottom-r1.top};
    if(orient == CS_BG_HORIZONTAL)
    {
        int dx = r2.left-r1.left;
        if((dx<0))
        {
            cv.cp[idc3]->AutoTransform.InitialRect = r;
            cv.cp[idc3]->AutoTransform.FinalRect = {inc,0,0,0};
            cv.AUTOTRANSCOUNT[idc3] = 0;
        }
        else if((dx>0))
        {
            cv.cp[idc3]->AutoTransform.InitialRect = r;
            cv.cp[idc3]->AutoTransform.FinalRect = {-dx,0,0,0};
            cv.AUTOTRANSCOUNT[idc3] = 0;
        }
    }
    else
    {
        int dy = r2.top-r1.top;
        if(dy<0)
        {
            cv.cp[idc3]->AutoTransform.InitialRect = r;
            cv.cp[idc3]->AutoTransform.FinalRect = {0,inc,0,0};
            cv.AUTOTRANSCOUNT[idc3] = 0;
        }
        else if(dy>0)
        {
            cv.cp[idc3]->AutoTransform.InitialRect = r;
            cv.cp[idc3]->AutoTransform.FinalRect = {0,-dy,0,0};
            cv.AUTOTRANSCOUNT[idc3] = 0;
        }
    }

}

void dblclickOnNextBtn(csARGS Args)
{
    bool orient = *(bool*)Args[0];
    int idc2 = *(int*)Args[1];
    int idc3 = *(int*)Args[2];
    int inc = *(int*)Args[3] * 5;
    RECT r1 = cv.CNTRECT[idc2], r2 = cv.CNTRECT[idc3];
    RECT r = {r2.left-r1.left,r2.top-r1.top,r2.right-r1.left,r2.bottom-r1.top};
    if(orient == CS_BG_HORIZONTAL)
    {
        if((r2.right>r1.right))
        {
            cv.cp[idc3]->AutoTransform.InitialRect = r;
            cv.cp[idc3]->AutoTransform.FinalRect = {-inc,0,0,0};
            cv.AUTOTRANSCOUNT[idc3] = 0;
        }

        else if(r2.right<r1.right && r2.left<r1.left)
        {
            cv.cp[idc3]->AutoTransform.InitialRect = r;
            cv.cp[idc3]->AutoTransform.FinalRect = {r1.right-r2.right,0,0,0};
            cv.AUTOTRANSCOUNT[idc3] = 0;
        }
    }
    else
    {
        if((r2.bottom>r1.bottom))
        {
            cv.cp[idc3]->AutoTransform.InitialRect = r;
            cv.cp[idc3]->AutoTransform.FinalRect = {0,-inc,0,0};
            cv.AUTOTRANSCOUNT[idc3] = 0;
        }

        else if(r2.bottom<r1.bottom && r2.top<r1.top)
        {
            cv.cp[idc3]->AutoTransform.InitialRect = r;
            cv.cp[idc3]->AutoTransform.FinalRect = {0,r1.bottom-r2.bottom,0,0};
            cv.AUTOTRANSCOUNT[idc3] = 0;
        }
    }
}

void next_mouseWheel(csARGS Args)
{
    bool oreint = *(bool*)Args[4];
    if(GET_WHEEL_DELTA_WPARAM(WPARAM(Args))>0)
    {

    }
    else
    {

    }
}

void unlock(csARGS Args)
{
    int active = *(int*)Args[0];
    if(active != int(Args))
    {
        cv.cp[active]->LockedMode.Locked = 0;
        cv.cp[active]->LockedMode.LockingActivated = 0;
        cv.cp[active]->LockedMode.ExtBool = 1;
        InvalidateRect(cv.CNTLIST[active], 0,1);
        *(int*)Args[0] = int(Args);
    }
}

void SideBtnPos(csARGS Args)
{
    int sideBtnLength = *(int*)Args[0];
    int marg = *(int*)Args[1];
    int idc2 = *(int*)Args[2];
    int idPrevBtn = *(int*)Args[3];
    int idNextBtn = *(int*)Args[4];
    int captlen = *(int*)Args[5];
    bool orient = *(bool*)Args[6];

    RECT* rs1 = (RECT*)Args[7];
    RECT* rs2 = (RECT*)Args[8];
    RECT* rid2 = (RECT*)Args[9];
    RECT r;
    GetClientRect((HWND)Args, &r);
    if(orient == CS_BG_HORIZONTAL)
    {
        int x = marg+sideBtnLength, len = r.right-x;
        *rs1 = {marg+captlen, marg, sideBtnLength,r.bottom-2*marg};
        *rs2 = {len, marg, sideBtnLength,rs1->bottom};
        *rid2 = {rs1->right+rs1->left+2, rs1->top, r.right-2*x-captlen-4,rs1->bottom};
    }
    else
    {
        int y = marg+sideBtnLength, len = r.bottom-y;
        *rs1 = {marg, marg+captlen ,r.right-2*marg, sideBtnLength};
        *rs2 = {marg, len, rs1->right, sideBtnLength};
        *rid2 = {rs1->left, rs1->bottom+rs1->top+2, rs1->right, r.bottom-2*y-captlen-4};
    }
    SendMessage(csHWND(idPrevBtn), WM_TIMER, 0,0);
    SendMessage(csHWND(idNextBtn), WM_TIMER, 0,0);
    SendMessage(csHWND(idc2), WM_TIMER, 0,0);
    frameButton_size(Args);
}

void pos_timer(csARGS Args)
{
    RECT* r = (RECT*)Args[0];
    if(r->left)
    {
        SetWindowPos((HWND)Args,HWND_TOP,r->left, r->top, r->right, r->bottom,SWP_NOZORDER);
        *r = {0,0,0,0};
    }
}

void normalMove(csARGS Args)
{
    int idc1 = *(int*)Args[0];
    if((WPARAM)Args == MK_LBUTTON)
    {
        RECT r = rectInParentRef(idc1);
        SetWindowPos(cv.CNTLIST[idc1],HWND_BOTTOM,r.left+cv.phit0.x-cv.TRACKING_POINT.x,
                                    r.top+cv.phit0.y-cv.TRACKING_POINT.y,0,0, SWP_NOSIZE|SWP_NOZORDER);
    }
}

void smoothMove(csARGS Args)
{
    if(cv.LBTN_CONTROL && cv.HWNDCAPTURE==(HWND)Args)
    {
        int idc1 = *(int*)Args[0];
        RECT r = rectInParentRef(idc1);
        cv.cp[idc1]->AutoTransform.Type=AUTO_TRANSF_LENGTH;
        cv.cp[idc1]->AutoTransform.Time=5;
        cv.cp[idc1]->AutoTransform.InitialRect=r;
        cv.cp[idc1]->AutoTransform.FinalRect={cv.phit0.x-cv.lbtndownPoint.x,
                                    cv.phit0.y-cv.lbtndownPoint.y, 0,0};
        cv.AUTOTRANSCOUNT[idc1]=0;
        cv.LBTN_CONTROL = 0;
    }
}

void makePrison(csARGS Args)
{
    int id = int(Args);
    RECT r = cv.CNTRECT[id];
    int idc1 = *(int*)Args[0];
    int xmarging = *(int*)Args[1];
    int ymarging = *(int*)Args[2];
    cv.cp[idc1]->XMaxTrackPosition = r.right-xmarging;
    cv.cp[idc1]->YMaxTrackPosition = r.bottom-ymarging;
}

void frameButton_btnup(csARGS Args)
{
    int idc2 = *(int*)Args[0];
    int idc3 = *(int*)Args[1];
    int idb = int(Args);
    bool orient = *(bool*)Args[2];
    RECT rb = cv.CNTRECT[idb], r2 = cv.CNTRECT[idc2];
    if(orient==CS_BG_HORIZONTAL)
    {
        int dx=r2.left-rb.left;
        int cx=r2.right-rb.right;
        if(dx>0)
        {
            cv.cp[idc3]->AutoTransform.Type=AUTO_TRANSF_LENGTH;
            cv.cp[idc3]->AutoTransform.Time=5;
            cv.cp[idc3]->AutoTransform.InitialRect=rectInParentRef(idc3);
            cv.cp[idc3]->AutoTransform.FinalRect={dx,0,0,0};
            cv.AUTOTRANSCOUNT[idc3]=0;
        }
        else if(cx<0 && dx!=0)
        {
            cv.cp[idc3]->AutoTransform.Type=AUTO_TRANSF_LENGTH;
            cv.cp[idc3]->AutoTransform.Time=5;
            cv.cp[idc3]->AutoTransform.InitialRect=rectInParentRef(idc3);
            cv.cp[idc3]->AutoTransform.FinalRect={cx,0,0,0};
            cv.AUTOTRANSCOUNT[idc3]=0;
        }

    }
    else
    {
        int dy=r2.top-rb.top;
        int cy=r2.bottom-rb.bottom;
        if(dy>0)
        {
            cv.cp[idc3]->AutoTransform.Type=AUTO_TRANSF_LENGTH;
            cv.cp[idc3]->AutoTransform.Time=5;
            cv.cp[idc3]->AutoTransform.InitialRect=rectInParentRef(idc3);
            cv.cp[idc3]->AutoTransform.FinalRect={0,dy,0,0};
            cv.AUTOTRANSCOUNT[idc3]=0;
        }
        else if(cy<0 && dy!=0)
        {
            cv.cp[idc3]->AutoTransform.Type=AUTO_TRANSF_LENGTH;
            cv.cp[idc3]->AutoTransform.Time=5;
            cv.cp[idc3]->AutoTransform.InitialRect=rectInParentRef(idc3);
            cv.cp[idc3]->AutoTransform.FinalRect={0,cy,0,0};
            cv.AUTOTRANSCOUNT[idc3]=0;
        }
    }
}

void frameButton_size(csARGS Args)
{
    int idc2 = *(int*)Args[2];
    int idc3 = *(int*)Args[10];
    int idb = int(Args);
    bool orient = *(bool*)Args[5];
    int marg3 = *(int*)Args[11];
    RECT r3 = cv.CNTRECT[idc3], r2 = cv.CNTRECT[idc2];
    if(orient==CS_BG_HORIZONTAL)
    {
        int dx=r3.left-r2.left;
        int cx=r3.right-r2.right;
        if(cx<0 && dx<0)
        {
            int d = dx-cx;
            if(d<0)
            {
                SetWindowPos(cv.CNTLIST[idc3], HWND_TOP, d, marg3 ,0,0, SWP_NOSIZE|SWP_NOZORDER);
            }
            else
                SetWindowPos(cv.CNTLIST[idc3], HWND_TOP, 0, marg3 ,0,0, SWP_NOSIZE|SWP_NOZORDER);
        }
        else
            SetWindowPos(cv.CNTLIST[idc3], HWND_TOP, 0, marg3 ,0,0, SWP_NOSIZE|SWP_NOMOVE);
    }
    else
    {
        int dy=r3.top-r2.top;
        int cy=r3.bottom-r2.bottom;
        if(cy<0 && dy<0)
        {
            int d = dy-cy;
            if(d<0)
                SetWindowPos(cv.CNTLIST[idc3], HWND_TOP, marg3, d ,0,0, SWP_NOSIZE|SWP_NOZORDER);
            else
                SetWindowPos(cv.CNTLIST[idc3], HWND_TOP, marg3, 0 ,0,0, SWP_NOSIZE|SWP_NOZORDER);
        }
        else
            SetWindowPos(cv.CNTLIST[idc3], HWND_TOP, marg3, 0 ,0,0, SWP_NOSIZE|SWP_NOMOVE);
    }
}

void autoHideSideButtons(csARGS Args)
{
    int idc2 = *(int*)Args[0];
    int idc3 = *(int*)Args[1];
    int ids1 = *(int*)Args[2];
    int ids2 = *(int*)Args[3];
    int marg = *(int*)Args[4];
    int moverLen = *(int*)Args[5];
    int sideBtnLen = *(int*)Args[6];
    bool orient = *(bool*)Args[7];
    bool* b0 = (bool*)Args[8];
    RECT r2 = cv.CNTRECT[idc2], r3 = cv.CNTRECT[idc3], r1 = cv.CNTRECT[int(Args)];
    RECT r2s = cv.CNTRECT_SAVED[idc2];
    bool b = (r2.right-r2.left > r3.right-r3.left);

    if(b)
    {
        if (!*b0)
        //if(IsWindowVisible(cv.CNTLIST[ids1]))
        {
            //RECT rs1 = rectInParentRef(ids1);
            //RECT rs2 = rectInParentRef(ids2);
            //cv.cp[ids1]->AutoTransform.InitialRect=rs1;
            //cv.cp[ids2]->AutoTransform.InitialRect=rs2;
            //cv.cp[idc2]->AutoTransform.InitialRect={r2.left-r1.left, r2.top-r1.top, r2.right-r1.left, r2.bottom-r1.top};
            if(orient == CS_BG_HORIZONTAL)
            {
                //cv.cp[ids1]->AutoTransform.FinalRect={0,-r2.bottom*2,0,0};
                //cv.cp[ids2]->AutoTransform.FinalRect={0,-r2.bottom*2,0,0};
                //cv.cp[idc2]->AutoTransform.FinalRect={0,0,0,0};
                MoveWindow(cv.CNTLIST[idc2], marg+moverLen, marg, r1.right-r1.left-2*marg/*-moverLen*/,csCLRECT(idc2).bottom,1);
            }
            else
            {
                //cv.cp[ids1]->AutoTransform.FinalRect={-r2.right*2,0,0,0};
                //cv.cp[ids2]->AutoTransform.FinalRect={-r2.right*2,0,0,0};
                MoveWindow(cv.CNTLIST[idc2], marg, marg+moverLen, csCLRECT(idc2).right, r1.bottom-r1.top-2*marg/*-moverLen*/,1);
            }
            //cv.AUTOTRANSCOUNT[ids1] = 1;
            //cv.AUTOTRANSCOUNT[ids2] = 1;
            //cv.AUTOTRANSCOUNT[idc2] = 1;
            ShowWindow(cv.CNTLIST[ids1],0);
            ShowWindow(cv.CNTLIST[ids2],0);
            *b0 = 1;
        }
    }
    else
    {
        if (*b0)
        {
            std::cout<<r2.left-r1.left<<"\n";
            //RECT rs1 = rectInParentRef(ids1);
            //RECT rs2 = rectInParentRef(ids2);
            //cv.cp[ids1]->AutoTransform.InitialRect=rs1;
            //cv.cp[ids2]->AutoTransform.InitialRect=rs2;
            //cv.cp[idc2]->AutoTransform.InitialRect={r2.left-r1.left, r2.top-r1.top, r2.right-r1.left, r2.bottom-r1.top};
            ShowWindow(cv.CNTLIST[ids1],1);
            ShowWindow(cv.CNTLIST[ids2],1);
            if(orient == CS_BG_HORIZONTAL)
            {
                MoveWindow(cv.CNTLIST[idc2], marg+sideBtnLen+moverLen, marg, r1.right-r1.left-2*(marg+sideBtnLen)-moverLen,csCLRECT(idc2).bottom,1);
                //cv.cp[ids1]->AutoTransform.FinalRect={0,r2.bottom*2,0,0};
                //cv.cp[ids2]->AutoTransform.FinalRect={0,r2.bottom*2,0,0};
                //cv.cp[idc2]->AutoTransform.FinalRect={0,0,0,0};
            }
            else
            {
                //cv.cp[ids1]->AutoTransform.FinalRect={r2.right*2,0,0,0};
                //cv.cp[ids2]->AutoTransform.FinalRect={r2.right*2,0,0,0};
                MoveWindow(cv.CNTLIST[idc2], marg, marg+sideBtnLen+moverLen,csCLRECT(idc2).right, r1.bottom-r1.top-2*(marg+sideBtnLen)-moverLen,1);
            }
            //cv.AUTOTRANSCOUNT[ids1] = 1;
            //cv.AUTOTRANSCOUNT[ids2] = 1;
            //cv.AUTOTRANSCOUNT[idc2] = 1;
            *b0 = 0;
        }
    }
}

void csReachLast(csARGS Args)
{
    int id = int(Args);
    int idc2 = *(int*)Args[0];
    int idc3 = *(int*)Args[1];
    bool orient = *(bool*)Args[2];
    RECT r2 = cv.CNTRECT[idc2], r3 = cv.CNTRECT[idc3];
    int dx = r2.right-r3.right;
    int dy = r2.bottom-r3.bottom;
    cv.cp[idc3]->AutoTransform.InitialRect={-r2.left+r3.left, -r2.top+r3.top, -r2.left+r3.right, -r2.top+r3.bottom};
//std::cout<<dx<<"  dx\n";
    if(orient == CS_BG_HORIZONTAL)
    {
        if(dx < 0)
        {
            cv.cp[idc3]->AutoTransform.FinalRect={dx,0,0,0};
            cv.AUTOTRANSCOUNT[idc3] = 0;
        }
    }
    else
    {
        if(dy < 0)
        {
            cv.cp[idc3]->AutoTransform.FinalRect={0,dy,0,0};
            cv.AUTOTRANSCOUNT[idc3] = 0;
        }
    }
}

void csReachFirst(csARGS Args)
{
    int id = int(Args);
    int idc2 = *(int*)Args[0];
    int idc3 = *(int*)Args[1];
    bool orient = *(bool*)Args[2];
    RECT r2 = cv.CNTRECT[idc2], r3 = cv.CNTRECT[idc3];
    int dx = r2.left-r3.left;
    int dy = r2.top-r3.top;
    cv.cp[idc3]->AutoTransform.InitialRect={-r2.left+r3.left, -r2.top+r3.top, -r2.left+r3.right, -r2.top+r3.bottom};

    if(orient == CS_BG_HORIZONTAL)
    {
        if(dx > 0)
        {
            cv.cp[idc3]->AutoTransform.FinalRect={dx,0,0,0};
            cv.AUTOTRANSCOUNT[idc3] = 0;
        }
    }
    else
    {
        if(dy > 0)
        {
            cv.cp[idc3]->AutoTransform.FinalRect={0,dy,0,0};
            cv.AUTOTRANSCOUNT[idc3] = 0;
        }
    }
}
extern HWND TRACKED_HWND;
void popup_life(csARGS Args)
{
    int id=(int)Args;
    csTEXTBUTTON*idbtn = (csTEXTBUTTON*)Args[0];
    unsigned n = *(unsigned*)Args[1];
    if(cv.BHOOK_LBUTNDOWN_POPUP)
    {
        if(IsWindowVisible(cv.CNTLIST[id]))
        {
            bool b = 1;
            for(unsigned i=0; i<n; i++)
            {
                if(TRACKED_HWND == cv.CNTLIST[idbtn[i].getId()])
                {
                    b = 0;
                    break;
                }
            }
            if(b)
                ShowWindow(cv.CNTLIST[id],0);
        }
        cv.BHOOK_LBUTNDOWN_POPUP=0;
    }

}

void onClic(csARGS Args)
{
    int popup = *(int*)Args[0];
    if(cv.cp[popup]->Show == 0)
        cv.cp[popup]->Show = 1;
    else
        cv.cp[popup]->Show = 0;
}

