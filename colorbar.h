/*
 * colorbar.h
 *
 *  Created on: 14 mai 2023
 *      Author: azphi
 */

#ifndef COLORBAR_H_
#define COLORBAR_H_

#include "LinearAlgebra.h"

void RGBAChanelsArrayWeigthedColor(double**singular_color, double*weight, size_t n, size_t cb_length,
									double**&rgba);
void discreteColors(double**singular_color, double*weight, size_t n, size_t& cb_length,
					double minval, double maxval, double**&rgba, double*&equivalence);
void smoothedColors(double**singular_color,
					size_t cb_length,
					size_t polynom_degree,
					size_t dx,
					double map_minval, double map_maxval, double**&rgba, double*&map_equivalence);
void mapToDiscreteRGBMap(double**map, size_t nx, size_t ny, double**cb_rgba,
						double*map_equivalence, size_t cb_length, char*&map_out);
void mapToDiscreteUIntMap(double**map, size_t nx, size_t ny, double**cb_rgba,
						double*map_equivalence, size_t cb_length, size_t**&map_out);


void colorbarExample();

#endif /* COLORBAR_H_ */
