#ifndef CSBUTTON_GROUP_H
#define CSBUTTON_GROUP_H
#define CS_BG_HORIZONTAL 0
#define CS_BG_VERTICAL 1

#include "csCONTAINER.h"
#include "genStruct.h"

#define CS_CXSCREEN GetSystemMetrics(SM_CXSCREEN)
#define CS_CYSCREEN GetSystemMetrics(SM_CYSCREEN)

#include "csBUTTON.h"

class csTEXTBUTTON_GROUP
{
    public:
        csTEXTBUTTON_GROUP(int id_parent=0, RECT geometry={0}, bool orientation=CS_BG_HORIZONTAL);
        void newButton(const char*title, int length, bool lockable,SIZE fontSize={13,0});
        void init(int id_parent, RECT geometry, bool orientation);
        void setBackgroundImage(char*path, csSIZE size={(unsigned)CS_CXSCREEN, (unsigned)CS_CYSCREEN});
        void setBorderColor(csRGBA color);
        void setMouseTrackingColors(csRGBA c_track1, csRGBA c_track2, csRGBA c_click, csRGBA c_lock);
        void resizable(int thickness);
        void resizable_left();
        void resizable_top();
        void resizable_right();
        void resizable_bottom();
        void connectAll();
        RECT getGeometry();
        RECT* getGeometryPtr();
        csTEXTBUTTON getButton(int id);
        void setActive(int gid);
        void setPopupCnt(int idpupop);
        void setPopupDelay(unsigned delay);
        void setMarging(int marging);
        void movable(int moverThickness, bool _smoothMove=0);
        int getID();
        int* getIDPtr();
        csTEXTBUTTON getMover();
        void create();
        //void init(int orientation);
        void removeBackground();
        void setTotalLength(int len);
        int getIDC3();
        int* getIDC3Ptr();
        int getIDC2();
        int* getIDC2Ptr();
        int getIDS1();
        int getIDS2();
        bool getOrientation();
        void setC3Marging(int marging);
        void setC3Size(int length=-1, int marging=-1);

        
        //virtual ~csTEXTBUTTON_GROUP();

    protected:
        
        
    private:
        bool* orient;
        RECT geom1;
        RECT geom2;
        int* marg, *marg3, *totalLength;
        int* sideBtnLength, *moverLen;
        int *defaultBtnLength;
        int *idc1;
        int *idc2, *idc3, *idS1, *idS2;
        int *inc;
        bool *hold;

        int *popup;
        unsigned *popupdelay;
        
        bool *lbtndown1, *lbtndown2;
        csLIST<csTEXTBUTTON> btns;
        csTEXTBUTTON side1, side2, capt;

        int active, *pactive;
        bool* bshow;
        csARGS args, btnargs;
        csBKG_MOUSEHOVER_GRADIENT mhg;

        char*path1, *path2;
};
/*void frameButton_btnup(csARGS Args);
void frameButton_size(csARGS Args);
void viewSideBtnOn(csARGS Args);
void viewSideBtnOff(csARGS Args);
void holdOnPrevBtn(csARGS Args);
void holdOnNextBtn(csARGS Args);
void unlock(csARGS Args);
void SideBtnPos(csARGS Args);
void normalMove(csARGS Args);
void send_lbtnDown(csARGS Args);
void send_lbtnUp(csARGS Args);
void receive_mouseMove(csARGS Args);
void receive_lbtnDown(csARGS Args);

void makePrison(csARGS Args);
void smoothMove(csARGS Args);
void autoHideSideButtons(csARGS Args);*/
#endif // CSBUTTON_GROUP_H
