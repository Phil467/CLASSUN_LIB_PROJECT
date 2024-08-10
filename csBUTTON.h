#ifndef CSBUTTON_H
#define CSBUTTON_H

#define CS_TEXT_BTN 0
#define CS_IMAGE_BTN 1

#include "csCONTAINER.h"
#include "genStruct.h"

class csTEXTBUTTON
{
    public:
        csTEXTBUTTON(int id_parent=0, const char*text=0, RECT geometry={0}, bool lockable=0);
        csCNTR_PARAMS* getParams();
        void create(int id_parent, const char*text, RECT geometry, bool lockable);
        int getId();
        int* getIdPtr();
        int setColors(csRGBA bkg, csRGBA text, csRGBA mouseOver1,csRGBA mouseOver2,
                            csRGBA click, csRGBA borders, int brdWidth, bool remBkg);
        virtual ~csTEXTBUTTON();

    protected:

    private:
        int id;
};

int textButton(csCNTR_PARAMS& cscp, int idp, char*text, csRGB tcol, RECT geometry, csLOCKED_MODE lm={0});
int textButton2(csCNTR_PARAMS& cscp, int idp, char*text, csRGB tcol, RECT geometry, csLOCKED_MODE lm={0},SIZE dcsize={0});
int imgButton(csCNTR_PARAMS& cscp, int idp, char*path1, char*path2, char*path3,
              RECT geometry, RECT margings, csRGBA color={15,15,15}, int SameDesignCnt=0, bool remColor=0);
int imgButton2(csCNTR_PARAMS& cscp, int idp, char*path1, char*path2, char*path3,
              RECT geometry, RECT margings, csRGBA color={15,15,15}, int SameDesignCnt=0, bool remColor=0);
int staticCnt(csCNTR_PARAMS& cscp, int idp, char*title, RECT geometry);
int staticCnt2(csCNTR_PARAMS& cscp, int idp, char*title, csRGBA color, RECT geometry, bool show=1, float mhgradientLevel=0.0, SIZE dcSize={0});
void csSetRulersTrackers(int* id, csRGBA color, int witdh=1, int length=20, bool x1=2, bool x2=1, bool y1=1, bool y2=1);
#endif // CSBUTTON_H
