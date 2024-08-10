#include "appMenu.h"

extern csCNTR_VARS cv;

csPAGES* menu(int idp)
{
    int n = 0;
    csPAGES pgs(idp, idp, {630, 3, 390, 52});
    pgs.initIndexer({5,29,630,26},{5,20,150,1},13,1);
    pgs.getIndexer()->setFont("Calibri", {15,0});
    pgs.getIndexer()->setTextMarging(2,0);
    pgs.getIndexer()->setMarging(0,0);


    cv.CTX[pgs.getIndexerBGroup()->getID()].setCntBorder({30,30,30},1);
    cv.CTX[pgs.getIndexerBGroup()->getIDC2()].setCntBorder({30,30,30},1);
    cv.CTX[pgs.getIndexerBGroup()->getIDC3()].setCntBorder({30,30,30},1);

    //csSetBackgroundColor(pgs.getIndexerBGroup()->getIDC2(),{30,30,30});

    SIZE imsz = {13,13};
    POINT impos = {-1,-1};
    POINT impos0 = {0,2};
    int maxItemNum = 20;
    char*path = "img\\app\\template_icon.bmp";
    csBGRID_PARAMS bgp = {2,2,700/2, 50/2};

    pgs.newPage("My CV", bgp, maxItemNum);
        pgs.getPage(n)->newBItem(impos0,imsz,"Curriculum V.","img\\app\\File\\newFile.bmp","img\\app\\File\\newFile.bmp","img\\app\\File\\newFile.bmp");
    n++; 
    pgs.newPage("File", bgp, maxItemNum);
        //pgs.getPage(n)->setMarging(2,2);
        pgs.getPage(n)->newBItem(impos0,imsz,"Open", "img\\app\\File\\open.bmp", "img\\app\\File\\open.bmp", "img\\app\\File\\open.bmp", "img\\app\\File\\open.bmp");
        pgs.getPage(n)->newBItem(impos,imsz,"New file", "img\\app\\File\\newFile.bmp", 0,0,0);
        pgs.getPage(n)->newBItem(impos,imsz,"Save file", "img\\app\\File\\saveFile.bmp", 0,0,0);
        pgs.getPage(n)->newBItem(impos,imsz,"New fold.", "img\\app\\File\\newFolder2.bmp", 0,0,0);
        pgs.getPage(n)->newBItem(impos,imsz,"Rem. fold.", "img\\app\\File\\delFolder.bmp", 0,0,0);
        pgs.getPage(n)->newBItem(impos,imsz,"New file", "img\\app\\File\\newFile.bmp", 0,0,0);
        pgs.getPage(n)->newBItem(impos,imsz,"Save file", "img\\app\\File\\saveFile.bmp", 0,0,0);
        pgs.getPage(n)->newBItem(impos,imsz,"New fold.", "img\\app\\File\\newFolder2.bmp", 0,0,0);
        pgs.getPage(n)->newBItem(impos,imsz,"Rem. fold.", "img\\app\\File\\delFolder.bmp", 0,0,0);
        pgs.getPage(n)->newBItem(impos,imsz,"New file", "img\\app\\File\\newFile.bmp", 0,0,0);
        pgs.getPage(n)->newBItem(impos,imsz,"Save file", "img\\app\\File\\saveFile.bmp", 0,0,0);
        pgs.getPage(n)->newBItem(impos,imsz,"New fold.", "img\\app\\File\\newFolder2.bmp", 0,0,0);
        pgs.getPage(n)->newBItem(impos,imsz,"Rem. fold.", "img\\app\\File\\delFolder.bmp", 0,0,0);
    n++;
    pgs.newPage("Edit", bgp, maxItemNum);
        pgs.getPage(n)->makeNTemplate("icon 1 ...", "img\\app\\template_icon.bmp", imsz);
    n++;
    pgs.newPage("View",{3,3,700/3,55/3},maxItemNum);
        pgs.getPage(n)->setTextPosition(CS_RDBTN_TEXT_AFTER);
        pgs.getPage(n)->setTextMarging(1,1);
        pgs.getPage(n)->setMarging(0,0);
        pgs.getPage(n)->showTitle(1);
        int height = 2;
        pgs.getPage(n)->makeNTemplate("button ","img\\app\\work.bmp",{8,8}, height, {30,8});
        //bgWork.setXRect_model01(30, height);
        pgs.getPage(n)->create();
        pgs.getPage(n)->setActiveItem(1);
        pgs.getPage(n)->setItemType(0, CS_BGRD_BI_SELECTION);
        pgs.getPage(n)->setItemState(0,1);
        pgs.getPage(n)->setItemTitle(0,csSTR("Colors"));
        pgs.getPage(n)->setItemIcon(0,"img\\app\\colors1.bmp");
        pgs.getPage(n)->updateItem(0);
    n++;
    pgs.newPage("Layers",{3,3,700/3,55/3},maxItemNum);
        pgs.getPage(n)->setTextPosition(CS_RDBTN_TEXT_UNDER);
        pgs.getPage(n)->setTextMarging(1,1);
        pgs.getPage(n)->setMarging(0,0);
        pgs.getPage(n)->showTitle(1);
        height = 1;
        pgs.getPage(n)->makeNTemplate("Lr button ","img\\app\\work.bmp",{13,13}, height, {30,16});
        //bgWork.setXRect_model01(30, height);
        pgs.getPage(n)->create();
        pgs.getPage(n)->setActiveItem(0);
    n++;
    
    pgs.newPage("Point",bgp,maxItemNum);
        pgs.getPage(n)->newBItem(impos0,imsz,"P1 Button",path,path,path);
    n++;
    pgs.newPage("Line",bgp,maxItemNum);
        pgs.getPage(n)->newBItem(impos0,imsz,"L1 Button",path,path,path);
    n++;
    pgs.newPage("Polygon",bgp,maxItemNum);
        pgs.getPage(n)->newBItem(impos0,imsz,"Plg1 Button",path,path,path);
    n++;
    pgs.newPage("Image",bgp,maxItemNum);
        pgs.getPage(n)->newBItem(impos0,imsz,"Img1 Button",path,path,path);
    n++;
    pgs.newPage("Text",bgp,maxItemNum);
        pgs.getPage(n)->newBItem(impos0,imsz,"Txt1 Button",path,path,path);
    n++;
    pgs.newPage("Simulation",bgp,maxItemNum);
        pgs.getPage(n)->newBItem(impos0,imsz,"Sim1 Button",path,path,path);
    n++;
    pgs.newPage("Module",bgp,maxItemNum);
        pgs.getPage(n)->newBItem(impos0,imsz,"Mod1 Button",path,path,path);
    n++;
    pgs.newPage("Document",bgp,maxItemNum);
        pgs.getPage(n)->newBItem(impos0,imsz,"Doc1 Button",path,path,path);
    n++;
    pgs.newPage("About",bgp,maxItemNum);
        pgs.getPage(n)->newBItem(impos0,imsz,"Abt1 Button",path,path,path);

    pgs.create();
    pgs.getPagesBGroup()->setC3Size(bgp.dx*bgp.nx, 1);
    pgs.getPagesBGroup()->setMarging(1);
    pgs.getIndexerBGroup()->setC3Size(-1, 1);
    pgs.getIndexerBGroup()->setMarging(1);

    
    cv.CTX[pgs.getPagesBGroup()->getID()].setCntBorder({30,30,30},1);
    cv.CTX[pgs.getPagesBGroup()->getIDC2()].setCntBorder({30,30,30},1);
    return csf_alloc2<csPAGES>(1,pgs);
}