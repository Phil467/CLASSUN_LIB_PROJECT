#include "csCOLORPALETTE.h"
#include "csSYSCMD.h"

extern csCNTR_PARAMS cscp;
extern csCNTR_VARS cv;

void makeIncrement(csARGS Args);
void makeIncrement1(csARGS Args);
void makeIncrement2(csARGS Args);
void btnDown(csARGS Args);
void btnUp(csARGS Args);
void autoSetPosition(csARGS Args);

void updateColors(csARGS Args);
void updateColors2(csARGS Args);
void updateSelectedColor1(csARGS Args);
void updateSelectedColor2(csARGS Args);
void selectColor_incSize(csARGS Args);
void selectColor_lbtndown(csARGS Args);
void selectColor_lbtndown2(csARGS Args);
void getColor(csARGS Args);

void resizeInc(csARGS Args);
void resizeIncChilds(csARGS Args);
void resizeIncChilds2(csARGS Args);
void resizePalette(csARGS Args);
void resizePaletteChilds(csARGS Args);

void longPress1(csARGS Args);
void longPress2(csARGS Args);

void setValueFromClick1(csARGS Args);
void setValueFromClick2(csARGS Args);
void id4ToBottom(csARGS Args);

void mouseWheelSizing(csARGS Args);
void selectorRepos(csARGS Args);
void keyDownIncrement(csARGS Args);

void mapTransposition(csARGS Args);

csRGBA GEN_COL = {40,40,40};

csCOLORPALETTE::csCOLORPALETTE(int idp, RECT geometry, csRGBA initialColor)
{
    pidMap = 0;
    r = 0;
    g = 0;
    b = 0;
    a = 0;
    colorSel = 0;
    rSizeArgsNum = 0; gSizeArgsNum = 0;

    id = staticCnt2(cscp, idp, "Colors", GEN_COL, geometry,1);
    cv.cp[id]->Title.Color = {220,220,220};
    cv.cp[id]->CaptionAreaLength = 30;
    cv.cp[id]->CaptionAreaPos = 1;
    cv.cp[id]->CaptionDirection = 1;
    cv.cp[id]->MinMaxStyle = 0;
    cv.cp[id]->MinTrackSize = {100, 150};
    cv.cp[id]->Title.Color = {255,255,255};
    cv.cp[id]->Title.Bold = FW_BOLD;
    cv.cp[id]->Title.TextRect = {-5,8};
    //cv.cp[id]->TitleAlign = CS_TA_TOP_RIGHT;
    cv.cp[id]->HTRight = 1;
    cv.cp[id]->HTTop = 1;
    cv.cp[id]->HTLeft = 1;
    cv.cp[id]->HTBottom = 1;
    cv.cp[id]->HTCorner = 1;
    cv.cp[id]->SizingAreaLength = 5;

    float sharp = 1;
    cv.CTX[id].brdGrad_right = {2,5,1,1,sharp};
    cv.CTX[id].brdGrad_bottom = {2,5,1,1,sharp};

    int*pid = csf_alloc2<int>(1,id);

    int*pidSys = csf_alloc2<int>(1,0);
    *pidSys = staticCnt2(cscp, id, "", GEN_COL, {0},1);
    cv.CTX[*pidSys].brdGrad_right = {3,5,0,1,1.9};
    cv.CTX[*pidSys].brdGrad_bottom = {3,5,0,1,1.9};
    cv.CTX[*pidSys].borderGradientColor = GEN_COL;
    cv.CTX[*pidSys].setCntBorder({25,25,25},1);

    int* idHider = csAddHider(*pidSys,pid, {22,2,18,18});

    int* pidTransp = csf_alloc2<int>(1,0);
    *pidTransp = imgButton(cscp, *pidSys, "img\\app\\color_transpose.bmp",
                "img\\app\\color_transpose2.bmp",0, {2,2,18,18},{1,1,2,2}, {30,30,30});

    idSelection = staticCnt2(cscp, id, "", {30,30,30}, {5,5,20,20},1);
    int* pidSelection = csf_alloc2<int>(1,idSelection);

    goto hslStyle;

    rgbStyle:
    {
        r = csIncrementer(id, "r", 0, {5,30,258,15}, {200, 0, 0}, CNTR_DISPOSITION_HORIZONTAL);
        g = csIncrementer(id, "g", 0, {5,50,258,15}, {0, 200, 0}, CNTR_DISPOSITION_HORIZONTAL);
        b = csIncrementer(id, "b", 0, {5,70,258,15}, {0, 0, 200}, CNTR_DISPOSITION_HORIZONTAL);
        a = csIncrementer(id, "a", 0, {5,90,258,15}, {40, 40, 40}, CNTR_DISPOSITION_HORIZONTAL);
    }

    hslStyle:
    {
        r = csIncrementer(id, "H", 0, {5,30,258,15}, {70, 70, 70}, CNTR_DISPOSITION_HORIZONTAL);
        g = csIncrementer(id, "S", 0, {5,50,258,15}, {70, 70, 70}, CNTR_DISPOSITION_HORIZONTAL);
        b = csIncrementer(id, "L", 0, {5,70,258,15}, {70, 70, 70}, CNTR_DISPOSITION_HORIZONTAL);
        a = csIncrementer(id, "A", 0, {5,90,258,15}, {50, 50, 50}, CNTR_DISPOSITION_HORIZONTAL);
    }


    cv.cp[r->id4]->Title.Font = "book antiqua";
    cv.cp[r->id4]->Title.FontSize = {12};
    cv.cp[r->id4]->TitleAlign = CS_TA_CENTER;
    cv.cp[r->id4]->AutoTransform.Update = 1;
    cv.cp[g->id4]->Title.Font = "book antiqua";
    cv.cp[g->id4]->Title.FontSize = {12};
    cv.cp[g->id4]->TitleAlign = CS_TA_CENTER;
    cv.cp[g->id4]->AutoTransform.Update = 1;
    cv.cp[b->id4]->Title.Font = "book antiqua";
    cv.cp[b->id4]->Title.FontSize = {12};
    cv.cp[b->id4]->TitleAlign = CS_TA_CENTER;
    cv.cp[b->id4]->AutoTransform.Update = 1;
    cv.cp[a->id4]->Title.Font = "book antiqua";
    cv.cp[a->id4]->Title.FontSize = {12};
    cv.cp[a->id4]->TitleAlign = CS_TA_CENTER;
    cv.cp[a->id4]->AutoTransform.Update = 1;
    /*h = csIncrementer(id, {5,135,190,20}, {100, 100, 100}, CNTR_DISPOSITION_HORIZONTAL);
    s = csIncrementer(id, {5,160,190,20}, {100, 100, 100}, CNTR_DISPOSITION_HORIZONTAL);
    l = csIncrementer(id, {5,185,190,20}, {100, 100, 100}, CNTR_DISPOSITION_HORIZONTAL);*/

    int*rgbbtn = csf_alloc2<int>(3,1), dx = 5, dy = 110, cx = 75, lx = dx+cx, cy = 20;
    SIZE dcsize = {CS_CXSCREEN/3.0, cy};
    rgbbtn[0] = textButton2(cscp, id, "0", {250,150,150}, {5,     dy,cx,cy}, {0}, dcsize);
    rgbbtn[1] = textButton2(cscp, id, "0", {150,250,150}, {5+1*lx,dy,cx,cy}, {0}, dcsize);
    rgbbtn[2] = textButton2(cscp, id, "0", {150,150,250}, {5+2*lx,dy,cx,cy}, {0}, dcsize);

    GetClientRect(csHWND(rgbbtn[0]), &csCLRECT(rgbbtn[0]));//sans effet
    GetClientRect(csHWND(rgbbtn[1]), &csCLRECT(rgbbtn[1]));
    GetClientRect(csHWND(rgbbtn[2]), &csCLRECT(rgbbtn[2]));


    int nbr = 3;
    sharp = 1.9;
    for(int i=0; i<3; i++)
    {
        cv.cp[rgbbtn[i]]->TitleAlign = CS_TA_CENTER;
        cv.cp[rgbbtn[i]]->MHGradient.Color2 = GEN_COL;
        cv.CTX[rgbbtn[i]].borderGradientColor = GEN_COL;
        cv.CTX[rgbbtn[i]].brdGrad_right = {nbr,5,0,1,sharp};
        cv.CTX[rgbbtn[i]].brdGrad_bottom = {nbr,5,0,1,sharp};
        cv.CTX[rgbbtn[i]].setCntBorder({25,25,25},1);
        cv.cp[rgbbtn[i]]->Title.Text = csf_alloc<char>(4);
        sprintf(cv.cp[rgbbtn[i]]->Title.Text, "%d",((*((unsigned int*)(&initialColor)))>>(4*(i+1)))&0xff);
    }



    idMap = staticCnt2(cscp, id, "", {30,30,30}, {5,135,258,258},1);
    cv.cp[idMap]->Cursor = LoadCursor(0,IDC_CROSS);
    cv.CTX[idMap].stretchable();
    //cv.CTX[idMap].setBlitSize({mSize.width, mSize.height});
    cv.CTX[idMap].setCntBorder({0}, 0);
    cv.CTX[idMap].redrawBackground();
    GetClientRect(csHWND(idMap), &csCLRECT(idMap));

    csEXTERN_HDC extHDC;
    extHDC.transparentHDC = 1;
    extHDC.oddColor = RGB(255,0,0);
    extHDC.LoadImage("img\\app\\col_selecter.bmp",{23,23});
    csCTX(idMap).extHDC.insertEnd(extHDC);

    mSize = {256,256};
    bmi = csSetBMI(mSize);
    map = csBitmap(mSize, &bmi);
    uchar*str = (uchar*)map.bm.bmBits;

    GetDIBits(map.dc, map.hbmp, 0, map.bm.bmHeight, str,&bmi, DIB_RGB_COLORS);

    int pos;
    //csRGB col;
    _RGB col;
    for(int j = 0; j<mSize.height; j++)
    {
        for(int i = 0; i<mSize.width; i++)
        {
            //col = {i,j,128};
            col = HSLToRGB(HSL{i*360.0/(map.bm.bmWidth-1),j*1.0/(map.bm.bmHeight-1),0.5});
            pos = (j + i*mSize.height)*4;
            str[pos] = col.b;
            str[pos+1] = col.g;
            str[pos+2] = col.r;
        }
    }

    SetDIBits(map.dc, map.hbmp, 0, map.bm.bmHeight, str,&bmi, DIB_RGB_COLORS);
    HDC hdc = cv.CTX[idMap].getDC();
    //SetStretchBltMode(hdc, TRANSPARENT);
    //StretchBlt(hdc, 1,1,190,190, map.dc, 0,0, 256,256, SRCCOPY);
    BitBlt(hdc, 0,0,256,256, map.dc, 0,0,SRCCOPY);

    csBMP* pmap = csf_alloc2<csBMP>(1,map);
    BITMAPINFO *pbmi = csf_alloc2<BITMAPINFO>(1,bmi);

    colorSel = csf_alloc2<csRGBA>(1,initialColor);

    SetTimer(cv.CNTLIST[idMap], 0, 17, 0);
    POINT *ptSel = csf_alloc2<POINT>(1,{0});
    int *pidMap = csf_alloc2<int>(1,idMap);

    bool*transpose = csf_alloc2<bool>(1,0);
    //csSetAction(idMap, WM_TIMER, updateColors, 6, pmap,pbmi,b, colorSel, pidSelection,ptSel);
    csSetAction(idMap, WM_TIMER, updateColors2, 8, pmap,pbmi,b, colorSel, pidSelection,ptSel, rgbbtn, transpose);
    //pour transposer, permuter les fonctions updateSelectedColor2 et updateSelectedColor1, la position (i+j*cy)*4 en (j+i*cy)*4
    csSetAction(r->id4, WM_SIZE, updateSelectedColor2, 9, pmap,pbmi,r, colorSel, pidSelection,ptSel, &(b->val), pidMap, rgbbtn);
    rSizeArgsNum = csf_alloc2<int>(1, csPARAMS(r->id4)->CntEventsFunc.SIZE.size()-1); //pour la fonction de transposition
    csSetAction(g->id4, WM_SIZE, updateSelectedColor1, 9, pmap,pbmi,g, colorSel, pidSelection,ptSel, &(b->val), pidMap, rgbbtn);
    gSizeArgsNum = csf_alloc2<int>(1, csPARAMS(g->id4)->CntEventsFunc.SIZE.size()-1); //pour la fonction de transposition

    csSetAction(*pidTransp, WM_LBUTTONUP, mapTransposition, 8, transpose, rSizeArgsNum, gSizeArgsNum, &r->id4, &g->id4, 
                                                               &r->size_message, &g->size_message, &b->size_message);

    csARGS rargs = cv.cp[g->id4]->CntEventsFunc.SIZE_ARGS[cv.cp[g->id4]->CntEventsFunc.SIZE_ARGS.size()-1];
    csSetAction(idMap, WM_SIZE, selectorRepos, rargs);

    csSetAction(idMap, WM_LBUTTONDOWN, selectColor_lbtndown2, 8, pmap,r,g,a,colorSel,pidSelection,ptSel, rgbbtn);
    csARGS aargs = cv.cp[idMap]->CntEventsFunc.LBUTTONDOWN_ARGS[cv.cp[idMap]->CntEventsFunc.LBUTTONDOWN_ARGS.size()-1];
    csSetAction(idMap, WM_TIMER, selectColor_incSize,aargs);
    csSetAction(idMap, WM_LBUTTONDBLCLK, getColor, 1, &validate);


    RECT *rr = csf_alloc2<RECT>(1,{0});
    RECT *rg = csf_alloc2<RECT>(1,{0});
    RECT *rb = csf_alloc2<RECT>(1,{0});
    RECT *ra = csf_alloc2<RECT>(1,{0});
    RECT *rrgb = csf_alloc2<RECT>(3,{0});
    RECT *rMap = csf_alloc2<RECT>(1,{0});

    csARGS sargs(12);
    sargs.makeArgs(&r->id, &g->id, &b->id, &a->id, rr, rg, rb, ra, pidMap, rgbbtn, rMap, rrgb);
    csSetAction(id, WM_SIZE, resizePalette, sargs);
    csSetAction(r->id, WM_TIMER, resizePaletteChilds, sargs);
    csSetAction(g->id, WM_TIMER, resizePaletteChilds, sargs);
    csSetAction(b->id, WM_TIMER, resizePaletteChilds, sargs);
    csSetAction(a->id, WM_TIMER, resizePaletteChilds, sargs);
    csSetAction(idMap, WM_TIMER, resizePaletteChilds, sargs);
    csSetAction(rgbbtn[0], WM_TIMER, resizePaletteChilds, sargs);
    csSetAction(rgbbtn[1], WM_TIMER, resizePaletteChilds, sargs);
    csSetAction(rgbbtn[2], WM_TIMER, resizePaletteChilds, sargs);

    SetTimer(cv.CNTLIST[r->id], 0, 11, 0);
    SetTimer(cv.CNTLIST[g->id], 0, 12, 0);
    SetTimer(cv.CNTLIST[b->id], 0, 13, 0);
    SetTimer(cv.CNTLIST[a->id], 0, 12, 0);

    HSL hsl = RGBtoHSL({initialColor.r/255.0, initialColor.g/255.0, initialColor.b/255.0});

    r->val = hsl.h*100.0/360;
    r->bInit = 1;
    g->val = hsl.s*100.0;
    g->bInit = 1;
    b->val = hsl.l*100.0;
    b->bInit = 1;
    a->val = initialColor.a;
    a->bInit = 1;

    csGeometryLink(pidMap, 1, csGLP4_PTR(csGLP4{*pidSys, {40,1.0,0}, {0,0,4}, {0,0,43}, {0,0,23}}));
}

void csCOLORPALETTE::setActiveColor(csRGBA color)
{
    HSL hsl = RGBtoHSL({color.r/255, color.g/255, color.b/255});

    r->val = hsl.h*100.0/360;
    g->val = hsl.s*100.0;
    b->val = hsl.l*100.0;
    a->val = color.a;
    *colorSel = color;
}

csRGBA csCOLORPALETTE::getSelectedColor()
{
    return *colorSel;
}

void selectorRepos(csARGS Args)
{
    POINT* pt = (POINT*)Args[5];
    int idMap = *(int*)Args[7];
    csBMP* map = (csBMP*)Args[0];

    int a = 11, xmarg = 1, ymarg = 1;
    POINT p;
    p.x = pt->x*csCLRECT(idMap).right/float(map->bm.bmWidth+2*xmarg);
    p.y = pt->y*csCLRECT(idMap).bottom/float(map->bm.bmHeight+2*ymarg);
    csCTX(idMap).extHDC[0].pos = {p.x-a, p.y-a};
    InvalidateRect(csHWND(idMap),0,1);
}

void updateColors(csARGS Args) // pour la bleue
{
    int id = int(Args);
    csBMP* map = (csBMP*)Args[0];
    BITMAPINFO* bmi = (BITMAPINFO*)Args[1];
    csINCREMENTER *inc = (csINCREMENTER*)Args[2];

    csRGBA* colorSel = (csRGBA*)Args[3];
    int idSel = *(int*)Args[4];
    POINT pt = *(POINT*)Args[5];

    if(inc->size_message)
    {
        int pos;
        csRGB col;
        int blue = ceil(inc->val*255/100.0);

        colorSel->b = blue;
        cv.CTX[idSel].setBkgBrush(*colorSel);
        InvalidateRect(cv.CNTLIST[idSel], 0,1);

        uchar*str = (uchar*)map->bm.bmBits;
        int cx = map->bm.bmWidth, cy = map->bm.bmHeight;
        for(int j = 0; j<cy; j++)
        {
            for(int i = 0; i<cx; i++)
            {
                //col = hsl_to_rgb({i,j,blue});
                col = {i,j,blue};
                pos = (i + j*cx)*4;
                str[pos] = col.b;
                str[pos+1] = col.g;
                str[pos+2] = col.r;
            }
        }

        SetDIBits(map->dc, map->hbmp, 0, map->bm.bmHeight, str, bmi, DIB_RGB_COLORS);
        HDC hdc = cv.CTX[id].getDC();
        //SetStretchBltMode(hdc, TRANSPARENT);
        //StretchBlt(hdc, 1,1,190,190, map.dc, 0,0, 256,256, SRCCOPY);
        BitBlt(hdc, 0,0,cx,cy, map->dc, 0,0,SRCCOPY);

        int a = 11, xmarg = 1, ymarg = 1;
        POINT p;
        p.x = pt.x*csCLRECT(id).right/float(map->bm.bmWidth+2*xmarg);
        p.y = pt.y*csCLRECT(id).bottom/float(map->bm.bmHeight+2*ymarg);
        csCTX(id).extHDC[0].pos = {p.x-a, p.y-a};

        InvalidateRect(HWND(Args),0,1);
        inc->size_message = 0;
    }
}

void updateColors2(csARGS Args) // pour la bleue
{
    int id = int(Args);
    csBMP* map = (csBMP*)Args[0];
    BITMAPINFO* bmi = (BITMAPINFO*)Args[1];
    csINCREMENTER *inc = (csINCREMENTER*)Args[2];

    csRGBA* colorSel = (csRGBA*)Args[3];
    int idSel = *(int*)Args[4];
    POINT pt = *(POINT*)Args[5];

    if(inc->size_message)
    {
        int pos;
        _RGB col;
        double light = inc->val/100.0;

        uchar*str = (uchar*)map->bm.bmBits;
        int cx = map->bm.bmWidth, cy = map->bm.bmHeight;

        bool transpose = *(bool*)Args[7];
        if(!transpose)
        for(int j = 0; j<cy; j++)
        {
            for(int i = 0; i<cx; i++)
            {
                col = HSLToRGB(HSL{i*360.0/(map->bm.bmWidth-1),j*1.0/(map->bm.bmHeight-1),light});
                pos = (j + i*cy)*4;
                str[pos] = col.b*255;
                str[pos+1] = col.g*255;
                str[pos+2] = col.r*255;
            }
        }
        else
        for(int j = 0; j<cy; j++)
        {
            for(int i = 0; i<cx; i++)
            {
                col = HSLToRGB(HSL{i*360.0/(map->bm.bmWidth-1),j*1.0/(map->bm.bmHeight-1),light});
                pos = (i + j*cx)*4;
                str[pos] = col.b*255;
                str[pos+1] = col.g*255;
                str[pos+2] = col.r*255;
            }
        }

        SetDIBits(map->dc, map->hbmp, 0, map->bm.bmHeight, str, bmi, DIB_RGB_COLORS);
        HDC hdc = cv.CTX[id].getDC();
        //SetStretchBltMode(hdc, TRANSPARENT);
        //StretchBlt(hdc, 1,1,190,190, map.dc, 0,0, 256,256, SRCCOPY);
        BitBlt(hdc, 0,0,cx,cy, map->dc, 0,0,SRCCOPY);

        //selecter
        int a = 11, xmarg = 1, ymarg = 1;
        POINT p;
        p.x = pt.x*csCLRECT(id).right/float(map->bm.bmWidth+2*xmarg);
        p.y = pt.y*csCLRECT(id).bottom/float(map->bm.bmHeight+2*ymarg);
        csCTX(id).extHDC[0].pos = {p.x-a, p.y-a};

        pos = (pt.x + pt.y*map->bm.bmWidth)*4;
        colorSel->b = str[pos];
        colorSel->g = str[pos+1];
        colorSel->r = str[pos+2];

        cv.CTX[idSel].setBkgBrush(*colorSel);
        cv.CTX[idSel].redrawBackground();

        int* rgbbtn = (int*)Args[6];
        for(int i=0; i<3; i++)
        {
            sprintf(cv.cp[rgbbtn[i]]->Title.Text, "%d", (unsigned)str[pos+2-i]);
            InvalidateRect(cv.CNTLIST[rgbbtn[i]],0,1);
        }

        InvalidateRect(HWND(Args),0,1);
        inc->size_message = 0;
    }
}

void mapTransposition(csARGS Args)
{
    int id = (int)Args;
    bool* transpose = (bool*)Args[0];
    int rSizeArgsNum = *(int*)Args[1];
    int gSizeArgsNum  = *(int*)Args[2];
    int rId4 = *(int*)Args[3];
    int gId4  = *(int*)Args[4];
    bool* rsize_message  = (bool*)Args[5];
    bool* gsize_message  = (bool*)Args[6];
    bool* bsize_message  = (bool*)Args[7];

    if(!*transpose)
    {
        *transpose = 1;
    }
    else
        *transpose = 0;

    void(*rfunc)(csARGS)  = csPARAMS(rId4)->CntEventsFunc.SIZE[rSizeArgsNum];
    csPARAMS(rId4)->CntEventsFunc.SIZE[rSizeArgsNum] = csPARAMS(gId4)->CntEventsFunc.SIZE[gSizeArgsNum];
    csPARAMS(gId4)->CntEventsFunc.SIZE[gSizeArgsNum] = rfunc;

    *bsize_message = 1;

    cv.HWNDFOCUS = csHWND(rId4);
    SendMessage(cv.HWNDFOCUS, WM_SIZE,0,0);
    cv.HWNDFOCUS = csHWND(gId4);
    SendMessage(cv.HWNDFOCUS, WM_SIZE,0,0);

}

void updateSelectedColor1(csARGS Args)
{
    csINCREMENTER *inc = (csINCREMENTER*)Args[2];

    if(inc->size_message)
    {
        int id = int(Args);
        csBMP* map = (csBMP*)Args[0];
        BITMAPINFO* bmi = (BITMAPINFO*)Args[1];

        csRGBA* colorSel = (csRGBA*)Args[3];
        int idSel = *(int*)Args[4];
        POINT* pt = (POINT*)Args[5];
        float light_fact = *(float*)Args[6];
        int idMap = *(int*)Args[7];

        float light = light_fact/100.0;

        pt->x = inc->val*map->bm.bmWidth/100.0;
        uchar*str = (uchar*)map->bm.bmBits;
        int pos = (pt->x + pt->y*map->bm.bmWidth)*4;

        colorSel->b = str[pos];
        colorSel->g = str[pos+1];
        colorSel->r = str[pos+2];

        int* rgbbtn = (int*)Args[8];
        for(int i=0; i<3; i++)
        {
            sprintf(cv.cp[rgbbtn[i]]->Title.Text, "%d", (unsigned)str[pos+2-i]);
            InvalidateRect(cv.CNTLIST[rgbbtn[i]],0,1);
        }

        cv.CTX[idSel].setBkgBrush(*colorSel);
        cv.CTX[idSel].redrawBackground();

        //selecter
        int a = 11, xmarg = 1, ymarg = 1;
        POINT p;
        p.x = pt->x*csCLRECT(idMap).right/float(map->bm.bmWidth+2*xmarg);
        p.y = pt->y*csCLRECT(idMap).bottom/float(map->bm.bmHeight+2*ymarg);
        csCTX(idMap).extHDC[0].pos = {p.x-a, p.y-a};

        cv.CTX[idMap].redrawBackground();
        HDC hdc = cv.CTX[idMap].getDC();
        BitBlt(hdc, 0,0,map->bm.bmWidth,map->bm.bmHeight, map->dc, 0,0,SRCCOPY);

        InvalidateRect(cv.CNTLIST[idMap],0,1);
        inc->size_message = 0;
    }
}

void updateSelectedColor2(csARGS Args)
{
    csINCREMENTER *inc = (csINCREMENTER*)Args[2];

    if(inc->size_message)
    {
        int id = int(Args);
        csBMP* map = (csBMP*)Args[0];
        BITMAPINFO* bmi = (BITMAPINFO*)Args[1];

        csRGBA* colorSel = (csRGBA*)Args[3];
        int idSel = *(int*)Args[4];
        POINT* pt = (POINT*)Args[5];

        float light_fact = *(float*)Args[6];
        int idMap = *(int*)Args[7];

        float light = light_fact/100.0;
        pt->y = inc->val*map->bm.bmWidth/100.0;
        uchar*str = (uchar*)map->bm.bmBits;
        int pos = (pt->x + pt->y*map->bm.bmWidth)*4;

        colorSel->b = str[pos];
        colorSel->g = str[pos+1];
        colorSel->r = str[pos+2];

        int* rgbbtn = (int*)Args[8];
        for(int i=0; i<3; i++)
        {
            sprintf(cv.cp[rgbbtn[i]]->Title.Text, "%d", (unsigned)str[pos+2-i]);
            InvalidateRect(cv.CNTLIST[rgbbtn[i]],0,1);
        }

        cv.CTX[idSel].setBkgBrush(*colorSel);
        cv.CTX[idSel].redrawBackground();

        //selector
        int a = 11, xmarg = 1, ymarg = 1;
        POINT p;
        p.x = pt->x*csCLRECT(idMap).right/float(map->bm.bmWidth+2*xmarg);
        p.y = pt->y*csCLRECT(idMap).bottom/float(map->bm.bmHeight+2*ymarg);
        csCTX(idMap).extHDC[0].pos = {p.x-a, p.y-a};


        cv.CTX[idMap].redrawBackground();
        HDC hdc = cv.CTX[idMap].getDC();
        BitBlt(hdc, 0,0,map->bm.bmWidth,map->bm.bmHeight, map->dc, 0,0,SRCCOPY);

        InvalidateRect(cv.CNTLIST[idMap],0,1);
        inc->size_message = 0;
    }
}

void selectColor_incSize(csARGS Args) // pour les autres
{
    csBMP* map = (csBMP*)Args[0];
    csINCREMENTER *rinc = (csINCREMENTER*)Args[1];
    csINCREMENTER *ginc = (csINCREMENTER*)Args[2];
    csINCREMENTER *ainc = (csINCREMENTER*)Args[3];
    csRGBA* color = (csRGBA*)Args[4];
    int idSel = *(int*)Args[5];

    if(rinc->size_message)
    {
        color->r = ceil(rinc->val*255/100.0);
        cv.CTX[idSel].setBkgBrush(*color); // ne pas factoriser,car wm_timer;
        rinc->size_message = 0;
    }
    else if(ginc->size_message)
    {
        color->g = ceil(ginc->val*255/100.0);
        cv.CTX[idSel].setBkgBrush(*color);
        ginc->size_message = 0;
    }
    else if(ainc->size_message)
    {
        color->a = ceil(ainc->val);
        ainc->size_message = 0;
    }

    int* rgbbtn = (int*)Args[7];
    sprintf(cv.cp[rgbbtn[0]]->Title.Text, "%d", (unsigned)color->r);
    sprintf(cv.cp[rgbbtn[1]]->Title.Text, "%d", (unsigned)color->g);
    sprintf(cv.cp[rgbbtn[2]]->Title.Text, "%d", (unsigned)color->b);
    InvalidateRect(cv.CNTLIST[rgbbtn[0]],0,1);
    InvalidateRect(cv.CNTLIST[rgbbtn[1]],0,1);
    InvalidateRect(cv.CNTLIST[rgbbtn[2]],0,1);
}

void selectColor_lbtndown(csARGS Args)
{
    int id = int(Args);
    csBMP* map = (csBMP*)Args[0];
    csINCREMENTER *rinc = (csINCREMENTER*)Args[1];
    csINCREMENTER *ginc = (csINCREMENTER*)Args[2];
    csINCREMENTER *ainc = (csINCREMENTER*)Args[3];
    csRGBA* color = (csRGBA*)Args[4];
    int idSel = *(int*)Args[5];
    POINT* ptSel = (POINT*)Args[6];

    GetWindowRect(cv.CNTLIST[rinc->id4], &cv.CNTRECT_SAVED[rinc->id4]);
    GetWindowRect(cv.CNTLIST[ginc->id4], &cv.CNTRECT_SAVED[ginc->id4]);

    int xmarg = 1, ymarg = 1;
    int cx = map->bm.bmWidth, cy = map->bm.bmHeight;

    POINT p;
    GetCursorPos(&p);
    ScreenToClient(HWND(Args), &p);
    int a = 11;
    csCTX(id).extHDC[0].pos = {p.x-a, p.y-a};

    p.x*=(float(cx+2*xmarg)/csCLRECT(id).right);
    p.y*=(float(cy+2*ymarg)/csCLRECT(id).bottom);
    *ptSel = p;

    int pos = ((p.x) + (p.y)*cx)*4; // transposition
    //int pos = ((p.y) + (p.x)*cy)*4;

    uchar*str = (uchar*)map->bm.bmBits;
    color->b = str[pos];
    color->g = str[pos+1];
    color->r = str[pos+2];
    color->a = ceil(ainc->val);

    //rinc->val = p.x*100.0/cx; // transposition
    //ginc->val = p.y*100.0/cy;
    rinc->val = p.y*100.0/cy;
    ginc->val = p.x*100.0/cx;

    int* rgbbtn = (int*)Args[7];
    for(int i=0; i<3; i++)
    {
        sprintf(cv.cp[rgbbtn[i]]->Title.Text, "%d", (unsigned)str[pos+2-i]);
        InvalidateRect(cv.CNTLIST[rgbbtn[i]],0,1);
    }
    cv.CTX[idSel].setBkgBrush(*color);
    cv.CTX[idSel].redrawBackground();

    HDC hdc = cv.CTX[(int)Args].getDC();

    BitBlt(hdc,0,0,cx,cy, map->dc, 0,0,SRCCOPY);

    InvalidateRect(HWND(Args),0,1);
}

void selectColor_lbtndown2(csARGS Args)
{
    int id = (int)Args;
    csBMP* map = (csBMP*)Args[0];
    csINCREMENTER *rinc = (csINCREMENTER*)Args[1];
    csINCREMENTER *ginc = (csINCREMENTER*)Args[2];
    csINCREMENTER *ainc = (csINCREMENTER*)Args[3];
    csRGBA* color = (csRGBA*)Args[4];
    int idSel = *(int*)Args[5];
    POINT* ptSel = (POINT*)Args[6];

    GetWindowRect(cv.CNTLIST[rinc->id4], &cv.CNTRECT_SAVED[rinc->id4]);
    GetWindowRect(cv.CNTLIST[ginc->id4], &cv.CNTRECT_SAVED[ginc->id4]);

    int xmarg = 1, ymarg = 1;
    int cx = map->bm.bmWidth, cy = map->bm.bmHeight;

    POINT p;
    GetCursorPos(&p);
    ScreenToClient(HWND(Args), &p);
    int a = 11;
    csCTX(id).extHDC[0].pos = {p.x-a, p.y-a};

    p.x*=(float(cx+2*xmarg)/csCLRECT(id).right);
    p.y*=(float(cy+2*ymarg)/csCLRECT(id).bottom);
    *ptSel = p;

    int pos = ((p.x) + (p.y)*cx)*4;

    uchar*str = (uchar*)map->bm.bmBits;
    color->b = str[pos];
    color->g = str[pos+1];
    color->r = str[pos+2];
    color->a = ceil(ainc->val);

    HSL hsl = RGBtoHSL(_RGB{color->r/255.0, color->g/255.0, color->b/255.0});
    rinc->val = hsl.h*100.0/360.0;
    ginc->val = hsl.s*100.0;

    /*int* rgbbtn = (int*)Args[7];
    sprintf(cv.cp[rgbbtn[0]]->Title.Text, "%d", (unsigned)color->r);
    sprintf(cv.cp[rgbbtn[1]]->Title.Text, "%d", (unsigned)color->g);
    sprintf(cv.cp[rgbbtn[2]]->Title.Text, "%d", (unsigned)color->b);
    InvalidateRect(cv.CNTLIST[rgbbtn[0]],0,1);
    InvalidateRect(cv.CNTLIST[rgbbtn[1]],0,1);
    InvalidateRect(cv.CNTLIST[rgbbtn[2]],0,1);*/

    cv.CTX[idSel].setBkgBrush(*color);
    cv.CTX[idSel].redrawBackground();

    HDC hdc = cv.CTX[(int)Args].getDC();

    BitBlt(hdc, 0,0,map->bm.bmWidth,map->bm.bmHeight, map->dc, 0,0,SRCCOPY);

    InvalidateRect(HWND(Args),0,1);
}

int csCOLORPALETTE::getId()
{
    return id;
}

void getColor(csARGS Args)
{
    bool* validate = (bool*)Args[0];
    *validate = 1;
}

csCOLORPALETTE::~csCOLORPALETTE()
{
    //dtor
}



/******************************************************************************************** */

csINCREMENTER *csIncrementer(int idp, char*title, float val, RECT geometry, csRGBA color, bool orientation)
{
    csINCREMENTER inc;
    inc.id = staticCnt2(cscp, idp, "", {30,30,30}, geometry,1);
    cv.CTX[inc.id].setCntBorder({30,30,30}, 1);

    inc.hmarg = 0;
    inc.vmarg = 0;
    inc.id12len = 15;
    inc.orientation = orientation;
    inc.step = 3;
    int dx = inc.mrg3 = 0;
    int mrg = inc.mrg4 = 2;
    inc.bInit = 1;
    inc.val = val;


    RECT *rr2 = csf_alloc2<RECT>(1,{0});
    RECT *rr3 = csf_alloc2<RECT>(1,{0});
    RECT *rr4 = csf_alloc2<RECT>(1,{0});
    RECT *rr5 = csf_alloc2<RECT>(1,{0});

    if(orientation == CNTR_DISPOSITION_HORIZONTAL)
    {
        inc.id1 = textButton(cscp, inc.id, "<", {100,100,100}, {inc.hmarg, inc.vmarg,
                            inc.id12len, geometry.bottom-2*inc.vmarg},{0});
        inc.id2 = textButton(cscp, inc.id, ">", {100,100,100}, {geometry.right-inc.hmarg-inc.id12len, inc.vmarg,
                            inc.id12len, geometry.bottom-2*inc.vmarg},{0});
        inc.id3 = staticCnt2(cscp, inc.id, title, {30,30,30}, {inc.hmarg+inc.id12len+dx, inc.vmarg,
                            geometry.right-2*inc.hmarg-2*inc.id12len-2*dx, geometry.bottom-2*inc.vmarg},1,0.05);
        inc.id4 = staticCnt2(cscp, inc.id3, "", color, {mrg, mrg,
                            15, geometry.bottom-2*inc.vmarg-2*mrg},1);


        cv.cp[inc.id4]->Title.Color={220,220,220};
        cv.cp[inc.id4]->Title.Text = (char*)malloc(20);
        cv.cp[inc.id4]->AutoTransform.Update = 1;
        cv.cp[inc.id4]->AutoTransform.Type = AUTO_TRANSF_LENGTH;
        cv.cp[inc.id4]->AutoTransform.Time = 5;
        sprintf(cv.cp[inc.id4]->Title.Text, "%d %%", (int)val);

        RECT r3 = cv.CNTCLWRECT[inc.id3];
        RECT r4 = cv.CNTCLWRECT[inc.id4];

        int maxInclen = inc.maxInclen = r3.right-r4.right-mrg;

        cv.cp[inc.id4]->MinTrackSize = {r4.right, r4.bottom};
        //cv.cp[inc.id4]->MaxTrackSize = {r3.right-mrg, r4.bottom};
        cv.cp[inc.id4]->HTMask = CSA_RIGHT;
        cv.CTX[inc.id4].setCntBorder({color.r+5,color.g+5,color.b+5}, 1);
        float sharp = 2;
        cv.CTX[inc.id4].brdGrad_right = {3,5,1,1,sharp};
        cv.CTX[inc.id4].brdGrad_bottom = {3,5,1,1,sharp};

        cv.CTX[inc.id1].setCntBorder({30,30,30}, 1);
        cv.cp[inc.id1]->BackgroundColor = {20,20,20};
        cv.cp[inc.id1]->MHGradient.Color1 = {50,50,5};
        cv.cp[inc.id1]->MHGradient.Color2 = {30,35,36};
        cv.cp[inc.id1]->Title.Color = {100,100,100};
        cv.cp[inc.id1]->Title.Font = "Calibri";
        cv.cp[inc.id1]->TitleAlign = CS_TA_CENTER;
        sharp = 1.5;
        cv.CTX[inc.id1].brdGrad_right = {3,5,1,1,sharp};
        cv.CTX[inc.id1].brdGrad_bottom = {3,5,1,1,sharp};

        cv.CTX[inc.id2].setCntBorder({30,30,30}, 1);
        cv.cp[inc.id2]->BackgroundColor = {20,20,20};
        cv.cp[inc.id2]->MHGradient.Color1 = GEN_COL;
        cv.cp[inc.id2]->MHGradient.Color2 = {30,35,36};
        cv.cp[inc.id2]->Title.Color = {100,100,100};
        cv.cp[inc.id2]->Title.Font = "Calibri";
        cv.cp[inc.id2]->TitleAlign = CS_TA_CENTER;
        cv.CTX[inc.id2].brdGrad_right = {3,5,1,1,sharp};
        cv.CTX[inc.id2].brdGrad_bottom = {3,5,1,1,sharp};

        cv.CTX[inc.id3].setCntBorder({30,30,30}, 1);
        csSetBackgroundColor(inc.id3,GEN_COL);// aucun effet si MHGradient est actif
        cv.CTX[inc.id3].brdGrad_right = {2,5,0,1,sharp};
        cv.CTX[inc.id3].brdGrad_bottom = {2,5,0,1,sharp};
        cv.CTX[inc.id3].borderGradientColor = cv.cp[inc.id3]->BackgroundColor;
        cv.cp[inc.id3]->TitleAlign = CS_TA_CENTER_RIGHT;
        cv.cp[inc.id3]->Title.Font = "book antiqua";
        cv.cp[inc.id3]->Title.Bold = FW_BOLD;
        cv.cp[inc.id3]->Title.Color = {120,120,120};
        cv.cp[inc.id3]->Title.TextRect = {-5};
        cv.cp[inc.id3]->Title.FontSize = {14};

        SetTimer(cv.CNTLIST[inc.id3], 0, 14, 0);
        SetTimer(cv.CNTLIST[inc.id4], 0, 16, 0);

    }

    csINCREMENTER* pinc = csf_alloc2<csINCREMENTER>(1,inc);
    pinc->val = val;

    csARGS args(1);
    args.makeArgs(pinc);
    csSetAction(inc.id4, WM_SIZE, makeIncrement, args);
    csSetAction(inc.id4, WM_TIMER, autoSetPosition, args);
    csSetAction(inc.id1, WM_MOUSEWHEEL, mouseWheelSizing, args);
    csSetAction(inc.id2, WM_MOUSEWHEEL, mouseWheelSizing, args);
    csSetAction(inc.id3, WM_MOUSEWHEEL, mouseWheelSizing, args);
    csSetAction(inc.id4, WM_MOUSEWHEEL, mouseWheelSizing, args);

    bool*b1 = csf_alloc2<bool>(1,0);
    csARGS args1;
    args1.setArgNumber(2);
    args1.makeArgs(pinc, b1);
    csSetAction(inc.id3, WM_LBUTTONUP, setValueFromClick1, args1);
    //csSetAction(inc.id4, WM_NCLBUTTONDOWN, setValueFromClick2, args1);
    csSetGroupedAction(inc.id1, longPress1, args1);

    bool*b2 = csf_alloc2<bool>(1,0);
    csARGS args2;
    args2.setArgNumber(2);
    args2.makeArgs(pinc, b2);
    csSetGroupedAction(inc.id2, longPress2, args2);


    csARGS rargs(4);
    rargs.makeArgs(pinc, rr2,rr3,rr4);
    csSetAction(inc.id, WM_SIZE, resizeInc, rargs);
    csSetAction(inc.id, WM_TIMER, resizeIncChilds2, rargs);
    /*csSetAction(inc.id2, WM_TIMER, resizeIncChilds, 6, pinc, rr2,rr3,rr4,rr5, &(pinc->id2));
    csSetAction(inc.id3, WM_TIMER, resizeIncChilds, 6, pinc, rr2,rr3,rr4,rr5, &(pinc->id3));
    csSetAction(inc.id4, WM_TIMER, resizeIncChilds, 6, pinc, rr2,rr3,rr4,rr5, &(pinc->id4));*/

    //SetClassLong(cv.CNTLIST[inc.id3], GCL_STYLE, GetClassLong(cv.CNTLIST[inc.id3], GCL_STYLE)&~CS_DBLCLKS);
    //SetClassLong(cv.CNTLIST[inc.id4], GCL_STYLE, GetClassLong(cv.CNTLIST[inc.id4], GCL_STYLE)&~CS_DBLCLKS);

    csSetAction(inc.id, WM_KEYDOWN, keyDownIncrement, rargs);
    csSetAction(inc.id1, WM_KEYDOWN, keyDownIncrement, rargs);
    csSetAction(inc.id2, WM_KEYDOWN, keyDownIncrement, rargs);
    csSetAction(inc.id3, WM_KEYDOWN, keyDownIncrement, rargs);
    csSetAction(inc.id4, WM_KEYDOWN, keyDownIncrement, rargs);

    return pinc;
}

void makeIncrement(csARGS Args)
{
    int id = int(Args);
    csINCREMENTER *inc = (csINCREMENTER*)Args[0];

    //if(id == inc->id4)
    if(cv.HWNDFOCUS == (HWND)Args || inc->bInit)
    {
        inc->size_message = 1;
        RECT r = cv.CNTCLWRECT[id];

        if(inc->orientation == CNTR_DISPOSITION_HORIZONTAL)
        {
            if(!inc->bInit)
            {
                //if(cv.cp[inc->id4]->AutoTransform.waitUntilAnimEnds)
                {
                    float f = (r.right-cv.cp[id]->MinTrackSize.cx)*100.0/inc->maxInclen;
                    std::cout<<inc->val<<" init val\n";
                    sprintf(cv.cp[inc->id4]->Title.Text, "%d %%", (int)inc->val);
                    InvalidateRect(cv.CNTLIST[inc->id4], 0,1);
                    inc->val = f;
                    inc->val_s = f;
                }

            }
            else
            {
                inc->bInit = 0;
                GetWindowRect(HWND(Args), &cv.CNTRECT[id]);
                GetWindowRect(HWND(Args), &cv.CNTRECT_SAVED[id]);
                //SendMessage(cv.CNTLIST[id], WM_TIMER, 0, 0);
            }
        }
        //SendMessage(cv.CNTLIST[inc->id],WM_TIMER,0,0);
    }

}

void btnDown(csARGS Args)
{
    *(bool*)Args[1] = 1;
}
void btnUp(csARGS Args)
{
    *(bool*)Args[1] = 0;
}

void makeIncrement1(csARGS Args)
{
    int id = int(Args);
    csINCREMENTER *inc = (csINCREMENTER*)Args[0];
    bool b = *(bool*)Args[1];

    //if(b)
    {
        inc->click1_message = 1;
        RECT r = cv.CNTCLWRECT[id];

        if(inc->orientation == CNTR_DISPOSITION_HORIZONTAL)
        {
            /*int dx = inc->step;
            RECT r4 = cv.CNTCLWRECT[inc->id4];
            float f = dx*100.0/inc->maxInclen;*/
            RECT r4 = cv.CNTCLWRECT[inc->id4];
            float f = inc->stepVal;
            int dx = inc->maxInclen*f/100.0;
            if(r4.right - dx > cv.cp[inc->id4]->MinTrackSize.cx)
            {   inc->val -= f;
                inc->val_s -= f;
                SetWindowPos(cv.CNTLIST[inc->id4], HWND_BOTTOM,0, 0, r4.right-dx, r4.bottom, SWP_NOMOVE);
                //cv.CNTCLWRECT[inc->id4].right-=dx;
            }
            else
            {
                SetWindowPos(cv.CNTLIST[inc->id4], HWND_BOTTOM,0, 0, cv.cp[inc->id4]->MinTrackSize.cx, r4.bottom, SWP_NOMOVE);
                //GetClientRect(cv.CNTLIST[inc->id4], &cv.CNTCLWRECT[inc->id4]);
                inc->val = 0;
                *(bool*)Args[1] = 0;
            }
            sprintf(cv.cp[inc->id4]->Title.Text, "%d %%", (int)inc->val);
            InvalidateRect(cv.CNTLIST[inc->id4], 0,1);

            cv.HWNDFOCUS = cv.CNTLIST[inc->id4];
            SendMessage(cv.CNTLIST[inc->id4], WM_SIZE,0,0);
        }
    }
    if(inc->mouseWheel1_extCmd) // simuler un clic si id1 et id2
    {
        SendMessage((HWND)Args, WM_LBUTTONUP, 0, 0);
        SendMessage((HWND)Args, WM_MOUSELEAVE, 0, 0);
    }

}

void makeIncrement2(csARGS Args)
{
    int id = int(Args);
    csINCREMENTER *inc = (csINCREMENTER*)Args[0];
    bool b = *(bool*)Args[1];

    //if(b)
    {
        inc->click2_message = 1;
        if(inc->orientation == CNTR_DISPOSITION_HORIZONTAL)
        {
            RECT r4 = cv.CNTCLWRECT[inc->id4];
            float f = inc->stepVal;
            int dx = inc->maxInclen*f/100.0;
            int minsz = cv.cp[inc->id4]->MinTrackSize.cx;
            //std::cout<<"mts : "<<inc->maxInclen<<"\n";
            if(r4.right-minsz + dx < inc->maxInclen)
            {   inc->val += f;
                inc->val_s += f;
                SetWindowPos(cv.CNTLIST[inc->id4], HWND_BOTTOM,0, 0, r4.right+dx, r4.bottom, SWP_NOMOVE|SWP_NOZORDER);
            }
            else
            {
                SetWindowPos(cv.CNTLIST[inc->id4], HWND_BOTTOM,0, 0, inc->maxInclen+minsz, r4.bottom, SWP_NOMOVE|SWP_NOZORDER);
                inc->val = 100;
                inc->val_s = 100;
                *(bool*)Args[1] = 0;
            }
            sprintf(cv.cp[inc->id4]->Title.Text, "%d %%", (int)inc->val);
            InvalidateRect(cv.CNTLIST[inc->id4], 0,1);

            cv.HWNDFOCUS = cv.CNTLIST[inc->id4];
            SendMessage(cv.CNTLIST[inc->id4], WM_SIZE,0,0);
        }
        //GetClientRect(cv.CNTLIST[inc->id4], &cv.CNTCLWRECT[inc->id4]);
    }

    if(inc->mouseWheel2_extCmd)
    {
        SendMessage((HWND)Args, WM_LBUTTONUP, 0, 0);
        SendMessage((HWND)Args, WM_MOUSELEAVE, 0, 0);
    }

}


void autoSetPosition(csARGS Args)
{
    int id = int(Args);
    csINCREMENTER *inc = (csINCREMENTER*)Args[0];

    if(inc->val != inc->val_s)
    {
        inc->val_s = inc->val;
        sprintf(cv.cp[inc->id4]->Title.Text, "%d %%", int(ceil(inc->val)));
        //InvalidateRect(cv.CNTLIST[inc->id4], 0,1);
//std::cout<<int(ceil(inc->val))<<" init val\n";
        RECT r4 = rectInParentRef(id);
        cv.cp[id]->AutoTransform.InitialRect = r4;
        cv.cp[id]->AutoTransform.EmergencyStop = 0;
        if(inc->orientation == CNTR_DISPOSITION_HORIZONTAL)
        {
            int l = ceil(inc->val*inc->maxInclen/100.0) + cv.cp[id]->MinTrackSize.cx;
            cv.cp[id]->AutoTransform.FinalRect = {0,0,l-(r4.right-r4.left),0};
        }
        else
        {
            int l = ceil(inc->val*inc->maxInclen/100.0) + cv.cp[id]->MinTrackSize.cy;
            cv.cp[id]->AutoTransform.FinalRect = {0,0,l-(r4.bottom-r4.top),0};
        }

        cv.AUTOTRANSCOUNT[id] = 0;
    }

    static int maxCount = 5, count = 0;

    if(inc->wheelCumulStep1)
    {
        if(count < maxCount)
        {
            count++;
        }
        else
        {
            float a = inc->val - inc->wheelCumulStep1;
            inc->val = (a > 0.0) ? a : 0.0;
            count = 0;
            inc->wheelCumulStep1 = 0;
        }
    }
    else if(inc->wheelCumulStep2)
    {
        if(count < maxCount)
        {
            count++;
        }
        else
        {
            float a = inc->val + inc->wheelCumulStep2;
            inc->val = (a < 100.0) ? a : 100.0;
            count = 0;
            inc->wheelCumulStep2 = 0;
        }
    }
}

void resizeInc(csARGS Args)
{
    int id = int(Args);
    csINCREMENTER inc = *(csINCREMENTER*)Args[0];
    RECT* r2 = (RECT*)Args[1];
    RECT* r3 = (RECT*)Args[2];
    RECT* r4 = (RECT*)Args[3];

    RECT r = cv.CNTCLWRECT[int(Args)];

    if(inc.orientation == CNTR_DISPOSITION_HORIZONTAL)
    {
        *r2 = {r.right-inc.hmarg-inc.id12len, inc.vmarg,
                            inc.id12len, r.bottom-2*inc.vmarg};
        *r3 = {inc.hmarg+inc.id12len+inc.mrg3, inc.vmarg,
                            r.right-2*inc.hmarg-2*inc.id12len-2*inc.mrg3, r.bottom-2*inc.vmarg};

        int maxIncLen = r3->right-cv.cp[inc.id4]->MinTrackSize.cx-inc.mrg4;

        ((csINCREMENTER*)Args[0])->maxInclen = maxIncLen;

        int l = ceil(inc.val*maxIncLen/100.0) + cv.cp[inc.id4]->MinTrackSize.cx;

        *r4 =  {inc.mrg4, inc.mrg4, l, r.bottom-2*inc.vmarg-2*inc.mrg4};

    }

    //SendMessage(cv.CNTLIST[inc.id1],WM_TIMER,0,0);

}
void resizeIncChilds(csARGS Args)
{
    //int id = int(Args);
    int id = *(int*)Args[5];
    csINCREMENTER inc = *(csINCREMENTER*)Args[0];
    RECT* r2 = (RECT*)Args[1];
    RECT* r3 = (RECT*)Args[2];
    RECT* r4 = (RECT*)Args[3];
    RECT* r5 = (RECT*)Args[4];

    if(inc.orientation == CNTR_DISPOSITION_HORIZONTAL)
    {
        if(id == inc.id2 && r2->left != 0)
        {
            SetWindowPos((HWND)Args, HWND_TOP, r2->left, r2->top,0,0,SWP_NOSIZE|SWP_NOZORDER);
            *r2 = {0,0,0,0};
        }
        else if(id == inc.id3 && r3->right != 0)
        {
            SetWindowPos((HWND)Args, HWND_BOTTOM, 0, 0,r3->right,r3->bottom,SWP_NOMOVE|SWP_NOZORDER);
            *r3 = {0,0,0,0};
        }
        else if(id == inc.id4 && r4->right != 0)
        {
            SetWindowPos((HWND)Args, HWND_BOTTOM, 0, 0,r4->right,r4->bottom,SWP_NOMOVE|SWP_NOZORDER);
            InvalidateRect((HWND)Args,0,1);
            *r4 = {0,0,0,0};
        }
    }
}

void resizeIncChilds2(csARGS Args)
{
    csINCREMENTER inc = *(csINCREMENTER*)Args[0];
    RECT* r2 = (RECT*)Args[1];
    RECT* r3 = (RECT*)Args[2];
    RECT* r4 = (RECT*)Args[3];

    if(inc.orientation == CNTR_DISPOSITION_HORIZONTAL)
    {
        if(r2->left != 0)
        {
            SetWindowPos(cv.CNTLIST[inc.id2], HWND_TOP, r2->left, r2->top,0,0,SWP_NOSIZE|SWP_NOZORDER);
            *r2 = {0,0,0,0};
        }
        if(r3->right != 0)
        {
            SetWindowPos(cv.CNTLIST[inc.id3], HWND_BOTTOM, 0, 0,r3->right,r3->bottom,SWP_NOMOVE|SWP_NOZORDER);
            *r3 = {0,0,0,0};
        }
        if(r4->right != 0)
        {
            SetWindowPos(cv.CNTLIST[inc.id4], HWND_BOTTOM, 0, 0,r4->right,r4->bottom,SWP_NOMOVE|SWP_NOZORDER);
            InvalidateRect(cv.CNTLIST[inc.id4],0,1);
            *r4 = {0,0,0,0};
        }
    }
}

void resizePalette(csARGS Args)
{
    int id = int(Args);
    RECT r = cv.CNTCLWRECT[id], rw = cv.CNTRECT[id];
    RECT *rr = (RECT*)Args[4];
    RECT *rg = (RECT*)Args[5];
    RECT *rb = (RECT*)Args[6];
    RECT *ra = (RECT*)Args[7];
    *rr = {0,0,r.right-2*cv.cp[(int)Args]->SizingAreaLength,0};
    *rg = *rr;
    *rb = *rr;
    *ra = *rr;

    RECT *rmap = (RECT*)Args[10];
    RECT *rrgb = (RECT*)Args[11];

    int *idr = (int*)Args[0];
    int *idg = (int*)Args[1];
    int *idb = (int*)Args[2];
    int *ida = (int*)Args[3];

    int *idMap = (int*)Args[8];
    int *rgbbtn = (int*)Args[9];

    RECT rm;// = cv.CNTRECT[*idMap];
    GetWindowRect(csHWND(*idMap), &rm);
    *rmap = {0,0,r.right-cv.cp[id]->SizingAreaLength*2, rw.bottom-rm.top-cv.cp[id]->SizingAreaLength};

    RECT r_rgb = cv.CNTCLWRECT[rgbbtn[0]]; //rw_rgb = cv.CNTRECT[rgbbtn[0]];

    int offset = 5;
    rrgb[0] = {cv.cp[id]->SizingAreaLength,0, (r.right-2*(offset + cv.cp[id]->SizingAreaLength))/3.0, r_rgb.bottom};
    rrgb[1] = {rrgb[0].right+rrgb[0].left+offset, 110, rrgb[0].right, r_rgb.bottom};
    rrgb[2] = {rrgb[1].right+rrgb[1].left+offset, rrgb[1].top, rrgb[0].right, r_rgb.bottom};

    SendMessage(cv.CNTLIST[*idr],WM_TIMER,0,0);
    SendMessage(cv.CNTLIST[*idg],WM_TIMER,0,0);
    SendMessage(cv.CNTLIST[*idb],WM_TIMER,0,0);
    SendMessage(cv.CNTLIST[*ida],WM_TIMER,0,0);
    SendMessage(cv.CNTLIST[*idMap],WM_TIMER,0,0);
    SendMessage(cv.CNTLIST[rgbbtn[0]],WM_TIMER,0,0);
    SendMessage(cv.CNTLIST[rgbbtn[1]],WM_TIMER,0,0);
    SendMessage(cv.CNTLIST[rgbbtn[2]],WM_TIMER,0,0);
}

void resizePaletteChilds(csARGS Args)
{
    int id = (int)Args;
    int *idr = (int*)Args[0];
    int *idg = (int*)Args[1];
    int *idb = (int*)Args[2];
    int *ida = (int*)Args[3];
    int *idMap = (int*)Args[8];
    int *rgbbtn = (int*)Args[9];

    RECT *rr = (RECT*)Args[4];
    RECT *rg = (RECT*)Args[5];
    RECT *rb = (RECT*)Args[6];
    RECT *ra = (RECT*)Args[7];
    RECT *rmap = (RECT*)Args[10];
    RECT *rrgb = (RECT*)Args[11];

    if(id == *idr && rr->right)
    {
        SetWindowPos((HWND)Args, HWND_TOP, 0,0,rr->right,cv.CNTCLWRECT[*idr].bottom,SWP_NOMOVE|SWP_NOZORDER);
        *rr = {0,0,0,0};
    }
    else if(id == *idg && rg->right)
    {
        SetWindowPos((HWND)Args, HWND_TOP, 0,0,rg->right,cv.CNTCLWRECT[*idg].bottom,SWP_NOMOVE|SWP_NOZORDER);
        *rg = {0,0,0,0};
    }
    else if(id == *idb && rb->right)
    {
        SetWindowPos((HWND)Args, HWND_TOP, 0,0,rb->right,cv.CNTCLWRECT[*idb].bottom,SWP_NOMOVE|SWP_NOZORDER);
        *rb = {0,0,0,0};
    }
    else if(id == *ida && ra->right)
    {
        SetWindowPos((HWND)Args, HWND_TOP, 0,0,ra->right,cv.CNTCLWRECT[*ida].bottom,SWP_NOMOVE|SWP_NOZORDER);
        *ra = {0,0,0,0};
    }
    else if(id == *idMap && rmap->right)
    {
        SetWindowPos((HWND)Args, HWND_TOP, 0,0,rmap->right,rmap->bottom,SWP_NOMOVE|SWP_NOZORDER);
        *rmap = {0,0,0,0};
    }
    else if(id == rgbbtn[0] && rrgb[0].right)
    {
        SetWindowPos((HWND)Args, HWND_TOP, rrgb[0].left,rrgb[0].top,rrgb[0].right,rrgb[0].bottom,SWP_NOMOVE|SWP_NOZORDER);
        InvalidateRect((HWND)Args,0,1);
        rrgb[0] = {0,0,0,0};
    }
    else if(id == rgbbtn[1] && rrgb[1].right)
    {
        SetWindowPos((HWND)Args, HWND_TOP, rrgb[1].left,rrgb[1].top,rrgb[1].right,rrgb[1].bottom,SWP_NOZORDER);
        InvalidateRect((HWND)Args,0,1);
        rrgb[1] = {0,0,0,0};
    }
    else if(id == rgbbtn[2] && rrgb[2].right)
    {
        SetWindowPos((HWND)Args, HWND_TOP, rrgb[2].left,rrgb[2].top,rrgb[2].right,rrgb[2].bottom,SWP_NOZORDER);
        InvalidateRect((HWND)Args,0,1);
        rrgb[2] = {0,0,0,0};
    }
}




void longPress2(csARGS Args)
{
    UINT msg = (UINT)Args;
    int timerid = 1;
    static bool signal=0;

    if(msg == WM_LBUTTONDOWN)
    {
        makeIncrement2(Args);
        signal = 1;
        SetTimer((HWND)Args, timerid, 150, 0);
    }
    if(msg == WM_LBUTTONDBLCLK)
    {
        makeIncrement2(Args);
    }
    else if(msg == WM_LBUTTONUP)
    {
        signal = 0;
        KillTimer(HWND(Args), timerid);
    }
    else if(msg == WM_TIMER && (WPARAM)Args == timerid && signal)
    {
        makeIncrement2(Args);
    }
}
void longPress1(csARGS Args)
{
    UINT msg = (UINT)Args;
    int timerid = 1;
    static bool signal=0;

    if(msg == WM_LBUTTONDOWN)
    {
        makeIncrement1(Args);
        signal = 1;
        SetTimer((HWND)Args, timerid, 150, 0);
    }
    if(msg == WM_LBUTTONDBLCLK)
    {
        makeIncrement1(Args);
    }
    else if(msg == WM_LBUTTONUP)
    {
        signal = 0;
        KillTimer(HWND(Args), timerid);
    }
    else if(msg == WM_TIMER && (WPARAM)Args == timerid && signal)
    {
        makeIncrement1(Args);
    }
}

void setValueFromClick1(csARGS Args)
{
    csINCREMENTER* inc = (csINCREMENTER*)Args[0];


    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient((HWND)Args, &pt);
    if(inc->orientation == CNTR_DISPOSITION_HORIZONTAL)
    {
        if(cv.cp[inc->id4]->MinTrackSize.cx < pt.x)
        {
            GetWindowRect(cv.CNTLIST[inc->id4], &cv.CNTRECT_SAVED[inc->id4]);
            inc->val = 100.0*(pt.x - cv.cp[inc->id4]->MinTrackSize.cx)/inc->maxInclen;
            //-inc.mrg4
            cv.HWNDFOCUS = cv.CNTLIST[inc->id4];
        }
    }
    else
    {
        if(cv.cp[inc->id4]->MinTrackSize.cy < pt.y)
        {
            GetWindowRect(cv.CNTLIST[inc->id4], &cv.CNTRECT_SAVED[inc->id4]);
            inc->val = 100.0*(pt.y - cv.cp[inc->id4]->MinTrackSize.cy)/inc->maxInclen;
            cv.HWNDFOCUS = cv.CNTLIST[inc->id4];
        }
    }

}

void setValueFromClick2(csARGS Args)
{
    csINCREMENTER* inc = (csINCREMENTER*)Args[0];

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(cv.CNTLIST[inc->id3], &pt);

    if(inc->orientation == CNTR_DISPOSITION_HORIZONTAL)
    {
        if(cv.cp[inc->id4]->MinTrackSize.cx < pt.x)
        {
            GetWindowRect(cv.CNTLIST[inc->id4], &cv.CNTRECT[inc->id4]);
            GetWindowRect(cv.CNTLIST[inc->id4], &cv.CNTRECT_SAVED[inc->id4]);
            inc->val = 100.0*(pt.x - cv.cp[inc->id4]->MinTrackSize.cx)/inc->maxInclen;
            //-inc.mrg4
            cv.HWNDFOCUS = cv.CNTLIST[inc->id4];
        }
    }
    else
    {
        if(cv.cp[inc->id4]->MinTrackSize.cy < pt.y)
        {
            GetWindowRect(cv.CNTLIST[inc->id4], &cv.CNTRECT[inc->id4]);
            GetWindowRect(cv.CNTLIST[inc->id4], &cv.CNTRECT_SAVED[inc->id4]);
            inc->val = 100.0*(pt.y - cv.cp[inc->id4]->MinTrackSize.cy)/inc->maxInclen;
            cv.HWNDFOCUS = cv.CNTLIST[inc->id4];
        }
    }

}

void mouseWheelSizing(csARGS Args)
{
    csINCREMENTER* inc = (csINCREMENTER*)Args[0];
    //GetWindowRect(cv.CNTLIST[inc->id4], &cv.CNTRECT[inc->id4]);
    GetWindowRect(cv.CNTLIST[inc->id4], &cv.CNTRECT_SAVED[inc->id4]);
    cv.HWNDFOCUS = cv.CNTLIST[inc->id4];// dont use csSetFocus()!

    cv.cp[inc->id4]->AutoTransform.EmergencyStop = 1;//stop preview animation

    if(GET_WHEEL_DELTA_WPARAM(WPARAM(Args))<0)
    {
        inc->wheelCumulStep1 += inc->stepVal;
        /*float a = inc->val - inc->stepVal;
        inc->val = (a > 0.0) ? a : 0.0;*/
    }
    else
    {
        inc->wheelCumulStep2 += inc->stepVal;
        /*float a = inc->val + inc->stepVal;
        inc->val = (a < 100.0) ? a : 100.0;*/
    }
    SendMessage(cv.CNTLIST[inc->id4], WM_TIMER, 0,0);
}

void keyDownIncrement(csARGS Args)
{
    csINCREMENTER* inc = (csINCREMENTER*)Args[0];
    WPARAM wp = WPARAM(Args);
    if(wp == VK_LEFT || wp == VK_DOWN)
    {
        HWND hwnd = csHWND(inc->id1);
        SendMessage(hwnd, WM_LBUTTONDOWN, 0,0);
        SendMessage(hwnd, WM_LBUTTONUP, 0,0);
        SendMessage(hwnd, WM_MOUSELEAVE, 0,0);
    }
    else if(wp == VK_UP || wp == VK_RIGHT)
    {
        HWND hwnd = csHWND(inc->id2);
        SendMessage(hwnd, WM_LBUTTONDOWN, 0,0);
        SendMessage(hwnd, WM_LBUTTONUP, 0,0);
        SendMessage(hwnd, WM_MOUSELEAVE, 0,0);
    }
}



_RGB HSLToRGB(HSL hsl) {
    double c = ((1.0 - std::fabs(2.0 * hsl.l - 1.0)) * hsl.s);
    double x = (c * (1.0 - std::fabs(fmod(hsl.h / 60.0, 2.0) - 1.0)));
    double m = (hsl.l - c / 2.0);
    double r, g, b;

    if (hsl.h >= 0 && hsl.h < 60) {
        r = c;
        g = x;
        b = 0;
    } else if (hsl.h >= 60 && hsl.h < 120) {
        r = x;
        g = c;
        b = 0;
    } else if (hsl.h >= 120 && hsl.h < 180) {
        r = 0;
        g = c;
        b = x;
    } else if (hsl.h >= 180 && hsl.h < 240) {
        r = 0;
        g = x;
        b = c;
    } else if (hsl.h >= 240 && hsl.h < 300) {
        r = x;
        g = 0;
        b = c;
    } else {
        r = c;
        g = 0;
        b = x;
    }

    _RGB rgb;
    rgb.r = (r + m);
    rgb.g = (g + m);
    rgb.b = (b + m);
    return rgb;
}


HSL RGBtoHSL(_RGB rgb) {
    double r = rgb.r;
    double g = rgb.g;
    double b = rgb.b;

    double max = std::max(r, std::max(g, b));
    double min = std::min(r, std::min(g, b));
    double delta = max - min;

    double h = 0.0;
    double s = 0.0;
    double l = (max + min) / 2.0;

    if (delta != 0.0) {
        s = (l > 0.5) ? delta / (2.0 - max - min) : delta / (max + min);

        if (max == r) {
            h = (g - b) / delta + (g < b ? 6.0 : 0.0);
        } else if (max == g) {
            h = (b - r) / delta + 2.0;
        } else if (max == b) {
            h = (r - g) / delta + 4.0;
        }

        h /= 6.0;
    }

    return HSL{h * 360.0, s , l};
}

