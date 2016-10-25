//
// auto-generated by ops.py
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPS_2D
#include "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_tea_leaf_yeqx_kernel(char const *, ops_block, int, int *,
                                       ops_arg, ops_arg);

void ops_par_loop_tea_leaf_jacobi_kernel(char const *, ops_block, int, int *,
                                         ops_arg, ops_arg, ops_arg, ops_arg,
                                         ops_arg, ops_arg, ops_arg, ops_arg);

#include "data.h"
#include "definitions.h"

#include "tea_leaf.h"
#include "tea_leaf_jacobi_kernels.h"

void tea_leaf_init_zero2_kernel(double *p, double *z);
void tea_leaf_init_zero_kernel(double *p);
void tea_leaf_yeqx_kernel(double *p, const double *x);
void tea_leaf_yeqax_kernel(double *p, const double *x, const double *a);
void tea_leaf_dot_kernel(const double *r, const double *p, double *rro);
void tea_leaf_axpy_kernel(double *u, const double *p, const double *alpha);
void tea_leaf_axpby_kernel(double *u, const double *p, const double *alpha,
                           const double *beta);
void tea_leaf_zeqxty_kernel(double *z, const double *x, const double *y);
void tea_leaf_recip_kernel(double *u, const double *p);
void tea_leaf_recip2_kernel(double *z, const double *x, const double *y);
void tea_leaf_norm2_kernel(const double *x, double *norm);

void tea_leaf_jacobi_solve(double rx, double ry, ops_dat Kx, ops_dat Ky,
                           double *error, ops_dat u0, ops_dat u1, ops_dat un) {

  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;

  int rangexy[] = {x_min, x_max, y_min, y_max};

  *error = 0.0;

  ops_par_loop_tea_leaf_yeqx_kernel(
      "tea_leaf_yeqx_kernel", tea_grid, 2, rangexy,
      ops_arg_dat(un, 1, S2D_00, "double", OPS_WRITE),
      ops_arg_dat(u1, 1, S2D_00, "double", OPS_READ));

  ops_par_loop_tea_leaf_jacobi_kernel(
      "tea_leaf_jacobi_kernel", tea_grid, 2, rangexy,
      ops_arg_dat(u1, 1, S2D_00, "double", OPS_WRITE),
      ops_arg_dat(Kx, 1, S2D_00_P10, "double", OPS_READ),
      ops_arg_dat(Ky, 1, S2D_00_0P1, "double", OPS_READ),
      ops_arg_dat(un, 1, S2D_00_0M1_M10_P10_0P1, "double", OPS_READ),
      ops_arg_dat(u0, 1, S2D_00, "double", OPS_READ),
      ops_arg_gbl(&rx, 1, "double", OPS_READ),
      ops_arg_gbl(&ry, 1, "double", OPS_READ),
      ops_arg_reduce(red_temp, 1, "double", OPS_INC));

  ops_reduction_result(red_temp, error);
}
