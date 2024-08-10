#include "csGRID.h"

extern csCNTR_VARS cv;

csGRID::csGRID(unsigned _idp, RECT _geometry, SIZE _size, bool _animate)
{
    geometry = _geometry;
    size = _size;
    animate = _animate;
    dx = geometry.right/size.cx;
    dy = geometry.bottom/size.cy;
    idp = _idp;
    for(unsigned j = 0; j<size.cy; j++)
    {
        map+=csNewList<int>();
        for(unsigned i = 0; i<size.cx; i++)
        {
            map[j]+=0;
        }
    }
    nextPos = 0;
}

unsigned csGRID::getMin(unsigned a, unsigned b)
{
    if(a<b) return a;
    else return b;
}

RECT csGRID::getNextGeometry(SIZE sz)
{
    UPOINT p[2]={{INT_MAX,INT_MAX},{INT_MAX,INT_MAX}};
    RECT ret={0};
    unsigned incx = 0;
    unsigned incy = 0;
    unsigned m = size.cx;
    unsigned n = size.cy;
    /*if(geomList.size() == 0)
    {
        ret={0,0,getMin(m,sz.cx), getMin(n,sz.cy)};
    }
    else*/
    {
        unsigned n1 = n-1, m1 = m-1, m2=m-2;
        for(unsigned j = 0; j<n; j++)
        {
            for(unsigned i = 0; i<m; i++)
            {
                if (incx==1) break;
                if(map[j][i]==0)
                {
                    p[incx].x = i;
                    p[incx].y = j;
                    incx++;
                }
            }
            if (incx==1) break;
        }
        for(unsigned j = p[0].y; j<n; j++)
        {
            for(unsigned i = p[0].x; i<m; i++)
            {
                if (incx==2) break;
                if(map[j][i]!=0)
                {
                    p[incx].x = i;
                    p[incx].y = j;
                    incx++;
                }
            }
            if (incx==2) break;
        }
    //std::cout<<"dx = "<<p[1].x<<"\n";
        ret={p[0].x,p[0].y,getMin(sz.cx,p[1].x-p[0].x), getMin(sz.cy,n-p[0].y)};
    }
    return ret;
}

void csGRID::setMap(RECT r, unsigned _id)
{
    unsigned m = r.right + r.left;
    unsigned n = r.bottom+r.top;
    for(unsigned j = r.top; j<n; j++)
    {
        for(unsigned i = r.left; i<m; i++)
        {
            map[j][i] = _id;
        }
    }
}

RECT csGRID::newGeometry(SIZE _size, RECT _marg)
{
    RECT geom=getNextGeometry(_size);
    if(geom.right==0 || geom.bottom==0)
        std::cout<<"Grid Limit exceeded !\n";
    else
    {
        geomList += geom;
        margList += _marg;
        setMap(geom, geomList.size());
    }
    return realGeometry(geom, _marg);
}

RECT csGRID::realGeometry(RECT geom, RECT _marg)
{
    return {geometry.left + geom.left*dx+_marg.left*dx/100,
                   geometry.top + geom.top*dy+_marg.top*dy/100,
                   geom.right*dx-(_marg.right+_marg.left)*dx/100,
                   geom.bottom*dy-(_marg.bottom+_marg.top)*dy/100};
}

RECT csGRID::realGeometry2(RECT geom, RECT _marg)
{
    RECT r = realGeometry(geom, _marg);
    r.right+=r.left;
    r.bottom+=r.top;
}

void csGRID::newContainer(unsigned _id)
{
    if(idList.size()<geomList.size())
    {
        idList += _id;
    }
    else
        std::cout<<"Cannot add a new Container ! \n First set geometry.";
}

unsigned csGRID::posFromID(unsigned _id)
{
    unsigned n = idList.size();
    unsigned i = 0;
    for(i=0; i<n; i++)
        if(idList[i]==_id)
            break;
    return i;
}

void csGRID::deleteContainer(unsigned _id)
{
    unsigned pos = posFromID(_id);
    unsigned n = idList.size();
    unsigned id = 0;
    int len = n-pos;

    //std::cout<<ShowWindow(cv.CNTLIST[_id],0);
    DestroyWindow(cv.CNTLIST[_id]);
    csLIST<RECT> geomSaved;//, idSaved, margSaved;
    //geomSaved += csLIST_DATATABPART<RECT>{0,geomList.getTable(), (int)pos, len};
    for(unsigned i=pos; i<n; i++)
        geomSaved += geomList[i];
    //idSaved += csLIST_DATATAB<int>{idList.getTable(), pos, len};
    //margSaved += csLIST_DATATAB<RECT>{idList.getTable(), pos, len};
    for(unsigned i=pos; i<n; i++)
        setMap(geomList[i],0);

    geomList -= csTABCOORDS{pos, len};

    //idList.printAll("before");
    idList -= pos;

        //std::cout<<"pos = "<<idList[0]<<" ID = "<<_id<<"\n";
    //idList.printAll("after");
    margList -= pos;

    RECT geom;
    for(unsigned i=0; i<len-1; i++)
    {
        id = idList[pos+i];
        geom=getNextGeometry({geomSaved[i+1].right, geomSaved[i+1].bottom});
        //std::cout<<id<<" "<<geomSaved[i+1].right<<" {"<<geom.left<<","<<geom.top<<","<<geom.right<<","<<geom.bottom<<"}\n";
        geomList += geom;
        setMap(geom, geomList.size());
        //std::cout<<i<<"\n";
        cv.cp[id]->AutoTransform.Type = AUTO_TRANSF_RECT;
        cv.cp[id]->AutoTransform.Time = 10;
        cv.cp[id]->AutoTransform.InitialRect = realGeometry(geomSaved[i+1],margList[pos+i]);
        cv.cp[id]->AutoTransform.FinalRect = realGeometry(geom,margList[pos+i]);

        /*RECT rdraw = {0,0,CntParams.BackgroundImageSizes.width,CntParams.BackgroundImageSizes.height};//transformed to max rect if {0,0,0,0}
        if(CntParams.DCSizes.width!=0 && CntParams.DCSizes.height !=0)
            rdraw = {0,0,CntParams.DCSizes.width,CntParams.DCSizes.height};
        cspa.initSurfaceDesign(hdc, CntParams.BackgroundColor, rdraw);*/

        //std::cout<<realGeometry(geomList[i-1],margList[i-1]).right<<"\n";
        cv.AUTOTRANSCOUNT[id] = 0;
    }
    geomSaved.clear();
    //setMap(RECT r, unsigned _id)
}

csGRID::~csGRID()
{
    //dtor
}
