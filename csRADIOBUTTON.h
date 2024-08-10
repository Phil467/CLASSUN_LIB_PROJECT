#ifndef CSRADIOBUTTON_H
#define CSRADIOBUTTON_H
#include "csCONTAINER.h"
#include "genStruct.h"
#include "utlFx.h"
#include "csBUTTON.h"

#define CS_RDBTN_GRID_HV  100
#define CS_RDBTN_GRID_VH  200
#define CS_RDBTN_GRID_NONE  300

#define CS_RDBTN_TEXT_H  10
#define CS_RDBTN_TEXT_V1  20
#define CS_RDBTN_TEXT_V2  21

#define CS_RDBTN_TEXT_BEFORE  1
#define CS_RDBTN_TEXT_AFTER  2
#define CS_RDBTN_TEXT_OVER  3
#define CS_RDBTN_TEXT_UNDER  4


typedef struct csRB_ITEM
{
    char* title;
    RECT pos;
    POINT posImg;
    POINT posTitle;
    HFONT font;
    COLORREF color0, color1, color2, color3, color4;
    COLORREF bkgcol0, bkgcol1, bkgcol2, bkgcol3, bkgcol4;
    HDC dcs0, dcs1, dcs2, dcs3, dcs4;
};

class csRADIOBUTTON
{
    public:
        csRADIOBUTTON(int idp = 0, int gridStyle=CS_RDBTN_GRID_HV, int gridWidth = 1);
        void init(int idp = 0, int gridStyle=CS_RDBTN_GRID_HV, int gridWidth = 1);
        void setImageSize(SIZE size);
        void setImage(char*path1, char*path2,char*path3,char*path4,SIZE size);
        void setParent(int idp);
        void setGridWidth(int gridWidth);
        void setRect(int id, RECT r);
        void setOrientation(int orient);
        void setOffset(SIZE _offset);
        void setMarging(SIZE _marging);
        void setTitle(int id, char* title);
        void setDefaultTitle(char* dfltTitle);
        void setTitles(char* ids[], char* _title[], int n);
        void setDefaultFont(char* fnt, SIZE size);
        void setFont(int id, char* fnt, SIZE size);
        void setColors(int id,COLORREF color, COLORREF highlightColor, COLORREF selectionColor);
        void setDefaultColors(COLORREF color, COLORREF highlightColor, COLORREF selectionColor);
        void setDefaultSize(SIZE size);
        void zebraStyle(csRGBA zcol, float zFactor);
        void newItem(char*title=0, RECT r={0}, int n=1, char*img1=0, char*img2=0, char*img3=0, char*img4=0);
        int* getActiveItem();
        int* getMouseOverItem();
        void setActiveItem(int id);
        void moveItem(int from, int to);
        void setMouseOverItem(int id);
        void updateActiveItem(int id);
        void unActivateItem(int id);
        void refresh();
        void organize();
        void create();
        bool* getCntState();
        void setCntState(bool activate);
        void autoRepos();
        
        void removeItem(int id);
        void getUsefulEventsNumber();
        void copyItem(int id);
        void cutItem(int id);
        void pasteItem(int id);
        void copyPasteStyle();
        bool* getCopyPasteState();
        int* getCopyPasteKeyDownState();
        void duplicate(int src, int pos);
        int getId();
        
        int getSize();
        bool *click_message = 0;
        void* (*pf)();
        virtual ~csRADIOBUTTON();

    protected:
        char*defaultItemTitle();
        void animate();

    private:
    int parent;
    csLIST<char*> title;
    char*dfltTitle;
    csLIST<RECT> pos;
    csLIST<POINT> posImg;
    csLIST<POINT> posTitle;
    csLIST<COLORREF> color0;
    csLIST<COLORREF> color1;
    csLIST<COLORREF> color2;
    csLIST<COLORREF> color3;
    csLIST<COLORREF> color4;
    csLIST<COLORREF> bkgcol0;
    csLIST<COLORREF> bkgcol1;
    csLIST<COLORREF> bkgcol2;
    csLIST<COLORREF> bkgcol3;
    csLIST<COLORREF> bkgcol4;
    csLIST<HFONT> font;
    HFONT dfltFont;
    csRGBA defcol;
    COLORREF dfltColor1, dfltColor2, dfltColor3, dfltColor4;
    COLORREF dfltBkgCol1, dfltBkgCol2, dfltBkgCol3, dfltBkgCol4;
    SIZE dfltSz, *pdfltSz;
    int gridStyle;
    int textOrientation;
    int TextPos;
    SIZE marging, *pmarging;
    SIZE offset, *poffset;
    SIZE fontSize, imgSize, *pimgSize;
    csDC imgdc1, imgdc2, imgdc3, imgdc4;
    HDC hdc, *phdc;
    int gridWidth, *pgridWidth;
    csLIST<HDC> dcs0;
    csLIST<HDC> dcs1;
    csLIST<HDC> dcs2, dcs3, dcs4;
    int* lastMouseOverid;
    int* lastMouseClickid;
    int*n;
    csARGS args;
    bool activeChoosed, *cntActivate, animated;
    int *vkCtrlCount, *vkCtrlCountControl;
    POINT *vkCtrlPoint, *vkCtrlGdcPos;
    int *smoothRepos;
    int *smoothReposCount;
    float zebFact;
    csRGBA zebColor;

    csRB_ITEM rbItem;

    int iter;

    int *cutPasteViewer;
    bool *cutPasteStart, *cutPasteDone, *cutPasteDone0;
    int *copyPasteKeyDownState;

    int moveMsgPos, lbtnDownMsgPos, lbtnUpMsgPos, leaveMsgPos, timerMsgPos, keyDownMsgPos, keyUpMsgPos;
};

void organize2(int parent, int n, SIZE imgSize,
                RECT*pos,POINT*posImg,POINT*posTitle, HDC* dcs0, HFONT* font, COLORREF* color0, COLORREF* bkgcol0, char**title, HDC hdc);
void colorTracking(int parent, int lastItem, int currentItem, int n, SIZE imgSize,
                RECT*pos,POINT*posImg,POINT*posTitle, HDC* dcs0, HFONT* font,
                 COLORREF* color0, COLORREF* bkgcol0, char**title, HDC hdc);
#endif // CSRADIOBUTTON_H
