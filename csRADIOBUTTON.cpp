#include "csRADIOBUTTON.h"
//#include <fftw3.h>
extern csCNTR_VARS cv;
extern csCNTR_PARAMS cscp;

void autoReposition(csARGS Args);
void _mouseMove(csARGS Args);
void mouseClick(csARGS Args);
void mouseLeave(csARGS Args);
void vkeydownSrcoll(csARGS Args);
void vkeydownSrcoll_timer(csARGS Args);
void vkeyupScroll(csARGS Args);
void vkeydownSelect(csARGS Args);
void startCutPaste(csARGS Args);
void endCutPaste(csARGS Args);
void makeCutPaste(csARGS Args);

csRADIOBUTTON::csRADIOBUTTON(int idp, int gridStyle, int _gridWidth)
{
    init(idp, gridStyle, _gridWidth);
}

void csRADIOBUTTON::init(int idp, int gridStyle, int _gridWidth)
{
    
    title.init(1);
    pos.init(1);
    posImg.init(1);
    posTitle.init(1);
    color0.init(1);
    color1.init(1);
    color2.init(1);
    color3.init(1);
    color4.init(1);
    bkgcol0.init(1);
    bkgcol1.init(1);
    bkgcol2.init(1);
    bkgcol3.init(1);
    bkgcol4.init(1);
    font.init(1);
    dcs0.init(1);
    dcs1.init(1);
    dcs2.init(1);
    dcs3.init(1);
    dcs4.init(1);
    dfltTitle = 0;
    pdfltSz = 0;
    pmarging = 0;
    poffset = 0;
    pimgSize = 0;
    phdc = 0;
    pgridWidth = 0;
    lastMouseOverid = 0;
    lastMouseClickid = 0;
    n = 0;
    cntActivate = 0;
    vkCtrlCount = 0;
    vkCtrlCountControl = 0;
    vkCtrlPoint = 0;
    vkCtrlGdcPos = 0;
    smoothRepos = 0;
    smoothReposCount = 0;
    cutPasteViewer = 0;
    cutPasteStart = 0;
    cutPasteDone = 0;
    cutPasteDone0 = 0;
    copyPasteKeyDownState = 0;
    click_message = 0;

    fontSize = {15,0};
    dfltFont = CreateFont(csGetAdjustedFontSizeX(fontSize.cx),csGetAdjustedFontSizeY(fontSize.cy), 
    0, 0, 0,0,0, 0,0,0,0,0,0, (LPCSTR)"Calibri");
    dfltColor1 = RGB(250,250,250);
    dfltColor2 = RGB(255,255,255);
    //dfltColor3 = RGB(255,255,100);
    dfltColor3 = RGB(10,10,10);
    csRGBA col = cv.cp[idp]->BackgroundColor;
    dfltColor4 = RGB(col.r+70,col.g+70,col.b+70);

    dfltBkgCol1 = RGB(col.r,col.g,col.b);
    defcol = cv.cp[idp]->BackgroundColor;
    dfltBkgCol2 = RGB(col.r+20,col.g+20,col.b+20);
    //dfltBkgCol3 = RGB(col.r-20,col.g-20,col.b-20);
    dfltBkgCol3 = RGB(200,200,200);
    dfltBkgCol4 = RGB(col.r,col.g,col.b);
    dfltSz = {100,20};
    marging = {1,1};
    offset = {5,5};
    imgSize = {15,15};
    imgdc1 = csGetImgBits("img\\combo_12.bmp", {15,15});
    imgdc2 = csGetImgBits("img\\combo_1.bmp", {15,15});
    imgdc3 = csGetImgBits("img\\combo_1.bmp", {15,15});
    imgdc4 = csGetImgBits("img\\combo_1.bmp", {15,15});
    gridStyle = gridStyle;
    textOrientation = CS_RDBTN_TEXT_H;
    TextPos = CS_RDBTN_TEXT_AFTER;
    gridWidth = _gridWidth;
    parent = idp;

    lastMouseOverid = (int*)malloc(sizeof(int));
    lastMouseClickid = (int*)malloc(sizeof(int));
    *lastMouseOverid = 0;
    *lastMouseClickid = 0;

    dfltTitle = (char*)malloc(100);
    sprintf(dfltTitle,"Item");

    pimgSize = (SIZE*)malloc(sizeof(SIZE)); *pimgSize = imgSize;
    n = (int*)malloc(sizeof(int));
    activeChoosed = 0;
    cntActivate = (bool*)malloc(sizeof(bool));
    *cntActivate = true;
    iter = 0;
    animated = 0;

    hdc = GetDC(cv.CNTLIST[parent]);
    phdc = (HDC*)malloc(sizeof(HDC));
    *phdc = hdc;

    smoothRepos = csf_alloc2<int>(1,1);
    smoothReposCount = csf_alloc2<int>(1,0);

    vkCtrlCount = (int*)malloc(sizeof(int)); *vkCtrlCount = 0;
    vkCtrlCountControl = (int*)malloc(sizeof(int)); *vkCtrlCountControl = 0;
    vkCtrlPoint = (POINT*)malloc(sizeof(POINT)); *vkCtrlPoint = {0,0};
    vkCtrlGdcPos = (POINT*)malloc(sizeof(POINT)); *vkCtrlGdcPos = {0,0};
    pmarging = (SIZE*)malloc(sizeof(SIZE)); *pmarging = {0,0};
    pdfltSz = (SIZE*)malloc(sizeof(SIZE)); *pdfltSz = {0,0};
    poffset = (SIZE*)malloc(sizeof(SIZE)); *poffset = {0,0};
    pgridWidth = (int*)malloc(sizeof(int)); *pgridWidth = _gridWidth;
    pf = (void*(*)())malloc(sizeof(void (*)()));
    click_message = (bool*)malloc(sizeof(bool)); *click_message = 0;

    zebColor = {255,255,255};
    zebFact = 0.0;

    cutPasteDone0 = 0;
    cutPasteDone = 0;
    cutPasteStart = 0;
    cutPasteViewer = 0;

    rbItem.title=0;
}

csRADIOBUTTON::~csRADIOBUTTON()
{
    //dtor
}

void csRADIOBUTTON::autoRepos()
{
    *smoothReposCount = 0;
}

bool* csRADIOBUTTON::getCntState()
{
    return cntActivate;
}
void csRADIOBUTTON::setCntState(bool activate)
{
    *cntActivate = activate;
}

void csRADIOBUTTON::setImage(char*path1, char*path2,char*path3,char*path4,SIZE size)
{
    csFreeDC(imgdc1);
    csFreeDC(imgdc2);
    csFreeDC(imgdc3);
    csFreeDC(imgdc4);
    imgdc1 = csGetImgBits(path1, {size.cx,size.cy});
    imgdc2 = csGetImgBits(path2, {size.cx,size.cy});
    imgdc3 = csGetImgBits(path3, {size.cx,size.cy});
    imgdc4 = csGetImgBits(path4, {size.cx,size.cy});
    imgSize = size;
}
void csRADIOBUTTON::setImageSize(SIZE size)
{
    csFreeDC(imgdc1);
    csFreeDC(imgdc2);
    csFreeDC(imgdc3);
    csFreeDC(imgdc4);
    imgdc1 = csGetImgBits("img\\combo_12.bmp", {size.cx,size.cy});
    imgdc2 = csGetImgBits("img\\combo_1.bmp", {size.cx,size.cy});
    imgdc3 = csGetImgBits("img\\combo_1.bmp", {size.cx,size.cy});
    imgdc4 = csGetImgBits("img\\combo_1.bmp", {size.cx,size.cy});
    imgSize = size;
}

void csRADIOBUTTON::setParent(int idp)
{
    parent = idp;

}
void csRADIOBUTTON::setGridWidth(int grdWidth)
{
    gridWidth = grdWidth;
}
void csRADIOBUTTON::setRect(int id, RECT r)
{
    pos[id] = r;
}
void csRADIOBUTTON::setTitle(int id, char* _title)
{
    title[id] = _title;
}
void csRADIOBUTTON::setTitles(char* ids[], char* _title[], int n)
{
    for(int i=0; i<n; i++)
    {
        title[(int)strtod(ids[i],0)] = (char*)_title[i];
    }
}
void csRADIOBUTTON::setFont(int id, char* fnt, SIZE size)
{
    if(textOrientation == CS_RDBTN_TEXT_H)
        font[id] = CreateFont(csGetAdjustedFontSizeX(size.cx),csGetAdjustedFontSizeY(size.cy), 0, 0, FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                          DEFAULT_PITCH|FF_SWISS, (LPCSTR)fnt);
    else if(textOrientation == CS_RDBTN_TEXT_V1)
        font[id] = CreateFont(csGetAdjustedFontSizeX(size.cx),csGetAdjustedFontSizeY(size.cy), 900, 0, FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                          DEFAULT_PITCH|FF_SWISS, (LPCSTR)fnt);
    else if(textOrientation == CS_RDBTN_TEXT_V2)
        font[id] = CreateFont(csGetAdjustedFontSizeX(size.cx),csGetAdjustedFontSizeY(size.cy), -900, 0, FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                          DEFAULT_PITCH|FF_SWISS, (LPCSTR)fnt);
    fontSize = size;
}

void csRADIOBUTTON::setDefaultFont(char* fnt, SIZE size)
{
    DeleteFont(dfltFont);
    if(textOrientation == CS_RDBTN_TEXT_H)
        dfltFont = CreateFont(csGetAdjustedFontSizeX(size.cx),csGetAdjustedFontSizeY(size.cy), 0, 0, FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                          DEFAULT_PITCH|FF_SWISS, (LPCSTR)fnt);
    else if(textOrientation == CS_RDBTN_TEXT_V1)
        dfltFont = CreateFont(csGetAdjustedFontSizeX(size.cx),csGetAdjustedFontSizeY(size.cy), 900, 0, FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                          DEFAULT_PITCH|FF_SWISS, (LPCSTR)fnt);
    else if(textOrientation == CS_RDBTN_TEXT_V2)
        dfltFont = CreateFont(csGetAdjustedFontSizeX(size.cx),csGetAdjustedFontSizeY(size.cy), -900, 0, FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                          DEFAULT_PITCH|FF_SWISS, (LPCSTR)fnt);
    fontSize = size;
}

void csRADIOBUTTON::zebraStyle(csRGBA zcol, float zFactor)
{
    zebFact = zFactor;
    zebColor = zcol;
}

void csRADIOBUTTON::copyPasteStyle()
{
    cutPasteViewer = csf_alloc2<int>(1, staticCnt2(cscp,0,"",{0},{0},0));
    csDetachCnt(*cutPasteViewer);
    cutPasteDone0 = csf_alloc2<bool>(1,0);
    cutPasteDone = csf_alloc2<bool>(1,0);
    cutPasteStart = csf_alloc2<bool>(1,0);
    copyPasteKeyDownState = csf_alloc2<int>(1,0);
}

void csRADIOBUTTON::setColors(int id, COLORREF color, COLORREF highlightColor, COLORREF selectionColor)
{
    color1[id] = color;
    color2[id] = highlightColor;
    color3[id] = selectionColor;
}

void csRADIOBUTTON::setDefaultColors(COLORREF color, COLORREF highlightColor, COLORREF selectionColor)
{
    dfltColor1 = color;
    dfltColor2 = highlightColor;
    dfltColor3 = selectionColor;
    defcol = {color&0xff, color>>8&0xff, color>>16&0xff};
}
void csRADIOBUTTON::setDefaultSize(SIZE size)
{
    dfltSz = size;
    if(size.cx>=size.cy)
        textOrientation = CS_RDBTN_TEXT_H;
    else
        textOrientation = CS_RDBTN_TEXT_V1;
}

char* csRADIOBUTTON::defaultItemTitle()
{
    char*str = (char*)malloc(100);
    sprintf(str,"%s %d", dfltTitle, iter++);
    return str;
}

void csRADIOBUTTON::setOrientation(int orient)
{
    textOrientation = orient;
}
void csRADIOBUTTON::setMarging(SIZE _marging)
{
    marging = _marging;
}
void csRADIOBUTTON::setOffset(SIZE _offset)
{
    offset = _offset;
}

int* csRADIOBUTTON::getActiveItem()
{
    return lastMouseClickid;
}
int* csRADIOBUTTON::getMouseOverItem()
{
    return lastMouseOverid;
}

int csRADIOBUTTON::getId()
{
    return parent;
}

int csRADIOBUTTON::getSize()
{
    return *n;
}

void csRADIOBUTTON::setActiveItem(int id)
{
    if(id < title.size())
    {
        *lastMouseClickid = id;
        //*lastMouseOverid = id; // attention annule le 28/06/2024
        color0[id]=dfltColor3;
        bkgcol0[id]=dfltBkgCol3;
        dcs0[id]=imgdc3.dc;
        activeChoosed = 1;

        /*args.setArg(18, (void*)lastMouseOverid);
        args.setArg(19, (void*)lastMouseClickid);
        args.setHwnd(cv.CNTLIST[parent]);
        int *par = csf_alloc2<int>(1,parent);
        args.setId((void*)par);
        mouseClick(args);*/
    }
}

void csRADIOBUTTON::setMouseOverItem(int id)
{
    *lastMouseOverid = id;
}


void csRADIOBUTTON::updateActiveItem(int id)
{
    if(id < title.size())
    {
        *lastMouseOverid = id;
        args.setId(&parent);
        args.setHwnd(&cv.CNTLIST[parent]);
        mouseClick(args);
    }
}

void csRADIOBUTTON::unActivateItem(int id)
{
    if(id < title.size())
    {
        color0[id]=color1[id];
        bkgcol0[id]=bkgcol1[id];
        dcs0[id]=imgdc1.dc;
        activeChoosed = 1;
        
    }
}

void csRADIOBUTTON::create()
{
    if(activeChoosed==0)
    {
        setActiveItem(0);
    }
    organize();
    animate();
    refresh();
}

void csRADIOBUTTON::copyItem(int id)
{
    rbItem.bkgcol0 = bkgcol0[id];
    rbItem.bkgcol1 = bkgcol1[id];
    rbItem.bkgcol2 = bkgcol2[id];
    rbItem.bkgcol3 = bkgcol3[id];
    rbItem.bkgcol4 = bkgcol4[id];

    rbItem.color0 = color0[id];
    rbItem.color1 = color1[id];
    rbItem.color2 = color2[id];
    rbItem.color3 = color3[id];
    rbItem.color4 = color4[id];

    rbItem.dcs0 = dcs0[id];
    rbItem.dcs1 = dcs1[id];
    rbItem.dcs2 = dcs2[id];
    rbItem.dcs3 = dcs3[id];
    rbItem.dcs4 = dcs4[id];

    rbItem.font = font[id];
    /*if(rbItem.title)
    {
        free(rbItem.title);
        rbItem.title = 0;
    }*/
    rbItem.title = csf_alloc<char>(strlen(title[id])+1);
    sprintf(rbItem.title,"%s",title[id]);

    rbItem.posTitle = posTitle[id];
    rbItem.pos = pos[id];
    rbItem.posImg = posImg[id];

}

bool* csRADIOBUTTON::getCopyPasteState()
{
    return cutPasteDone;
}

int* csRADIOBUTTON::getCopyPasteKeyDownState()
{
    return copyPasteKeyDownState;
}

void csRADIOBUTTON::cutItem(int id)
{
    copyItem(id);
    removeItem(id); 
}

void csRADIOBUTTON::pasteItem(int id)
{
    
    unActivateItem(*lastMouseClickid);

    bkgcol0.insertAt(rbItem.bkgcol0, id);
    bkgcol1.insertAt(rbItem.bkgcol1, id);
    bkgcol2.insertAt(rbItem.bkgcol2, id);
    bkgcol3.insertAt(rbItem.bkgcol3, id);
    bkgcol4.insertAt(rbItem.bkgcol4, id);

    color0.insertAt(rbItem.color0, id);
    color1.insertAt(rbItem.color1, id);
    color2.insertAt(rbItem.color2, id);
    color3.insertAt(rbItem.color3, id);
    color4.insertAt(rbItem.color4, id);

    dcs0.insertAt(rbItem.dcs0, id);
    dcs1.insertAt(rbItem.dcs1, id);
    dcs2.insertAt(rbItem.dcs2, id);
    dcs3.insertAt(rbItem.dcs3, id);
    dcs4.insertAt(rbItem.dcs4, id);

    font.insertAt(rbItem.font, id);
    title.insertAt(rbItem.title, id);

    posTitle.insertAt(rbItem.posTitle, id);
    pos.insertAt(rbItem.pos, id);
    posImg.insertAt(rbItem.posImg, id);

    setActiveItem(id);
}

void csRADIOBUTTON::duplicate(int src, int _pos)
{
    color0[_pos] = color1[_pos];
    dcs0[_pos] = dcs1[_pos];
    bkgcol0[_pos] = bkgcol1[_pos];
    
    unActivateItem(*lastMouseClickid);

    bkgcol0.insertAt(bkgcol0[src], _pos);
    bkgcol1.insertAt(bkgcol1[src], _pos);
    bkgcol2.insertAt(bkgcol2[src], _pos);
    bkgcol3.insertAt(bkgcol3[src], _pos);
    bkgcol4.insertAt(bkgcol4[src], _pos);

    color0.insertAt(color0[src], _pos);
    color1.insertAt(color1[src], _pos);
    color2.insertAt(color2[src], _pos);
    color3.insertAt(color3[src], _pos);
    color4.insertAt(color4[src], _pos);

    dcs0.insertAt(dcs0[src], _pos);
    dcs1.insertAt(dcs1[src], _pos);
    dcs2.insertAt(dcs2[src], _pos);
    dcs3.insertAt(dcs3[src], _pos);
    dcs4.insertAt(dcs4[src], _pos);

    font.insertAt(font[src], _pos);
    title.insertAt(title[src], _pos);

    posTitle.insertAt(posTitle[src], _pos);
    pos.insertAt(pos[src], _pos);
    posImg.insertAt(posImg[src], _pos);


    if(zebFact > 0.0)
    {
        float zf = zebFact/2;
        COLORREF col_inact = RGB((defcol.r*(1-zf) + zebColor.r*zf), 
                                    (defcol.g*(1-zf) + zebColor.g*zf),
                                    (defcol.b*(1-zf) + zebColor.b*zf));
        COLORREF col = RGB((defcol.r*(1-zebFact) + zebColor.r*zebFact), 
                                (defcol.g*(1-zebFact) + zebColor.g*zebFact),
                                (defcol.b*(1-zebFact) + zebColor.b*zebFact));
        *n= color0.size();
        for(int i=_pos; i<*n; i++)
        {
            if(i%2 == 0)
            {
                bkgcol0[i] = col;
                bkgcol1[i] = col;
                bkgcol4[i] = col_inact;
            }
            else
            {
                bkgcol0[i] = dfltBkgCol1;
                bkgcol1[i] = dfltBkgCol1;
                bkgcol4[i] = dfltBkgCol4;
            }
        }
    }

    setActiveItem(_pos);
}

void csRADIOBUTTON::moveItem(int from, int to)
{
    //if(from >=0 && to >= 0 && from < *n && to < *n)
    {
        color0[to] = color1[to];
        dcs0[to] = dcs1[to];
        bkgcol0[to] = bkgcol1[to];

        unActivateItem(from);

        color0.move(from, to);
        color1.move(from, to);
        color2.move(from, to);
        color3.move(from, to);
        color4.move(from, to);

        dcs0.move(from, to);
        dcs1.move(from, to);
        dcs2.move(from, to);
        dcs3.move(from, to);
        dcs4.move(from, to);
        
        font.move(from, to);
        title.move(from, to);

        posTitle.move(from, to);
        pos.move(from, to);
        posImg.move(from, to);
        
        if(zebFact == 0)
        {
            bkgcol0.move(from, to);
            bkgcol1.move(from, to);
            bkgcol2.move(from, to);
            bkgcol3.move(from, to);
            bkgcol4.move(from, to);
        }
        setActiveItem(to);
    }
}

void csRADIOBUTTON::removeItem(int id)
{
    if(title.size()>1)
    {
        int n = title.size()-1;
        if(zebFact>0 && id<n)
        {
            for(int i=n; i>id; i--)
            {
                int id1 = i-1;
                bkgcol0[i] = bkgcol0[id1];
                bkgcol1[i] = bkgcol1[id1];
                bkgcol2[i] = bkgcol2[id1];
                bkgcol3[i] = bkgcol3[id1];
            }

        }
        title.deleteAt(id);
        pos.deleteAt(id);
        posImg.deleteAt(id);
        posTitle.deleteAt(id);
        color0.deleteAt(id);
        color1.deleteAt(id);
        color2.deleteAt(id);
        color3.deleteAt(id);
        color4.deleteAt(id);
        bkgcol0.deleteAt(id);
        bkgcol1.deleteAt(id);
        bkgcol2.deleteAt(id);
        bkgcol3.deleteAt(id);
        bkgcol4.deleteAt(id);
        font.deleteAt(id);
        dcs0.deleteAt(id);
        dcs1.deleteAt(id);
        dcs2.deleteAt(id);
        dcs3.deleteAt(id);
        dcs4.deleteAt(id);

        if(title.size()>id)
            setActiveItem(id);
        else
            setActiveItem(id-1);
    }
    else
    {
        title.clear();
        pos.clear();
        posImg.clear();
        posTitle.clear();
        color0.clear();
        color1.clear();
        color2.clear();
        color3.clear();
        color4.clear();
        bkgcol0.clear();
        bkgcol1.clear();
        bkgcol2.clear();
        bkgcol3.clear();
        bkgcol4.clear();
        font.clear();
        dcs0.clear();
        dcs1.clear();
        dcs2.clear();
        dcs3.clear();
        dcs4.clear();
    }
}

void csRADIOBUTTON::setDefaultTitle(char* _dfltTitle)
{
    sprintf(dfltTitle,"%s",_dfltTitle);
}

void csRADIOBUTTON::newItem(char*_title,RECT r, int n, char*img1, char*img2, char*img3, char*img4)
{
    char*str = _title;
    for(int i=0; i<n; i++)
    {
        if(!_title)
        {
            str = defaultItemTitle();
        }

        title.insertEnd(str);
        pos.insertEnd(r);
        posImg.insertEnd({0});
        posTitle.insertEnd({0});
        color0.insertEnd(dfltColor1);
        color1.insertEnd(dfltColor1);
        color2.insertEnd(dfltColor2);
        color3.insertEnd(dfltColor3);
        color4.insertEnd(dfltColor4);
        if(zebFact == 0.0)
        {
            bkgcol0.insertEnd(dfltBkgCol1);
            bkgcol1.insertEnd(dfltBkgCol1);
            bkgcol4.insertEnd(dfltBkgCol4);
        }
        else
        {
            if(color0.size()%2 == 1)
            {
                COLORREF col = RGB((defcol.r*(1-zebFact) + zebColor.r*zebFact), 
                                   (defcol.g*(1-zebFact) + zebColor.g*zebFact),
                                   (defcol.b*(1-zebFact) + zebColor.b*zebFact));
                bkgcol0.insertEnd(col);
                bkgcol1.insertEnd(col);
                float zf = zebFact/2;
                bkgcol4.insertEnd(RGB((defcol.r*(1-zf) + zebColor.r*zf), 
                                   (defcol.g*(1-zf) + zebColor.g*zf),
                                   (defcol.b*(1-zf) + zebColor.b*zf)));
            }
            else
            {
                bkgcol0.insertEnd(dfltBkgCol1);
                bkgcol1.insertEnd(dfltBkgCol1);
                bkgcol4.insertEnd(dfltBkgCol4);
            }
        }
        bkgcol2.insertEnd(dfltBkgCol2);
        bkgcol3.insertEnd(dfltBkgCol3);
        font.insertEnd(dfltFont);
        if(img1==0 || img2==0)
        {
            dcs0.insertEnd(imgdc1.dc);
            dcs1.insertEnd(imgdc1.dc);
            dcs2.insertEnd(imgdc2.dc);
            dcs3.insertEnd(imgdc3.dc);
            dcs4.insertEnd(imgdc4.dc);
        }
        else
        {

            csDC idc1 = csGetImgBits(img1, {imgSize.cx,imgSize.cy});
            csDC idc2 = csGetImgBits(img2, {imgSize.cx,imgSize.cy});
            csDC idc3 = csGetImgBits(img3, {imgSize.cx,imgSize.cy});
            csDC idc4 = csGetImgBits(img4, {imgSize.cx,imgSize.cy});
            dcs0.insertEnd(idc1.dc);
            dcs1.insertEnd(idc1.dc);
            dcs2.insertEnd(idc2.dc);
            dcs3.insertEnd(idc3.dc);
            dcs4.insertEnd(idc4.dc);
            DeleteBitmap(idc1.hbmp);
            DeleteBitmap(idc2.hbmp);
            DeleteBitmap(idc3.hbmp);
            DeleteBitmap(idc4.hbmp);
            //csFreeDC(idc1);
            //csFreeDC(idc2);
        }

        unActivateItem(*lastMouseClickid);
        setActiveItem(title.size()-1);
        //activeChoosed = 0;
        
    }
}

void csRADIOBUTTON::organize()
{

    HDC dc =cv.CTX[parent].createDC(hdc);
    SetBkMode(dc, TRANSPARENT);
    if(TextPos == CS_RDBTN_TEXT_AFTER)
    {
        int ximg, yimg, xstr, ystr, xof = offset.cx, yof = offset.cy, j, k, N=gridWidth;
        int cxmax = cv.CNTCLWRECT[parent].right, cymax=cv.CNTCLWRECT[parent].bottom;
        bool b = 0;
        for(int i=0; i<title.size(); i++)
        {
            k = i/N;
            j = i%N;
            /*if(k==0)
                xof = 0;
            else
                xof = offset.cx;
            if(j==0)
                yof = 0;
            else
                yof = offset.cy;*/
            int a = (dfltSz.cx + xof)*j, b = (dfltSz.cy + yof)*k;
            ximg = marging.cx + a;
            yimg = marging.cy + b + dfltSz.cy/2 - imgdc1.sz.height/2;
            pos[i] = {ximg,marging.cy+b, ximg+dfltSz.cx, marging.cy+b+dfltSz.cy};
            posImg[i] = {ximg,yimg};
            xstr = ximg + imgdc1.sz.width + 5;
            if(cxmax < pos[i].right) cxmax = pos[i].right;
            if(cymax < pos[i].bottom) cymax = pos[i].bottom;
            //std::cout<<pos[i].left<<","<<pos[i].top<< ","<<pos[i].right<<","<<pos[i].bottom<<"\n";
            if(textOrientation == CS_RDBTN_TEXT_H)
            {
                ystr = marging.cy + b+ (dfltSz.cy-fontSize.cx)/2;
                //std::cout<<5445454545<<"\n";
            }
            else if(textOrientation == CS_RDBTN_TEXT_V1)
                ystr = marging.cy + b ;//+ dfltSz.cy/2;
            else if(textOrientation == CS_RDBTN_TEXT_V2)
            {
                //LPSIZE lps = csTextExtent(parent, font[i], title[i]);
                ystr = marging.cy - b - dfltSz.cy/2;
            }
            posTitle[i] = {xstr, ystr};
            csDrawGDIRectangle(dc,bkgcol0[i],bkgcol0[i],1,pos[i]);
            SelectFont(dc, font[i]);
            SetTextColor(dc, color0[i]);
            TextOut(dc,xstr,ystr,(LPCSTR)title[i],strlen(title[i]));
            BitBlt(dc,ximg,yimg,imgdc1.sz.width,imgdc1.sz.height, dcs0[i],0,0,SRCCOPY);
        }
        if(cv.cp[parent]->DCSizes.width<cxmax)
        {
            cv.cp[parent]->DCSizes.width = cxmax;// + dfltSz.cx*30;
            b = 1;
        }
        if(cv.cp[parent]->DCSizes.height<cymax)
        {
            cv.cp[parent]->DCSizes.height = cymax;// + dfltSz.cy*30;
            b = 1;
        }
        if(b)
        {
            cv.CTX[parent].setDwgSurfSize({cv.cp[parent]->DCSizes.width,cv.cp[parent]->DCSizes.height});
        }
    }
    SendMessage(cv.CNTLIST[parent],WM_ERASEBKGND,0,0);

}

void organize2(int parent, int n, SIZE imgSize,
                RECT*pos,POINT*posImg,POINT*posTitle, HDC* dcs0, HFONT* font, COLORREF* color0, COLORREF* bkgcol0, char**title, HDC hdc)
{

    //HDC hdc = GetDC(cv.CNTLIST[parent]);
    HDC dc =cv.CTX[parent].createDC(hdc);
    SetBkMode(dc, TRANSPARENT);
    for(int i=0; i<n; i++)
    {
        SelectFont(dc, font[i]);
        SetTextColor(dc, color0[i]);
        csDrawGDIRectangle(dc,bkgcol0[i],bkgcol0[i],1,pos[i]);
        TextOut(dc,posTitle[i].x,posTitle[i].y,(LPCSTR)title[i],strlen(title[i]));
        BitBlt(dc,posImg[i].x,posImg[i].y,imgSize.cx,imgSize.cy, dcs0[i],0,0,SRCCOPY);
    }

    SendMessage(cv.CNTLIST[parent],WM_ERASEBKGND,0,0);
    //ReleaseDC(cv.CNTLIST[parent], hdc);
}

void colorTracking(int parent, int lastItem, int currentItem, int n, SIZE imgSize,
                RECT*pos,POINT*posImg,POINT*posTitle, HDC* dcs0, HFONT* font,
                 COLORREF* color0, COLORREF* bkgcol0, char**title, HDC hdc)
{

    //HDC hdc = GetDC(cv.CNTLIST[parent]);
    //std::cout<<currentItem<<"\n";
    HDC gdc = cv.CTX[parent].getDC();
    //HDC gdc = GetDC(0);
    int i=lastItem;
    csSIZE sz = {pos[i].right-pos[i].left,pos[i].bottom-pos[i].top};
    csDC idc = csNewCompatibleDC(hdc,sz, bkgcol0[i]);
    SetBkMode(idc.dc, TRANSPARENT);
    SelectFont(idc.dc, font[i]);
    SetTextColor(idc.dc, color0[i]);
    TextOut(idc.dc,posTitle[i].x-pos[i].left,posTitle[i].y-pos[i].top,(LPCSTR)title[i],strlen(title[i]));
    BitBlt(idc.dc,posImg[i].x-pos[i].left,posImg[i].y-pos[i].top,imgSize.cx,imgSize.cy, dcs0[i],0,0,SRCCOPY);
    BitBlt(gdc,pos[i].left,pos[i].top,sz.width,sz.height, idc.dc,0,0,SRCCOPY);
    csFreeDC(idc);

    i = currentItem;
    sz = {pos[i].right-pos[i].left,pos[i].bottom-pos[i].top};
    idc = csNewCompatibleDC(hdc,sz, bkgcol0[i]);
    SetBkMode(idc.dc, TRANSPARENT);
    SelectFont(idc.dc, font[i]);
    SetTextColor(idc.dc, color0[i]);
    TextOut(idc.dc,posTitle[i].x-pos[i].left,posTitle[i].y-pos[i].top,(LPCSTR)title[i],strlen(title[i]));
    BitBlt(idc.dc,posImg[i].x-pos[i].left,posImg[i].y-pos[i].top,imgSize.cx,imgSize.cy, dcs0[i],0,0,SRCCOPY);
    BitBlt(gdc,pos[i].left,pos[i].top,sz.width,sz.height, idc.dc,0,0,SRCCOPY);
    csFreeDC(idc);
//std::cout<<"\n j = "<<lastItem<<" , i = "<<currentItem<<"   ----------\n";
    SendMessage(cv.CNTLIST[parent],WM_ERASEBKGND,0,0);
    InvalidateRect(cv.CNTLIST[parent],0,1);
    //ReleaseDC(0, gdc);
}


void csRADIOBUTTON::animate()
{
    *n = pos.size();
    *pimgSize = imgSize;
    *pmarging = marging;
    *pdfltSz = dfltSz;
    *poffset = offset;
    *pgridWidth = gridWidth;

    if(args.getArgNumber()!=0)
    {
        args.freeArgs();
    }
    args.setArgNumber(40);
    args.makeArgs(dcs0.getTable(), dcs1.getTable(),dcs2.getTable(),dcs3.getTable(),
                 color0.getTable(), color1.getTable(),color2.getTable(),color3.getTable(),
                 bkgcol0.getTable(), bkgcol1.getTable(),bkgcol2.getTable(),bkgcol3.getTable(),
                 pos.getTable(), posImg.getTable(), posTitle.getTable(),
                 font.getTable(), title.getTable(), pimgSize,
        lastMouseOverid, lastMouseClickid, n, &colorTracking, cntActivate, phdc,
        vkCtrlCount, vkCtrlCountControl, vkCtrlPoint, vkCtrlGdcPos, pmarging, pdfltSz, 
        poffset, pgridWidth, smoothRepos, smoothReposCount, 
        cutPasteViewer, cutPasteStart, cutPasteDone, cutPasteDone0,copyPasteKeyDownState,click_message);

    if(!animated)
    {
        csSetAction(parent, WM_MOUSEMOVE, _mouseMove, args); // contient makeCutPaste()
        csSetAction(parent, WM_LBUTTONDOWN, mouseClick, args); // contient startCutPaste()
        csSetAction(parent, WM_LBUTTONUP, endCutPaste, args);
        csSetAction(parent, WM_MOUSELEAVE, mouseLeave, args);
        csSetAction(parent, WM_KEYDOWN, vkeydownSelect, args);
        csSetAction(parent, WM_TIMER, autoReposition, args);
        //csSetAction(parent, WM_TIMER, vkeydownSrcoll_timer, args);
        //csSetAction(parent, WM_KEYUP, vkeyupScroll, args);
        animated = 1;
        getUsefulEventsNumber();
    }
    else
    {
        cv.cp[parent]->CntEventsFunc.MOUSEMOVE_ARGS[moveMsgPos] = args;
        cv.cp[parent]->CntEventsFunc.LBUTTONDOWN_ARGS[lbtnDownMsgPos] = args;
        cv.cp[parent]->CntEventsFunc.LBUTTONUP_ARGS[lbtnUpMsgPos] = args;
        cv.cp[parent]->CntEventsFunc.MOUSELEAVE_ARGS[leaveMsgPos] = args;
        cv.cp[parent]->CntEventsFunc.KEYDOWN_ARGS[leaveMsgPos] = args;
        cv.cp[parent]->CntEventsFunc.TIMER_ARGS[timerMsgPos] = args;
        //cv.cp[parent]->CntEventsFunc.KEYUP_ARGS[0] = args;
    }

    //csSetAction(parent, WM_LBUTTONDOWN, mouseClick, cv.cp[parent]->CntEventsFunc.MOUSEMOVE_ARGS[0]);
}

void csRADIOBUTTON::getUsefulEventsNumber()
{
    moveMsgPos = cv.cp[parent]->CntEventsFunc.MOUSEMOVE_ARGS.size()-1;
    lbtnDownMsgPos = cv.cp[parent]->CntEventsFunc.LBUTTONDOWN_ARGS.size()-1;
    lbtnUpMsgPos = cv.cp[parent]->CntEventsFunc.LBUTTONUP_ARGS.size()-1;
    leaveMsgPos = cv.cp[parent]->CntEventsFunc.MOUSELEAVE_ARGS.size()-1;
    timerMsgPos = cv.cp[parent]->CntEventsFunc.TIMER_ARGS.size()-1;
    keyDownMsgPos = cv.cp[parent]->CntEventsFunc.KEYDOWN_ARGS.size()-1;
    keyUpMsgPos = cv.cp[parent]->CntEventsFunc.KEYUP_ARGS.size()-1;
    
}

void csRADIOBUTTON::refresh()
{

    if(*cntActivate)
    {
        organize2(parent, pos.size(), imgSize,
            pos.getTable(),posImg.getTable(),posTitle.getTable(),
            dcs0.getTable(), font.getTable(), color0.getTable(),bkgcol1.getTable(), title.getTable(), hdc);

        if(font.size())
        {
            int i = *lastMouseClickid;
            HDC dc = cv.CTX[parent].getDC();
            SelectFont(dc, font[i]);
            SetTextColor(dc, color3[i]);
            csDrawGDIRectangle(dc,bkgcol3[i],bkgcol3[i],1,pos[i]);
            TextOut(dc,posTitle[i].x,posTitle[i].y,(LPCSTR)title[i],strlen(title[i]));
            BitBlt(dc,posImg[i].x,posImg[i].y,imgSize.cx,imgSize.cy, dcs3[i],0,0,SRCCOPY);
        }
    }
    else
    {
        organize2(parent, pos.size(), imgSize,
            pos.getTable(),posImg.getTable(),posTitle.getTable(),
            dcs4.getTable(), font.getTable(), color4.getTable(),bkgcol4.getTable(), title.getTable(), hdc);
    }
    InvalidateRect(cv.CNTLIST[parent], 0,1);
}

void mouseMouve2()
{
    int lastMouseOverid = 451;
    std::cout<<lastMouseOverid<<"\n";
}

void _mouseMove(csARGS Args)
{
    bool cntState = *(bool*)Args[22];
    short g = GetAsyncKeyState(VK_LBUTTON); // evite un bug
    if(cntState && (!g || (g && PtInRect(&cv.CNTRECT[int(Args)],cv.TRACKING_POINT2))))
    {
        int id = (int)Args;
        HDC* dcs0=(HDC*)Args[0];
        HDC* dcs1=(HDC*)Args[1];
        HDC* dcs2=(HDC*)Args[2];
        HDC* dcs3=(HDC*)Args[3];
        COLORREF* color0=(COLORREF*)Args[4];
        COLORREF* color1=(COLORREF*)Args[5];
        COLORREF* color2=(COLORREF*)Args[6];
        COLORREF* color3=(COLORREF*)Args[7];
        COLORREF* bkgcol0=(COLORREF*)Args[8];
        COLORREF* bkgcol1=(COLORREF*)Args[9];
        COLORREF* bkgcol2=(COLORREF*)Args[10];
        COLORREF* bkgcol3=(COLORREF*)Args[11];
        RECT* pos=(RECT*)Args[12];
        POINT* posImg=(POINT*)Args[13];
        POINT* posTitle=(POINT*)Args[14];
        HFONT* font=(HFONT*)Args[15];
        char** title=(char**)Args[16];
        SIZE imgSize = *(SIZE*)Args[17];
        int* lastMouseOverid = (int*)Args[18];
        int* lastMouseClickid = (int*)Args[19];
        int n = *(int*)Args[20];
        HDC parentdc = *(HDC*)Args[23];

        int *vkCtrlCount = (int*)Args[24];
        int *vkCtrlCountControl = (int*)Args[25];
        POINT vkCtrlPoint = *(POINT*)Args[26];
        POINT vkCtrlGdcPos = *(POINT*)Args[27];
        SIZE marging = *(SIZE*)Args[28];
        SIZE dfltSz = *(SIZE*)Args[29];
        SIZE offset = *(SIZE*)Args[30];
        int width = *(int*)Args[31];

        POINT p={0,0}, pvk;
        GetCursorPos(&p);
        pvk = p;

        ScreenToClient(HWND(Args), &p);
        
        if(!PtInRect(&cv.CNTRECT[id], pvk))
        {
            SendMessage(HWND(Args), WM_LBUTTONUP,0,0); // resolution du bug cause par wm_keydown
        }
        else
        {if(*vkCtrlCount == 0)
        {
            POINT dcpos = cv.CTX[id].getDwgSurfPos();
            
            if(n>0)
            {
                int lastId = *lastMouseOverid;
                float jf = (p.x - dcpos.x - marging.cx)/float(dfltSz.cx + offset.cx);
                float kf = (p.y - dcpos.y - marging.cy)/float(dfltSz.cy + offset.cy);

                int j = ((jf - int(jf))*(dfltSz.cx + offset.cx) <= dfltSz.cx)?int(jf):-1;
                int k = ((kf - int(kf))*(dfltSz.cy + offset.cy) <= dfltSz.cy)?int(kf):-1;

                int i = k*width + j;

                if(i>=0 && i<n && lastId >= 0 && lastId < n)
                {
                    if(*lastMouseClickid != lastId)
                    {
                        color0[lastId] = color1[lastId];
                        bkgcol0[lastId] = bkgcol1[lastId];
                        dcs0[lastId] = dcs1[lastId];
                    }
                    
                    if(i != *lastMouseClickid)
                    {
                        color0[i] = color2[i];
                        bkgcol0[i] = bkgcol2[i];
                        dcs0[i] = dcs2[i];
                    }
                    if(*lastMouseOverid != i)
                    {
                        ((void(*)(int,int,int,int,SIZE, RECT*,POINT*,POINT*, HDC*, HFONT*, COLORREF*, COLORREF*, char**, HDC))((void*)Args[21]))(
                            id,lastId, i,n, imgSize, pos, posImg, posTitle, dcs0, font, color0, bkgcol0, title, parentdc);
                        //*lastMouseOverid = i;
                    }
                }
                else
                    SendMessage(cv.CNTLIST[id],WM_MOUSELEAVE,0,0);
                *lastMouseOverid = i;    
            }
        }
        else if(*vkCtrlCount == 2)
        {
            int dx = pvk.x - vkCtrlPoint.x;
            int dy = pvk.y - vkCtrlPoint.y;

            int DX = cv.CNTRECT[id].right - vkCtrlPoint.x;
            int DY = cv.CNTRECT[id].bottom - vkCtrlPoint.y;

            int CX = cv.cp[id]->DCSizes.width - cv.CNTCLWRECT[id].right;
            int CY = cv.cp[id]->DCSizes.height - cv.CNTCLWRECT[id].bottom;

            int cx = -dx*CX*2/DX;
            int cy = -dy*CY*2/DY;
            POINT pt = {vkCtrlGdcPos.x+cx, vkCtrlGdcPos.y+cy};

            if(pt.x>0) pt.x = 0;
            if(pt.y>0) pt.y=0;
            if(pt.x<-CX) pt.x = cx;
            if(pt.y<-CY) pt.y = cy;
            //std::cout<<pt.x<<" , "<<pt.y<<"\n";
            cv.CTX[id].setDwgSurfPos(pt);
            InvalidateRect((HWND)Args,0,1);

        }
        }

        

        makeCutPaste(Args);
    }
}


void mouseClick(csARGS Args)
{
    bool cntState = *(bool*)Args[22];
    if(cntState)
    {
        int id = (int)Args;
        HDC* dcs0=(HDC*)Args[0];
        HDC* dcs1=(HDC*)Args[1];
        HDC* dcs2=(HDC*)Args[2];
        HDC* dcs3=(HDC*)Args[3];
        COLORREF* color0=(COLORREF*)Args[4];
        COLORREF* color1=(COLORREF*)Args[5];
        COLORREF* color2=(COLORREF*)Args[6];
        COLORREF* color3=(COLORREF*)Args[7];
        COLORREF* bkgcol0=(COLORREF*)Args[8];
        COLORREF* bkgcol1=(COLORREF*)Args[9];
        COLORREF* bkgcol2=(COLORREF*)Args[10];
        COLORREF* bkgcol3=(COLORREF*)Args[11];
        RECT* pos=(RECT*)Args[12];
        POINT* posImg=(POINT*)Args[13];
        POINT* posTitle=(POINT*)Args[14];
        HFONT* font=(HFONT*)Args[15];
        char** title=(char**)Args[16];
        SIZE imgSize = *(SIZE*)Args[17];
        int* lastMouseOverid = (int*)Args[18];
        int* lastMouseClickid = (int*)Args[19];
        int n = *(int*)Args[20];
        HDC parentdc = *(HDC*)Args[23];
        bool*click_message = (bool*)Args[39];

        
        int* smoothReposCount = (int*)Args[33];

        if(n>0 && *lastMouseOverid >=0 &&  *lastMouseOverid < n && *lastMouseClickid >= 0 && *lastMouseClickid < n)
        {
            int i = *lastMouseOverid, j = *lastMouseClickid;
            if(i!=j)
            {
                color0[i] = color3[i];
                bkgcol0[i] = bkgcol3[i];
                dcs0[i] = dcs3[i];
                //std::cout<<"\n j = "<<j<<" , i = "<<i<<"   ----------\n";
                //std::cout<<"\n idparent = "<<id<<"   ----------\n";
                dcs0[j] = dcs1[j];
                color0[j] = color1[j];
                bkgcol0[j] = bkgcol1[j];
                *lastMouseClickid = i;
                ((void(*)(int,int,int,int,SIZE, RECT*,POINT*,POINT*, HDC*, HFONT*, COLORREF*, COLORREF*, char**, HDC))((void*)Args[21]))(
                                id,j, i,n, imgSize, pos, posImg, posTitle, dcs0, font, color0, bkgcol0, title, parentdc);

                *click_message = 1;
            }
        }
        
        //void (*f)() = (void(*)())((void*)Args[11]);
        //f();
        int *vkCtrlCount = (int*)Args[24];
        int *vkCtrlCountControl = (int*)Args[25];
        *vkCtrlCount = 0;
        *vkCtrlCountControl = 0;

        *smoothReposCount = 0;

        startCutPaste(Args);
    }
}

void mouseLeave(csARGS Args)
{
    bool cntState = *(bool*)Args[22];
    if(cntState)
    {
        int id = (int)Args;
        HDC* dcs0=(HDC*)Args[0];
        HDC* dcs1=(HDC*)Args[1];
        HDC* dcs2=(HDC*)Args[2];
        HDC* dcs3=(HDC*)Args[3];
        COLORREF* color0=(COLORREF*)Args[4];
        COLORREF* color1=(COLORREF*)Args[5];
        COLORREF* color2=(COLORREF*)Args[6];
        COLORREF* color3=(COLORREF*)Args[7];
        COLORREF* bkgcol0=(COLORREF*)Args[8];
        COLORREF* bkgcol1=(COLORREF*)Args[9];
        COLORREF* bkgcol2=(COLORREF*)Args[10];
        COLORREF* bkgcol3=(COLORREF*)Args[11];
        RECT* pos=(RECT*)Args[12];
        POINT* posImg=(POINT*)Args[13];
        POINT* posTitle=(POINT*)Args[14];
        HFONT* font=(HFONT*)Args[15];
        char** title=(char**)Args[16];
        SIZE imgSize = *(SIZE*)Args[17];
        int* lastMouseOverid = (int*)Args[18];
        int* lastMouseClickid = (int*)Args[19];
        int n = *(int*)Args[20];
        HDC parentdc = *(HDC*)Args[23];

        if(*lastMouseOverid != *lastMouseClickid && n>0 && *lastMouseOverid < n && *lastMouseClickid < n
            && *lastMouseOverid >= 0 && *lastMouseClickid >= 0)
        {
            int i = *lastMouseOverid;
            color0[i] = color1[i];
            bkgcol0[i] = bkgcol1[i];
            dcs0[i] = dcs1[i];
            ((void(*)(int,int,int,int,SIZE, RECT*,POINT*,POINT*, HDC*, HFONT*, COLORREF*, COLORREF*, char**, HDC))((void*)Args[21]))(
                            id,*lastMouseClickid, i,n, imgSize, pos, posImg, posTitle, dcs0, font, color0, bkgcol0, title, parentdc);
            *lastMouseOverid=*lastMouseClickid;
        }

        //void (*f)() = (void(*)())((void*)Args[11]);
        //f();
        int *vkCtrlCount = (int*)Args[24];
        int *vkCtrlCountControl = (int*)Args[25];
        *vkCtrlCount = 0;
        *vkCtrlCountControl = 0;

        int *cutPasteViewer = (int*)Args[34];
        if(cutPasteViewer)
        {
            if(cv.cp[*cutPasteViewer]->Show)
            {
                bool*cutPasteStart = (bool*)Args[35];
                bool*cutPasteDone = (bool*)Args[36];
                bool*cutPasteDone0 = (bool*)Args[37];
        
                cv.cp[*cutPasteViewer]->Show = 0;
                *cutPasteStart = 0;

                if(*cutPasteDone0)
                {
                    *cutPasteDone0 = 0;
                    *cutPasteDone = 1;
                }
           }
        }
            
    }
}

void autoReposition(csARGS Args)
{
    bool cntState = *(bool*)Args[22];
    if(cntState)
    {
        
        int id = (int)Args;
        RECT* pos=(RECT*)Args[12];
        int lastMouseOverid = *(int*)Args[18];
        int lastMouseClickid = *(int*)Args[19];
        int n = *(int*)Args[20];
        int* smoothRepos = (int*)Args[32];
        int* smoothReposCount = (int*)Args[33];

        if(*smoothReposCount < *smoothRepos)
        {
            if(lastMouseClickid >= 0 && lastMouseClickid < n && n>0)
            {
                POINT p = cv.CTX[id].getDwgSurfPos();
                if(pos[lastMouseClickid].right+p.x > cv.CNTCLWRECT[id].right)
                {
                    int dx = (pos[lastMouseClickid].right+p.x - cv.CNTCLWRECT[id].right);
                    if(pos[lastMouseClickid].left+p.x - dx > 0) 
                    {
                        int a = dx/(*smoothRepos);
                        if(a == 0) a = dx;
                        p.x -= a;
                        cv.CTX[id].setDwgSurfPos(p);
                        InvalidateRect(HWND(Args),0,1);
                    }
                }
                else if(pos[lastMouseClickid].left+p.x < 0)
                {
                    int dx = pos[lastMouseClickid].left+p.x;
                    int a = dx/(*smoothRepos);
                    if(a == 0) a = dx;
                    p.x -= a;
                    cv.CTX[id].setDwgSurfPos(p);
                    InvalidateRect(HWND(Args),0,1);
                }
                else if(pos[n-1].right+p.x < cv.CNTCLWRECT[id].right)
                {
                    int dx = -(p.x+pos[n-1].right - cv.CNTCLWRECT[id].right);
                    if(dx + p.x <= 0) 
                    {
                        int a = dx/(*smoothRepos);
                        if(a == 0) a = dx;
                        p.x += a;
                        cv.CTX[id].setDwgSurfPos(p);
                        InvalidateRect(HWND(Args),0,1);
                    }
                    else if(p.x < 0)
                    {
                        cv.CTX[id].setDwgSurfPos({0,p.y});
                        InvalidateRect(HWND(Args),0,1);
                    }
                }
                
                if(pos[lastMouseClickid].bottom+p.y > cv.CNTCLWRECT[id].bottom)
                {
                    int dy = (pos[lastMouseClickid].bottom+p.y - cv.CNTCLWRECT[id].bottom);
                    if(pos[lastMouseClickid].top+p.y - dy > 0) 
                    {
                        int a = dy/(*smoothRepos);
                        if(a == 0) a = dy;
                        p.y -= a;
                        cv.CTX[id].setDwgSurfPos(p);
                        InvalidateRect(HWND(Args),0,1);
                    }
                }
                else if(pos[lastMouseClickid].top+p.y < 0)
                {
                    int dy = pos[lastMouseClickid].top+p.y;
                    int a = dy/(*smoothRepos);
                    if(a == 0) a = dy;
                    p.y -= a;
                    cv.CTX[id].setDwgSurfPos(p);
                    InvalidateRect(HWND(Args),0,1);
                }
                
                else if(pos[n-1].bottom+p.y < cv.CNTCLWRECT[id].bottom)
                {
                    int dy = -(p.y+pos[n-1].bottom - cv.CNTCLWRECT[id].bottom);
                    if(dy + p.y <= 0) 
                    {
                        int a = dy/(*smoothRepos);
                        if(a == 0) a = dy;
                        p.y += a;
                        cv.CTX[id].setDwgSurfPos(p);
                        InvalidateRect(HWND(Args),0,1);
                    }
                    else if(p.y < 0)
                    {
                        cv.CTX[id].setDwgSurfPos({p.x,0});
                        InvalidateRect(HWND(Args),0,1);
                    }
                }
                
            }
            *smoothReposCount += 1;
        }
    }
}

//effectuer un double press de la touche 'controle' -------------------------------------------
void vkeydownSrcoll(csARGS Args)
{
    bool cntState = *(bool*)Args[22];
    if(cntState)
    {
        
        int id = (int)Args;
        int *count = (int*)Args[24];
        int *countControl = (int*)Args[25];

        if((WPARAM)Args == VK_CONTROL)
        {
            *count = 2;
            GetCursorPos((POINT*)Args[26]);
            *(POINT*)Args[27] = cv.CTX[id].getDwgSurfPos();
            /*if(*countControl==0)
                *count = 1;
            else if(*count == 1)
            {std::cout<<"sdfdfs\n";
                GetCursorPos((POINT*)Args[21]);
                *(POINT*)Args[22] = cv.CTX[id].getDwgSurfPos();
                *count = 2;
            }*/
        }
    }

}

void vkeydownSelect(csARGS Args)
{
    bool cntState = *(bool*)Args[22];
    if(cntState)
    {
        HDC* dcs0=(HDC*)Args[0];
        HDC* dcs3=(HDC*)Args[3];
        COLORREF* color0=(COLORREF*)Args[4];
        COLORREF* color3=(COLORREF*)Args[7];
        COLORREF* bkgcol0=(COLORREF*)Args[8];
        COLORREF* bkgcol3=(COLORREF*)Args[11];

        int id = (int)Args;
        int *count = (int*)Args[24];
        int *countControl = (int*)Args[25];

        int* lastMouseOverid = (int*)Args[18];
        int* lastMouseClickid = (int*)Args[19];
        int n = *(int*)Args[20];
        int* smoothRepos = (int*)Args[32];
        int width = *(int*)Args[31];
        int* smoothReposCount = (int*)Args[33];

        WPARAM wp = WPARAM(Args);
        if(n > 0)
        {
            if(wp == VK_UP && *lastMouseClickid > 0 && *lastMouseClickid < n)
            {
                int id  = *lastMouseClickid-1;
                color0[id] = color3[id];
                bkgcol0[id] = bkgcol3[id];
                dcs0[id] = dcs3[id];
                *lastMouseOverid = id;
                *smoothReposCount = 1;
                SendMessage(HWND(Args), WM_LBUTTONDOWN, 0,0);
                SendMessage(HWND(Args), WM_LBUTTONUP, 0,0);
            }
            else if(wp == VK_DOWN && *lastMouseClickid+1 < n)
            {
                int id  = *lastMouseClickid+1;
                color0[id] = color3[id];
                bkgcol0[id] = bkgcol3[id];
                dcs0[id] = dcs3[id];
                *lastMouseOverid = id;
                *smoothReposCount = 1;
                SendMessage(HWND(Args), WM_LBUTTONDOWN, 0,0);
                SendMessage(HWND(Args), WM_LBUTTONUP, 0,0);
            }
            else if(wp == VK_LEFT && *lastMouseClickid-n/width >= 0)
            {
                int id  = *lastMouseClickid-n/width;
                color0[id] = color3[id];
                bkgcol0[id] = bkgcol3[id];
                dcs0[id] = dcs3[id];
                *lastMouseOverid = id;
                *smoothReposCount = 1;
                SendMessage(HWND(Args), WM_LBUTTONDOWN, 0,0);
            }
            else if(wp == VK_RIGHT && *lastMouseClickid+n/width < n)
            {
                int id  = *lastMouseClickid+n/width;
                color0[id] = color3[id];
                bkgcol0[id] = bkgcol3[id];
                dcs0[id] = dcs3[id];
                *lastMouseOverid = id;
                *smoothReposCount = 1;
                SendMessage(HWND(Args), WM_LBUTTONDOWN, 0,0);
            }
        }
    }
}

void startCutPaste(csARGS Args)
{
    //bool cntState = *(bool*)Args[22];
    //if(cntState)
    {
        
        if((int*)Args[34])
        {
            
            bool*cutPasteStart = (bool*)Args[35];
            //int cutPasteViewer = *(int*)Args[34];
            bool*cutPasteDone0 = (bool*)Args[37];

            *cutPasteStart = 1;
            *cutPasteDone0 = 0;
        }
    }
}

void endCutPaste(csARGS Args)
{
    bool cntState = *(bool*)Args[22];
    if(cntState)
    {
        
        if((int*)Args[34])
        {
            bool*cutPasteStart = (bool*)Args[35];
            bool*cutPasteDone = (bool*)Args[36];
            bool*cutPasteDone0 = (bool*)Args[37];
            int cutPasteViewer = *(int*)Args[34];
    //std::cout<<"6656456\n";
            cv.cp[cutPasteViewer]->Show = 0;
            *cutPasteStart = 0;

            if(*cutPasteDone0)
            {
                *cutPasteDone0 = 0;
                *cutPasteDone = 1;
            }
            /*int* lastMouseOverid = (int*)Args[18];
            std::cout<<"lastMouseOverid : "<<*lastMouseOverid<<" --\n";*/

        }
    }
}

void makeCutPaste(csARGS Args)
{
    //bool cntState = *(bool*)Args[22];
    //if(cntState)
    {
        static bool a = 0;
        int n = *(int*)Args[20];
        if((int*)Args[34] && n)
        {
            a = 0;
            int* copyPasteKeyDownState = (int*)Args[38];
            if(GetAsyncKeyState(VK_LSHIFT))
            {
                *copyPasteKeyDownState = VK_LSHIFT;
                a = 1;
            }
            else if(GetAsyncKeyState(VK_LBUTTON))
            {
                *copyPasteKeyDownState = VK_LBUTTON;
                a = 1;
            }

            if(a)
            {
                bool*cutPasteStart = (bool*)Args[35];
                int cutPasteViewer = *(int*)Args[34];

                if(*cutPasteStart)
                {
                    bool*cutPasteDone0 = (bool*)Args[37];
                    cv.cp[cutPasteViewer]->Show = 1;
                    int* lastMouseClickid = (int*)Args[19];
                    RECT pos=((RECT*)Args[12])[*lastMouseClickid];
                    POINT p = cv.TRACKING_POINT;
                    
                    MoveWindow(cv.CNTLIST[cutPasteViewer],p.x+20,p.y+20, pos.right-pos.left, pos.bottom-pos.top,1);
                    GetClientRect(cv.CNTLIST[cutPasteViewer], &cv.CNTCLWRECT[cutPasteViewer]);

                    HDC* dcs3=(HDC*)Args[3];
                    COLORREF* color3=(COLORREF*)Args[7];
                    COLORREF* bkgcol3=(COLORREF*)Args[11];

                    POINT* posImg=(POINT*)Args[13];
                    POINT* posTitle=(POINT*)Args[14];
                    HFONT* font=(HFONT*)Args[15];
                    char** title=(char**)Args[16];
                    SIZE imgSize = *(SIZE*)Args[17];

                    RECT r = cv.CNTCLWRECT[int(Args)];

                    int i = *lastMouseClickid;
                    HDC dc = cv.CTX[cutPasteViewer].getDC();
                    SetBkMode(dc,TRANSPARENT);
                    SelectFont(dc, font[i]);
                    SetTextColor(dc, color3[i]);
                    csDrawGDIRectangle(dc,bkgcol3[i],bkgcol3[i],1,{0,0,pos.right-pos.left, pos.bottom-pos.top});
                    TextOut(dc,posTitle[i].x-posImg[i].x,(r.bottom-imgSize.cy)/2,(LPCSTR)title[i],strlen(title[i]));
                    BitBlt(dc,1,(r.bottom-imgSize.cy)/2,imgSize.cx,imgSize.cy, dcs3[i],0,0,SRCCOPY);
                    InvalidateRect(cv.CNTLIST[cutPasteViewer],0,1);
                    *cutPasteStart = 0;
                    *cutPasteDone0 = 1;
                }
                //std::cout<<"lastMouseOverid : "<<*lastMouseOverid<<"\n";
                POINT p;
                GetCursorPos(&p);
                SetWindowPos(cv.CNTLIST[cutPasteViewer],0,p.x+20,p.y+20, 0,0,SWP_NOSIZE);
            }
        }
    }
}

void vkeydownSrcoll_timer(csARGS Args)
{
    /*int id = (int)Args;
    int *count = (int*)Args[19];
    int *countControl = (int*)Args[20];
//effectuer un double press de la touche 'controle'
    if(*count==1)
    {*countControl = *countControl + 1;}
    if(*countControl >= 50)
    {
        countControl = 0;
        if(*count == 1) // si on n'a pas appuye une seconde fois dans le timing
            *count = 0;
    }*/
}


void vkeyupScroll(csARGS Args)
{
    int id = (int)Args;
    int *count = (int*)Args[24];
    int *countControl = (int*)Args[25];

    /*if(*count == 2 || *countControl>50)
    {
        *count = 0;
        *countControl=0;
    }*/
    //*count = 0;
}

//------------------------------------------------------------------
