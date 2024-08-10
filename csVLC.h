#ifndef CSVLC_H
#define CSVLC_H

#include "genStruct.h"
#include "csCONTAINER.h"
#include "csBUTTON.h"
#include "utlFx.h"

class csVLC
{
    public:
        csVLC(int* idp, int lmarg=2, int rmarg=2, int offset=5);
        void init(int* idp, int lmarg, int rmarg, int offset);
        void setDCSize(SIZE size);
        void newContainer(int*_id = 0, int minSize=15, int maxSize=CS_CXSCREEN);
        int getContainerId(int i);
        int*getContainerId_Ptr(int i);
        void autoUpdate(int i, bool update);
        virtual ~csVLC();

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
        int *totalLen;
        
};

#endif // CSVLC_H
