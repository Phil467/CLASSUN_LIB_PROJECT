#include "csSURFACE.h"

void csSURFACE::csHLine(int IDO, int& r, int& g, int& b, double& tmp, double& a, long& lVal, long& dVal, long& nCount, char* buf, char* DEPTH)
{
    int k;
    if(SPO.isObjectVisible(IDG, IDO))
        for(int k1=0; k1 <= SPO.LEP(IDG, IDO); k1++)
        {
            for(k=0; k < SPO.LDP(IDG, IDO, k1); k++)
            {
                //std::cout<<k<<" ";
                vect2= {SPO[IDG][IDO][k1][k], SPO[IDG][IDO][k1][k+1]};
                if(vect2.A.y==vect2.B.y)
                {
                    csf_getMinMax(vect2.A,vect2.B,pt0, pt);

                    if(pt0.x<0) pt0.x=0;
                    else if(pt0.x>smx) pt0.x=smx;
                    if(pt.x<0) pt.x=0;
                    else if(pt.x>smy) pt.x=smx;
                    for(int i=pt0.x; i<pt.x; i++)
                    {
                        nCount=(pt.y*smx+i)*4;
                        memcpy(&dVal, &DEPTH[nCount], 4);
                        if(dVal<VALUE[IDG][IDO])
                        {
                            memcpy(&lVal, &buf[nCount], 4);
                            memcpy(&lVal, &buf[nCount], 4);
                            b = GetRValue(lVal);
                            g = GetGValue(lVal);
                            r = GetBValue(lVal);
                            lVal=Tint({SCO[IDG][IDO][k1][k].b,SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r},
                            {b,g,r}, SCO[IDG][IDO][k1][k].a);
                            memcpy(&buf[nCount], &lVal, 4);
                            memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                        }
                    }
                }
            }
        }
}

void csSURFACE::csVLine(int IDO, int& r, int& g, int& b, double& tmp, double& a, long& lVal, long& dVal, long& nCount, char* buf, char* DEPTH)
{
    int k;
    double fres;
    if(SPO.isObjectVisible(IDG, IDO))
        for(int k1=0; k1 <= SPO.LEP(IDG, IDO); k1++)
        {
            for(k=0; k < SPO.LDP(IDG, IDO, k1); k++)
            {
                //std::cout<<k<<" ";
                vect2= {SPO[IDG][IDO][k1][k], SPO[IDG][IDO][k1][k+1]};
                if(vect2.A.x==vect2.B.x)
                {
                    csf_getMinMax(vect2.A,vect2.B,pt0, pt);

                    if(pt0.y<0) pt0.y=0;
                    else if(pt0.y>smy) pt0.y=smy;
                    if(pt.y<0) pt.y=0;
                    else if(pt.y>smy) pt.y=smy;
                    for(int j=pt0.y; j<pt.y; j++)
                    {
                        nCount=(j*smx+pt.x)*4;
                        memcpy(&dVal, &DEPTH[nCount], 4);
                        if(dVal<VALUE[IDG][IDO])
                        {
                            memcpy(&lVal, &buf[nCount], 4);
                            b = GetRValue(lVal);
                            g = GetGValue(lVal);
                            r = GetBValue(lVal);
                            lVal=Tint({SCO[IDG][IDO][k1][k].b,SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r},
                            {b,g,r}, SCO[IDG][IDO][k1][k].a);
                            memcpy(&buf[nCount], &lVal, 4);
                            memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                        }
                    }
                }
            }
        }
}

void csSURFACE::csLine(int IDO, int& r, int& g, int& b, double& tmp, double& a, long& lVal, long& dVal, long& nCount, char* buf, char* DEPTH)
{
    int k;
    double fres;
    if(SPO.isObjectVisible(IDG, IDO))
        for(int k1=0; k1 <= SPO.LEP(IDG, IDO); k1++)
        {
            for(k=0; k < SPO.LDP(IDG, IDO, k1); k++)
            {
                //std::cout<<k<<" ";
                vect2= {SPO[IDG][IDO][k1][k], SPO[IDG][IDO][k1][k+1]};
                csf_getMinMax(vect2.A,vect2.B,pt0, pt);


                double dx=vect2.A.x-vect2.B.x, dy=vect2.A.y-vect2.B.y;
                if(dx==0)
                {
                    dx=0.00001;

                }

                a=dy/dx;
                if(fabs(a)>1.0)
                {
                    if(pt0.y<0) pt0.y=0;
                    else if(pt0.y>smy) pt0.y=smy;
                    if(pt.y<0) pt.y=0;
                    else if(pt.y>smy) pt.y=smy;
                    for(int j=pt0.y; j<pt.y; j++)
                    {
                        tmp=(double)(j-vect2.A.y)/a+vect2.A.x;
                        int l0=int(tmp)-THK[IDG][IDO][k1][0], l1=int(tmp)+THK[IDG][IDO][k1][0];
                        if(l0>0&&l0<smx)
                        {
                            nCount=(j*smx+l0)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=tmp-double(int(tmp))+SCO[IDG][IDO][k1][0].a)>1.0) fres=1;
                                lVal=Tint({SCO[IDG][IDO][k1][0].b,SCO[IDG][IDO][k1][0].g, SCO[IDG][IDO][k1][0].r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }

                        if(l1>0&&l1<smx)
                        {
                            nCount=(j*smx+l1)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=tmp-double(int(tmp))+SCO[IDG][IDO][k1][0].a)>1.0) fres=1;
                                lVal=TintInverse({SCO[IDG][IDO][k1][0].b, SCO[IDG][IDO][k1][0].g, SCO[IDG][IDO][k1][0].r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                        if(l0<0) l0=0;
                        if(l1<0) l1=0;
                        if(l0>=smx) l0=smx-1;
                        if(l1>=smx) l1=smx-1;
                        for(int i=l0+1; i<l1; i++)
                        {
                            nCount=(j*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                lVal=Tint({SCO[IDG][IDO][k1][0].b,SCO[IDG][IDO][k1][0].g, SCO[IDG][IDO][k1][0].r},
                                {b,g,r}, SCO[IDG][IDO][k1][0].a);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                    }
                }
                else
                {
                    if(pt0.x<0) pt0.x=0;
                    else if(pt0.x>smx) pt0.x=smx;
                    if(pt.x<0) pt.x=0;
                    else if(pt.x>smx) pt.x=smx;
                    for(int i=pt0.x; i<pt.x; i++)
                    {
                        tmp=(double)(i-vect2.A.x)*a+vect2.A.y;
                        int l0=int(tmp)-THK[IDG][IDO][k1][0], l1=int(tmp)+THK[IDG][IDO][k1][0];
                        if(l0>0&&l0<smy)
                        {
                            nCount=(l0*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=tmp-double(int(tmp))+SCO[IDG][IDO][k1][0].a)>1.0) fres=1;
                                lVal=Tint({SCO[IDG][IDO][k1][0].b, SCO[IDG][IDO][k1][0].g, SCO[IDG][IDO][k1][0].r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }

                        if(l1>0&&l1<smy)
                        {
                            nCount=(l1*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=tmp-double(int(tmp))+SCO[IDG][IDO][k1][0].a)>1.0) fres=1;
                                lVal=TintInverse({SCO[IDG][IDO][k1][0].b, SCO[IDG][IDO][k1][0].g, SCO[IDG][IDO][k1][0].r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                        if(l0<0) l0=0;
                        if(l1<0) l1=0;
                        if(l0>=smy) l0=smy-1;
                        if(l1>=smy) l1=smy-1;
                        for(int j=l0+1; j<l1; j++)
                        {
                            nCount=(j*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                lVal=Tint({SCO[IDG][IDO][k1][0].b,SCO[IDG][IDO][k1][0].g, SCO[IDG][IDO][k1][0].r},
                                {b,g,r}, SCO[IDG][IDO][k1][0].a);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                    }
                }

            }
        }
}

void csSURFACE::csJLines(int IDO, int& r, int& g, int& b, double& tmp, double& a, long& lVal, long& dVal, long& nCount, char* buf, char* DEPTH)
{
    int k;
    double fres;
    if(SPO.isObjectVisible(IDG, IDO))
        for(int k1=0; k1 <= SPO.LEP(IDG, IDO); k1++)
        {
            for(k=0; k < SPO.LDP(IDG, IDO, k1); k++)
            {
                //std::cout<<k<<" ";
                vect2= {SPO[IDG][IDO][k1][k], SPO[IDG][IDO][k1][k+1]};
                csf_getMinMax(vect2.A,vect2.B,pt0, pt);


                double dx=vect2.A.x-vect2.B.x, dy=vect2.A.y-vect2.B.y;
                if(dx==0)
                {
                    dx=0.00001;

                }

                a=dy/dx;
                if(fabs(a)>1.0)
                {
                    if(pt0.y<0) pt0.y=0;
                    else if(pt0.y>smy) pt0.y=smy;
                    if(pt.y<0) pt.y=0;
                    else if(pt.y>smy) pt.y=smy;
                    for(int j=pt0.y; j<pt.y; j++)
                    {
                        tmp=(double)(j-vect2.A.y)*dx/dy+vect2.A.x;
                        int l0=int(tmp)-THK[IDG][IDO][k1][k], l1=int(tmp)+THK[IDG][IDO][k1][k];
                        if(l0>0&&l0<smx)
                        {
                            nCount=(j*smx+l0)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=tmp-double(int(tmp))+SCO[IDG][IDO][k1][k].a)>1.0) fres=1;
                                lVal=Tint({SCO[IDG][IDO][k1][k].b,SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }

                        if(l1>0&&l1<smx)
                        {
                            nCount=(j*smx+l1)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=tmp-double(int(tmp))+SCO[IDG][IDO][k1][k].a)>1.0) fres=1;
                                lVal=TintInverse({SCO[IDG][IDO][k1][k].b, SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                        if(l0<0) l0=0;
                        if(l1<0) l1=0;
                        if(l0>=smx) l0=smx-1;
                        if(l1>=smx) l1=smx-1;
                        for(int i=l0+1; i<l1; i++)
                        {
                            nCount=(j*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                lVal=Tint({SCO[IDG][IDO][k1][k].b,SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r},
                                {b,g,r}, SCO[IDG][IDO][k1][k].a);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                    }
                }
                else
                {
                    if(pt0.x<0) pt0.x=0;
                    else if(pt0.x>smx) pt0.x=smx;
                    if(pt.x<0) pt.x=0;
                    else if(pt.x>smx) pt.x=smx;
                    for(int i=pt0.x; i<pt.x; i++)
                    {
                        tmp=(double)(i-vect2.A.x)*dy/dx+vect2.A.y;
                        int l0=int(tmp)-THK[IDG][IDO][k1][k], l1=int(tmp)+THK[IDG][IDO][k1][k];
                        if(l0>0&&l0<smy)
                        {
                            nCount=(l0*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=tmp-double(int(tmp))+SCO[IDG][IDO][k1][k].a)>1.0) fres=1;
                                lVal=Tint({SCO[IDG][IDO][k1][k].b, SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }

                        if(l1>0&&l1<smy)
                        {
                            nCount=(l1*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=tmp-double(int(tmp))+SCO[IDG][IDO][k1][k].a)>1.0) fres=1;
                                lVal=TintInverse({SCO[IDG][IDO][k1][k].b, SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                        if(l0<0) l0=0;
                        if(l1<0) l1=0;
                        if(l0>=smy) l0=smy-1;
                        if(l1>=smy) l1=smy-1;
                        for(int j=l0+1; j<l1; j++)
                        {
                            nCount=(j*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                lVal=Tint({SCO[IDG][IDO][k1][k].b,SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r},
                                {b,g,r}, SCO[IDG][IDO][k1][k].a);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                    }
                }

            }
        }
}


void csSURFACE::csPLine(int IDO, int& r, int& g, int& b, double& tmp, double& a, long& lVal, long& dVal, long& nCount, char* buf, char* DEPTH)
{
    int k;
    if(SPO.isObjectVisible(IDG, IDO))
        for(int k1=0; k1 <= SPO.LEP(IDG, IDO); k1++)
        {
            for(k=0; k < SPO.LDP(IDG, IDO, k1); k++)
            {
                //std::cout<<k<<" ";
                vect2= {SPO[IDG][IDO][k1][k], SPO[IDG][IDO][k1][k+1]};
                csf_getMinMax(vect2.A,vect2.B,pt0, pt);


                double dx=vect2.A.x-vect2.B.x, dy=vect2.A.y-vect2.B.y;
                if(dx==0)
                {
                    dx+=1;

                }

                a=dy/dx;
                if(fabs(a)>1.0)
                {
                    if(pt0.y<0) pt0.y=0;
                    else if(pt0.y>smy) pt0.y=smy;
                    if(pt.y<0) pt.y=0;
                    else if(pt.y>smy) pt.y=smy;
                    for(int j=pt0.y; j<pt.y; j++)
                    {
                        tmp=(double)(j-vect2.A.y)/a+vect2.A.x;
                        tmp=tmp+THK[IDG][IDO][k1][k]*cos(atan(a));
                        int l0=int(tmp)-THK[IDG][IDO][k1][k], l1=int(tmp)+THK[IDG][IDO][k1][k];
                        if(l0>0&&l0<smx)
                        {
                            nCount=(j*smx+l0)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                lVal=Tint({SCO[IDG][IDO][k1][k].b,SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r}, {b,g,r}, tmp-double(int(tmp)));
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }

                        if(l1>0&&l1<smx)
                        {
                            nCount=(j*smx+l1)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                lVal=TintInverse({SCO[IDG][IDO][k1][k].b, SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r}, {b,g,r}, tmp-double(int(tmp)));
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                        if(l0<0) l0=0;
                        if(l1<0) l1=0;
                        if(l0>=smx) l0=smx-1;
                        if(l1>=smx) l1=smx-1;
                        for(int i=l0+1; i<l1; i++)
                        {
                            nCount=(j*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                lVal=RGB(SCO[IDG][IDO][k1][k].b, SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                    }
                }
                else
                {
                    if(pt0.x<0) pt0.x=0;
                    else if(pt0.x>smx) pt0.x=smx;
                    if(pt.x<0) pt.x=0;
                    else if(pt.x>smx) pt.x=smx;
                    for(int i=pt0.x; i<pt.x; i++)
                    {
                        tmp=(double)(i-vect2.A.x)*a+vect2.A.y;
                        tmp=tmp+THK[IDG][IDO][k1][k]*cos(atan(a));
                        int l0=int(tmp)-THK[IDG][IDO][k1][k], l1=int(tmp)+THK[IDG][IDO][k1][k];
                        if(l0>0&&l0<smy)
                        {
                            nCount=(l0*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                lVal=Tint({SCO[IDG][IDO][k1][k].b, SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r}, {b,g,r}, tmp-double(int(tmp)));
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }

                        if(l1>0&&l1<smy)
                        {
                            nCount=(l1*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                lVal=TintInverse({SCO[IDG][IDO][k1][k].b, SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r}, {b,g,r}, tmp-double(int(tmp)));
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                        if(l0<0) l0=0;
                        if(l1<0) l1=0;
                        if(l0>=smy) l0=smy-1;
                        if(l1>=smy) l1=smy-1;
                        for(int j=l0+1; j<l1; j++)
                        {
                            nCount=(j*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<VALUE[IDG][IDO])
                            {
                                lVal=RGB(SCO[IDG][IDO][k1][k].b, SCO[IDG][IDO][k1][k].g, SCO[IDG][IDO][k1][k].r);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                    }
                }

            }
        }
}

void csSURFACE::csPolygLine(int IDO, int& r, int& g, int& b, double& tmp, double& a, long& lVal, long& dVal, long& nCount, char* buf, char* DEPTH)
{
    int k;
    double fres, l1;
    if(SPO.isObjectVisible(IDG, IDO))
        for(int k1=0; k1 <= SPO.LEP(IDG, IDO); k1++)
        {
            for(k=0; k < SPO.LDP(IDG, IDO, k1); k++)
            {
                //std::cout<<k<<" ";
                vect2= {SPO[IDG][IDO][k1][k], SPO[IDG][IDO][k1][k+1]};
                csf_getMinMax(vect2.A,vect2.B,pt0, pt);


                double dx=vect2.A.x-vect2.B.x, dy=vect2.A.y-vect2.B.y;
                pt0.y-=THK[IDG][IDO][k1][0]/2;
                pt0.x-=THK[IDG][IDO][k1][0]/2;
                if(fabs(dy)>fabs(dx))
                {
                    if(pt0.y<0) pt0.y=0;
                    else if(pt0.y>smy) pt0.y=smy;
                    if(pt.y<0) pt.y=0;
                    else if(pt.y>smy) pt.y=smy;
                    for(int j=pt0.y; j<pt.y; j++)
                    {
                        tmp=(double)(j-vect2.A.y)*dx/dy+vect2.A.x;
                        int l0=int(tmp)-THK[IDG][IDO][k1][0], l1=int(tmp)+THK[IDG][IDO][k1][0];
                        if(l0>0&&l0<smx)
                        {
                            nCount=(j*smx+l0)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<=VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=tmp-double(int(tmp))+SCO[IDG][IDO][k1][0].a)>1.0) fres=1;
                                lVal=Tint({SCO[IDG][IDO][k1][0].b,SCO[IDG][IDO][k1][0].g, SCO[IDG][IDO][k1][0].r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }

                        if(l1>0&&l1<smx)
                        {
                            nCount=(j*smx+l1)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<=VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=tmp-double(int(tmp))+SCO[IDG][IDO][k1][0].a)>1.0) fres=1;
                                lVal=TintInverse({SCO[IDG][IDO][k1][0].b, SCO[IDG][IDO][k1][0].g, SCO[IDG][IDO][k1][0].r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                        if(l0<0) l0=0;
                        if(l1<0) l1=0;
                        if(l0>=smx) l0=smx-1;
                        if(l1>=smx) l1=smx-1;
                        for(int i=l0+1; i<l1; i++)
                        {
                            nCount=(j*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<=VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                lVal=Tint({SCO[IDG][IDO][k1][0].b,SCO[IDG][IDO][k1][0].g, SCO[IDG][IDO][k1][0].r},
                                {b,g,r}, SCO[IDG][IDO][k1][k].a);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                    }
                }
                else
                {
                    if(pt0.x<0) pt0.x=0;
                    else if(pt0.x>smx) pt0.x=smx;
                    if(pt.x<0) pt.x=0;
                    else if(pt.x>smx) pt.x=smx;
                    for(int i=pt0.x; i<pt.x; i++)
                    {
                        tmp=(double)(i-vect2.A.x)*dy/dx+vect2.A.y;
                        int l0=int(tmp)-THK[IDG][IDO][k1][0], l1=int(tmp)+THK[IDG][IDO][k1][0];
                        if(l0>0&&l0<smy)
                        {
                            nCount=(l0*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<=VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=tmp-double(int(tmp))+SCO[IDG][IDO][k1][0].a)>1.0) fres=1;
                                lVal=Tint({SCO[IDG][IDO][k1][0].b, SCO[IDG][IDO][k1][0].g, SCO[IDG][IDO][k1][0].r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }

                        if(l1>0&&l1<smy)
                        {
                            nCount=(l1*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<=VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=tmp-double(int(tmp))+SCO[IDG][IDO][k1][0].a)>1.0) fres=1;
                                lVal=TintInverse({SCO[IDG][IDO][k1][0].b, SCO[IDG][IDO][k1][0].g, SCO[IDG][IDO][k1][0].r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                        if(l0<0) l0=0;
                        if(l1<0) l1=0;
                        if(l0>=smy) l0=smy-1;
                        if(l1>=smy) l1=smy-1;
                        for(int j=l0+1; j<l1; j++)
                        {
                            nCount=(j*smx+i)*4;
                            memcpy(&dVal, &DEPTH[nCount], 4);
                            if(dVal<=VALUE[IDG][IDO])
                            {
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                lVal=Tint({SCO[IDG][IDO][k1][0].b,SCO[IDG][IDO][k1][0].g, SCO[IDG][IDO][k1][0].r},
                                {b,g,r}, SCO[IDG][IDO][k1][0].a);
                                memcpy(&buf[nCount], &lVal, 4);
                                memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                            }
                        }
                    }
                }

            }
        }
}


void csSURFACE::csPolygon(int IDO, int& r, int& g, int& b, double& tmp, long& lVal, long& dVal, long& nCount, char* buf, char* DEPTH)
{
    double dx, dy;
    int *xstab, transf;
    if(SPO.isObjectVisible(IDG, IDO))
        for(int k0=0; k0 <= SPO.LEP(IDG,IDO); k0++)
        {
            csVECT2F vect2[SPO.LDP(IDG, IDO, k0)];
            double a[SPO.LDP(IDG, IDO, k0)];
            int xstab[SPO.LDP(IDG, IDO, k0)];
            int i=0;
            pt0.y=SPO[IDG][IDO][k0][0].y;
            pt.y=SPO[IDG][IDO][k0][0].y;
            for(int p=1; p <= SPO.LDP(IDG, IDO, k0); p++)
            {
                //std::cout<<SPO[IDG][IDO][k0][p].z<<"\n";
                vect2[i]= {SPO[IDG][IDO][k0][p], SPO[IDG][IDO][k0][p-1]};

                if(SPO[IDG][IDO][k0][p].y<pt0.y)
                {
                    pt0.y=SPO[IDG][IDO][k0][p].y;
                }
                if(SPO[IDG][IDO][k0][p].y>pt.y)
                {
                    pt.y=SPO[IDG][IDO][k0][p].y;
                }
                dx=vect2[i].A.x-vect2[i].B.x, dy=vect2[i].A.y-vect2[i].B.y;
                if(dx==0)
                {
                    if(dy>0) a[i]=MAXLONG;
                    else a[i]=-MAXLONG;
                }
                else a[i]=dy/dx;
                i++;
            }
            if(pt0.y<0) pt0.y=0;
            else if(pt0.y>=smy) pt0.y=smy-1;
            if(pt.y<0) pt.y=0;
            else if(pt.y>=smy) pt.y=smy-1;
            double xsol;
            for(int j=pt0.y; j<pt.y; j++)
            {
                int al=0;
                for(int k=0; k<i; k++)
                {
                    xsol=(j-vect2[k].A.y)/a[k]+vect2[k].A.x;
                    if((xsol<=vect2[k].A.x && xsol>=vect2[k].B.x && vect2[k].A.x>=vect2[k].B.x)||
                            (xsol>=vect2[k].A.x && xsol<=vect2[k].B.x && vect2[k].A.x<=vect2[k].B.x))
                    {
                        xstab[al]=(int)xsol;
                        al++;
                    }
                }

                if(al%2==1) al-=1;
                for(int l=0; l<al; l++)
                    for(int k=0; k<al-1; k++)
                    {
                        if(xstab[k]>xstab[k+1])
                        {
                            transf=xstab[k];
                            xstab[k]=xstab[k+1];
                            xstab[k+1]=transf;
                        }
                    }
                for(int V=0; V<al; V+=2)
                {
                    for(int U=xstab[V]; U<xstab[V+1]; U++)
                    {
                        nCount=(j*smx+U)*4;
                        memcpy(&dVal, &DEPTH[nCount], 4);
                        if(dVal<VALUE[IDG][IDO])
                        {
                            memcpy(&lVal, &buf[nCount], 4);
                            b = GetRValue(lVal);
                            g = GetGValue(lVal);
                            r = GetBValue(lVal);
                            lVal=Tint({SCO[IDG][IDO][k0][0].b, SCO[IDG][IDO][k0][0].g, SCO[IDG][IDO][k0][0].r},
                            {b,g,r}, SCO[IDG][IDO][k0][0].a);
                            memcpy(&buf[nCount], &lVal, 4);
                            memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                        }
                    }
                }


            }
        }
}


