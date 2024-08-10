/*
 * jacobi.h
 *
 *  Created on: 13 mai 2023
 *      Author: azphi
 */

#ifndef JACOBI_H_
#define JACOBI_H_


#include "utilities.h"

typedef struct
{
    double* A,*B;
    int*C;
    size_t M,N, n2, n;
    double *X, *Y;
    void set(size_t _n)
    {
        n = _n;
        n2 = n*n;
        M = firstDegreePyramidalArrayIndexLevel(n);
        N = secondDegreePyramidalArrayIndexLevel(n);
    //	std::cout<<"\n N = "<<N<<"\n\n";

        A=(double*)malloc(sizeof(double)*N);
        B=(double*)malloc(sizeof(double)*M);
        C=(int*)malloc(sizeof(int)*n); //pour retenir les indices de lignes avec premier terme non nul

        X = (double*)malloc(sizeof(double)*n2);
        Y = (double*)malloc(sizeof(double)*n);
    }
}csPYRAMID_VARS;

double* cJacobi(double*a1, double*b1, int n);
double* cJacobi2(double*a1, double*b1, int n, double*&cf);
void cPyramid(double* a, double* b, int n, double*& P, double*& Q, int*& R, double*& CF);
void cPyramid2(double* a, double* b, int n, double*& P, double*& Q, int*& R);
void cJacobi3(double**cf, csPYRAMID_VARS* pv);
void cPyramid3(csPYRAMID_VARS* pv);


#endif /* JACOBI_H_ */
