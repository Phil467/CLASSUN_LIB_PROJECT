/*
 * jacobi.cpp
 *
 *  Created on: 13 mai 2023
 *      Author: azphi
 */

#include "jacobi.h"


char* JACOBI_SOLVER_ERR = (char*)"";
int JACOBI_MESSAGE_ID = 0;

void cPyramid(double* a, double* b, int n, double*& P, double*& Q, int*& R, double*& CF)
{
    int n2 = n*n;
	int M = firstDegreePyramidalArrayIndexLevel(n);
	int N = secondDegreePyramidalArrayIndexLevel(n);
//	std::cout<<"\n N = "<<N<<"\n\n";

	int sz = sizeof(double)*n;
	double *p=(double*)malloc(sizeof(double)*N);
	double *q=(double*)malloc(sizeof(double)*M);
	int *r=(int*)malloc(sz); //pour retenir les indices de lignes avec premier terme non nul
	double *cf=(double*)malloc(sz);

	for (int k=0; k<n2; k++)
	{
		p[k] = a[k];
	}
	for (int k=0; k<n; k++)
	{
		q[k] = b[k];
		r[k] = 0;
		cf[k] = 0;
	}
	for (int k=n2; k<N; k++)
	{
		p[k] = 0;
	}
	for (int k=n; k<M; k++)
	{
		q[k] = 0;
	}
	P = p; Q = q; R = r; CF = cf;
}


void cPyramid2(double* a, double* b, int n, double*& P, double*& Q, int*& R)
{
    int n2 = n*n;
	int M = firstDegreePyramidalArrayIndexLevel(n);
	int N = secondDegreePyramidalArrayIndexLevel(n);
//	std::cout<<"\n N = "<<N<<"\n\n";

	int sz = sizeof(double)*n;
	double *p=(double*)malloc(sizeof(double)*N);
	double *q=(double*)malloc(sizeof(double)*M);
	int *r=(int*)malloc(sz); //pour retenir les indices de lignes avec premier terme non nul

	for (int k=0; k<n2; k++)
	{
		p[k] = a[k];
	}
	for (int k=0; k<n; k++)
	{
		q[k] = b[k];
		r[k] = 0;
	}
	for (int k=n2; k<N; k++)
	{
		p[k] = 0;
	}
	for (int k=n; k<M; k++)
	{
		q[k] = 0;
	}
	P = p; Q = q; R = r;
}

void pyramidVars(int n, int& M, int& N, double*& p, double*& q, int*& r)
{
	M = firstDegreePyramidalArrayIndexLevel(n);
	N = secondDegreePyramidalArrayIndexLevel(n);
//	std::cout<<"\n N = "<<N<<"\n\n";

	p=(double*)malloc(sizeof(double)*N);
	q=(double*)malloc(sizeof(double)*M);
	r=(int*)malloc(sizeof(double)*n); //pour retenir les indices de lignes avec premier terme non nul
}


double* cJacobi(double*a1, double*b1, int n)
{
	double *a = 0, *b = 0, *cf = 0, aa;
	int *r = 0;
	cPyramid(a1, b1, n, a, b, r, cf);

	int k = 0, bj = 0, j = 0, jsz = 0, l = 0, nk = 0, i = 0;

	int Ka = 0, Kb = 0, iid, jjd, lld, _iid, _jjd, _lld;
	for (k = 0; k < n; k++)
	{
		jsz = 0; l = 0; bj = 0; j = 0;
		nk = n-k;

		for (l = 0; l < nk; l++)
		{
			if (a[Ka + l*nk + 0]!=0)
			{
				bj = 1;
				break;
			}
		}

		r[k]=l;
		if (bj == 0)
		{
			JACOBI_SOLVER_ERR = "\nJacobi Solver Warning : zeros colums found!";
			JACOBI_MESSAGE_ID += 1;
			break; //colone de 0
		}
		for (j = 0; j < nk; j++)
		{
			if (j != l)
			{
				iid = Ka + nk*nk + jsz*(nk-1);
				jjd = Ka + j*nk;
				lld = Ka + l*nk;
				aa = a[jjd + 0]/a[lld + 0];
				for (i = 1; i < nk; i++)
				{
					a[iid + i-1] = a[jjd + i] - aa*a[lld + i];
				}
				_iid = Kb + nk + jsz;
				_jjd = Kb + j;
				_lld = Kb + l;
				b[_iid] = b[_jjd] - aa*b[_lld];
				jsz += 1;
			}
		}

		Ka += nk*nk;
		Kb += nk;
	}
	if (bj!=0)
	{
		k = n-1;
		Kb = firstDegreePyramidalArrayIndexLevel(n)-1;
		Ka = secondDegreePyramidalArrayIndexLevel(n)-1;

		b[Kb] = b[Kb]/a[Ka];
		cf[k] = b[Kb];
		k = n-2;
		double x = 0;
		int t = 0, idj = 0, Na = 0, Nb = 0;

		for (k = n-2; k >= 0; k--)
		{
			j = r[k];
			x = 0;
			t = 0;
			nk = n-k;
			Na = Ka+1 - secondDegreePyramidalArrayIndexLevel(nk);
			for (i = n-k-1; i >= 1; i--)
			{
				idj = n-1-t;
				Nb = Kb+1 - firstDegreePyramidalArrayIndexLevel(t+1); //t+1 = n - idj
				x += b[Nb + r[idj]]*a[Na + j*nk + i];
				t += 1;
			}
			Nb = Kb+1 - firstDegreePyramidalArrayIndexLevel(nk);

			b[Nb + j] = ((b[Nb + j]-x) / a[Na + nk*j + 0]);
			cf[k] = (b[Nb + j]);
		}
	}
	free(a);
	free(b);
	free(r);
	return cf;
}


double* cJacobi2(double*a1, double*b1, int n, double*&cf)
{
	double *a = 0, *b = 0, aa;
	int *r = 0;
	cPyramid2(a1, b1, n, a, b, r);

	int k = 0, bj = 0, j = 0, jsz = 0, l = 0, nk = 0, i = 0;

	int Ka = 0, Kb = 0, iid, jjd, lld, _iid, _jjd, _lld;
	for (k = 0; k < n; k++)
	{
		jsz = 0; l = 0; bj = 0; j = 0;
		nk = n-k;

		for (l = 0; l < nk; l++)
		{
			if (a[Ka + l*nk + 0]!=0)
			{
				bj = 1;
				break;
			}
		}

		r[k]=l;
		if (bj == 0)
		{
			JACOBI_SOLVER_ERR = "\nJacobi Solver Warning : zeros colums found!";
			JACOBI_MESSAGE_ID += 1;
			break; //colone de 0
		}
		for (j = 0; j < nk; j++)
		{
			if (j != l)
			{
				iid = Ka + nk*nk + jsz*(nk-1);
				jjd = Ka + j*nk;
				lld = Ka + l*nk;
				aa = a[jjd + 0]/a[lld + 0];
				for (i = 1; i < nk; i++)
				{
					a[iid + i-1] = a[jjd + i] - aa*a[lld + i];
				}
				_iid = Kb + nk + jsz;
				_jjd = Kb + j;
				_lld = Kb + l;
				b[_iid] = b[_jjd] - aa*b[_lld];
				jsz += 1;
			}
		}

		Ka += nk*nk;
		Kb += nk;
	}
	if (bj!=0)
	{
		k = n-1;
		Kb = firstDegreePyramidalArrayIndexLevel(n)-1;
		Ka = secondDegreePyramidalArrayIndexLevel(n)-1;

		b[Kb] = b[Kb]/a[Ka];
		cf[k] = b[Kb];
		k = n-2;
		double x = 0;
		int t = 0, idj = 0, Na = 0, Nb = 0;

		for (k = n-2; k >= 0; k--)
		{
			j = r[k];
			x = 0;
			t = 0;
			nk = n-k;
			Na = Ka+1 - secondDegreePyramidalArrayIndexLevel(nk);
			for (i = n-k-1; i >= 1; i--)
			{
				idj = n-1-t;
				Nb = Kb+1 - firstDegreePyramidalArrayIndexLevel(t+1); //t+1 = n - idj
				x += b[Nb + r[idj]]*a[Na + j*nk + i];
				t += 1;
			}
			Nb = Kb+1 - firstDegreePyramidalArrayIndexLevel(nk);

			b[Nb + j] = ((b[Nb + j]-x) / a[Na + nk*j + 0]);
			cf[k] = (b[Nb + j]);
		}
	}
	free(a);
	free(b);
	free(r);
	return cf;
}

/**************************************************************/

void cPyramid3(csPYRAMID_VARS* pv)
{
	double* a = pv->X, *b = pv->Y;
	int n = pv->n;
	int M = pv->M, N = pv->N;
	double *p = pv->A, *q = pv->B;
	int *r = pv->C;

    int n2 = n*n;

	for (int k=0; k<n2; k++)
	{
		p[k] = a[k];
	}
	for (int k=0; k<n; k++)
	{
		q[k] = b[k];
		r[k] = 0;
	}
	for (int k=n2; k<N; k++)
	{
		p[k] = 0;
	}
	for (int k=n; k<M; k++)
	{
		q[k] = 0;
	}
}

void cJacobi3(double**cf, csPYRAMID_VARS* pv)
{
	cPyramid3(pv);
	
	double*a1 = pv->X, *b1 = pv->Y, n = pv->n; 
	double *a = pv->A, *b = pv->B, aa;
	int *r = pv->C;

	int k = 0, bj = 0, j = 0, jsz = 0, l = 0, nk = 0, i = 0;

	int Ka = 0, Kb = 0, iid, jjd, lld, _iid, _jjd, _lld;
	for (k = 0; k < n; k++)
	{
		jsz = 0; l = 0; bj = 0; j = 0;
		nk = n-k;

		for (l = 0; l < nk; l++)
		{
			if (a[Ka + l*nk + 0]!=0)
			{
				bj = 1;
				break;
			}
		}

		r[k]=l;
		if (bj == 0)
		{
			JACOBI_SOLVER_ERR = "\nJacobi Solver Warning : zeros colums found!";
			JACOBI_MESSAGE_ID += 1;
			break; //colone de 0
		}
		for (j = 0; j < nk; j++)
		{
			if (j != l)
			{
				iid = Ka + nk*nk + jsz*(nk-1);
				jjd = Ka + j*nk;
				lld = Ka + l*nk;
				aa = a[jjd + 0]/a[lld + 0];
				for (i = 1; i < nk; i++)
				{
					a[iid + i-1] = a[jjd + i] - aa*a[lld + i];
				}
				_iid = Kb + nk + jsz;
				_jjd = Kb + j;
				_lld = Kb + l;
				b[_iid] = b[_jjd] - aa*b[_lld];
				jsz += 1;
			}
		}

		Ka += nk*nk;
		Kb += nk;
	}
	
	if (bj!=0)
	{
		k = n-1;
		Kb = firstDegreePyramidalArrayIndexLevel(n)-1;
		Ka = secondDegreePyramidalArrayIndexLevel(n)-1;

		b[Kb] = b[Kb]/a[Ka];
		(*cf)[k] = b[Kb];
		k = n-2;
		double x = 0;
		int t = 0, idj = 0, Na = 0, Nb = 0;

		for (k = n-2; k >= 0; k--)
		{
			j = r[k];
			x = 0;
			t = 0;
			nk = n-k;
			Na = Ka+1 - secondDegreePyramidalArrayIndexLevel(nk);
			for (i = n-k-1; i >= 1; i--)
			{
				idj = n-1-t;
				Nb = Kb+1 - firstDegreePyramidalArrayIndexLevel(t+1); //t+1 = n - idj
				x += b[Nb + r[idj]]*a[Na + j*nk + i];
				t += 1;
			}
			Nb = Kb+1 - firstDegreePyramidalArrayIndexLevel(nk);

			b[Nb + j] = ((b[Nb + j]-x) / a[Na + nk*j + 0]);
			(*cf)[k] = (b[Nb + j]);
		}
	}
}


