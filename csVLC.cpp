#include "csVLC.h"
void resizingfunc(csARGS Args);
csVLC::csVLC(int* _idp, int _lmarg, int _rmarg, int _offset)
{
    init(_idp, _lmarg, _rmarg, _offset);
}

extern csCNTR_PARAMS cscp;
extern csCNTR_VARS cv;

void csVLC::init(int* _idp, int _lmarg, int _rmarg, int _offset)
{
    ids.init(1);
    minSizes.init(1);
    maxSizes.init(1);
    glps.init(1);
    widthRatios.init(1);
    totalLen = 0;
    totalLen = csf_alloc2<int>(1,0);
    lMarg = _lmarg;
    rMarg = _rmarg;
    offset = _offset;
    idp = _idp;
    dcSize = {0};
    tMarg = 3;
    bMarg = 6;

    TimerMessagePos.init(1);
    GroupMessagePos.init(1);
    ParSizeMessagePos = csPARAMS(*_idp)->CntEventsFunc.SIZE.size();

}

void csVLC::setDCSize(SIZE size)
{
    dcSize = size;
}

int csVLC::getContainerId(int i)
{
    return ids[i];
}

int* csVLC::getContainerId_Ptr(int i)
{
    return &ids[i];
}

void csVLC::autoUpdate(int i, bool update)
{
    glps[i]->Update = update;
}

void csVLC::newContainer(int*_id, int _minSize, int _maxSize)
{
    csRGBA GEN_COL = csPARAMS(*idp)->BackgroundColor;
    //if(create)
    {
        minSizes.insertEnd(_minSize);
        maxSizes.insertEnd(_maxSize);
        int i = ids.size(), marg = lMarg+rMarg;
        int len = (csCLRECT(*idp).right-2*marg-i*offset);

        if(i >= 1)
        {
            csPARAMS(ids[i-1])->SizingAreaLength = 2;
            csPARAMS(ids[i-1])->HTRight = 1;
        }

        float irat= 1.0/(i+1), reductionRatio = i*irat;
        for(int j = 0; j<i; j++)
        {
            widthRatios[j] *= reductionRatio;
            glps[j]->l.a *= reductionRatio;
            glps[j]->r.a *= reductionRatio;
        }
        widthRatios.insertEnd(irat);
        int id;
        if(!_id)
        {
            id = staticCnt2(cscp, *idp, 0, GEN_COL, {0},1,0.01, dcSize);
            int nbr = 2;
            int sharp = 1.9;
            cv.cp[id]->TitleAlign = CS_TA_CENTER;
            cv.cp[id]->MHGradient.Color2 = GEN_COL;
            cv.CTX[id].borderGradientColor = GEN_COL;
            cv.CTX[id].brdGrad_right = {nbr,5,0,1,sharp};
            cv.CTX[id].brdGrad_bottom = {nbr,5,0,1,sharp};
            cv.CTX[id].setCntBorder(csTint(GEN_COL,{0},0.1),1);
            //cv.CTX[id].setCntBorder(GEN_COL,1);
        }
        else
            id=*_id;

        *totalLen = marg+i*offset;
        glps.insertEnd(csGLP4_PTR({id, {*totalLen,reductionRatio,lMarg+i*offset}, {0,0,tMarg}, {*totalLen,irat,0}, {bMarg,1.0,0}}));

        ids.insertEnd(id);
        csPARAMS(id)->MinTrackSize = {_minSize, csPARAMS(*idp)->Geometry.bottom};

        //suppress old events occurring, and create new ones at the end of events list
        for(int j=0; j<i; j++)
        {
            csPARAMS(ids[j])->CntEventsFunc.TIMER.deleteAt(TimerMessagePos[j]);
            csPARAMS(ids[j])->CntEventsFunc.TIMER_ARGS.deleteAt(TimerMessagePos[j]);
            TimerMessagePos[j] = csPARAMS(ids[j])->CntEventsFunc.TIMER.size();
            if(i>1 && j>0)
            {
                int j1 = j-1;
                cv.GROUPED_EVENTS_FUNC[ids[j1]].deleteAt(GroupMessagePos[j1]);
                cv.GROUPED_EVENTS_ARGS[ids[j1]].deleteAt(GroupMessagePos[j1]);
            }
            GroupMessagePos[j] = cv.GROUPED_EVENTS_ARGS[ids[j]].size();
            csARGS args(4);
            args.makeArgs(glps[j], glps[j+1], totalLen, &minSizes);
            csSetGroupedAction(ids[j], resizingfunc, args);
        }

        if(i>0)
        {
            csPARAMS(*idp)->CntEventsFunc.SIZE.deleteAt(ParSizeMessagePos);
            csPARAMS(*idp)->CntEventsFunc.SIZE_ARGS.deleteAt(ParSizeMessagePos);
        }
        ParSizeMessagePos = csPARAMS(*idp)->CntEventsFunc.SIZE.size();

        TimerMessagePos.insertEnd(csPARAMS(id)->CntEventsFunc.TIMER.size());
        GroupMessagePos.insertEnd(cv.GROUPED_EVENTS_FUNC[id].size());

        csGeometryLink(idp, ids.size(), glps.getTable());

    }
}

void resizingfunc(csARGS Args)
{
    UINT msg = (UINT)Args;
    // float f = *(float*)Args[4];
    // float fn1 = *(float*)Args[5];
    // float fn2 = *(float*)Args[6];
    static float f = 0.0;
    static float fn1 = 0.0;
    static float fn2 = 0.0;
    csGLP4* glp = (csGLP4*)Args[0];
    csGLP4* glpn = (csGLP4*)Args[1];
    static int maxsize;
    csLIST<int> minSzn = *(csLIST<int>*)Args[3];

    if(msg == WM_NCLBUTTONDOWN)
    {
        f = glp->r.a;
        fn1 = glpn->l.a;
        fn2 = glpn->r.a;

        maxsize = csCLRECT(glp->id).right + csCLRECT(glpn->id).right - 20;
        csPARAMS(glp->id)->MaxTrackSize = {maxsize, CS_CYSCREEN};
    }

    else if(msg == WM_SIZE && cv.HWNDFOCUS == (HWND)Args && minSzn.size()>1)
    {
        csGLP4* glp = (csGLP4*)Args[0];
        csGLP4* glpn = (csGLP4*)Args[1];
        int totalLen = csCLRECT(cv.CNTPARID[glp->id]).right - *(int*)Args[2];

        int idNext = glpn->id;
        int delta=0;
        csSizeSyncDeltaX(int(Args),delta);

        RECT rn = csWRECT_S(idNext);
        RECT rp = csWRECT_S(cv.CNTPARID[glp->id]);

        int cx = rn.right-rn.left-delta;
        SetWindowPos(csHWND(idNext),HWND_BOTTOM,rn.left-rp.left+delta, rn.top-rp.top, cx, rn.bottom-rn.top, SWP_NOZORDER);
//std::cout<<*(int*)Args[2]<<" totalen\n";
        float dRat = delta*1.0/totalLen;

        glp->r.a = f + dRat;
        glpn->l.a = fn1 + dRat;
        glpn->r.a = fn2 - dRat;

        if(glp->Update)
        {
            InvalidateRect(HWND(Args), 0, 1);
            InvalidateRect(csHWND(idNext), 0, 1);
        }
    }

}


csVLC::~csVLC()
{
    //dtor
}
