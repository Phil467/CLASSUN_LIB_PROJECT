/*
 * LinearAlgebra.h
 *
 *  Created on: 14 mai 2023
 *      Author: azphi
 */

#ifndef LINEARALGEBRA_H_
#define LINEARALGEBRA_H_

#include <iostream>
#include "jacobi.h"
#include "utilities.h"

double xPowSum(double*xarr, int n, double p);
double xPowSum2(double*xarr, int id1, int id2, double p);
double xPowDotYSum(double*xarr, double*yarr, int n, double p);
double xPowDotYSum2(double*xarr, double*yarr, int id1, int id2, double p);
double xPowDotYSum3(double*xarr, double*yarr, int id1, int id2, double p);
double* polynomialInterpolationCoefs(double*x, double*y, int n, int p);
double* polynomialInterpolationCoefs2(double*x, double*y, int id1, int id2, int p);
double* polynomialInterpolationCoefs3(double*x, double*y, int id1, int id2, int p);
void polynomialInterpolationCoefs3(double*x, double*y, int id1, int id2, double** cf, csPYRAMID_VARS* pv);

double* polynomialPrediction(double*x, double*y, int n, double p, double*xp, int m, double*& cf);


void pyramidalArrayIndexFunctionExample(unsigned int dimension);

double** descretePolynomialInterpolationCoefs1D(double* y, size_t n, size_t cell_length,
												size_t n_overlap, size_t polynom_degree,
												double*& y_out, size_t& n_out, size_t& n_coefs_cell);

void descretePolynomialInterpolationCoefs1D2(double* y, double**&coefs, size_t n, size_t cell_length,
												size_t n_overlap, size_t polynom_degree,
												size_t n_out, size_t n_coefs_cells);

double** getCoefsArray(size_t n, size_t n_overlap, size_t cell_length, size_t polynom_degree,
						size_t*n_coefs_cells, size_t* n_out);
void correctInterpolationSize(size_t n, size_t cell_length, size_t* cell_length_interp, size_t*n_interp, size_t dx);
double*descretePolynomialInterpolation1D(double**coefs, size_t n_coefs_cells, size_t polynom_degree,
										size_t cell_length, size_t n_overlap, size_t* cell_length_interp, size_t* n_interp);
void discreteInterpExample();

double** cellPolynomialInterpolation2D(double **x_interp, double **y_interp, size_t nx_interp, size_t ny_interp,
								size_t dx, size_t dy, size_t nx, size_t ny);
double**multilinePolynomialInterpolation(double**arr, size_t nx, size_t ny, size_t cell_length,
											size_t n_overlap, size_t polynom_degree, size_t dx,
											size_t* cell_length_interp, size_t* n_interp);
double**polynomialInterpolation2D(double**arr, size_t nx, size_t ny,
								size_t xcell_length, size_t ycell_length,
								size_t nx_overlap, size_t ny_overlap,
								size_t xpolynom_degree, size_t ypolynom_degree,
								size_t dx, size_t dy,
								size_t* nx_interp, size_t* ny_interp);

double** getReadyMap(double** map, size_t nx, size_t ny,
                    size_t xcell_length,size_t ycell_length,
					size_t nx_overlap, size_t ny_overlap,
					size_t* nx_out,size_t* ny_out);

double*** getUniDirDiscreteCoefs2D(double** map, size_t nx, size_t ny,size_t _nx, size_t _ny,
                    size_t cell_length,
					size_t nx_overlap,size_t ny_overlap, 
					size_t polynom_degree, size_t *n_cells_coefs, csPYRAMID_VARS*pv);

double polynomialCellPointValue2D(size_t x_dest,size_t y_dest, double** map_src, size_t nx_src, size_t ny_src, double*** x_coefs,
                                  double*** y_coefs, size_t nx_dest, size_t ny_dest,
                                  size_t xdegree, size_t ydegree, size_t xcell_length,
                                  size_t ycell_length, size_t nx_overlap, size_t ny_overlap);

double** getInterpolatedMap(double** map_src, size_t nx_src,
                          size_t ny_src, double*** x_coefs,
                          double*** y_coefs, size_t nx_dest, size_t ny_dest,
                          size_t xdegree, size_t ydegree, size_t xcell_length,
                          size_t ycell_length, size_t nx_overlap, size_t ny_overlap);
void test();
double** transpose(double**arr, size_t nx, size_t ny);
void interp2DExample();


#endif /* LINEARALGEBRA_H_ */
