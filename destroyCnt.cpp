#include "csCONTAINER.h"

extern csCNTR_VARS cv;

void destroyContainer_Init(csARGS Args)
{
    int id = *(int*)Args[0];
    cv.DESTROY_GROUP=getCntChilds(id);
    int n = cv.DESTROY_GROUP.size();
    for(int i=n-1; i>=0; i--)
    {
        SendMessage(cv.CNTLIST[cv.DESTROY_GROUP[i]], WM_DESTROY,0,0);
        std::cout<<cv.DESTROY_GROUP[i]<<"  dest--\n";
    }
    cv.DESTROY_GROUP.minMaxSortL();
    cv.DESTROY_ITER = 0;
}

void destroyContainer_clearVars()
{
    static int last=-1;
    int n = cv.DESTROY_GROUP.size();
    if(cv.DESTROY_ITER<n)
    {
        int i = cv.DESTROY_ITER;
        if(last<cv.DESTROY_GROUP[i] && last>-1)
            destroyContainerVars(cv.DESTROY_GROUP[i]-1);
        else
            destroyContainerVars(cv.DESTROY_GROUP[i]);
    std::cout<<"destroying Container "<<cv.DESTROY_GROUP[i]<<"\n";
        last = cv.DESTROY_GROUP[i];
        cv.DESTROY_ITER++;
        if(cv.DESTROY_ITER == n)
        {
            int a = cv.ID.size();
            for(int j=0; j<n; j++)
            {
                int e1 = *cv.idPtr(cv.DESTROY_GROUP[j]);
                cv.ID[e1]=-1;
                for(int k=e1; k<a; k++)
                {
                    cv.ID[k]-=1;
                }
            }
            cv.DESTROY_ITER=-1;
        }
    }
}

void destroyContainer_End()
{
    if(cv.REID_ITER >-1)
    {
        int n = cv.DESTROY_GROUP.size();
        if(cv.REID_ITER<n)
        {

        }
        cv.DESTROY_GROUP.clear();
        cv.REID_ITER++;
    }
}


void destroyContainer(csARGS Args)
{
    int id = *(int*)Args[0];
    csLIST<int> list=getCntChilds(id);
    int n = list.size();
    for(int i=n-1; i>=0; i--)
    {
        SendMessage(cv.CNTLIST[list[i]], WM_DESTROY,0,0);
        std::cout<<list[i]<<"  dest--\n";
    }
    static int last=-1;
    for(int i=0; i>=0; i--)
    {
        std::cout<<"destroying Container "<<list[i]<<"\n";
        if(last<list[i] && last>-1)
            destroyContainerVars(list[i]-1);
        else
            destroyContainerVars(list[i]);
        last = list[i];
    }
    list.clear();
}

csLIST<int> getCntChilds(int id)
{
    csLIST<int> list;
    list.insertEnd(id);
    int n=cv.CNTPARID.size();
    for(int j=0; j<list.size(); j++)
    {
        for(int i=0; i<n; i++)
        {
            if(cv.CNTPARID[i]==list[j])
                list.insertEnd(i);
        }
        std::cout<<list[j]<<" ";
    }
    std::cout<<"\n";
    return list;
}
void destroyContainerVars(int id)
{
    cv.CNTLIST.deleteAt(id);
    cv.CNTPARLIST.deleteAt(id);
    cv.CNTRECT.deleteAt(id);
    cv.CNTRECT_SAVED.deleteAt(id);
    cv.CNTCLRECT.deleteAt(id);
    cv.CNTCLWRECT.deleteAt(id);
    cv.CNTCLWRECT_SAVED.deleteAt(id);
    cv.CTX.deleteAt(id);
    cv.CNTDC.deleteAt(id);
    //csLIST<bool>                                            CNTALLOWDRAW;
    //csLIST<bool>                                            CNTDRAWSIGNAL;
    //csLIST<csPOINT2F>                                       CNTDRAWPOINTS;
    //csLIST<int>                                             CNTDRAWTYPE;
    cv.lkt.deleteAt(id);
    cv.CNTPARID.deleteAt(id);
    cv.CNTOLDZOOMFACTOR.deleteAt(id);
    deletePointerList<csDC_METRICS>(id,cv.DCMETRICS);

    cv.LOCKLINK.deleteAt(id);
    deleteListList<int>(id, cv.IDCNTLEFTLINK);
    deleteListList<int>(id, cv.IDCNTRIGHTLINK);
    deleteListList<int>(id, cv.IDCNTTOPLINK);
    deleteListList<int>(id, cv.IDCNTBOTTOMLINK);
    cv.LEFTLINKSIGNAL.deleteAt(id);
    cv.TOPLINKSIGNAL.deleteAt(id);
    cv.RIGHTLINKSIGNAL.deleteAt(id);
    cv.BOTTOMLINKSIGNAL.deleteAt(id);
    cv.SHOWWINDOWSIGNAL.deleteAt(id);
    cv.HIDEWINDOWSIGNAL.deleteAt(id);
    cv.MOUSEHOVERSIGNAL.deleteAt(id);
    cv.MOUSEHOVERCOUNT.deleteAt(id);
    cv.CLICKGRADIENTCOUNT.deleteAt(id);
    cv.AUTOTRANSCOUNT.deleteAt(id);
    cv.TIMEREVENTFUNCCOUNT.deleteAt(id);
    cv.CATCHLASTGEOMETRY.deleteAt(id);
    cv.CATCHLASTPARENT.deleteAt(id);
    cv.CNTCREATION.deleteAt(id);
    cv.CNTBORDERCLICKED.deleteAt(id);
    cv.CNTHITALLOW.deleteAt(id);
    deleteListList<csDC>(id, cv.MHGRADIENTDC);
    cv.DCLOCK.deleteAt(id);
    cv.ClassName.deleteAt(id);

    if(cv.cp[id]->CntEventsFunc.LBUTTONDOWN.size())
    {
        cv.cp[id]->CntEventsFunc.LBUTTONDOWN.clear();
        int n = cv.cp[id]->CntEventsFunc.LBUTTONDOWN_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.LBUTTONDOWN_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.LBUTTONDOWN_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN.size())
    {
        cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN.clear();
        int n = cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.NCLBUTTONDOWN_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.RBUTTONDOWN.size())
    {
        cv.cp[id]->CntEventsFunc.RBUTTONDOWN.clear();
        int n = cv.cp[id]->CntEventsFunc.RBUTTONDOWN_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.RBUTTONDOWN_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.RBUTTONDOWN_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN.size())
    {
        cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN.clear();
        int n = cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.NCRBUTTONDOWN_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.MBUTTONDOWN.size())
    {
        cv.cp[id]->CntEventsFunc.MBUTTONDOWN.clear();
        int n = cv.cp[id]->CntEventsFunc.MBUTTONDOWN_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.MBUTTONDOWN_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.MBUTTONDOWN_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.NCMBUTTONDOWN.size())
    {
        cv.cp[id]->CntEventsFunc.NCMBUTTONDOWN.clear();
        int n = cv.cp[id]->CntEventsFunc.NCMBUTTONDOWN_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.NCMBUTTONDOWN_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.NCMBUTTONDOWN_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.LBUTTONUP.size())
    {
        cv.cp[id]->CntEventsFunc.LBUTTONUP.clear();
        int n = cv.cp[id]->CntEventsFunc.LBUTTONUP_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.LBUTTONUP_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.LBUTTONUP_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.NCLBUTTONUP.size())
    {
        cv.cp[id]->CntEventsFunc.NCLBUTTONUP.clear();
        int n = cv.cp[id]->CntEventsFunc.NCLBUTTONUP_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.NCLBUTTONUP_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.NCLBUTTONUP_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.RBUTTONUP.size())
    {
        cv.cp[id]->CntEventsFunc.RBUTTONUP.clear();
        int n = cv.cp[id]->CntEventsFunc.RBUTTONUP_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.RBUTTONUP_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.RBUTTONUP_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.NCRBUTTONUP.size())
    {
        cv.cp[id]->CntEventsFunc.NCRBUTTONUP.clear();
        int n = cv.cp[id]->CntEventsFunc.NCRBUTTONUP_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.NCRBUTTONUP_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.NCRBUTTONUP_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.MBUTTONUP.size())
    {
        cv.cp[id]->CntEventsFunc.MBUTTONUP.clear();
        int n = cv.cp[id]->CntEventsFunc.MBUTTONUP_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.MBUTTONUP_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.MBUTTONUP_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.NCMBUTTONUP.size())
    {
        cv.cp[id]->CntEventsFunc.NCMBUTTONUP.clear();
        int n = cv.cp[id]->CntEventsFunc.NCMBUTTONUP_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.NCMBUTTONUP_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.NCMBUTTONUP_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK.size())
    {
        cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK.clear();
        int n = cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.LBUTTONDBLCLK_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.NCLBUTTONDBLCLK.size())
    {
        cv.cp[id]->CntEventsFunc.NCLBUTTONDBLCLK.clear();
        int n = cv.cp[id]->CntEventsFunc.NCLBUTTONDBLCLK_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.NCLBUTTONDBLCLK_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.NCLBUTTONDBLCLK_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK.size())
    {
        cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK.clear();
        int n = cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.RBUTTONDBLCLK_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.NCRBUTTONDBLCLK.size())
    {
        cv.cp[id]->CntEventsFunc.NCRBUTTONDBLCLK.clear();
        int n = cv.cp[id]->CntEventsFunc.NCRBUTTONDBLCLK_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.NCRBUTTONDBLCLK_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.NCRBUTTONDBLCLK_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK.size())
    {
        cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK.clear();
        int n = cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.MBUTTONDBLCLK_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.NCMBUTTONDBLCLK.size())
    {
        cv.cp[id]->CntEventsFunc.NCMBUTTONDBLCLK.clear();
        int n = cv.cp[id]->CntEventsFunc.NCMBUTTONDBLCLK_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.NCMBUTTONDBLCLK_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.NCMBUTTONDBLCLK_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.MOUSEMOVE.size())
    {
        cv.cp[id]->CntEventsFunc.MOUSEMOVE.clear();
        int n = cv.cp[id]->CntEventsFunc.MOUSEMOVE_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.MOUSEMOVE_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.MOUSEMOVE_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.MOUSEHOVER.size())
    {
        cv.cp[id]->CntEventsFunc.MOUSEHOVER.clear();
        int n = cv.cp[id]->CntEventsFunc.MOUSEHOVER_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.MOUSEHOVER_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.MOUSEHOVER_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.MOUSELEAVE.size())
    {
        cv.cp[id]->CntEventsFunc.MOUSELEAVE.clear();
        int n = cv.cp[id]->CntEventsFunc.MOUSELEAVE_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.MOUSELEAVE_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.MOUSELEAVE_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.MOVE.size())
    {
        cv.cp[id]->CntEventsFunc.MOVE.clear();
        int n = cv.cp[id]->CntEventsFunc.MOVE_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.MOVE_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.MOVE_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.SIZE.size())
    {
        cv.cp[id]->CntEventsFunc.SIZE.clear();
        int n = cv.cp[id]->CntEventsFunc.SIZE_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.SIZE_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.SIZE_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.SETFOCUS.size())
    {
        cv.cp[id]->CntEventsFunc.SETFOCUS.clear();
        int n = cv.cp[id]->CntEventsFunc.SETFOCUS_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.SETFOCUS_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.SETFOCUS_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.CREATE.size())
    {
        cv.cp[id]->CntEventsFunc.CREATE.clear();
        int n = cv.cp[id]->CntEventsFunc.CREATE_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.CREATE_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.CREATE_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.DESTROY.size())
    {
        cv.cp[id]->CntEventsFunc.DESTROY.clear();
        int n = cv.cp[id]->CntEventsFunc.DESTROY_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.DESTROY_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.DESTROY_ARGS.clear();

    }
    if(cv.cp[id]->CntEventsFunc.TIMER.size())
    {
        cv.cp[id]->CntEventsFunc.TIMER.clear();
        int n = cv.cp[id]->CntEventsFunc.TIMER_ARGS.size();
        for(int i=0; i<n; i++)
            cv.cp[id]->CntEventsFunc.TIMER_ARGS[i].freeArgs();
        cv.cp[id]->CntEventsFunc.TIMER_ARGS.clear();
    }
    cv.cp.deleteAt(id);

}

