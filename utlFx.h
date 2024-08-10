#ifndef UTLFX_H
#define UTLFX_H

#include "csCONTAINER.h"
#include "csBUTTONGRID.h"
#include "csBUTTON_GROUP.h"

class utlFx
{
    public:
        utlFx();
        virtual ~utlFx();

    protected:

    private:
};

class csPAGEFLIPPING_VARS
{
public:
    csPAGEFLIPPING_VARS(RECT dR={0,10,0,0})
    {
        cslk = 0;
        b_allow_click_after_anim_ends = 0;
        mxcount = 8;
        mxcount2 = 16;
        count = -1;
        count2 = mxcount2+2;
        transitionTime = 8;
        alphaMin = 100;
        dr=dR;
        bg=0;
        cntOrder = HWND_BOTTOM;
    }
    int hiderFromPage(int idPage)
    {
        //int n=sizeof(pages)/sizeof(pages[0]);
        int idHider=0;
        for(int i=0; i<*n_pages; i++)
        {
            if(idPage==pages[i])
            {
                idHider=hiders[i];
                break;
            }
        }
        return idHider;
    }
    int pageFromHider(int idHider)
    {
        //int n=sizeof(pages)/sizeof(pages[0]);
        int idPage=0;
        if(!bg)
        for(int i=0; i<*n_pages; i++)
        {
            if(idHider==hiders[i])
            {
                idPage=pages[i];
                break;
            }
        }
        else
            if(idHider<*n_pages)
                idPage = pages[idHider];
        return idPage;
    }

    bool cslk;
    int mxcount;
    int mxcount2;
    BYTE alphaMin;
    int count;
    int count2;
    int id;
    int active;
    int transitionTime;
    RECT r1, r2, dr={-10,0,0,0};
    bool b_allow_click_after_anim_ends = 0;
    int*hiders;
    int*pages;
    int active_hider;
    int* n_pages;
    csBUTTONGRID* bg;
    HWND cntOrder;
};



class csPAGES
{
private:
    csLIST<csBUTTONGRID> pages;
    csBUTTONGRID* indexer;
    int idp_pages;
    int idp_indexer;
    RECT geom_pages;
    csPAGEFLIPPING_VARS* pfv;
    csTEXTBUTTON_GROUP* indxBgp, *pgBgp;
public:
    csPAGES(int idp_pages=0, int idp_indexer=0, RECT geom_pages={0});
    void init(int _idp_pages, int _idp_indexer, RECT geom_pages);
    csBUTTONGRID* getIndexer();
    csBUTTONGRID* getPage(int i);
    csBUTTONGRID* getPages();
    csTEXTBUTTON_GROUP* getIndexerBGroup();
    csTEXTBUTTON_GROUP* getPagesBGroup();
    void newPage(char*title="", csBGRID_PARAMS pageParams={0}, int nItemWidth=2);
    void initIndexer(RECT geometry, csBGRID_PARAMS bgpar={0}, int nItemWidth=2, bool withSideButton=1);
    void create();
};


char*csSTR(const char* str);

RECT csSizeSyncDelta(int id, SIZE& delta);
RECT csSizeSyncDeltaX(int id, int& delta);
RECT csSizeSyncDeltaY(int id, int& delta);
RECT csPosSyncDelta(int id, SIZE& delta);
RECT csPosSyncDeltaX(int id, int& delta);
RECT csPosSyncDeltaY(int id, int& delta);
RECT csGeomSyncDelta(int id, RECT& delta);
void cnt_show_hide(csARGS Args);
void cnt_show_hide_click(csARGS Args);
void cntgroup_show_hide(csARGS Args);
void cntgroup_show_hide_click(csARGS Args);
RECT transformRect(RECT r, RECT dr, float iter, float maxiter);
RECT invTransformRect(RECT r, RECT dr, float iter, float maxiter);
csPAGEFLIPPING_VARS getHideShowVars(int* hiders, int* pages, int* n_ptr, csBUTTONGRID* bg=0, RECT drTransform={0,10,0,0});

void csTITLE(int id, char*title, csRGBA color={150,150,150}, char* font="book antiqua", int bold=FW_BOLD, bool italic=1, SIZE size={14});

void csAddColorFilter(int*id, csRGBA color, int cLevel);
csPAGEFLIPPING_VARS* csPageBGHider(csLIST<csBUTTONGRID> pages, csBUTTONGRID*hider, int idp_tbg, RECT tbgGeom,
                                csTEXTBUTTON_GROUP*&tbg, unsigned time1=2, unsigned time2=4, unsigned transTime=2);
void hsTest(int idp);
void hsTest2(int idp);
void csSetParent(int id, int idp);
void csDetachCnt(int id);
void csDrawGDIRectangle(HDC dc, COLORREF brush, COLORREF pen, int border, RECT r);



#endif // UTLFX_H
