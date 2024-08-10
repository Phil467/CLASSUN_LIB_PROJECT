#include "csHLC.h"

void resizingfunc_(csARGS Args);
csHLC::csHLC(int* _idp, int _tmarg, int _bmarg, int _offset)
{
    init(_idp, _tmarg, _bmarg, _offset);
}

extern csCNTR_PARAMS cscp;
extern csCNTR_VARS cv;

void csHLC::init(int* _idp, int _tmarg, int _bmarg, int _offset)
{
    ids.init(1);
    minSizes.init(1);
    maxSizes.init(1);
    glps.init(1);
    widthRatios.init(1);
    totalLen = 0;
    totalLen = csf_alloc2<int>(1,0);
    tMarg = _tmarg;
    bMarg = _bmarg;
    offset = _offset;
    idp = _idp;
    dcSize = {0};
    lMarg = 3;
    rMarg = 6;

    TimerMessagePos.init(1);
    GroupMessagePos.init(1);
    ParSizeMessagePos = csPARAMS(*_idp)->CntEventsFunc.SIZE.size();

}

void csHLC::setDCSize(SIZE size)
{
    dcSize = size;
}

int csHLC::getContainerId(int i)
{
    return ids[i];
}

int* csHLC::getContainerId_Ptr(int i)
{
    return &ids[i];
}

void csHLC::autoUpdate(int i, bool update)
{
    glps[i]->Update = update;
}

void csHLC::newContainer(int*_id, int _minSize, int _maxSize)
{
    //if(create)
    {
        minSizes.insertEnd(_minSize);
        maxSizes.insertEnd(_maxSize);
        int i = ids.size(), marg = tMarg+bMarg;
        int len = (csCLRECT(*idp).bottom-2*marg-i*offset);

        if(i >= 1)
        {
            csPARAMS(ids[i-1])->SizingAreaLength = 2;
            csPARAMS(ids[i-1])->HTBottom = 1;
        }

        float irat= 1.0/(i+1), reductionRatio = i*irat;
        for(int j = 0; j<i; j++)
        {
            widthRatios[j] *= reductionRatio;
            glps[j]->t.a *= reductionRatio;
            glps[j]->b.a *= reductionRatio;
        }
        widthRatios.insertEnd(irat);
        int id;
        if(!_id)
        {
            csRGBA GEN_COL = csPARAMS(*idp)->BackgroundColor;
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
        glps.insertEnd(csGLP4_PTR({id, {0,0,lMarg}, {*totalLen,reductionRatio,tMarg+i*offset}, {rMarg,1.0,0}, {*totalLen,irat,0}}));

        ids.insertEnd(id);
        csPARAMS(id)->MinTrackSize = {csPARAMS(*idp)->Geometry.right, _minSize};

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
            csSetGroupedAction(ids[j], resizingfunc_, args);

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

void resizingfunc_(csARGS Args)
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
    //csLIST<int> minSzn = *(csLIST<int>*)Args[3];

    if(msg == WM_NCLBUTTONDOWN)
    {
        f = glp->b.a;
        fn1 = glpn->t.a;
        fn2 = glpn->b.a;

//std::cout<<minSzn.size()<<" minSzn.size()\n";
        maxsize = csCLRECT(glp->id).bottom + csCLRECT(glpn->id).bottom - 20;
        csPARAMS(glp->id)->MaxTrackSize = {CS_CXSCREEN,maxsize};
    }

    else if(msg == WM_SIZE && cv.HWNDFOCUS == (HWND)Args/*  && minSzn.size()>1 */)
    {
        int totalLen = csCLRECT(cv.CNTPARID[glp->id]).bottom - *(int*)Args[2];

        int idNext = glpn->id;
        int delta=0;
        csSizeSyncDeltaY(int(Args),delta);

        RECT rn = csWRECT_S(idNext);
        RECT rp = csWRECT_S(cv.CNTPARID[glp->id]);

        SetWindowPos(csHWND(idNext),HWND_BOTTOM,rn.left-rp.left, rn.top-rp.top+delta, rn.right-rn.left, rn.bottom-rn.top-delta, SWP_NOZORDER);

        float dRat = delta*1.0/totalLen;

        glp->b.a = f + dRat;
        glpn->t.a = fn1 + dRat;
        glpn->b.a = fn2 - dRat;

        if(glp->Update)
        {
            InvalidateRect(HWND(Args), 0, 1);
            InvalidateRect(csHWND(idNext), 0, 1);
        }
    }

}
