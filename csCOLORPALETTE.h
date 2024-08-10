#ifndef CSCOLORPALETTE_H
#define CSCOLORPALETTE_H
#include "csCONTAINER.h"
#include "csBUTTON.h"

typedef struct
{
    int id, id1, id2,id3, id4, id5;
    int hmarg, vmarg, id12len, mrg3, mrg4;
    int maxInclen, step;
    bool orientation;
    float val, val_s, stepVal=2.0;

    bool size_message,click1_message, click2_message, bInit=1;
    bool mouseWheel1_extCmd=0, mouseWheel2_extCmd=0;

    float wheelCumulStep1, wheelCumulStep2;

    char*title="";
    bool moveTitle=1;


}csINCREMENTER;

struct HSL {
    double h; // Hue: Valeur entre 0.0 et 360.0
    double s; // Saturation: Valeur entre 0.0 et 1.0
    double l; // Lightness: Valeur entre 0.0 et 1.0
};
struct _RGB {
    double r; // 
    double g; // 
    double b; // 
};

class csCOLORPALETTE
{
    
    public:
        csCOLORPALETTE(int idp=0, RECT geometry={0}, csRGBA initialColor={0});
        csRGBA getSelectedColor();
        void setActiveColor(csRGBA color);
        int getId();
        virtual ~csCOLORPALETTE();
        int validate = 0;

    protected:

    private:
        csBMP map;
        csSIZE mSize;
        int id, idMap, *pidMap;
        csINCREMENTER *r, *g, *b, *a, *h, *s, *l, *c, *m, *j, *k;
        int *rSizeArgsNum,*gSizeArgsNum;
        BITMAPINFO bmi;
        int idSelection;
        csRGBA* colorSel;
};

csINCREMENTER* csIncrementer(int idp, char*title, float val, RECT geometry, csRGBA color, bool orientation);
_RGB HSLToRGB(HSL hsl);
HSL RGBtoHSL(_RGB rgb);
#endif // CSCOLORPALETTE_H
