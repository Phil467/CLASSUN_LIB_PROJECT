#include "csBUTTONGRID.h"
#include <iostream>

#define CS_RDBTN_TEXT_BEFORE  1
#define CS_RDBTN_TEXT_AFTER  2
#define CS_RDBTN_TEXT_OVER  3
#define CS_RDBTN_TEXT_UNDER  4

extern csCNTR_VARS cv;
extern csCNTR_PARAMS cscp;

void mouseMouve_update(csARGS Args);
void mouseLeave_update(csARGS Args);
void mouseLbtndown_update(csARGS Args);
void mouseLbtnup_update(csARGS Args);

csBUTTONGRID::csBUTTONGRID(int _idp, csBGRID_PARAMS bgpar, int _nItemWidth, bool newCnt)
{
    if(bgpar.nx!=0 && bgpar.ny!=0 && bgpar.dx!=0 && bgpar.dy!=0)
        init(_idp, bgpar, _nItemWidth, newCnt);
}

void csBUTTONGRID::init(int _idp, csBGRID_PARAMS bgpar, int _nItemWidth, bool newCnt)
{
    map.init(1);
    items.init(1);
    itemRect.init(1);
    textRect.init(1);
    iconRect.init(1);
    itemTitle.init(1);
    iconDC.init(1);
    titleCol.init(1);
    bkgCol.init(1);
    brdCol.init(1);
    titleFont.init(1);
    finalDC.init(1);
    enable.init(1);
    itemState.init(1);
    showITitle.init(1);
    type.init(1);

    bgp=0;
    id=0;
    idp=0;
    size=0;
    currentId=0;
    lastId=0;
    activedId=0;
    nsz=0;
    xtotalLen=0;
    ytotalLen=0;
    click_message=0;

    defFont = CreateFontA(csGetAdjustedFontSizeX(12),0,0, 0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                          OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                          DEFAULT_PITCH|FF_SWISS, (LPCSTR)"Calibri");
    defFont0 = CreateFontA(csGetAdjustedFontSizeX(13),0,0, 0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                          OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                          DEFAULT_PITCH|FF_SWISS, (LPCSTR)"Calibri");
    textPos = CS_RDBTN_TEXT_UNDER;
    xmarg = 1, ymarg = 1; xmarg_text = 1; ymarg_text=1;
    xoffset = 0; yoffset = 0;
    nItemWidth = _nItemWidth;
    id=0; idp=0; size = 0; bgp=0;currentId=0;lastId=0;activedId=0; nsz=0;
    
    id = csf_alloc<int>(1);
    idp = csf_alloc2<int>(1, _idp);
    size = csf_alloc2<SIZE>(1, {bgpar.dx*bgpar.nx, bgpar.dy*bgpar.ny});
    bgp = csf_alloc2<csBGRID_PARAMS>(1,bgpar);
    currentId = csf_alloc2<int>(1,-1);
    lastId = csf_alloc2<int>(1,-1);
    activedId = csf_alloc2<int>(1,0);
    nsz = csf_alloc2<unsigned>(1,0);
    xtotalLen = csf_alloc2<int>(1,0);
    ytotalLen = csf_alloc2<int>(1,0);
    click_message = csf_alloc2<bool>(1,0);

    size->cx = bgpar.dx*bgpar.nx;
    size->cy = bgpar.dy*bgpar.ny;

    bgp->dx = bgpar.dx;
    bgp->dy = bgpar.dy;
    bgp->nx = bgpar.nx;
    bgp->ny = bgpar.ny;

    defBkgCol1 = RGB(30,30,30);
    //defBkgCol1 = RGB(40,30,40);
    //defBkgCol1 = RGB(0,0,0);
    defBkgCol2 = RGB(70,70,70);
    defBkgCol3 = RGB(220,220,220);
    defBkgCol4 = RGB(30,30,30);

    defTextCol1 = RGB(250,250,250);
    defTextCol2 = RGB(255,255,255);
    defTextCol3 = RGB(10,10,10);
    defTextCol4 = RGB(50,50,50);

    defBrdCol1 = RGB(35,35,35);
    defBrdCol2 = RGB(40,40,40);
    defBrdCol3 = RGB(80,80,80);
    defBrdCol4 = RGB(35,35,35);

    defShowTitle = 1;

    if(newCnt)
        *id = staticCnt2(cscp, _idp, "", {30,30,30},{0,0,size->cx, size->cy},1);
    else
        *id = _idp;

        //std::cout<<bgp->ny<<" ny\n";
    for(int j=0; j<bgp->ny; j++)
    {
        csLIST<int> X;
        //std::cout<<j<<" before \n";
        X.full(bgp->nx, -1);
        //std::cout<<j<<" during \n";
        map.insertEnd(X);
        //std::cout<<j<<" after \n";
    }

    //void mouseMouve_update(csARGS Args);
    //void mouseLeave_update(csARGS Args);
    //void mouseLbtndown_update(csARGS Args);
    //void mouseLbtnup_update(csARGS Args);

    args.setArgNumber(12);
    args.makeArgs(finalDC.getTable(), finalDC.sizePtr(), 
    activedId, lastId, currentId, bgp, map.getTable(), itemRect.getTable(), 
    enable.getTable(), itemState.getTable(), type.getTable(), click_message);
    csSetAction(*id, WM_MOUSEMOVE, mouseMouve_update, args);
    csSetAction(*id, WM_MOUSELEAVE, mouseLeave_update, args);
    csSetAction(*id, WM_LBUTTONDOWN, mouseLbtndown_update, args);
    csSetAction(*id, WM_LBUTTONUP, mouseLbtnup_update, args);
    //csSetAction(ids[14], WM_LBUTTONUP, rltDraw_newPolygonBtn, args);

    getUsefulEventsNumber();
}

POINT csBUTTONGRID::getNextPosition()
{
    POINT p = {0};
    //int nx = bgp->nx - xmarg, ii=0;
    //int ny = bgp->ny - ymarg;
    bool b = 0;
    if(itemRect.size()==0)
        p = {xmarg, ymarg};
    else
    {
        RECT r = itemRect[itemRect.size()-1];
        if(itemRect.size()%nItemWidth != 0)
            //p = {(r.left+r.right)/bgp->dx+xmarg-xoffset, r.top/bgp->dy};
            p = {(r.left+r.right-xmarg)/bgp->dx + xoffset, r.top/bgp->dy};
        else
            //p = {xmarg, (r.top+r.bottom)/bgp->dy-yoffset + ymarg};
            p = {xmarg, (r.top+r.bottom-ymarg)/bgp->dy + yoffset};
        
        // for(int j=ymarg; j<ny; j++)
        // {
        //     for(int i=xmarg; i<nx; i++)
        //     {
        //         if(map[j][i]==-1)
        //         {
        //             if(map[j+2*ymarg][i+2*xmarg] == -1)
        //             {
        //                 p = {i+xmarg,j+ymarg};
        //                 b=1;
        //                 break;
        //             }
        //         }
        //     }
        //     if(b)
        //         break;
        // }
    }
    return p;

}

int csBUTTONGRID::getItemNumber()
{
    return itemTitle.size();
}
char* csBUTTONGRID::getTitle(int id)
{
    return itemTitle[id];
}

void csBUTTONGRID::setItemIcon(int i, char*icon1, char*icon2, char*icon3, char*icon4)
{
    SIZE iconSize = {iconRect[i].right, iconRect[i].bottom};
    char* _ico1 = icon1;
    char* _ico2 = (icon2 != 0)?icon2:icon1;
    char* _ico3 = (icon3 != 0)?icon3:icon1;
    char* _ico4 = (icon4 != 0)?icon4:icon1;
    HDC dc1 = csLoadImage(_ico1, {iconSize.cx, iconSize.cy});
    HDC dc2 = csLoadImage(_ico2, {iconSize.cx, iconSize.cy});
    HDC dc3 = csLoadImage(_ico3, {iconSize.cx, iconSize.cy});
    HDC dc4 = csLoadImage(_ico4, {iconSize.cx, iconSize.cy});

    DeleteDC(iconDC[i][0]);
    iconDC[i][0] = dc1;
    DeleteDC(iconDC[i][1]);
    iconDC[i][1] = dc2;
    DeleteDC(iconDC[i][2]);
    iconDC[i][2] = dc3;
    DeleteDC(iconDC[i][3]);
    iconDC[i][3] = dc4;
}

RECT csBUTTONGRID::newBItem(POINT pos, SIZE iconSize, char*title,
                    char*icon1, char*icon2, char*icon3, char*icon4, bool _enable, SIZE itemSize)
{
    char* _ico1 = icon1;
    char* _ico2 = (icon2 != 0)?icon2:icon1;
    char* _ico3 = (icon3 != 0)?icon3:icon1;
    char* _ico4 = (icon4 != 0)?icon4:icon1;
    LPSIZE sz = csTextExtent(*id, defFont0,title);
    sz->cx = (long)ceil(double(sz->cx)/bgp->dx)*bgp->dx;
    sz->cy = (long)ceil(double(sz->cy)/bgp->dy)*bgp->dy;

    if(defShowTitle == 0)
    {
        *sz={0,0};
    }

    RECT r;
    POINT pt = pos;
    if(pos.x==-1 || pos.y==-1)
    {
        POINT p = getNextPosition();
        if(pt.x == -1)
            pt.x = p.x;
        if(pt.y==-1)
            pt.y = p.y;
    }
    //pt.x -= xmarg_text;
    //pt.y -= ymarg_text;
    //if(r.left+r.right<bgp->nx && r.top+r.bottom<bgp->ny)
    //iconSizeInput.insertEnd(iconSize);
    itemTitle.insertEnd(title);
    enable.insertEnd(_enable);
    itemState.insertEnd(0);
    showITitle.insertEnd(defShowTitle);
    type.insertEnd(CS_BGRD_GROUP_SELECTION);
    titleCol.insertEnd(csNewList<COLORREF>());
    bkgCol.insertEnd(csNewList<COLORREF>());
    brdCol.insertEnd(csNewList<COLORREF>());
    int i = titleCol.size()-1;
    titleCol[i].insertEnd(defTextCol1);
    titleCol[i].insertEnd(defTextCol2);
    titleCol[i].insertEnd(defTextCol3);
    titleCol[i].insertEnd(defTextCol4);
    bkgCol[i].insertEnd(defBkgCol1);
    bkgCol[i].insertEnd(defBkgCol2);
    bkgCol[i].insertEnd(defBkgCol3);
    bkgCol[i].insertEnd(defBkgCol4);
    brdCol[i].insertEnd(defBrdCol1);
    brdCol[i].insertEnd(defBrdCol2);
    brdCol[i].insertEnd(defBrdCol3);
    brdCol[i].insertEnd(defBrdCol4);
    int d = 0;
    int icoLen = (iconSize.cx-2*xmarg_text)*bgp->dx;
    int icoHeigh = (iconSize.cy-2*ymarg_text)*bgp->dy;
    SIZE retIcoSz={icoLen, icoHeigh};
    HDC dc1 = csLoadImage(_ico1, {icoLen, icoHeigh},&retIcoSz);
    HDC dc2 = csLoadImage(_ico2, {icoLen, icoHeigh});
    HDC dc3 = csLoadImage(_ico3, {icoLen, icoHeigh});
    HDC dc4 = csLoadImage(_ico4, {icoLen, icoHeigh});

    int margx = xmarg_text*bgp->dx;
    int margy = ymarg_text*bgp->dy;

    if(textPos == CS_RDBTN_TEXT_OVER || textPos == CS_RDBTN_TEXT_UNDER)
    {
        if(itemSize.cx && itemSize.cy)
        r = {(pt.x)*bgp->dx+xmarg, (pt.y)*bgp->dy+ymarg, itemSize.cx*bgp->dx, itemSize.cy*bgp->dy};
        else
        r = {(pt.x)*bgp->dx+xmarg, (pt.y)*bgp->dy+ymarg, std::max(retIcoSz.cx,sz->cx) + 2*margx, 
        retIcoSz.cy + margy + sz->cy};
    }
    else if(textPos == CS_RDBTN_TEXT_BEFORE || textPos == CS_RDBTN_TEXT_AFTER)
    {
        if(itemSize.cx && itemSize.cy)
        r = {pt.x*bgp->dx+xmarg, pt.y*bgp->dy+ymarg, itemSize.cx*bgp->dx, itemSize.cy*bgp->dy};
        else
        r = {(pt.x)*bgp->dx+xmarg, (pt.y)*bgp->dy+ymarg, std::max(retIcoSz.cx,sz->cx) + 2*margx, 
        retIcoSz.cy + margy + sz->cy};
    }

    itemRect.insertEnd(r);
    
    iconDC.insertEnd(csNewList<HDC>());
    iconDC[i].insertEnd(dc1);
    iconDC[i].insertEnd(dc2);
    iconDC[i].insertEnd(dc3);
    iconDC[i].insertEnd(dc4);
    titleFont.insertEnd(defFont);

    csDC fdc1 = csNewDC({r.right, r.bottom});
    DeleteBitmap(fdc1.hbmp);
    csDC fdc2 = csNewDC({r.right, r.bottom});
    DeleteBitmap(fdc2.hbmp);
    csDC fdc3 = csNewDC({r.right, r.bottom});
    DeleteBitmap(fdc3.hbmp);
    csDC fdc4 = csNewDC({r.right, r.bottom});
    DeleteBitmap(fdc4.hbmp);
    finalDC.insertEnd(csNewList<HDC>());
    finalDC[i].insertEnd(fdc1.dc);
    finalDC[i].insertEnd(fdc2.dc);
    finalDC[i].insertEnd(fdc3.dc);
    finalDC[i].insertEnd(fdc4.dc);

    int l1 = ceil(double(r.top+r.bottom)/bgp->dy);
    int l2 = ceil(double(r.left+r.right)/bgp->dx);
    for(int j=pt.y; j<l1; j++)
    {
        if(j>=0 && j<bgp->ny)
        for(int k=pt.x; k<l2; k++)
        {
            if(k>=0 && k<bgp->nx)
            {
                map[j][k] = i;
            }
        }
    }

    
    if(textPos == CS_RDBTN_TEXT_UNDER)
    {
        int x = r.left +(r.right - retIcoSz.cx)/2;
        int y = r.top + margy;
        iconRect.insertEnd({x, y, retIcoSz.cx, retIcoSz.cy});

        LPSIZE sz1 = csTextExtent(*id, defFont,title);
        RECT rr;

        int d = (retIcoSz.cy)?margy:0;
        rr.left = r.left +(r.right - sz1->cx)/2;
        rr.top = r.top + d + retIcoSz.cy + (sz->cy - sz1->cy)/2;
        rr.right = sz->cx;
        rr.bottom = sz->cy;

        textRect.insertEnd(rr);
        free(sz1);
    }
    else if(textPos == CS_RDBTN_TEXT_AFTER)
    {
        int x = margx + r.left;
        int y = r.top + margy;
        iconRect.insertEnd({x, y, retIcoSz.cx, retIcoSz.cy});
        x = r.left + 2*margx + retIcoSz.cx;
        textRect.insertEnd({x, r.top + (r.bottom-sz->cy)/2, sz->cx, sz->cy});

    }

    if(r.left+r.right > *xtotalLen)
        *xtotalLen = r.left+r.right;
    if(r.top+r.bottom > *ytotalLen)
        *ytotalLen = r.top+r.bottom;
    
    free(sz);
    
    return itemRect[i];
    
    /*else
    {
        std::cout<< "Invalid BItem size !\n";
        return {0};
    }*/

}

void csBUTTONGRID::setXRect_model01(int cx, int height)
{
    int n = nItemWidth*height;
    for(int i=0; i<n; i+=nItemWidth)
    {
        textRect[i].right+=cx;
        itemRect[i].right+=cx;

        int l1 = ceil(double(itemRect[i].top+itemRect[i].bottom)/bgp->dy);
        int l2 = ceil(double(itemRect[i].left+itemRect[i].right)/bgp->dx);
        int px = (itemRect[i].left-xmarg)/bgp->dx;
        int py = (itemRect[i].top-ymarg)/bgp->dy;
        for(int j=py; j<l1; j++)
        {
            if(j>=0 && j<bgp->ny)
            for(int k=px; k<l2; k++)
            {
                if(k>=0 && k<bgp->nx)
                {
                    map[j][k] = i;
                }
            }
        }

        int k = i+nItemWidth;
        for(int j=i+1;j<k;j++)
        {
            textRect[j].left+=cx;
            iconRect[j].left+=cx;
            itemRect[j].left+=cx;

            int l1 = ceil(double(itemRect[j].top+itemRect[j].bottom)/bgp->dy);
            int l2 = ceil(double(itemRect[j].left+itemRect[j].right)/bgp->dx);
            int px = (itemRect[j].left-xmarg)/bgp->dx;
            int py = (itemRect[j].top-ymarg)/bgp->dy;
            for(int m=py; m<l1; m++)
            {
                if(m>=0 && m<bgp->ny)
                for(int o=px; o<l2; o++)
                {
                    if(o>=0 && o<bgp->nx)
                    {
                        map[m][o] = j;
                    }
                }
            }
        }
    }
    //create();
}

void csBUTTONGRID::setFont(char*font, SIZE fsize)
{
    if(defFont)
    {
        DeleteFont(defFont);
        DeleteFont(defFont0);
    }
    //else
    {
        defFont = CreateFontA(csGetAdjustedFontSizeX(fsize.cx),csGetAdjustedFontSizeY(fsize.cy),
                            0, 0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                          DEFAULT_PITCH|FF_SWISS, (LPCSTR)font);
        if(fsize.cy == 0)
            defFont0 = CreateFontA(csGetAdjustedFontSizeX(fsize.cx+1),0,0, 0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                          OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                          DEFAULT_PITCH|FF_SWISS, (LPCSTR)font);
        else
            defFont0 = CreateFontA(csGetAdjustedFontSizeX(fsize.cx+1),csGetAdjustedFontSizeY(fsize.cy+1),
                                0, 0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                                OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                          DEFAULT_PITCH|FF_SWISS, (LPCSTR)font);
    }
}


int csBUTTONGRID::makeNTemplate(char*defName, char*iconPath, SIZE unitSz, int n, SIZE itemSize)
{
    int N = nItemWidth*n;
    if(itemRect.size()==0)
    {
        char*str=csf_alloc<char>(20);
        sprintf(str,"%s 0 ", defName);
        newBItem({0,0}, unitSz, str,iconPath, 0,0,0, 1,itemSize);
    }

    for(int i=1; i<N; i++)
    {
        char*str=csf_alloc<char>(20);
        sprintf(str,"%s %d ", defName,i);
        newBItem({-1,-1}, unitSz, str,iconPath, 0,0,0, 1,itemSize);
    }
}
int csBUTTONGRID::makeNBItems(char**names, char**iconPaths, SIZE unitSz)
{
    int N = nItemWidth;
    int ii = 0;
    if(itemRect.size()==0)
    {
        newBItem({0,0}, unitSz, names[0],iconPaths[0], 0,0,0, 1);
        ii++;
    }

    for(int i=ii; i<N; i++)
    {
        newBItem({-1,-1}, unitSz, names[i],iconPaths[i], 0,0,0, 1);
    }
}

int csBUTTONGRID::makeNCopy(char**name, char**iconPath1, char**iconPath2, char**iconPath3, char**iconPath4, 
SIZE* iconSize, int n_copy, int _ymarg)
{
    int n = sizeof(iconSize)/sizeof(iconSize[0]);
    int m = std::min(n,itemRect.size());
    for(int i=0; i<n_copy; i++)
    {
        for(int j=0; j<m; j++)
        {
            newBItem({(itemRect[j].left-xmarg)/bgp->dx,(itemRect[j].top-ymarg)/bgp->dy+i*_ymarg*bgp->dy}, iconSize[j], 
                     name[j],iconPath1[i],iconPath2[i],iconPath3[i],iconPath4[i], 1);
        }
    }
}


int csBUTTONGRID::getTolalWidth()
{
    int len = 0, t=0;
    for(int i=0; i<itemRect.size(); i++)
    {
        t = itemRect[i].left+itemRect[i].right;
        if(t>len)
            len = t;
    }
    return len;
}

int csBUTTONGRID::getXLength()
{
    return *xtotalLen;
}

int csBUTTONGRID::getYLength()
{
    return *ytotalLen;
}

void csBUTTONGRID::setTitleColors(COLORREF c1, COLORREF c2, COLORREF c3, COLORREF c4)
{
    defTextCol1 = c1;
    defTextCol2 = c2;
    defTextCol3 = c3;
    defTextCol4 = c4;
}

void csBUTTONGRID::setBItemBackgroundColors(COLORREF c1, COLORREF c2, COLORREF c3, COLORREF c4)
{
    defBkgCol1 = c1;
    defBkgCol2 = c2;
    defBkgCol3 = c3;
    defBkgCol4 = c4;
}
void csBUTTONGRID::setBItemBordersColors(COLORREF c1, COLORREF c2, COLORREF c3, COLORREF c4)
{
    defBrdCol1 = c1;
    defBrdCol2 = c2;
    defBrdCol3 = c3;
    defBkgCol4 = c4;
}

void csBUTTONGRID::setMouseHoverBackground(COLORREF c)
{
    defBkgCol2 = c;
}

void csBUTTONGRID::setTextPosition(int tpos)
{
    textPos = tpos;
}

void csBUTTONGRID::setTextMarging(int x, int y)
{
    xmarg_text = x;
    ymarg_text = y;
}
void csBUTTONGRID::setOffset(int xoff, int yoff)
{
    xoffset = xoff;
    yoffset = yoff;
}

void csBUTTONGRID::setMarging(int _xmarg, int _ymarg)
{
    xmarg = _xmarg;
    ymarg = _ymarg;
}

void csBUTTONGRID::showTitle(bool show)
{
    defShowTitle = show;
}

void csBUTTONGRID::setItemTitle(int id, char*title)
{
    free(itemTitle[id]);
    itemTitle[id] = title;

}

int csBUTTONGRID::findId(POINT p)
{
    int i = p.x/bgp->dx;
    int j = p.y/bgp->dy;
    
    return map[j][i];
}


int csBUTTONGRID::getId()
{
    return *id;
}

csCNTR_PARAMS *csBUTTONGRID::getParams()
{
    return cv.cp[*id];
}

RECT* csBUTTONGRID::getItemRect(int i)
{
    return &itemRect[i];
}
bool* csBUTTONGRID::getItemState(int i)
{
    return &itemState[i];
}

void csBUTTONGRID::createItem(int iItem)
{
    int i =iItem;
    RECT r = itemRect[i];
    RECT ri = iconRect[i];
    RECT rt = textRect[i];
    HFONT hf = titleFont[i];
    
    for(int j = 0; j<4; j++)
    {
        DeleteDC(finalDC[i][j]);
        csDC dc = csNewDC({r.right,r.bottom});
        
        HBRUSH hb = CreateSolidBrush(bkgCol[i][j]);
        HPEN hp = CreatePen(0,1,brdCol[i][j]);
        SelectBrush(dc.dc, hb);
        SelectPen(dc.dc, hp);
        Rectangle(dc.dc,0,0,r.right,r.bottom);
        DeleteBrush(hb);
        DeletePalette(hp);

        BitBlt(dc.dc, ri.left-r.left, ri.top-r.top, ri.right, ri.bottom, 
        iconDC[i][j],0,0,SRCCOPY);

        if(showITitle[i])
        {
            SetBkMode(dc.dc, TRANSPARENT);
            SetTextColor(dc.dc, titleCol[i][j]);
            SelectFont(dc.dc, titleFont[i]);
            TextOutA(dc.dc, rt.left-r.left, rt.top-r.top, (LPCSTR)itemTitle[i], strlen(itemTitle[i]));
        }
        finalDC[i][j] = dc.dc;
        DeleteBitmap(dc.hbmp);
    }
}

void csBUTTONGRID::updateItem(int i)
{
    createItem(i);
    setItemState(i, itemState[i]);
}

void csBUTTONGRID::setItemState(int i, bool _state)
{
    if(i<itemState.size() && enable[i])
    {
        itemState[i] = _state;
        HDC dc = cv.CTX[*id].getDC();
        RECT r = itemRect[i];
        //POINT pdc = cv.CTX[*id].getDwgSurfPos();
        POINT pdc = {0};
        if(_state)
        {
            BitBlt(dc, r.left+pdc.x, r.top+pdc.y, r.right, r.bottom, 
            finalDC[i][2],0,0,SRCCOPY);
        }
        else
        {
            BitBlt(dc, r.left+pdc.x, r.top+pdc.y, r.right, r.bottom, 
            finalDC[i][0],0,0,SRCCOPY);
        }
    }
}

void csBUTTONGRID::enableItem(int i, bool _enable)
{
    if(i<itemState.size())
    {
        
        HDC dc = cv.CTX[*id].getDC();
        RECT r = itemRect[i];
        //POINT pdc = cv.CTX[*id].getDwgSurfPos();
        POINT pdc = {0};
        if(_enable)
        {
            BitBlt(dc, r.left+pdc.x, r.top+pdc.y, r.right, r.bottom, 
            finalDC[i][0],0,0,SRCCOPY);
        }
        else
        {
            BitBlt(dc, r.left+pdc.x, r.top+pdc.y, r.right, r.bottom, 
            finalDC[i][3],0,0,SRCCOPY);
        }
    }
}

void csBUTTONGRID::setActiveItem(int i)
{
    if(itemTitle.size()>i)
    {
        //*lastId = *activedId;
        *currentId = i;
        //args.setArg(3,(void*)lastId);
        args.setArg(4,(void*)currentId);
        args.setId((void*)id);
        HWND h = cv.CNTLIST[*id];
        args.setHwnd((void*)&h);
        mouseLbtnup_update(args);
    }
}

int csBUTTONGRID::getActiveItem()
{
    return *activedId;
}

void csBUTTONGRID::setItemType(int i, short _type)
{
    if(itemTitle.size()>i)
    {
        type[i] = _type;
    }
}

void csBUTTONGRID::create()
{
    HDC dc = cv.CTX[*id].getDC();
    SetBkMode(dc, TRANSPARENT);
    
    int n = titleCol.size();
    RECT r;
    for(int i=0; i<n; i++)
    {
        createItem(i);
        r = itemRect[i];
        //POINT pdc = cv.CTX[*id].getDwgSurfPos();
        POINT pdc = {0};
        if(enable[i])
        {
            if(*activedId == i)
                BitBlt(dc, r.left+pdc.x, r.top+pdc.y, r.right, r.bottom, 
                finalDC[i][2],0,0,SRCCOPY);
            else
                BitBlt(dc, r.left+pdc.x, r.top+pdc.y, r.right, r.bottom, 
                finalDC[i][0],0,0,SRCCOPY);
        }
        else
        {
            if(*activedId == i)
            {
                BitBlt(dc, r.left+pdc.x, r.top+pdc.y, r.right, r.bottom, 
                finalDC[i][2],0,0,SRCCOPY);
                enable[i]=1;
            }
            else
            {
                BitBlt(dc, r.left+pdc.x, r.top+pdc.y, r.right, r.bottom, 
                finalDC[i][3],0,0,SRCCOPY);
            }
        }
    }

    //bgp->nx = ceil(double(*xtotalLen)/bgp->dx);
    //bgp->ny = ceil(double(*ytotalLen)/bgp->dy);
    //SetWindowPos(cv.CNTLIST[*id], 0, 0,0, *xtotalLen, *ytotalLen, SWP_NOMOVE);
    
    if(args.getArgNumber())
        args.freeArgs();
    args.setArgNumber(12);
    *nsz = finalDC.size();
    args.makeArgs(finalDC.getTable(), finalDC.sizePtr(), 
    activedId, lastId, currentId, bgp, map.getTable(), itemRect.getTable(), 
    enable.getTable(), itemState.getTable(), type.getTable(), click_message);

    cv.cp[*id]->CntEventsFunc.MOUSEMOVE_ARGS[moveMsgPos] = args;
    cv.cp[*id]->CntEventsFunc.MOUSELEAVE_ARGS[leaveMsgPos] = args;
    cv.cp[*id]->CntEventsFunc.LBUTTONDOWN_ARGS[lbtnDownMsgPos] = args;
    cv.cp[*id]->CntEventsFunc.LBUTTONUP_ARGS[lbtnUpMsgPos] = args;
    InvalidateRect(cv.CNTLIST[*id], 0 ,1);
}

void csBUTTONGRID::getUsefulEventsNumber()
{
    moveMsgPos = cv.cp[*id]->CntEventsFunc.MOUSEMOVE_ARGS.size()-1;
    lbtnDownMsgPos = cv.cp[*id]->CntEventsFunc.LBUTTONDOWN_ARGS.size()-1;
    lbtnUpMsgPos = cv.cp[*id]->CntEventsFunc.LBUTTONUP_ARGS.size()-1;
    leaveMsgPos = cv.cp[*id]->CntEventsFunc.MOUSELEAVE_ARGS.size()-1;
    timerMsgPos = cv.cp[*id]->CntEventsFunc.TIMER_ARGS.size()-1;
    keyDownMsgPos = cv.cp[*id]->CntEventsFunc.KEYDOWN_ARGS.size()-1;
    keyUpMsgPos = cv.cp[*id]->CntEventsFunc.KEYUP_ARGS.size()-1;
}

csBUTTONGRID::~csBUTTONGRID()
{
    //dtor
}

void mouseMouve_update(csARGS Args)
{
    int id = int(Args);
    csLIST<HDC>* finalDC = (csLIST<HDC>*)Args[0];
    unsigned n = *(unsigned*)Args[1];
    int*activedId = (int*)Args[2];
    int*lastId = (int*)Args[3];
    int*currentId = (int*)Args[4];

    csBGRID_PARAMS* bgp = (csBGRID_PARAMS*)Args[5];
    csLIST<int>* map = (csLIST<int>*)Args[6];
    RECT*r = (RECT*)Args[7];
    bool*enable = (bool*)Args[8];
    bool*state = (bool*)Args[9];
    short*type = (short*)Args[10];

    POINT p={0};
    GetCursorPos(&p);
    ScreenToClient((HWND)Args, &p);
    POINT pdc = cv.CTX[id].getDwgSurfPos();
    int i = (p.x-pdc.x)/bgp->dx;
    int j = (p.y-pdc.y)/bgp->dy;
    //std::cout<<-p.x+bgp->nx*bgp->dx<<" "<<-p.y+bgp->ny*bgp->dy<<"\n\n";
    
    if(i>=0 && i < bgp->nx && j>=0 && j < bgp->ny)
    {
        HDC dc = cv.CTX[id].getDC();
        *currentId = map[j][i];
        if(*currentId != -1)
        {
            if(enable[*currentId])
            {
                //std::cout<<"init ... ";
                if(*currentId != -1 && *currentId != *lastId && *currentId != *activedId)
                {
                    RECT rc = r[*currentId];
                    if(type[*currentId] == CS_BGRD_GROUP_SELECTION || type[*currentId] == CS_BGRD_UNI_SELECTION
                        || (type[*currentId] == CS_BGRD_BI_SELECTION && 
                        state[*currentId] == 0))
                    {
                        BitBlt(dc, rc.left, rc.top, rc.right, rc.bottom, 
                        finalDC[*currentId][1],0,0,SRCCOPY);
                        RECT rr = {rc.left,rc.top,rc.right+rc.left,rc.top+rc.bottom};
                        InvalidateRect((HWND)Args,&rr,1);
                    }
                }
                if(*lastId != -1 && *lastId != *currentId && *lastId != *activedId
                    && (type[*lastId] == CS_BGRD_GROUP_SELECTION || type[*lastId] == CS_BGRD_UNI_SELECTION || 
                    (type[*lastId] == CS_BGRD_BI_SELECTION && state[*lastId] == 0)))
                {
                    RECT rc = r[*lastId];
                    BitBlt(dc, rc.left, rc.top, rc.right, rc.bottom, 
                    finalDC[*lastId][0],0,0,SRCCOPY);
                    RECT rr = {rc.left,rc.top,rc.right+rc.left,rc.top+rc.bottom};
                    InvalidateRect((HWND)Args,&rr,1);
                }
                *lastId = *currentId;
            }
        }
        else
        {
            if(*lastId > -1 && enable[*currentId] && state[*lastId] == 0)
            {
                RECT rc = r[*lastId];
                BitBlt(dc, rc.left, rc.top, rc.right, rc.bottom, 
                finalDC[*lastId][0],0,0,SRCCOPY);
                RECT rr = {rc.left,rc.top,rc.right+rc.left,rc.top+rc.bottom};
                InvalidateRect((HWND)Args,&rr,1);
                *lastId = -1;
            }
        }
    }

}

void mouseLeave_update(csARGS Args)
{
    int id = int(Args);
    csLIST<HDC>* finalDC = (csLIST<HDC>*)Args[0];
    unsigned n = *(unsigned*)Args[1];
    int*activedId = (int*)Args[2];
    int*lastId = (int*)Args[3];
    int*currentId = (int*)Args[4];
    bool*enable = (bool*)Args[8];
    bool*state = (bool*)Args[9];
    short*type = (short*)Args[10];

    csBGRID_PARAMS* bgp = (csBGRID_PARAMS*)Args[5];
    csLIST<int>* map = (csLIST<int>*)Args[6];
    RECT*r = (RECT*)Args[7];
    
    if(*currentId != -1 && *currentId != *activedId)
    {
        if(enable[*currentId])
        {
            RECT rc = r[*currentId];
            HDC dc = cv.CTX[id].getDC();
            if(type[*currentId] == CS_BGRD_GROUP_SELECTION
            || (type[*currentId] == CS_BGRD_BI_SELECTION && 
                state[*currentId] == 0))
            {
                BitBlt(dc, rc.left, rc.top, rc.right, rc.bottom, 
                finalDC[*currentId][0],0,0,SRCCOPY);
                *lastId = -1;
                RECT rr = {rc.left,rc.top,rc.right+rc.left,rc.top+rc.bottom};
                InvalidateRect((HWND)Args,&rr,1);
            }
            

        }
    }
}

void mouseLbtndown_update(csARGS Args)
{
    int id = int(Args);
    csLIST<HDC>* finalDC = (csLIST<HDC>*)Args[0];
    unsigned n = *(unsigned*)Args[1];
    int*activedId = (int*)Args[2];
    int*lastId = (int*)Args[3];
    int*currentId = (int*)Args[4];
    bool*enable = (bool*)Args[8];
    bool*state = (bool*)Args[9];
    short*type = (short*)Args[10];

    csBGRID_PARAMS* bgp = (csBGRID_PARAMS*)Args[5];
    csLIST<int>* map = (csLIST<int>*)Args[6];
    RECT*r = (RECT*)Args[7];
    
    if(*currentId != -1)//modif
    {
        if(enable[*currentId])
        {
            RECT rc = r[*currentId];
            HDC dc = cv.CTX[id].getDC();
            if((type[*currentId] == CS_BGRD_GROUP_SELECTION && *currentId != *activedId )/*|| type[*currentId] == CS_BGRD_BI_SELECTION*/)//modif
            {
                BitBlt(dc, rc.left, rc.top, rc.right, rc.bottom, 
                finalDC[*currentId][0],0,0,SRCCOPY);
            }
            else if(type[*currentId] == CS_BGRD_UNI_SELECTION)
            {
                BitBlt(dc, rc.left, rc.top, rc.right, rc.bottom, 
                finalDC[*currentId][2],0,0,SRCCOPY);
            }
            RECT rr = {rc.left,rc.top,rc.right+rc.left,rc.top+rc.bottom};
            InvalidateRect((HWND)Args,&rr,1);
        }
        //*activedId = *currentId;
    }
}
void mouseLbtnup_update(csARGS Args)
{
    int id = int(Args);
    csLIST<HDC>* finalDC = (csLIST<HDC>*)Args[0];
    unsigned n = *(unsigned*)Args[1];
    int*activedId = (int*)Args[2];
    int*lastId = (int*)Args[3];
    int*currentId = (int*)Args[4];
    bool*enable = (bool*)Args[8];
    bool*state = (bool*)Args[9];
    short*type = (short*)Args[10];
    bool *click_message = (bool*)Args[11];

    csBGRID_PARAMS* bgp = (csBGRID_PARAMS*)Args[5];
    csLIST<int>* map = (csLIST<int>*)Args[6];
    RECT*r = (RECT*)Args[7];
    //std::cout<<"current id : "<<*currentId<<std::endl;
    if(*currentId != -1)
    {
        if(enable[*currentId])
        {
            if(type[*currentId] == CS_BGRD_GROUP_SELECTION && *currentId != *activedId)
            {
                RECT rc = r[*currentId];
                HDC dc = cv.CTX[id].getDC();
                BitBlt(dc, rc.left, rc.top, rc.right, rc.bottom, 
                finalDC[*currentId][2],0,0,SRCCOPY);
                RECT rr = {rc.left,rc.top,rc.right+rc.left,rc.top+rc.bottom};
                InvalidateRect((HWND)Args,&rr,1);
                state[*currentId] = 1;
                
                if(*activedId != -1 && type[*activedId] == CS_BGRD_GROUP_SELECTION)
                {
                    RECT rc = r[*activedId];
                    HDC dc = cv.CTX[id].getDC();
                    BitBlt(dc, rc.left, rc.top, rc.right, rc.bottom, 
                    finalDC[*activedId][0],0,0,SRCCOPY);
                    RECT rr = {rc.left,rc.top,rc.right+rc.left,rc.top+rc.bottom};
                    InvalidateRect((HWND)Args,&rr,1);
                    state[*activedId] = 0;
                }

                *activedId = *currentId;
            }
            else if(type[*currentId] == CS_BGRD_UNI_SELECTION)
            {
                RECT rc = r[*currentId];
                HDC dc = cv.CTX[id].getDC();
                BitBlt(dc, rc.left, rc.top, rc.right, rc.bottom, 
                finalDC[*currentId][0],0,0,SRCCOPY);
                RECT rr = {rc.left,rc.top,rc.right+rc.left,rc.top+rc.bottom};
                InvalidateRect((HWND)Args,&rr,1);
                state[*currentId] = 1;
            }
            else if(type[*currentId] == CS_BGRD_BI_SELECTION)
            {
                RECT rc = r[*currentId];
                HDC dc = cv.CTX[id].getDC();
                if(state[*currentId] == 0)
                {
                    BitBlt(dc, rc.left, rc.top, rc.right, rc.bottom, 
                    finalDC[*currentId][2],0,0,SRCCOPY);
                    state[*currentId] = 1;
                }
                else
                {
                    BitBlt(dc, rc.left, rc.top, rc.right, rc.bottom, 
                    finalDC[*currentId][0],0,0,SRCCOPY);
                    state[*currentId] = 0;
                }
                RECT rr = {rc.left,rc.top,rc.right+rc.left,rc.top+rc.bottom};
                InvalidateRect((HWND)Args,&rr,1);
            }
            //*activedId = *currentId;
            *click_message = 1;
        }
    }
}

