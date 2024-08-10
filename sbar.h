#ifndef SBAR_H
#define SBAR_H
#include "csCONTAINER.h"

class csSBAR
{
    public:
        csSBAR(csCNTR_PARAMS& bccp, int idp, csRGBA bkgcol, RECT geometry, bool orient);
        virtual ~csSBAR();

    protected:

    private:
        int idcnt, idb, idc, idprev, idnext;

};

#endif // SBAR_H
