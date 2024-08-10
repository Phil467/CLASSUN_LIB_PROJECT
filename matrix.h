#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "structures.h"
#include <iostream>
#include <string.h>

using namespace std;

typedef long int IDT;

/*typedef struct
{
    double x, y, z;
}csPOINT3F;*/

typedef struct DLL_EXPORT
{
    IDT iObject, szObject;
    IDT defObjInc, defElInc, defDatInc;
    IDT*iElement,*szElement;
    IDT**iData,**szData;
}csMAT3PARAMS;

template <class T> void DLL_EXPORT csRealloc(T*& tab, IDT size, const char*errType)
{
    if(!tab)
    {
        tab=(T*)malloc(size*sizeof(T));
        if(!tab) std::cout<<"Error in "<<errType<<" allocation!\n";
    }
    else
    {
        T*tmp=(T*)realloc(tab, size*sizeof(T));
        if(tmp)
        {
            tab=tmp;
        }else std::cout<<"Error in "<<errType<<" reallocation!\n";
    }
}

template <class T> struct DLL_EXPORT GROUP_EXTRACTED
{
    T****LType;
    IDT***iDat, ***szDat;
    IDT**iElm, **szElm;
    IDT*iObj,*szObj;
    IDT iType, szType;
    IDT idGp;
    bool showGroup;
    bool *showType;
    bool **showObj;
    char *gName, **tName, ***oName, ****eName, *****dName;
    bool showGName, *showTName, **showOName, ***showEName, ****showDName;
};

template <class T> struct DLL_EXPORT TYPE_EXTRACTED
{
    T***LObject;
    IDT**iDat, **szDat;
    IDT*iElm, *szElm;
    IDT iObj, szObj;
    IDT idTp, idGp;
    bool showType;
    bool *showObj;
    char *tName, **oName, ***eName, ****dName;
    bool showTName, *showOName, **showEName, ***showDName;
};
template <class T> struct DLL_EXPORT OBJECT_EXTRACTED
{
    T**LElement;
    IDT*iDat, *szDat;
    IDT iElm, szElm;
    IDT idObj, idTp, idGp;
    bool showObj;
    char *oName, **eName, ***dName;
    bool showOName, *showEName, **showDName;
};
template <class T> struct DLL_EXPORT ELEMENT_EXTRACTED
{
    T*LData;
    IDT iDat, szDat;
    IDT idElm, idObj, idTp, idGp;
    char *eName, **dName;
    bool showEName, *showDName;
};
template <class T> struct DLL_EXPORT DATA_EXTRACTED
{
    T Data;
    IDT idDat,idElm, idObj, idTp, idGp;
    char *dName;
    bool showDName;
};
template <class T>ELEMENT_EXTRACTED<T> DLL_EXPORT elementFromObject(IDT idElm,
                                          OBJECT_EXTRACTED<T> oe)
{
    ELEMENT_EXTRACTED<T> ee;
    ee.LData=oe.LElement[idElm];
    ee.iDat=oe.iDat[idElm];
    ee.iElm=oe.iElm;
}

void DLL_EXPORT catNumToChar(char*&chr, IDT num);

void DLL_EXPORT initChar(char*&chr, char*init);

template <class T> class DLL_EXPORT csDATALIST
{
    protected:
        void groupAllocBlock()
        {
            csRealloc<T****>(matrix, szGroup, "Object");
            csRealloc<IDT***>(szData, szGroup, "Datas size");
            csRealloc<IDT***>(iData, szGroup, "Datas length");
            csRealloc<IDT**>(szElement, szGroup, "Element size");
            csRealloc<IDT**>(iElement, szGroup, "Element length");
            csRealloc<IDT*>(szObject, szGroup, "Object size");
            csRealloc<IDT*>(iObject, szGroup, "Object length");
            csRealloc<IDT>(szType, szGroup, "Object size");
            csRealloc<IDT>(iType, szGroup, "Object length");
            csRealloc<bool**>(showObj, szGroup, "ShowObj");
            csRealloc<bool*>(showType, szGroup, "ShowType");
            csRealloc<bool>(showGroup, szGroup, "ShowGroup");
            csRealloc<char*****>(dName, szGroup, "dName");
            csRealloc<char****>(eName, szGroup, "eName");
            csRealloc<char***>(oName, szGroup, "oName");
            csRealloc<char**>(tName, szGroup, "tName");
            csRealloc<char*>(gName, szGroup, "gName");
            csRealloc<bool****>(showDName, szGroup, "ShowDName");
            csRealloc<bool***>(showEName, szGroup, "ShowEName");
            csRealloc<bool**>(showOName, szGroup, "ShowOName");
            csRealloc<bool*>(showTName, szGroup, "ShowTName");
            csRealloc<bool>(showGName, szGroup, "ShowGName");
        }
        void groupInitBlock()
        {
            for(IDT i=iGroup; i<szGroup; i++)
            {
                matrix[i]=0;
                szData[i]=0;
                iData[i]=0;
                szElement[i]=0;
                iElement[i]=0;
                szObject[i]=0;
                iObject[i]=0;
                iType[i]=0;
                szType[i]=0;
                showObj[i]=0;
                showType[i]=0;
                showGroup[i]=1;
                dName[i]=0;
                eName[i]=0;
                oName[i]=0;
                tName[i]=0;
                gName[i]=0;
                initChar(gName[i],gDefName);
                catNumToChar(gName[i], i);
                showGName[i]=1;
                showTName[i]=0;
                showOName[i]=0;
                showEName[i]=0;
                showDName[i]=0;
            }
        }

        void typeAllocBlock(IDT idGroup)
        {
            csRealloc<T***>(matrix[idGroup], szType[idGroup], "Object");
            csRealloc<IDT**>(szData[idGroup], szType[idGroup], "Datas size");
            csRealloc<IDT**>(iData[idGroup], szType[idGroup], "Datas length");
            csRealloc<IDT*>(szElement[idGroup], szType[idGroup], "Element size");
            csRealloc<IDT*>(iElement[idGroup], szType[idGroup], "Element length");
            csRealloc<IDT>(szObject[idGroup], szType[idGroup], "Object size");
            csRealloc<IDT>(iObject[idGroup], szType[idGroup], "Object length");
            csRealloc<bool*>(showObj[idGroup], szType[idGroup], "ShowObj");
            csRealloc<bool>(showType[idGroup], szType[idGroup], "ShowType");
            csRealloc<char****>(dName[idGroup], szType[idGroup], "dName");
            csRealloc<char***>(eName[idGroup], szType[idGroup], "eName");
            csRealloc<char**>(oName[idGroup], szType[idGroup], "oName");
            csRealloc<char*>(tName[idGroup], szType[idGroup], "tName");
            csRealloc<bool***>(showDName[idGroup], szType[idGroup], "ShowDName");
            csRealloc<bool**>(showEName[idGroup], szType[idGroup], "ShowEName");
            csRealloc<bool*>(showOName[idGroup], szType[idGroup], "ShowOName");
            csRealloc<bool>(showTName[idGroup], szType[idGroup], "ShowTName");
        }
        void typeInitBlock(IDT idGroup)
        {
            for(IDT i=iType[idGroup]; i<szType[idGroup]; i++)
            {
                matrix[idGroup][i]=0;
                szData[idGroup][i]=0;
                iData[idGroup][i]=0;
                szElement[idGroup][i]=0;
                iElement[idGroup][i]=0;
                szObject[idGroup][i]=0;
                iObject[idGroup][i]=0;
                showType[idGroup][i]=1;
                showObj[idGroup][i]=0;
                dName[idGroup][i]=0;
                eName[idGroup][i]=0;
                oName[idGroup][i]=0;
                tName[idGroup][i]=0;
                initChar(tName[idGroup][i],tDefName);
                catNumToChar(tName[idGroup][i], i);
                showTName[idGroup][i]=1;
                showOName[idGroup][i]=0;
                showEName[idGroup][i]=0;
                showDName[idGroup][i]=0;
            }
        }

        void objectAllocBlock(IDT idGroup, IDT idType)
        {

            csRealloc<T**>(matrix[idGroup][idType], szObject[idGroup][idType], "Object");
            csRealloc<IDT*>(szData[idGroup][idType], szObject[idGroup][idType], "Datas size");
            csRealloc<IDT*>(iData[idGroup][idType], szObject[idGroup][idType], "Datas length");
            csRealloc<IDT>(szElement[idGroup][idType], szObject[idGroup][idType], "Element size");
            csRealloc<IDT>(iElement[idGroup][idType], szObject[idGroup][idType], "Element length");
            csRealloc<bool>(showObj[idGroup][idType], szObject[idGroup][idType], "ShowObj");
            csRealloc<char***>(dName[idGroup][idType], szType[idGroup], "dName");
            csRealloc<char**>(eName[idGroup][idType], szType[idGroup], "eName");
            csRealloc<char*>(oName[idGroup][idType], szType[idGroup], "oName");
            csRealloc<bool**>(showDName[idGroup][idType], szType[idGroup], "ShowDName");
            csRealloc<bool*>(showEName[idGroup][idType], szType[idGroup], "ShowEName");
            csRealloc<bool>(showOName[idGroup][idType], szType[idGroup], "ShowOName");

        }
        void objectInitBlock(IDT idGroup, IDT idType)
        {
            for(IDT i=iObject[idGroup][idType]; i<szObject[idGroup][idType]; i++)
            {
                matrix[idGroup][idType][i]=0;
                szData[idGroup][idType][i]=0;
                iData[idGroup][idType][i]=0;
                szElement[idGroup][idType][i]=0;
                iElement[idGroup][idType][i]=0;
                showObj[idGroup][idType][i]=1;
                dName[idGroup][idType][i]=0;
                eName[idGroup][idType][i]=0;
                oName[idGroup][idType][i]=0;
                initChar(oName[idGroup][idType][i],oDefName);
                catNumToChar(oName[idGroup][idType][i], i);
                showOName[idGroup][idType][i]=1;
                showEName[idGroup][idType][i]=0;
                showDName[idGroup][idType][i]=0;

            }
        }

        void ElementAllocBlock(IDT idGroup, IDT idType, IDT idObj)
        {
            csRealloc<T*>(matrix[idGroup][idType][idObj], szElement[idGroup][idType][idObj], "Object");
            csRealloc<IDT>(szData[idGroup][idType][idObj], szElement[idGroup][idType][idObj], "Datas size");
            csRealloc<IDT>(iData[idGroup][idType][idObj], szElement[idGroup][idType][idObj], "Datas length");
            csRealloc<char**>(dName[idGroup][idType][idObj], szElement[idGroup][idType][idObj], "dName");
            csRealloc<char*>(eName[idGroup][idType][idObj], szElement[idGroup][idType][idObj], "eName");
            csRealloc<bool*>(showDName[idGroup][idType][idObj], szElement[idGroup][idType][idObj], "ShowDName");
            csRealloc<bool>(showEName[idGroup][idType][idObj], szElement[idGroup][idType][idObj], "ShowEName");

        }
        void ElementInitBlock(IDT idGroup, IDT idType, IDT idObj)
        {
            for(IDT i=iElement[idGroup][idType][idObj]; i<szElement[idGroup][idType][idObj]; i++)
            {
                matrix[idGroup][idType][idObj][i]=0;
                szData[idGroup][idType][idObj][i]=0;
                iData[idGroup][idType][idObj][i]=0;
                dName[idGroup][idType][idObj][i]=0;
                eName[idGroup][idType][idObj][i]=0;
                initChar(eName[idGroup][idType][idObj][i],eDefName);
                catNumToChar(eName[idGroup][idType][idObj][i], i);
                showEName[idGroup][idType][idObj][i]=1;
                showDName[idGroup][idType][idObj][i]=0;
            }
        }

        void dataAllocBlock(IDT idGroup, IDT idType, IDT idObj, IDT idEl)
        {
            csRealloc<T>(matrix[idGroup][idType][idObj][idEl], szData[idGroup][idType][idObj][idEl], "Object");
            csRealloc<char*>(dName[idGroup][idType][idObj][idEl], szData[idGroup][idType][idObj][idEl], "dName");
            csRealloc<bool>(showDName[idGroup][idType][idObj][idEl], szData[idGroup][idType][idObj][idEl], "ShowDName");
        }
        void dataInitBlock(IDT idGroup, IDT idType, IDT idObj, IDT idEl)
        {
            for(IDT i=iData[idGroup][idType][idObj][idEl]; i<szData[idGroup][idType][idObj][idEl]; i++)
            {
                dName[idGroup][idType][idObj][idEl][i]=0;
                initChar(dName[idGroup][idType][idObj][idEl][i],dDefName);
                catNumToChar(dName[idGroup][idType][idObj][idEl][i], i);
                showDName[idGroup][idType][idObj][idEl][i]=1;
            }
        }

    public:
        void (*insDRecipFunc)(FILE* f);
        T******tab;

        csDATALIST(IDT GroupInc, IDT TypeInc, IDT ObjInc, IDT ElmInc, IDT DatInc)
        {
            tab=0;
            tab=&matrix;
            defObjInc=ObjInc;
            defTypeInc=TypeInc;
            defElInc=ElmInc;
            defDatInc=DatInc;
            defGroupInc=GroupInc;
            iElement=szElement=0;
            matrix=0;
            iData=szData=0;
            iObject=szObject=0;
            iGroup=szGroup=0;
            showObj=0;
            showType=0;
            showGroup=0;
            iType=szType=0;
            gName=0;
            tName=0;
            oName=0;
            eName=0;
            dName=0;
            gDefName=tDefName=oDefName=eDefName=dDefName=0;
            showGName=0;
            showTName=0;
            showOName=0;
            showEName=0;
            showDName=0;
        }

        void setAllDefaultNames(char *GDefName, char *TDefName, char *ODefName,
                                char*EDefName, char*DDefName)
        {
            csRealloc<char>(gDefName, strlen(GDefName), "gDefName");
            csRealloc<char>(tDefName, strlen(TDefName), "tDefName");
            csRealloc<char>(oDefName, strlen(ODefName), "oDefName");
            csRealloc<char>(eDefName, strlen(EDefName), "eDefName");
            csRealloc<char>(dDefName, strlen(DDefName), "dDefName");
            sprintf(gDefName, "%s", GDefName);
            sprintf(tDefName, "%s", TDefName);
            sprintf(oDefName, "%s", ODefName);
            sprintf(eDefName, "%s", EDefName);
            sprintf(dDefName, "%s", DDefName);
        }
        void setGDefaultName(char *GDefName)
        {
            csRealloc<char>(gDefName, strlen(GDefName), "gDefName");
            sprintf(gDefName, "%s", GDefName);
        }
        void setTDefaultName(char *TDefName)
        {
            csRealloc<char>(tDefName, strlen(TDefName), "tDefName");
            sprintf(tDefName, "%s", TDefName);
        }
        void setODefaultName(char *ODefName)
        {
            csRealloc<char>(oDefName, strlen(ODefName), "oDefName");
            sprintf(oDefName, "%s", ODefName);
        }
        void setEDefaultName(char *EDefName)
        {
            csRealloc<char>(eDefName, strlen(EDefName), "eDefName");
            sprintf(eDefName, "%s", EDefName);
        }
        void setDDefaultName(char *DDefName)
        {
            csRealloc<char>(dDefName, strlen(DDefName), "dDefName");
            sprintf(dDefName, "%s", DDefName);
        }
        void setGName(IDT idGroup, char*name)
        {
            if(idGroup < iGroup)
            {   if(strlen(name) > strlen(gName[idGroup]))
                {
                    csRealloc<char>(gName[idGroup], strlen(name), "gName");
                }
                sprintf(gName[idGroup], "%s", name);
            }
        }
        void setTName(IDT idGroup, IDT idType, char*name)
        {
            if(idGroup < iGroup && idType < iType[idGroup])
            {
                if(strlen(name) > strlen(tName[idGroup][idType]))
                {
                    csRealloc<char>(tName[idGroup][idType], strlen(name), "tName");
                }
                sprintf(tName[idGroup][idType], "%s", name);

            }
        }
        void setOName(IDT idGroup, IDT idType, IDT idObj, char*name)
        {
            if(idGroup < iGroup && idType < iType[idGroup] && idObj < iObject[idType][idGroup])
            {
                if(strlen(name) > strlen(oName[idGroup][idType][idObj]))
                {
                    csRealloc<char>(oName[idGroup][idType][idObj], strlen(name), "oName");
                }
                sprintf(oName[idGroup][idType][idObj], "%s", name);

            }
        }
        void setEName(IDT idGroup, IDT idType, IDT idObj, IDT idEl,  char*name)
        {
            if(idGroup < iGroup && idType < iType[idGroup] && idObj < iObject[idType][idGroup]  &&
               idEl < iElement[idType][idGroup][idObj])
            {
                if(strlen(name) > strlen(eName[idGroup][idType][idObj][idEl]))
                {
                    csRealloc<char>(eName[idGroup][idType][idObj][idEl], strlen(name), "eName");
                }
                sprintf(eName[idGroup][idType][idObj][idEl], "%s", name);

            }
        }
        void setDName(IDT idGroup, IDT idType, IDT idObj, IDT idEl, IDT idData, char*name)
        {
            if(idGroup < iGroup && idType < iType[idGroup] && idObj < iObject[idType][idGroup]  &&
               idEl < iElement[idType][idGroup][idObj] && idData < iData[idType][idGroup][idObj][idEl])
            {
                if(strlen(name) > strlen(dName[idGroup][idType][idObj][idEl][idData]))
                {
                    csRealloc<char>(dName[idGroup][idType][idObj][idEl][idData], strlen(name), "dName");
                }
                sprintf(dName[idGroup][idType][idObj][idEl][idData], "%s", name);

            }
        }

        char* getGName(IDT idGroup)
        {
            char*ch=0;
            if(idGroup < iGroup)
            {
                ch=gName[idGroup];
            }
            return ch;
        }
        char* getTName(IDT idGroup, IDT idType)
        {
            char*ch=0;
            if(idGroup < iGroup && idType < iType[idGroup])
            {
                ch=tName[idGroup][idType];

            }
            return ch;
        }
        char* getOName(IDT idGroup, IDT idType, IDT idObj)
        {
            char*ch=0;
            if(idGroup < iGroup && idType < iType[idGroup] && idObj < iObject[idType][idGroup])
            {
                ch=oName[idGroup][idType][idObj];

            }
            return ch;
        }
        char* getEName(IDT idGroup, IDT idType, IDT idObj, IDT idEl)
        {
            char*ch=0;
            if(idGroup < iGroup && idType < iType[idGroup] && idObj < iObject[idType][idGroup]  &&
               idEl < iElement[idType][idGroup][idObj])
            {
                ch=eName[idGroup][idType][idObj][idEl];

            }
            return ch;
        }
        char* getDName(IDT idGroup, IDT idType, IDT idObj, IDT idEl, IDT idData)
        {
            char*ch=0;
            if(idGroup < iGroup && idType < iType[idGroup] && idObj < iObject[idType][idGroup]  &&
               idEl < iElement[idType][idGroup][idObj] && idData < iData[idType][idGroup][idObj][idEl])
            {
                ch=dName[idGroup][idType][idObj][idEl][idData];

            }
            return ch;
        }


        bool isOVisible(IDT idGroup, IDT idType, IDT idObj)
        {
            return showObj[idGroup][idType][idObj];
        }
        void showO(IDT idGroup, IDT idType, IDT idObj, bool show)
        {
            showObj[idGroup][idType][idObj]=show;
        }
        bool isTVisible(IDT idGroup, IDT idType)
        {
            return showType[idGroup][idType];
        }
        void showT(IDT idGroup, IDT idType, bool show)
        {
            showType[idGroup][idType]=show;
        }
        bool isGVisible(IDT idGroup)
        {
            return showGroup[idGroup];
        }
        void showG(IDT idGroup, bool show)
        {
            showGroup[idGroup]=show;
        }

        DATA_EXTRACTED<T> getD(IDT idGroup, IDT idType, IDT idObj, IDT idEl, IDT idData)
        {
            DATA_EXTRACTED<T> de;
            de.dName=0;
            de.Data=matrix[idGroup][idType][idObj][idEl][idData];
            de.idDat=idData;
            de.idElm=idEl;
            de.idGp=idGroup;
            de.idTp=idType;
            de.showDName=showDName[idGroup][idType][idObj][idEl][idData];
            csRealloc<char>(de.dName,strlen(dName[idGroup][idType][idObj][idEl][idData]),"dName");
            sprintf(de.dName,"%s",dName[idGroup][idType][idObj][idEl][idData]);
            return de;
        }
        ELEMENT_EXTRACTED<T> getE(IDT idGroup, IDT idType, IDT idObj, IDT idEl)
        {
            ELEMENT_EXTRACTED<T> ee;
            ee.eName=0;
            ee.LData=matrix[idGroup][idType][idObj][idEl];
            ee.idObj=idObj;
            ee.iDat=iData[idGroup][idType][idObj][idEl];
            ee.szDat=szData[idGroup][idType][idObj][idEl];
            ee.idTp=idType;
            ee.idElm=idEl;
            ee.idGp=idGroup;
            ee.dName=dName[idGroup][idType][idObj][idEl];
            ee.showDName=showDName[idGroup][idType][idObj][idEl];
            csRealloc<char>(ee.eName,strlen(eName[idGroup][idType][idObj][idEl]),"eName");
            sprintf(ee.eName,"%s",eName[idGroup][idType][idObj][idEl]);
            ee.showEName=showEName[idGroup][idType][idObj][idEl];
            return ee;
        }
        OBJECT_EXTRACTED<T> getO(IDT idGroup, IDT idType, IDT idObj)
        {
            OBJECT_EXTRACTED<T> oe;
            oe.oName=0;
            oe.LElement=matrix[idGroup][idType][idObj];
            oe.idObj=idObj;
            oe.iElm=iElement[idGroup][idType][idObj];
            oe.szElm=szElement[idGroup][idType][idObj];
            oe.iDat=iData[idGroup][idType][idObj];
            oe.szDat=szData[idGroup][idType][idObj];
            oe.idTp=idType;
            oe.idGp=idGroup;
            oe.showGroup=showGroup[idGroup];
            oe.dName=dName[idGroup][idType][idObj];
            oe.showDName=showDName[idGroup][idType][idObj];
            oe.eName=eName[idGroup][idType][idObj];
            oe.showEName=showEName[idGroup][idType][idObj];
            csRealloc<char>(oe.oName,strlen(oName[idGroup][idType][idObj]),"oName");
            sprintf(oe.oName,"%s",oName[idGroup][idType][idObj]);
            oe.showOName=showOName[idGroup][idType][idObj];
            return oe;
        }
        TYPE_EXTRACTED<T> getT(IDT idGroup, IDT idType)
        {
            TYPE_EXTRACTED<T> te;
            te.tName=0;
            te.LObject=matrix[idGroup][idType];
            te.iObj=iObject[idGroup][idType];
            te.szObj=szObject[idGroup][idType];
            te.iElm=iElement[idGroup][idType];
            te.szElm=szElement[idGroup][idType];
            te.iDat=iData[idGroup][idType];
            te.szDat=szData[idGroup][idType];
            te.idTp=idType;
            te.idGp=idGroup;
            te.showType=showType[idGroup];
            te.showObj=showObj[idGroup][idType];
            te.dName=dName[idGroup][idType];
            te.showDName=showDName[idGroup][idType];
            te.eName=eName[idGroup][idType];
            te.showEName=showEName[idGroup][idType];
            te.oName=oName[idGroup][idType];
            te.showOName=showOName[idGroup][idType];
            csRealloc<char>(te.tName,strlen(tName[idGroup][idType]),"tName");
            sprintf(te.oName,"%s",tName[idGroup][idType]);
            te.showTName=showTName[idGroup][idType];
            return te;
        }
        GROUP_EXTRACTED<T> getG(IDT idGroup)
        {
            GROUP_EXTRACTED<T> ge;
            ge.gName=0;
            ge.LType=matrix[idGroup];
            ge.iObj=iObject[idGroup];
            ge.szObj=szObject[idGroup];
            ge.iElm=iElement[idGroup];
            ge.szElm=szElement[idGroup];
            ge.iDat=iData[idGroup];
            ge.szDat=szData[idGroup];
            ge.iType=iType[idGroup];
            ge.szType=iType[idGroup];
            ge.idGp=idGroup;
            ge.showGroup=showGroup[idGroup];
            ge.showType=showType[idGroup];
            ge.showObj=showObj[idGroup];
            ge.dName=dName[idGroup];
            ge.showDName=showDName[idGroup];
            ge.eName=eName[idGroup];
            ge.showEName=showEName[idGroup];
            ge.oName=oName[idGroup];
            ge.showOName=showOName[idGroup];
            ge.tName=tName[idGroup];
            ge.showTName=showTName[idGroup];
            csRealloc<char>(ge.gName,strlen(gName[idGroup]),"gName");
            sprintf(ge.gName,"%s",gName[idGroup]);
            ge.showGName=showGName[idGroup];
            return ge;
        }

        IDT EL(IDT idGroup, IDT idType, IDT idObj)
        {
            return iElement[idGroup][idType][idObj];
        }
        IDT OL(IDT idGroup, IDT idType)
        {
            return iObject[idGroup][idType];
        }
        IDT TL(IDT idGroup)
        {
            return iType[idGroup];
        }
        IDT GL()
        {
            return iGroup;
        }
        IDT DL(IDT idGroup, IDT idType, IDT idObj, IDT idEl)
        {
            return iData[idGroup][idType][idObj][idEl];
        }

        void setD(IDT idGroup, IDT idType, IDT idObj, IDT idEl, IDT idData, T data)
        {
            matrix[idGroup][idType][idObj][idEl][idData]=data;
        }
        void setE(IDT idGroup, IDT idType, IDT idObj, IDT idEl, T*& elemt)
        {
            free(matrix[idGroup][idType][idObj][idEl]);
            matrix[idGroup][idType][idObj][idEl]=nullptr;
            matrix[idGroup][idType][idObj][idEl]=elemt;
        }
        void setO(IDT idGroup, IDT idType, IDT idObj, T**& obj)
        {
            for(IDT i=0; i<iElement[idGroup][idType][idObj]; i++)
            {   free(matrix[idGroup][idType][idObj][i]);
                matrix[idGroup][idType][i]=nullptr;
            }
            free(matrix[idGroup][idType][idObj]);
            matrix[idGroup][idType][idObj]=nullptr;
            matrix[idGroup][idType][idObj]=obj;
        }

        void insertD(IDT idGroup, IDT idType, IDT idObj, IDT idEl,  DATA_EXTRACTED<T>& de, IDT position)
        {
            if(idEl<iElement[idGroup][idType][idObj])
            {
                if(position <= iData[idGroup][idType][idObj][idEl])
                {
                    if(iData[idGroup][idType][idObj][idEl]+1 >= szData[idGroup][idType][idObj][idEl])
                    {   szData[idGroup][idType][idObj][idEl]+=defDatInc;
                        dataAllocBlock(idGroup, idType, idObj, idEl);
                        dataInitBlock(idGroup, idType, idObj, idEl);
                    }
                    for(IDT i=iData[idGroup][idType][idObj][idEl]; i>=position; i--)
                    {   matrix[idGroup][idType][idObj][idEl][i+1]=matrix[idGroup][idType][idObj][idEl][i];
                        csRealloc<char>(dName[idGroup][idType][idObj][idEl][i+1],
                                    strlen(dName[idGroup][idType][idObj][idEl][i]), "dName");
                        sprintf(dName[idGroup][idType][idObj][idEl][i+1], "%s",
                                dName[idGroup][idType][idObj][idEl][i]);
                        showDName[idGroup][idType][idObj][idEl][i+1]=showDName[idGroup][idType][idObj][idEl][i];
                    }

                    matrix[idGroup][idType][idObj][idEl][position]=de.Data;
                    csRealloc<char>(dName[idGroup][idType][idObj][idEl][position],
                                    strlen(de.dName), "dName");
                    sprintf(dName[idGroup][idType][idObj][idEl][position], "%s", de.dName);
                    showDName[idGroup][idType][idObj][idEl][position]=de.showDName;
                    iData[idGroup][idType][idObj][idEl]++;
                }
                else std::cout<<"Position highter than table length!\n";
            }
        }
        void insertE(IDT idGroup, IDT idType, IDT idObj, ELEMENT_EXTRACTED<T>& ee, IDT position)
        {
            if(idObj<iObject[idGroup][idType])
            {
                if(position <= iElement[idGroup][idType][idObj])
                {
                    if(iElement[idGroup][idType][idObj]+1 >= szElement[idGroup][idType][idObj])
                    {   szElement[idGroup][idType][idObj]+=defElInc;
                        ElementAllocBlock(idGroup, idType, idObj);
                        ElementInitBlock(idGroup, idType, idObj);
                    }
                    for(IDT i=iElement[idGroup][idType][idObj]; i>=position; i--)
                    {
                        //free(matrix[idGroup][idType][idObj][i+1])
                        matrix[idGroup][idType][idObj][i+1]=matrix[idGroup][idType][idObj][i];
                        szData[idGroup][idType][idObj][i+1]=szData[idGroup][idType][idObj][i];
                        iData[idGroup][idType][idObj][i+1]=iData[idGroup][idType][idObj][i];
                        showEName[idGroup][idType][idObj][i+1]=showEName[idGroup][idType][idObj][i];
                        showDName[idGroup][idType][idObj][i+1]=showDName[idGroup][idType][idObj][i];
                        csRealloc<char>(eName[idGroup][idType][idObj][i+1], strlen(eName[idGroup][idType][idObj][i]), "eName");
                        sprintf(eName[idGroup][idType][idObj][i+1], "%s", eName[idGroup][idType][idObj][i]);
                        dName[idGroup][idType][idObj][i+1]=dName[idGroup][idType][idObj][i];
                    }

                    matrix[idGroup][idType][idObj][position]=ee.LData;
                    szData[idGroup][idType][idObj][position]=ee.szDat;
                    iData[idGroup][idType][idObj][position]=ee.iDat;
                    showEName[idGroup][idType][idObj][position]=ee.showEName;
                    showDName[idGroup][idType][idObj][position]=ee.showDName;
                    csRealloc<char>(eName[idGroup][idType][idObj][position],strlen(ee.eName),"eName");
                    sprintf(eName[idGroup][idType][idObj][position],"%s",ee.eName);
                    dName[idGroup][idType][idObj][position]=ee.dName;
                    iElement[idGroup][idType][idObj]++;
                }
                else std::cout<<"Position highter than table length!\n";
            }
        }
        void insertO(IDT idGroup, IDT idType, OBJECT_EXTRACTED<T>& oe, IDT position)
        {
            if(idGroup<iGroup)
            {
                if(idType<iType[iGroup])
                {
                    if(position < iObject[idGroup][idType])
                    {
                        if(iObject[idGroup][idType]+1 >= szObject[idGroup][idType])
                        {   szObject[idGroup][idType]+=defObjInc;
                            objectAllocBlock(idGroup, idType);
                            objectInitBlock(idGroup,idType);
                        }
                        for(IDT i=iObject[idGroup][idType]; i>=position; i--)
                        {
                            //free(matrix[idGroup][idType][idObj][i+1])
                            matrix[idGroup][idType][i+1]=matrix[idGroup][idType][i];
                            szData[idGroup][idType][i+1]=szData[idGroup][idType][i];
                            iData[idGroup][idType][i+1]=iData[idGroup][idType][i];
                            szElement[idGroup][idType][i+1]=szElement[idGroup][idType][i];
                            iElement[idGroup][idType][i+1]=iElement[idGroup][idType][i];
                            dName[idGroup][idType][i+1]=dName[idGroup][idType][i];
                            eName[idGroup][idType][i+1]=eName[idGroup][idType][i];
                            csRealloc<char>(oName[idGroup][idType][i+1],strlen(oName[idGroup][idType][i]),"oName");
                            sprintf(oName[idGroup][idType][i+1],"%s",oName[idGroup][idType][i]);
                            showOName[idGroup][idType][i+1]=showOName[idGroup][idType][i];
                            showEName[idGroup][idType][i+1]=showEName[idGroup][idType][i];
                            showDName[idGroup][idType][i+1]=showDName[idGroup][idType][i];
                        }

                        matrix[idGroup][idType][position]=oe.LElement;
                        szElement[idGroup][idType][position]=oe.szElm;
                        iElement[idGroup][idType][position]=oe.iElm;
                        szData[idGroup][idType][position]=oe.szDat;
                        iData[idGroup][idType][position]=oe.iDat;
                        dName[idGroup][idType][position]=oe.dName;
                        eName[idGroup][idType][position]=oe.eName;
                        csRealloc<char>(oName[idGroup][idType][position],strlen(oe.oName),"oName");
                        sprintf(oName[idGroup][idType][position],"%s",oe.oName);
                        showOName[idGroup][idType][position]=oe.showOName;
                        showEName[idGroup][idType][position]=oe.showEName;
                        showDName[idGroup][idType][position]=oe.showDName;

                        iObject[idGroup][idType]++;
                    }
                    else std::cout<<"Position highter than table length!\n";
                }else std::cout<<"Type doesn't exist!\n";
            }else std::cout<<"Group doesn't exist!\n";
        }
        void insertT(IDT idGroup, TYPE_EXTRACTED<T>& te, IDT position)
        {
            if(idGroup<iGroup)
            {
                if(szType[idGroup] <= iType[idGroup])
                {
                    szType[idGroup] = iType[idGroup] + defTypeInc;
                    typeAllocBlock(idGroup);
                    typeInitBlock(idGroup);
                }
                for(IDT i=iType[idGroup]; i>=position; i--)
                {
                    //free(matrix[idGroup][idType][idObj][i+1])
                    matrix[idGroup][i+1]=matrix[idGroup][i];
                    szObject[idGroup][i+1]=szObject[idGroup][i];
                    iObject[idGroup][i+1]=iObject[idGroup][i];
                    szData[idGroup][i+1]=szData[idGroup][i];
                    iData[idGroup][i+1]=iData[idGroup][i];
                    szElement[idGroup][i+1]=szElement[idGroup][i];
                    iElement[idGroup][i+1]=iElement[idGroup][i];
                    showType[idGroup][i+1]=showType[idGroup][i];
                    showObj[idGroup][i+1]=showObj[idGroup][i];
                    dName[idGroup][i+1]=dName[idGroup][i];
                    eName[idGroup][i+1]=eName[idGroup][i];
                    oName[idGroup][i+1]=oName[idGroup][i];
                    csRealloc<char>(tName[idGroup][i+1],strlen(tName[idGroup][i]),"tName");
                    sprintf(tName[idGroup][i+1],"%s",tName[idGroup][i]);
                    showTName[idGroup][i+1]=showTName[idGroup][i];
                    showOName[idGroup][i+1]=showOName[idGroup][i];
                    showEName[idGroup][i+1]=showEName[idGroup][i];
                    showDName[idGroup][i+1]=showDName[idGroup][i];
                }

                matrix[idGroup][position]=te.LObject;
                szObject[idGroup][position]=te.szObj;
                iObject[idGroup][position]=te.iObj;
                szElement[idGroup][position]=te.szElm;
                iElement[idGroup][position]=te.iElm;
                szData[idGroup][position]=te.szDat;
                iData[idGroup][position]=te.iDat;
                showType[idGroup][position]=te.showType;
                showObj[idGroup][position]=te.showObj;
                dName[idGroup][position]=te.dName;
                eName[idGroup][position]=te.eName;
                oName[idGroup][position]=te.oName;
                csRealloc<char>(tName[idGroup][position],strlen(te.tName),"tName");
                sprintf(tName[idGroup][position],"%s",te.tName);
                showTName[idGroup][position]=te.showTName;
                showOName[idGroup][position]=te.showOName;
                showEName[idGroup][position]=te.showEName;
                showDName[idGroup][position]=te.showDName;

                iType[idGroup]++;
            }else std::cout<<"Group doesn't exist!\n";
        }
        void insertG(GROUP_EXTRACTED<T>& ge, IDT position)
        {
            if(szGroup <= iGroup)
            {
                szGroup = defGroupInc + iGroup;
                groupAllocBlock();
                groupInitBlock();
            }
            for(IDT i=iGroup; i>=position; i--)
            {
                //free(matrix[idGroup][idType][idObj][i+1])
                matrix[i+1]=matrix[i];
                szObject[i+1]=szObject[i];
                iObject[i+1]=iObject[i];
                szType[i+1]=szType[i];
                iType[i+1]=iType[i];
                szData[i+1]=szData[i];
                iData[i+1]=iData[i];
                szElement[i+1]=szElement[i];
                iElement[i+1]=iElement[i];
                showObj[i+1]=showObj[i];
                showType[i+1]=showType[i];
                showGroup[i+1]=showGroup[i];
                dName[i+1]=dName[i];
                eName[i+1]=eName[i];
                oName[i+1]=oName[i];
                tName[i+1]=tName[i];
                csRealloc<char>(gName[i+1], strlen(gName[i]), "gName");
                sprintf(gName[i+1], "%s",gName[i]);
                showGName[i+1]=showGName[i];
                showTName[i+1]=showTName[i];
                showOName[i+1]=showOName[i];
                showEName[i+1]=showEName[i];
                showDName[i+1]=showDName[i];
            }

            matrix[position]=ge.LType;
            szObject[position]=ge.szObj;
            iObject[position]=ge.iObj;
            szType[position]=ge.szType;
            iType[position]=ge.iType;
            szElement[position]=ge.szElm;
            iElement[position]=ge.iElm;
            szData[position]=ge.szDat;
            iData[position]=ge.iDat;
            showObj[position]=ge.showObj;
            showType[position]=ge.showType;
            showGroup[position]=ge.showGroup;
            dName[position]=ge.dName;
            eName[position]=ge.eName;
            oName[position]=ge.oName;
            tName[position]=ge.tName;
            gName[position]=0;
            csRealloc(gName[position], strlen(ge.gName), "gName");
            sprintf(gName[position], "%s",ge.gName);
            showGName[position]=ge.showGName;
            showTName[position]=ge.showTName;
            showOName[position]=ge.showOName;
            showEName[position]=ge.showEName;
            showDName[position]=ge.showDName;

            iGroup++;
        }

        void deleteD(IDT idGroup, IDT idType, IDT idObj, IDT idEl, IDT position)
        {
            if(position <= iData[idGroup][idType][idObj][idEl])
            {   for(int i=position; i<iData[idGroup][idType][idObj][idEl]-1; i++)
                    matrix[idGroup][idType][idObj][idEl][i]=matrix[idGroup][idType][idObj][idEl][i+1];

                szData[idGroup][idType][idObj][idEl]=--iData[idGroup][idType][idObj][idEl];
                dataAllocBlock(idGroup, idType, idObj, idEl);
            }
            else std::cout<<"Position highter than table szData[idType][idObj][idElement]!\n";
        }
        void deleteE(IDT idGroup, IDT idType, IDT idObj, IDT position)
        {
            if(idObj <= iObject[idGroup][idType])
            {
                if(position <= iElement[idGroup][idType][idObj])
                {
                    for(IDT i=position; i<iElement[idGroup][idType][idObj]; i++)
                    {
                        matrix[idGroup][idType][idObj][i]=matrix[idGroup][idType][idObj][i+1];
                        szData[idGroup][idType][idObj][i]=szData[idGroup][idType][idObj][i+1];
                        iData[idGroup][idType][idObj][i]=iData[idGroup][idType][idObj][i+1];
                        dName[idGroup][idType][idObj][i]=dName[idGroup][idType][idObj][i+1];
                        eName[idGroup][idType][idObj][i]=eName[idGroup][idType][idObj][i+1];
                        showEName[idGroup][idType][idObj][i]=showEName[idGroup][idType][idObj][i+1];
                        showDName[idGroup][idType][idObj][i]=showDName[idGroup][idType][idObj][i+1];
                    }

                    szElement[idGroup][idType][idObj]= --iElement[idGroup][idType][idObj];
                    ElementAllocBlock(idGroup, idType, idObj);
                }
                else std::cout<<"Position highter than table length!\n";
            }
        }
        void deleteO(IDT idGroup, IDT idType, IDT position)
        {
            if(idGroup<=iGroup)
            {
                if(idType<=iType[iGroup])
                {
                    if(position <= iObject[idGroup][idType])
                    {
                        for(IDT i=position; i<iObject[idGroup][idType]; i++)
                        {
                            matrix[idGroup][idType][i]=matrix[idGroup][idType][i+1];
                            szData[idGroup][idType][i]=szData[idGroup][idType][i+1];
                            iData[idGroup][idType][i]=iData[idGroup][idType][i+1];
                            szElement[idGroup][idType][i]=szElement[idGroup][idType][i+1];
                            iElement[idGroup][idType][i]=iElement[idGroup][idType][i+1];
                            dName[idGroup][idType][i]=dName[idGroup][idType][i+1];
                            eName[idGroup][idType][i]=eName[idGroup][idType][i+1];
                            oName[idGroup][idType][i]=oName[idGroup][idType][i+1];
                            showOName[idGroup][idType][i]=showOName[idGroup][idType][i+1];
                            showEName[idGroup][idType][i]=showEName[idGroup][idType][i+1];
                            showDName[idGroup][idType][i]=showDName[idGroup][idType][i+1];
                        }

                        szObject[idGroup][idType]=--iObject[idGroup][idType];
                        objectAllocBlock(idGroup, idType);

                    }
                    else std::cout<<"Position highter than table length!\n";
                }else std::cout<<"Type doesn't exist!\n";
            }else std::cout<<"Group doesn't exist!\n";
        }
        void deleteT(IDT idGroup, IDT position)
        {
            if(idGroup<=iGroup)
            {
                if(szType[idGroup] <= iType[idGroup])
                {
                    for(IDT i=position; i<iType[idGroup]; i++)
                    {
                        matrix[idGroup][i]=matrix[idGroup][i+1];
                        szObject[idGroup][i]=szObject[idGroup][i+1];
                        iObject[idGroup][i]=iObject[idGroup][i+1];
                        szData[idGroup][i]=szData[idGroup][i+1];
                        iData[idGroup][i]=iData[idGroup][i+1];
                        szElement[idGroup][i]=szElement[idGroup][i+1];
                        iElement[idGroup][i]=iElement[idGroup][i+1];
                        showType[idGroup][i]=showType[idGroup][i+1];
                        showObj[idGroup][i]=showObj[idGroup][i+1];
                        dName[idGroup][i]=dName[idGroup][i+1];
                        eName[idGroup][i]=eName[idGroup][i+1];
                        oName[idGroup][i]=oName[idGroup][i+1];
                        tName[idGroup][i]=tName[idGroup][i+1];
                        showTName[idGroup][i]=showTName[idGroup][i+1];
                        showOName[idGroup][i]=showOName[idGroup][i+1];
                        showEName[idGroup][i]=showEName[idGroup][i+1];
                        showDName[idGroup][i]=showDName[idGroup][i+1];
                    }
                    szType[idGroup] = --iType[idGroup];
                    typeAllocBlock(idGroup);

                }
            }else std::cout<<"Group doesn't exist!\n";
        }
        void deleteG(IDT position)
        {
            if(szGroup <= iGroup)
            {
                for(IDT i=position; i<iGroup; i++)
                {
                    //free(matrix[idGroup][idType][idObj][i+1])
                    matrix[i]=matrix[i+1];
                    szObject[i]=szObject[i+1];
                    iObject[i]=iObject[i+1];
                    szType[i]=szType[i+1];
                    iType[i]=iType[i+1];
                    szData[i]=szData[i+1];
                    iData[i]=iData[i+1];
                    szElement[i]=szElement[i+1];
                    iElement[i]=iElement[i+1];
                    showObj[i]=showObj[i+1];
                    showType[i]=showType[i+1];
                    showGroup[i]=showGroup[i+1];
                    dName[i]=dName[i+1];
                    eName[i]=eName[i+1];
                    oName[i]=oName[i+1];
                    tName[i]=tName[i+1];
                    gName[i]=gName[i+1];
                    showGName[i]=showGName[i+1];
                    showTName[i]=showTName[i+1];
                    showOName[i]=showOName[i+1];
                    showEName[i]=showEName[i+1];
                    showDName[i]=showDName[i+1];
                }
                szGroup = --iGroup;
                groupAllocBlock();

            }
        }


        void newData(IDT idGroup, IDT idType, IDT idObj, IDT idEl, T data)
        {
            if(idObj <= iObject[idGroup][idType])
            {
                if(idEl <= iElement[idGroup][idType][idObj])
                {
                    if(szData[idGroup][idType][idObj][idEl] <= iData[idGroup][idType][idObj][idEl])
                    {
                        szData[idGroup][idType][idObj][idEl] = defDatInc + iData[idGroup][idType][idObj][idEl];
                        dataAllocBlock(idGroup, idType, idObj, idEl);
                        dataInitBlock(idGroup, idType, idObj, idEl);
                    }
                    matrix[idGroup][idType][idObj][idEl][iData[idGroup][idType][idObj][idEl]]=data;
                    iData[idGroup][idType][idObj][idEl]++;
                }else std::cout<<"Element doesn't exist!\n";
            }
            else std::cout<<"Object doesn't exist!\n";
        }
        void newDefElement(IDT idGroup, IDT idType, IDT idObj, T*Element)
        {
            if(idObj <= iObject[idGroup][idType])
            {   if(szElement[idGroup][idType][idObj] <= iElement[idGroup][idType][idObj])
                {
                    szElement[idGroup][idType][idObj] = defElInc + iElement[idGroup][idType][idObj];
                    csRealloc<T*>(matrix[idGroup][idType][idObj], szElement[idGroup][idType][idObj], "Object");
                    csRealloc<IDT>(szData[idGroup][idType][idObj], szElement[idGroup][idType][idObj], "Datas size");
                    csRealloc<IDT>(iData[idGroup][idType][idObj], szElement[idGroup][idType][idObj], "Datas length");

                    for(IDT i=iElement[idGroup][idType][idObj]; i<szElement[idGroup][idType][idObj]; i++)
                    {
                        matrix[idGroup][idType][idObj][i]=0;
                        szData[idGroup][idType][idObj][i]=0;
                        iData[idGroup][idType][idObj][i]=0;
                    }
                }
                matrix[idGroup][idType][idObj][iElement[idGroup][idType][idObj]]=Element;
                iElement[idGroup][idType][idObj]++;
            }
            else std::cout<<"Object doesn't exist!\n";
        }
        void newElement(IDT idGroup, IDT idType, IDT idObj)
        {
            if(idObj <= iObject[idGroup][idType])
            {
                if(szElement[idGroup][idType][idObj] <= iElement[idGroup][idType][idObj])
                {
                    szElement[idGroup][idType][idObj] = defElInc + iElement[idGroup][idType][idObj];
                    ElementAllocBlock(idGroup, idType, idObj);
                    ElementInitBlock(idGroup, idType, idObj);

                }
                iElement[idGroup][idType][idObj]++;
            }
            else std::cout<<"Object doesn't exist!\n";
        }
        void newDefObject(IDT idGroup, IDT idType, T**object)
        {
            if(idGroup<=iGroup)
            {
                if(idType<=iType[idGroup])
                {
                    if(szObject[idGroup][idType] <= iObject[idGroup][idType])
                    {
                        szObject[idGroup][idType] = defObjInc + iObject[idGroup][idType];
                        objectAllocBlock(idGroup, idType);
                        objectInitBlock(idGroup, idType);
                    }
                }else std::cout<<"Type doesn't exist!\n";
            }else std::cout<<"Group doesn't exist!\n";
        }
        void newObject(IDT idGroup, IDT idType)
        {
            if(idGroup<=iGroup)
            {
                if(idType<=iType[idGroup])
                {
                    if(szObject[idGroup][idType] <= iObject[idGroup][idType])
                    {
                        szObject[idGroup][idType] = defObjInc + iObject[idGroup][idType];
                        objectAllocBlock(idGroup, idType);
                        objectInitBlock(idGroup, idType);
                    }
                    iObject[idGroup][idType]++;
                }else std::cout<<"Type doesn't exist!\n";
            }else std::cout<<"Group doesn't exist!\n";
        }
        void newType(IDT idGroup)
        {
            if(idGroup<iGroup)
            {
                if(szType[idGroup] <= iType[idGroup])
                {
                    szType[idGroup] = iType[idGroup] + defTypeInc;
                    typeAllocBlock(idGroup);
                    typeInitBlock(idGroup);
                }
                iType[idGroup]++;
            }else std::cout<<"Group doesn't exist!\n";
        }
        void newGroup()
        {
            if(szGroup <= iGroup)
            {
                szGroup = defGroupInc + iGroup;
                groupAllocBlock();
                groupInitBlock();
            }
            iGroup++;
        }

    private:
        IDT iGroup, szGroup;
        IDT *iType, *szType;
        IDT **iObject, **szObject;
        IDT defGroupInc, defTypeInc, defObjInc, defElInc, defDatInc;
        IDT***iElement,***szElement;
        IDT****iData,****szData;
        bool***showObj;
        bool**showType;
        bool*showGroup;
        char **gName, ***tName, ****oName, *****eName, ******dName;
        char *gDefName, *tDefName, *oDefName, *eDefName, *dDefName;
        bool *showGName, **showTName, ***showOName, ****showEName, *****showDName;
        T*****matrix;
};

void DLL_EXPORT printP3f(csPOINT3F p3f);
void DLL_EXPORT printP3f1(csPOINT3F* p3f, IDT len);
void DLL_EXPORT printP3fAll(csDATALIST<csPOINT3F> dat);



#endif // MATRIX_H_INCLUDED
