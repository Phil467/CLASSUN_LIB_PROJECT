/*
 * utilities.h
 *
 *  Created on: 13 mai 2023
 *      Author: azphi
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <string.h>
#include <cmath>
#include <iomanip>
#include <time.h>

using namespace std;

typedef struct
{
	int64_t a, b;
	double quotient()
	{
		if(b==0)
		{
			std::cout<<"\nFraction computing warning : \n  b must be different of zero! Set to 1 by default.\n";
			b = 1;
		}
		return double(a)/double(b);
	}
}Fraction;

extern int TAB_PRINT_ID;

double* fx(double*x, size_t n, double*cf, size_t P);
void fx2(double*x, double*& y, size_t n, double*cf, size_t P);
void fx21(double*x, double*& y, size_t id1, size_t id2, double*cf, size_t P);
void array2dToArray1D(double** a2d, size_t nx, size_t ny, double*& a1d);
double* array2dToArray1D2(double** a2d, size_t nx, size_t ny);

size_t firstDegreePyramidalArrayIndexLevel(size_t level);
size_t secondDegreePyramidalArrayIndexLevel(size_t level);
double* linspace(double a, double b, size_t n);
double* linspaceExcb(double a, double b, size_t n);
Fraction findFraction(double nb, double prec);
Fraction* findFractionList(double*nbs, size_t n, double prec=1e-5);
double getRandomDouble(int64_t n1, int64_t n2, size_t exponent);
double*getRandomDoubleArray1D(size_t n, int64_t min, int64_t max, size_t exponent);
double**getRandomDoubleArray2D(size_t nx, size_t ny, int64_t min, int64_t max, size_t exponent);
double* getIntPowList(size_t n, double p);
double* getCumulList(double*l, size_t n);

template<class T> void printArray2D(T** arr, size_t nx, size_t ny, const char*title, size_t wordLen)
{
    if (strcasecmp(title,"Table")==0)
        std::cout<<"Table id : "<<TAB_PRINT_ID<<"\n";
    else
        std::cout<<title<<"\n";
    for (int j=0; j<ny; j++)
    {
    	for (int i=0; i<nx; i++)
		{
			std::cout<<setw(wordLen)<<arr[j][i]<<"  ";
		}
    	std::cout<<"\n";
    }
    std::cout<<"\n\n";
    TAB_PRINT_ID++;
}

template<class T> void printArray1D(T* arr, size_t n, const char*title, size_t wordLen)
{
    if (strcasecmp(title,"Table")==0)
        std::cout<<"Table id : "<<TAB_PRINT_ID<<"\n";
    else
        std::cout<<title<<"\n";
    for (int i=0; i<n; i++)
    {
        std::cout<<setw(wordLen)<<arr[i];
    }
    std::cout<<"\n\n";
    TAB_PRINT_ID++;
}
void printArray2D(double** arr, size_t nx, size_t ny, const char*title, size_t wordLen);
void printArray1D(size_t* arr, size_t n, const char*title, size_t wordLen);
void printArray2D(size_t** arr, size_t nx, size_t ny, const char*title, size_t wordLen);
void printArray1D(double* arr, size_t n, const char*title, size_t wordLen);
void printFactionsArray(Fraction* arr, size_t n, const char*title, size_t wordLen);

double sum(double*arr, size_t n);
double round(double nb, size_t ndigits);
double roundZero(double nb);
double* arrayRound(double*arr, size_t n, size_t ndigits);
void arrayRound2(double*&arr, size_t n, size_t ndigits);
double* arrayBoost(double* arr, size_t n, double fact);
void arrayBoost2(double*& arr, size_t n, double fact);
void minmax1D(double*arr, size_t n, size_t& minval, size_t& maxval);
void minmax2D(double**arr, size_t nx, size_t ny, double& minval, double& maxval);
size_t**fullUInt2D(size_t nx, size_t ny, size_t nb);
int**fullInt2D(size_t nx, size_t ny, int nb);
double**fullDouble2D(size_t nx, size_t ny, double nb);
template<class T> T*full1D(size_t nx, T nb)
{
    T*arr = (T*)malloc(sizeof(T)*nx);
    for (int i=0; i<nx; i++)
    {
        arr[i]=nb;
    }
	return arr;
}

template<class T> T**full2D(size_t nx, size_t ny, T nb)
{
    T**arr = (T**)malloc(sizeof(T*)*ny);
	for (int j=0; j<ny; j++)
	{
		arr[j] = (T*)malloc(sizeof(T)*nx);
		for (int i=0; i<nx; i++)
		{
			arr[j][i]=nb;
		}
	}
	return arr;
}

//void setStrRGB(char*str,   size_t pos,  csRGBA c);

void setStrRGB2(char*str,   size_t pos,  size_t r, size_t g, size_t b);


template<class T> T* trim1D(T*map, size_t nx, int x, int cx)
{
    T*ret=0;
    if(x>=0 && x<=nx && cx>x && cx<nx)
    {
        T*ret=(T*)malloc(cx*sizeof(T));
        for(int i=0; i<cx; i++)
        {
            ret[i] = map[i+x];
        }
    }
    else
    {
        std::cout<<"From trimDouble1D() : Invalid trimming sizes."<<std::endl;
        ret = map;
    }
    return ret;
}

template<class T> T** trim2D(T**map, size_t nx, size_t ny, int x, int y, int cx, int cy)
{
    T**ret=0;
    if(x>=0 && x<=nx && y>=0 && y<=ny && cx>x && cx<nx && cy>y && cy<=ny)
    {
        T**ret=(T**)malloc(cy*sizeof(T*));
        for(int j=0; j<cy; j++)
        {
            ret[j] = (T*)malloc(cx*sizeof(T));
            for(int i=0; i<cx; i++)
                ret[j][i] = map[j+y][i+x];
        }
    }
    else
    {
        std::cout<<"From trimDouble2D() : Invalid trimming sizes."<<std::endl;
        ret = map;
    }
    return ret;
}

double fxi(double xi, double*cf, size_t P);
double* trimDouble1D(double*map, size_t nx, size_t ny, int x, int cx);
int* trimInt1D(int*map, size_t nx, size_t ny, int x, int cx);
char* trimDouble1D(char*map, size_t nx, size_t ny, int x, int cx);
double** trimDouble2D(double**map, size_t nx, size_t ny, int x, int y, int cx, int cy);
int** trimInt2D(int**map, size_t nx, size_t ny, int x, int y, int cx, int cy);
char** trimChar2D(char**map, size_t nx, size_t ny, int x, int y, int cx, int cy);
#endif /* UTILITIES_H_ */
