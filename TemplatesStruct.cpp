#include "TemplatesStruct.h"
#include <string.h>
#include <iostream>
#include <windows.h>



template<> void csLIST<char*>::moveCharPtr(int from, int to)
{
    char*data = csf_alloc<char>(strlen((const char*)DataTab[from])+1);
    sprintf(data,"%s",DataTab[from]);

    if(from < to)
    {
        for(int i=from+1; i<=to; i++) 
        {
            int j = i-1;
            DataTab[j] = (char*)realloc(DataTab[j], strlen((const char*)DataTab[i])+1);
            sprintf(DataTab[j],"%s",DataTab[i]);
        }
        free(DataTab[to]);
        DataTab[to] = data;
    }
    else if(from > to)
    {
        for(int i=from-1; i>=to; i--) 
        {
            int j = i+1;
            DataTab[j] = (char*)realloc(DataTab[j], strlen((const char*)DataTab[i])+1);
            sprintf(DataTab[j],"%s",DataTab[i]);
        }
        free(DataTab[to]);
        DataTab[to] = data;
    }
}

template<> void csLIST<csLIST<POINT> >::duplicatePointList(int from, int to)
{
    if(iLength)
    {
        int n = DataTab[from].size();
        csLIST<POINT> data;
        data.full(n, {0,0});
        for(int i=0; i<n; i++)
        {
            data[i] = DataTab[from][i];
        }
        insertAt(data, to);
    }
}

template<> char* csLIST<char>::toString(int from, int to)
{
    char* ret = 0;
    if(from < to)
    {
        int end = to + 1;
        if(to >= iLength)
            end = iLength;
        ret = (char*)malloc(end - from);
        sprintf(ret,"");
        char c[2];
        for(int i=from; i<end; i++)
        {
            sprintf(c, "%c", DataTab[i]);
            strcat(ret,c);
        }
    }
    else
    {
        int end = from + 1;
        if(from >= iLength)
            end = iLength;
        ret = (char*)malloc(end - to);
        sprintf(ret,"");
        char c[2];
        for(int i=end-1; i>=to; i--)
        {
            sprintf(c, "%c", DataTab[i]);
            strcat(ret,c);
        }
    }
    return ret;
}
