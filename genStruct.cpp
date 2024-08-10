#include "genStruct.h"
#include "csCONTAINER.h"
#include <math.h>

extern csCNTR_VARS cv;

csARGS::csARGS(unsigned int _nbArgs)
{
    Args = 0;
    nbArgs = _nbArgs;
    Args = (void**)malloc(sizeof(void*)*(nbArgs+5));
};
void* csARGS::getArg(unsigned int i)
{
    return Args[i+5];
}
void* csARGS::getHwnd()
{
    return Args[0];
}
void* csARGS::getMessage()
{
    return Args[1];
}
void* csARGS::getWParam()
{
    return Args[2];
}
void* csARGS::getLParam()
{
    return Args[3];
}
void* csARGS::getLID()
{
    return Args[4];
}
void csARGS::setProcParams(HWND* hwnd, UINT* msg, WPARAM* wp, LPARAM* lp, int*id)
{
    Args[0]=(void*)hwnd;
    Args[1]=(void*)msg;
    Args[2]=(void*)wp;
    Args[3]=(void*)lp;
    Args[4]=(void*)id;
}

int csARGS::getArgNumber()
{
    return nbArgs;
}

void csARGS::setArg(unsigned int i, void*arg)
{
    //free(Args[i+4]);
    Args[i+5]=arg;
}
void csARGS::setId(void*id)
{
    //free(Args[i+4]);
    Args[4]=id;
}
void csARGS::setHwnd(void*hwnd)
{
    //free(Args[i+4]);
    Args[0]=hwnd;
}
void csARGS::setArg_int(unsigned int i, int arg)
{
    static int a = 0;
    a=arg;
    Args[i+5]=(void*)&a;
}

void csARGS::setArgNumber(unsigned int _nbArgs)
{
    nbArgs = _nbArgs;
    int m = nbArgs + 5;
    Args = (void**)realloc(Args, m*sizeof(void*));
}
/*void csARGS::setArg(unsigned int i, void*arg)
{
    Args[i+4][0]=arg[0];
}*/

void csARGS::makeArgs(...)
{
    va_list adArgs ;
    void* parv;
    va_start (adArgs, nbArgs);
    HWND hwnd=0;
    UINT msg=0;
    WPARAM wp=0;
    LPARAM lp=0;
    int id =0;
    Args[0]=(void*)&hwnd;
    Args[1]=(void*)&msg;
    Args[2]=(void*)&wp;
    Args[3]=(void*)&lp;
    Args[4]=(void*)&id;
    for (int i=0 ; i<nbArgs ; i++)
    {
        parv = va_arg (adArgs, void*) ;
        Args[i+5]=parv;
    }
}
void csARGS::makeArgs2(void**args, int nbArgs)
{
    HWND hwnd=0;
    UINT msg=0;
    WPARAM wp=0;
    LPARAM lp=0;
    int id=0;
    Args[0]=(void*)&hwnd;
    Args[1]=(void*)&msg;
    Args[2]=(void*)&wp;
    Args[3]=(void*)&lp;
    Args[4]=(void*)&id;
    for (int i=0 ; i<nbArgs ; i++)
    {
        Args[i+5]=args[i];
    }
}

void csARGS::freeArgs()
{
    free(Args);
    Args = 0;
}

bool csSetAction(int id, UINT message, void(*fx)(csARGS), int nbArgs, ...)
{
    bool b = 1;
    va_list adArgs ;
    void* parv;
    void*args[nbArgs]={NULL};
    va_start (adArgs, nbArgs);
    for (int i=0 ; i<nbArgs ; i++)
    {
        parv = va_arg (adArgs, void*) ;
        args[i]=parv;
    }

    csARGS Args(nbArgs);
    Args.makeArgs2(args, nbArgs);
    switch (message)
    {
        case WM_LBUTTONDOWN:
            cv.cp[id]->CntEventsFunc.LBUTTONDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.LBUTTONDOWN_ARGS.insertEnd(Args);
            break;
        case WM_NCLBUTTONDOWN:
            cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN_ARGS.insertEnd(Args);
            break;
        case WM_RBUTTONDOWN:
            cv.cp[id]->CntEventsFunc.RBUTTONDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.RBUTTONDOWN_ARGS.insertEnd(Args);
            break;
        case WM_NCRBUTTONDOWN:
            cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN_ARGS.insertEnd(Args);
            break;
        case WM_MBUTTONDOWN:
            cv.cp[id]->CntEventsFunc.MBUTTONDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MBUTTONDOWN_ARGS.insertEnd(Args);
            break;
        case WM_NCMBUTTONDOWN:
            cv.cp[id]->CntEventsFunc.NCMBUTTONDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCMBUTTONDOWN_ARGS.insertEnd(Args);
            break;
        case WM_LBUTTONUP:
            cv.cp[id]->CntEventsFunc.LBUTTONUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.LBUTTONUP_ARGS.insertEnd(Args);
            break;
        case WM_NCLBUTTONUP:
            cv.cp[id]->CntEventsFunc.NCLBUTTONUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCLBUTTONUP_ARGS.insertEnd(Args);
            break;
        case WM_RBUTTONUP:
            cv.cp[id]->CntEventsFunc.RBUTTONUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.RBUTTONUP_ARGS.insertEnd(Args);
            break;
        case WM_NCRBUTTONUP:
            cv.cp[id]->CntEventsFunc.NCRBUTTONUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCRBUTTONUP_ARGS.insertEnd(Args);
            break;
        case WM_MBUTTONUP:
            cv.cp[id]->CntEventsFunc.MBUTTONUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MBUTTONUP_ARGS.insertEnd(Args);
            break;
        case WM_NCMBUTTONUP:
            cv.cp[id]->CntEventsFunc.NCMBUTTONUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCMBUTTONUP_ARGS.insertEnd(Args);
            break;
        case WM_LBUTTONDBLCLK:
            cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK_ARGS.insertEnd(Args);
            break;
        case WM_NCLBUTTONDBLCLK:
            cv.cp[id]->CntEventsFunc.NCLBUTTONDBLCLK.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCLBUTTONDBLCLK_ARGS.insertEnd(Args);
            break;
        case WM_RBUTTONDBLCLK:
            cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK_ARGS.insertEnd(Args);
            break;
        case WM_NCRBUTTONDBLCLK:
            cv.cp[id]->CntEventsFunc.NCRBUTTONDBLCLK.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCRBUTTONDBLCLK_ARGS.insertEnd(Args);
            break;
        case WM_MBUTTONDBLCLK:
            cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK_ARGS.insertEnd(Args);
            break;
        case WM_NCMBUTTONDBLCLK:
            cv.cp[id]->CntEventsFunc.NCMBUTTONDBLCLK.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCMBUTTONDBLCLK_ARGS.insertEnd(Args);
            break;
        case WM_MOUSEMOVE:
            cv.cp[id]->CntEventsFunc.MOUSEMOVE.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MOUSEMOVE_ARGS.insertEnd(Args);
            break;
        case WM_MOUSEHOVER:
            cv.cp[id]->CntEventsFunc.MOUSEHOVER.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MOUSEHOVER_ARGS.insertEnd(Args);
            break;
        case WM_MOUSELEAVE:
            cv.cp[id]->CntEventsFunc.MOUSELEAVE.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MOUSELEAVE_ARGS.insertEnd(Args);
            break;
        case WM_MOUSEWHEEL:
            cv.cp[id]->CntEventsFunc.MOUSEWHEEL.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MOUSEWHEEL_ARGS.insertEnd(Args);
            break;
        case WM_MOVE:
            cv.cp[id]->CntEventsFunc.MOVE.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MOVE_ARGS.insertEnd(Args);
            break;
        case WM_SIZE:
            cv.cp[id]->CntEventsFunc.SIZE.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.SIZE_ARGS.insertEnd(Args);
            break;
        case WM_SETFOCUS:
            cv.cp[id]->CntEventsFunc.SETFOCUS.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.SETFOCUS_ARGS.insertEnd(Args);
            break;
        case WM_CREATE:
            cv.cp[id]->CntEventsFunc.CREATE.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.CREATE_ARGS.insertEnd(Args);
            break;
        case WM_DESTROY:
            cv.cp[id]->CntEventsFunc.DESTROY.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.DESTROY_ARGS.insertEnd(Args);
            break;
        case WM_TIMER:
            cv.cp[id]->CntEventsFunc.TIMER.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.TIMER_ARGS.insertEnd(Args);
            break;
        case WM_NCHITTEST:
            cv.cp[id]->CntEventsFunc.NCHITTEST.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCHITTEST_ARGS.insertEnd(Args);
            break;
        case WM_ERASEBKGND:
            cv.cp[id]->CntEventsFunc.ERASEBKGND.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.ERASEBKGND_ARGS.insertEnd(Args);
            break;
        case WM_KEYUP:
            cv.cp[id]->CntEventsFunc.KEYUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.KEYUP_ARGS.insertEnd(Args);
            break;
        case WM_KEYDOWN:
            cv.cp[id]->CntEventsFunc.KEYDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.KEYDOWN_ARGS.insertEnd(Args);
            break;
        case WM_SYSCOMMAND:
            cv.cp[id]->CntEventsFunc.SYSCOMMAND.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.SYSCOMMAND_ARGS.insertEnd(Args);
            break;
        default:
            b=0;
    }
    if (b==0)
        std::cout<<"Window event message '"<<message<<"' not supported !\n";
    return b;
}

bool csSetAction(int id, UINT message, void(*fx)(csARGS), csARGS& Args)
{
    bool b=1;
    switch (message)
    {
        case WM_LBUTTONDOWN:
            cv.cp[id]->CntEventsFunc.LBUTTONDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.LBUTTONDOWN_ARGS.insertEnd(Args);
            break;
        case WM_NCLBUTTONDOWN:
            cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN_ARGS.insertEnd(Args);
            break;
        case WM_RBUTTONDOWN:
            cv.cp[id]->CntEventsFunc.RBUTTONDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.RBUTTONDOWN_ARGS.insertEnd(Args);
            break;
        case WM_NCRBUTTONDOWN:
            cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN_ARGS.insertEnd(Args);
            break;
        case WM_MBUTTONDOWN:
            cv.cp[id]->CntEventsFunc.MBUTTONDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MBUTTONDOWN_ARGS.insertEnd(Args);
            break;
        case WM_NCMBUTTONDOWN:
            cv.cp[id]->CntEventsFunc.NCMBUTTONDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCMBUTTONDOWN_ARGS.insertEnd(Args);
            break;
        case WM_LBUTTONUP:
            cv.cp[id]->CntEventsFunc.LBUTTONUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.LBUTTONUP_ARGS.insertEnd(Args);
            break;
        case WM_NCLBUTTONUP:
            cv.cp[id]->CntEventsFunc.NCLBUTTONUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCLBUTTONUP_ARGS.insertEnd(Args);
            break;
        case WM_RBUTTONUP:
            cv.cp[id]->CntEventsFunc.RBUTTONUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.RBUTTONUP_ARGS.insertEnd(Args);
            break;
        case WM_NCRBUTTONUP:
            cv.cp[id]->CntEventsFunc.NCRBUTTONUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCRBUTTONUP_ARGS.insertEnd(Args);
            break;
        case WM_MBUTTONUP:
            cv.cp[id]->CntEventsFunc.MBUTTONUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MBUTTONUP_ARGS.insertEnd(Args);
            break;
        case WM_NCMBUTTONUP:
            cv.cp[id]->CntEventsFunc.NCMBUTTONUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCMBUTTONUP_ARGS.insertEnd(Args);
            break;
        case WM_LBUTTONDBLCLK:
            cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK_ARGS.insertEnd(Args);
            break;
        case WM_NCLBUTTONDBLCLK:
            cv.cp[id]->CntEventsFunc.NCLBUTTONDBLCLK.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCLBUTTONDBLCLK_ARGS.insertEnd(Args);
            break;
        case WM_RBUTTONDBLCLK:
            cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK_ARGS.insertEnd(Args);
            break;
        case WM_NCRBUTTONDBLCLK:
            cv.cp[id]->CntEventsFunc.NCRBUTTONDBLCLK.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCRBUTTONDBLCLK_ARGS.insertEnd(Args);
            break;
        case WM_MBUTTONDBLCLK:
            cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK_ARGS.insertEnd(Args);
            break;
        case WM_NCMBUTTONDBLCLK:
            cv.cp[id]->CntEventsFunc.NCMBUTTONDBLCLK.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCMBUTTONDBLCLK_ARGS.insertEnd(Args);
            break;
        case WM_MOUSEMOVE:
            cv.cp[id]->CntEventsFunc.MOUSEMOVE.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MOUSEMOVE_ARGS.insertEnd(Args);
            break;
        case WM_MOUSEHOVER:
            cv.cp[id]->CntEventsFunc.MOUSEHOVER.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MOUSEHOVER_ARGS.insertEnd(Args);
            break;
        case WM_MOUSELEAVE:
            cv.cp[id]->CntEventsFunc.MOUSELEAVE.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MOUSELEAVE_ARGS.insertEnd(Args);
            break;
        case WM_MOUSEWHEEL:
            cv.cp[id]->CntEventsFunc.MOUSEWHEEL.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MOUSEWHEEL_ARGS.insertEnd(Args);
            break;
        case WM_MOVE:
            cv.cp[id]->CntEventsFunc.MOVE.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.MOVE_ARGS.insertEnd(Args);
            break;
        case WM_SIZE:
            cv.cp[id]->CntEventsFunc.SIZE.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.SIZE_ARGS.insertEnd(Args);
            break;
        case WM_SETFOCUS:
            cv.cp[id]->CntEventsFunc.SETFOCUS.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.SETFOCUS_ARGS.insertEnd(Args);
            break;
        case WM_CREATE:
            cv.cp[id]->CntEventsFunc.CREATE.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.CREATE_ARGS.insertEnd(Args);
            break;
        case WM_DESTROY:
            cv.cp[id]->CntEventsFunc.DESTROY.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.DESTROY_ARGS.insertEnd(Args);
            break;
        case WM_TIMER:
            cv.cp[id]->CntEventsFunc.TIMER.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.TIMER_ARGS.insertEnd(Args);
            break;
        case WM_NCHITTEST:
            cv.cp[id]->CntEventsFunc.NCHITTEST.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.NCHITTEST_ARGS.insertEnd(Args);
            break;
        case WM_ERASEBKGND:
            cv.cp[id]->CntEventsFunc.ERASEBKGND.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.ERASEBKGND_ARGS.insertEnd(Args);
            break;
        case WM_KEYUP:
            cv.cp[id]->CntEventsFunc.KEYUP.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.KEYUP_ARGS.insertEnd(Args);
            break;
        case WM_KEYDOWN:
            cv.cp[id]->CntEventsFunc.KEYDOWN.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.KEYDOWN_ARGS.insertEnd(Args);
            break;
        case WM_SYSCOMMAND:
            cv.cp[id]->CntEventsFunc.SYSCOMMAND.insertEnd(fx);
            cv.cp[id]->CntEventsFunc.SYSCOMMAND_ARGS.insertEnd(Args);
            break;
        default:
            b=0;
    }
    //cv.cp[id]->CntEventsFunc = cv.cp[id]->CntEventsFunc;
    if (b==0)
        std::cout<<"Window event message '"<<message<<"' not supported !\n";
    return b;
}

bool csSetGroupedAction(int id, void(*f)(csARGS), csARGS args)
{
    cv.GROUPED_EVENTS_FUNC[id].insertEnd(f);
    cv.GROUPED_EVENTS_ARGS[id].insertEnd(args);
    return 1;
}

csBMP csBitmapFromFile(char*path, BITMAPINFO*bmi)
{
    csBMP bmp;
    bmp.hbmp=(HBITMAP)LoadImageA(NULL,path,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    GetObjectA((HGDIOBJ)bmp.hbmp,sizeof(bmp.bm),(PVOID)&bmp.bm);
    char*buf0 = (char*)bmp.bm.bmBits;
    HDC dc=GetDC(0);
    bmp.dc=CreateCompatibleDC(dc);
    SelectBitmap(bmp.dc,bmp.hbmp);
    /*DrawStateA(bmp.dc,NULL,NULL,
               (long long)bmp.hbmp,NULL,0,0,0,0,DST_BITMAP);*/
    bmp.bm.bmBits = (LPVOID)malloc(bmi->bmiHeader.biSizeImage*sizeof(void));
    int bres = GetDIBits(bmp.dc,bmp.hbmp,0,bmp.bm.bmHeight,bmp.bm.bmBits,bmi,DIB_RGB_COLORS);
    ReleaseDC(0,dc);
    return bmp;
}

HDC csLoadImage(char*path, csSIZE2 size, SIZE*retSize)
{
    HDC rdc=0;
    if(path && strlen(path))
    {
        HDC dc=GetDC(0);
        csBMP bmp;
        bmp.hbmp=(HBITMAP)LoadImageA(NULL,path,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
        GetObjectA((HGDIOBJ)bmp.hbmp,sizeof(bmp.bm),(PVOID)&bmp.bm);
        bmp.dc=CreateCompatibleDC(dc);
        SelectBitmap(bmp.dc,bmp.hbmp);
        /*DrawStateA(bmp.dc,NULL,NULL,
                (long long)bmp.hbmp,NULL,0,0,0,0,DST_BITMAP);*/
        
        HBITMAP bm;
        rdc=CreateCompatibleDC(dc);
        if(size.height  < 0 || size.width < 0)
        {
            if(retSize)
                *retSize = {bmp.bm.bmWidth,bmp.bm.bmHeight};
            bm=CreateCompatibleBitmap(dc, bmp.bm.bmWidth, bmp.bm.bmHeight);
            SelectBitmap(rdc,bm);
            BitBlt(rdc,0,0, bmp.bm.bmWidth, bmp.bm.bmHeight,bmp.dc,0,0,SRCCOPY);
            
        }
        else
        {
            bm=CreateCompatibleBitmap(dc, size.width, size.height);
            SelectBitmap(rdc,bm);
            SetStretchBltMode(rdc,HALFTONE);
            StretchBlt(rdc,0,0, size.width, size.height,bmp.dc,0,0,bmp.bm.bmWidth, bmp.bm.bmHeight,SRCCOPY);
        }
        freeBMP(bmp);
        DeleteBitmap(bm);
        ReleaseDC(0,dc);
    }
    else if(retSize)
                *retSize = {0,0};
    return rdc;
}

BITMAPINFO csSetBMI(csSIZE sz)
{
    BITMAPINFO bi;
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = sz.width;
    bi.bmiHeader.biHeight = -sz.height;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    bi.bmiHeader.biSizeImage = sz.width * 4 * sz.height;
    bi.bmiHeader.biClrUsed = 0;
    bi.bmiHeader.biClrImportant = 0;
    return bi;
}

csBMP csBitmap(csSIZE sz, BITMAPINFO*bmi)
{
    csBMP bmp;
    csDC  ndc = csNewDC(sz);
    bmp.dc = ndc.dc;
    bmp.hbmp = ndc.hbmp;
    GetObjectA((HGDIOBJ)bmp.hbmp,sizeof(bmp.bm),(PVOID)&bmp.bm);
    bmp.bm.bmBits = (LPVOID)malloc(bmi->bmiHeader.biSizeImage*sizeof(void));
    int bres = GetDIBits(bmp.dc,bmp.hbmp,0,bmp.bm.bmHeight,bmp.bm.bmBits,bmi,DIB_RGB_COLORS);
    return bmp;
}

csDC csNewDC(csSIZE sz)
{
    csDC dc;
    HDC hdc = GetDC(0);
    dc.dc=CreateCompatibleDC(hdc);
    dc.hbmp = CreateCompatibleBitmap(hdc, sz.width, sz.height);
    SelectBitmap(dc.dc,dc.hbmp);
    /*DrawStateA(dc.dc,NULL,NULL,
               (long long)dc.hbmp,NULL,0,0,0,0,DST_BITMAP);*/
    ReleaseDC(0,hdc);
    dc.sz = sz;
    return dc;
}
csDC csNewCompatibleDC(HDC hdc, csSIZE sz, COLORREF bkgCol)
{
    csDC dc;
    dc.dc=CreateCompatibleDC(hdc);
    dc.hbmp = CreateCompatibleBitmap(hdc, sz.width, sz.height);
    SelectBitmap(dc.dc,dc.hbmp);
    HBRUSH brush = CreateSolidBrush(bkgCol);
    SelectBrush(dc.dc, brush);
    HPEN hp = CreatePen(0,1,bkgCol);
    SelectPen(dc.dc,hp);
    Rectangle(dc.dc,0,0,sz.width,sz.height);
    dc.sz = sz;
    DeleteBrush(brush);
    DeletePen(hp);
    return dc;
}

void csFreeDC(csDC dc)
{
    DeleteDC(dc.dc);
    DeleteObject(dc.hbmp);
    dc.sz = {0,0};
}

void freeBMP(csBMP bmp)
{
    DeleteDC(bmp.dc);
    DeleteObject(bmp.hbmp);
    free(bmp.bm.bmBits);
}

csDC csGetImgBits(char*path, csSIZE sz)
{
    csDC dc;
    BITMAPINFO bmi = csSetBMI(sz);
    csBMP bmp1 = csBitmapFromFile(path, &bmi);
    csBMP fbmp1 = csBitmap(sz, &bmi);

    SetStretchBltMode(fbmp1.dc, HALFTONE);
    //TransparentBlt(fbmp1.dc, 0,0,sz.width, sz.height, bmp1.dc, 0,0,bmp1.bm.bmWidth,bmp1.bm.bmHeight,SRCCOPY);
    StretchBlt(fbmp1.dc, 0,0,sz.width, sz.height, bmp1.dc, 0,0,bmp1.bm.bmWidth,bmp1.bm.bmHeight,SRCCOPY);
    dc.dc = fbmp1.dc;
    dc.hbmp = fbmp1.hbmp;
    dc.sz = sz;
    freeBMP(bmp1);
    return dc;
}

csLIST<csDC> getImgColGrad(char*path,csRGBA colRem, csSIZE sz, BYTE transl, unsigned int n)
{
    csLIST<csDC> dcs;
    BITMAPINFO bmi = csSetBMI(sz);
    csBMP bmp1 = csBitmapFromFile(path, &bmi);
    //std::cout<<((char*)(bmp1.bm.bmBits))[0];
    csBMP fbmp1 = csBitmap(sz, &bmi);

    SetStretchBltMode(fbmp1.dc, HALFTONE);
    StretchBlt(fbmp1.dc, 0,0,sz.width, sz.height, bmp1.dc, 0,0,bmp1.bm.bmWidth,bmp1.bm.bmHeight,SRCCOPY);
    GetDIBits(fbmp1.dc,fbmp1.hbmp,0,fbmp1.bm.bmHeight,fbmp1.bm.bmBits,&bmi,DIB_RGB_COLORS);

    char*buf1 = (char*)fbmp1.bm.bmBits;

    long lval=0,nCount=0;
    BYTE r, g, b, t;
    float dx = (float)transl/(n-1);
    for (int k=0; k<n; k++)
    {
        csDC ndc;
        csBMP mbmp = csBitmap(sz, &bmi);
        char*buf = (char*)mbmp.bm.bmBits;
        t=k*dx;
        for (int j=0; j<sz.height; j++)
        {
            for (int i=0; i<sz.width; i++)
            {
                nCount=(j*sz.width+i)*4;
                r = BYTE(buf1[nCount]) + t;
                g = BYTE(buf1[nCount+1]) + t;
                b = BYTE(buf1[nCount+2]) + t;
                if(r<=255 && g<=255 && b<=255)
                {
                    buf[nCount] = r;
                    buf[nCount+1] = g;
                    buf[nCount+2] = b;
                }
                else
                {
                    buf[nCount] = buf1[nCount];
                    buf[nCount+1] = buf1[nCount+1];
                    buf[nCount+2] = buf1[nCount+2];
                }
                //std::cout<<r<<"  ";
            }
        }
        SetDIBits(mbmp.dc, mbmp.hbmp, 0, sz.height, buf,  &bmi, DIB_RGB_COLORS);
        //StretchBlt(GetDC(0), 0,0,sz.width, sz.height, mbmp.dc, 0,0,mbmp.bm.bmWidth,mbmp.bm.bmHeight,SRCCOPY);
        free(buf);
        ndc.dc = mbmp.dc;
        ndc.hbmp = mbmp.hbmp;
        ndc.sz = sz;
        //StretchBlt(GetDC(0), 0,0,sz.width, sz.height, ndc.dc, 0,0,mbmp.bm.bmWidth,mbmp.bm.bmHeight,SRCCOPY);
        dcs.insertEnd(ndc);
        //freeBMP(mbmp);//***************attention***
    }
    freeBMP(bmp1);
    freeBMP(fbmp1);
    return dcs;
}

BYTE interpByte(char b1, char b2, char b3, char b4,float dx, float dy)
{
    //float f = ((1.0-dy)*(1.0-dx)*((BYTE)b1) + dx*(1.0-dy)*((BYTE)b2) + (1.0-dx)*dy*((BYTE)b3) + dx*dy*((BYTE)b4));
    float f = (1.0-dy)*((1.0-dx)*((BYTE)b1) + dx*((BYTE)b2)) + dy*((1-dx)*((BYTE)b3) + dx*((BYTE)b4));
    return (BYTE)f;
}

csLIST<csDC> getImageGradients(char*path1,char*path2, csSIZE sz, unsigned int n, float rotAng, float zoom,
                           csRGBA bkgColor, csRGBA teint, float teintLevel)
{
    csLIST<csDC> dcs;
    BITMAPINFO bmi = csSetBMI(sz);
    csBMP bmp1 = csBitmapFromFile(path1, &bmi);
    csBMP bmp2 = csBitmapFromFile(path2, &bmi);
    //std::cout<<((char*)(bmp1.bm.bmBits))[0];
    csBMP fbmp1 = csBitmap(sz, &bmi);
    csBMP fbmp2 = csBitmap(sz, &bmi);

    SetStretchBltMode(fbmp1.dc, HALFTONE);
    SetStretchBltMode(fbmp2.dc, HALFTONE);
    StretchBlt(fbmp1.dc, 0,0,sz.width, sz.height, bmp1.dc, 0,0,bmp1.bm.bmWidth,bmp1.bm.bmHeight,SRCCOPY);
    StretchBlt(fbmp2.dc, 0,0,sz.width, sz.height, bmp2.dc, 0,0,bmp2.bm.bmWidth,bmp2.bm.bmHeight,SRCCOPY);
    GetDIBits(fbmp1.dc,fbmp1.hbmp,0,fbmp1.bm.bmHeight,fbmp1.bm.bmBits,&bmi,DIB_RGB_COLORS);
    GetDIBits(fbmp2.dc,fbmp2.hbmp,0,fbmp2.bm.bmHeight,fbmp2.bm.bmBits,&bmi,DIB_RGB_COLORS);

    char*buf1 = (char*)fbmp1.bm.bmBits;
    char*buf2 = (char*)fbmp2.bm.bmBits;

    long lval=0,nCount=0, r, g, b, a, szmax=sz.height*sz.width*4;
    float rrat, grat, brat, rat, arat, da, toRad=3.141516/180, xc=sz.width/2, yc=sz.height/2;
    int j0, i0;
    float j0f, i0f, dx, dy;
    long nCount11, nCount12, nCount21, nCount22, nCount0;
    BYTE bi1, bi2;
    for (int k=0; k<n; k++)
    {
        csDC ndc;
        csBMP mbmp = csBitmap(sz, &bmi);
        char*buf = (char*)mbmp.bm.bmBits;
        for (int j=0; j<sz.height; j++)
        {
            for (int i=0; i<sz.width; i++)
            {
                nCount=(j*sz.width+i)*4;
                rat = (float)k/(n-1);
                da = -rotAng*rat*toRad;
                i0 = int(i0f = xc*rat*zoom+(xc+(i-xc)*cos(da)+(j-yc)*sin(da))*(1-rat*zoom));
                j0 = int(j0f = yc*rat*zoom+(yc-(i-xc)*sin(da)+(j-yc)*cos(da))*(1-rat*zoom));
                dx = i0f-i0;
                dy = j0f-j0;
                if(i0==sz.width-1) i0 --;
                else if(i0<0) i0++;
                if(j0==sz.height-1) j0 --;
                else if(j0<0) j0++;

                nCount0=(j0*sz.width+i0)*4;
                nCount11=(j0*sz.width+i0)*4;
                nCount12=(j0*sz.width+(i0+1))*4;
                nCount21=((j0+1)*sz.width+i0)*4;
                nCount22=((j0+1)*sz.width+(i0+1))*4;
                if(nCount0>0&&nCount0<szmax)
                {
                    bi2 = interpByte(buf2[nCount11], buf2[nCount12],buf2[nCount21],buf2[nCount22], dx,dy);
                    bi1 = interpByte(buf1[nCount11], buf1[nCount12],buf1[nCount21],buf1[nCount22], dx,dy);
                    r = (1-rat*teintLevel)*(bi2*rat + bi1*(1-rat)) + rat*teint.r*teintLevel;
                    bi2 = interpByte(buf2[nCount11+1], buf2[nCount12+1],buf2[nCount21+1],buf2[nCount22+1], dx,dy);
                    bi1 = interpByte(buf1[nCount11+1], buf1[nCount12+1],buf1[nCount21+1],buf1[nCount22+1], dx,dy);
                    g = (1-rat*teintLevel)*(bi2*rat + bi1*(1-rat)) + rat*teint.g*teintLevel;
                    bi2 = interpByte(buf2[nCount11+2], buf2[nCount12+2],buf2[nCount21+2],buf2[nCount22+2], dx,dy);
                    bi1 = interpByte(buf1[nCount11+2], buf1[nCount12+2],buf1[nCount21+2],buf1[nCount22+2], dx,dy);
                    b = (1-rat*teintLevel)*(bi2*rat + bi1*(1-rat)) + rat*teint.b*teintLevel;
                    //a = BYTE(buf2[nCount11+3])*(rat) + BYTE(buf1[nCount11+3])*(1-rat);
                }
                else
                {
                    r=bkgColor.r; g=bkgColor.g; b=bkgColor.b;
                }

                buf[nCount] = (BYTE)r;
                buf[nCount+1] = (BYTE)g;
                buf[nCount+2] = (BYTE)b;
                //buf[nCount+3] = (BYTE)a;
                //std::cout<<r<<"  ";
            }
        }
        SetDIBits(mbmp.dc, mbmp.hbmp, 0, sz.height, buf,  &bmi, DIB_RGB_COLORS);
        //StretchBlt(GetDC(0), 0,0,sz.width, sz.height, mbmp.dc, 0,0,mbmp.bm.bmWidth,mbmp.bm.bmHeight,SRCCOPY);
        free(buf);
        ndc.dc = mbmp.dc;
        ndc.hbmp = mbmp.hbmp;
        ndc.sz = sz;
        //StretchBlt(GetDC(0), 0,0,sz.width, sz.height, ndc.dc, 0,0,mbmp.bm.bmWidth,mbmp.bm.bmHeight,SRCCOPY);
        dcs.insertEnd(ndc);
    }
    freeBMP(bmp1);
    freeBMP(bmp2);
    freeBMP(fbmp1);
    freeBMP(fbmp2);
    return dcs;
}

void csBmpToCntSurface(char*path,csSIZE sz, HDC dc)
{
    csLIST<csDC> dcs;
    BITMAPINFO bmi = csSetBMI(sz);
    csBMP bmp = csBitmapFromFile(path, &bmi);

    SetStretchBltMode(dc, HALFTONE);
    if(sz.width!=0 && sz.height!=0)
        StretchBlt(dc, 0,0,sz.width, sz.height, bmp.dc, 0,0,bmp.bm.bmWidth,bmp.bm.bmHeight,SRCCOPY);
    else
        BitBlt(dc, 0,0,bmp.bm.bmWidth,bmp.bm.bmHeight, bmp.dc, 0,0,SRCCOPY);
    freeBMP(bmp);
}

void drawCntTitle(HDC dc, csTEXT Title)
{
    if(Title.Text)
    {
        SetBkMode(dc,TRANSPARENT);
        HFONT hf = CreateFont(csGetAdjustedFontSizeX(Title.FontSize.cx),csGetAdjustedFontSizeY(Title.FontSize.cy), 0, Title.Orientation, Title.Bold,Title.Italic,Title.Underline, 0,0,0,0,0,0, (LPCSTR)Title.Font);
        SelectFont(dc,hf);
        SetTextColor(dc,RGB(Title.Color.r, Title.Color.g,Title.Color.b));
        SetTextAlign(dc, TA_TOP);
        TextOut(dc,0,0,(LPCSTR)Title.Text,strlen(Title.Text));
        DeleteFont(hf);
    }
}

/*void calcrectText()
{
    wchar_t* msg = L"Hello\r\nworld";
    RECT rcMeasure = {0, 0, 400, 0};
    DrawTextEx(hdc, msg, -1, &rcMeasure, DT_CALCRECT, 0);
    RECT rcDraw = {10, 30, 10 + rcMeasure.bottom - rcMeasure.top, 30 + rcMeasure.right - rcMeasure.left };
    FillRect(hdc, &rcDraw, (HBRUSH) (COLOR_WINDOW+2));
    SetTextAlign(hdc, TA_TOP | TA_CENTER);
    DrawTextEx(hdc, msg, -1, &rcDraw, DT_BOTTOM, 0);
}*/

LPSIZE csTextExtent(int idCnt, HFONT font, char*text)
{
    LPSIZE lps=(LPSIZE)malloc(sizeof(LPSIZE));
    HDC dc=GetDC(cv.CNTLIST[idCnt]);
    SelectFont(dc, font);
    GetTextExtentPoint32A(dc, (LPCSTR)text, strlen((LPCSTR)text), lps);
    ReleaseDC(cv.CNTLIST[idCnt], dc);
    return lps;
}
LPSIZE textExtent2(HDC dc, HFONT font, char*text)
{
    LPSIZE lps=(LPSIZE)malloc(sizeof(LPSIZE));
    SelectFont(dc, font);
    GetTextExtentPoint32A(dc, (LPCSTR)text, strlen((LPCSTR)text), lps);
    return lps;
}

void drawCntTitle2(HWND hwnd, HDC dc, csTEXT& Title, RECT rc, int textAlign)
{
    if(Title.Text)
    {
        SetBkMode(dc,TRANSPARENT);
        //csGetAdjustedFontSizeX(Title.FontSize.cx)
        //csGetAdjustedFontSizeY(Title.FontSize.cy);
        //-MulDiv(Title.FontSize.cx,GetDeviceCaps(dc,LOGPIXELSY),72),
        //-MulDiv(Title.FontSize.cy,GetDeviceCaps(dc,LOGPIXELSX),72),
        /*HFONT hf = CreateFont(csGetAdjustedFontSizeX(Title.FontSize.cx),
                                csGetAdjustedFontSizeY(Title.FontSize.cy),
        Title.Orientation, 0, Title.Bold,Title.Italic,Title.Underline, 0,0,OUT_OUTLINE_PRECIS,0,ANTIALIASED_QUALITY,
        0, (LPCSTR)Title.Font);*/

        HFONT hf = CreateFont(csGetAdjustedFontSizeX(Title.FontSize.cx),
                              csGetAdjustedFontSizeY(Title.FontSize.cy),
                                Title.Orientation, 0, Title.Bold,Title.Italic,Title.Underline,0,ANSI_CHARSET,
                            OUT_OUTLINE_PRECIS,CLIP_STROKE_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH|FF_SWISS, (LPCSTR)Title.Font);
        SelectFont(dc,hf);
        SetTextColor(dc,RGB(Title.Color.r, Title.Color.g,Title.Color.b));
        //SetTextAlign(dc, textAlign);
        int b = (Title.FontSize.cy>0)?Title.FontSize.cy:Title.FontSize.cx;

        //TextOut(dc,rc.right/2,(rc.bottom-b)/2,(LPCSTR)Title.Text,strlen(Title.Text));
        LPSIZE lps = textExtent2(dc, hf, Title.Text);
        /*if(Title.Orientation == -900)
        {
            Title.TextRect.right = lps->cy;
            Title.TextRect.bottom = lps->cx;
        }
        else
        {
            Title.TextRect.right = lps->cx;
            Title.TextRect.bottom = lps->cy;
        }*/

        if(textAlign == CS_TA_TOP_CENTER)
        {
            TextOut(dc,(rc.right-lps->cx)/2,Title.TextRect.top,(LPCSTR)Title.Text,strlen(Title.Text));
        }
        if(textAlign == CS_TA_CENTER)
        {   
            if(Title.Orientation == -900)
            {
                TextOut(dc,(rc.right+lps->cy)/2,(rc.bottom-lps->cx)/2,(LPCSTR)Title.Text,strlen(Title.Text));
            }
            else if(Title.Orientation == 900)
            {
                TextOut(dc,(rc.right-lps->cy)/2,(rc.bottom+lps->cx)/2,(LPCSTR)Title.Text,strlen(Title.Text));
            }
            else
            TextOut(dc,(rc.right-lps->cx)/2,(rc.bottom-lps->cy)/2,(LPCSTR)Title.Text,strlen(Title.Text));
        }
        else if(textAlign == CS_TA_TOP_LEFT)
            TextOut(dc,Title.TextRect.left,Title.TextRect.top,(LPCSTR)Title.Text,strlen(Title.Text));
        else if(textAlign == CS_TA_CENTER_LEFT)
            TextOut(dc,Title.TextRect.left,(rc.bottom-lps->cy)/2+Title.TextRect.top,(LPCSTR)Title.Text,strlen(Title.Text));
        else if(textAlign == CS_TA_TOP_RIGHT)
            TextOut(dc,(rc.right-lps->cx)+Title.TextRect.left,Title.TextRect.top,
            (LPCSTR)Title.Text,strlen(Title.Text));
        else if(textAlign == CS_TA_CENTER_RIGHT)
            TextOut(dc,(rc.right-lps->cx)+Title.TextRect.left,(rc.bottom-lps->cy)/2 + Title.TextRect.top,
            (LPCSTR)Title.Text,strlen(Title.Text));
    
        DeleteFont(hf);
        free(lps);
    }
}

long colorEdit(UINT msg, WPARAM wp, int id)
{
    long lr=0;
    if(msg==WM_CTLCOLOREDIT)
    {
        csEDITBOX_PARAMS ebp = cv.cp[id]->EditBox;
        SetBkColor((HDC)wp, ebp.EditModeBkgColor);
        SetTextColor((HDC)wp, ebp.EditModeTextColor);
        lr=LONG((LONG_PTR)ebp.hbr);
    }
    return lr;
}

void quit(UINT msg)
{
    if(msg==WM_DESTROY)
    {
        PostQuitMessage(0);
    }
}

void createEdit(HWND hwnd,UINT msg, int id)
{
    HBRUSH hb;
    HPEN hp;
    int len;
    if(msg==WM_TIMER && cv.cp[id]->EditBox.AddEditBox && !cv.cp[id]->EditBox.CreateSignal)
    {
        csEDITBOX_PARAMS* ebp = &cv.cp[id]->EditBox;
        ebp->lps=(LPSIZE)malloc(sizeof(SIZE));
        int fx = csGetAdjustedFontSizeX(ebp->Title.FontSize.cx);
        int fy = csGetAdjustedFontSizeY(ebp->Title.FontSize.cy);

        if(ebp->Title.Font)
            ebp->Hfont_Title=CreateFontA(fx,fy,0,0,ebp->Title.Bold,
                                         ebp->Title.Italic,0,0,0,OUT_OUTLINE_PRECIS,0,CLEARTYPE_QUALITY
                                         ,0,ebp->Title.Font);
        else
            ebp->Hfont_Title=CreateFont(fx,fy,0,0,ebp->Title.Bold,
                                        ebp->Title.Italic,0,0,0,OUT_OUTLINE_PRECIS,0,CLEARTYPE_QUALITY
                                        ,0,"book antiqua");
        if(ebp->String.Font)
            ebp->Hfont_String=CreateFont(fx,fy,0,0,ebp->String.Bold,
                                         ebp->String.Italic,0,0,0,OUT_OUTLINE_PRECIS,0,CLEARTYPE_QUALITY
                                         ,0,ebp->String.Font);
        else
            ebp->Hfont_String=CreateFont(fx,fy,0,0,ebp->String.Bold,
                                         ebp->String.Italic,0,0,0,OUT_OUTLINE_PRECIS,0,CLEARTYPE_QUALITY
                                         ,0,"book antiqua");
        HDC dc=GetDC(hwnd);
        RECT rpos = ebp->Title.TextRect, r1 = rpos;
        SelectFont(dc, ebp->Hfont_Title);
        GetTextExtentPoint32(dc, (LPCSTR)ebp->Title.Text, strlen((LPCSTR)ebp->Title.Text), ebp->lps);
        ReleaseDC(hwnd, dc);
        HINSTANCE hinst = (HINSTANCE)GetWindowLongA(hwnd,GWLP_HINSTANCE);
        int pos = ebp->TitlePosition;
        LPSIZE lps = ebp->lps;
        if(pos==0||pos==1||pos==2)
            rpos = {4,2+lps->cy,rpos.right-6,rpos.bottom-4-lps->cy};
        else if(pos==3)
            rpos = {4+lps->cx,2,rpos.right-6-lps->cx,rpos.bottom-4};
        else if(pos==4)
            rpos = {4,2,rpos.right-6-lps->cx,rpos.bottom-4};
        else if(pos==5||pos==6||pos==7)
            rpos = {4,2,rpos.right-6,rpos.bottom-4-lps->cy};
        ebp->EditBoxHandle=CreateWindowEx (
               0, "edit",
                "",WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ebp->Style,
               rpos.left,rpos.top,rpos.right,rpos.bottom,
                hwnd,NULL,hinst,NULL);

        SendMessage(ebp->EditBoxHandle, WM_SETFONT, (WPARAM)ebp->Hfont_String, 1);
        if(ebp->DefText)
            SetWindowText(ebp->EditBoxHandle,ebp->DefText);

        ebp->hbr = CreateSolidBrush(ebp->EditModeBkgColor);
        cv.cp[id]->EditBox.CreateSignal = 1;
        cv.cp[id]->EditBox.Title.TextRect = r1;
    }
    if(msg == WM_SIZE)
    {
        csEDITBOX_PARAMS* ebp = &cv.cp[id]->EditBox;
        RECT rpos = ebp->Title.TextRect;
        //MoveWindow(ebp->EditBoxHandle,rpos.left,rpos.top,rpos.right,rpos.bottom,1);
    }
}

void EditBoxDesign(int id, HDC wDc)
{
    if(cv.cp[id]->EditBox.AddEditBox && cv.cp[id]->EditBox.CreateSignal)
    {
        csEDITBOX_PARAMS ebp = cv.cp[id]->EditBox;

        HBRUSH hb=CreateSolidBrush(ebp.BorderColor);
        HPEN hp=CreatePen(0,1,ebp.LineColor);
        SelectBrush(wDc, hb);
        SelectPen(wDc, hp);
        //Rectangle(wDc, rpos.left, rpos.top, rpos.right-rpos.left, rpos.bottom-rpos.top);
        SelectFont(wDc, ebp.Hfont_Title);
        SetTextColor(wDc, RGB(ebp.Title.Color.r,ebp.Title.Color.g,ebp.Title.Color.b));
        SetBkMode(wDc, TRANSPARENT);
        SetTextAlign(wDc, TA_LEFT);
        LPCSTR title = (LPCSTR)ebp.Title.Text;
        int len=strlen(title);
        int pos = ebp.TitlePosition;
        RECT rpos = ebp.Title.TextRect;
        LPSIZE lps =ebp.lps;
        //LPSIZE lps =(LPSIZE)malloc(sizeof(SIZE));
        //GetTextExtentPoint32(wDc, (LPCSTR)title, len, lps);
        char* str = (char*)malloc(100);
        sprintf(str,"");
        GetWindowTextA(cv.cp[id]->EditBox.EditBoxHandle,(LPSTR)str,100);
        if(pos==0)
        {   TextOut(wDc, 0, 0, title, len);
            Rectangle(wDc, 2,0+lps->cy,rpos.right,rpos.bottom);
            SelectFont(wDc, ebp.Hfont_String);
            SetTextColor(wDc, RGB(ebp.String.Color.r,ebp.String.Color.g,ebp.String.Color.b));
            TextOutA(wDc, 4,2+lps->cy, (LPCSTR)str, strlen(str));
        }
        else if(pos==1)
        {   TextOut(wDc, 0+(rpos.right-lps->cx)/2, 0, title, len);
            Rectangle(wDc, 2,0+lps->cy,rpos.right,rpos.bottom);
            SelectFont(wDc, ebp.Hfont_String);
            SetTextColor(wDc, RGB(ebp.String.Color.r,ebp.String.Color.g,ebp.String.Color.b));
            TextOutA(wDc, 0,0+lps->cy, (LPCSTR)str, strlen(str));
        }
        else if(pos==2)
        {   TextOut(wDc, rpos.right-lps->cx, 0, title, len);
            Rectangle(wDc, 0,0+lps->cy,rpos.right,rpos.bottom);
            SelectFont(wDc, ebp.Hfont_String);
            SetTextColor(wDc, RGB(ebp.String.Color.r,ebp.String.Color.g,ebp.String.Color.b));
            TextOutA(wDc, 0,0+lps->cy, (LPCSTR)str, strlen(str));
        }
        else if(pos==3)
        {   TextOut(wDc, 0, 0, title, len);
            Rectangle(wDc, 0+lps->cx,0,rpos.right,rpos.bottom);
            SelectFont(wDc, ebp.Hfont_String);
            SetTextColor(wDc, RGB(ebp.String.Color.r,ebp.String.Color.g,ebp.String.Color.b));
            TextOutA(wDc, lps->cx,0, (LPCSTR)str, strlen(str));
        }
        else if(pos==4)
        {   TextOut(wDc, rpos.right-lps->cx, 0, title, len);
            Rectangle(wDc, 0,0,rpos.right-lps->cx,rpos.bottom);
            SelectFont(wDc, ebp.Hfont_String);
            SetTextColor(wDc, RGB(ebp.String.Color.r,ebp.String.Color.g,ebp.String.Color.b));
            TextOutA(wDc, 0,0, (LPCSTR)str, strlen(str));
        }
        else if(pos==5)
        {   TextOut(wDc, 0, rpos.bottom-lps->cy, title, len);
            Rectangle(wDc, 0,0,rpos.right,rpos.bottom-lps->cy);
            SelectFont(wDc, ebp.Hfont_String);
            SetTextColor(wDc, RGB(ebp.String.Color.r,ebp.String.Color.g,ebp.String.Color.b));
            TextOutA(wDc, 0,0, (LPCSTR)str, strlen(str));
        }
        else if(pos==6)
        {   TextOut(wDc, 0+(rpos.right-lps->cx)/2, rpos.bottom-lps->cy, title, len);
            Rectangle(wDc, 0,0,rpos.right,rpos.bottom-lps->cy);
            SelectFont(wDc, ebp.Hfont_String);
            SetTextColor(wDc, RGB(ebp.String.Color.r,ebp.String.Color.g,ebp.String.Color.b));
            TextOutA(wDc, 0,0, (LPCSTR)str, strlen(str));
        }
        else if(pos==7)
        {   TextOut(wDc, rpos.right-lps->cx, rpos.bottom-lps->cy, title, len);
            Rectangle(wDc, 0,0,rpos.right,rpos.bottom-lps->cy);
            SelectFont(wDc, ebp.Hfont_String);
            SetTextColor(wDc, RGB(ebp.String.Color.r,ebp.String.Color.g,ebp.String.Color.b));
            TextOutA(wDc, 0,0, (LPCSTR)str, strlen(str));
        }
        DeletePen(hp);
        DeleteBrush(hb);
        free(str);
    }
}

void manageEditBox(HWND hwnd, UINT msg, int id)
{
    if(msg==WM_TIMER)
    {
        POINT p = cv.phit0;
        HWND hedit = cv.cp[id]->EditBox.EditBoxHandle;
        if(PtInRect(&cv.CNTRECT[id],p))
        {
            if(hedit && !IsWindowVisible(hedit))
            {
                ShowWindow(hedit,1);
            }
        }
        else if(hedit && IsWindowVisible(hedit))
        {
            ShowWindow(hedit,0);
        }
    }
}

void mwfunc(HWND*hedit, HWND hbtn, UINT msg, LPARAM lp)
{
    char chr[5][100]={""};
    bool b=0;
    if(msg==WM_COMMAND)
    {
        if(HWND(lp)==hbtn)
        {
            for(int i=0; i<5; i++)
            {   GetWindowText(hedit[i], chr[i], 100);
                if(strlen((const char*)chr[i])==0)
                    b=1;
            }
            if(!b)
            {
                //movew(chr[0], (int)strtod(chr[1],0),
//                      (int)strtod(chr[2],0),
//                      (int)strtod(chr[3],0),
//                      (int)strtod(chr[4],0));
//                //std::cout<<chr[0];
            }
        }
    }
}

csGLP4* csGLP4_PTR(csGLP4 glp)
{
    return csf_alloc2<csGLP4>(1,glp);
}

void csGeometryLink(int* idp, int n, csGLP4** glp)
{
    csARGS* args = csf_alloc<csARGS>(n);
    bool*signal = csf_alloc2<bool>(n,0);
    int*ids = csf_alloc<int>(n);
    for(int i=0; i<n; i++)
    {
        args[i].setArgNumber(3);
        args[i].makeArgs(glp[i], &signal[i], idp);
        csSetAction(glp[i]->id, WM_TIMER, csSelfGeometrySetting, args[i]);
        ids[i] = glp[i]->id;
    }

    csSetAction(*idp, WM_SIZE, csGLPParentSizing, 3, ids, signal, csf_alloc2<int>(1,n));
}

void csGeometryLink(int* idp, int nbArgs, ...)
{
    va_list adArgs ;
    csGLP4* parv;
    csGLP4*glp[nbArgs]={NULL};
    va_start (adArgs, nbArgs);

    for (int i=0 ; i<nbArgs ; i++)
    {
        parv = va_arg (adArgs, csGLP4*) ;
        glp[i]=parv;
    }

    csARGS* args = csf_alloc<csARGS>(nbArgs);
    bool*signal = csf_alloc2<bool>(nbArgs,0);
    int*ids = csf_alloc<int>(nbArgs);
    for(int i=0; i<nbArgs; i++)
    {
        args[i].setArgNumber(3);
        args[i].makeArgs(glp[i], &signal[i], idp);
        csSetAction(glp[i]->id, WM_TIMER, csSelfGeometrySetting, args[i]);
        ids[i] = glp[i]->id;
    }

    csSetAction(*idp, WM_SIZE, csGLPParentSizing, 3, ids, signal, csf_alloc2<int>(1,nbArgs));
}

void csGLPParentSizing(csARGS Args)
{
    int* ids = (int*)Args[0];
    bool*signal = (bool*)Args[1];
    int n = *(int*)Args[2];

    for(int i=0; i<n; i++)
    {
        signal[i] = 1;
        SendMessage(csHWND(ids[i]), WM_TIMER, 0,0);
    }
}

void csSelfGeometrySetting(csARGS Args)
{
    bool*signal = (bool*)Args[1];
    if(*signal)
    {
        csGLP4* glp = (csGLP4*)Args[0];
        int idp = *(int*)Args[2];
        RECT r = csCLRECT(idp);
        SetWindowPos(HWND(Args),glp->ZOrder, (r.right-glp->l.x)*glp->l.a + glp->l.b,
                                             (r.bottom-glp->t.x)*glp->t.a + glp->t.b,
                                             (r.right-glp->r.x)*glp->r.a + glp->r.b,
                                             (r.bottom-glp->b.x)*glp->b.a + glp->b.b,
                                             glp->Flag);
        *signal = 0;
        if(glp->Update)
        {
            InvalidateRect(HWND(Args), 0, 1);
        }
    }
}

//void createGroup(RECT rpos, HDC& wDc, HFONT hf, COLORREF col[2], char*title, int pos, UINT msg)
//{
//    HBRUSH hb;
//    HPEN hp;
//    static LPSIZE lps;
//    int len;
//    if(msg==WM_CREATE)
//    {
//        if(!lps) lps=(LPSIZE)malloc(sizeof(lps));
//    }
//    if(msg==WM_PAINT)
//    {
//        hb=CreateSolidBrush(BKGCOL);
//        hp=CreatePen(0,1,col[0]);
//        SelectBrush(wDc, hb);
//        SelectPen(wDc, hp);
//        //Rectangle(wDc, rpos.left, rpos.top, rpos.right-rpos.left, rpos.bottom-rpos.top);
//        SelectFont(wDc, hf);
//        SetTextColor(wDc, col[1]);
//        SetBkColor(wDc, BKGCOL);
//        len=strlen((LPCSTR)title);
//        GetTextExtentPoint32(wDc, (LPCSTR)title, len, lps);
//        if(pos==0)
//        {
//            Rectangle(wDc, rpos.left,rpos.top+lps->cy/2,rpos.right,rpos.bottom);
//            TextOut(wDc, rpos.left, rpos.top, (LPCSTR)title, len);
//        }
//        else if(pos==1)
//        {
//            Rectangle(wDc, rpos.left,rpos.top+lps->cy/2,rpos.right,rpos.bottom);
//            TextOut(wDc, rpos.left+(rpos.right-lps->cx)/2, rpos.top, (LPCSTR)title, len);
//        }
//        else if(pos==2)
//        {
//            Rectangle(wDc, rpos.left,rpos.top+lps->cy/2,rpos.right,rpos.bottom);
//            TextOut(wDc, rpos.right-lps->cx, rpos.top, (LPCSTR)title, len);
//        }
//        else if(pos==3)
//        {
//            Rectangle(wDc, rpos.left+lps->cx,rpos.top,rpos.right-lps->cx,rpos.bottom-rpos.top);
//            TextOut(wDc, rpos.left, rpos.top, (LPCSTR)title, len);
//        }
//        else if(pos==4)
//        {
//            Rectangle(wDc, rpos.left,rpos.top,rpos.right-lps->cx,rpos.bottom-rpos.top);
//            TextOut(wDc, rpos.right-lps->cx, rpos.top, (LPCSTR)title, len);
//        }
//        else if(pos==5)
//        {
//            Rectangle(wDc, rpos.left,rpos.top,rpos.right,rpos.bottom-lps->cy/2);
//            TextOut(wDc, rpos.left, rpos.bottom-lps->cy, (LPCSTR)title, len);
//        }
//        else if(pos==6)
//        {
//            Rectangle(wDc, rpos.left,rpos.top,rpos.right,rpos.bottom-lps->cy);
//            TextOut(wDc, rpos.left+(rpos.right-lps->cx)/2, rpos.bottom-lps->cy/2, (LPCSTR)title, len);
//        }
//        else if(pos==7)
//        {
//            Rectangle(wDc, rpos.left,rpos.top,rpos.right,rpos.bottom-lps->cy);
//            TextOut(wDc, rpos.right-lps->cx, rpos.bottom-lps->cy/2, (LPCSTR)title, len);
//        }
//        DeletePen(hp);
//        DeleteBrush(hb);
//    }
//}

void copyStringToClipBoard(HWND hwnd, char* str)
{
    HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE, strlen(str)+1);
    if(!hg)
    {
        CloseClipboard();
        return ;
    }
    memcpy(GlobalLock(hg), str, strlen(str)+1);
    GlobalUnlock(hg);

    OpenClipboard(hwnd);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();

    GlobalFree(hg);

}

char* getTextFromClipBoard(HWND hwnd)
{
    if(!OpenClipboard(hwnd))
    {
        return 0; std::cout<<"no datas";
    }
    //ansi text = CF_TEXT
    //unicode text = CF_UNICODETEXT
    HANDLE hdata=GetClipboardData(CF_TEXT);
    if(!hdata)
        {perror("hdata");return 0;}

    char* ch=static_cast<char*>(GlobalLock(hdata));
    if(!ch) {perror("hdata"); return 0;}
    GlobalUnlock(hdata);
    CloseClipboard();
    return ch;
}

void initCopyText(HWND hwnd)
{
    copyStringToClipBoard(hwnd, "Bonjour le monde");
    std::cout<<getTextFromClipBoard(hwnd);
}


int  csGetAdjustedFontSizeX(int xSize)
{
    return ceil(xSize*CS_CXSCREEN/1366.0);
}
int  csGetAdjustedFontSizeY(int ySize)
{
    return ceil(ySize*CS_CYSCREEN/768.0);
}

