#include "csRULER.h"

csRULER::csRULER(SIZE _size, bool _style, double _first, double _outdx,
        unsigned _unit, unsigned _dx, unsigned _DX)
{
    size = _size;
    if(size.cx > size.cy)
        orient = CS_RULER_HORIZONTAL;
    else
        orient = CS_RULER_VERTICAL;
        
    style = _style;
    first = _first;
    outdx = _outdx;
    unit = _unit;
    dx = _dx;
    DX = _DX;
    l1 = 4;
    l2 = 8;

    goto dark;

    light :
    {
        bkgCol = {100,100,100};
        brdCol = {100,100,100};
        linesCol1 = {10,10,10};
        linesCol2 = {0,0,0};
        textCol = {0,0,0};
    }

    dark:
    {
        bkgCol = {30,30,30};
        brdCol = {25,25,25};
        linesCol1 = {150,150,150};
        linesCol2 = {200,200,200};
        textCol = {150,150,150};
    }

    rulerDC = csNewDC({size.cx, size.cy});

    HDC dc = rulerDC.dc;
    HBRUSH hbr = CreateSolidBrush(RGB(bkgCol.r, bkgCol.g, bkgCol.b));
    HPEN hpn = CreatePen(0,1,RGB(brdCol.r, brdCol.g, brdCol.b));
    SelectBrush(dc, hbr);
    SelectPen(dc, hpn);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc,RGB(textCol.r,textCol.g,textCol.b));
    
    Rectangle(dc,0,0,size.cx,size.cy);

    DeleteBrush(hbr);
    DeletePen(hpn);

    char str[20];

    int d = dx*DX, od = outdx*DX;
    int n = size.cx/dx, n2 = n*2;
    int N = size.cx/d, N2 = N*2;

    if(orient == CS_RULER_VERTICAL)
    {
        n = size.cy/dx; n2 = n*2;
        N = size.cy/d; N2 = N*2;
    }

    POINT pts[n2];
    POINT pts2[N2];
    unsigned long sz[n], sz2[N];
    POLYTEXTW ppt[N];
    if(orient == CS_RULER_VERTICAL)
    {
        
        hf = CreateFontA(csGetAdjustedFontSizeX(12),0,-900, 0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                          OUT_OUTLINE_PRECIS, CLIP_MASK, DEFAULT_QUALITY,
                          VARIABLE_PITCH, (LPCSTR)"Calibri");
        SelectFont(dc, hf);

        char str[10];
        if(style == CS_RULER_TEXT_UNDER)
        {
            for(int i=0; i<n2; i+=2)
            {
                pts[i] = {0, i*dx};
                pts[i+1] = {l1, i*dx};
                sz[i/2] = 2;
            }
            for(int i=0; i<N2; i+=2)
            {
                int j = i*d;
                pts2[i] = {0, j};
                pts2[i+1] = {l2, j};
                sz2[i/2] = 2;
                sprintf(str,"%.0lf",(double)first + i*od);
                LPSIZE lps = csTextExtent(0,hf,str);
                TextOutA(dc,l2+lps->cy,j-lps->cx/2,LPCSTR(str),strlen(str));
                free(lps);
            }
        }
        else
        {
            for(int i=0; i<n2; i+=2)
            {
                pts[i] = {size.cx, i*dx};
                pts[i+1] = {size.cx-l1, i*dx};
                sz[i/2] = 2;
            }
            for(int i=0; i<N2; i+=2)
            {
                int j = i*d;
                pts2[i] = {size.cx, j};
                pts2[i+1] = {size.cx-l2, j};
                sz2[i/2] = 2;

                sprintf(str,"%.0lf",(double)first + i*od);
                LPSIZE lps = csTextExtent(0,hf,str);
                TextOutA(dc,lps->cy,j-lps->cx/2,LPCSTR(str),strlen(str));
                free(lps);
            }
        }
        DeleteFont(hf);
        
    }
    else
    {
        hf = CreateFontA(csGetAdjustedFontSizeX(12),0,0, 0,FW_THIN,FALSE,FALSE,FALSE,ANSI_CHARSET,
                          OUT_OUTLINE_PRECIS, CLIP_MASK, DEFAULT_QUALITY,
                          VARIABLE_PITCH, (LPCSTR)"Calibri");
        SelectFont(dc, hf);

        if(style == CS_RULER_TEXT_UNDER)
        {
            for(int i=0; i<n2; i+=2)
            {
                pts[i] = {i*dx, 0};
                pts[i+1] = {i*dx, l1};
                sz[i/2] = 2;
            }
            for(int i=0; i<N2; i+=2)
            {
                int j = i*d;
                pts2[i] = {j, 0};
                pts2[i+1] = {j, l2};
                sz2[i/2] = 2;

                sprintf(str,"%.0lf",(double)first + i*od);
                LPSIZE lps = csTextExtent(0,hf,str);
                TextOutA(dc,j-lps->cx/2, l2,LPCSTR(str),strlen(str));
                free(lps);
            }
        }
        else
        {
            for(int i=0; i<n2; i+=2)
            {
                pts[i] = {i*dx, size.cy};
                pts[i+1] = {i*dx, size.cy-l1};
                sz[i/2] = 2;
            }
            for(int i=0; i<N2; i+=2)
            {
                int j = i*d;
                pts2[i] = {j, size.cy};
                pts2[i+1] = {j, size.cy-l2};
                sz2[i/2] = 2;

                sprintf(str,"%.0lf",(double)first + i*od);
                LPSIZE lps = csTextExtent(0,hf,str);
                TextOutA(dc,j-lps->cx/2, 0,LPCSTR(str),strlen(str));
                free(lps);
            }
        }
        DeleteFont(hf);
    }
    
    hpn = CreatePen(0,1,RGB(linesCol1.r, linesCol1.g, linesCol1.b));
    SelectPen(dc,hpn);
    PolyPolyline(dc,(const POINT*)pts, (const DWORD*)sz, n);
    DeletePen(hpn);

    hpn = CreatePen(0,1,RGB(linesCol2.r, linesCol2.g, linesCol2.b));
    SelectPen(dc,hpn);
    PolyPolyline(dc,(const POINT*)pts2, (const DWORD*)sz2, N);
    DeletePen(hpn);
    //ctor
}

HDC csRULER::getDC()
{
    return rulerDC.dc;
}
SIZE csRULER::getSize()
{
    return size;
}
POINT csRULER::getPos()
{
    return pos;
}
bool csRULER::getOrientation()
{
    return orient;
}

void csRULER::place(HDC dc, POINT p)
{
    BitBlt(dc,p.x,p.y,size.cx,size.cy, rulerDC.dc, 0,0,SRCCOPY);
    pos = p;
}

csRULER::~csRULER()
{
    //dtor
}


