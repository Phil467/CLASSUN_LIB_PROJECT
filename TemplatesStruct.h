#ifndef TEMPLATESSTRUCT_H_INCLUDED
#define TEMPLATESSTRUCT_H_INCLUDED
#include <iostream>

void csf_outputAllocError(int idObj, int lineNum);

template<class TYPE> void csf_realloc(TYPE** table, int actualSize, int newSize)
{
    if(!table)
    {
        *table=(TYPE*)malloc(newSize*sizeof(TYPE));
        if(!(*table)) std::cout<<"Error in allocation!\n";
        else
        {
            for(int i=actualSize; i<newSize; i++)
            {
                (*table)[i]=0;
            }
        }
    }
    else
    {
        TYPE*tmp=(TYPE*)realloc(*table, newSize*sizeof(TYPE));
        if(tmp)
        {
            *table=tmp;
            for(int i=actualSize; i<newSize; i++)
            {
                (*table)[i]=0;
            }
        }else std::cout<<"Error in reallocation!\n";
    }
}

template<class TYPE> void csf_VRealloc2(TYPE** table, int actualSize, int newSize, TYPE init)
{
    if(!(*table))
    {
        *table=(TYPE*)malloc(newSize*sizeof(TYPE));
        if(!(*table)) std::cout<<"Error in allocation!\n";
        else
        {
            for(int i=actualSize; i<newSize; i++)
            {
                (*table)[i]=init;
            }
        }
    }
    else
    {
        TYPE*tmp=(TYPE*)realloc(*table, newSize*sizeof(TYPE));
        if(tmp)
        {
            *table=tmp;
            for(int i=actualSize; i<newSize; i++)
            {
                (*table)[i]=init;
            }
        }else std::cout<<"Error in reallocation!\n";
    }
}

template<class TYPE> void csf_VRealloc(TYPE** table, int newSize)
{
    if(!(*table))
    {
        *table=(TYPE*)malloc(newSize*sizeof(TYPE));
        if(!(*table)) std::cout<<"Error in allocation!\n";
    }
    else
    {
        TYPE*tmp=(TYPE*)realloc(*table, newSize*sizeof(TYPE));
        if(tmp)
        {
            (*table)=tmp;
        }else std::cout<<"Error in reallocation!\n";
    }
}


template<class TYPE> TYPE* csf_alloc(size_t size)
{
    return (TYPE*)calloc(size, sizeof(TYPE));
}
template<class TYPE> TYPE* csf_alloc2(size_t size, TYPE init)
{
    TYPE* d = (TYPE*)malloc(size*sizeof(TYPE));
    *d = init;
    return d;
}

template<class TYPE> class /*DLL_EXPORT*/ csDATABASE
{
    private:
        int iType;
        TYPE****DataTab;
        int ***iData,**iElement, *iObject;
        int ***szData,**szElement, *szObject;
        bool **setThis, **showThis;
    public:
        csDATABASE()
        {
                DataTab=0;
                iData=0;
                iElement=0;
                iObject=0;
                szData=0;
                szElement=0;
                szObject=0;
                setThis=0;
                showThis=0;
        };
        void init(int TypeNum)
        {
            iType=TypeNum;
            csf_realloc<TYPE***>(&DataTab, 0, iType);
            csf_realloc<int**>(&iData, 0, iType);
            csf_realloc<int**>(&szData, 0, iType);
            csf_realloc<int*>(&iElement, 0, iType);
            csf_realloc<int*>(&szElement, 0, iType);
            csf_realloc<bool*>(&showThis, 0, iType);
            csf_realloc<bool*>(&setThis, 0, iType);
            csf_VRealloc2<int>(&iObject, 0, iType, 0);
            csf_VRealloc2<int>(&szObject, 0, iType, 0);
        }
    void newObject(int idType)
    {
        if(idType<=iType)
        {
            if(szObject[idType] <= iObject[idType])
            {
                szObject[idType] = 1 + iObject[idType];
                csf_realloc<TYPE**>(&DataTab[idType], iObject[idType], szObject[idType]);
                csf_realloc<int*>(&iData[idType], iObject[idType], szObject[idType]);
                csf_realloc<int*>(&szData[idType], iObject[idType], szObject[idType]);
                csf_VRealloc2<int>(&iElement[idType], iObject[idType], szObject[idType], 0);
                csf_VRealloc2<int>(&szElement[idType], iObject[idType], szObject[idType], 0);
                csf_VRealloc2<bool>(&showThis[idType], iObject[idType], szObject[idType], 1);

            }
            iObject[idType]++;
        }else std::cout<<"Type doesn't exist!\n";
    }

    void newElement(int idType, int idObj)
    {

        if(iElement[idType][idObj] >= szElement[idType][idObj])
        {   szElement[idType][idObj]+=2;
            csf_realloc<TYPE*>(&DataTab[idType][idObj], iElement[idType][idObj], szElement[idType][idObj]);
            csf_VRealloc2<int>(&iData[idType][idObj], iElement[idType][idObj], szElement[idType][idObj], 0);
            csf_VRealloc2<int>(&szData[idType][idObj], iElement[idType][idObj], szElement[idType][idObj],0);
        }
        iElement[idType][idObj]++;
    }

    void newElement2(int idType, int idObj, int memSize)
    {
        if(iElement[idType][idObj] >= szElement[idType][idObj])
        {   szElement[idType][idObj]+=memSize;
            csf_realloc<TYPE*>(&DataTab[idType][idObj], iElement[idType][idObj], szElement[idType][idObj]);
            csf_VRealloc2<int>(&iData[idType][idObj], iElement[idType][idObj], szElement[idType][idObj], 0);
            csf_VRealloc2<int>(&szData[idType][idObj], iElement[idType][idObj], szElement[idType][idObj],0);
        }
        iElement[idType][idObj]++;
    }

    void newDefinedElement(int idType, int idObj, TYPE* pData, int size)
    {
        if(iElement[idType][idObj] >= szElement[idType][idObj])
        {   szElement[idType][idObj]+=2;
            csf_realloc<TYPE*>(&DataTab[idType][idObj], iElement[idType][idObj], szElement[idType][idObj]);
            csf_VRealloc2<int>(&iData[idType][idObj], iElement[idType][idObj], szElement[idType][idObj], 0);
            csf_VRealloc2<int>(&szData[idType][idObj], iElement[idType][idObj], szElement[idType][idObj],0);
        }
        DataTab[idType][idObj][iElement[idType][idObj]]=pData;
        iData[idType][idObj][iElement[idType][idObj]]=size;
        szData[idType][idObj][iElement[idType][idObj]]=size;
        iElement[idType][idObj]++;
    }

    void InsertElementAt(int idType, int idObj, TYPE* pData, int position, int size)
    {
        if(position<iElement[idType][idObj])
        {
            newElement(idType, idObj);
            for(int i=iElement[idType][idObj]-1; i >= position; i--)
            {   DataTab[idType][idObj][i+1]=DataTab[idType][idObj][i];
                iData[idType][idObj][i+1]=iData[idType][idObj][i];
                szData[idType][idObj][i+1]=szData[idType][idObj][i];
            }
            DataTab[idType][idObj][position]=pData;
            iData[idType][idObj][position]=size;
            szData[idType][idObj][position]=size;
        }
        else std::cout<<"Position higher than table szData[idType][idObj]!\n";
    }

    void DeleteElementAt(int idType, int idObj, int position)
    {
        if(position<iElement[idType][idObj])
        {   for(int i=position; i<iElement[idType][idObj]-1; i++)
            {   DataTab[idType][idObj][i]=DataTab[idType][idObj][i+1];
                iData[idType][idObj][i]=iData[idType][idObj][i+1];
                szData[idType][idObj][i]=szData[idType][idObj][i+1];
            }

            szElement[idType][idObj]=--iElement[idType][idObj];
            csf_realloc<TYPE*>(&DataTab[idType][idObj], iElement[idType][idObj], szElement[idType][idObj]);
            csf_VRealloc2<int>(&iData[idType][idObj], iElement[idType][idObj], szElement[idType][idObj], 0);
            csf_VRealloc2<int>(&szData[idType][idObj], iElement[idType][idObj], szElement[idType][idObj], 0);
        }
        else std::cout<<"Position higher than table szData[idType][idObj]!\n";
    }

    void InsertDataAtEnd(int idType, int idObj, int idElement, TYPE Data)
    {
        if(iData[idType][idObj][idElement] >= szData[idType][idObj][idElement])
        {   szData[idType][idObj][idElement]+=5;

            csf_VRealloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement]);
        }
        DataTab[idType][idObj][idElement][iData[idType][idObj][idElement]]=Data;
        //std::cout<<idObj<<" "<<idElement<<" "<<iData[idType][idObj][idElement]<<"\n";
        iData[idType][idObj][idElement]++;
    }

    void InsertDataAtEnd2(int idType, int idObj, int idElement, TYPE Data)
    {
        if(iData[idType][idObj][idElement]>szData[idType][idObj][idElement]-2)
        {   szData[idType][idObj][idElement]+=2;

            csf_VRealloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement]);
        }
        DataTab[idType][idObj][idElement][iData[idType][idObj][idElement]]=Data;
        //std::cout<<idObj<<" "<<idElement<<" "<<iData[idType][idObj][idElement]<<"\n";
        iData[idType][idObj][idElement]++;
    }

    void InsertDataAtEnd3(int idType, int idObj, int idElement, TYPE Data, int memSize)
    {
        if(iData[idType][idObj][idElement] >= szData[idType][idObj][idElement])
        {   szData[idType][idObj][idElement]+=memSize;

            csf_VRealloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement]);
        }
        DataTab[idType][idObj][idElement][iData[idType][idObj][idElement]]=Data;
        //std::cout<<idObj<<" "<<idElement<<" "<<iData[idType][idObj][idElement]<<"\n";
        iData[idType][idObj][idElement]++;
    }

    void InsertDataOnTop(int idType, int idObj, int idElement, TYPE Data)
    {
        if(iData[idType][idObj][idElement] >= szData[idType][idObj][idElement])
        {   szData[idType][idObj][idElement]+=5;
            csf_VRealloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement]);
        }

        for(int i=iData[idType][idObj][idElement]; i>=0; i--)
        {   DataTab[idType][idObj][idElement][i+1]=DataTab[idType][idObj][idElement][i];
        }
        DataTab[idType][idObj][idElement][0]=Data;
        iData[idType][idObj][idElement]++;
    }

    void InsertDataAt(int idType, int idObj, int idElement, TYPE Data, int position)
    {
        if(position<=iData[idType][idObj][idElement])
        {   if(iData[idType][idObj][idElement]>szData[idType][idObj][idElement]-2)
            {   szData[idType][idObj][idElement]+=20;
                csf_VRealloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement]);
            }
            for(int i=iData[idType][idObj][idElement]; i>=position; i--)
                DataTab[idType][idObj][idElement][i+1]=DataTab[idType][idObj][idElement][i];

            DataTab[idType][idObj][idElement][position]=Data;
            iData[idType][idObj][idElement]++;
        }
        else std::cout<<"Position higher than table sizegth!\n";
    }

    void InsertDatasStartingTo(int idType, int idObj, int idElement, TYPE* Data, int position, int size)
    {
        if(position<=iData[idType][idObj][idElement])
        {   if(iData[idType][idObj][idElement]>=szData[idType][idObj][idElement]-size)
            {   szData[idType][idObj][idElement]+=size+1;
                csf_VRealloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement]);
            }
            for(int i=iData[idType][idObj][idElement]; i>=position; i--)
                DataTab[idType][idObj][idElement][i+size]=DataTab[idType][idObj][idElement][i];

            int sz=position+size;
            for(int i=position; i<sz; i++)
                DataTab[idType][idObj][idElement][i]=Data[i-position];
            iData[idType][idObj][idElement]+=size;
        }
        else std::cout<<"Position larger than table size!\n";
    }

    void InsertInverseDatasStartingTo(int idType, int idObj, int idElement, TYPE* Data, int position, int size)
    {
        if(position<=iData[idType][idObj][idElement])
        {   if(iData[idType][idObj][idElement]>=szData[idType][idObj][idElement]-size)
            {   szData[idType][idObj][idElement]+=size+1;
                csf_VRealloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement]);
            }
            for(int i=iData[idType][idObj][idElement]; i>=position; i--)
                DataTab[idType][idObj][idElement][i+size]=DataTab[idType][idObj][idElement][i];

            int sz=position+size;
            for(int i=position; i<sz; i++)
                DataTab[idType][idObj][idElement][i]=Data[size-1-i+position];
            iData[idType][idObj][idElement]+=size;
        }
        else std::cout<<"Position larger than table size!\n";
    }

    void InsertDatasOnTop(int idType, int idObj, int idElement, TYPE* Data, int size)
    {
        if(iData[idType][idObj][idElement] >= szData[idType][idObj][idElement]-size)
            {   szData[idType][idObj][idElement]+=size+1;
                csf_VRealloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement]);
            }
            for(int i=iData[idType][idObj][idElement]; i>=0; i--)
                DataTab[idType][idObj][idElement][i+size]=DataTab[idType][idObj][idElement][i];

            int sz=size;
            for(int i=0; i<sz; i++)
                DataTab[idType][idObj][idElement][i]=Data[i];
            iData[idType][idObj][idElement]+=size;

        //else std::cout<<"Position larger than table size!\n";
    }

    void SetDataPoint(int idType, int idObj, int idElement,int idData, TYPE Data)
    {
        if(idData>szData[idType][idObj][idElement]-2)
        {   szData[idType][idObj][idElement]=idData+50;
            iData[idType][idObj][idElement]=idData+1;
            csf_realloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement], 0);
        }
        if(idData>=iData[idType][idObj][idElement]) iData[idType][idObj][idElement]=idData+1;
            DataTab[idType][idObj][idElement][idData]=Data;
    }

    void DeleteLastData(int idType, int idObj, int idElement)
    {
        szData[idType][idObj][idElement]=iData[idType][idObj][idElement]--;
        csf_realloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement], 0);

    }

    void DeleteFirstData(int idType, int idObj, int idElement)
    {
        for(int i=0; i<iData[idType][idObj][idElement]-1; i++)
        {   DataTab[idType][idObj][idElement][i]=DataTab[idType][idObj][idElement][i+1];
        }
        szData[idType][idObj][idElement]=--iData[idType][idObj][idElement];
        csf_realloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement], 0);
    }

    void DeleteDataAt(int idType, int idObj, int idElement, int position)
    {
        if(position<iData[idType][idObj][idElement])
        {   for(int i=position; i<iData[idType][idObj][idElement]-1; i++)
                DataTab[idType][idObj][idElement][i]=DataTab[idType][idObj][idElement][i+1];

            szData[idType][idObj][idElement]=--iData[idType][idObj][idElement];
            csf_realloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement], 0);
        }
        else std::cout<<"Position higher than table szData[idType][idObj][idElement]!\n";
    }

    void DeleteTopDatas(int idType, int idObj, int idElement, int size)
    {
        if(size<iData[idType][idObj][idElement])
        {
            for(int i=size; i<iData[idType][idObj][idElement]; i++)
                DataTab[idType][idObj][idElement][i-size]=DataTab[idType][idObj][idElement][i];
            szData[idType][idObj][idElement]=(iData[idType][idObj][idElement]-=size);
            csf_realloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement], 0);
        }
        else std::cout<<"Position higher than table szData[idType][idObj][idElement]!\n";
    }

    void DeleteDatasStartingTo(int idType, int idObj, int idElement, int position, int size)
    {
        int sz=position+size;
        if(sz<iData[idType][idObj][idElement])
        {
            for(int i=sz; i<iData[idType][idObj][idElement]; i++)
                DataTab[idType][idObj][idElement][i-size]=DataTab[idType][idObj][idElement][i];

            szData[idType][idObj][idElement]=(iData[idType][idObj][idElement]-=size);
            csf_realloc<TYPE>(&DataTab[idType][idObj][idElement], szData[idType][idObj][idElement], 0);
        }
        else std::cout<<"Position higher than table szData[idType][idObj][idElement]!\n";
    }

    /*void print(int idType, int idObj, int idElement, int i)
    {
        std::cout<<"x = "<<DataTab[i].x<<"\n";
        std::cout<<"y = "<<DataTab[i].y<<"\n";
        std::cout<<"z = "<<DataTab[i].z<<"\n";
        std::cout<<"idData = "<<DataTab[i].idData<<"\n";
        std::cout<<"idObj = "<<DataTab[i].idObj<<"\n";
        std::cout<<"lightF = "<<DataTab[i].lightF<<"\n";
        std::cout<<"iData[idType][idObj][idElement] = "<<iData[idType][idObj][idElement]<<"\n\n";
    }*/

    void clearDatas()
    {   for(int i=0; i<2; i++)
        {
            for(int j=0; j<iObject[i]; j++)
            {
                for(int k=0; k<iElement[i][iObject[i]];  k++)
                {
                    free(DataTab[i][j][k]);
                    DataTab[i][j][k]=NULL;
                }
                free(iData[i][j]);
                iData[i][j]=NULL;
                free(szData[i][j]);
                szData[i][j]=NULL;
            }
        }
    }

    void clearAll()
    {   for(int i=0; i<4; i++)
        {
            for(int j=0; j<iObject[i]; j++)
            {
                for(int k=0; k<iElement[i][j];  k++)
                {
                    free(DataTab[i][j][k]);
                    DataTab[i][j][k]=NULL;
                }
                free(DataTab[i][j]);
                DataTab[i][j]=NULL;
                free(iData[i][j]);
                iData[i][j]=NULL;
                free(szData[i][j]);
                szData[i][j]=NULL;
            }
            free(DataTab[i]);
            DataTab[i]=NULL;
            free(iData[i]);
            iData[i]=NULL;
            free(szData[i]);
            szData[i]=NULL;
            free(showThis[i]);
            showThis[i]=NULL;
            free(setThis[i]);
            setThis[i]=NULL;
        iObject[i]=0;
        szObject[i]=0;
        free(iElement[i]);
        iElement[i]=NULL;
        free(szElement[i]);
        szElement[i]=NULL;
        }
    }

    int LEP(int idType, int idObj)
    {
        return iElement[idType][idObj]-1;
    }

    int LOP(int idType)
    {
        return iObject[idType]-1;
    }

    int LDP(int idType, int idObj, int idElement)
    {
        return iData[idType][idObj][idElement]-1;
    }

    bool isObjectVisible(int idType, int idObj)
    {
        return showThis[idType][idObj];
    }

    TYPE GetLastData(int idType, int idObj, int idElement)
    {
        return DataTab[idType][idObj][idElement][iData[idType][idObj][idElement]-1];
    }

    TYPE*** & operator [] (int i) { return DataTab[i] ; };
};


template<class TYPE> class csMATRIX3
{
    private:
        TYPE***DataTab;
        int **iData,*iElement, iObject;
        int **szData,*szElement, szObject;
        bool *setThis, *showThis;
    public:
        csMATRIX3()
        {
            DataTab=0;
            iData=0;
            iElement=0;
            iObject=0;
            szData=0;
            szElement=0;
            szObject=0;
            setThis=0;
            showThis=0;
        }
    void newObject()
    {
        if(szObject <= iObject)
        {
            szObject = 1 + iObject;
            csf_realloc<TYPE**>(&DataTab, iObject, szObject);
            csf_realloc<int*>(&iData, iObject, szObject);
            csf_realloc<int*>(&szData, iObject, szObject);
            csf_VRealloc2<int>(&iElement, iObject, szObject, 0);
            csf_VRealloc2<int>(&szElement, iObject, szObject, 0);
            csf_VRealloc2<bool>(&showThis, iObject, szObject, 1);

        }
        iObject++;
    }

    void newElement(int idObj)
    {

        if(iElement[idObj] >= szElement[idObj])
        {   szElement[idObj]+=2;
            csf_realloc<TYPE*>(&DataTab[idObj], iElement[idObj], szElement[idObj]);
            csf_VRealloc2<int>(&iData[idObj], iElement[idObj], szElement[idObj], 0);
            csf_VRealloc2<int>(&szData[idObj], iElement[idObj], szElement[idObj],0);
        }
        iElement[idObj]++;
    }

    void newElement2(int idObj, int memSize)
    {
        if(iElement[idObj] >= szElement[idObj])
        {   szElement[idObj]+=memSize;
            csf_realloc<TYPE*>(&DataTab[idObj], iElement[idObj], szElement[idObj]);
            csf_VRealloc2<int>(&iData[idObj], iElement[idObj], szElement[idObj], 0);
            csf_VRealloc2<int>(&szData[idObj], iElement[idObj], szElement[idObj],0);
        }
        iElement[idObj]++;
    }

    void newDefinedElement(int idObj, TYPE* pData, int size)
    {
        if(iElement[idObj] >= szElement[idObj])
        {   szElement[idObj]+=2;
            csf_realloc<TYPE*>(&DataTab[idObj], iElement[idObj], szElement[idObj]);
            csf_VRealloc2<int>(&iData[idObj], iElement[idObj], szElement[idObj], 0);
            csf_VRealloc2<int>(&szData[idObj], iElement[idObj], szElement[idObj],0);
        }
        DataTab[idObj][iElement[idObj]]=pData;
        iData[idObj][iElement[idObj]]=size;
        szData[idObj][iElement[idObj]]=size;
        iElement[idObj]++;
    }

    void InsertElementAt(int idObj, TYPE* pData, int position, int size)
    {
        if(position<iElement[idObj])
        {
            newElement(idObj);
            for(int i=iElement[idObj]-1; i >= position; i--)
            {   DataTab[idObj][i+1]=DataTab[idObj][i];
                iData[idObj][i+1]=iData[idObj][i];
                szData[idObj][i+1]=szData[idObj][i];
            }
            DataTab[idObj][position]=pData;
            iData[idObj][position]=size;
            szData[idObj][position]=size;
        }
        else std::cout<<"Position higher than table szData[idObj]!\n";
    }

    void DeleteElementAt(int idObj, int position)
    {
        if(position<iElement[idObj])
        {   for(int i=position; i<iElement[idObj]-1; i++)
            {   DataTab[idObj][i]=DataTab[idObj][i+1];
                iData[idObj][i]=iData[idObj][i+1];
                szData[idObj][i]=szData[idObj][i+1];
            }

            szElement[idObj]=--iElement[idObj];
            csf_realloc<TYPE*>(&DataTab[idObj], iElement[idObj], szElement[idObj]);
            csf_VRealloc2<int>(&iData[idObj], iElement[idObj], szElement[idObj], 0);
            csf_VRealloc2<int>(&szData[idObj], iElement[idObj], szElement[idObj], 0);
        }
        else std::cout<<"Position higher than table szData[idObj]!\n";
    }

    void InsertDataAtEnd(int idObj, int idElement, TYPE Data)
    {
        if(iData[idObj][idElement] >= szData[idObj][idElement])
        {   szData[idObj][idElement]+=5;

            csf_VRealloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement]);
        }
        DataTab[idObj][idElement][iData[idObj][idElement]]=Data;
        //std::cout<<idObj<<" "<<idElement<<" "<<iData[idObj][idElement]<<"\n";
        iData[idObj][idElement]++;
    }

    void InsertDataAtEnd2(int idObj, int idElement, TYPE Data)
    {
        if(iData[idObj][idElement]>szData[idObj][idElement]-2)
        {   szData[idObj][idElement]+=2;

            csf_VRealloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement]);
        }
        DataTab[idObj][idElement][iData[idObj][idElement]]=Data;
        //std::cout<<idObj<<" "<<idElement<<" "<<iData[idObj][idElement]<<"\n";
        iData[idObj][idElement]++;
    }

    void InsertDataAtEnd3(int idObj, int idElement, TYPE Data, int memSize)
    {
        if(iData[idObj][idElement] >= szData[idObj][idElement])
        {   szData[idObj][idElement]+=memSize;

            csf_VRealloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement]);
        }
        DataTab[idObj][idElement][iData[idObj][idElement]]=Data;
        //std::cout<<idObj<<" "<<idElement<<" "<<iData[idObj][idElement]<<"\n";
        iData[idObj][idElement]++;
    }

    void InsertDataOnTop(int idObj, int idElement, TYPE Data)
    {
        if(iData[idObj][idElement] >= szData[idObj][idElement])
        {   szData[idObj][idElement]+=5;
            csf_VRealloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement]);
        }

        for(int i=iData[idObj][idElement]; i>=0; i--)
        {   DataTab[idObj][idElement][i+1]=DataTab[idObj][idElement][i];
        }
        DataTab[idObj][idElement][0]=Data;
        iData[idObj][idElement]++;
    }

    void InsertDataAt(int idObj, int idElement, TYPE Data, int position)
    {
        if(position<=iData[idObj][idElement])
        {   if(iData[idObj][idElement]>szData[idObj][idElement]-2)
            {   szData[idObj][idElement]+=20;
                csf_VRealloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement]);
            }
            for(int i=iData[idObj][idElement]; i>=position; i--)
                DataTab[idObj][idElement][i+1]=DataTab[idObj][idElement][i];

            DataTab[idObj][idElement][position]=Data;
            iData[idObj][idElement]++;
        }
        else std::cout<<"Position larger than table size!\n";
    }

    void InsertDatasStartingTo(int idObj, int idElement, TYPE* Data, int position, int size)
    {
        if(position<=iData[idObj][idElement])
        {   if(iData[idObj][idElement]>=szData[idObj][idElement]-size)
            {   szData[idObj][idElement]+=size+1;
                csf_VRealloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement]);
            }
            for(int i=iData[idObj][idElement]; i>=position; i--)
                DataTab[idObj][idElement][i+size]=DataTab[idObj][idElement][i];

            int sz=position+size;
            for(int i=position; i<sz; i++)
                DataTab[idObj][idElement][i]=Data[i-position];
            iData[idObj][idElement]+=size;
        }
        else std::cout<<"Position larger than table size!\n";
    }

    void InsertInverseDatasStartingTo(int idObj, int idElement, TYPE* Data, int position, int size)
    {
        if(position<=iData[idObj][idElement])
        {   if(iData[idObj][idElement]>=szData[idObj][idElement]-size)
            {   szData[idObj][idElement]+=size+1;
                csf_VRealloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement]);
            }
            for(int i=iData[idObj][idElement]; i>=position; i--)
                DataTab[idObj][idElement][i+size]=DataTab[idObj][idElement][i];

            int sz=position+size;
            for(int i=position; i<sz; i++)
                DataTab[idObj][idElement][i]=Data[size-1-i+position];
            iData[idObj][idElement]+=size;
        }
        else std::cout<<"Position larger than table size!\n";
    }

    void InsertDatasOnTop(int idObj, int idElement, TYPE* Data, int size)
    {
        if(iData[idObj][idElement] >= szData[idObj][idElement]-size)
            {   szData[idObj][idElement]+=size+1;
                csf_VRealloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement]);
            }
            for(int i=iData[idObj][idElement]; i>=0; i--)
                DataTab[idObj][idElement][i+size]=DataTab[idObj][idElement][i];

            int sz=size;
            for(int i=0; i<sz; i++)
                DataTab[idObj][idElement][i]=Data[i];
            iData[idObj][idElement]+=size;

        //else std::cout<<"Position larger than table size!\n";
    }

    void SetDataPoint(int idObj, int idElement,int idData, TYPE Data)
    {
        if(idData>szData[idObj][idElement]-2)
        {   szData[idObj][idElement]=idData+50;
            iData[idObj][idElement]=idData+1;
            csf_realloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement], 0);
        }
        if(idData>=iData[idObj][idElement]) iData[idObj][idElement]=idData+1;
            DataTab[idObj][idElement][idData]=Data;
    }

    void DeleteLastData(int idObj, int idElement)
    {
        szData[idObj][idElement]=iData[idObj][idElement]--;
        csf_realloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement], 0);

    }

    void DeleteFirstData(int idObj, int idElement)
    {
        for(int i=0; i<iData[idObj][idElement]-1; i++)
        {   DataTab[idObj][idElement][i]=DataTab[idObj][idElement][i+1];
        }
        szData[idObj][idElement]=--iData[idObj][idElement];
        csf_realloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement], 0);
    }

    void DeleteDataAt(int idObj, int idElement, int position)
    {
        if(position<iData[idObj][idElement])
        {   for(int i=position; i<iData[idObj][idElement]-1; i++)
                DataTab[idObj][idElement][i]=DataTab[idObj][idElement][i+1];

            szData[idObj][idElement]=--iData[idObj][idElement];
            csf_realloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement], 0);
        }
        else std::cout<<"Position higher than table szData[idObj][idElement]!\n";
    }

    void DeleteTopDatas(int idObj, int idElement, int size)
    {
        if(size<iData[idObj][idElement])
        {
            for(int i=size; i<iData[idObj][idElement]; i++)
                DataTab[idObj][idElement][i-size]=DataTab[idObj][idElement][i];
            szData[idObj][idElement]=(iData[idObj][idElement]-=size);
            csf_realloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement], 0);
        }
        else std::cout<<"Position higher than table szData[idObj][idElement]!\n";
    }

    void DeleteDatasStartingTo(int idType, int idObj, int idElement, int position, int size)
    {
        int sz=position+size;
        if(sz<iData[idObj][idElement])
        {
            for(int i=sz; i<iData[idObj][idElement]; i++)
                DataTab[idObj][idElement][i-size]=DataTab[idObj][idElement][i];

            szData[idObj][idElement]=(iData[idObj][idElement]-=size);
            csf_realloc<TYPE>(&DataTab[idObj][idElement], szData[idObj][idElement], 0);
        }
        else std::cout<<"Position higher than table szData[idObj][idElement]!\n";
    }

    /*void print(int idType, int idObj, int idElement, int i)
    {
        std::cout<<"x = "<<DataTab[i].x<<"\n";
        std::cout<<"y = "<<DataTab[i].y<<"\n";
        std::cout<<"z = "<<DataTab[i].z<<"\n";
        std::cout<<"idData = "<<DataTab[i].idData<<"\n";
        std::cout<<"idObj = "<<DataTab[i].idObj<<"\n";
        std::cout<<"lightF = "<<DataTab[i].lightF<<"\n";
        std::cout<<"iData[idObj][idElement] = "<<iData[idObj][idElement]<<"\n\n";
    }*/

    void clearDatas()
    {
        for(int j=0; j<iObject; j++)
            {
                for(int k=0; k<iElement[iObject];  k++)
                {
                    free(DataTab[j][k]);
                    DataTab[j][k]=NULL;
                }
                free(iData[j]);
                iData[j]=NULL;
                free(szData[j]);
                szData[j]=NULL;
            }
    }

    void clearAll()
    {
        for(int j=0; j<iObject; j++)
            {
                for(int k=0; k<iElement[j];  k++)
                {
                    free(DataTab[j][k]);
                    DataTab[j][k]=NULL;
                }
                free(DataTab[j]);
                DataTab[j]=NULL;
                free(iData[j]);
                iData[j]=NULL;
                free(szData[j]);
                szData[j]=NULL;
            }
            free(DataTab);
            DataTab=NULL;
            free(iData);
            iData=NULL;
            free(szData);
            szData=NULL;
            free(showThis);
            showThis=NULL;
            free(setThis);
            setThis=NULL;
    }

    int LEP(int idObj)
    {
        return iElement[idObj]-1;
    }

    int LOP()
    {
        return iObject-1;
    }

    int LDP(int idObj, int idElement)
    {
        return iData[idObj][idElement]-1;
    }

    bool isObjectVisible(int idObj)
    {
        return showThis[idObj];
    }

    TYPE GetLastData(int idObj, int idElement)
    {
        return DataTab[idObj][idElement][iData[idObj][idElement]-1];
    }

    TYPE*** & operator [] (int i) { return DataTab[i] ; };
};


template<class TYPE> struct csLIST_DATA
{
    int position;
    TYPE data;
};

template<class TYPE> struct csLIST_DATATAB
{
    int position;
    TYPE* data;
    int size;
};

template<class TYPE> struct csLIST_DATATABPART
{
    int position;
    TYPE* data;
    int begin;
    int size;
};

struct csTABCOORDS
{
    int position;
    int size;
};


template<class TYPE> class csLIST
{
    private:
        TYPE*DataTab;
        int length, iLength, inc;
    public:
        csLIST()
        {
            DataTab=0;
            length=0;
            iLength=0;
            inc=2;
        }
        /*~csLIST()
        {
            free(DataTab);
            DataTab = 0;
        }*/
    int size()
    {
        return iLength;
    }
    int*sizePtr()
    {
        return &iLength;
    }
    TYPE & operator[](int i)
    {
        return DataTab[i];
    }
    TYPE* getTable()
    {
        return DataTab;
    }
    void init(int size)
    {
        DataTab=0;
        length=0;
        iLength=0;
        inc=2;

        if(size>0)
        {   iLength=0;
            DataTab = (TYPE*)malloc(size*sizeof(TYPE));
            if(!DataTab) std::cout<<"Memory allocation error!\n";
            else length=size;
        }
        else std::cout<<"The size most be upper than 0!\n";
    }
    void full(int size, TYPE data)
    {
        if(size>0)
        {   
            DataTab = (TYPE*)malloc(size*sizeof(TYPE));
            if(!DataTab) std::cout<<"Memory allocation error!\n";
            else 
            {
                length=size;
                for(int i=0; i<size; i++)
                {
                    DataTab[i] = data;
                }
                iLength=size;
            }
        }
        else std::cout<<"The size most be upper than 0!\n";
    }
    void insertEnd(TYPE data)
    {
        if(iLength>=length)
        {   length+=inc;
            TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
            if(!tmp)
            {
                free(DataTab);
            }
            else DataTab=tmp;
        }
        DataTab[iLength++]=data;
    }
    void insertEnd2(TYPE data, size_t memsz)
    {
        if(iLength>=length)
        {   length+=memsz;
            TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
            if(!tmp)
                free(DataTab);
            else DataTab=tmp;
        }
        DataTab[iLength++]=data;
    }
    void insertBegin(TYPE data)
    {
        if(iLength>=length)
        {   length+=inc;
            TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
            if(!tmp)
            {   free(DataTab);
                std::cout<<"Memory allocation error!\n";
            }
            else DataTab=tmp;
        }

        for(int i=iLength-1; i>=0; i--) 
        {   DataTab[i+1]=DataTab[i];
        }
        DataTab[0]=data;
        iLength++;
    }
    void insertAt(TYPE data, int position)
    {
        if(position<=iLength)
        {   if(iLength>=length)
            {   length+=inc;
                TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
                if(!tmp)
                {   free(DataTab);
                    std::cout<<"Memory allocation error!\n";
                }
                else DataTab=tmp;
            }
            for(int i=iLength-1; i>=position; i--)
                DataTab[i+1]=DataTab[i];

            DataTab[position]=data;
            iLength++;
        }
        else
        {
            length+=position-iLength+1;
            TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
            if(!tmp)
            {   free(DataTab);
                std::cout<<"Memory allocation error!\n";
            }
            else DataTab=tmp;

            /*for(int i=iLength; i<position; i++)
                DataTab[i]=zero;*/

            DataTab[position]=data;
            iLength = position +1;
            std::cout<<"Warning : Position larger than table size.\n";
            std::cout<<"This could cause problems!\n";
        }
    }
    void insertTableAt(TYPE* data, int position, int size)
    {
        if(position<=iLength)
        {   
            if(iLength>=length-size)
            {      
                iLength = iLength|1; // si iLength = 0, iLength = 1;
                length = iLength + size +1;
                TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
                if(!tmp)
                {   free(DataTab);
                    std::cout<<"Memory allocation error!\n";
                }
                else DataTab=tmp;
            }
            for(int i=iLength-1; i>=position; i--)
                DataTab[i+size]=DataTab[i];

            int sz=position+size;
            for(int i=position, j=0; i<sz; i++, j++)   
                DataTab[i]=data[j];
            iLength+=size;
        }
        else
        {
            length+=position-iLength+size+1;
            TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
            if(!tmp)
            {   free(DataTab);
                std::cout<<"Memory allocation error!\n";
            }
            else DataTab=tmp;

            /*for(int i=iLength; i<position; i++)
                DataTab[i]=zero;*/

            int sz=position+size;
            for(int i=position; i<sz; i++)
                DataTab[i]=data[i-position];
            iLength = position + size;
            std::cout<<"Warning : Position larger than table size.\n";
            std::cout<<"This could cause problems!\n";
        }
    }
    void insertTablePartAt(int position, TYPE* data, int begin, int size)
    {
        if(position<=iLength)
        {   if(iLength>=length-size)
            {   length+=size+1;
                TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
                if(!tmp)
                {   free(DataTab);
                    std::cout<<"Memory allocation error!\n";
                }
                else DataTab=tmp;
            }
            for(int i=iLength; i>=position; i--)
            {   DataTab[i+size]=DataTab[i];
            }
            int sz=position+size;
            for(int i=position, j=begin; i<sz; i++, j++)
                DataTab[i]=data[j];
            iLength+=size;
        }
        else
        {
            length+=position-iLength+size+1;
            TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
            if(!tmp)
            {   free(DataTab);
                std::cout<<"Memory allocation error!\n";
            }
            else DataTab=tmp;

            /*for(int i=iLength; i<position; i++)
                DataTab[i]=zero;*/

            int sz=position+size, pos = begin-position;
            for(int i=position, j=begin; i<sz; i++, j++)
                DataTab[i]=data[j];
            iLength = position + size;
            std::cout<<"Warning : Position larger than table size.\n";
            std::cout<<"This could cause problems!\n";
        }
    }
    
    void move(int from, int to)
    {
        TYPE data = DataTab[from];
        if(from < to)
        {
            for(int i=from+1; i<=to; i++) 
                DataTab[i-1] = DataTab[i];
            DataTab[to] = data;
        }
        else if(from > to)
        {
            for(int i=from-1; i>=to; i--) 
                DataTab[i+1] = DataTab[i];
            DataTab[to] = data;
        }
    }
    void duplicate(int src, int pos)
    {
        TYPE data = DataTab[src];
        insertAt(data, pos);
    }
    void moveCharPtr(int from, int to);
    void duplicatePointList(int from, int to);
    char* toString(int from, int to);
    /*{
        char*data = csf_alloc<char>(strlen((const char*)DataTab[from])+1);
        sprintf(data,"%s",DataTab[from]);

        if(from < to)
        {
            for(int i=from+1; i<to; i++) 
            {
                int j = i-1;
                free(DataTab[j]);
                DataTab[j] = csf_alloc<char>(strlen((const char*)DataTab[i])+1);
                printf(DataTab[j],"%s",DataTab[i]);
            }
            free(DataTab[to]);
            DataTab[to] = data;
        }
        else if(from > to)
        {
            for(int i=from-1; i>to; i--) 
            {
                int j = i+1;
                free(DataTab[j]);
                DataTab[j] = csf_alloc<char>(strlen((const char*)DataTab[i])+1);
                printf(DataTab[j],"%s",(const char*)DataTab[i]);
            }
            free(DataTab[to]);
            DataTab[to] = data;
        }
    }*/
    void permute(int i, int j)
    {
        TYPE data = DataTab[i];
        DataTab[i] = DataTab[j];
        DataTab[j] = data;
    }
    void deleteEnd()
    {
        length=iLength--;
        TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
        if(!tmp)
        {   free(DataTab);
            std::cout<<"Memory allocation error!\n";
        }
        else DataTab=tmp;

    }
    void deleteBegin()
    {
        for(int i=0; i<iLength-1; i++)
        {   DataTab[i]=DataTab[i+1];
        }
        length=--iLength;
        TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
        if(!tmp)
        {   free(DataTab);
            std::cout<<"Memory allocation error!\n";
        }
        else DataTab=tmp;
    }
    void deleteAt(int position)
    {
        if(position<iLength)
        {   
            if(iLength>1)
            {
                for(int i=position; i<iLength-1; i++)
                DataTab[i]=DataTab[i+1];

                length=--iLength;
                TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
                if(!tmp)
                {   free(DataTab);
                    std::cout<<"Memory allocation error!\n";
                }
                else DataTab=tmp;
            }
            else clear();
        }
        else std::cout<<"Position larger than table size!\n";
    }
    void deleteTableAtBegining(int size)
    {
        if(size<iLength)
        {
            for(int i=size; i<iLength; i++)
                DataTab[i-size]=DataTab[i];
            length=(iLength-=size);
            TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
            if(!tmp)
            {   free(DataTab);
                std::cout<<"Memory allocation error!\n";
            }
            else DataTab=tmp;
        }
        else std::cout<<"Position larger than table size!\n";
    }
    void deleteTableAt(int position, int size)
    {
        int sz=position+size;
        if(sz<iLength)
        {
            for(int i=sz; i<iLength; i++)
                DataTab[i-size]=DataTab[i];

            length=(iLength-=size);
            TYPE* tmp=(TYPE*)realloc(DataTab, length*sizeof(TYPE));
            if(!tmp)
            {   free(DataTab);
                std::cout<<"Memory allocation error!\n";
            }
            else DataTab=tmp;
        }
        else
        {
            if(position==0&&size>=iLength)
                clear();
            else
                std::cout<<"Position larger than table size!\n";
        }
    }
    void minMaxSortD()
    {
        if(iLength>0)
        {
            double mn, mx;
            for(int j=0; j<iLength; j++)
            for(int i=1; i<iLength; i++)
            {
                mx=(double)DataTab[i];
                mn =(double)DataTab[i-1];
                if(mx<mn)
                {
                    DataTab[i]=(TYPE)mn;
                    DataTab[i-1]=(TYPE)mx;
                }
            }
        }
        else
            std::cout<<"Empty list connot be sorted !\n";
    }
    void maxMinSortD()
    {
        if(iLength>0)
        {
            double mn, mx;
            for(int j=0; j<iLength; j++)
            for(int i=1; i<iLength; i++)
            {
                mx=(double)DataTab[i];
                mn =(double)DataTab[i-1];
                if(mx>mn)
                {
                    DataTab[i]=(TYPE)mn;
                    DataTab[i-1]=(TYPE)mx;
                }
            }
        }
        else
            std::cout<<"Empty list connot be sorted !\n";
    }
    void minMaxSortL()
    {
        if(iLength>0)
        {
            long mn, mx;
            for(int j=0; j<iLength; j++)
            for(int i=1; i<iLength; i++)
            {
                mx = DataTab[i];
                mn = DataTab[i-1];
                if(mx<mn)
                {
                    DataTab[i]=mn;
                    DataTab[i-1]=mx;
                }
            }
        }
        else
            std::cout<<"Empty list connot be sorted !\n";
    }
    void maxMinSortL()
    {
        if(iLength>0)
        {
            long mn, mx;
            for(int j=0; j<iLength; j++)
            for(int i=1; i<iLength; i++)
            {
                mx = DataTab[i];
                mn = DataTab[i-1];
                if(mx>mn)
                {
                    DataTab[i]=mn;
                    DataTab[i-1]=mx;
                }
            }
        }
        else
            std::cout<<"Empty list connot be sorted !\n";
    }
    void print(int i)
    {
        std::cout<<DataTab[i]<<" ";
    }
    void printD(int i)
    {
        //std::cout<<setprecision(precision)<<*(double*)&DataTab[i]<<" ";
        std::cout<<DataTab[i]<<" ";
    }
    void printAll(const char*title="")
    {
        std::cout<<title<<"\n{ ";
        for(int i=0; i<iLength; i++)
            print(i);
        std::cout<<"}\n";
    }
    void printAllD(const char*title="")
    {
        std::cout<<title<<"\n{ ";
        for(int i=0; i<iLength; i++)
            printD(i);
        std::cout<<"}\n";
    }
    void operator+=(TYPE data)
    {
        insertEnd(data);
    }
    void operator+=(csLIST_DATA<TYPE> data)
    {
        insertAt(data.data,data.position);
    }
    void operator+=(csLIST_DATATAB<TYPE> data)
    {
        insertTableAt(data.data,data.position,data.size);
    }
    void operator+=(csLIST_DATATABPART<TYPE> data)
    {
        insertTablePartAt(data.position,data.data,data.begin,data.size);
    }
    void operator--(int i)
    {
        deleteEnd();
    }
    void operator-=(unsigned int i)
    {
        deleteAt(i);
    }
    void operator-=(csTABCOORDS coords)
    {
        deleteTableAt(coords.position, coords.size);
    }
    void clear()
    {
        if(iLength)
        {
            free(DataTab);
            DataTab=NULL;
            iLength=0;
            length=0;
        }
    }
};


#endif // TEMPLATESSTRUCT_H_INCLUDED
