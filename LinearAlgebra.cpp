/*
 * LinearAlgebra.cpp
 *
 *  Created on: 14 mai 2023
 *      Author: azphi
 */

#include <LinearAlgebra.h>

extern int TAB_PRINT_ID;


void discreteInterpExample()
{
	size_t n = 600, wordLen=10, n_out=0, n_coefs_cells=0, cell_length_interp=0, n_interp = 0, dx = 4;
	int64_t min = 1, max = 10, exponent = 0;
	double*x_out;
	double*y = getRandomDoubleArray1D(n, min, max, exponent), *y_out;
	printArray1D(y, n, "y :", wordLen=20);
	int cell_length, n_overlap, polynom_degree, n_cell_interest=0;

	double** coefs = descretePolynomialInterpolationCoefs1D(y, n, cell_length=3,
													n_overlap=2, polynom_degree=7,
													y_out, n_out, n_coefs_cells);

	//printArray1D(y_out, n_out, "y_out :", wordLen=8);
	//printArray2D(coefs, polynom_degree+1, n_coefs_cells, "coefs :", wordLen);
	correctInterpolationSize(n, cell_length, &cell_length_interp, &n_interp, dx);
	std::cout<<n_interp;
	double*yinterp = descretePolynomialInterpolation1D(coefs, n_coefs_cells, polynom_degree,
											cell_length, n_overlap, &cell_length_interp, &n_interp);

	printArray1D(yinterp, n_interp, "yinterp :", wordLen=10);
}

void interp2DExample()
{
	size_t nx = 4, ny=4, xcell_length, ycell_length, nx_overlap, ny_overlap;
	size_t xpolynom_degree, ypolynom_degree, nx_interp=0, ny_interp=0, dx=1, dy=1;
	double**arr = getRandomDoubleArray2D(nx, ny, -10, 10, 0);
	double** arr_interp = polynomialInterpolation2D(arr, nx, ny,
									xcell_length=3, ycell_length=3,
									nx_overlap=2, ny_overlap=2,
									xpolynom_degree=7, ypolynom_degree=7,
									dx=3, dy = 3, &nx_interp, &ny_interp);
	printArray2D(arr_interp, nx_interp, ny_interp, "arr_interp :", 4);
//ypolynom_degree = xcell_length + 2*ny_overlap
    /*double *x1_coefs=0, *y1_coefs=0, *x2_coefs=0, *y2_coefs=0;
    double polynomialInterpolationCoefs()
    double d = polynomialCellPointValue2D(2.5,2.1, x1_coefs, x2_coefs,
                                  y1_coefs, y2_coefs,
                                  xpolynom_degree, ypolynom_degree, xcell_length,
                                  ycell_length, nx_overlap, ny_overlap);*/
    //std::cout<<d;
}


void pyramidalArrayIndexFunctionExample(unsigned int dimension)
{
	int wordLen=7;
	int xpow = dimension;       // puissance des x dont on recherche l'expression de la somme : x^xpow + (x-1)^xpow + ... + 2^xpow + 1^pow
	//int p = xpow + 1;   // puissance maximale d'entrainement de l'agorithme
	//int n = p*2+5 ;     // nombre de donnees d'entrainement de l'agorithme
	int p = xpow + 1;   // puissance maximale d'entrainement de l'agorithme
	int n = 5;     // nombre de donnees d'entrainement de l'agorithme
	int m = 20+n;       // nombre de point de prediction de la fonction obtenue

	double*L = getIntPowList(n, xpow);
	double*CUMLIST = getCumulList(L, n);
	printArray1D(L, n, "List :", wordLen);
	printArray1D(CUMLIST, n, "CUMLIST :", wordLen);

	double *x = linspace(1,n,n), *y = CUMLIST, *xp = linspace(1,m,m), *cf=NULL;
	printArray1D(x, n, "x :", wordLen=9);
	printArray1D(y, n, "y :", wordLen=9);

	double*yp = polynomialPrediction(x, y, n, p, xp, m, cf);
	int cf_size = (int)p+1;
	printArray1D(cf, cf_size, "cf :", wordLen=15);

	double prec=1e-5;
	Fraction* cf_frac = findFractionList(cf, int(p), prec=1e-5);
	printFactionsArray(cf_frac, cf_size, "Coefs (Fraction)", wordLen=10);

	printArray1D(xp, m, "xp :", wordLen=9);
	printArray1D(yp, m, "yp :", wordLen=9);


	free(L);
	free(CUMLIST);
	free(x);
	free(yp);
	free(xp);
	free(cf);
	free(cf_frac);
}

//----------poynomial-------------------------------------------------------

double xPowSum(double*xarr, int n, double p)
{
	double ret=0;
	for (int i = 0; i<n; i++)
		ret += pow(xarr[i],p);
	return ret;
}

double xPowSum2(double*xarr, int id1, int id2, double p)
{
	double ret=0;
	for (int i = id1; i<id2; i++)
		ret += pow(xarr[i],p);
	return ret;
}

double xPowDotYSum(double*xarr, double*yarr, int n, double p)
{
	double ret = 0;
	for (int i = 0; i<n; i++)
		ret += pow(xarr[i],p)*yarr[i];

	return ret;
}

double xPowDotYSum2(double*xarr, double*yarr, int id1, int id2, double p)
{
	double ret = 0;
	for (int i = id1; i<id2; i++)
		ret += pow(xarr[i],p)*yarr[i];

	return ret;
}

double xPowDotYSum3(double*xarr, double*yarr, int id1, int id2, double p)
{
	double ret = 0;
	for (int i = id1, j=0; i<id2; i++)
	{
		ret += pow(xarr[j],p)*yarr[i];
		j++;
	}

	return ret;
}


double* polynomialPrediction(double*x, double*y, int n, double p, double*xp, int m, double*& cf)
{
	cf = polynomialInterpolationCoefs(x,y,n,p);
	double*yp = fx(xp, m, cf,(int)p+1);

	return yp;
}

double* polynomialInterpolationCoefs(double*x, double*y, int n, int p)
{
	int P = p + 1;
	double*M = (double*)malloc(sizeof(double)*P*P);
	double*N = (double*)malloc(sizeof(double)*P);
	int i = 0, j = 0;

	for (j=0; j<P; j++)
	{
		for (i = P-1; i>=0; i--)
        {
            M[j*P + (P-1-i)] = xPowSum(x, n, i+j);
        }

		N[j] = xPowDotYSum(x, y, n,j);
	}
	double* ret = cJacobi(M,N,P);
	free(M);
	free(N);
	return ret;
}

double* polynomialInterpolationCoefs2(double*x, double*y, int id1, int id2, int p)
{
	int P = p + 1;
	double*M = (double*)malloc(sizeof(double)*P*P);
	double*N = (double*)malloc(sizeof(double)*P);
	int i = 0, j = 0;

	for (j=0; j<P; j++)
	{
		for (i = P-1; i>=0; i--)
        {
            M[j*P + (P-1-i)] = xPowSum2(x, id1, id2, i+j);
        }

		N[j] = xPowDotYSum2(x, y, id1, id2,j);
	}

	double* ret = cJacobi(M,N,P);
	free(M);
	free(N);
	return ret;
}

double* polynomialInterpolationCoefs3(double*x, double*y, int id1, int id2, int p)
{
	int P = p + 1;
	double*M = (double*)malloc(sizeof(double)*P*P);
	double*N = (double*)malloc(sizeof(double)*P);
	int i = 0, j = 0, nx = id2-id1;

	for (j=0; j<P; j++)
	{
		for (i = P-1; i>=0; i--)
        {
            M[j*P + (P-1-i)] = xPowSum(x, nx, i+j);
        }

		N[j] = xPowDotYSum3(x, y, id1, id2,j);
	}
	double* ret = cJacobi(M,N,P);
	free(M);
	free(N);
	return ret;
}

void polynomialInterpolationCoefs4(double*x, double*y, int id1, int id2, int p, double*& cf)
{
	int P = p + 1;
	double*M = (double*)malloc(sizeof(double)*P*P);
	double*N = (double*)malloc(sizeof(double)*P);
	int i = 0, j = 0, nx = id2-id1;

	for (j=0; j<P; j++)
	{
		for (i = p; i>=0; i--)
        {
            M[j*P + (p-i)] = xPowSum(x, nx, i+j);
        }

		N[j] = xPowDotYSum3(x, y, id1, id2,j);
	}

	cJacobi2(M,N,P, cf);
	free(M);
	free(N);
}

void polynomialInterpolationCoefs3(double*x, double*y, int id1, int id2, double** cf, csPYRAMID_VARS* pv)
{
	int P = pv->n, p = pv->n-1;
	double*M = pv->X;
	double*N = pv->Y;
	int i = 0, j = 0, nx = id2-id1;

	for (j=0; j<P; j++)
	{
		for (i = p; i>=0; i--)
        {
            M[j*P + (p-i)] = xPowSum(x, nx, i+j);
        }

		N[j] = xPowDotYSum3(x, y, id1, id2,j);
	}
	cJacobi3(cf, pv);

}


double** transpose(double**arr, size_t nx, size_t ny)
{
	double** ret = (double**)malloc(nx*sizeof(double*));
	for (size_t i=0; i<nx; i++)
	{
		ret[i] = (double*)malloc(ny*sizeof(double));
		for (size_t j=0; j<ny; j++)
			ret[i][j] = arr[j][i];
	}
	return ret;
}

double** descretePolynomialInterpolationCoefs1D( double* y, size_t n, size_t cell_length,
												size_t n_overlap, size_t polynom_degree,
												double*& y_out, size_t& n_out, size_t& n_coefs_cells)
{

	double** coefs=NULL;
	if (cell_length < 1)
	{
		cout<<"Error message from descretePolynomialInterpolationCoefs():\n "
				"Invalid Values. Make sure you have cell_length > 2*n_overlap\n\n";
		exit(0);
	}
	else
	{
		size_t r = n%(cell_length);

		n_out = n + (cell_length - r) + 2*n_overlap; // 2*n_overlap = extra zeros on the left and right sides of arrle

		if (r == 0)
			n_out = n + 2*n_overlap;

		y_out = (double*)malloc(n_out*sizeof(double));
		for (size_t i = 0; i<n_overlap; i++)
		{
			y_out[i] = 0;
		}

		size_t n1 = n + n_overlap;
		for (size_t i = n1; i<n_out; i++)
		{
			y_out[i] = 0;
		}

		for (size_t i = n_overlap; i<n1; i++)
		{
			y_out[i] = y[i-n_overlap];
		}

		n_coefs_cells = (n_out-2*n_overlap)/cell_length;
		size_t Total_length = cell_length + 2*n_overlap;

		coefs = (double**)malloc(n_coefs_cells*sizeof(double*));
		double *x = linspace(1,Total_length, Total_length);


		size_t id1=0, id2 = Total_length;
		for (size_t i = 0; i<n_coefs_cells; i++)
		{
			coefs[i] = polynomialInterpolationCoefs3(x,y_out,id1, id2,polynom_degree);
			id1 += cell_length;
			id2 = id1 + Total_length;
		}
		free(x);
	}
	return coefs;
}


void descretePolynomialInterpolationCoefs1D2(double* y, double**&coefs, size_t n, size_t cell_length,
												size_t n_overlap, size_t polynom_degree,
												size_t n_out, size_t n_coefs_cells)
{

	if (cell_length < 1)
	{
		cout<<"Error message from descretePolynomialInterpolationCoefs():\n "
				"Invalid Values. Make sure you have cell_length > 2*n_overlap\n\n";
		exit(0);
	}
	else
	{

		double *y_out = (double*)malloc(n_out*sizeof(double));
		for (size_t i = 0; i<n_overlap; i++)
		{
			y_out[i] = 0;
		}

		size_t n1 = n + n_overlap;
		for (size_t i = n1; i<n_out; i++)
		{
			y_out[i] = 0;
		}

		for (size_t i = n_overlap; i<n1; i++)
		{
			y_out[i] = y[i-n_overlap];
		}


		size_t Total_length = cell_length + 2*n_overlap;

		double *x = linspace(1,Total_length, Total_length);

		//printArray1D<double>(*coefs, polynom_degree, "coefs -------- :", 9);
		size_t id1=0, id2 = Total_length;
		for (size_t i = 0; i<n_coefs_cells; i++)
		{
			polynomialInterpolationCoefs4(x,y_out,id1, id2,polynom_degree, coefs[i]);

			id1 += cell_length;
			id2 = id1 + Total_length;
		}
		free(x);
		free(y_out);
	}
}


/*********************************************************************************************************************************/

double** getReadyMap(double** map, size_t nx, size_t ny,
                    size_t xcell_length,size_t ycell_length,
					size_t nx_overlap, size_t ny_overlap,
					size_t* nx_out,size_t* ny_out)
{

	if (xcell_length < 1||ycell_length < 1)
	{
		cout<<"Error message from descretePolynomialInterpolationCoefs():\n "
				"Invalid Values. Make sure you have cell_length > 2*n_overlap\n\n";
		exit(0);
	}
	else
	{
        size_t r_xcell_length = nx%xcell_length, r_ycell_length = ny%ycell_length;
        size_t zeropadx_bottom = (xcell_length + nx_overlap)-r_xcell_length, zeropady_bottom = (ycell_length + ny_overlap)-r_ycell_length;
        if(r_xcell_length == 0)  zeropadx_bottom = nx_overlap;
        if(r_ycell_length == 0)  zeropady_bottom = ny_overlap;

        size_t zeropadx_top = nx_overlap, zeropady_top = ny_overlap;
        size_t psz = sizeof(double*), sz = sizeof(double);
        size_t n = zeropadx_top+nx, n1 = zeropady_top + ny;

        *nx_out = n + zeropadx_bottom;
        *ny_out = n1 + zeropady_bottom;

		size_t t = *nx_out*sz;

		double **map_out = (double**)malloc(*ny_out*psz);
		for(size_t j = 0; j<zeropady_top; j++)
        {
            //map_out[j] = (double*)calloc(*nx_out, sz);
			map_out[j] = (double*)malloc(t);
			for(size_t i = 0, i0 =0 ; i<*nx_out; i++)
			{
				if(i>=zeropadx_top && i<n)
					map_out[j][i] = map[0][i0++];
				else
					map_out[j][i] = 0;
			}
        }
        for(size_t j = n1; j<*ny_out; j++)
        {
            //map_out[j] = (double*)calloc(*nx_out, sz);
			map_out[j] = (double*)malloc(t);
			for(size_t i = 0, i0=0; i<*nx_out; i++)
			{
				if(i>=zeropadx_top && i<n)
					map_out[j][i] = map[ny-1][i0++];
				else
					map_out[j][i] = 0;
			}
        }

        for(size_t j = zeropady_top, j0 = 0; j<n1; j++, j0++)
		{
		    map_out[j] = (double*)malloc(t);
		    for (size_t i = 0; i<zeropadx_top; i++)
            {
                map_out[j][i] = map[j0][0];
            }

            for (size_t i = n; i<*nx_out; i++)
            {
                map_out[j][i] = map[j0][nx-1];
            }

            for (size_t i = zeropadx_top, i0=0; i<n; i++)
            {
                map_out[j][i] = map[j0][i0++];
            }
		}
		
		return map_out;
	}
}

double*** getUniDirDiscreteCoefs2D(double** map, size_t nx, size_t ny,size_t _nx, size_t _ny,
                    size_t cell_length,
					size_t nx_overlap,size_t ny_overlap, 
					size_t polynom_degree, size_t *n_cells_coefs, csPYRAMID_VARS* pv)
{

    *n_cells_coefs = ceil(double(_nx)/cell_length);
	size_t Total_length = cell_length + 2*nx_overlap, NY = _ny+1;

    double *x = linspace(1,Total_length, Total_length);

    double ***coefs = (double***)malloc(NY*sizeof(double**));
    //cout<<polynom_degree<<" ooo\n";
    size_t sz = *n_cells_coefs*sizeof(double*), csz = (polynom_degree+1)*sizeof(double);
    size_t id1=0, id2 = Total_length, j1;
    for (size_t j = 0; j<NY; j++)
    {
        coefs[j] = (double**)malloc(sz);
		j1 = j+ny_overlap;
    	id1=0; id2 = Total_length;
        for (size_t i = 0; i<*n_cells_coefs; i++)
        {
            coefs[j][i]=(double*)malloc(csz);
			//cout<<coefs[j][i]<<" test \n";
            polynomialInterpolationCoefs3(x,map[j1],id1, id2, &coefs[j][i], pv);
            id1 += cell_length;
            id2 = id1 + Total_length;
        }
    }
    free(x);
    return coefs;
}


double polynomialCellPointValue2D(size_t x_dest,size_t y_dest, double** map_src, size_t nx_src, size_t ny_src, double*** x_coefs,
                                  double*** y_coefs, size_t nx_dest, size_t ny_dest,
                                  size_t xdegree, size_t ydegree, size_t xcell_length,
                                  size_t ycell_length, size_t nx_overlap, size_t ny_overlap)
{
    double x0 = x_dest*nx_src/double(nx_dest);
	double y0 = y_dest*ny_src/double(ny_dest);
	double xf_src = x0 + nx_overlap;
	double yf_src = y0 + ny_overlap;
	size_t x_src = (size_t)xf_src;
	size_t y_src = (size_t)yf_src;
    double dx = xf_src - x_src;
    double dy = yf_src - y_src;

	size_t i = (x_src-nx_overlap)/xcell_length, j = (y_src - ny_overlap)/ycell_length;

    size_t px = xdegree+1, py = ydegree+1;
	size_t x1i = (i+1)*xcell_length + nx_overlap;
	size_t y1i = (j+1)*ycell_length + ny_overlap;

    double a11 = map_src[y_src][x_src]*(1-dx) + map_src[y_src][x1i]*dx;
    double a21 = map_src[y1i][x_src]*(1-dx) + map_src[y1i][x1i]*dx;

    double plnval = a11*(1-dy) + a21*dy;

	double dx2 = x0/xcell_length,dy2 = y0/ycell_length;
	dx2 = (dx2 - (double)(size_t)dx2)*xcell_length;
	dy2 = (dy2 - (double)(size_t)dy2)*ycell_length;
	size_t x0i = int(x0), y0i = int(y0);
    double xinterp = fxi(dy2+ny_overlap+1,y_coefs[x0i][j],py)*(1-dx) + fxi(dy2+ny_overlap+1,y_coefs[x0i+1][j],py)*dx;
    double yinterp = fxi(dx2+nx_overlap+1,x_coefs[y0i][i],px)*(1-dy) + fxi(dx2+nx_overlap+1,x_coefs[y0i+1][i],px)*dy;
    
	return xinterp + yinterp - plnval;
}

double** getInterpolatedMap(double** map_src, size_t nx_src,
                          size_t ny_src, double*** x_coefs,
                          double*** y_coefs, size_t nx_dest, size_t ny_dest,
                          size_t xdegree, size_t ydegree, size_t xcell_length,
                          size_t ycell_length, size_t nx_overlap, size_t ny_overlap)
{
    double**map_dest = (double**)malloc(ny_dest*sizeof(double*));
    for(size_t j = 0; j<ny_dest; j++)
    {
        map_dest[j] = (double*)malloc(nx_dest*sizeof(double));
        for(size_t i=0; i<nx_dest; i++)
        {
            map_dest[j][i] = polynomialCellPointValue2D(i,j, map_src, nx_src, ny_src, x_coefs,
                                  y_coefs, nx_dest, ny_dest,
                                  xdegree, ydegree, xcell_length,
                                  ycell_length, nx_overlap, ny_overlap);
        }
    }
    return map_dest;
}

void test()
{
    double**arr_interp=NULL;
    size_t nx = 10, ny=10, xcell_length, ycell_length, nx_overlap, ny_overlap;
	size_t xpolynom_degree=7, ypolynom_degree=7, nx_interp=0, ny_interp=0, dx=1, dy=1;
	size_t nx_out=0, ny_out=0;
	csPYRAMID_VARS xpv, ypv;
	xpv.set(xpolynom_degree+1);
	ypv.set(ypolynom_degree+1);

	double**arr = getRandomDoubleArray2D(nx, ny, 0, 10, 1);
	printArray2D(arr, nx, ny, "arr :", 7);

    double **map = getReadyMap(arr, nx, ny,
                    xcell_length=3,ycell_length=3,
					nx_overlap=2, ny_overlap=2,
					&nx_out,&ny_out);
    printArray2D(map, nx_out, ny_out, "map :", 7);
	double**map_t = transpose(map, nx_out, ny_out);
	//printArray2D(map_t, ny_out, nx_out, "map_t :", 9);
	size_t nx_cells_coefs=0, ny_cells_coefs=0, nx_dest=nx*3,ny_dest=ny*3;
    double*** xcoefs = getUniDirDiscreteCoefs2D(map, nx_out, ny_out, nx, ny,
                        xcell_length,nx_overlap,ny_overlap, xpolynom_degree, &nx_cells_coefs, &xpv);
    double*** ycoefs = getUniDirDiscreteCoefs2D(map_t, ny_out, nx_out, ny, nx,
                        ycell_length,ny_overlap,nx_overlap, ypolynom_degree, &ny_cells_coefs, &ypv);

    double** map_interp = getInterpolatedMap(map, nx, ny, xcoefs,
                          ycoefs, nx_dest, ny_dest,
                          xpolynom_degree, ypolynom_degree, xcell_length,
                          ycell_length, nx_overlap, ny_overlap);

    printArray2D(map_interp, nx_dest, ny_dest, "map_interp :", 7);
	/*for(int j=0; j<ny; j++)
	{	
		for(int i=0; i<nx_cells_coefs; i++)
			for(int k=3; k<xcell_length+nx_overlap+1; k++)
				cout<<(fxi(k,xcoefs[j][i],polynom_degree+1))<<"  ";
		cout<<"\n";
	}*/
}


/*********************************************************************************************************************************/

double** getCoefsArray(size_t n, size_t n_overlap, size_t cell_length, size_t polynom_degree,
						size_t*n_coefs_cells, size_t* n_out)
{
	size_t r = n%(cell_length);

	*n_out = n + (cell_length - r) + 2*n_overlap; // 2*n_overlap = extra zeros on the left and right sides of arrle

	if (r == 0)
		*n_out = n + 2*n_overlap;
	*n_coefs_cells = (*n_out-2*n_overlap)/cell_length;

	double**coefs = (double**)malloc(*n_coefs_cells*sizeof(double*));
	size_t sz = polynom_degree + 1;

	for (size_t i = 0; i<*n_coefs_cells; i++)
	{
		coefs[i] = (double*)malloc(sz*sizeof(double));
		for(size_t j=0; j<sz; j++)
		{
			coefs[i][j] = 0;
		}
	}
	return coefs;
}

void correctInterpolationSize(size_t n, size_t cell_length, size_t* cell_length_interp, size_t*n_interp, size_t dx)
{// a verifier en cas de probleme...n vs n_out
	*n_interp = dx*n;
	size_t nx = dx*cell_length;
	*cell_length_interp = nx;
	*n_interp = *n_interp + (nx - *n_interp%nx); // n_interp doit etre multiple nx
}

double*descretePolynomialInterpolation1D(double**coefs, size_t n_coefs_cells, size_t polynom_degree,
										size_t cell_length, size_t n_overlap, size_t* cell_length_interp, size_t* n_interp)
{

	size_t nx = *cell_length_interp, id1 = 0, id2=nx;
	double*y = (double*)malloc(*n_interp*sizeof(double));
	if (nx >= 1)
	{
		double*x = linspaceExcb(n_overlap+1, n_overlap + cell_length+1, nx);
		for (size_t i = 0; i<n_coefs_cells; i++)
		{
			fx21(x, y, id1, id2, coefs[i], polynom_degree+1);
			id1 += nx;
			id2 = id1 + nx;
		}
		free(x);
		x = NULL;
	}
	else
	{
		for (size_t i = 0; i<*n_interp; i++)
		{
			y[i] = 0;
		}
		cout<<"Error from descretePolynomialInterpolation1D() : \n"
				"Invalid n_out parameter !\n\n";
	}
	return y;
}



double** cellPolynomialInterpolation2D(double **x_interp, double **y_interp, size_t nx_interp, size_t ny_interp,
								size_t dx, size_t dy, size_t nx, size_t ny)
{

	double ri = 0.0, rj = 0.0, xinterp = 0.0, yinterp = 0.0;
	double a11 = 0.0, a21 = 0.0;
	double plnval = 0.0;
	size_t id1x, id2x, id1y, id2y, a = dx*nx-1, b = dy*ny-1;

	double **ret = (double**)malloc(ny_interp*sizeof(double*));
	for(size_t j=0; j<ny_interp; j+=1)
	{
		ret[j] = (double*)malloc(nx_interp*sizeof(double));
		for(size_t i=0; i<nx_interp; i+=1)
			if (j%dy == 0 && j<b)
				ret[j][i] = x_interp[j/dy+j%dy][i];
			else if (i%dx == 0 && i<a)
				ret[j][i] = y_interp[i/dx+i%dx][j];
			else
				ret[j][i] = 0.0;
	}

	for(size_t j=0; j<ny_interp-dy; j+=dy)
	{
		for(size_t i=0; i<nx_interp-dx; i+=dx)
		{
			id1x = i + 1;
			id2x = i + dx;
			id1y = j + 1;
			id2y = j + dx;
			for(size_t j0=id1y; j0<id2y; j0++)
			{
				rj = double(j0%(dy+1))/dy;
				for(size_t i0=id1x; i0<id2x; i0++)
				{
					ri = double(i0%(dx+1))/dx;
//cout<<ri<<"\n";
					a11 = ret[j][i]*(1-ri) + ret[j][i+dx]*ri;
					a21 = ret[j+dy][i]*(1-ri) + ret[j+dy][i+dx]*ri;

					plnval = a11*(1-rj) + a21*rj;

					xinterp = ret[j0][i]*(1-ri) + ret[j0][i+dx]*ri;
					yinterp = ret[j][i0]*(1-rj) + ret[j+dy][i0]*rj;

					ret[j0][i0] = xinterp + yinterp - plnval;
				}
			}
		}
	}
	return ret;
}


double**multilinePolynomialInterpolation(double**arr, size_t nx, size_t ny, size_t cell_length,
                                        size_t n_overlap, size_t polynom_degree, size_t dx,
                                        size_t* cell_length_interp, size_t* n_interp)
{
	size_t n_out=0, n_coefs_cells=0;
	double*y_out=NULL;
	double **ret = (double**)malloc(ny*sizeof(double*));

	double**coefs=getCoefsArray(nx, n_overlap, cell_length, polynom_degree,
						&n_coefs_cells, &n_out);

	correctInterpolationSize(nx, cell_length, cell_length_interp, n_interp, dx);
	for(size_t j=0; j<ny; j++)
	{
		descretePolynomialInterpolationCoefs1D2(arr[j],coefs, nx, cell_length,
														n_overlap, polynom_degree,
														n_out, n_coefs_cells);

		ret[j] = descretePolynomialInterpolation1D(coefs, n_coefs_cells, polynom_degree,
												cell_length, n_overlap, cell_length_interp, n_interp);
		//printArray1D<double>(ret[j], nx/3, "ret :", 9);
		//cout<<j<<"\n";*/
	}
	return ret;
}

double**multilinePolynomialInterpolation_2(double**arr, size_t nx, size_t ny, size_t cell_length,
                                        size_t n_overlap, size_t polynom_degree, size_t dx,
                                        size_t* cell_length_interp, size_t* n_interp, double***& coefs)
{
	size_t n_out=0, n_coefs_cells=0;
	double*y_out=NULL;
	double **ret = (double**)malloc(ny*sizeof(double*));

	coefs = (double***)malloc(ny*sizeof(double**));
	correctInterpolationSize(nx, cell_length, cell_length_interp, n_interp, dx);
	for(size_t j=0; j<ny; j++)
	{
		coefs[j]=getCoefsArray(nx, n_overlap, cell_length, polynom_degree,
						&n_coefs_cells, &n_out);
		descretePolynomialInterpolationCoefs1D2(arr[j],coefs[j], nx, cell_length,
														n_overlap, polynom_degree,
														n_out, n_coefs_cells);

		ret[j] = descretePolynomialInterpolation1D(coefs[j], n_coefs_cells, polynom_degree,
												cell_length, n_overlap, cell_length_interp, n_interp);
		//printArray1D<double>(ret[j], nx/3, "ret :", 9);
		//cout<<j<<"\n";*/
	}
	return ret;
}

double**polynomialInterpolation2D(double**arr, size_t nx, size_t ny,
								size_t xcell_length, size_t ycell_length,
								size_t nx_overlap, size_t ny_overlap,
								size_t xpolynom_degree, size_t ypolynom_degree,
								size_t dx, size_t dy,
								size_t* nx_interp, size_t* ny_interp)
{
	double**arr_interp=NULL;
	printArray2D(arr, nx, ny, "arr :", 9);
	size_t xcell_length_interp=0, ycell_length_interp=0;
	double**xarr = multilinePolynomialInterpolation(arr, nx, ny, xcell_length,
												nx_overlap, xpolynom_degree, dx,
												&xcell_length_interp, nx_interp);
	printArray2D(xarr, *nx_interp, ny, "xarr_interp :", 9);
	double**arr_t = transpose(arr, nx, ny);
	double**yarr = multilinePolynomialInterpolation(arr_t, ny, nx, ycell_length,
													ny_overlap, ypolynom_degree, dy,
													&ycell_length_interp, ny_interp);
	printArray2D(yarr, *ny_interp, nx, "yarr_interp :", 9);

	arr_interp = cellPolynomialInterpolation2D(xarr, yarr, *nx_interp, *ny_interp,
									dx, dy, nx, ny);
	printArray2D(arr_interp, *nx_interp, *ny_interp, "arr_interp :", 9);
	return arr_interp;
}






