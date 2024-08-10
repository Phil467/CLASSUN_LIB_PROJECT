#ifndef CSSYSCMD_H
#define CSSYSCMD_H
#include "genStruct.h"
#include "csCONTAINER.h"
#include "csBUTTON.h"


class csSYSCMD
{
    public:
        csSYSCMD();
        virtual ~csSYSCMD();

    protected:

    private:
};

int* csAddAppCloser(int idp, RECT geometry={0}, RECT marg={0});
int* csAddDestroyer(int idp, int* idTarget, RECT geometry={0}, RECT marg={0});
int* csAddHider(int idp, int* idTarget, RECT geometry={0}, RECT marg={0});

void showHideCnt(csARGS Args);
void cntshow(csARGS Args);
void holdingLbtn(csARGS Args);
void closeCnt(csARGS Args);
void minimizeCntInit(csARGS Args);
void minimizeCntEnd(csARGS Args);
void minimizeCnt(int idmin, int& client);
void restoreCntInit(csARGS Args);
void restoreCnt(int client);
void closeApp(csARGS Args);
void destroyCnt(csARGS Args);
void hideCnt(csARGS Args);

#endif // CSSYSCMD_H
