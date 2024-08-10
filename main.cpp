#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <thread>
#include "csCONTAINER.h"
#include "sbar.h"
#include "DefaultCont.h"
#include "csGRID.h"
#include "csBUTTON.h"
#include "csBUTTON_GROUP.h"
//#include "shapefil.h"
#include "csRADIOBUTTON.h"
#include "LinearAlgebra.h"
#include "csBUTTONGRID.h"
#include "utlFx.h"
#include "csCOLORPALETTE.h"
#include "csSCROLLBAR.h"
#include "csSYSCMD.h"
#include "csVLC.h"
#include "csHLC.h"
#include "appMenu.h"

using namespace std;

extern MSG Messages;
csCONTAINER csc;
csCNTR_PARAMS cscp;
csPOLYLINE_PARAMS plp;
csJOINTLINE_PARAMS jlp;
csPOLYGON_PARAMS pgp;
csCIRCLE_PARAMS crp;
csSURFACE srf, *psrf, srf0, rsfr;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
int dynamicCnt(csCNTR_PARAMS& cscp, int idp, char*title, RECT geometry);
int staticCnt(csCNTR_PARAMS& cscp, int idp, char*title, RECT geometry);
//int staticCnt2(csCNTR_PARAMS& cscp, int idp, char*title, csRGBA color, RECT geometry, bool show=1);
int editBox(csCNTR_PARAMS& cscp, int idp, char*title, char*dflt, RECT geometry,
            int*idbtns=0, int*SameDesignCnts=0, int textPos = 0, bool withControlers=1);

int*window_with_menu_caption(HINSTANCE hThisInstance);
//csLIST<csCNTR_PARAMS*> cpptr = getCntParamsPointer();
extern csCNTR_VARS cv;
int* Hmove;
int* h4, *h5;
HINSTANCE* Hinst;
void menuSizeSinc(csARGS Args);
void autoResizeLayers_base(csARGS Args);
void autoResizeLayers_client(csARGS Args);
void autoResizeCTBG(csARGS Args);

void resizeSys(csARGS Args);
void resizeClient(csARGS Args);
void _resizeSys(csARGS Args);
void _resizeClient(csARGS Args);

void _deleteGridContainer(csARGS Args);
void calculate(csARGS Args);
int* tabbed(csCNTR_PARAMS& cscp, int id_btn_cnt, int id_client_cnt, RECT geometry,
            int*&btn,csPAGEFLIPPING_VARS*&hs, int*&N);

int* simpleApp(int idpar);
void simpleAppFunc(csARGS Args);

int* csRealtimeDrawing(int& idCanvas, int& idboard, int& idmousepos, csBUTTONGRID*subMenus);
void cvContainer(csARGS Args);
int myCVContainer();


int HWNDSIZING = 0;

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{

    cv.DESTROY_ITER = -1; //tres important
    cv.REID_ITER = -1; //tres important
    initLists(200);
//    csLIST<int> lst;
//    lst.insertTableAt((int*)(2,5,87),0,3);
//    lst.printAll();
    Hinst = &hThisInstance;
    initContParams(cscp);
    cscp.Hinstance=hThisInstance;
    cscp.Geometry= {200,25,1000,600};
    cscp.MaxSize = {(unsigned)CS_CXSCREEN,(unsigned)CS_CYSCREEN-hauteurBarreDeTache()};
    cscp.MinMaxStyle=1;
    cscp.ClingToParent=1;
    cscp.CaptionDirection=1;
    cscp.CaptionAreaLength=30;
    cscp.CaptionAreaPos=1;
    cscp.HTTop=1;
    cscp.HTRight=1;
    cscp.HTLeft=1;
    cscp.HTBottom=1;
    cscp.HTCorner = 1;
    cscp.SizingAreaLength=5;
    cscp.Show=1;
    cscp.Transparency=0;
    cscp.SizingParams= {0,0,0,0};
    //cscp.BackgroundImage = "img\\bkg1.bmp";
    //cscp.BackgroundImage = "img\\app\\sbkg0.bmp";
    cscp.DCSizes = {(unsigned)CS_CXSCREEN,(unsigned)CS_CYSCREEN*1.5};
    cscp.BackgroundColor= {50,50,50};
    cscp.Title.Text="SHAPER";
    cscp.Title.Bold=1;
    cscp.Title.FontSize= {5,0};
    cscp.Title.Font="Bauhaus 93";
    cscp.Title.Color= {255,255,255};
    int h1=csc.csCNT_newContainer(0, cscp);
    //csSetBackgroundImage(h1,"img\\app\\sbkg1.bmp",{(unsigned)CS_CXSCREEN,(unsigned)CS_CYSCREEN*2});

    //SetWindowLong(cv.CNTLIST[h1],GWL_STYLE,GetWindowLong(cv.CNTLIST[h1], GWL_STYLE)|WS_CAPTION);

    //csSetAction(h1, WM_TIMER, cntshow, 0);

    //int idSys = staticCnt2(cscp, h1, "", {60,60,60},{545,0,50,25},1);
    int idSys = staticCnt2(cscp, h1, "", {30,30,30},{425,3,50,50},1);


    char*btnclose1="img\\app\\Sys\\close1.bmp";
    char*btnclose2="img\\app\\Sys\\close2.bmp";
    csRGBA btn_color = {15,15,15};
    RECT marg = {1,1,2,2};
    //int btnclose = imgButton(cscp, idSys, btnclose2, btnclose1,0, {25,0,25,25},marg, btn_color);
    int btnclose = imgButton(cscp, idSys, btnclose1, btnclose2,0, {25,0,25,25},marg, btn_color);
    csSetAction(btnclose, WM_LBUTTONUP, closeApp, 0);
    char*btnmin1="img\\app\\Sys\\min2.bmp";
    char*btnmin2="img\\app\\Sys\\min1.bmp";
    //int btnmin = imgButton(cscp, idSys, btnmin1, btnmin2,0, {0,0,25,25}, marg, btn_color);
    int btnmin = imgButton(cscp, idSys, btnmin1, btnmin2,0, {0,0,25,25}, marg, btn_color);
    int btncolors = imgButton(cscp, idSys, "img\\app\\Sys\\colors2.bmp", "img\\app\\Sys\\colors1.bmp",0, {0,25,25,25}, marg, btn_color);
    int btnmax = imgButton(cscp, idSys, "img\\app\\Sys\\max1.bmp", "img\\app\\Sys\\max2.bmp",0, {25,25,25,25}, marg, btn_color);
    bool bool_btmin = 0;
    //csSetAction(btnmin, WM_TIMER, holdingLbtn, 0);
    minimizeCnt(btnmin, h1);
    restoreCnt(h1);


    initContParams(cscp);
    cscp.Hinstance=hThisInstance;
    cscp.Geometry= {5,55,cv.cp[h1]->Geometry.right-10,cv.cp[h1]->Geometry.bottom-60};
    cscp.MinMaxStyle=1;
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.Transparency=0;
    cscp.BackgroundColor= {70,70,70};
    cscp.MouseLeaveRemoveBkg = 0;
    cscp.Title.Text="";
    cscp.MHGradient.GradientType = 0;
    cscp.MHGradient.GradientNumber = 3;
    cscp.MHGradient.TimeStep = 3;
    cscp.MHGradient.Color1 = {70,70,70};
    cscp.MHGradient.Color2 = {60,60,60};
    cscp.MouseHoverTime = 3;
    /*cscp.AutoAlphaFade.Geometry = {-30,0,0,0};
    cscp.AutoAlphaFade.FadeTime = 8;
    cscp.AutoAlphaFade.AlphaMin = 50;
    cscp.AutoAlphaFade.Activate = 0;
    cscp.AutoAlphaFade.ShowHide = 1;*/
    int h2 = csc.csCNT_newContainer(h1, cscp);
    HWNDSIZING = h2;

    int* tabbtn=0, *N_tab=0, *page=0;
    csPAGEFLIPPING_VARS*hs;
    page = tabbed(cscp, h1, h2, {0,0,CS_CXSCREEN,CS_CYSCREEN}, tabbtn, hs, N_tab);
    int hedit = editBox(cscp, page[1],"Test","0", {2,2,200,40});
    int tb = textButton(cscp, page[1], "destroyer", {220,220,220}, {205,7,100,25});
    csSetAction(tb, WM_LBUTTONUP, destroyContainer_Init, 1, &hedit);

    //cout<<"test id : "<<tabbtn<<"\n";
    /*SetParent(cv.CNTLIST[tabbtn[3]], cv.CNTLIST[idSys]);
    SetParent(cv.CNTLIST[tabbtn[4]], cv.CNTLIST[idSys]);
    SetWindowPos(cv.CNTLIST[tabbtn[3]], 0,0,0,0,0,SWP_NOSIZE);
    SetWindowPos(cv.CNTLIST[tabbtn[4]], 0,60,0,0,0,SWP_NOSIZE);*/
    HRGN reg = CreateRoundRectRgn(0,0,90,25,10,10);
    //InvertRgn(cv.CTX[tb].getDC(), reg);
    csSetAction(tb, WM_CREATE, csApplyRegion, 1, &reg);
    csSetAction(tb, WM_MOVE, csApplyRegion, 1, &reg);
    int tb1 = imgButton2(cscp, page[1], "img\\circle1.bmp", "img\\circle2.bmp",0,
                         {0,100,150,100},{0}, {0,0,0},0,1);
    /*RGNDATA*pData;
    HGLOBAL hData;
    int nReg = 2, type=RGN_DIFF;
    HRGN* region = (HRGN*)malloc(nReg*sizeof(HRGN));
    region[0]= CreateRectRgn(0,0,100,25);
    region[1]= CreateRoundRectRgn(0,0,100,25,10,10);
    HRGN regcmb = 0;
    csSetAction(tb1, WM_CREATE, csSetRegionCombiner, 2, pData,&hData,&nReg);
    csSetAction(tb1, WM_CREATE, csCombineRegion, 5, &regcmb,pData,region,&nReg,&type);
    //csSetAction(tb1, WM_CREATE, csApplyRegion, 1, &regcmb);
    csSetAction(tb1, WM_SIZE, csCombineRegion, 5, &regcmb,pData,region,&nReg,&type);
    //InvertRgn(cv.CTX[tb1].getDC(), reg1);
    csSetAction(tb1, WM_SIZE, csApplyRegion, 1, &regcmb);*/

    UINT msg;


    csGRID grid1(page[2],{20,30,500,200},{7,7});
    int gbtn[10];
    gbtn[0] = textButton(cscp, page[2], "Button 1", {220,220,220}, grid1.newGeometry({1,1},{0}));
    gbtn[1] = textButton(cscp, page[2], "Button 2", {220,220,220}, grid1.newGeometry({1,1}));
    gbtn[2] = textButton(cscp, page[2], "Button 3", {220,220,220}, grid1.newGeometry({1,1}));
    gbtn[3] = textButton(cscp, page[2], "Button 4", {220,220,220}, grid1.newGeometry({1,1}));
    gbtn[4] = textButton(cscp, page[2], "Button 5", {220,220,220}, grid1.newGeometry({1,1}));
    gbtn[5] = textButton(cscp, page[2], "Button 6", {220,220,220}, grid1.newGeometry({1,1}));
    gbtn[6] = textButton(cscp, page[2], "Button 7", {220,220,220}, grid1.newGeometry({1,1}));
    gbtn[7] = textButton(cscp, page[2], "Button 8", {220,220,220}, grid1.newGeometry({4,1}));
    gbtn[8] = textButton(cscp, page[2], "Button 9", {220,220,220}, grid1.newGeometry({5,1}));
    grid1.newContainer(gbtn[0]);
    grid1.newContainer(gbtn[1]);
    grid1.newContainer(gbtn[2]);
    grid1.newContainer(gbtn[3]);
    grid1.newContainer(gbtn[4]);
    grid1.newContainer(gbtn[5]);
    grid1.newContainer(gbtn[6]);
    grid1.newContainer(gbtn[7]);
    grid1.newContainer(gbtn[8]);

    //grid1.deleteContainer(gbtn[5]);
    int cbtn[10]={0};
    char*btnpath51="img\\btnclose3.bmp";
    char*btnpath52="img\\btnclose2.bmp";
    cbtn[0] = imgButton(cscp, gbtn[0], btnpath51, btnpath52, 0, {0,0,8,8}, {0}, {50,30,40});
    cbtn[1] = imgButton(cscp, gbtn[1], btnpath51, btnpath52, 0, {0,0,8,8}, {0}, {50,30,40},cbtn[0]);
    cbtn[2] = imgButton(cscp, gbtn[2], btnpath51, btnpath52, 0, {0,0,8,8}, {0}, {50,30,40},cbtn[0]);
    cbtn[3] = imgButton(cscp, gbtn[3], btnpath51, btnpath52, 0, {0,0,8,8}, {0}, {50,30,40},cbtn[0]);
    cbtn[4] = imgButton(cscp, gbtn[4], btnpath51, btnpath52, 0, {0,0,8,8}, {0}, {50,30,40},cbtn[0]);
    cbtn[5] = imgButton(cscp, gbtn[5], btnpath51, btnpath52, 0, {0,0,8,8}, {0}, {50,30,40},cbtn[0]);
    cbtn[6] = imgButton(cscp, gbtn[6], btnpath51, btnpath52, 0, {0,0,8,8}, {0}, {50,30,40},cbtn[0]);
    cbtn[7] = imgButton(cscp, gbtn[7], btnpath51, btnpath52, 0, {0,0,8,8}, {0}, {50,30,40},cbtn[0]);
    cbtn[8] = imgButton(cscp, gbtn[8], btnpath51, btnpath52, 0, {0,0,8,8}, {0}, {50,30,40},cbtn[0]);
    msg=WM_LBUTTONUP;
    csSetAction(cbtn[0], msg, _deleteGridContainer, 2, &gbtn[0], &grid1);
    csSetAction(cbtn[1], msg, _deleteGridContainer, 2, &gbtn[1], &grid1);
    csSetAction(cbtn[2], msg, _deleteGridContainer, 2, &gbtn[2], &grid1);
    csSetAction(cbtn[3], msg, _deleteGridContainer, 2, &gbtn[3], &grid1);
    csSetAction(cbtn[4], msg, _deleteGridContainer, 2, &gbtn[4], &grid1);
    csSetAction(cbtn[5], msg, _deleteGridContainer, 2, &gbtn[5], &grid1);
    csSetAction(cbtn[6], msg, _deleteGridContainer, 2, &gbtn[6], &grid1);
    csSetAction(cbtn[7], msg, _deleteGridContainer, 2, &gbtn[7], &grid1);
    csSetAction(cbtn[8], msg, _deleteGridContainer, 2, &gbtn[8], &grid1);


    int popup = staticCnt2(cscp, 0, "Infos", {40,40,40},{0,0,200,400},0);
    SetParent(cv.CNTLIST[popup],0);
    //cv.cp[popup]->CursorTracking.AllowCursorTracking=1;

    csPAGES* Menu = menu(h1);
    int cvCnt = myCVContainer();
    csSetAction(Menu->getPage(0)->getId(), WM_LBUTTONUP, cvContainer, 2, Menu->getPage(0), &cvCnt);

/*************************************************/

    int parCaption = staticCnt2(cscp, h1, "", {40,40,40},{480,3,170,25},1);
    cv.cp[parCaption]->CaptionDirection=1;
    cv.cp[parCaption]->CaptionAreaLength=30;
    cv.cp[parCaption]->CaptionAreaPos=1;
    cv.cp[parCaption]->MouseLeaveRemoveBkg=1;
    SetWindowLong(cv.CNTLIST[parCaption],GWL_EXSTYLE,GetWindowLong(cv.CNTLIST[parCaption], GWL_EXSTYLE)|WS_EX_TRANSPARENT);
    csSetBackgroundImage(parCaption,"img\\app\\TITLE2.bmp",{170,25});

    //cv.CTX[parCaption].setCntBorder({100,100,100}, 2);
    void move_h1_1(csARGS Args);
    void move_h1_2(csARGS Args);
    bool* bll = (bool*)malloc(sizeof(bool));
    *bll = 0;
    csSetAction(parCaption,WM_MOVE, move_h1_1, 1, bll);
    csSetAction(parCaption,WM_MOUSEMOVE, move_h1_2, cv.cp[parCaption]->CntEventsFunc.MOVE_ARGS[0]);

    cv.cp[page[4]]->HTRight=1;
    cv.cp[page[4]]->SizingAreaLength=5;
    //cv.cp[page[4]]->MouseLeaveRemoveBkg=1;

    int bottomBar = staticCnt2(cscp, h1, "", {25,25,25},{0},1);
    int level = 4;
    float sharp = 1;
    cv.CTX[bottomBar].setCntBorder({25,25,25},1);
    cv.CTX[bottomBar].borderGradientColor = csTint(csPARAMS(bottomBar)->BackgroundColor, {0}, .3);
    cv.CTX[bottomBar].brdGrad_top = {level,3,0,0,sharp};
    SetTimer(cv.CNTLIST[bottomBar], 0, 27, 0);


    int board = staticCnt2(cscp, page[3], "", {50,50,50},{0,0,200,700},1);

    csSCROLLBAR hscroll(page[3], {210,1,400,9});
    hscroll.mouseLeaveHide(10);
    cv.CTX[page[3]].hScrollBarId = hscroll.getId();
    SetTimer(cv.CNTLIST[hscroll.getId()],0,18,0);

    csSCROLLBAR vscroll(page[3], {201,0,9,400}, 1, CS_SBAR_VERTICAL);
    vscroll.mouseLeaveHide(10);
    cv.CTX[page[3]].vScrollBarId = vscroll.getId();
    SetTimer(cv.CNTLIST[vscroll.getId()],0,18,0);

    int linkType = GLINK_SIZE;
    int linkType1 = GLINK_POSITION;
    int area = CSA_RIGHT, area2 = CSA_BOTTOM;
    int n_arg = 3;
    int sz1=0, sz2=0;
    SIZE sz3 = {0}, szctbg1={0};
    RECT rctbg2={0};
    RECT rbb={0};
    RECT rboard={0};
    int hscrollLen=0, vscrollLen=0;
    void autoMoveChilds(csARGS Args);

    csSetAction(h1,WM_SIZE, autoResizeLayers_base, 19, &idSys, &h2,
             Menu->getIndexerBGroup()->getIDPtr(), Menu->getPagesBGroup()->getIDPtr(), &parCaption, bll,
              &sz1, &sz2, &sz3, &rctbg2, &szctbg1, &bottomBar, &rbb, hscroll.getIdPtr(), &hscrollLen,
              vscroll.getIdPtr(), &vscrollLen, &board, &rboard);

    csARGS args = cv.cp[h1]->CntEventsFunc.SIZE_ARGS[cv.cp[h1]->CntEventsFunc.SIZE_ARGS.size()-1];

    csPARAMS(Menu->getPagesBGroup()->getID())->SizingAreaLength = 2;
    csPARAMS(Menu->getPagesBGroup()->getID())->HTLeft = 1;
    csSetAction(Menu->getPagesBGroup()->getID(),WM_SIZE, menuSizeSinc, args);


    csSetAction(h2,WM_TIMER, autoMoveChilds, args);
    csSetAction(idSys,WM_TIMER, autoMoveChilds, args);
    csSetAction(parCaption,WM_TIMER, autoMoveChilds, args);
    csSetAction(Menu->getIndexerBGroup()->getID(),WM_TIMER, autoMoveChilds, args);
    csSetAction(Menu->getPagesBGroup()->getID(),WM_TIMER, autoMoveChilds, args);
    csSetAction(bottomBar,WM_TIMER, autoMoveChilds, args);
    csSetAction(hscroll.getId(),WM_TIMER, autoMoveChilds, args);
    csSetAction(vscroll.getId(),WM_TIMER, autoMoveChilds, args);
    csSetAction(board,WM_TIMER, autoMoveChilds, args);


    int* iedit = simpleApp(page[4]);

    //csSetBackgroundImage(page[4],"img\\bkg.bmp",{(unsigned)CS_CXSCREEN,(unsigned)CS_CYSCREEN+(unsigned)CS_CYSCREEN/2});
    /*csLIST<POINT> pts;
    pts.insertEnd({100, 100});
    pts.insertEnd({200, 300});
    cv.CTX[page[3]].newgdiLine(pts, RGB(255, 255, 255), 5, PS_SOLID);*/

    int idCanvas = staticCnt2(cscp, page[3], "", {30,30,30},{209,9,(unsigned)CS_CXSCREEN,(unsigned)CS_CYSCREEN},1);
    cv.CTX[idCanvas].setCntBorder(cv.cp[idCanvas]->BackgroundColor,1); //Remove border
    //csSetBackgroundImage(idCanvas,"img\\bkg.bmp",{(unsigned)CS_CXSCREEN,(unsigned)CS_CYSCREEN+(unsigned)CS_CYSCREEN/2});
    csSetTransparency(idCanvas, 5);
    //cv.cp[idCanvas]->MouseLeaveRemoveBkg=1;
    //int idCanvas = textButton(cscp, page[3], "", {30,30,36}, {212,10,(unsigned)CS_CXSCREEN,(unsigned)CS_CYSCREEN}, {0});
    //SendMessage(cv.CNTLIST[idCanvas],WM_MOUSELEAVE,0,0);

    int idshowcoords = staticCnt2(cscp, h1, "", {20,20,20},{330,3,115,25},1);
    SetWindowLong(cv.CNTLIST[idshowcoords],GWL_EXSTYLE,GetWindowLong(cv.CNTLIST[idshowcoords], GWL_EXSTYLE)|WS_EX_TRANSPARENT);
    //cv.cp[idshowcoords]->MouseLeaveRemoveBkg=1;
    cv.cp[idshowcoords]->Title.Color={200,200,200};
    cv.cp[idshowcoords]->Title.Text = (char*)malloc(20);
    cv.cp[idshowcoords]->Title.Text = (char*)malloc(20);
    cv.cp[idshowcoords]->TitleAlign = CS_TA_CENTER;

    csTEXTBUTTON coordUnit(h1,">>",{444,3,20,25});
    coordUnit.getParams()->Title.Orientation = -900;
    coordUnit.getParams()->Title.TextRect = {0};
    coordUnit.getParams()->Title.FontSize = {20,3};
    coordUnit.getParams()->TitleAlign = CS_TA_CENTER;



    int* iidd = csRealtimeDrawing(idCanvas, board, idshowcoords, Menu->getPages());

    cv.CTX[idCanvas].initExtDwg();
    cv.CTX[idCanvas].createIDSMap();

    csSetRulersTrackers(&idCanvas, {255,255,50}, 1, CS_CXSCREEN, 1,0,1,0);
    cv.CTX[idCanvas].addRulers();
    cv.CTX[idCanvas].addRulersTrackers();
    cv.CTX[idCanvas].idMask = h2; // pour le positionnement relatif des regles a droite et en bas
    cv.CTX[idCanvas].rulerRelativePosX = 0;
    cv.CTX[idCanvas].rulerRelativePosY = 0;
    csResizeUpdateClient(h2,idCanvas); // mise a jour du positionnement relatif des regles a droite et en bas

    hscroll.setClient(idCanvas,h2);
    hscroll.setPosition(0.5);
    vscroll.setClient(idCanvas,h2);
    vscroll.setPosition(0.5);


    //csAddColorFilter(ctbg2.getIDPtr(), {200,20, 200}, 7);
    //csAddColorFilter(&idSys, {255,255, 0}, 20);

    //int testSHP();
    //testSHP();
    //hsTest(page[0]);


    cv.CAPTIONER = staticCnt2(cscp, 0, 0, {20,20,20},{0,0,1,1},1);
    csDetachCnt(cv.CAPTIONER);
    cv.cp[cv.CAPTIONER]->Cursor = LoadCursor(0,IDC_SIZEALL);
    csSetTransparency(cv.CAPTIONER, 97);

    csLIST<char> list;
    list.init(5);
    char strr[20];
    sprintf(strr,"ggdfgdgdf");
    list.insertTableAt(strr, 0, strlen(strr));
    char*cret = list.toString(7,3);
    std::cout<<"cret : "<<cret<<"\n";

    csVLC vlc(&bottomBar,3,10);
    vlc.newContainer(0,20,100);
    vlc.newContainer(0,20,100);
    vlc.newContainer(0,20,100);
    vlc.newContainer(0,20,100);
    vlc.newContainer(0,20,100);

    int zoomId = vlc.getContainerId(4);
    csINCREMENTER* inc = csIncrementer(zoomId, "Zoom", 25, {2,2,200,15}, {40, 40, 40}, CNTR_DISPOSITION_HORIZONTAL);


    csSetBackgroundColor(inc->id4, {150,150,150});
    csTITLE(inc->id4, csSTR("          "), {255,255,255}, "book antiqua", FW_BOLD, 0, {12});
    csPARAMS(inc->id1)->Title.Color = {240,240,240};
    csPARAMS(inc->id2)->Title.Color = {240,240,240};
    csCTX(inc->id4).setCntBorder({150,150,150}, 1);
    csCTX(inc->id4).brdGrad_bottom.n = 0;
    csCTX(inc->id4).brdGrad_right.n = 0;

    csGeometryLink(&zoomId, 1, csGLP4_PTR({inc->id, {0,0,2}, {0,0,2}, {4,1.0,0}, {0,0,15}}));
    inc->bInit = 1;
    cv.HWNDFOCUS = cv.CNTLIST[inc->id4];
    SendMessage(csHWND(inc->id),WM_SIZE,0,0);

    csTITLE(vlc.getContainerId(0), "Progress Bar");
    csTITLE(vlc.getContainerId(1), "Active Command");
    csTITLE(vlc.getContainerId(2), "Command Input");
    csTITLE(vlc.getContainerId(3), "Canvas Tools");
    csTITLE(vlc.getContainerId(4), "Zoom");

    vlc.autoUpdate(0, 1);
    vlc.autoUpdate(1, 1);
    vlc.autoUpdate(2, 1);
    vlc.autoUpdate(3, 1);
    vlc.autoUpdate(4, 1);

    return csf_close();
}

/***** Fonction d'affichage du CV *******************/
void cvContainer(csARGS Args)
{
    csBUTTONGRID* bgCV = (csBUTTONGRID*)Args[0];
    int cvCnt = *(int*)Args[1];

    if(bgCV->getActiveItem() == 0)
    {
        if(cv.cp[cvCnt]->Show == 0)
        {
            cv.cp[cvCnt]->Show = 1;
        }
        else
        {
            cv.cp[cvCnt]->Show = 0;
        }
    }
}

int myCVContainer()
{
    int cvCnt = staticCnt2(cscp, 0, "Mon CV - AZEUFACK PHILIPPE LEVANG", {50,50,50},{CS_CXSCREEN/2-400,50,800,600},0);
    cv.cp[cvCnt]->SizingAreaLength = 5;
    cv.cp[cvCnt]->HTTop = 1;
    cv.cp[cvCnt]->HTLeft = 1;
    cv.cp[cvCnt]->HTRight = 1;
    cv.cp[cvCnt]->HTBottom = 1;
    cv.cp[cvCnt]->HTCorner = 1;
    cv.cp[cvCnt]->CaptionAreaLength = 30;
    cv.cp[cvCnt]->CaptionAreaPos = 1;
    cv.cp[cvCnt]->CaptionDirection = 1;
    cv.cp[cvCnt]->Title.Color = {255,255,255};
    cv.cp[cvCnt]->Title.Bold = FW_BOLD;
    cv.cp[cvCnt]->Title.TextRect = {0,8};

    csINCREMENTER* inc = csIncrementer(cvCnt, "Zoom", 25, {0,0,200,25}, {40, 40, 40}, CNTR_DISPOSITION_HORIZONTAL);

    int *pclient = csf_alloc2<int>(1,staticCnt2(cscp, cvCnt, "", {50,50,50},{5,35,380,450},1));
    int client = *pclient;
    SetTimer(cv.CNTLIST[client],0,10,0);

    csDetachCnt(cvCnt);

    csSCROLLBAR hscroll = csAddHScrollBar(&cvCnt, pclient, pclient, 90);
    csSCROLLBAR vscroll = csAddVScrollBar(&cvCnt, pclient, pclient, 90);
    hscroll.setScrollColors({200,200,20}, {100,100,20});

    BITMAPINFO bmi = csSetBMI({0,0});
    csBMP bmp = csBitmapFromFile("img\\app\\CV_Azeufack.bmp", &bmi);
    SIZE sz = {bmp.bm.bmWidth,bmp.bm.bmHeight};
    cv.CTX[client].setDwgSurfSize(sz);
    cv.CTX[client].xcentering = 1;
    HDC dc = cv.CTX[client].getDC();
    SetStretchBltMode(dc, HALFTONE);
    StretchBlt(dc, 0,0,sz.cx, sz.cy, bmp.dc, 0,0,bmp.bm.bmWidth,bmp.bm.bmHeight, SRCCOPY);
    InvalidateRect(cv.CNTLIST[client], 0,1);
    freeBMP(bmp);

    //cv.cp[cvCnt]->MaxTrackSize = sz;
    cv.cp[cvCnt]->MinTrackSize = {sz.cx/3, 200};
    cv.cp[cvCnt]->MinMaxStyle = 1;
    cv.cp[cvCnt]->MaxSize = {CS_CXSCREEN, CS_CYSCREEN - hauteurBarreDeTache()};

    //MoveWindow(cv.CNTLIST[cvCnt], CS_CXSCREEN/2-sz.cx,CS_CYSCREEN/2-sz.cy,sz.cx,sz.cy,1);

    void resizeCVContainer(csARGS Args);
    void autoResizeCVClient(csARGS Args);

    csARGS args(9);
    RECT *rclient = csf_alloc2<RECT>(1,{0});
    RECT *rhscroll = csf_alloc2<RECT>(1,{0});
    RECT *rvscroll = csf_alloc2<RECT>(1,{0});
    RECT *rInc = csf_alloc2<RECT>(1,{0});
    RECT *rTitle = csf_alloc2<RECT>(1,{0});
    args.makeArgs(pclient, hscroll.getIdPtr(), vscroll.getIdPtr(), &inc->id,
                  rclient, rhscroll, rvscroll, rInc, rTitle);

    csSetAction(cvCnt, WM_SIZE, resizeCVContainer, args);
    csSetAction(cvCnt, WM_TIMER, autoResizeCVClient, args);
    csSetAction(client, WM_TIMER, autoResizeCVClient, args);
    csSetAction(hscroll.getId(), WM_TIMER, autoResizeCVClient, args);
    csSetAction(vscroll.getId(), WM_TIMER, autoResizeCVClient, args);
    csSetAction(inc->id, WM_TIMER, autoResizeCVClient, args);

    void zoomFromIncrementer(csARGS Args);
    SIZE *bmSize = csf_alloc2<SIZE>(1,{bmp.bm.bmWidth,bmp.bm.bmHeight});
    int *updateZoomTime = csf_alloc2<int>(1,0);

    csARGS args2(3);
    args2.makeArgs(inc, bmSize, updateZoomTime);
    csSetAction(client, WM_TIMER, zoomFromIncrementer, args2);

    void zoomFromMouseWheel(csARGS Args);
    csSetAction(client, WM_MOUSEWHEEL, zoomFromMouseWheel, args2);

    void btnDownUpdate(csARGS Args);
    //csSetAction(client, WM_LBUTTONDOWN, btnDownUpdate, 0);
    csSetAction(client, WM_LBUTTONUP, btnDownUpdate, 0);

    return cvCnt;
}

void btnDownUpdate(csARGS Args)
{
    *(cv.CTX[int(Args)].getUpdateAfterStretchingBool()) = 1;
    InvalidateRect(HWND(Args),0,1);
}

void resizeCVContainer(csARGS Args)
{
    int id = int(Args);
    RECT r = cv.CNTCLWRECT[id];

    int client = *(int*)Args[0];
    int hscroll = *(int*) Args[1];
    int vscroll = *(int*)Args[2];
    int inc = *(int*)Args[3];

    RECT* rclient = (RECT*)Args[4];
    RECT* rHscroll = (RECT*)Args[5];
    RECT* rVscroll = (RECT*)Args[6];
    RECT* rInc = (RECT*)Args[7];
    RECT* rTitle = (RECT*)Args[8];

    *rclient = {5,35,r.right-20, r.bottom-50};
    *rHscroll = {5, r.bottom-15, r.right-10, 10};
    *rVscroll = {r.right-15, 35, 10, r.bottom-50};
    *rInc = {r.right-15-200, 5, 200, 25};

    SendMessage(cv.CNTLIST[client], WM_TIMER,0,0);
    SendMessage(cv.CNTLIST[hscroll], WM_TIMER,0,0);
    SendMessage(cv.CNTLIST[vscroll], WM_TIMER,0,0);
    SendMessage(cv.CNTLIST[inc], WM_TIMER,0,0);
    SendMessage(cv.CNTLIST[id], WM_TIMER,0,0);

    *rTitle = {0,0,r.right, cv.cp[id]->CaptionAreaLength
                + cv.cp[id]->SizingAreaLength};
}

void autoResizeCVClient(csARGS Args)
{
    int id = int(Args);

    int client = *(int*)Args[0];
    int hscroll = *(int*) Args[1];
    int vscroll = *(int*)Args[2];
    int inc = *(int*)Args[3];

    RECT* rclient = (RECT*)Args[4];
    RECT* rHscroll = (RECT*)Args[5];
    RECT* rVscroll = (RECT*)Args[6];
    RECT* rInc = (RECT*)Args[7];
    RECT* rTitle = (RECT*)Args[8];

    if(id == client && rclient->right)
    {
        MoveWindow(cv.CNTLIST[id], rclient->left, rclient->top, rclient->right, rclient->bottom, 0);
        InvalidateRect(cv.CNTLIST[id], 0,1);
        *rclient = {0,0,0,0};
    }
    else if(id == hscroll && rHscroll->right)
    {
        MoveWindow(cv.CNTLIST[id], rHscroll->left, rHscroll->top, rHscroll->right, rHscroll->bottom, 0);
        *rHscroll = {0,0,0,0};
    }
    else if(id == vscroll && rVscroll->bottom)
    {
        MoveWindow(cv.CNTLIST[id], rVscroll->left, rVscroll->top, rVscroll->right, rVscroll->bottom,0);
        *rVscroll = {0,0,0,0};
    }
    else if(id == inc && rInc->left)
    {
        MoveWindow(cv.CNTLIST[id], rInc->left, rInc->top, rInc->right, rInc->bottom,0);
        *rInc = {0,0,0,0};
    }
    else if(rTitle->right)
    {
        InvalidateRect(cv.CNTLIST[id], rTitle,1);
        *rTitle = {0,0,0,0};
    }
}

void updateAfterStretching(csARGS Args)
{
    int* maxtime = (int*)Args[2];

    if(*maxtime > 0)
    {
        (*maxtime)--;
        if(*maxtime == 1)
        {
            *(cv.CTX[int(Args)].getUpdateAfterStretchingBool()) = 1;
            InvalidateRect(HWND(Args),0,1);
        }
    }
}
void zoomFromIncrementer(csARGS Args)
{
    csINCREMENTER* inc = (csINCREMENTER*)Args[0];
    SIZE max = *(SIZE*)Args[1];

    if(inc->size_message)
    {
        int limit = 2;
        float fct = (inc->val)/100.0;
        SIZE sz = {limit*max.cx*fct, limit*max.cy*fct};
        if(sz.cx==0) sz.cx == 1;
        if(sz.cy==0) sz.cy == 1;
        cv.CTX[int(Args)].setBlitSize(sz);
        csDC_METRICS dcm = {0};
        dcm.zoomFactor = fct;
        cv.CTX[int(Args)].setZoomParams(dcm);
        InvalidateRect(HWND(Args), 0,1);
        inc->size_message = 0;
        int* maxtime = (int*)Args[2];
        *maxtime = 2;
    }
    updateAfterStretching(Args);
}
void zoomFromMouseWheel(csARGS Args)
{
    csINCREMENTER* inc = (csINCREMENTER*)Args[0];

    if(!GetAsyncKeyState(VK_CONTROL) && !GetAsyncKeyState(VK_SHIFT))
    {
        int d = GET_WHEEL_DELTA_WPARAM(WPARAM(Args));
        SendMessage(cv.CNTLIST[inc->id4], WM_MOUSEWHEEL, d, 0);
    }
}

/****************************************************/

void move_h1_1(csARGS Args)
{
    if(*(int*)Args[0])
    {
        int id = (int)Args;
        RECT r1 = cv.CNTRECT[id];
        RECT r2 = cv.CNTCLWRECT[id];

        RECT r = cv.CNTCLWRECT[0];
        int dx = r1.left+(r2.right-r.right)/2;
        int dy = r1.top;

        SetWindowPos(cv.CNTLIST[0], 0, dx, dy, 0,0,SWP_NOSIZE|SWP_NOREDRAW);
    }

}
void move_h1_2(csARGS Args)
{
    *(bool*)Args[0] = 1;
}

void menuSizeSinc(csARGS Args)
{
    int id = *(int*)Args[3];
    RECT r = cv.CNTRECT[cv.CNTPARID[id]];
                //std::cout<<cv.CURRENT_HITTEST_AREA<<" id "<< (int)Args <<" iuyuyi \n";
    //if(!cv.CNTCREATION[(int)Args]) */// eviter les bugs de dimensionnement au demarrage
    //if((cv.CURRENT_HITTEST_AREA == CSA_LEFT || cv.CURRENT_HITTEST_AREA == CSA_NW || cv.CURRENT_HITTEST_AREA == CSA_SW)
    //&& Messages.hwnd == csHWND(*(int*)Args[3])) // ne surtout pas supprimer, car evite les bugs de deimensionnement au demarrage
    if(Messages.hwnd == csHWND(id) && r.right!=0 && r.bottom!=0)
    {
        RECT r2 = csWRECT(id);
        int id1 = *(int*)Args[2];

        *(SIZE*)Args[10] = {r2.left-r.left-2-5, cv.cp[id1]->Geometry.bottom};

        int idcapt = *(int*)Args[4];
        *(int*)Args[7] = r2.left - r.left - csPARAMS(idcapt)->Geometry.right - 2;

        SendMessage(cv.CNTLIST[id1],WM_TIMER,0,0);
        SendMessage(cv.CNTLIST[idcapt],WM_TIMER,0,0);
    }
}

void autoResizeLayers_client(csARGS Args)
{
    int id = int(Args);
    int idg = *(int*)Args[0];
    int idg3 = *(int*)Args[1];
    RECT rg3=cv.CNTRECT_SAVED[idg3], r;
    GetClientRect((HWND)Args, &r);
    if(cv.CURRENT_HITTEST_AREA != CSA_RIGHT && cv.CURRENT_HITTEST_AREA != CSA_LEFT)
    {
        SetWindowPos(cv.CNTLIST[idg],0,0,0,cv.cp[idg]->Geometry.right,r.bottom-4,SWP_NOMOVE);
        SetWindowPos(cv.CNTLIST[idg3],0,rg3.left,r.bottom-40,0,0,SWP_NOSIZE);
    }
}

void resizeSys(csARGS Args)
{
    //int dx1=0, dx2=1;
    while(1)
    {
        if(*(bool*)Args[0])
        {//std::cout<<activate<<" thread 1\n";
        int id = *(int*)Args[1], id_src = *(int*)Args[2];
        //dx1 = cv.CNTRECT[id].left;
        SetWindowPos(cv.CNTLIST[id],0,cv.CNTCLWRECT[id_src].right-cv.cp[id]->Geometry.right-5,0,0,0,SWP_NOSIZE);
        //GetWindowRect(cv.CNTLIST[id],&cv.CNTRECT[id]);
        //dx2 = cv.CNTRECT[id].left;
        }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
void resizeClient(csARGS Args)
{
    //int dx1=0, dx2=1, dy1=0, dy2=1;
    //while((dx1!=dx2) || (dy1!=dy2))
    while(1)
    {
        if(*(bool*)Args[0])//std::cout<<activate<<" thread 2\n";
        {int id = *(int*)Args[1], id_src = *(int*)Args[2];
        //std::cout<<" thread 2\n";
        //dx1 = cv.CNTRECT[id].right;
        //dy1 = cv.CNTRECT[id].bottom;
        SetWindowPos(cv.CNTLIST[id],0,5,55,cv.CNTCLWRECT[id_src].right-10,
                     cv.CNTCLWRECT[id_src].bottom-10,SWP_NOZORDER);
        //GetWindowRect(cv.CNTLIST[id],&cv.CNTRECT[id]);
        //dx2 = cv.CNTRECT[id].right;
        //dy2 = cv.CNTRECT[id].bottom;
        }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
void _resizeSys(csARGS Args)
{
    //*(bool*)Args[0] = 1;
    std::thread t1(resizeSys, Args);
    //((std::thread*)Args[0])->join();
}
void _resizeClient(csARGS Args)
{
    std::thread t2(resizeClient, Args);

    //((std::thread*)Args[0])->join();
}

void autoResizeLayers_base(csARGS Args)
{
    RECT r = cv.CNTCLWRECT[int(Args)], r0 = cv.CNTRECT[int(Args)];
    //GetClientRect((HWND)Args, &r);
    if(r.right!=0 && r.bottom!=0)
    {
        int id = int(Args);
        int idSys = *(int*)Args[0];
        int idClient = *(int*)Args[1];
        int id1 = *(int*)Args[2];
        int id2 = *(int*)Args[3];
        int idcapt = *(int*)Args[4];
        int idbottomBar = *(int*)Args[11];
        RECT r1, r2, rs=cv.CNTRECT_SAVED[id];
        r2 = cv.CNTCLWRECT_SAVED[id2];
        int idHscroll = *(int*)Args[13];
        int* hscrollLen = (int*)Args[14];
        int idVscroll = *(int*)Args[15];
        int* vscrollLen = (int*)Args[16];
        int idboard = *(int*)Args[17];

        //int dcx  = r.right-(rs.right-rs.left);

       // if(cv.CURRENT_HITTEST_AREA != CSA_BOTTOM && cv.CURRENT_HITTEST_AREA != CSA_TOP)
       int e = 2, bblen = 25+e;
        *(SIZE*)Args[8] = {r.right-10,r.bottom-60-bblen};

        *(int*)Args[6] = r.right-cv.cp[idSys]->Geometry.right-5;

        int a = cv.cp[id]->SizingAreaLength;
        if(cv.CNTRECT[id2].left>=0)
        /**(RECT*)Args[9] = {r.right-r2.right-dcx-cv.cp[id]->CaptionAreaLength-cv.cp[idSys]->Geometry.right,r2.top,
         r0.right-cv.CNTRECT[id2].left-cv.cp[idSys]->Geometry.right-cv.cp[id]->SizingAreaLength,
         cv.cp[id2]->Geometry.bottom};*/
         *(RECT*)Args[9] = {0,0,
         r0.right-cv.CNTRECT[id2].left-cv.cp[idSys]->Geometry.right-a,
         cv.cp[id2]->Geometry.bottom};

        *(RECT*)Args[12] = {a, r.bottom-a-bblen, r.right-a*2,bblen};

        *hscrollLen = r.right - cv.cp[idHscroll]->Geometry.left - 2*a;
        *vscrollLen = r.bottom - cv.cp[idHscroll]->Geometry.top - 2*a-cv.cp[id]->CaptionAreaLength
                        - bblen - cv.cp[id1]->Geometry.bottom;

        RECT* rboard = (RECT*)Args[18];

        *rboard = {0,0,csPARAMS(idboard)->Geometry.right, r.bottom-60-bblen};

        SendMessage(cv.CNTLIST[idSys],WM_TIMER,0,0);
        SendMessage(cv.CNTLIST[idClient],WM_TIMER,0,0);
        SendMessage(cv.CNTLIST[id2],WM_TIMER,0,0);
        SendMessage(cv.CNTLIST[idbottomBar],WM_TIMER,0,0);
        SendMessage(cv.CNTLIST[idHscroll],WM_TIMER,0,0);
        SendMessage(cv.CNTLIST[idVscroll],WM_TIMER,0,0);
        SendMessage(cv.CNTLIST[idboard],WM_TIMER,0,0);
    }
}

void autoMoveChilds(csARGS Args)
{
    int idSys = *(int*)Args[0];
    int idcapt = *(int*)Args[4];
    int id1 = *(int*)Args[2];
    int id2 = *(int*)Args[3];
    int idClient = *(int*)Args[1];
    int idbottomBar = *(int*)Args[11];
    int idHscroll = *(int*)Args[13];
    int idVscroll = *(int*)Args[15];
    int idboard = *(int*)Args[17];

    if(*(int*)Args[6] && (int)Args==idSys)
    {
        SetWindowPos(cv.CNTLIST[idSys],HWND_TOP,*(int*)Args[6],3,0,0,SWP_NOSIZE|SWP_NOREDRAW);
        *(int*)Args[6] = 0;
    }
    else if(*(int*)Args[7] && (int)Args==idcapt)
    {
        SetWindowPos(cv.CNTLIST[idcapt],HWND_BOTTOM,*(int*)Args[7],3,0,0,SWP_NOSIZE);
        *(int*)Args[7] = 0;
    }
    else if((*(RECT*)Args[9]).right && (int)Args==id2)
    {
        RECT r = (*(RECT*)Args[9]);
        SetWindowPos(cv.CNTLIST[id2],HWND_BOTTOM,0,0,r.right,r.bottom,SWP_NOMOVE|SWP_NOREDRAW);
        *(RECT*)Args[9] = {0,0,0,0};
    }
    else if((*(SIZE*)Args[8]).cx && (int)Args==idClient)
    {
        SIZE sz = (*(SIZE*)Args[8]);
        SetWindowPos(cv.CNTLIST[idClient],HWND_BOTTOM,5,55,sz.cx,sz.cy,SWP_NOZORDER);
        *(SIZE*)Args[8] = {0,0};
    }
    else if((*(SIZE*)Args[10]).cx && (int)Args==id1)
    {
        SIZE sz = (*(SIZE*)Args[10]);
        SetWindowPos(cv.CNTLIST[id1],HWND_BOTTOM,0,0,sz.cx,sz.cy,SWP_NOMOVE);
        *(SIZE*)Args[10] = {0,0};
    }
    else if((*(RECT*)Args[12]).right && (int)Args==idbottomBar)
    {
        RECT r = (*(RECT*)Args[12]);
        SetWindowPos(cv.CNTLIST[idbottomBar],HWND_BOTTOM,r.left,r.top,r.right,r.bottom,SWP_NOZORDER);
        *(RECT*)Args[12] = {0,0,0,0};
    }
    else if((*(int*)Args[14]) && (int)Args==idHscroll)
    {
        int cx = (*(int*)Args[14]);
        SetWindowPos(cv.CNTLIST[idHscroll],HWND_BOTTOM,0,0,cx,cv.CNTCLWRECT[idHscroll].bottom,SWP_NOMOVE);
        *(int*)Args[14] = 0;
    }
    else if((*(int*)Args[16]) && (int)Args==idVscroll)
    {
        int cy = (*(int*)Args[16]);
        SetWindowPos(cv.CNTLIST[idVscroll],HWND_BOTTOM,0,0,cv.CNTCLWRECT[idVscroll].right, cy,SWP_NOMOVE);
        *(int*)Args[16] = 0;
    }
    else if((*(RECT*)Args[18]).bottom && (int)Args==idboard)
    {
        RECT* r = (RECT*)Args[18];
        SetWindowPos(cv.CNTLIST[idboard],HWND_TOP,0,0,r->right, r->bottom,SWP_NOMOVE);
        *r = {0,0,0,0};
    }
}


void autoResizeCTBG(csARGS Args)
{
    int id1 = int(Args);
    RECT r1=cv.CNTRECT[id1], r1s = cv.CNTRECT_SAVED[id1];
    //GetWindowRect((HWND)Args, &r1);
    int id2 = *(int*)Args[0];
    RECT r2s = rectInParentRef(id2, cv.CNTRECT_SAVED[id2]);
    int dx  = r1.left-r1s.left, dcx  = r1.right-r1s.right;
    int dy  = r1.top-r1s.top, dcy  = r1.bottom-r1s.bottom;

    int desttype = *(int*)Args[1];
    int srcarea = *(int*)Args[2];
    HWND hdest = cv.CNTLIST[id2];
    if(cv.CURRENT_HITTEST_AREA == CSA_RIGHT && srcarea == CSA_RIGHT)
    {
        if(desttype == GLINK_SIZE)
        {
            SetWindowPos(hdest,0,0, 0, r2s.right-r2s.left+dcx,r2s.bottom-r2s.top,SWP_NOMOVE);
            //std::cout<<r1.right<<"\n";
        }
        else if(desttype == GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left+dcx,r2s.top,0,0,SWP_NOSIZE);
        else if(desttype == GLINK_SIZE|GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left+dcx,r2s.top+dcy,r2s.right-r2s.left+dcx,r2s.bottom-r2s.top,SWP_NOZORDER);
    }
    else if(cv.CURRENT_HITTEST_AREA == CSA_BOTTOM && srcarea == CSA_BOTTOM)
    {
        if(desttype == GLINK_SIZE)
            SetWindowPos(hdest,0,0, 0, r2s.right-r2s.left,r2s.bottom-r2s.top+dcy,SWP_NOMOVE);
        else if(desttype == GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left,r2s.top+dcy,0,0,SWP_NOSIZE);
        else if(desttype == GLINK_SIZE|GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left,r2s.top+dcy,r2s.right-r2s.left,r2s.bottom-r2s.top+dcy,SWP_NOZORDER);
    }
    else if(cv.CURRENT_HITTEST_AREA == CSA_SE && srcarea == CSA_SE)
    {
        if(desttype == GLINK_SIZE)
            SetWindowPos(hdest,0,0, 0, r2s.right-r2s.left+dcx,r2s.bottom-r2s.top+dcy,SWP_NOMOVE);
        else if(desttype == GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left+dcx,r2s.top+dcy,0,0,SWP_NOSIZE);
        else if(desttype == GLINK_SIZE|GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left+dcx,r2s.top+dcx,r2s.right-r2s.left+dcx,r2s.bottom-r2s.top+dcy,SWP_NOZORDER);
    }
    else if(cv.CURRENT_HITTEST_AREA == CSA_LEFT && srcarea == CSA_LEFT)
    {
        if(desttype == GLINK_SIZE)
            SetWindowPos(hdest,0,0, 0,r2s.right-r2s.left+dx,r2s.bottom-r2s.top,SWP_NOMOVE);
        else if(desttype == GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left+dx,r2s.top,0,0,SWP_NOSIZE);
        else if(desttype == GLINK_SIZE|GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left+dx,r2s.top,r2s.right-r2s.left+dx,r2s.bottom-r2s.top,SWP_NOZORDER);
    }
    else if(cv.CURRENT_HITTEST_AREA == CSA_TOP && srcarea == CSA_TOP)
    {
        if(desttype == GLINK_SIZE)
            SetWindowPos(hdest,0,0, 0,r2s.right-r2s.left,r2s.bottom-r2s.top+dy,SWP_NOMOVE);
        else if(desttype == GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left,r2s.top+dy,0,0,SWP_NOSIZE);
        else if(desttype == GLINK_SIZE|GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left,r2s.top+dy,r2s.right-r2s.left,r2s.bottom-r2s.top+dy,SWP_NOZORDER);
        //SetWindowPos(hdest,0, 0,0, r.right,geom.bottom,SWP_NOSIZE);
    }
    else if(cv.CURRENT_HITTEST_AREA == CSA_NW && srcarea == CSA_NW)
    {
        if(desttype == GLINK_SIZE)
            SetWindowPos(hdest,0,0, 0,r2s.right-r2s.left+dx,r2s.bottom-r2s.top+dy,SWP_NOMOVE);
        else if(desttype == GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left+dx,r2s.top+dy,0,0,SWP_NOSIZE);
        else if(desttype == GLINK_SIZE|GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left+dx,r2s.top+dy,r2s.right-r2s.left+dx,r2s.bottom-r2s.top+dy,SWP_NOZORDER);
        //SetWindowPos(hdest,0, 0,0, r.right,geom.bottom,SWP_NOSIZE);
    }
    else if(cv.CURRENT_HITTEST_AREA == CSA_NE && srcarea == CSA_NE)
    {
        if(desttype == GLINK_SIZE)
            SetWindowPos(hdest,0,0, 0,r2s.right-r2s.left+dx,r2s.bottom-r2s.top+dy,SWP_NOMOVE);
        else if(desttype == GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left+dx,r2s.top+dy,0,0,SWP_NOSIZE);
        else if(desttype == GLINK_SIZE|GLINK_POSITION)
            SetWindowPos(hdest,0,r2s.left+dx,r2s.top+dy,r2s.right-r2s.left+dx,r2s.bottom-r2s.top+dy,SWP_NOZORDER);
        //SetWindowPos(hdest,0, 0,0, r.right,geom.bottom,SWP_NOSIZE);
    }
    /*else if
    {
        if(desttype == GLINK_SIZE)
            SetWindowPos(hdest,0,0, 0,r2s.right+dcx,r2s.bottom+dcy,SWP_NOMOVE);
        else
            SetWindowPos(hdest,0,r2s.left+dx,r2s.top+dy,0,0,SWP_NOSIZE);
    }*/
}


void _deleteGridContainer(csARGS Args)
{
    DestroyWindow((HWND)Args);
    ((csGRID*)Args[1])->deleteContainer(*(int*)Args[0]);
}

int* tabbed(csCNTR_PARAMS& cscp, int id_btn_cnt, int id_client_cnt, RECT geometry,
            int*&btn,csPAGEFLIPPING_VARS*&hs, int*&N)
{
    csLOCKED_MODE lm={0};
    lm.ExternalUnlocking = 1;
    lm.Lockable = 1;
    lm.LockingColor = {60,60,70};

    N=(int*)malloc(sizeof(int));
    int n=5;
    *N = n;
    int dy = 3, dx = 1, cx = 60, lx = cx+dx;
    btn = (int*)malloc(n*sizeof(int));
    btn[0] = textButton2(cscp, id_btn_cnt, "Page 1", {250,250,250}, {5,     dy,cx,25}, lm);
    btn[1] = textButton2(cscp, id_btn_cnt, "Page 2", {250,250,250}, {5+1*lx,dy,cx,25}, lm);
    btn[2] = textButton2(cscp, id_btn_cnt, "Page 3", {250,250,250}, {5+2*lx,dy,cx,25}, lm);
    btn[3] = textButton2(cscp, id_btn_cnt, "Page 4", {250,250,250}, {5+3*lx,dy,cx,25}, lm);
    btn[4] = textButton2(cscp, id_btn_cnt, "Page 5", {250,250,250}, {5+4*lx,dy,cx,25}, lm);

    cv.cp[btn[0]]->TitleAlign = CS_TA_CENTER;
    cv.cp[btn[1]]->TitleAlign = CS_TA_CENTER;
    cv.cp[btn[2]]->TitleAlign = CS_TA_CENTER;
    cv.cp[btn[3]]->TitleAlign = CS_TA_CENTER;
    cv.cp[btn[4]]->TitleAlign = CS_TA_CENTER;

    cv.CTX[btn[0]].setCntBorder({25,25,25},1);
    cv.CTX[btn[1]].setCntBorder({25,25,25},1);
    cv.CTX[btn[2]].setCntBorder({25,25,25},1);
    cv.CTX[btn[3]].setCntBorder({25,25,25},1);
    cv.CTX[btn[4]].setCntBorder({25,25,25},1);

    //cv.CTX[btn[0]].brdGrad_top = {2,5,1,0,1};
    float sharp = 2;
    int nbr = 3;
    cv.CTX[btn[0]].brdGrad_left = {nbr,5,1,1,sharp};
    //cv.CTX[btn[0]].brdGrad_top = {nbr,5,1,1,sharp};
    //cv.CTX[btn[0]].brdGrad_right = {nbr,5,1,1,sharp};
    cv.CTX[btn[0]].brdGrad_bottom = {nbr,5,1,1,sharp};

    cv.CTX[btn[1]].brdGrad_left = {nbr,5,1,1,sharp};
    //cv.CTX[btn[1]].brdGrad_top = {nbr,5,1,1,sharp};
    //cv.CTX[btn[1]].brdGrad_right = {nbr,5,1,1,sharp};
    cv.CTX[btn[1]].brdGrad_bottom = {nbr,5,1,1,sharp};

    cv.CTX[btn[2]].brdGrad_left = {nbr,5,1,1,sharp};
    //cv.CTX[btn[2]].brdGrad_top = {nbr,5,1,1,sharp};
    //cv.CTX[btn[2]].brdGrad_right = {nbr,5,1,1,sharp};
    cv.CTX[btn[2]].brdGrad_bottom = {nbr,5,1,1,sharp};

    cv.CTX[btn[3]].brdGrad_left = {nbr,5,1,1,sharp};
    //cv.CTX[btn[3]].brdGrad_top = {nbr,5,1,1,sharp};
    //cv.CTX[btn[3]].brdGrad_right = {nbr,5,1,1,sharp};
    cv.CTX[btn[3]].brdGrad_bottom = {nbr,5,1,1,sharp};

    cv.CTX[btn[4]].brdGrad_left = {nbr,5,1,1,sharp};
    //cv.CTX[btn[4]].brdGrad_top = {nbr,5,1,1,sharp};
    //cv.CTX[btn[4]].brdGrad_right = {nbr,5,1,1,sharp};
    cv.CTX[btn[4]].brdGrad_bottom = {nbr,5,1,1,sharp};

    int *page = (int*)malloc(n*sizeof(int));
    page[0] = staticCnt2(cscp, id_client_cnt, "", {20,30,30}, geometry, 0);
    page[1] = staticCnt2(cscp, id_client_cnt, "", {40,40,40}, geometry, 0);
    page[2] = staticCnt2(cscp, id_client_cnt, "", {50,30,40}, geometry, 0);
    page[3] = staticCnt2(cscp, id_client_cnt, "", {30,30,30}, geometry, 1);
    page[4] = staticCnt2(cscp, id_client_cnt, "", {40,40,40}, geometry, 0);

    for(int i = 0; i<n; i++)
    {
        SetTimer(cv.CNTLIST[page[i]], 0, 15, 0);
    }

    hs = (csPAGEFLIPPING_VARS*)malloc(sizeof(csPAGEFLIPPING_VARS));
    *hs = getHideShowVars(btn, page, N);
    hs->dr = {10,0,0,0};

    csSetAction(btn[0], WM_LBUTTONUP, cntgroup_show_hide_click, 1, hs);
    csARGS args = cv.cp[btn[0]]->CntEventsFunc.LBUTTONUP_ARGS[0];
    csSetAction(btn[0], WM_TIMER, cntgroup_show_hide, args);
    csSetAction(btn[1], WM_LBUTTONUP, cntgroup_show_hide_click, args);
    csSetAction(btn[1], WM_TIMER, cntgroup_show_hide, args);
    csSetAction(btn[2], WM_LBUTTONUP, cntgroup_show_hide_click, args);
    csSetAction(btn[2], WM_TIMER, cntgroup_show_hide, args);
    csSetAction(btn[3], WM_LBUTTONUP, cntgroup_show_hide_click, args);
    csSetAction(btn[3], WM_TIMER, cntgroup_show_hide, args);
    csSetAction(btn[4], WM_LBUTTONUP, cntgroup_show_hide_click, args);
    csSetAction(btn[4], WM_TIMER, cntgroup_show_hide, args);

    return page;
}


/*************************************************************/


void calculate(csARGS Args)
{
    int idres = *((int*)Args[0]);
    int idtype = *((int*)Args[1]);
    int n = *((int*)Args[2]);
    int* idE = (int*)Args[3];
    char* name = (char*)Args[4];
    double moy=0;
    double* val = (double*)malloc(n*sizeof(double));
    char* str = (char*)malloc(100);
    sprintf(str,"");
    int N = 0;
    for(int i=0; i<n; i++)
    {
        GetWindowTextA(cv.cp[idE[i]]->EditBox.EditBoxHandle,(LPSTR)str,100);
        val[i] = strtod(str,0);
        if (val[i]>0.0)
        {
            moy+=val[i];
            N++;
            sprintf(str,"%.2lf",val[i]);
            SetWindowTextA(cv.cp[idE[i]]->EditBox.EditBoxHandle,(LPCSTR)str);
        }else
        {
            sprintf(str,"0.00");
            SetWindowTextA(cv.cp[idE[i]]->EditBox.EditBoxHandle,(LPCSTR)str);
        }
        SendMessage(GetParent(cv.cp[idE[i]]->EditBox.EditBoxHandle), WM_ERASEBKGND, 0, 0);
    }
    moy/=N;
    double ec = 0;
    for(int i=0; i<n; i++)
    {
        if (val[i]>0)
        {
            ec+=(val[i] - moy)*(val[i] - moy);
        }
    }
    ec /= N;
    ec = sqrt(ec);

    double minval = moy - ec;
    double maxval = moy + ec;

    GetWindowTextA(cv.cp[idtype]->EditBox.EditBoxHandle,(LPSTR)str,100);
    double etype = strtod(str,0);
    char Text[500];
    if(etype<=0.0)
    {
        sprintf(Text,"Veuillez Entrer une épaisseur valide \r\n pour l'article %s. ", name);
    }
    else
    {
        double minlen = ((4.1+minval)*(4.1+minval)-4.1*4.1)*3.141596/etype;
        double maxlen = ((4.1+maxval)*(4.1+maxval)-4.1*4.1)*3.141596/etype;
        sprintf(Text,"Intervalle de longeur pour %s : \r\n   [%d cm, %d cm]"
                " \r\n \r\nLongueur moyenne :\r\n   %d"
                " \r\n \r\nEcart-type :\r\n   %.6lf"
                " \r\n \r\nEpaisseur Moyenne du rouleau :\r\n   %.2lf cm",
                name,int(minlen), int(maxlen), int((minlen+maxlen)/2), ec, moy);
    }
    HDC hdc = GetDC(cv.CNTLIST[idres]);
    HDC dc =cv.CTX[idres].createDC(hdc);
    SetBkMode(dc,TRANSPARENT);
    HFONT hf = CreateFont(20, 0, 0, 1,0,0, 0,0,0,0,0,0,0, (LPCSTR)"Arial");
    SelectFont(dc,hf);
    SetTextColor(dc,RGB(250, 250,250));
    SetTextAlign(dc, TA_LEFT);
    RECT r={0,40,300,300};
    DrawTextA(dc,(LPCSTR)Text,-1,&r,DT_LEFT);
    //TextOut(dc,10,40,(LPCSTR)Text,strlen(Text));
    DeleteFont(hf);
    SendMessage(cv.CNTLIST[idres],WM_ERASEBKGND,0,0);
    ReleaseDC(cv.CNTLIST[idres],hdc);

    free(val);
    free(str);
}

int*window_with_menu_caption(HINSTANCE hThisInstance)
{
    int *id=(int*)malloc(4*3);
    cscp.Hinstance=hThisInstance;
    cscp.Geometry= {200,100,850,500};
    cscp.MinMaxStyle=1;
    cscp.ClingToParent=0;
    cscp.Show=1;
    cscp.HTCorner=1;
    cscp.HTLeft=1;
    cscp.HTTop=1;
    cscp.HTRight=1;
    cscp.HTBottom=1;
    cscp.SizingAreaLength=10;
    cscp.CaptionDirection=1;
    cscp.CaptionAreaLength=20;
    cscp.CaptionAreaPos=1;
    cscp.Transparency=5;
    cscp.SizingParams= {0};
    cscp.MinTrackSize= {500,400};
    cscp.MaxSize= {GetSystemMetrics(SM_CXSCREEN),
                   GetSystemMetrics(SM_CYSCREEN)-hauteurBarreDeTache()
                  };
    cscp.Title.Text="Ma Fenetre";
    //cscp.BackgroundColor={0,100,200};
    srf0.backImageDesign("fond.bmp", {200,0,255,0}, {0});
    int Cont0=csc.csCNT_newContainer(0, cscp);
    csc.csc_setSurface(&srf0, 0);
    //csc.csc_setSurface(&srf0, 0);
    initContParams(cscp);
    cscp.Hinstance=hThisInstance;
    cscp.Geometry= {10,35,500-20,300-20-15};
    cscp.ClingToParent=0;
    cscp.Show=1;
    cscp.HTCorner=0;
    cscp.HTLeft=0;
    cscp.HTTop=0;
    cscp.HTRight=0;
    cscp.HTBottom=0;
    cscp.SizingAreaLength=0;
    cscp.CaptionDirection=0;
    cscp.CaptionAreaLength=0;
    cscp.CaptionAreaPos=1;
    cscp.DcZoomIncrement=0.0;
    cscp.Transparency=5;
    cscp.BackgroundColor= {50,50,70};
    cscp.SizingParams= {5,35,-5,-5};
    cscp.Title.Text="Ma Fenetre1";
    int h1=csc.csCNT_newContainer(Cont0, cscp);

    initContParams(cscp);
    cscp.Hinstance=hThisInstance;
    cscp.Geometry= {10+80,5,500-20-160,300-10};
    cscp.ClingToParent=0;
    cscp.Show=1;
    cscp.HTCorner=0;
    cscp.HTLeft=0;
    cscp.HTTop=0;
    cscp.HTRight=0;
    cscp.HTBottom=0;
    cscp.SizingAreaLength=0;
    cscp.CaptionDirection=1;
    cscp.CaptionAreaLength=30;
    cscp.CaptionAreaPos=1;
    cscp.DcZoomIncrement=0.0;
    cscp.Transparency=90;
    cscp.SizingParams= {30,5,-30,30};
    cscp.BackgroundColor= {150,50,70};
    cscp.Title.Text="Ma Fenetre4";
    int h4=csc.csCNT_newContainer(Cont0, cscp);

    id[0]=Cont0;
    id[1]=h4;
    id[2]=h1;
    return id;
}


int dynamicCnt(csCNTR_PARAMS& cscp, int idp, char*title, RECT geometry)
{
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    cscp.Geometry= geometry;
    cscp.MinMaxStyle=1;
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.HTCorner=1;
    cscp.HTLeft=1;
    cscp.HTTop=1;
    cscp.HTRight=1;
    cscp.HTBottom=0;
    cscp.SizingAreaLength=5;
    cscp.CaptionDirection=1;
    cscp.CaptionAreaLength=30;
    cscp.CaptionAreaPos=1;
    cscp.DcZoomIncrement=0.05;//zzzzzzzzzzzzzzzzzzzzzzzzzzz
    cscp.MinTrackSize= {100,100};
    cscp.MaxTrackSize= {1000,1000};
    cscp.BlockedWithinParent = 1;
    cscp.XMinTrackPosition_extra = 100;
    cscp.YMinTrackPosition_extra = 0;
    cscp.Transparency=0;
    cscp.SizingParams= {0,0,0,0};
    cscp.BackgroundColor= {20,30,30};
    cscp.BorderWidth= 1;
    cscp.BorderColor= {70,70,70};
    cscp.MouseLeaveRemoveBkg = 0;
    cscp.Title.Text=title;
    cscp.TitleAlign=CS_TA_TOP_CENTER;
    cscp.MHGradient.GradientType = CS_GRAD_COLOR;
    cscp.MHGradient.GradientNumber = 3;
    cscp.MHGradient.TimeStep = 3;
    cscp.MHGradient.Color1 = {30,40,40};
    cscp.MHGradient.Color2 = {10,20,20};
    cscp.MouseHoverTime = 3;
    cscp.AutoTransform.Type = AUTO_TRANSF_LENGTH;
    cscp.AutoTransform.Time = 50;
    cscp.AutoTransform.FinalRect = {0,0,0,0};
    cscp.AutoTransformFadeOut.AccelCaptureTime = 1;
    cscp.AutoTransformFadeOut.FadeOutTime = 20;
    cscp.AutoAlphaFade.FadeTime = 10;
    cscp.AutoAlphaFade.AlphaMin = 0;
    cscp.AutoAlphaFade.Activate = 1;
    cscp.AutoAlphaFade.ShowHide = 1;
    return csc.csCNT_newContainer(idp, cscp);
}


int editBox(csCNTR_PARAMS& cscp, int idp, char*title,char*dflt, RECT geometry, int*idbtns, int*SameDesignCnts,
            int titlePos, bool withControlers)
{
    initContParams(cscp);
    cscp.Hinstance=*Hinst;
    cscp.Geometry= geometry;
    cscp.ClingToParent=1;
    cscp.Show=1;
    cscp.BackgroundColor={40,40,40};
    cscp.BorderWidth= 1;
    cscp.BorderColor= {70,70,70};
    cscp.Title.Text="";
    cscp.DCSizes={(unsigned int)geometry.right, (unsigned int)geometry.bottom};
    cscp.MHGradient.GradientType = CS_GRAD_COLOR;
    cscp.MHGradient.GradientNumber = 5;
    cscp.MHGradient.TimeStep = 3;
    cscp.MHGradient.Color1 = {50,50,40};
    cscp.MHGradient.Color2 = {40,40,40};
    cscp.MouseHoverTime = 3;
    //------------------------------------------
    cscp.EditBox.AddEditBox=1;
    cscp.EditBox.Title.Text=title;
    cscp.EditBox.Title.Font="Calibri";
    cscp.EditBox.Title.FontSize={13,0};
    cscp.EditBox.Title.Bold=1;
    cscp.EditBox.Title.TextRect={0,0,geometry.right,geometry.bottom};
    cscp.EditBox.Title.Color={210,210,210};
    cscp.EditBox.String.Font="Calibri";
    cscp.EditBox.String.Italic=1;
    cscp.EditBox.String.Bold=1;
    cscp.EditBox.String.FontSize={13,0};
    cscp.EditBox.WithControlers=withControlers;
    //cscp.EditBox.String.TextRect={180,200,180};
    cscp.EditBox.String.Color={180,200,180};
    cscp.EditBox.TitlePosition=titlePos;
    cscp.EditBox.DefText=dflt;
    //cscp.EditBox..EditModeBkgColor=RGB(100,100,100);
    cscp.EditBox.EditModeBkgColor=RGB(20,20,20);
    cscp.EditBox.EditModeTextColor=RGB(200,200,200);
    cscp.EditBox.LineColor=RGB(50,50,50);
    //cscp.EditBox.BorderColor=RGB(150,150,150);
    cscp.EditBox.BorderColor=RGB(30,35,35);
    int h4=csc.csCNT_newContainer(idp, cscp);


    char*btnpath11="img\\arrPrev.bmp";
    char*btnpath12="img\\arrPrev2.bmp";
    char*btnpath21="img\\arrNext.bmp";
    char*btnpath22="img\\arrNext2.bmp";
    char*btnpath31="img\\arrUp.bmp";
    char*btnpath32="img\\arrUp2.bmp";
    char*btnpath41="img\\arrDown.bmp";
    char*btnpath42="img\\arrDown2.bmp";
    char*btnpath51="img\\btnclose3.bmp";
    char*btnpath52="img\\btnclose2.bmp";

    int n = 5;
    int* btn = (int*)malloc(n*sizeof(int));
    RECT marg = {1,1,2,2};
    if(withControlers)
    {
        if(!SameDesignCnts)
        {
            btn[0] = imgButton(cscp, h4, btnpath11, btnpath12, 0, {50,1,10,10}, marg);
            btn[1] = imgButton(cscp, h4, btnpath21, btnpath22, 0, {62,1,10,10}, marg);
            btn[2] = imgButton(cscp, h4, btnpath31, btnpath32, 0, {74,1,10,10}, marg);
            btn[3] = imgButton(cscp, h4, btnpath41, btnpath42, 0, {86,1,10,10}, marg);
            btn[4] = imgButton(cscp, h4, btnpath51, btnpath52, 0, {86,15,15,15}, {0});
        }
        else
            for(int i=0; i<n; i++)
            {
                btn[i] = imgButton(cscp, h4, btnpath11, btnpath12, 0,
                        {50+i*12,1,10,10}, marg, {15,15,15}, SameDesignCnts[i]);
            }
        idbtns = btn;
    }
    return h4;
}

int* simpleApp(int idpar)
{
    int** idbtn=0;
    idbtn=(int**)malloc(4*sizeof(int*));
    int* edit=(int*)malloc(4*sizeof(int));
    int x = 450, y = 50;
    edit[0] = editBox(cscp, idpar, "FACT","1.0", {x,y,100,40}, idbtn[0], 0);
    edit[1] = editBox(cscp, idpar, "R","255", {x,y+42,100,40}, idbtn[1], 0);
    edit[2] = editBox(cscp, idpar, "G","255", {x,y+84,100,40}, idbtn[2], 0);
    edit[3] = editBox(cscp, idpar, "B","255", {x,y+126,100,40}, idbtn[3], 0);
    int btn = textButton(cscp, idpar, "Teint !", {220,220,220}, {x,y+168,100,25});
    csSetAction(btn, WM_LBUTTONUP, simpleAppFunc, 1, edit);
    return edit;
}

void simpleAppFunc(csARGS Args)
{
    int ide = *(int*)Args[0];
    int idr = ((int*)Args[0])[1];
    int idg = ((int*)Args[0])[2];
    int idb = ((int*)Args[0])[3];
    char* str = (char*)malloc(100);
    sprintf(str,"");
    std::cout<<" Colors Changed !\n";

    GetWindowText(cv.cp[ide]->EditBox.EditBoxHandle, (LPSTR)str, 20);
    float cf = strtod(str,0);

    GetWindowText(cv.cp[idr]->EditBox.EditBoxHandle, (LPSTR)str, 20);
    int r = (int)strtod(str,0);

    GetWindowText(cv.cp[idg]->EditBox.EditBoxHandle, (LPSTR)str, 20);
    int g = (int)strtod(str,0);

    GetWindowText(cv.cp[idb]->EditBox.EditBoxHandle, (LPSTR)str, 20);
    int b = (int)strtod(str,0);

    int n = cv.CNTLIST.size();
    csCNTR_PARAMS* cp;
    COLORREF c2 = RGB(r,g,b);
    csRGB c3 = {r,g,b};
    for(int i=0; i<n; i++)
    {
        cp = (cv.cp[i]);
        if(cp->EditBox.AddEditBox)
        {
            COLORREF c = cp->EditBox.EditModeTextColor;
            cp->EditBox.EditModeTextColor = c*(1.0-cf) + c2*cf;

            csRGB cl = cp->EditBox.String.Color;
            cp->EditBox.String.Color = {cl.r*(1-cf)+c3.r*cf, cl.g*(1-cf)+c3.g*cf, cl.b*(1-cf)+c3.b*cf};
            InvalidateRect(cv.CNTLIST[i],0,1);
        }

        if(cp->Title.Text)
        {
            csRGB cl = cp->Title.Color;
            cp->Title.Color = {cl.r*(1-cf)+c3.r*cf, cl.g*(1-cf)+c3.g*cf, cl.b*(1-cf)+c3.b*cf};
            InvalidateRect(cv.CNTLIST[i],0,1);
        }
    }
    free(str);
}

csBUTTONGRID* canvasButtonGrid(int idCanvas)
{
    csBUTTONGRID bgrd(idCanvas, {2,2,300,25}, 10);
    bgrd.newBItem({1,1}, {15,15}, "Set Color", "img\\unlock.bmp", "img\\lock.bmp", "img\\unlock.bmp", "img\\unlock_dis.bmp");
    //bgrd.newBItem({-1,-1}, {15,15}, "Button ...", "img\\unlock.bmp", "img\\lock.bmp", "img\\unlock.bmp", "img\\unlock_dis.bmp",0);
    bgrd.newBItem({-1,-1}, {15,15}, "Button ...", "img\\unlock.bmp", "img\\lock.bmp", "img\\unlock.bmp", "img\\unlock_dis.bmp");
    bgrd.newBItem({-1,-1}, {15,15}, "Button ...", "img\\unlock.bmp", "img\\lock.bmp", "img\\unlock.bmp", "img\\unlock_dis.bmp");
    bgrd.newBItem({-1,-1}, {15,15}, "Button ...", "img\\unlock.bmp", "img\\lock.bmp", "img\\unlock.bmp", "img\\unlock_dis.bmp");
    bgrd.newBItem({-1,-1}, {15,15}, "Button ...", "img\\unlock.bmp", "img\\lock.bmp", "img\\unlock.bmp", "img\\unlock_dis.bmp");
    bgrd.newBItem({-1,-1}, {15,15}, "Button ...", "img\\unlock.bmp", "img\\lock.bmp", "img\\unlock.bmp", "img\\unlock_dis.bmp");
    bgrd.newBItem({-1,-1}, {15,15}, "Button ...", "img\\unlock.bmp", "img\\lock.bmp", "img\\unlock.bmp", "img\\unlock_dis.bmp");
    bgrd.newBItem({-1,-1}, {15,15}, "Button ...", "img\\unlock.bmp", "img\\lock.bmp", "img\\unlock.bmp", "img\\unlock_dis.bmp");
    bgrd.newBItem({-1,-1}, {15,15}, "Button ...", "img\\unlock.bmp", "img\\lock.bmp", "img\\unlock.bmp", "img\\unlock_dis.bmp");
    bgrd.newBItem({-1,-1}, {15,15}, "Button ...", "img\\unlock.bmp", "img\\lock.bmp", "img\\unlock.bmp", "img\\unlock_dis.bmp");
    bgrd.setItemType(0, CS_BGRD_BI_SELECTION);
    //bgrd.setActiveItem(2);
    //bgrd.setItemType(3, CS_BGRD_UNI_SELECTION);
    bgrd.create();
    //bgrd.getParams()->AutoAlphaFade. = 1;
    bgrd.getParams()->AutoAlphaFade.Geometry = {0,0,0,0};
    bgrd.getParams()->AutoAlphaFade.FadeTime = 8;
    bgrd.getParams()->AutoAlphaFade.AlphaMin = 10;
    bgrd.getParams()->AutoAlphaFade.State = CS_AAF_SHOW_CNTR;
    bgrd.getParams()->AutoAlphaFade.SetGeometry = 0;
    bgrd.getParams()->MouseLeaveTransparency = 1;

    return csf_alloc2<csBUTTONGRID>(1,bgrd);
}


int* csRealtimeDrawing(int& idCanvas, int& idboard, int& idmousepos, csBUTTONGRID*subMenus)
{
    int* ids = (int*)malloc(30*sizeof(int));
    int** idbtn=(int**)malloc(7*sizeof(int*));
    csLOCKED_MODE lm={0};
    lm.ExternalUnlocking = 1;
    lm.Lockable = 1;
    lm.LockingColor = {0};

    int titlePos = 3, dy = 40*10, ethk=15;
    bool withControlers=0;

    ids[21] = idmousepos;

    //ids[0] = staticCnt2(cscp, cv.CNTPARID[idCanvas], "", {30,30,36},{0,0,200,700},1); cv.cp[ids[0]]->MouseLeaveRemoveBkg = 1;
    ids[0] = idboard;
    //ids[0] = staticCnt2(cscp, cv.CNTPARID[idCanvas], "", {50,50,50},{0,0,200,700},1); cv.cp[ids[0]]->Transparency = 20;
    ids[1] = imgButton(cscp, ids[0], "img\\app\\newpoint2.bmp","img\\app\\newpoint3.bmp", "img\\app\\newpoint3.bmp",{1,1,20,20},{0});
    ids[8] = imgButton(cscp, ids[0], "img\\app\\newline2.bmp","img\\app\\newline2.bmp", "img\\app\\newline3.bmp", {22,1,20,20},{0});
    ids[14] = imgButton(cscp, ids[0], "img\\app\\newpolygon2.bmp","img\\app\\newpolygon3.bmp", "img\\app\\newpolygon3.bmp", {44,1,20,20},{0});
    ids[15] = imgButton(cscp, ids[0], "img\\app\\newimage2.bmp","img\\app\\newimage2.bmp", "img\\app\\newimage2.bmp", {66,1,20,20},{0});
    ids[16] = imgButton(cscp, ids[0], "img\\app\\delpoint2_sel.bmp","img\\app\\delpoint2.bmp", "img\\app\\delpoint2.bmp", {88,1,20,20},{0});
    ids[17] = imgButton(cscp, ids[0], "img\\app\\delline2_sel.bmp","img\\app\\delline2.bmp", "img\\app\\delline2.bmp", {110,1,20,20},{0});
    ids[18] = imgButton(cscp, ids[0], "img\\app\\delpolygon2_sel.bmp","img\\app\\delpolygon2.bmp", "img\\app\\delpolygon2.bmp", {132,1,20,20},{0});
    ids[19] = imgButton(cscp, ids[0], "img\\app\\delimage2_sel.bmp","img\\app\\delimage2.bmp", "img\\app\\delimage2.bmp", {154,1,20,20},{0});
    ids[23] = imgButton(cscp, ids[0], "img\\app\\select1.bmp","img\\app\\select2.bmp", "img\\app\\select3.bmp", {176,1,20,20},{0});

    csLIST<int> lockList;
    lockList +=  ids[1];
    lockList += ids[8];
    lockList += ids[14];
    lockList += ids[15];
    lockList += ids[23];
    cv.EXTUNLOCKINGCNT[ids[1]] = lockList;
    cv.EXTUNLOCKINGCNT[ids[8]] = lockList;
    cv.EXTUNLOCKINGCNT[ids[14]] = lockList;
    cv.EXTUNLOCKINGCNT[ids[15]] = lockList;
    cv.EXTUNLOCKINGCNT[ids[23]] = lockList;


    ids[9] = staticCnt2(cscp, ids[0], "", {30,30,35},{2,72,196,dy-4},1); //cv.cp[ids[9]]->MouseLeaveRemoveBkg = 1;
    ids[10] = staticCnt2(cscp, ids[0], "", {35,35,35},{1,31,198,20},1); //cv.cp[ids[10]]->MouseLeaveRemoveBkg = 1;
    ids[13] = staticCnt2(cscp, ids[0], "", {35,35,35},{1,51,198,20},1); //cv.cp[ids[13]]->MouseLeaveRemoveBkg = 1;
    ids[12] = staticCnt2(cscp, ids[9], "", {30,30,30},{2,2,95,dy-8},1); //cv.cp[ids[12]]->MouseLeaveRemoveBkg = 1;
    ids[25] = staticCnt2(cscp, ids[9], "", {30,40,30},{98,2,98,dy-8},1); //cv.cp[ids[25]]->MouseLeaveRemoveBkg = 1;
    ids[20] = staticCnt2(cscp, ids[25], "", {30,30,40},{2,2,96,dy-10},1); //cv.cp[ids[20]]->MouseLeaveRemoveBkg = 1;
    ids[11] = staticCnt2(cscp, ids[25], "", {40,30,30},{2,2,96,dy-10},1); //cv.cp[ids[11]]->MouseLeaveRemoveBkg = 1;
    csGeometryLink(&ids[25], 2, csGLP4_PTR(csGLP4{ids[20], {0,0,2}, {0,0,2}, {4,1.0,0}, {4,1.0,0}}),
                                csGLP4_PTR(csGLP4{ids[11], {0,0,2}, {0,0,2}, {4,1.0,0}, {4,1.0,0}}));
    //SetWindowPos(csHWND(ids[9]),0,0,0,196, dy-5, SWP_NOMOVE);
    csVLC vlc1(&ids[9], 2, 2,0);
    vlc1.newContainer(&ids[12], 10);
    vlc1.newContainer(&ids[25],10);
    //csPARAMS(ids[9])->SizingAreaLength = 4;
    //csPARAMS(ids[9])->HTRight = 1;

    ids[2] = editBox(cscp, ids[0], "THICK ","1", {1,3+71+dy,95,ethk}, idbtn[0], 0, titlePos, withControlers);
    ids[3] = editBox(cscp, ids[0], "STYLE ","0", {1+95+5,3+71+dy,95,ethk}, idbtn[1], 0, titlePos, withControlers);
    ids[4] = editBox(cscp, ids[0], "R ","255", {1,12+71+(ethk)*2+dy,48,ethk}, idbtn[2], 0, titlePos, withControlers);
    ids[5] = editBox(cscp, ids[0], "G ","255", {1+45+5,12+71+(ethk)*2+dy,45,ethk}, idbtn[3], 0, titlePos, withControlers);
    ids[6] = editBox(cscp, ids[0], "B ","255", {1+(45+5)*2,12+71+(ethk)*2+dy,45,ethk}, idbtn[4], 0, titlePos, withControlers);
    ids[22] = editBox(cscp, ids[0], "A ","0", {1+(45+5)*3,12+71+(ethk)*2+dy,45,ethk}, idbtn[6], 0, titlePos, withControlers);
    ids[7] = editBox(cscp, ids[0], "ACTIVE LINE ","0", {1,6+71+(ethk)+dy,198,ethk}, idbtn[5], 0, titlePos, withControlers);
    ids[24] = staticCnt2(cscp, ids[0], "", {30,40,30},{0,68+dy,198,170},1); //cv.cp[ids[24]]->MouseLeaveRemoveBkg = 1;

    csHLC hlc1(&ids[0], 72, 2, 3);
    hlc1.newContainer(&ids[9]);
    hlc1.newContainer(&ids[24]);

    csRaise(ids[11], 3, 1, 0, 0, 1, 0);
    //csRaise(ids[12], 3, 1.0, 0, 1, 1, 1);
    int level = 5;
    float sharp = 1;
    cv.CTX[ids[12]].borderGradientColor = csTint(cv.cp[ids[12]]->BackgroundColor, {0}, .5);
    cv.CTX[ids[12]].brdGrad_right = {level,3,0,0,sharp};
    csRaise(ids[20], 3, 1.9, 0, 0, 1, 0);

    cv.CTX[ids[24]].borderGradientColor = csTint({40,40,40}, {0}, .45);
    cv.CTX[ids[24]].brdGrad_top = {4,3,0,0,sharp};

    cv.EXTHIDECNT[ids[8]] += ids[11];
    cv.EXTHIDECNT[ids[14]] += ids[20];

    csTEXTBUTTON capt;
    capt.create(ids[0], "Screen capture", {2,580,196,25}, 0);
    capt.setColors({220,220,220}, {10,10,10},{200,200,200},{220,220,220},{230,230,230}, {30,30,30}, 1, 0);
    capt.getParams()->Show = 0;

    csRADIOBUTTON rb(ids[10],100,2);
    rb.setImageSize({15,15});
    rb.setDefaultFont("Arial",{13,0});
    rb.setDefaultColors(RGB(230,230,255), RGB(250,250,255), RGB(0,0,0));
    rb.newItem(0,{0},2);
    rb.setTitle(0,"Polyline");
    rb.setTitle(1,"Hand Free");
    rb.create();
    csRADIOBUTTON rb1(ids[13],100,2);
    rb1.setDefaultFont("Arial",{13,0});
    rb1.newItem("Locked",{0},1,"img\\lock.bmp", "img\\lock.bmp", "img\\lock.bmp");
    rb1.newItem("Unlocked",{0},1,"img\\unlock.bmp","img\\unlock.bmp", "img\\unlock.bmp");
    rb1.create();

    csRADIOBUTTON *prblines, rblines(ids[11]);
    prblines = (csRADIOBUTTON*)calloc(1,sizeof(csRADIOBUTTON));
    //rblines.zebraStyle({255,255,255},0.05);
    rblines.copyPasteStyle();
    rblines.setOffset({0,0});
    rblines.setDefaultFont("Arial",{12});
    rblines.setDefaultTitle("Line");
    rblines.setImage("img\\app\\line.bmp","img\\app\\line_sel.bmp","img\\app\\line_sel.bmp","img\\app\\line_inact.bmp",{15,15});
    //rblines.newItem(0,{0},2);
    rblines.create();
    *prblines=rblines;
    csSCROLLBAR vsblines = csAddVScrollBar(&ids[11]);
    csSCROLLBAR hsblines = csAddHScrollBar(&ids[11]);
    csGeometryLink(&ids[11], 2, csGLP4_PTR(csGLP4{vsblines.getId(), {12,1.0,0}, {0,0,0}, {0,0,10}, {10,1.0,0}}),
                               csGLP4_PTR(csGLP4{hsblines.getId(), {0,0,0}, {10,1.0,0}, {2,1.0,0}, {0,0,10}}));

    csRADIOBUTTON *prbPolygon, rbPolygon(ids[20]);
    prbPolygon = (csRADIOBUTTON*)calloc(1,sizeof(csRADIOBUTTON));
    //rbPolygon.zebraStyle({255,255,255},0.05);
    rbPolygon.copyPasteStyle();
    rbPolygon.setOffset({0,0});
    rbPolygon.setDefaultFont("Arial",{12});
    rbPolygon.setDefaultTitle("Polygon");
    rbPolygon.setImage("img\\app\\polygon.bmp","img\\app\\polygon_sel.bmp","img\\app\\polygon_sel.bmp","img\\app\\polygon_inact.bmp",{15,15});
    //rblines.newItem(0,{0},2);
    rbPolygon.create();
    *prbPolygon=rbPolygon;
    csSCROLLBAR vsbpolygon = csAddVScrollBar(&ids[20]);
    csSCROLLBAR hsbpolygon = csAddHScrollBar(&ids[20]);
    csGeometryLink(&ids[20], 2, csGLP4_PTR(csGLP4{vsbpolygon.getId(), {12,1.0,0}, {0,0,0}, {0,0,10}, {10,1.0,0}}),
                               csGLP4_PTR(csGLP4{hsbpolygon.getId(), {0,0,0}, {10,1.0,0}, {2,1.0,0}, {0,0,10}}));

    csRADIOBUTTON *prblayer, rblayer(ids[12]);
    prblayer = (csRADIOBUTTON*)calloc(1,sizeof(csRADIOBUTTON));
    //rblayer.zebraStyle({255,255,255},0.05);
    rblayer.copyPasteStyle();
    rblayer.setOffset({0,0});
    rblayer.setDefaultFont("Arial",{12});
    rblayer.setDefaultTitle("Layer");
    rblayer.setImage("img\\app\\layer.bmp","img\\app\\layer_sel.bmp","img\\app\\layer_sel.bmp","img\\app\\layer_sel.bmp",{15,15});
    rblayer.newItem(0,{0},2*10);
    rblayer.create();
    *prblayer=rblayer;
    csSCROLLBAR vsblayer = csAddVScrollBar(&ids[12]);
    csSCROLLBAR hsblayer = csAddHScrollBar(&ids[12]);
    csGeometryLink(&ids[12], 2, csGLP4_PTR(csGLP4{vsblayer.getId(), {12,1.0,0}, {0,0,0}, {0,0,10}, {10,1.0,0}}),
                               csGLP4_PTR(csGLP4{hsblayer.getId(), {0,0,0}, {10,1.0,0}, {2,1.0,0}, {0,0,10}}));

    csEXTERN_HDC extHDC;
    extHDC.LoadImage("img\\arrUp.bmp",{15,15});
    csCTX(ids[12]).extHDC.insertEnd(extHDC);

    /*csRADIOBUTTON *prbWork, rbWork(ids[24]);
    prbWork = (csRADIOBUTTON*)calloc(1,sizeof(csRADIOBUTTON));
    rbWork.setMarging({0,0});
    rbWork.setDefaultFont("Calibri",{12});
    rbWork.setDefaultTitle("Work");
    rbWork.setDefaultSize({300,20});
    rbWork.setImage("img\\app\\work.bmp","img\\app\\work_sel.bmp","img\\app\\work_sel.bmp",{15,15});
    rbWork.newItem(0,{0},2*10,10);
    rbWork.create();
    *prbWork=rbWork;*/
    csSCROLLBAR vsWork = csAddVScrollBar(&ids[24]);
    csSCROLLBAR hsWork = csAddHScrollBar(&ids[24]);
    csGeometryLink(&ids[24], 2, csGLP4_PTR(csGLP4{vsWork.getId(), {12,1.0,0}, {0,0,0}, {0,0,10}, {10,1.0,0}}),
                               csGLP4_PTR(csGLP4{hsWork.getId(), {0,0,0}, {10,1.0,0}, {2,1.0,0}, {0,0,10}}));

    csBUTTONGRID bgWork(ids[24],{3,3,500/3,1000/3},1,0);
    bgWork.setTextPosition(CS_RDBTN_TEXT_AFTER);
    bgWork.setTextMarging(1,1);
    bgWork.setMarging(0,0);
    bgWork.showTitle(1);
    SIZE sz = {3,3};
    /*bgWork.newBItem({0,0},sz," par 1 ","img\\app\\work.bmp");
    bgWork.newBItem({-1,-1},sz,"par 2 ","img\\app\\work.bmp");
    bgWork.newBItem({-1,-1},sz,"par 3 ","img\\app\\work.bmp");
    bgWork.newBItem({-1,-1},sz,"par 4 ","img\\app\\work.bmp");
    bgWork.newBItem({-1,-1},sz,"par 5 ","img\\app\\work.bmp");
    bgWork.newBItem({-1,-1},sz,"par 6 ","img\\app\\work.bmp");*/
    int height = 70;
    bgWork.makeNTemplate("Action history","img\\app\\work.bmp",{9,9}, height, {120,3*3});
    //bgWork.setXRect_model01(30, height);
    bgWork.create();
    bgWork.setActiveItem(0);

    void rltDraw_newLineBtn(csARGS Args);
    void rltDraw_newPolygonBtn(csARGS Args);
    void rltDraw_Canv_leftbtndown(csARGS Args);
    void rltDraw_Canv_rightbtndown(csARGS Args);
    void rltDraw_Canv_mousemove(csARGS Args);
    void rltDraw_Canv_cancelLast(csARGS Args);
    void rltDraw_Canv_leftbtnup(csARGS Args);
    void drawCurrentPolygon(csARGS Args);
    void drawCurrentPolygon_keyup(csARGS Args);

    void drawText(csARGS Args);
    void screenCapture(csARGS Args);

    int*activeGdiLine = (int*)malloc(sizeof(int));
    *activeGdiLine = 0;
    int*lastListSize = (int*)malloc(sizeof(int));
    *lastListSize = 0;
    bool*newDwg = (bool*)malloc(sizeof(bool));
    *newDwg = 0;
    bool*lbtnDown = csf_alloc2<bool>(1,0);
    POINT *psaved = csf_alloc2<POINT>(1,{0});


    csBUTTONGRID* canvBGrid = canvasButtonGrid(idCanvas);
    cv.cp[canvBGrid->getId()]->Show = 0; //hide

    csCOLORPALETTE palette(idCanvas, {100,100,268,400}, {200,100, 150, 0});
    csDetachCnt(palette.getId());
    csCOLORPALETTE *ppalette = csf_alloc2<csCOLORPALETTE>(1,palette);


    csSetAction(ids[8], WM_LBUTTONUP, rltDraw_newLineBtn, 16, &idCanvas, ids, prblines->getActiveItem(),
                    rb.getActiveItem(), prblines, rb1.getActiveItem(), activeGdiLine, lastListSize, newDwg,
                    prbPolygon, lbtnDown, psaved, ppalette, canvBGrid, prblayer, subMenus);
    csARGS args = cv.cp[ids[8]]->CntEventsFunc.LBUTTONUP_ARGS[0];
    csSetAction(ids[14], WM_LBUTTONUP, rltDraw_newPolygonBtn, args);
    csSetAction(idCanvas, WM_LBUTTONUP, rltDraw_Canv_leftbtnup, args);
    csSetAction(idCanvas, WM_LBUTTONDOWN, rltDraw_Canv_leftbtndown, args);
    csSetAction(idCanvas, WM_RBUTTONDOWN, rltDraw_Canv_rightbtndown, args);
    csSetAction(idCanvas, WM_MOUSEMOVE, rltDraw_Canv_mousemove, args);
    csSetAction(idCanvas, WM_TIMER, rltDraw_Canv_cancelLast, args);

    int idcp = capt.getId();
    csSetAction(idcp, WM_LBUTTONUP,screenCapture,1, &idCanvas);


    void deleteItem_action(csARGS Args);
    csSetAction(ids[11], WM_KEYUP,deleteItem_action,args);
    csSetAction(ids[20], WM_KEYUP,deleteItem_action,args);
    // la precedure de dessin du polygon selectionné est améliorée par rapport
    // celle du dessin de la ligne
    csSetAction(ids[20], WM_LBUTTONUP,drawCurrentPolygon,args);
    csSetAction(ids[20], WM_KEYDOWN,drawCurrentPolygon_keyup,args);
    csSetAction(idCanvas, WM_KEYUP,deleteItem_action,args);


    void linesDesign(int id, int n, COLORREF color, int thickness, POINT init,POINT center);
    //linesDesign(cv.CNTPARID[idCanvas], 250, RGB(40,40,40), 1, {50,50}, {0,0});
    //linesDesign(cv.CNTPARID[idCanvas], 250, RGB(40,40,40), 1, {50,50}, {CS_CYSCREEN/2,0});
    csRGBA bcol = cv.cp[0]->BackgroundColor;
    linesDesign(0, 250, RGB(bcol.r-10,bcol.g-10,bcol.b-10), 1, {0,0}, {CS_CYSCREEN/2,0});


    //SetParent(cv.CNTLIST[idCanvas], cv.CNTLIST[cv.CNTPARID[idCanvas]]);
    //csSetBackgroundImage(scroll,"img\\hscroll.bmp",{50,10});


    void showCoords_timer(csARGS Args);
    POINT*psaved_old = csf_alloc2<POINT>(1,{0});
    csSetAction(idmousepos, WM_TIMER,showCoords_timer,2,psaved, psaved_old);


    //cv.CTX[idCanvas].drawPolygonVertices(1);

    return ids;
}

void screenCapture(csARGS Args)
{
    int idcanv = *(int*)Args[0];
    //ShowWindow(cv.CNTLIST[0], SW_MINIMIZE);
    RECT r = cv.CNTRECT[0];
    SetWindowPos(cv.CNTLIST[0],0, CS_CXSCREEN+1,0,1,1,SWP_NOZORDER);
    HDC screenDC = GetDC(0);

    HDC hdc = cv.CTX[idcanv].getDC();
    SetStretchBltMode(hdc,HALFTONE);
    StretchBlt(hdc, 0,0,900,650, screenDC, 0,0,CS_CXSCREEN, CS_CYSCREEN, SRCCOPY);
    //BitBlt(hdc, 205,5,700,600, screenDC, 0,0, SRCCOPY);
    ReleaseDC(0,screenDC);
    InvalidateRect(cv.CNTLIST[idcanv],0,1);
    SetWindowPos(cv.CNTLIST[0],0, r.left,r.top,r.right-r.left,r.bottom-r.top,SWP_NOZORDER);
}


void drawText(csARGS Args)
{
    int id = (int)Args;
    char**str=(char**)Args[0];
    POINT* pos = (POINT*)Args[1];
    int n = *(int*)Args[2];
    COLORREF color = *(COLORREF*)Args[3];
    HFONT font = *(HFONT*)Args[4];

    HDC dc = cv.CTX[id].getDC();
    SelectFont(dc, font);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, color);
    for(int i = 0; i<n; i++)
        TextOut(dc,pos[i].x,pos[i].y,(LPCSTR)str[i],strlen(str[i]));

}

void drawCurrentLine(csARGS Args);
void drawCurrentPolygon(csARGS Args);
/*void deleteItem_action0(csARGS Args)
{
    int idcanv = *(int*)Args[0];
    int*ids=(int*)Args[1];
    csRADIOBUTTON* rb=(csRADIOBUTTON*)Args[4];
    csRADIOBUTTON* rbp=(csRADIOBUTTON*)Args[14];


}*/
void deleteItem_action(csARGS Args)
{
    int idcanv = *(int*)Args[0];
    int*ids=(int*)Args[1];
    csRADIOBUTTON* rb=(csRADIOBUTTON*)Args[4];
    csRADIOBUTTON* rbp=(csRADIOBUTTON*)Args[9];

    if((WPARAM)Args==VK_DELETE && (cv.HWNDFOCUS==(HWND)Args || cv.HWNDFOCUS==cv.CNTLIST[idcanv]))
    {std::cout<<" delete --\n";
        int type = cv.CTX[idcanv].getActiveDwgObject();

        if(type == CS_DWGTYPE_POLYLINE)
        {
            if(cv.CTX[idcanv].getgdiLineNum()>0)
            {
                int i = *(rb->getActiveItem());
                cv.CTX[idcanv].deletegdiLine(i);
                rb->removeItem(i);
                rb->create();
                drawCurrentLine(Args);
                InvalidateRect(cv.CNTLIST[idcanv],0,1);
            }
        }
        else if(type == CS_DWGTYPE_POLYGON)
        {
            if(cv.CTX[idcanv].getPolygonsNum()>0)
            {
                int i = *(rbp->getActiveItem());
                std::cout<<i<<"  --\n";
                cv.CTX[idcanv].deletePolygon(i);
                rbp->removeItem(i);
                rbp->create();
                rbp->autoRepos();
                //cv.CTX[idcanv].setActivePolygonId(*(rbp->getActiveItem()));
                cv.CTX[idcanv].updatePolygonsDwg();
                cv.CTX[idcanv].redrawBackground();
                cv.CTX[idcanv].setActivePolygonId(*(rbp->getActiveItem()));
                cv.CTX[idcanv].showSelectedPolygon();
                InvalidateRect(cv.CNTLIST[idcanv],0,1);
                std::cout<<i<<"  --\n";
            }
        }
    }
}

void changeDwgColor(csARGS Args)
{
    int idCanvas = *(int*)Args[0];
    int*ids=(int*)Args[1];
    if(cv.cp[ids[23]]->LockedMode.Locked)
    {
        csCOLORPALETTE* palette = (csCOLORPALETTE*)Args[12];
        csSURFACE* srf = &cv.CTX[idCanvas];
        if(srf->getActiveDwgObject() == CS_DWGTYPE_POLYGON && srf->getPolygonsNum())
        {
           int i = srf->getActivePolygonId();
           if(i < srf->getPolygonsNum());
           {
                srf->getPolygonParams(i)->color = palette->getSelectedColor();
                srf->updatePolygonsDwg();
                srf->redrawBackground();
                srf->showSelectedPolygon();
                InvalidateRect(cv.CNTLIST[idCanvas],0,1);
           }
        }
    }
}

void rltDraw_newLineBtn(csARGS Args)
{
    int idCanvas = *(int*)Args[0];
    int*ids=(int*)Args[1];
    csRADIOBUTTON* rb=(csRADIOBUTTON*)Args[4];
    bool *newDwg = (bool*)Args[8];

    int activeLine = 0;
    if(cv.cp[ids[8]]->LockedMode.Locked)
    {
        *newDwg = 1;
        //ShowWindow(cv.CNTLIST[ids[20]],0);
        //ShowWindow(cv.CNTLIST[ids[11]],1);
        //cv.cp[ids[20]]->Show=0;
        //cv.cp[ids[11]]->Show=1;
        rb->setCntState(0); // eviter des calculs excessifs conduisant aux bogue
        /*cv.cp[ids[1]]->LockedMode.Locked = 0;//fermer le mode 'point'
        cv.cp[ids[1]]->LockedMode.ExtBool = 1;//fermer le mode 'point'
        cv.cp[ids[14]]->LockedMode.Locked = 0;//fermer le mode 'Polygone'
        cv.cp[ids[14]]->LockedMode.ExtBool = 1;//fermer le mode 'point'
        cv.cp[ids[15]]->LockedMode.Locked = 0;//fermer le mode 'image'
        cv.cp[ids[15]]->LockedMode.ExtBool = 1;//fermer le mode 'image'
        cv.cp[ids[23]]->LockedMode.Locked = 0;//fermer le mode 'selection'
        cv.cp[ids[23]]->LockedMode.ExtBool = 1;//fermer le mode 'selection'*/
        cv.CTX[idCanvas].drawActiveAboveAll(1);//place le dessin en cours au-dessus de tous les autres
        cv.CTX[idCanvas].setActiveDwgObject(CS_DWGTYPE_POLYLINE);
        cv.cp[idCanvas]->Cursor = LoadCursor(0,IDC_CROSS);
        SendMessage(cv.CNTLIST[ids[23]], WM_LBUTTONUP, 0,0);
    }
    else
    {
        /*cv.cp[ids[1]]->LockedMode.Locked = 0;//fermer le mode 'point'
        cv.cp[ids[1]]->LockedMode.ExtBool = 1;//fermer le mode 'point'
        cv.cp[ids[8]]->LockedMode.Locked = 0;//fermer le mode 'Ligne'
        cv.cp[ids[8]]->LockedMode.ExtBool = 1;//fermer le mode 'Ligne'
        cv.cp[ids[15]]->LockedMode.Locked = 0;//fermer le mode 'image'
        cv.cp[ids[15]]->LockedMode.ExtBool = 1;//fermer le mode 'image'
        cv.cp[ids[23]]->LockedMode.Locked = 0;//fermer le mode 'selection'
        cv.cp[ids[23]]->LockedMode.ExtBool = 1;//fermer le mode 'selection'*/
        //SendMessage(cv.CNTLIST[ids[23]], WM_LBUTTONUP, 0,0);
        rb->setCntState(1);
        cv.cp[idCanvas]->Cursor = LoadCursor(0,IDC_ARROW);
    }
}

void rltDraw_newPolygonBtn(csARGS Args)
{
    int idCanvas = *(int*)Args[0];
    int*ids=(int*)Args[1];
    csRADIOBUTTON* rbp=(csRADIOBUTTON*)Args[9];
    bool *newDwg = (bool*)Args[8];

    if(cv.cp[ids[14]]->LockedMode.Locked)
    {
        //ShowWindow(cv.CNTLIST[ids[20]],1);
        //ShowWindow(cv.CNTLIST[ids[11]],0);
        //cv.cp[ids[20]]->Show=1;
        //cv.cp[ids[11]]->Show=0;
        *newDwg = 1;
        rbp->setCntState(0); // eviter des calculs excessifs conduisant aux bogue
        rbp->refresh();
        /*cv.cp[ids[1]]->LockedMode.Locked = 0;//fermer le mode 'point'
        cv.cp[ids[1]]->LockedMode.ExtBool = 1;//fermer le mode 'point'
        cv.cp[ids[8]]->LockedMode.Locked = 0;//fermer le mode 'Polygone'
        cv.cp[ids[8]]->LockedMode.ExtBool = 1;//fermer le mode 'point'
        cv.cp[ids[15]]->LockedMode.Locked = 0;//fermer le mode 'image'
        cv.cp[ids[15]]->LockedMode.ExtBool = 1;//fermer le mode 'image'
        cv.cp[ids[23]]->LockedMode.Locked = 0;//fermer le mode 'selection'
        cv.cp[ids[23]]->LockedMode.ExtBool = 1;//fermer le mode 'selection'*/
        cv.CTX[idCanvas].drawActiveAboveAll(1); //place le dessin en cours au-dessus de tous les autres
        cv.CTX[idCanvas].setActiveDwgObject(CS_DWGTYPE_POLYGON);
        if(cv.CTX[idCanvas].getPolygonsNum()>0)
            cv.CTX[idCanvas].setActivePolygonId(cv.CTX[idCanvas].getPolygonsNum()-1);
        cv.CTX[idCanvas].updatePolygonsDwg();
        cv.cp[idCanvas]->Cursor = LoadCursor(0,IDC_CROSS);

    }
    else
    {
        //cv.cp[ids[23]]->LockedMode.Locked = 1;//activer le mode 'selection'
        //SendMessage(cv.CNTLIST[ids[23]], WM_LBUTTONUP, 0,0);

        rbp->setCntState(1);
        rbp->refresh();
        cv.cp[idCanvas]->Cursor = LoadCursor(0,IDC_ARROW);

        cv.CTX[idCanvas].updatePolygonsDwg();
        cv.CTX[idCanvas].redrawBackground();
        cv.CTX[idCanvas].showSelectedPolygon();
    }
}

void rltDraw_newPointBtn(csARGS Args)
{
    int idCanvas = *(int*)Args[0];
    int*ids=(int*)Args[1];
    csRADIOBUTTON* rbp=(csRADIOBUTTON*)Args[9];
    bool *newDwg = (bool*)Args[8];

    if(cv.cp[ids[14]]->LockedMode.Locked)
    {
        //ShowWindow(cv.CNTLIST[ids[20]],1);
        //ShowWindow(cv.CNTLIST[ids[11]],0);
        //cv.cp[ids[20]]->Show=1;
        //cv.cp[ids[11]]->Show=0;
        *newDwg = 1;
        rbp->setCntState(0); // eviter des calculs excessifs conduisant aux bogue
        /*cv.cp[ids[1]]->LockedMode.Locked = 0;//fermer le mode 'point'
        cv.cp[ids[1]]->LockedMode.ExtBool = 1;//fermer le mode 'point'
        cv.cp[ids[8]]->LockedMode.Locked = 0;//fermer le mode 'Polygone'
        cv.cp[ids[8]]->LockedMode.ExtBool = 1;//fermer le mode 'Polygone'
        cv.cp[ids[15]]->LockedMode.Locked = 0;//fermer le mode 'image'
        cv.cp[ids[15]]->LockedMode.ExtBool = 1;//fermer le mode 'image'
        cv.cp[ids[23]]->LockedMode.Locked = 0;//fermer le mode 'selection'
        cv.cp[ids[23]]->LockedMode.ExtBool = 1;//fermer le mode 'selection'*/
        cv.CTX[idCanvas].drawActiveAboveAll(1); //place le dessin en cours au-dessus de tous les autres
        cv.CTX[idCanvas].setActiveDwgObject(CS_DWGTYPE_POLYGON);
        cv.CTX[idCanvas].setActivePolygonId(cv.CTX[idCanvas].getPolygonsNum()-1);
        cv.CTX[idCanvas].updatePolygonsDwg();
        cv.cp[idCanvas]->Cursor = LoadCursor(0,IDC_CROSS);

    }
    else
    {
        //cv.cp[ids[23]]->LockedMode.Locked = 1;//activer le mode 'selection'
        //SendMessage(cv.CNTLIST[ids[23]], WM_LBUTTONUP, 0,0);

        rbp->setCntState(1);
        cv.cp[idCanvas]->Cursor = LoadCursor(0,IDC_ARROW);

        cv.CTX[idCanvas].updatePolygonsDwg();
        cv.CTX[idCanvas].redrawBackground();
        cv.CTX[idCanvas].showSelectedPolygon();
    }
}

void rltDraw_Canv_leftbtndown(csARGS Args)
{
    int idCanvas = *(int*)Args[0];
    int*ids=(int*)Args[1];
    csRADIOBUTTON* rb=(csRADIOBUTTON*)Args[4];
    csRADIOBUTTON* rbp=(csRADIOBUTTON*)Args[9];
    bool *newDwg = (bool*)Args[8];

    if(cv.cp[ids[8]]->LockedMode.Locked)
    {
        int *activeLine = (int*)Args[2];

        if(*newDwg)
        {
            char* str = (char*)malloc(100);
            sprintf(str,"");

            cout<<"start drawing !\n";

            GetWindowText(cv.cp[ids[2]]->EditBox.EditBoxHandle, (LPSTR)str, 20);
            int thk = (int)strtod(str,0);

            GetWindowText(cv.cp[ids[3]]->EditBox.EditBoxHandle, (LPSTR)str, 20);
            int style = (int)strtod(str,0);

            /*GetWindowText(cv.cp[ids[4]]->EditBox.EditBoxHandle, (LPSTR)str, 20);
            int r = (int)strtod(str,0);

            GetWindowText(cv.cp[ids[5]]->EditBox.EditBoxHandle, (LPSTR)str, 20);
            int g = (int)strtod(str,0);

            GetWindowText(cv.cp[ids[6]]->EditBox.EditBoxHandle, (LPSTR)str, 20);
            int b = (int)strtod(str,0);

            GetWindowText(cv.cp[ids[22]]->EditBox.EditBoxHandle, (LPSTR)str, 20);
            int a = (int)strtod(str,0);*/

            //if(cv.CTX[idCanvas].getgdiLineSize())

            csCOLORPALETTE* palette = (csCOLORPALETTE*)Args[12];
            csRGBA c = palette->getSelectedColor();

            cv.CTX[idCanvas].newgdiEmptyLine(RGB(c.r, c.g, c.b), thk, style);
            rb->newItem(0,{0},1);
            rb->create();
            rb->autoRepos();

            *activeLine = cv.CTX[idCanvas].getgdiLineNum()-1;
            sprintf(str,"%d", *activeLine);
            SetWindowText(cv.cp[ids[7]]->EditBox.EditBoxHandle, (LPSTR)str);
            InvalidateRect(cv.CNTLIST[ids[7]],0,1);

            *newDwg=0;
            free(str);
        }
        /*else
        {*/
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(cv.CNTLIST[idCanvas], &p);
            if(cv.CTX[idCanvas].getgdiLineSize(*activeLine)==0)
            {
                //cv.CTX[idCanvas].setgdiLinePoint(activeLine, 0, p);
                cv.CTX[idCanvas].newgdiLinePoint(*activeLine,p);
                cv.CTX[idCanvas].newgdiLinePoint(*activeLine,p);
            }
            else
            {
                cv.CTX[idCanvas].setgdiLinePoint(*activeLine, cv.CTX[idCanvas].getgdiLineSize(*activeLine)-1, p);
                cv.CTX[idCanvas].newgdiLinePoint(*activeLine,{0,0});
            }
        //}
    }
    else if(cv.cp[ids[14]]->LockedMode.Locked)
    {
        if(*newDwg)
        {
            char* str = (char*)malloc(100);
            sprintf(str,"");

            cout<<"start drawing !\n";

            GetWindowText(cv.cp[ids[2]]->EditBox.EditBoxHandle, (LPSTR)str, 20);
            int thk = (int)strtod(str,0);

            GetWindowText(cv.cp[ids[3]]->EditBox.EditBoxHandle, (LPSTR)str, 20);
            int style = (int)strtod(str,0);

            /*GetWindowText(cv.cp[ids[4]]->EditBox.EditBoxHandle, (LPSTR)str, 20);
            int r = (int)strtod(str,0);

            GetWindowText(cv.cp[ids[5]]->EditBox.EditBoxHandle, (LPSTR)str, 20);
            int g = (int)strtod(str,0);

            GetWindowText(cv.cp[ids[6]]->EditBox.EditBoxHandle, (LPSTR)str, 20);
            int b = (int)strtod(str,0);

            GetWindowText(cv.cp[ids[22]]->EditBox.EditBoxHandle, (LPSTR)str, 20);
            int a = (int)strtod(str,0);*/

            //if(cv.CTX[idCanvas].getgdiLineSize())

            csCOLORPALETTE* palette = (csCOLORPALETTE*)Args[12];
            csRGBA c = palette->getSelectedColor();

            cv.CTX[idCanvas].newPolygon(c, thk);
            rbp->newItem(0,{0},1);
            rbp->create();
            rbp->autoRepos();

            cv.CTX[idCanvas].setActivePolygonId(cv.CTX[idCanvas].getPolygonsNum()-1);
            sprintf(str,"%d", cv.CTX[idCanvas].getActivePolygonId());
            SetWindowText(cv.cp[ids[7]]->EditBox.EditBoxHandle, (LPSTR)str);
            InvalidateRect(cv.CNTLIST[ids[7]],0,1);

            *newDwg=0;
            free(str);
        }
        int activePolygon = cv.CTX[idCanvas].getActivePolygonId();
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(cv.CNTLIST[idCanvas], &p);
        p.x -= cv.CTX[idCanvas].getDwgSurfPos().x;
        p.y -= cv.CTX[idCanvas].getDwgSurfPos().y;
        if(cv.CTX[idCanvas].getPolygonSize(activePolygon)==0)
        {
            //cv.CTX[idCanvas].setgdiLinePoint(activeLine, 0, p);
            cv.CTX[idCanvas].newPolygonPoint(activePolygon,p);
            cv.CTX[idCanvas].newPolygonPoint(activePolygon,p);
            cv.CTX[idCanvas].newPolygonPoint(activePolygon,p);
        }
        else
        {
            cv.CTX[idCanvas].setPolygonPoint(activePolygon, cv.CTX[idCanvas].getPolygonSize(activePolygon)-2, p);
            cv.CTX[idCanvas].insertPolygonPoint(activePolygon, cv.CTX[idCanvas].getPolygonSize(activePolygon)-2,p);
        }
    }
    else
    {
        POINT p = *(POINT*)Args[11];
        int type = 0;
        unsigned idd = cv.CTX[idCanvas].getDwgId(p.x, p.y, type);
std::cout<<" idd = "<<idd<<"\n";
        // redessiner juste l'objet en cours
        if(type == CS_DWGTYPE_POLYGON ||
        (cv.CTX[idCanvas].getActivePolygonId() != idd && idd < cv.CTX[idCanvas].getPolygonsNum()))
        {
            rbp->updateActiveItem(idd);
            rbp->autoRepos();
            drawCurrentPolygon(Args);
        //cv.CTX[idCanvas].setActivePolygonId(idd); // deja present dans drawCurrentPolygon()
        };

        cv.CTX[idCanvas].setActiveDwgObject(type); //permet d'effacer le rectangle de selection en invalidant le type de dessin

        /*if(cv.CTX[idCanvas].arePolygonVerticesDrawn())
        {
            //redessiner entierement
            cv.CTX[idCanvas].updatePolygonsDwg();
            cv.CTX[idCanvas].redrawBackground();
            //if(type == CS_DWGTYPE_POLYGON)
                cv.CTX[idCanvas].showSelectedPolygon();
        }*/
    }
}


void pointCorrection(POINT*&pts, int size);
void rltDraw_Canv_rightbtndown(csARGS Args)
{
    int idCanvas = *(int*)Args[0];
    int*ids=(int*)Args[1];
    csRADIOBUTTON* rb=(csRADIOBUTTON*)Args[4];
    csRADIOBUTTON* rbp=(csRADIOBUTTON*)Args[9];
    int*unlock=(int*)Args[5];
    bool *newDwg = (bool*)Args[8];

    if(cv.cp[ids[8]]->LockedMode.Locked && cv.CTX[idCanvas].getgdiLineNum())
    {
        int activeLine = *(int*)Args[2];

        if(*unlock)
        {
            cv.cp[ids[8]]->LockedMode.Locked=0;
            rb->setCntState(1);
            rb->refresh();
            cv.cp[idCanvas]->Cursor = LoadCursor(0,IDC_ARROW);

            if(cv.CTX[idCanvas].getgdiLineSize(activeLine)>0)
            {
                cv.CTX[idCanvas].deletegdiLinePoint(activeLine, cv.CTX[idCanvas].getgdiLineSize(activeLine)-1);
            }
            else if(cv.CTX[idCanvas].getgdiLineNum()>0)
            {
                cv.CTX[idCanvas].deletegdiLine(activeLine);
            }
        }
        else
        {
            int FreeHand = *(int*)Args[3];
            if(FreeHand)
            {
                csLIST<POINT> ptl = cv.CTX[idCanvas].getgdiLine(activeLine);
                POINT *ptss = ptl.getTable();
                pointCorrection(ptss,ptl.size());
            }

            rltDraw_newLineBtn(Args);
        }
        InvalidateRect(cv.CNTLIST[idCanvas],0,1);

        *newDwg = 1;
    }
    else if(cv.cp[ids[14]]->LockedMode.Locked && cv.CTX[idCanvas].getPolygonsNum())
    {
        int activePolygon = cv.CTX[idCanvas].getActivePolygonId();

        if(*unlock)
        {
            cv.cp[ids[14]]->LockedMode.Locked=0;
            rbp->setCntState(1);
            rbp->refresh();
            cv.cp[idCanvas]->Cursor = LoadCursor(0,IDC_ARROW);

            if(cv.CTX[idCanvas].getPolygonSize(activePolygon)>1)
            {
                cv.CTX[idCanvas].deletePolygonPoint(activePolygon, cv.CTX[idCanvas].getPolygonSize(activePolygon)-2);
            }
            else if(cv.CTX[idCanvas].getPolygonsNum()>0)
            {
                cv.CTX[idCanvas].deletePolygon(activePolygon);
            }
        }
        else
        {
            int FreeHand = *(int*)Args[3];
            if(FreeHand)
            {
                csLIST<POINT> ptl = cv.CTX[idCanvas].getPolygon(activePolygon);
                POINT *ptss = ptl.getTable();
                pointCorrection(ptss,ptl.size());
            }

            rltDraw_newPolygonBtn(Args);
        }
        //cv.CTX[idCanvas].validateActiveDwg();
        InvalidateRect(cv.CNTLIST[idCanvas],0,1);

        *newDwg = 1;
    }
}



void changeDwgColor(csARGS Args);
void rltDraw_Canv_leftbtnup(csARGS Args)
{
    int idCanvas = *(int*)Args[0];std::cout<<"id paint " <<idCanvas<<"\n";
    bool *lbtnup = (bool*)Args[10];
    csBUTTONGRID *bgrd = (csBUTTONGRID*)Args[13];
    csSURFACE* srf = &cv.CTX[idCanvas];
    //il faut eviter que lbtnup ne s'execute s'il n'a pas plus d'un point sur le polygone
    if(*lbtnup)
    {
        *lbtnup = 0;
        srf->drawActiveAboveAll(0);//evite que le dessin en cours ..
        //.. ne se place au-dessus de tous les autres
        if(srf->getActiveDwgObject()==CS_DWGTYPE_POLYGON)
        {
            int activePlg = srf->getActivePolygonId();
            //if(srf->getPolygonSize(activePlg)>2)
            {
                csLIST<POINT> plg = srf->getPolygon(activePlg);
                csDWG_TRANSFORM_PARAMS* dtp = srf->getPolygonDwgTransformParams(activePlg);
                for(int i=0; i<plg.size(); i++)
                {
                    plg[i] = {plg[i].x*dtp->cfx+dtp->x, plg[i].y*dtp->cfy+dtp->y};
                }
                *dtp = {0,0,1,1};
                srf->updatePolygonsDwg();
                srf->redrawBackground();
                srf->showSelectedPolygon();
            }
        }
        InvalidateRect(cv.CNTLIST[idCanvas],0,1);
    }

    else if(srf->arePolygonVerticesDrawn() && srf->getActivePolygonId() != srf->lastPolygonId)
    {
        srf->updatePolygonsDwg();
        srf->redrawBackground();
        //srf->showSelectedPolygon();
        InvalidateRect(cv.CNTLIST[idCanvas],0,1);
        srf->lastPolygonId = srf->getActivePolygonId();
    }
    else if(*(bgrd->getItemState(0)))
        changeDwgColor(Args);
}

void rltDraw_Canv_mousemove(csARGS Args)
{
    int idCanvas = *(int*)Args[0];
    int*ids=(int*)Args[1];
    bool *newDwg = (bool*)Args[8];

    POINT p;
    GetCursorPos(&p);
    ScreenToClient(cv.CNTLIST[idCanvas], &p);

    POINT pt = cv.CTX[idCanvas].getDwgSurfPos();
    p.x -= pt.x;
    p.y -= pt.y;

    *(POINT*)Args[11] = p;

    if(cv.cp[ids[8]]->LockedMode.Locked)
    {
        if(cv.CTX[idCanvas].getgdiLineNum() && !*newDwg)
        {
            int activeLine = *(int*)Args[2];
            int FreeHand = *(int*)Args[3];
            if(!FreeHand)
            {
                if(cv.CTX[idCanvas].getgdiLineSize(activeLine)>0)
                {
                    cv.CTX[idCanvas].setgdiLinePoint(activeLine, cv.CTX[idCanvas].getgdiLineSize(activeLine)-1, p);
                    InvalidateRect(cv.CNTLIST[idCanvas],0,1);
                }
            }
            else if(cv.CTX[idCanvas].getgdiLineSize(activeLine)>0)
            {
                int last = cv.CTX[idCanvas].getgdiLineSize(activeLine)-1;
                POINT pt = cv.CTX[idCanvas].getgdiLinePoint(activeLine, last-1);
                cv.CTX[idCanvas].setgdiLinePoint(activeLine, last, p);
                if((int)sqrt((p.x-pt.x)*(p.x-pt.x)+(p.y-pt.y)*(p.y-pt.y)) >= 10)
                {
                    cv.CTX[idCanvas].newgdiLinePoint(activeLine,{p.x,p.y});
                }
                InvalidateRect(cv.CNTLIST[idCanvas],0,1);
            }
        }
    }

    else if(cv.cp[ids[14]]->LockedMode.Locked)
    {
        if(cv.CTX[idCanvas].getPolygonsNum() && !*newDwg)
        {
            int activePolygon = cv.CTX[idCanvas].getActivePolygonId();
            int FreeHand = *(int*)Args[3];
            if(!FreeHand)
            {
                if(cv.CTX[idCanvas].getPolygonSize(activePolygon)>1)
                {
                    cv.CTX[idCanvas].setPolygonPoint(activePolygon, cv.CTX[idCanvas].getPolygonSize(activePolygon)-2, p);
                    InvalidateRect(cv.CNTLIST[idCanvas],0,1);
                }
            }
            else if(cv.CTX[idCanvas].getPolygonSize(activePolygon)>1)
            {
                int last = cv.CTX[idCanvas].getPolygonSize(activePolygon)-2;
                POINT pt = cv.CTX[idCanvas].getPolygonPoint(activePolygon, last-1);
                cv.CTX[idCanvas].setPolygonPoint(activePolygon, last, p);
                if((int)sqrt((p.x-pt.x)*(p.x-pt.x)+(p.y-pt.y)*(p.y-pt.y)) >= 10)
                {
                    cv.CTX[idCanvas].insertPolygonPoint(activePolygon,last,{p.x,p.y});
                }
                InvalidateRect(cv.CNTLIST[idCanvas],0,1);
            }
        }
    }

    else
    {
        if(WPARAM(Args)==1) // bouton gauche appuye
        {
            //if(cv.CTX[idCanvas].getActiveDwgObject() == CS_DWGTYPE_POLYGON)
            {
                POINT pt = cv.TRACKING_POINT;
                ScreenToClient(HWND(Args), &pt);
                pt.x -= cv.CTX[idCanvas].getDwgSurfPos().x;
                pt.y -= cv.CTX[idCanvas].getDwgSurfPos().y;
                cv.CTX[idCanvas].setActiveDwgTransformParams({p.x-pt.x,p.y-pt.y,1,1});
                InvalidateRect(cv.CNTLIST[idCanvas],0,1);
                //drawCurrentPolygon(Args);
                cv.CTX[idCanvas].drawActiveAboveAll(1);
                bool*lbtnup = (bool*)Args[10];
                *lbtnup = 1;
            }
        }
    }

    //int idshowcoords = ids[21];
    /*sprintf(cv.cp[idshowcoords]->Title.Text, "x = %d, y = %d", int(p.x), int(p.y));
    InvalidateRect(cv.CNTLIST[idshowcoords],0,1);*/
    //SendMessage(cv.CNTLIST[idshowcoords], WM_TIMER, 0,0);
}

void showCoords_timer(csARGS Args)
{
    POINT p = *(POINT*)Args[0];
    POINT* psaved_old = (POINT*)Args[1];

    if(psaved_old->x != p.x || psaved_old->y != p.y)
    {
        int id = int(Args);
        sprintf(cv.cp[id]->Title.Text, "x = %d, y = %d", int(p.x), int(p.y));
        InvalidateRect(cv.CNTLIST[id],0,1);
        *psaved_old = p;
    }
}


void copyPaste(csARGS Args);
void viewColorPalette(csARGS Args);
void rltDraw_Canv_cancelLast(csARGS Args)
{
    int*ids=(int*)Args[1];
    static int delay = 1;
    int idCanvas = *(int*)Args[0];
    if(cv.cp[ids[8]]->LockedMode.Locked)
    {
        int activeLine = *(int*)Args[2];
        if(delay==2)
        {
            if(GetKeyState(VK_BACK))
            {
                if(cv.CTX[idCanvas].getgdiLineSize(activeLine) > 2)
                {
                    cv.CTX[idCanvas].deletegdiLinePoint(activeLine, cv.CTX[idCanvas].getgdiLineSize(activeLine)-2);
                    InvalidateRect(cv.CNTLIST[idCanvas],0,1);
                }
            }
            delay = 0;
        }
        delay++;
    }
    else if(cv.cp[ids[14]]->LockedMode.Locked)
    {
        if(GetAsyncKeyState(VK_BACK) && cv.CTX[idCanvas].getPolygonsNum())
        {
            int activePolygon = cv.CTX[idCanvas].getActivePolygonId();
            if(cv.CTX[idCanvas].getPolygonSize(activePolygon) > 4)
            {
                cv.CTX[idCanvas].deletePolygonPoint(activePolygon, cv.CTX[idCanvas].getPolygonSize(activePolygon)-3);
                InvalidateRect(cv.CNTLIST[idCanvas],0,1);
            }
        }
    }
    //drawCurrentLine(Args);
    copyPaste(Args);
    viewColorPalette(Args);
}

void viewColorPalette(csARGS Args)
{
    csBUTTONGRID *subMenus =  (csBUTTONGRID*)Args[15];
    csCOLORPALETTE* palette = (csCOLORPALETTE*)Args[12];
    static int VIEW = 3, COLORS_ID = 0;
    bool* state = subMenus[VIEW].getItemState(COLORS_ID);
    if(*(subMenus[VIEW].click_message))
    {
        /*int idi = subMenus[3].getActiveItem();
        if(strcmp(subMenus[3].getTitle(idi), "Colors") == 1)
        {
            csPARAMS(palette->getId())->Show = 1;
        }*/
        if(*state)
        {
            csPARAMS(palette->getId())->Show = 1;
        }
        else
        {
            csPARAMS(palette->getId())->Show = 0;
        }
        *(subMenus[VIEW].click_message) = 0;
    }
    if(csPARAMS(palette->getId())->Show == 0)
    {
        if(*state)
        {
            subMenus[VIEW].setItemState(COLORS_ID,0);
            InvalidateRect(csHWND(subMenus[VIEW].getId()),0,1);
        }
    }
}

void drawCurrentLine(csARGS Args)
{
    int idCanvas = *(int*)Args[0];
    int*ids=(int*)Args[1];
    //csRADIOBUTTON* rb=(csRADIOBUTTON*)Args[4];
    int*unlock=(int*)Args[5];
    int *lastActiveLine = (int*)Args[6];
    if(*unlock || cv.cp[ids[8]]->LockedMode.Locked==0)
    {//std::cout<<*(int*)Args[2]<<std::endl;
        int *actItem =  (int*)Args[2];
        int *lastListSize = (int*)Args[7]; //si un element est supprime
        int actualListSize = cv.CTX[idCanvas].getgdiLineNum();
        if(*lastActiveLine != *actItem)
        {

            *lastActiveLine = *actItem;
            POINT*t = cv.CTX[idCanvas].getgdiLine(*actItem).getTable();
            int n = cv.CTX[idCanvas].getgdiLine(*actItem).size();
            HDC dc = cv.CTX[idCanvas].redrawBackground();
            HPEN hp = CreatePen(PS_SOLID,cv.CTX[idCanvas].getgdiLineThickness(*actItem)+4,RGB(255,255,0));
            SelectPen(dc, hp);
            Polyline(dc,(const POINT*)t,n);
            DeletePen(hp);
            InvalidateRect((HWND)Args,0,1);
        }
        if(*lastListSize!=actualListSize)
        {

            *lastListSize = actualListSize;
            POINT*t = cv.CTX[idCanvas].getgdiLine(*actItem).getTable();
            int n = cv.CTX[idCanvas].getgdiLine(*actItem).size();
            HDC dc = cv.CTX[idCanvas].redrawBackground();

            HPEN hp = CreatePen(PS_SOLID,cv.CTX[idCanvas].getgdiLineThickness(*actItem)+4,RGB(255,255,0));
            SelectPen(dc, hp);
            Polyline(dc,(const POINT*)t,n);
            DeletePen(hp);
            InvalidateRect((HWND)Args,0,1);
        }
    }
}


void drawCurrentPolygon(csARGS Args)
{
    int idCanvas = *(int*)Args[0];
    int*ids=(int*)Args[1];
    csRADIOBUTTON* rbp=(csRADIOBUTTON*)Args[9];
    csSURFACE srf = cv.CTX[idCanvas];
    int id = *(rbp->getActiveItem());

    //if(srf.getActivePolygonId() != id)
    {
        cv.CTX[idCanvas].setActivePolygonId(id);
        cv.CTX[idCanvas].showSelectedPolygon();
        InvalidateRect(cv.CNTLIST[idCanvas], 0,1);
    }
}
void drawCurrentPolygon_keyup(csARGS Args)
{
    int idCanvas = *(int*)Args[0];
    int*ids=(int*)Args[1];
    csRADIOBUTTON* rbp=(csRADIOBUTTON*)Args[9];
    csSURFACE srf = cv.CTX[idCanvas];
    int id = *(rbp->getActiveItem());

    WPARAM wp = (WPARAM)Args;
    if(srf.getActivePolygonId() != id && (wp == VK_UP || wp == VK_DOWN))
    {
        cv.CTX[idCanvas].setActivePolygonId(id);
        cv.CTX[idCanvas].showSelectedPolygon();
        InvalidateRect(cv.CNTLIST[idCanvas], 0,1);
    }
}

void copyPaste(csARGS Args)
{
    int idCanvas = *(int*)Args[0];
    csRADIOBUTTON* rb=(csRADIOBUTTON*)Args[4];
    csRADIOBUTTON* rbp=(csRADIOBUTTON*)Args[9];
    csRADIOBUTTON* rblay = (csRADIOBUTTON*)Args[14];

    int keysState = *(rblay->getCopyPasteKeyDownState());
    bool* blay = rblay->getCopyPasteState();
    if(*blay)
    {
        int a = *(rblay->getActiveItem());
        if(a >= 0)
        {
            int b = *(rblay->getMouseOverItem());
            if(b >= 0 && b < rblay->getSize())
            {
                if(keysState == VK_LSHIFT)
                    rblay->duplicate(a, b);
                else if(keysState == VK_LBUTTON)
                    rblay->moveItem(a, b);
                rblay->setMouseOverItem(*(rblay->getActiveItem()));
                rblay->create();
            }
        }
        *blay = 0;
    }

    bool* bplg = rbp->getCopyPasteState();
    keysState = *(rbp->getCopyPasteKeyDownState());
    if(*bplg)
    {
        int a = *(rbp->getActiveItem());
        if(a >= 0 && a < cv.CTX[idCanvas].getPolygonsNum())
        {
            int b = *(rbp->getMouseOverItem());
            if(b >= 0 && b < cv.CTX[idCanvas].getPolygonsNum())
            {
                if(keysState == VK_LSHIFT)
                {
                    rbp->duplicate(a, b);
                    cv.CTX[idCanvas].duplicate(a, b);
                }
                else if(keysState == VK_LBUTTON)
                {
                    rbp->moveItem(a, b);
                    cv.CTX[idCanvas].setPolygonRange(a, b);
                }

                rbp->setMouseOverItem(*(rbp->getActiveItem()));
                rbp->create();

                cv.CTX[idCanvas].updatePolygonsDwg();
                cv.CTX[idCanvas].redrawBackground();
                //InvalidateRect(HWND(Args),0,1);
                drawCurrentPolygon(Args);
            }
        }
        *bplg = 0;
    }

    bool* bline = rb->getCopyPasteState();
    if(*bline)
    {
        int a = *(rb->getActiveItem());
        if(a >= 0 && a < cv.CTX[idCanvas].getgdiLineNum())
        {
            int b = *(rb->getMouseOverItem());
            if(b >= 0 && b < cv.CTX[idCanvas].getgdiLineNum())
            {
                rb->moveItem(a, b);
                rb->setMouseOverItem(*(rb->getActiveItem()));
                rb->create();

                /*cv.CTX[idCanvas].setPolygonRange(a, b);
                cv.CTX[idCanvas].updatePolygonsDwg();
                cv.CTX[idCanvas].redrawBackground();
                //InvalidateRect(HWND(Args),0,1);
                drawCurrentPolygon(Args);*/
            }
        }
        *bline = 0;
    }
}

void linesDesign(int id, int n, COLORREF color, int thickness, POINT init, POINT center)
{
    RECT r = cv.CNTRECT[id];

    int dx = CS_CYSCREEN/n, dy = CS_CYSCREEN/n, g = CS_CYSCREEN, h = CS_CYSCREEN, k, l;
    POINT p[2];
    cv.CTX[id].redrawBackground();
    HDC dc = cv.CTX[id].getDC();
    HPEN hp = CreatePen(0, thickness, color);
    SelectPen(dc, hp);
    for(int i=0; i<n; i++)
    {
        k = i*dx+init.x;
        p[0] = {k, center.y};
        p[1] = {g - k, h+center.y};

        csLIST<POINT> lst;
        lst.insertEnd(p[0]);
        lst.insertEnd(p[1]);
        Polyline(dc, (const POINT*)p, 2);

        if(i%2==0)
        {
            l = i*dy+init.y;
            p[0] = {center.x, l};
            p[1] = {g+center.x, h-l};

            csLIST<POINT> lst;
            lst.insertEnd(p[0]);
            lst.insertEnd(p[1]);
            Polyline(dc, (const POINT*)p, 2);
        }
    }
    InvalidateRect(cv.CNTLIST[id],0,1);
    DeletePen(hp);
}



/*int testSHP()
{
    // Création d'un nouvel objet SHPHandle (shapefile)
    SHPHandle hSHP = SHPCreate("output", SHPT_POLYGON);
    if (hSHP == NULL) {
        std::cerr << "Impossible de créer le fichier shapefile." << std::endl;
        return 1;
    }

    // Définition des points du polygone
    double x[5] = {0, 0, 10, 10, 0};
    double y[5] = {0, 10, 10, 0, 0};

    // Création de l'objet SHPObject (objet géométrique)
    SHPObject *psObject = SHPCreateObject(SHPT_POLYGON, -1, 0, NULL, NULL, 5, x, y, NULL, NULL);
    if (psObject == NULL) {
        std::cerr << "Impossible de créer l'objet géométrique." << std::endl;
        SHPClose(hSHP);
        return 1;
    }

    // Écriture de l'objet géométrique dans le fichier shapefile
    int nShapeId = SHPWriteObject(hSHP, -1, psObject);
    if (nShapeId == -1) {
        std::cerr << "Erreur lors de l'écriture de l'objet géométrique." << std::endl;
        SHPClose(hSHP);
        SHPDestroyObject(psObject);
        return 1;
    }

    // Fermeture du fichier shapefile
    SHPClose(hSHP);

    std::cout << "Fichier shapefile sauvegardé avec succès." << std::endl;

    return 0;
}*/

void pointCorrection(POINT*&pts, int size)
{
	double*xin = (double*)malloc(size*sizeof(double));
	double*yin = (double*)malloc(size*sizeof(double));
    for(int i =0; i<size; i++)
    {
        xin[i] = pts[i].x;
        yin[i] = pts[i].y;
    }

    for(int j =0; j<1; j++)
    {
        for(int i = 1; i<size-1; i++)
        {
            xin[i] = (xin[i+1]+xin[i])/2;
            yin[i] = (yin[i+1]+yin[i])/2;
        }
        xin[1] = (xin[0]+xin[1])/2;
        yin[1] = (yin[0]+yin[1])/2;
    }

    for(int i = 0; i<size; i++)
    {
        pts[i].x = xin[i];
        pts[i].y = yin[i];
        //cout<<"{"<<pts[i].x<<","<<pts[i].y<<"}";
    }
    free(xin);
    free(yin);
}

/*void pointCorrection(POINT*&pts, int size)
{
	size_t n = size, wordLen=10, n_out=0, n_coefs_cells=0, cell_length_interp=0, n_interp = 0, dx = 1;
	size_t min = 1, max = 10, exponent = 0;
	double*xin = (double*)malloc(size*sizeof(double)), *xo=0;
	double*yin = (double*)malloc(size*sizeof(double)), *yo=0;
    for(int i =0; i<size; i++)
    {
        xin[i] = pts[i].x;
        yin[i] = pts[i].y;
    }
	//printArray1D(y, n, "y :", wordLen=20);
	int cell_length, n_overlap, polynom_degree, n_cell_interest=0;

	double** ycoefs = descretePolynomialInterpolationCoefs1D(yin, n, cell_length=5,
													n_overlap=2, polynom_degree=5,
													yo, n_out, n_coefs_cells);


	//printArray1D(y_out, n_out, "y_out :", wordLen=8);
	//printArray2D(coefs, polynom_degree+1, n_coefs_cells, "coefs :", wordLen);
	correctInterpolationSize(n, cell_length, &cell_length_interp, &n_interp, dx);
    //cout<<"{"<<pts[0].x<<","<<pts[0].y<<"} ";
	//std::cout<<n_coefs_cells;
	double*ycorr = descretePolynomialInterpolation1D(ycoefs, n_coefs_cells, polynom_degree,
											cell_length, n_overlap, &cell_length_interp, &n_interp);

	double** xcoefs = descretePolynomialInterpolationCoefs1D(xin, n, cell_length,
													n_overlap, polynom_degree,
													xo, n_out, n_coefs_cells);
	double*xcorr = descretePolynomialInterpolation1D(xcoefs, n_coefs_cells, polynom_degree,
											cell_length, n_overlap, &cell_length_interp, &n_interp);

	//printArray1D(ycorr, n_interp, "yinterp :", wordLen=10);
    for(int i = 0; i<size; i++)
    {
        pts[i].x = xcorr[i];
        pts[i].y = ycorr[i];
        //cout<<"{"<<pts[i].x<<","<<pts[i].y<<"}";
    }
    free(xcorr);
    free(ycorr);
    free(xo);
    free(yo);
    for(int i = 0; i<n_coefs_cells; i++)
    {
        free(xcoefs[i]);
        free(ycoefs[i]);
    }
}*/
