#include "csSURFACE.h"
csCIRCLE_PARAMS csSURFACE::cparFromPoint2f(csPOINT2F& pdat, csPOINT2F& pcenter, csRGBA& col)
{
    csCIRCLE_PARAMS c= {pcenter, pdat.x, pdat.y, col, pdat.depth, pdat.lightF};
    return c;
}
csELLIPSE_PARAMS csSURFACE::eparFromPoint2f(csPOINT2F& pdat, csPOINT2F& pdat0, csPOINT2F& pcenter, csRGBA& col)
{
    csELLIPSE_PARAMS c= {pcenter, pdat.x, pdat.y, pdat.idObj, col, pdat.depth, pdat.lightF,
                         pdat0.x, pdat0.y, pdat0.depth, pdat0.lightF, pdat0.idObj
                        };
    return c;
}

void csSURFACE::csFCircle(int IDO, int& r, int& g, int& b, long& lVal, long& dVal, long& nCount, char* buf, char* DEPTH)
{
    int k, dx, dy, intRay;
    double calcRay, fl, fres;
    csCIRCLE_PARAMS c=cparFromPoint2f(SPO[IDG][IDO][0][1], SPO[IDG][IDO][0][0], SCO[IDG][IDO][0][0]);
    if(SPO.isObjectVisible(IDG, IDO))
        for(int k1=0; k1 <= SPO.LEP(IDG,IDO); k1++)
        {
            for(k=0; k <= SPO.LDP(IDG, IDO, k1); k++)
            {
                for(int j=-c.outRay; j<=c.outRay; j++)
                    for(int i=-c.outRay; i<=c.outRay; i++)
                    {
                        calcRay=sqrt(i*i+j*j);
                        intRay=(int)calcRay;
                        if(intRay<(int)c.outRay&&(int)c.inRay<intRay)
                        {

                            dx=(i+c.center.x);
                            dy=(j+c.center.y);
                            if(dx<smx && dy<smy && dx>0 && dy>0)
                            {
                                nCount=(dy*smx+dx)*4;
                                memcpy(&dVal, &DEPTH[nCount], 4);
                                if(dVal<VALUE[IDG][IDO])
                                {
                                    memcpy(&lVal, &buf[nCount], 4);
                                    b = GetRValue(lVal);
                                    g = GetGValue(lVal);
                                    r = GetBValue(lVal);
                                    lVal=Tint({c.fillColor.b,c.fillColor.g,c.fillColor.r}, {b,g,r}, c.fillColor.a);
                                    memcpy(&buf[nCount], &lVal, 4);
                                    memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                                }
                            }
                        }
                        else if(intRay==(int)c.outRay)
                        {
                            dx=(i+c.center.x);
                            dy=(j+c.center.y);
                            fl=calcRay-intRay;
                            if(dx<smx && dy<smy && dx>0 && dy>0)
                            {
                                nCount=(dy*smx+dx)*4;
                                memcpy(&dVal, &DEPTH[nCount], 4);
                                if(dVal<VALUE[IDG][IDO])
                                {
                                    memcpy(&lVal, &buf[nCount], 4);
                                    b = GetRValue(lVal);
                                    g = GetGValue(lVal);
                                    r = GetBValue(lVal);
                                    if((fres=fl+c.fillColor.a)>1.0) fres=1;
                                    lVal=Tint({c.fillColor.b,c.fillColor.g,c.fillColor.r}, {b,g,r}, fres);
                                    memcpy(&buf[nCount], &lVal, 4);
                                    memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                                }
                            }
                        }
                        else if(intRay==(int)c.inRay)
                        {
                            dx=(i+c.center.x);
                            dy=(j+c.center.y);
                            fl=calcRay-intRay;
                            if(dx<smx && dy<smy && dx>0 && dy>0)
                            {
                                nCount=(dy*smx+dx)*4;
                                memcpy(&dVal, &DEPTH[nCount], 4);
                                if(dVal<VALUE[IDG][IDO])
                                {
                                    memcpy(&lVal, &buf[nCount], 4);
                                    b = GetRValue(lVal);
                                    g = GetGValue(lVal);
                                    r = GetBValue(lVal);
                                    if((fres=1-fl+c.fillColor.a)>1.0) fres=1;
                                    lVal=Tint({c.fillColor.b,c.fillColor.g,c.fillColor.r}, {b,g,r}, fres);
                                    memcpy(&buf[nCount], &lVal, 4);
                                    memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                                }
                            }
                        }
                    }
            }
        }
}

void csSURFACE::csFEllipse(int IDO, int& r, int& g, int& b, long& lVal, long& dVal, long& nCount, char* buf, char* DEPTH)
{
    int k, dx, dy, intUnit, intUnit0;
    double fl, fres, unit, unit0;
    csELLIPSE_PARAMS c=eparFromPoint2f(SPO[IDG][IDO][0][1], SPO[IDG][IDO][0][2], SPO[IDG][IDO][0][0], SCO[IDG][IDO][0][0]);
    if(SPO.isObjectVisible(IDG, IDO))
        for(int k1=0; k1 <= SPO.LEP(IDG,IDO); k1++)
        {
            for(k=0; k <= SPO.LDP(IDG, IDO, k1); k++)
            {
                for(int j=-c.yRay-c.marging; j<=c.yRay+c.marging; j++)
                    for(int i=-c.xRay-c.marging; i<=c.xRay+c.marging; i++)
                    {
                        unit=square(i)/square(c.xRay)+square(j)/square(c.yRay);
                        unit0=square(i)/square(c.xRay-c.thickness)+square(j)/square(c.yRay-c.thickness);
                        intUnit=(int)unit;
                        intUnit0=(int)unit0;
                        if(unit<1.0&&unit0>1.0)
                        {

                            dx=(i+c.center.x);
                            dy=(j+c.center.y);
                            if(dx<smx && dy<smy && dx>0 && dy>0)
                            {
                                nCount=(dy*smx+dx)*4;
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                lVal=Tint({c.fillColor.b,c.fillColor.g,c.fillColor.r}, {b,g,r}, c.fillColor.a);
                                memcpy(&buf[nCount], &lVal, 4);
                            }
                        }
                        else if(unit>=1.0&&unit<c.outSill)
                        {
                            dx=(i+c.center.x);
                            dy=(j+c.center.y);
                            fl=unit-intUnit;
                            if(dx<smx && dy<smy && dx>0 && dy>0)
                            {
                                nCount=(dy*smx+dx)*4;
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=fl*c.outDegradedFact+c.fillColor.a)>1.0) fres=1;
                                lVal=Tint({c.fillColor.b,c.fillColor.g,c.fillColor.r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                            }
                        }
                        else if(unit0>=c.inSill&&unit0<=1.0)
                        {
                            dx=(i+c.center.x);
                            dy=(j+c.center.y);
                            fl=unit0-intUnit0;
                            if(dx<smx && dy<smy && dx>0 && dy>0)
                            {
                                nCount=(dy*smx+dx)*4;
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=(1-fl)*c.inDegradedFact+c.fillColor.a)>1.0) fres=1;
                                lVal=Tint({c.fillColor.b,c.fillColor.g,c.fillColor.r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                            }
                        }
                    }
            }
        }
}

void csSURFACE::csFEllipseArc(int IDO, int& r, int& g, int& b, long& lVal, long& dVal, long& nCount, char* buf, char* DEPTH)
{
    int k, dx, dy, intUnit, intUnit0;
    double fl, fres, unit, unit0, ang;
    csELLIPSE_PARAMS c=eparFromPoint2f(SPO[IDG][IDO][0][1], SPO[IDG][IDO][0][2], SPO[IDG][IDO][0][0], SCO[IDG][IDO][0][0]);
    int beg0=-c.yRay-c.marging, end0=c.yRay+c.marging;
    int beg1=-c.xRay-c.marging, end1=c.xRay+c.marging;
    int inxr=c.xRay-c.thickness, inyr=c.yRay-c.thickness;
    if(SPO.isObjectVisible(IDG, IDO))
        for(int k1=0; k1 <= SPO.LEP(IDG,IDO); k1++)
        {
            for(k=0; k <= SPO.LDP(IDG, IDO, k1); k++)
            {
                for(int j=beg0; j<=end0; j++)
                    for(int i=beg1; i<=end1; i++)
                    {
                        unit=square(i)/square(c.xRay)+square(j)/square(c.yRay);
                        unit0=square(i)/square(inxr)+square(j)/square(inyr);
                        intUnit=(int)unit;
                        intUnit0=(int)unit0;
                        if(unit<1.0&&unit0>1.0)
                        {

                            dx=(i+c.center.x);
                            dy=(j+c.center.y);
                            if(i==0)
                            {
                                if(-j<0) ang=-3.14159/2;
                                else ang=3.14159/2;
                            }
                            else ang=atan(double(-j)/i);
                            if(i<0) ang+=3.14159;
                            else if(-j<0&&i>=0) ang+=6.28318;
                            if(dx<smx && dy<smy && dx>0 && dy>0 && ang<c.greatAngle && ang>c.smallAngle)
                            {
                                nCount=(dy*smx+dx)*4;
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                lVal=Tint({c.fillColor.b,c.fillColor.g,c.fillColor.r}, {b,g,r}, c.fillColor.a);
                                memcpy(&buf[nCount], &lVal, 4);
                            }
                        }
                        else if(unit>=1.0&&unit<c.outSill)
                        {
                            dx=(i+c.center.x);
                            dy=(j+c.center.y);
                            fl=unit-intUnit;
                            if(i==0)
                            {
                                if(-j<0) ang=-3.14159/2;
                                else ang=3.14159/2;
                            }
                            else ang=atan(double(-j)/i);
                            if(i<0) ang+=3.14159;
                            else if(-j<0&&i>=0) ang+=6.28318;
                            if(dx<smx && dy<smy && dx>0 && dy>0 && ang<c.greatAngle && ang>c.smallAngle)
                            {
                                nCount=(dy*smx+dx)*4;
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=fl*c.outDegradedFact+c.fillColor.a)>1.0) fres=1;
                                lVal=Tint({c.fillColor.b,c.fillColor.g,c.fillColor.r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                            }
                        }
                        else if(unit0>=c.inSill&&unit0<=1.0)
                        {
                            dx=(i+c.center.x);
                            dy=(j+c.center.y);
                            fl=unit0-intUnit0;
                            if(i==0)
                            {
                                if(-j<0) ang=-3.14159/2;
                                else ang=3.14159/2;
                            }
                            else ang=atan(double(-j)/i);
                            if(i<0) ang+=3.14159;
                            else if(-j<0&&i>=0) ang+=6.28318;
                            if(dx<smx && dy<smy && dx>0 && dy>0 && ang<c.greatAngle && ang>c.smallAngle)
                            {
                                nCount=(dy*smx+dx)*4;
                                memcpy(&lVal, &buf[nCount], 4);
                                b = GetRValue(lVal);
                                g = GetGValue(lVal);
                                r = GetBValue(lVal);
                                if((fres=(1-fl)*c.inDegradedFact+c.fillColor.a)>1.0) fres=1;
                                lVal=Tint({c.fillColor.b,c.fillColor.g,c.fillColor.r}, {b,g,r}, fres);
                                memcpy(&buf[nCount], &lVal, 4);
                            }
                        }
                    }
            }
        }
}

void csSURFACE::csFArc(int IDO, int& r, int& g, int& b, long& lVal, long& dVal, long& nCount, char* buf, char* DEPTH)
{
    int k, dx, dy, intRay;
    double calcRay, fl, fres, ang;
    csCIRCLE_PARAMS c=cparFromPoint2f(SPO[IDG][IDO][0][1], SPO[IDG][IDO][0][0], SCO[IDG][IDO][0][0]);
    if(SPO.isObjectVisible(IDG, IDO))
        for(int k1=0; k1 <= SPO.LEP(IDG,IDO); k1++)
        {
            for(k=0; k <= SPO.LDP(IDG, IDO, k1); k++)
            {
                //std::cout<<k<<" ";
                for(int j=-c.outRay; j<=c.outRay; j++)
                    for(int i=-c.outRay; i<=c.outRay; i++)
                    {
                        calcRay=sqrt(i*i+j*j);
                        intRay=(int)calcRay;
                        if(intRay<c.outRay&&c.inRay<intRay)
                        {
                            dx=(i+c.center.x);
                            dy=(j+c.center.y);
                            if(i==0)
                            {
                                if(-j<0) ang=-3.14159/2;
                                else ang=3.14159/2;
                            }
                            else ang=atan(double(-j)/i);
                            if(i<0) ang+=3.14159;
                            else if(-j<0&&i>=0) ang+=6.28318;
                            if(dx<smx && dy<smy && dx>0 && dy>0 && ang<c.greatAngle && ang>c.smallAngle)
                            {
                                nCount=(dy*smx+dx)*4;
                                memcpy(&dVal, &DEPTH[nCount], 4);
                                if(dVal<VALUE[IDG][IDO])
                                {
                                    memcpy(&lVal, &buf[nCount], 4);
                                    b = GetRValue(lVal);
                                    g = GetGValue(lVal);
                                    r = GetBValue(lVal);
                                    lVal=Tint({c.fillColor.b,c.fillColor.g,c.fillColor.r}, {b,g,r}, c.fillColor.a);
                                    memcpy(&buf[nCount], &lVal, 4);
                                    memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                                }
                            }
                        }
                        else if(intRay==c.outRay)
                        {
                            dx=(i+c.center.x);
                            dy=(j+c.center.y);
                            fl=calcRay-intRay;
                            if(i==0)
                            {
                                if(-j<0) ang=-3.14159/2;
                                else ang=3.14159/2;
                            }
                            else ang=atan(double(-j)/i);
                            if(i<0) ang+=3.14159;
                            else if(-j<0&&i>=0) ang+=6.28318;
                            if(dx<smx && dy<smy && dx>0 && dy>0 && ang<c.greatAngle && ang>c.smallAngle)
                            {
                                nCount=(dy*smx+dx)*4;
                                memcpy(&dVal, &DEPTH[nCount], 4);
                                if(dVal<VALUE[IDG][IDO])
                                {
                                    memcpy(&lVal, &buf[nCount], 4);
                                    b = GetRValue(lVal);
                                    g = GetGValue(lVal);
                                    r = GetBValue(lVal);
                                    if((fres=fl+c.fillColor.a)>1.0) fres=1;
                                    lVal=Tint({c.fillColor.b,c.fillColor.g,c.fillColor.r}, {b,g,r}, fres);
                                    memcpy(&buf[nCount], &lVal, 4);
                                    memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                                }
                            }
                        }
                        else if(intRay==c.inRay)
                        {
                            dx=(i+c.center.x);
                            dy=(j+c.center.y);
                            fl=calcRay-intRay;
                            if(i==0)
                            {
                                if(-j<0) ang=-3.14159/2;
                                else ang=3.14159/2;
                            }
                            else ang=atan(double(-j)/i);
                            if(i<0) ang+=3.14159;
                            else if(-j<0&&i>=0) ang+=6.28318;
                            if(dx<smx && dy<smy && dx>0 && dy>0 && ang<c.greatAngle && ang>c.smallAngle)
                            {
                                nCount=(dy*smx+dx)*4;
                                memcpy(&dVal, &DEPTH[nCount], 4);
                                if(dVal<VALUE[IDG][IDO])
                                {
                                    memcpy(&lVal, &buf[nCount], 4);
                                    b = GetRValue(lVal);
                                    g = GetGValue(lVal);
                                    r = GetBValue(lVal);
                                    if((fres=1-fl+c.fillColor.a)>1.0) fres=1;
                                    lVal=Tint({c.fillColor.b,c.fillColor.g,c.fillColor.r}, {b,g,r}, fres);
                                    memcpy(&buf[nCount], &lVal, 4);
                                    memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                                }
                            }
                        }
                    }
            }
        }
}

int csSURFACE::getIndex(int idobj)
{
    int id=0;
    for(int i=0; i<CHAROBJINDEX[IDG].size(); i++)
    {
        if(CHAROBJINDEX[IDG][i]==idobj)
        {
            id=i;
            break;
        }
    }
    return id;
}


void csSURFACE::csText(int IDO, int& r, int& g, int& b, long& lVal, long& dVal, long& nCount, char* buf, char* DEPTH)
{
    if(SPO.isObjectVisible(IDG, IDO))
    {
        HDC dc=CreateCompatibleDC(0);
        HBITMAP bm=CreateCompatibleBitmap(hdc, smx, smy);
        SelectBitmap(dc, bm);
        SetBkMode(dc, TRANSPARENT);
        char *buf2=(char*)malloc(smx*smy*4);
        int bres=GetDIBits(dc, bm, 0, smy, buf2, &gbi, DIB_RGB_COLORS);
        SetDIBits(dc, bm, 0, bres, buf,  &gbi2, DIB_RGB_COLORS);
        int id=getIndex(IDO);
        csPOINT2F p=SPO[IDG][IDO][0][0];
        for(int k1=0; k1 <= CHAROBJ.LEP(IDG,id); k1++)
        {
            for(int k=0; k <= CHAROBJ.LDP(IDG,id, k1); k++)
            {
                csRGB col=CHAROBJCOL[IDG][id][k1][k];
                csRECT sz=CHAROBJPOS[IDG][id][k1][k];

                SetTextColor(dc, RGB(col.r,col.g,col.b));
                SelectFont(dc, CHAROBJFONT[IDG][id][k1][k]);

                TextOut(dc, p.x+sz.l, p.y+sz.t, (LPCSTR)CHAROBJ[IDG][id][k1][k],
                        strlen(CHAROBJ[IDG][id][k1][k]));
            }
        }
        GetDIBits(dc, bm, 0, smy, buf2, &gbi, DIB_RGB_COLORS);

        for(int j=p.y; j<=p.lightF+p.y; j++)
            for(int i=p.x; i<=p.depth+p.x; i++)
            {
                nCount=(j*smx+i)*4;
                memcpy(&dVal, &DEPTH[nCount], 4);
                if(dVal<VALUE[IDG][IDO])
                {
                    memcpy(&lVal, &buf2[nCount], 4);
                    memcpy(&buf[nCount], &lVal, 4);
                    memcpy(&DEPTH[nCount], &(VALUE[IDG][IDO]), 4);
                }
            }
        free(buf2);
        DeleteDC(dc);
        DeleteBitmap(bm);
    }
}

