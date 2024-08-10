/*
 * colorbar.cpp
 *
 *  Created on: 13 mai 2023
 *      Author: azphi
 */

#include "utilities.h"
#include "colorbar.h"

void RGBAChanelsArrayWeigthedColor(double**singular_color, double*weight, size_t n, size_t cb_length,
									double**&rgba)
{
	rgba = (double**)malloc(n*sizeof(double*));
	for(size_t i=0; i<n; i++)
	{
		rgba[i] = (double*)malloc(cb_length*sizeof(double));
	}
	size_t pos = 0;
	for(size_t i=0; i<n; i++)
	{
		for(size_t j=0; j<size_t(weight[i]); j++)
		{
			rgba[0][pos] = (singular_color[0][i]);
			rgba[1][pos] = (singular_color[1][i]);
			rgba[2][pos] = (singular_color[2][i]);
			rgba[3][pos] = (singular_color[3][i]);
			pos++;
		}
	}
}

void discreteColors(double**singular_color, double*weight, size_t n, size_t& cb_length,
					double map_minval, double map_maxval, double**&rgba, double*&map_equivalence)
{
	double total_weight = sum(weight, n), ratio = cb_length/total_weight;
	double* weight2 = arrayBoost(weight, n, ratio);
	arrayRound2(weight2, n, 0);
	cb_length = (size_t)sum(weight2, n);
	RGBAChanelsArrayWeigthedColor(singular_color, weight2, n, cb_length,
										rgba);
	map_equivalence = linspace(map_minval, map_maxval, cb_length);
}

void smoothedColors(double**singular_color,
					size_t cb_length,
					size_t polynom_degree,
					size_t dx,
					double map_minval, double map_maxval, double**&rgba, double*&map_equivalence)
{
	size_t cell_length = 2, n_overlap = 2;
	size_t n_interp = 0, cell_length_interp = 0;
	rgba = multilinePolynomialInterpolation(rgba, cb_length, 4, cell_length,
													n_overlap, polynom_degree, dx,
													&cell_length_interp, &n_interp);
	printArray2D(rgba, n_interp, 4, "rgba (smoothed) :", 9);
}

void mapToDiscreteRGBMap(double**map, size_t nx, size_t ny, double**cb_rgba,
						double*map_equivalence, size_t cb_length, char*&map_out)
{
	size_t pos=0;
	size_t n = cb_length-1;
	if (n<2)
	{
		cout<<"Error message from mapToDiscreteRGBMap(): \n cb_length must be greater or equal than 2!\n\n";
		exit(0);
	}
	for(size_t j=0; j<ny; j++)
	{
		for(size_t i=0; i<nx; i++)
		{
			pos = (j*nx + i)*4;
			for(size_t k=0; k<n; k++)
			{
				if(map[j][i] >= map_equivalence[k] && map[j][i] < map_equivalence[k+1])
					setStrRGB2(map_out, pos, size_t(cb_rgba[0][k]),size_t(cb_rgba[1][k]),size_t(cb_rgba[2][k]));
			}
		}
	}
}

void mapToDiscreteUIntMap(double**map, size_t nx, size_t ny, double**cb_rgba,
						double*map_equivalence, size_t cb_length, size_t**&map_out)
{
	size_t pos=0;
	size_t n = cb_length-1;
	for(size_t j=0; j<ny; j++)
	{
		for(size_t i=0; i<nx; i++)
		{
			pos = (j*nx + i)*4;
			for(size_t k=0; k<n; k++)
			{
				if(map[j][i] >= map_equivalence[k] && map[j][i] <= map_equivalence[k+1])
					map_out[j][i] = (size_t(cb_rgba[2][k])<<16)|(size_t(cb_rgba[1][k])<<8)|size_t(cb_rgba[0][k]);
			}
		}
	}
}


void colorbarExample()
{
	size_t cb_length = 50, n = 10, dx=4, nx=50, ny=50;
	double map_minval = 0, map_maxval=0;
	double**rgba=0, *map_equivalence=0;
	double**singular_color = getRandomDoubleArray2D(n, 4, 0, 255, 0);
	double*weight = getRandomDoubleArray1D(n, 2, 10, 0);
	double**map = getRandomDoubleArray2D(nx, ny, -5, 5, 0);

	minmax2D(map, nx, ny, map_minval, map_maxval);

	printArray2D(map, nx, ny, "map :", 6);
	printArray2D(singular_color, n, 4, "colorbar - singular_color :", 6);
	printArray1D(weight, n, "colorbar - weight :", 6);
	discreteColors(singular_color, weight, n,
							cb_length,
							map_minval, map_maxval, rgba, map_equivalence);
	printArray2D(rgba, cb_length, 4, "colorbar - rgba (discrete) :", 6);
	printArray1D(map_equivalence, cb_length, "colorbar - map_equivalence :", 9);

	//char*map_out = (char*)malloc(nx*ny*4);
	//mapToDiscreteRGBMap(map, nx, ny, rgba, map_equivalence, cb_length, map_out);
	size_t** map_out = fullUInt2D(nx, ny, 0);
	mapToDiscreteUIntMap(map, nx, ny, rgba, map_equivalence, cb_length, map_out);
	printArray2D(map_out, nx, ny, "map_out (discrete) :", 10);
}



















