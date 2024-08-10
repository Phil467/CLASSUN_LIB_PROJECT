#ifndef CSHLC_H
#define CSHLC_H

#include "genStruct.h"
#include "csCONTAINER.h"
#include "csBUTTON.h"
#include "utlFx.h"

class csHLC
{
    public:
        csHLC(int* idp=0, int tmarg=2, int bmarg=2, int offset=5);
        void init(int* idp, int lmarg, int rmarg, int offset);
        void setDCSize(SIZE size);
        void newContainer(int*id, int minSize=15, int maxSize=CS_CYSCREEN);
        int getContainerId(int i);
        int*getContainerId_Ptr(int i);
        void autoUpdate(int i, bool update);

    protected:

    private:
        csLIST<int> ids;
        csLIST<int> minSizes;
        csLIST<int> maxSizes;
        csLIST<float> widthRatios;
        csLIST<csGLP4*> glps;
        csLIST<int> TimerMessagePos, GroupMessagePos;
        int *idp, lMarg, rMarg, offset;
        int tMarg, bMarg;
        SIZE dcSize;
        int ParSizeMessagePos;
        int* totalLen;
        
};


#endif // CSHLC_H
