#include "utlFx.h"
extern csCNTR_VARS cv;
extern csCNTR_PARAMS cscp;
utlFx::utlFx()
{
    //ctor
}

utlFx::~utlFx()
{
    //dtor
}

char*csSTR(const char* str)
{
    char*ret = csf_alloc<char>(strlen(str)+1);
    sprintf(ret,"%s", str);
    return ret;
}

void csTITLE(int id, char*title, csRGBA color, char* font, int bold, bool italic, SIZE size)
{
    csPARAMS(id)->Title.Text = title;
    csPARAMS(id)->Title.Color = color;
    csPARAMS(id)->Title.Font = font;
    csPARAMS(id)->Title.Bold = bold;
    csPARAMS(id)->Title.Italic = italic;
    csPARAMS(id)->Title.FontSize = size;
}


RECT csSizeSyncDelta(int id, SIZE& delta)
{
    RECT r, rs = cv.CNTRECT_SAVED[id];
    GetWindowRect(cv.CNTLIST[id], &r);
    delta.cx  = r.right-rs.right; delta.cy  = r.bottom-rs.bottom;
    return r;
}
RECT csSizeSyncDeltaY(int id, int& delta)
{
    RECT r, rs = cv.CNTRECT_SAVED[id];
    GetWindowRect(cv.CNTLIST[id], &r);
    delta  = r.bottom-rs.bottom;
    return r;
}
RECT csSizeSyncDeltaX(int id, int& delta)
{
    RECT r, rs = cv.CNTRECT_SAVED[id];
    GetWindowRect(cv.CNTLIST[id], &r);
    delta  = r.right-rs.right;
    return r;
}

RECT csPosSyncDelta(int id, SIZE& delta)
{
    RECT r, rs = cv.CNTRECT_SAVED[id];
    GetWindowRect(cv.CNTLIST[id], &r);
    delta.cx  = r.left-rs.left; delta.cy  = r.top-rs.top;
    return r;
}
RECT csPosSyncDeltaY(int id, int& delta)
{
    RECT r, rs = cv.CNTRECT_SAVED[id];
    GetWindowRect(cv.CNTLIST[id], &r);
    delta  = r.top-rs.top;
    return r;
}
RECT csPosSyncDeltaX(int id, int& delta)
{
    RECT r, rs = cv.CNTRECT_SAVED[id];
    GetWindowRect(cv.CNTLIST[id], &r);
    delta  = r.left-rs.left;
    return r;
}

RECT csGeomSyncDelta(int id, RECT& delta)
{
    RECT r, rs = cv.CNTRECT_SAVED[id];
    GetWindowRect(cv.CNTLIST[id], &r);
    delta.left  = r.left-rs.left; delta.top  = r.top-rs.top;
    delta.right  = r.right-rs.right; delta.bottom  = r.bottom-rs.bottom;
    return r;
}

RECT transformRect(RECT r, RECT dr, float iter, float maxiter)
{
    float rat = iter/maxiter;
    RECT rs = {r.left+dr.left*rat, r.top+dr.top*rat, r.right+dr.right*rat, r.bottom+dr.bottom*rat};
    return rs;
}
RECT invTransformRect(RECT r, RECT dr, float iter, float maxiter)
{
    float rat = iter/maxiter;
    RECT rs = {r.left-dr.left*rat, r.top-dr.top*rat, r.right-dr.right*rat, r.bottom-dr.bottom*rat};
    return rs;
}

static bool cslk = 0;
static bool b_allow_click_after_anim_ends = 0;
static int mxcount = 4;
static int mxcount2 = 4;
static int count = -1;
static int count2 = mxcount2+2;
static RECT r1, r2, dr={-30,0,0,0};

void cnt_show_hide_click(csARGS Args)
{
    int id = *((int*)Args[0]);
    if(!b_allow_click_after_anim_ends)
    if(!cslk)
    {
        GetWindowRect(cv.CNTLIST[id],&r1);
        r1 = rectInParentRef(id,r1);
        r1.right-=r1.left;
        r1.bottom-=r1.top;
        r2 = {r1.left+dr.left, r1.top+dr.top, r1.right+dr.right, r1.bottom+dr.bottom};
        cslk = 1;
        count = -1;
    }
    else
    {
        cslk = 0;
        count2 = -1;
    }
}

void cnt_show_hide(csARGS Args)
{
    int id = *((int*)Args[0]);
    HWND hw = cv.CNTLIST[id];
    static int inc = 42;
    RECT r = {0,0,0,0};
    if(cslk)
    {
        if(count <= mxcount)
        {
            b_allow_click_after_anim_ends = 1;
            SetLayeredWindowAttributes(hw, 0, 200*(1-float(count)/mxcount), LWA_ALPHA);
            r = transformRect(r1,dr,count,mxcount);
            MoveWindow(hw,r.left,r.top, r.right,r.bottom,1);
            count++;
        }
        if(count == mxcount+1)
        {
            b_allow_click_after_anim_ends = 0;
            MoveWindow(hw,r2.left,r2.top, r2.right,r2.bottom,1);
            ShowWindow(hw,0);
            count++;
        }
    }
    else
    {
        if(count2 == -1)
            ShowWindow(hw,1);
        if(count2 <= mxcount2)
        {
            b_allow_click_after_anim_ends = 1;
            SetLayeredWindowAttributes(hw, 0, 55+200*(float(count2)/mxcount2), LWA_ALPHA);
            r = invTransformRect(r2,dr,count2,mxcount2);
            //cout<<r.left<<"\n";
            MoveWindow(hw,r.left,r.top, r.right,r.bottom,1);
            count2++;
        }
        if(count2 == mxcount2+1)
        {
            b_allow_click_after_anim_ends = 0;
            MoveWindow(hw,r1.left,r1.top, r1.right,r1.bottom,1);
            count2++;
        }
    }
}

csPAGEFLIPPING_VARS getHideShowVars(int* hiders, int* pages, int* n_ptr, csBUTTONGRID* bg, RECT drTransform)
{
    csPAGEFLIPPING_VARS hs;
    hs.hiders = hiders;
    hs.pages = pages;
    hs.n_pages = n_ptr;
    hs.dr = drTransform;
    bool b = 0;
    /*csBUTTONGRID* bg=0;*/
    for(int i=0; i<*n_ptr; i++)
    {
        if(cv.cp[pages[i]]->Show)
        {
            hs.active = pages[i];
            if(!bg)
            {
                cv.cp[hiders[i]]->LockedMode.Locked = 1;
                cv.cp[hiders[i]]->LockedMode.ExtBool = 1;
            }
            else
            {
                bg->setActiveItem(i);
            }
            b = 1;
            break;
        }
    }
    if(b)
    {
        for(int i=0; i<*n_ptr; i++)
        {
            if(pages[i]!=hs.active && cv.cp[pages[i]]->Show)
            {
                cv.cp[pages[i]]->Show = 0;
                ShowWindow(cv.CNTLIST[pages[i]], 0);
            }
        }
    }
    else
    {
        cv.cp[pages[0]]->Show = 1;
        ShowWindow(cv.CNTLIST[pages[0]], 1);
        hs.active = pages[0];
        if(!bg)
        {
            cv.cp[hiders[0]]->LockedMode.Locked = 1;
            cv.cp[hiders[0]]->LockedMode.ExtBool = 1;
            SendMessage(cv.CNTLIST[hiders[0]], WM_LBUTTONUP, 0, 0);
        }
        else
        {
            bg->setActiveItem(0);
        }
    }
    hs.bg = bg;
    return hs;
}

void cntgroup_show_hide_click(csARGS Args)
{
    csPAGEFLIPPING_VARS hs, *hs0 = (csPAGEFLIPPING_VARS*)Args[0];
    //csPAGEFLIPPING_VARS hs0 = *((csPAGEFLIPPING_VARS*)Args[0]);
    int hider=0;
    if(!hs0->bg)
       { hider = int(Args); }
    else hider = hs0->bg->getActiveItem();

    int page = hs0->pageFromHider(hider);
    int j=0;
    if(!IsWindowVisible(cv.CNTLIST[page])&&
    //if(page != ((csPAGEFLIPPING_VARS*)Args[0])->active &&
       !hs0->b_allow_click_after_anim_ends)
    {
    //std::cout<<"btnup page out: "<<page<<"\n";
        //cv.cp[hider]->LockedMode.Locked=1;
        //cv.cp[hider]->LockedMode.LockingActivated = 1;
        hs = *hs0;
        hs.id = page;// placer l'id dans une structure qui sera ensuite utilisee dans un timer
        int*ids = hs.pages;
        int n = *hs.n_pages;
        for(int i = 0; i<n; i++)
        {
            j=ids[i];
            if(IsWindowVisible(cv.CNTLIST[j]))
            {
                hs.active = j;
                if(!hs.bg)
                {
                    cv.cp[hs.hiders[i]]->LockedMode.Locked=0;
                    cv.cp[hs.hiders[i]]->LockedMode.LockingActivated = 0;
                    cv.cp[hs.hiders[i]]->LockedMode.ExtBool = 1;
                }
                break;
            }
        }
        GetWindowRect(cv.CNTLIST[hs.active],&hs.r1);
        hs.r1 = rectInParentRef(hs.active,hs.r1);
        hs.r1.right-=hs.r1.left;
        hs.r1.bottom-=hs.r1.top;
        hs.r2 = {hs.r1.left+hs.dr.left, hs.r1.top+hs.dr.top,
                hs.r1.right+hs.dr.right, hs.r1.bottom+hs.dr.bottom};
        hs.count = -1;
        //hs.count2 = -1;
        hs.cslk = 1;
        //Args.setArg(0,(void*)&hs);
        *((csPAGEFLIPPING_VARS*)Args[0]) = hs;

    }
}

void cntgroup_show_hide(csARGS Args)
{
    csPAGEFLIPPING_VARS hs;

    if(((csPAGEFLIPPING_VARS*)Args[0])->cslk)
    {
        hs = *((csPAGEFLIPPING_VARS*)Args[0]);
        HWND hw2 = cv.CNTLIST[hs.active];
        int id = hs.id;
        HWND hw = cv.CNTLIST[id];
        RECT r = {0,0,0,0};
        if(hs.count <= hs.mxcount)
        {
            hs.count++;
            hs.b_allow_click_after_anim_ends = 1;
            float alpha = hs.alphaMin+(255-hs.alphaMin)*(1.0-float(hs.count)/hs.mxcount);
            SetLayeredWindowAttributes(hw2, 0, alpha, LWA_ALPHA);
            r = transformRect(hs.r1,hs.dr,hs.count,hs.mxcount);
            //MoveWindow(hw2,r.left,r.top, r.right,r.bottom,1);
            SetWindowPos(hw2,hs.cntOrder, r.left,r.top, r.right,r.bottom,SWP_NOZORDER);
        }
        else if(hs.count == hs.mxcount+1)
        {
            //hs.b_allow_click_after_anim_ends = 0;
            SetWindowPos(hw2,hs.cntOrder,hs.r2.left,hs.r2.top, hs.r2.right,hs.r2.bottom,SWP_NOZORDER);
            //ShowWindow(hw2,0);
            cv.cp[hs.active]->Show = 0;
            hs.count++;
        }
        else if(hs.count > hs.mxcount+1 && hs.count<=hs.transitionTime+hs.mxcount+1)
        {
            if(hs.count==hs.transitionTime+hs.mxcount+1)
            {
               hs.count2 = -1;
            }
            hs.count++;
        }

        if(hs.count2 == -1)
        {
            //ShowWindow(hw,1);
            cv.cp[id]->Show = 1;
            /*for(int i=0; i<cv.CNTLIST.size(); i++)
            {
                InvalidateRect(cv.CNTLIST[i],0,1);
            }*/
            //SendMessage(hw, WM_SIZE, 0,0);
            //InvalidateRect(hw,0,1);
        }
        if(hs.count2 <= hs.mxcount2)
        {
            //hs.b_allow_click_after_anim_ends = 1;
            float alpha = hs.alphaMin+(255-hs.alphaMin)*(float(hs.count2)/hs.mxcount2);
            SetLayeredWindowAttributes(hw, 0, alpha, LWA_ALPHA);
            r = invTransformRect(hs.r2,hs.dr,hs.count2,hs.mxcount2);
            SetWindowPos(hw,hs.cntOrder,r.left,r.top, r.right,r.bottom,SWP_NOZORDER);
            hs.count2++;
        }
        else if(hs.count2 == hs.mxcount2+1)
        {
            hs.b_allow_click_after_anim_ends = 0;
            SetWindowPos(hw,hs.cntOrder,hs.r1.left,hs.r1.top, hs.r1.right,hs.r1.bottom,SWP_NOZORDER);
            hs.count2++;
            hs.cslk = 0;
        }
        //Args.setArg(0,(void*)&hs);
        *((csPAGEFLIPPING_VARS*)Args[0]) = hs;
    }
}

/***************************************************************/
void cntgroup_show_hide_click2(csARGS Args)
{
    int id = *((int*)Args[0]);
    static csPAGEFLIPPING_VARS hs;
    if(!IsWindowVisible(cv.CNTLIST[id])&&
       !((csPAGEFLIPPING_VARS*)Args[1])->b_allow_click_after_anim_ends)
    {
        hs = *((csPAGEFLIPPING_VARS*)Args[1]);
        int id2 = *((int*)Args[2]);
        GetWindowRect(cv.CNTLIST[id2],&hs.r1);
        hs.r1 = rectInParentRef(id2,hs.r1);
        hs.r1.right-=hs.r1.left;
        hs.r1.bottom-=hs.r1.top;
        hs.r2 = {hs.r1.left+hs.dr.left, hs.r1.top+hs.dr.top,
                hs.r1.right+hs.dr.right, hs.r1.bottom+hs.dr.bottom};
        hs.count = -1;
        hs.cslk = 1;
        Args.setArg(1,(void*)&hs);
    }
}

void cntgroup_show_hide2(csARGS Args)
{
    int id = *((int*)Args[0]);
    HWND hw = cv.CNTLIST[id];
    static csPAGEFLIPPING_VARS hs;
    static int last_id;
    HWND hw2 = cv.CNTLIST[*((int*)Args[2])];
    RECT r = {0,0,0,0};
    if(((csPAGEFLIPPING_VARS*)Args[1])->cslk)
    {
        hs = *((csPAGEFLIPPING_VARS*)Args[1]);
        if(hs.count == -1)
            SetWindowPos(hw,HWND_BOTTOM,hs.r1.left,hs.r1.top, hs.r1.right,hs.r1.bottom,SWP_SHOWWINDOW);
        else if(hs.count <= hs.mxcount)
        {
            //ShowWindow(hw,1);
            hs.b_allow_click_after_anim_ends = 1;
            float alpha = hs.alphaMin+(255-hs.alphaMin)*(1.0-float(hs.count)/hs.mxcount);
            //SetLayeredWindowAttributes(hw2, 0, alpha, LWA_ALPHA);
            r = transformRect(hs.r1,hs.dr,hs.count,hs.mxcount);
            MoveWindow(hw2,r.left,r.top, r.right,r.bottom,1);
            hs.count++;
        }
        else if(hs.count == hs.mxcount+1)
        {
            //hs.b_allow_click_after_anim_ends = 0;
            MoveWindow(hw2,hs.r2.left,hs.r2.top, hs.r2.right,hs.r2.bottom,1);
            ShowWindow(hw2,0);
            hs.b_allow_click_after_anim_ends = 0;
            last_id = id;
            Args.setArg(2,(void*)&last_id);
            hs.cslk = 0;
            hs.count++;
        }

        Args.setArg(1,(void*)&hs);
    }
}

/***************************************************************************/
void csAddColorFilter(int* id, csRGBA color, int cLevel)
{

    //int genColor = staticCnt2(cscp, id, "", color,{1,1,CS_CXSCREEN,CS_CYSCREEN},1);
    RECT geom = cv.cp[*id]->Geometry;
    int genColor = staticCnt2(cscp, *id, "", color,{1,1,geom.right,geom.bottom},1);
    csSetTransparency(genColor,100-cLevel%100);
    SetWindowLong(cv.CNTLIST[genColor],GWL_EXSTYLE,GetWindowLong(cv.CNTLIST[genColor], GWL_EXSTYLE)|WS_EX_TRANSPARENT);


    void resizeFilter(csARGS Args);
    csSetAction(genColor,WM_TIMER, resizeFilter, 1, id);
    cv.cp[*id]->ColorFilter = genColor;
}
void resizeFilter(csARGS Args)
{
    int idp = *(int*)Args[0];
    RECT r1 = cv.CNTRECT[int(Args)], r2 = cv.CNTRECT[idp];
    int dx1 = r1.right-r1.left, dx2 = r2.right-r2.left;
    int dy1 = r1.bottom-r1.top, dy2 = r2.bottom-r2.top;
    if(dx1 != dx2 || dy1 != dy2)
    {
        SetWindowPos(HWND(Args), HWND_TOP, 0,0,dx2,dy2,SWP_NOZORDER);
    }
}

/*******************************************************/

void csPageBGHider(int*pages, int* n, csBUTTONGRID*bg, unsigned time1, unsigned time2, unsigned transTime)
{
    csPAGEFLIPPING_VARS* _hs = (csPAGEFLIPPING_VARS*)malloc(sizeof(csPAGEFLIPPING_VARS));
    *_hs = getHideShowVars(0, pages, n, bg);
    _hs->mxcount = time1; // temps de disparition
    _hs->mxcount2 = time2; // temps d'apparition
    _hs->transitionTime = transTime;
    csSetAction(bg->getId(), WM_LBUTTONUP, cntgroup_show_hide_click, 1, _hs);
    int n_bgm = cv.cp[bg->getId()]->CntEventsFunc.LBUTTONUP_ARGS.size()-1;
    csARGS m_args = cv.cp[bg->getId()]->CntEventsFunc.LBUTTONUP_ARGS[n_bgm];
    csSetAction(bg->getId(), WM_TIMER, cntgroup_show_hide, m_args);

    SetTimer(cv.CNTLIST[bg->getId()],0,15,0);
}

csPAGEFLIPPING_VARS* csPageBGHider(csLIST<csBUTTONGRID> pages, csBUTTONGRID*hider, int idp_tbg, RECT tbgGeom,
                                csTEXTBUTTON_GROUP*&tbg, unsigned time1, unsigned time2, unsigned transTime)
{
    int *n = csf_alloc2<int>(1,pages.size());
    int*_pages = csf_alloc<int>(*n);


    bool orient = CS_BG_HORIZONTAL;
    if (pages[0].getXLength() < pages[0].getYLength()) orient = CS_BG_VERTICAL;

    tbg = (csTEXTBUTTON_GROUP*)malloc(sizeof(csTEXTBUTTON_GROUP));
    csTEXTBUTTON_GROUP _tbg(idp_tbg, tbgGeom, orient);
    _tbg.setTotalLength(300);
    _tbg.setMarging(2);
    _tbg.create();
    *tbg = _tbg;

    int idc3 = tbg->getIDC3();
    for(int i=0; i<*n; i++)
    {
        _pages[i]=pages[i].getId();
        csSetParent(_pages[i], idc3);
    }

    int id = hider->getId();

    csPAGEFLIPPING_VARS* _hs = (csPAGEFLIPPING_VARS*)malloc(sizeof(csPAGEFLIPPING_VARS)); // a liberer a la fin du programme
    *_hs = getHideShowVars(0, _pages, n, hider);
    _hs->mxcount = time1; // temps de disparition
    _hs->mxcount2 = time1; // temps d'apparition
    _hs->transitionTime = transTime;
    //_hs->dr = {-40,0,0,0};


    csSetAction(id, WM_LBUTTONUP, cntgroup_show_hide_click, 1, _hs);
    int n_bgm = cv.cp[id]->CntEventsFunc.LBUTTONUP_ARGS.size()-1;
    csARGS args = cv.cp[id]->CntEventsFunc.LBUTTONUP_ARGS[n_bgm];
    csSetAction(id, WM_TIMER, cntgroup_show_hide, args);

    void setLength(csARGS Args);
    void autoFrameActiveItem(csARGS Args);

    bool*autoFrameActItem = csf_alloc2<bool>(1,0);
    csARGS args1/*, *pargs1 = csf_alloc<csARGS>(1) */;
    args1.setArgNumber(4);
    args1.makeArgs(hider, pages.getTable(), tbg, autoFrameActItem);
    csSetAction(id, WM_LBUTTONUP, setLength, args1);

    void reposIDC3pages(csARGS Args);
    for(int i=0; i<*n; i++)
    {
        csSetAction(_pages[i], WM_LBUTTONUP, reposIDC3pages, args1);
        csSetAction(_pages[i], WM_TIMER, autoFrameActiveItem, args1);
    }
    //*pargs1 = args1;

    SetTimer(cv.CNTLIST[id],0,15,0);

    return _hs;
}

void setLength(csARGS Args)
{
    csBUTTONGRID*hider=(csBUTTONGRID*)Args[0];
    csBUTTONGRID*pages=(csBUTTONGRID*)Args[1];
    csTEXTBUTTON_GROUP*tbg=(csTEXTBUTTON_GROUP*)Args[2];

    int id3 = tbg->getIDC3();
    int activeItem = hider->getActiveItem();
//std::cout<<pages[activeItem].getId()<<" --act\n";
    if(tbg->getOrientation()==CS_BG_HORIZONTAL)
    {
        tbg->setTotalLength(pages[activeItem].getXLength());
        // SetWindowPos(cv.CNTLIST[id3],0,0,0,pages[activeItem].getXLength(),
        //             cv.CNTRECT[id3].bottom-cv.CNTRECT[id3].top,SWP_NOMOVE|SWP_NOZORDER);
//std::cout<<pages[activeItem].getXLength()<<" --act\n";
    }
    else
    {
        tbg->setTotalLength(pages[activeItem].getYLength());
    }
    InvalidateRect(cv.CNTLIST[id3],0,1);

    bool *autoFrameActItem = (bool*)Args[3];
    *autoFrameActItem = 1;

}

void reposIDC3pages(csARGS Args)
{
    csBUTTONGRID*hider=(csBUTTONGRID*)Args[0];
    csBUTTONGRID*pages=(csBUTTONGRID*)Args[1];
    csTEXTBUTTON_GROUP*tbg=(csTEXTBUTTON_GROUP*)Args[2];
//xstd::cout<<pages[hider->getActiveItem()].getId()<<" --act\n";
    int id3 = tbg->getIDC3();

    RECT r = cv.CNTRECT[tbg->getIDC2()], ri = *(pages[hider->getActiveItem()].getItemRect(pages[hider->getActiveItem()].getActiveItem()));
    RECT r3 = cv.CNTRECT[id3], r3p = rectInParentRef(id3, r3);
    int a = r.right - (r3.left + ri.left + ri.right);

    if(a < 0)
    {
        cv.cp[id3]->AutoTransform.Time=4;
        cv.cp[id3]->AutoTransform.Type=AUTO_TRANSF_LENGTH;
        cv.cp[id3]->AutoTransform.InitialRect=r3p;
        cv.cp[id3]->AutoTransform.FinalRect={a,0,0,0};
        cv.AUTOTRANSCOUNT[id3]=0;
        //SetWindowPos(cv.CNTLIST[id3],0,r3p.left+a,r3p.top,0,0,SWP_NOSIZE);
    }
    else
    {
        int b = r.left - (r3.left + ri.left);
        if(b > 0)
        {
            cv.cp[id3]->AutoTransform.Time=4;
            cv.cp[id3]->AutoTransform.Type=AUTO_TRANSF_LENGTH;
            cv.cp[id3]->AutoTransform.InitialRect=r3p;
            cv.cp[id3]->AutoTransform.FinalRect={b,0,0,0};
            cv.AUTOTRANSCOUNT[id3]=0;
            //SetWindowPos(cv.CNTLIST[id3],0,r3p.left+a,r3p.top,0,0,SWP_NOSIZE);
        }
    }
}
void reposIDC3indexer(csARGS Args);
void reposIDC3indexer(csARGS Args)
{
    csBUTTONGRID*indexer=(csBUTTONGRID*)Args[0];
    csTEXTBUTTON_GROUP*tbg=(csTEXTBUTTON_GROUP*)Args[1];
//xstd::cout<<pages[hider->getActiveItem()].getId()<<" --act\n";
    int id3 = tbg->getIDC3();

    RECT r = cv.CNTRECT[tbg->getIDC2()], ri = *(indexer->getItemRect(indexer->getActiveItem()));
    RECT r3 = cv.CNTRECT[id3], r3p = rectInParentRef(id3, r3);
    
    int a = r.right - (r3.left + ri.left + ri.right);

    if(tbg->getOrientation()==CS_BG_HORIZONTAL)
    {
        int a1 = r.right - (r3.left + indexer->getTolalWidth());
        if(a1 > 0)
        {
            a1 = std::min(a1, int(r.left-r3.left));
            cv.cp[id3]->AutoTransform.Time=4;
            cv.cp[id3]->AutoTransform.Type=AUTO_TRANSF_LENGTH;
            cv.cp[id3]->AutoTransform.InitialRect=r3p;
            cv.cp[id3]->AutoTransform.FinalRect={a1,0,0,0};
            cv.AUTOTRANSCOUNT[id3]=0;
        }
        else if(a < 0)
        {
            cv.cp[id3]->AutoTransform.Time = 4;
            cv.cp[id3]->AutoTransform.Type = AUTO_TRANSF_LENGTH;
            cv.cp[id3]->AutoTransform.InitialRect = r3p;
            cv.cp[id3]->AutoTransform.FinalRect = {a,0,0,0};
            cv.AUTOTRANSCOUNT[id3] = 0;
        }
        else
        {
            int b = r.left - (r3.left + ri.left);
            if(b > 0)
            {
                cv.cp[id3]->AutoTransform.Time=4;
                cv.cp[id3]->AutoTransform.Type=AUTO_TRANSF_LENGTH;
                cv.cp[id3]->AutoTransform.InitialRect=r3p;
                cv.cp[id3]->AutoTransform.FinalRect={b,0,0,0};
                cv.AUTOTRANSCOUNT[id3]=0;
            }
        }
        
    }
}

void autoFrameActiveItem(csARGS Args)
{
    bool *autoFrameActItem = (bool*)Args[3];
    static int count1 = 0, count2 = 0, count3 = 0;

    if(*autoFrameActItem)
    {
        csBUTTONGRID*hider=(csBUTTONGRID*)Args[0];
        csBUTTONGRID*pages=(csBUTTONGRID*)Args[1];
        int activeItem = hider->getActiveItem();
        int id = int(Args);
        if(id == pages[activeItem].getId())
        {
            //count1 = 16;
            count2 = 16;
            *autoFrameActItem = 0;
        }
    }

    /*if(count1)
    {
        if(count1 == 1)
        {
            csBUTTONGRID*hider=(csBUTTONGRID*)Args[0];
            csBUTTONGRID*pages=(csBUTTONGRID*)Args[1];
            csTEXTBUTTON_GROUP*tbg=(csTEXTBUTTON_GROUP*)Args[2];
            int activeItem = hider->getActiveItem();
            int id = int(Args);
            int id3 = tbg->getIDC3();

            cv.cp[id3]->AutoTransform.Time = 8;
            cv.cp[id3]->AutoTransform.Type = AUTO_TRANSF_LENGTH;
            cv.cp[id3]->AutoTransform.InitialRect = rectInParentRef(id3, csWRECT(id3));
            cv.cp[id3]->AutoTransform.FinalRect = {0,0,pages[activeItem].getXLength()-csCLRECT(id3).right,0};
            cv.AUTOTRANSCOUNT[id3] = 0;
            count2 = 16;
        }
        count1--;
    }*/

    if(count2)
    {
        if(count2 == 1)
        {
            //frame the active item
            count3 = 10;
            reposIDC3pages(Args);

        }

        count2--;
    }

    if(count3)
    {
        if(count3 == 1)
        {
            // frame the container
            csTEXTBUTTON_GROUP*tbg=(csTEXTBUTTON_GROUP*)Args[2];
            int id2 = tbg->getIDC2();
            int id3 = tbg->getIDC3();
            csBUTTONGRID*hider=(csBUTTONGRID*)Args[0];
            csBUTTONGRID*pages=(csBUTTONGRID*)Args[1];
            int i = hider->getActiveItem();
            int lastItem = pages[i].getItemNumber()-1;
            RECT rlastItem = *(pages[i].getItemRect(lastItem));

            RECT r2 = cv.CNTRECT[id2], r3 = cv.CNTRECT[id3], r3p = rectInParentRef(id3, r3),
                    rpg = cv.CNTRECT[pages[i].getId()];
            int dx = r2.right-r2.left - (r3p.left + rlastItem.left + rlastItem.right);

            if(dx > 0)
            {
                int dx_left = r2.left - rpg.left;
                dx = std::min(dx, dx_left);
                cv.cp[id3]->AutoTransform.Time = 16;
                cv.cp[id3]->AutoTransform.Type = AUTO_TRANSF_LENGTH;
                cv.cp[id3]->AutoTransform.InitialRect = r3p;
                cv.cp[id3]->AutoTransform.FinalRect={dx,0,0,0};
                cv.AUTOTRANSCOUNT[id3] = 0;
            }

        }
        count3--;
    }
}

void hsTest(int idp)
{
    csLIST<csBUTTONGRID> pages;
    int n = 2;
    SIZE imsz = {-1,-1};
    char str[10];
    for(int i=0; i<n; i++)
    {
        csBUTTONGRID bg(idp, {2,40, (600)/2, 1}, 10-2*i);
        bg.setFont("Calibri", {12,0});
        bg.setTextMarging(1,0);
        bg.setMarging(0,0);
        sprintf(str,"icon %d ...", i);
        bg.makeNTemplate((char*)str, "img\\app\\template_icon.bmp", imsz);
        bg.create();
        pages.insertEnd(bg);
    }

    csBUTTONGRID* phider = csf_alloc<csBUTTONGRID>(1);
    csBUTTONGRID hider(idp,{2,2,100/2,20/2},2);
    hider.setFont("Calibri", {12,0});
    hider.setTextMarging(1,1);
    hider.setMarging(0,0);
    hider.makeNTemplate("item 1", "img\\app\\template_icon.bmp", imsz);
    hider.create();

    *phider = hider;

    csTEXTBUTTON_GROUP*tbg;
    csPAGEFLIPPING_VARS* hs = csPageBGHider(pages, phider, idp, {0,200,300,50},tbg);
}

void hsTest2(int idp)
{
    int n = 0;
    csPAGES pgs(idp, idp, {200, 50, 200, 50});
    pgs.initIndexer({0,0,200,25},{2,2,500/2, 30/2}, 2,1);

    int maxItemNum = 20;
    char*path = "img\\app\\template_icon.bmp";
    csBGRID_PARAMS bgp = {2,2,500/2, 50/2};
    pgs.newPage("Menu 1", bgp, maxItemNum);
    pgs.getPage(n)->newBItem({0},{10,10},"Button 11",path,path,path);
    pgs.getPage(n)->newBItem({-1,-1},{10,10},"Button 12",path,path,path);
    pgs.getPage(n)->newBItem({-1,-1},{10,10},"Button 13",path,path,path);
    pgs.getPage(n)->newBItem({-1,-1},{10,10},"Button 14",path,path,path);
    n++;
    pgs.newPage("Menu 2", bgp, maxItemNum);
    pgs.getPage(n)->newBItem({0},{10,10},"Button 21",path,path,path);
    pgs.getPage(n)->newBItem({-1},{10,10},"Button 22",path,path,path);
    pgs.getPage(n)->newBItem({-1},{10,10},"Button 23",path,path,path);
    pgs.getPage(n)->newBItem({-1},{10,10},"Button 24",path,path,path);
    pgs.getPage(n)->newBItem({-1},{10,10},"Button 25",path,path,path);
    pgs.getPage(n)->newBItem({-1},{10,10},"Button 26",path,path,path);
    n++;

    pgs.create();
}


/**************************************************************************************** */
csPAGES::csPAGES(int idp_pages, int idp_indexer, RECT geom_pages)
{
    init(idp_pages, idp_indexer, geom_pages);
}

void csPAGES::init(int _idp_pages, int _idp_indexer, RECT _geom_pages)
{
    pages.init(1);
    indexer = 0;
    indexer = csf_alloc<csBUTTONGRID>(1);
    idp_pages = _idp_pages;
    idp_indexer = _idp_indexer;
    geom_pages = _geom_pages;
}

csBUTTONGRID* csPAGES::getIndexer()
{
    return indexer;
}

csBUTTONGRID* csPAGES::getPage(int i)
{
    return &pages[i];
}
csBUTTONGRID* csPAGES::getPages()
{
    return pages.getTable();
}

csTEXTBUTTON_GROUP* csPAGES::getIndexerBGroup()
{
    return indxBgp;
}

csTEXTBUTTON_GROUP* csPAGES::getPagesBGroup()
{
    return pgBgp;
}

void csPAGES::newPage(char*title, csBGRID_PARAMS pageParams, int nItemWidth)
{

    if(pages.size() == 0)
        indexer->newBItem({0},{0},title);
    else
        indexer->newBItem({-1,-1},{0},title);

    csBUTTONGRID bg;
    bg.init(idp_indexer, pageParams, nItemWidth, 1);
    pages.insertEnd(bg);
}

void csPAGES::initIndexer(RECT geometry, csBGRID_PARAMS bgpar, int nItemWidth, bool withSideButton)
{
    if(withSideButton)
    {
        indxBgp = 0;
        indxBgp = (csTEXTBUTTON_GROUP*)malloc(sizeof(csTEXTBUTTON_GROUP));
        bool orient = geometry.right > geometry.bottom ? 0 : 1;
        csTEXTBUTTON_GROUP _tbg(idp_indexer, geometry, orient);
        if(!orient)
            _tbg.setTotalLength(bgpar.dx*bgpar.nx);
        else
            _tbg.setTotalLength(bgpar.dy*bgpar.ny);

        _tbg.setMarging(2);
        _tbg.create();
        *indxBgp = _tbg;

        indexer->init(_tbg.getIDC3(), bgpar, nItemWidth, 0);
        indexer->setFont("Calibri", {12,0});
        indexer->setTextMarging(1,1);
        indexer->setMarging(0,0);

        int idc3 = indxBgp->getIDC3();
        csARGS args(2);
        args.makeArgs(indexer, indxBgp);
        csSetAction(idc3, WM_LBUTTONUP, reposIDC3indexer, args);
        //csSetAction(indx, WM_TIMER, autoFrameActiveItem, args);
    }
    else
    {
        indexer->init(idp_indexer, bgpar, nItemWidth, 0);
        indexer->setFont("Calibri", {12,0});
        indexer->setTextMarging(1,1);
        indexer->setMarging(0,0);
    }


}

void csPAGES::create()
{
    indexer->create();
    int n = pages.size();
    for(int i=0; i<n; i++)
    {
        pages[i].create();
    }
    pgBgp = 0;
    pfv = csPageBGHider(pages, indexer, idp_pages, geom_pages,pgBgp);
}

/**************************************************************************************** */


void csSetParent(int id, int idp)
{
    SetParent(cv.CNTLIST[id], cv.CNTLIST[idp]);
    cv.cp[id]->ClingToParent = 1;
    cv.CNTPARID[id] = idp;
}

void csDetachCnt(int id)
{
    SetParent(cv.CNTLIST[id],0);
    cv.cp[id]->ClingToParent = 0;
}


void csDrawGDIRectangle(HDC dc, COLORREF brush, COLORREF pen, int border, RECT r)
{
    HBRUSH hb = CreateSolidBrush(brush);
    HPEN hp = CreatePen(0,border,pen);
    SelectBrush(dc,hb);
    SelectPen(dc,hp);
    Rectangle(dc,r.left, r.top, r.right, r.bottom);
    DeletePen(hp);
    DeleteBrush(hb);
}
