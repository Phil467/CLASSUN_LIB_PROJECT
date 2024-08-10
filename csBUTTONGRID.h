#ifndef CSBUTTONGRID_H
#define CSBUTTONGRID_H
#include "csCONTAINER.h"
#include "csBUTTON.h"
//#include "csRADIOBUTTON.h"
#include "genStruct.h"
#include <windowsx.h>

#define CS_BGRD_GROUP_SELECTION 0
#define CS_BGRD_UNI_SELECTION 1
#define CS_BGRD_BI_SELECTION 2

typedef struct 
{
    int dx, dy, nx, ny;
}csBGRID_PARAMS;
typedef struct 
{
    float cfx, cfy;
}csPROPORTION;



class csBUTTONGRID
{
    public:
        csBUTTONGRID(int _idp=0, csBGRID_PARAMS bgpar={0}, int nItemWidth=2, bool newCnt=1);
        void init(int _idp, csBGRID_PARAMS bgpar, int _nItemWidth=2, bool newCnt=1);
        RECT newBItem(POINT pos, SIZE iconSize, char*title="",
                    char*icon1="", char*icon2="", char*icon3="", char*icon4="", bool enable=1, SIZE itemSize={0});
        void setFont(char*font, SIZE fsize);
        void setTitleColors(COLORREF c1, COLORREF c2, COLORREF c3, COLORREF c4);
        void setBItemBackgroundColors(COLORREF c1, COLORREF c2, COLORREF c3, COLORREF c4);
        void setBItemBordersColors(COLORREF c1, COLORREF c2, COLORREF c3, COLORREF c4);
        void setMouseHoverBackground(COLORREF c);
        void setTextPosition(int tpos);
        void setMarging(int xmarg, int ymarg);
        void setOffset(int xoff, int yoff);
        void create();
        void createItem(int iItem);
        void updateItem(int i);
        void setItemState(int i, bool state);
        void setActiveItem(int i);
        int getActiveItem();
        void enableItem(int i, bool _enable);
        void setItemType(int i, short type);
        void setTextMarging(int x, int y);
        void setItemTitle(int i, char*title);
        void setItemIcon(int i, char*icon1, char*icon2=0, char*icon3=0, char*icon4=0);
        int getTolalWidth();
        int makeNTemplate(char*defTitles, char*iconPath, SIZE unitSz, int n=1, SIZE itemSize={0});
        int makeNBItems(char**titles, char**iconPaths, SIZE unitSz);
        void setXRect_model01(int cx, int height);
        int getId();
        int getXLength();
        int getYLength();
        RECT* getItemRect(int i);
        void showTitle(bool show);
        csCNTR_PARAMS *getParams();
        bool* getItemState(int i);
        int getItemNumber();
        char* getTitle(int id);
        int makeNCopy(char**name, char**iconPath1, char**iconPath2, char**iconPath3, char**iconPath4, SIZE* iconSize, 
                            int n_copy, int _yoffset);

        void getUsefulEventsNumber();
        virtual ~csBUTTONGRID();

        bool *click_message=0;
    protected:
    POINT getNextPosition();
    int findId(POINT p);

    private:
    csBGRID_PARAMS* bgp;
    csLIST< csLIST<int> > map;
    csLIST<int> items;
    csLIST<RECT> itemRect;
    csLIST<RECT> textRect;
    csLIST<RECT> iconRect;
    csLIST<char*> itemTitle;
    csLIST< csLIST<HDC> > iconDC;
    csLIST< csLIST<COLORREF> > titleCol;
    csLIST< csLIST<COLORREF> > bkgCol;
    csLIST< csLIST<COLORREF> > brdCol;
    csLIST< HFONT> titleFont;
    csLIST< csLIST<HDC> > finalDC;

    int* id, *idp;
    SIZE* size;
    //csLIST<SIZE> iconSizeInput;
    HFONT defFont, defFont0;
    COLORREF defTextCol1, defTextCol2, defTextCol3, defTextCol4;
    COLORREF defBkgCol1, defBkgCol2, defBkgCol3, defBkgCol4;
    COLORREF defBrdCol1, defBrdCol2, defBrdCol3, defBrdCol4;
    int textPos, nItemWidth;
    int xoffset, yoffset, xmarg_text, ymarg_text, xTotal, yTotal, xmarg, ymarg;
    int *currentId, *lastId, *activedId;
    unsigned *nsz;
    csARGS args;
    csLIST<bool> enable;
    csLIST<bool> itemState;
    csLIST<bool> showITitle;
    unsigned nextPos;
    csLIST<short> type;
    bool defShowTitle;
    int* xtotalLen;
    int* ytotalLen;

    
    int moveMsgPos, lbtnDownMsgPos, lbtnUpMsgPos, leaveMsgPos, timerMsgPos, keyDownMsgPos, keyUpMsgPos;
};

#endif // CSBUTTONGRID_H
