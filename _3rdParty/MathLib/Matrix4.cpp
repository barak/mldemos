/*
 * Copyright (C) 2010 Learning Algorithms and Systems Laboratory, EPFL, Switzerland
 * Author: Eric Sauser
 * email:   eric.sauser@a3.epf.ch
 * website: lasa.epfl.ch
 *
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */

#include "Matrix4.h"
#ifdef USE_MATHLIB_NAMESPACE
using namespace MathLib;
#endif

const Matrix4 Matrix4::ZERO(
	R_ZERO, R_ZERO, R_ZERO, R_ZERO,
	R_ZERO, R_ZERO, R_ZERO, R_ZERO,
	R_ZERO, R_ZERO, R_ZERO, R_ZERO,
	R_ZERO, R_ZERO, R_ZERO, R_ZERO);

const Matrix4 Matrix4::IDENTITY(
	R_ONE , R_ZERO, R_ZERO, R_ZERO,
	R_ZERO, R_ONE , R_ZERO, R_ZERO,
	R_ZERO, R_ZERO, R_ONE , R_ZERO,
	R_ZERO, R_ZERO, R_ZERO, R_ONE );

