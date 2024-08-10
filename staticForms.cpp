#include "csSURFACE.h"

void csf_staticPolyline(csPOINT2F** pts, int** thk, csRGBA**cols, int length1, int length2, HDC dc, HBITMAP hbm, int szx, int szy)
{
    int k;
    long dt=0;
    double fres;
    csVECT2F vect2;
    csPOINT2F pt, pt0;
    int IDO, r, g, b, bRes;
    double tmp, a;
    long lVal, nCount;
    char* buf;
    BITMAPINFO gbi;
    gbi.bmiHeader.biSize = sizeof(gbi.bmiHeader);
    gbi.bmiHeader.biWidth = szx;
    gbi.bmiHeader.biHeight = -szy;
    gbi.bmiHeader.biPlanes = 1;
    gbi.bmiHeader.biBitCount = 32;
    gbi.bmiHeader.biCompression = BI_RGB;
    gbi.bmiHeader.biSizeImage = (szx) * 4 * (szy);
    gbi.bmiHeader.biClrUsed = 0;
    gbi.bmiHeader.biClrImportant = 0;
    buf = (char *) malloc((szx) * 4 * (szy));
    bRes = GetDIBits(dc, hbm, 0, szy, buf, &gbi, DIB_RGB_COLORS);
    for(int k1=0; k1 < length1; k1++)
    {
        for(k=0; k < length2-1; k++)
        {
            //std::cout<<k<<" ";
            vect2= {pts[k1][k], pts[k1][k+1]};
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
                else if(pt0.y>szy) pt0.y=szy;
                if(pt.y<0) pt.y=0;
                else if(pt.y>szy) pt.y=szy;
                for(int j=pt0.y; j<pt.y; j++)
                {
                    tmp=(double)(j-vect2.A.y)/a+vect2.A.x;
                    int l0=int(tmp)-thk[k1][0], l1=int(tmp)+thk[k1][0];
                    if(l0>0&&l0<szx)
                    {
                        nCount=(j*szx+l0)*4;
                        memcpy(&lVal, &buf[nCount], 4);
                        b = GetRValue(lVal);
                        g = GetGValue(lVal);
                        r = GetBValue(lVal);
                        if((fres=tmp-double(int(tmp))+cols[k1][0].a)>1.0) fres=1;
                        lVal=Tint({cols[k1][0].b,cols[k1][0].g, cols[k1][0].r}, {b,g,r}, fres);
                        memcpy(&buf[nCount], &lVal, 4);
                    }

                    if(l1>0&&l1<szx)
                    {
                        nCount=(j*szx+l1)*4;
                        memcpy(&lVal, &buf[nCount], 4);
                        b = GetRValue(lVal);
                        g = GetGValue(lVal);
                        r = GetBValue(lVal);
                        if((fres=tmp-double(int(tmp))+cols[k1][0].a)>1.0) fres=1;
                        lVal=TintInverse({cols[k1][0].b, cols[k1][0].g, cols[k1][0].r}, {b,g,r}, fres);
                        memcpy(&buf[nCount], &lVal, 4);
                    }
                    if(l0<0) l0=0;
                    if(l1<0) l1=0;
                    if(l0>=szx) l0=szx-1;
                    if(l1>=szx) l1=szx-1;
                    for(int i=l0+1; i<l1; i++)
                    {
                        nCount=(j*szx+i)*4;
                        memcpy(&lVal, &buf[nCount], 4);
                        b = GetRValue(lVal);
                        g = GetGValue(lVal);
                        r = GetBValue(lVal);
                        lVal=Tint({cols[k1][0].b,cols[k1][0].g, cols[k1][0].r},
                        {b,g,r}, cols[k1][0].a);
                        memcpy(&buf[nCount], &lVal, 4);
                    }
                }
            }
            else
            {
                if(pt0.x<0) pt0.x=0;
                else if(pt0.x>szx) pt0.x=szx;
                if(pt.x<0) pt.x=0;
                else if(pt.x>szx) pt.x=szx;
                for(int i=pt0.x; i<pt.x; i++)
                {
                    tmp=(double)(i-vect2.A.x)*a+vect2.A.y;
                    int l0=int(tmp)-thk[k1][0], l1=int(tmp)+thk[k1][0];
                    if(l0>0&&l0<szy)
                    {
                        nCount=(l0*szx+i)*4;
                        memcpy(&lVal, &buf[nCount], 4);
                        b = GetRValue(lVal);
                        g = GetGValue(lVal);
                        r = GetBValue(lVal);
                        if((fres=tmp-double(int(tmp))+cols[k1][0].a)>1.0) fres=1;
                        lVal=Tint({cols[k1][0].b, cols[k1][0].g, cols[k1][0].r}, {b,g,r}, fres);
                        memcpy(&buf[nCount], &lVal, 4);
                    }

                    if(l1>0&&l1<szy)
                    {
                        nCount=(l1*szx+i)*4;
                        memcpy(&lVal, &buf[nCount], 4);
                        b = GetRValue(lVal);
                        g = GetGValue(lVal);
                        r = GetBValue(lVal);
                        if((fres=tmp-double(int(tmp))+cols[k1][0].a)>1.0) fres=1;
                        lVal=TintInverse({cols[k1][0].b, cols[k1][0].g, cols[k1][0].r}, {b,g,r}, fres);
                        memcpy(&buf[nCount], &lVal, 4);
                    }
                    if(l0<0) l0=0;
                    if(l1<0) l1=0;
                    if(l0>=szy) l0=szy-1;
                    if(l1>=szy) l1=szy-1;
                    for(int j=l0+1; j<l1; j++)
                    {
                        nCount=(j*szx+i)*4;
                        memcpy(&lVal, &buf[nCount], 4);
                        b = GetRValue(lVal);
                        g = GetGValue(lVal);
                        r = GetBValue(lVal);
                        lVal=Tint({cols[k1][0].b,cols[k1][0].g, cols[k1][0].r},
                        {b,g,r}, cols[k1][0].a);
                        memcpy(&buf[nCount], &lVal, 4);
                    }
                }
            }

        }
    }
    SetDIBits(dc, hbm, 0, bRes, buf,  &gbi, DIB_RGB_COLORS);
}


void csf_staticPolygon(csPOINT2F** pts, csRGBA**cols, int length1, int length2, HDC dc, HBITMAP hbm, int szx, int szy)
{
    int k;
    long dt=0;
    double fres;
    csVECT2F vect2;
    csPOINT2F pt, pt0;
    int IDO, r, g, b, bRes;
    double tmp, a;
    long lVal, nCount;
    char* buf;
    BITMAPINFO gbi;
    gbi.bmiHeader.biSize = sizeof(gbi.bmiHeader);
    gbi.bmiHeader.biWidth = szx;
    gbi.bmiHeader.biHeight = -szy;
    gbi.bmiHeader.biPlanes = 1;
    gbi.bmiHeader.biBitCount = 32;
    gbi.bmiHeader.biCompression = BI_RGB;
    gbi.bmiHeader.biSizeImage = (szx) * 4 * (szy);
    gbi.bmiHeader.biClrUsed = 0;
    gbi.bmiHeader.biClrImportant = 0;
    buf = (char *) malloc((szx) * 4 * (szy));
    bRes = GetDIBits(dc, hbm, 0, szy, buf, &gbi, DIB_RGB_COLORS);
    double dx, dy;
    int *xstab, transf;

    for(int k0=0; k0 < length1; k0++)
    {
        csVECT2F vect2[length2-1];
        double a[length2-1];
        int xstab[length2-1];
        int i=0;
        pt0.y=pts[k0][0].y;
        pt.y=pts[k0][0].y;
        for(int p=1; p < length2; p++)
        {
            //std::cout<<pts[k0][p].z<<"\n";
            vect2[i]= {pts[k0][p], pts[k0][p-1]};

            if(pts[k0][p].y<pt0.y)
            {
                pt0.y=pts[k0][p].y;
            }
            if(pts[k0][p].y>pt.y)
            {
                pt.y=pts[k0][p].y;
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
        else if(pt0.y>=szy) pt0.y=szy-1;
        if(pt.y<0) pt.y=0;
        else if(pt.y>=szy) pt.y=szy-1;
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
                    nCount=(j*szx+U)*4;
                    memcpy(&lVal, &buf[nCount], 4);
                    b = GetRValue(lVal);
                    g = GetGValue(lVal);
                    r = GetBValue(lVal);
                    lVal=Tint({cols[k0][0].b, cols[k0][0].g, cols[k0][0].r},
                    {b,g,r}, cols[k0][0].a);
                    memcpy(&buf[nCount], &lVal, 4);
                }
            }


        }
    }
    SetDIBits(dc, hbm, 0, bRes, buf,  &gbi, DIB_RGB_COLORS);
}
