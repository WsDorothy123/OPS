//
// auto-generated by ops.py
//
#include "./MPI_inline/tea_leaf_common.h"

int xdim0_tea_leaf_jacobi_kernel;
int xdim1_tea_leaf_jacobi_kernel;
int xdim2_tea_leaf_jacobi_kernel;
int xdim3_tea_leaf_jacobi_kernel;
int xdim4_tea_leaf_jacobi_kernel;

#define OPS_ACC0(x, y)                                                         \
  (n_x * 1 + n_y * xdim0_tea_leaf_jacobi_kernel * 1 + x +                      \
   xdim0_tea_leaf_jacobi_kernel * (y))
#define OPS_ACC1(x, y)                                                         \
  (n_x * 1 + n_y * xdim1_tea_leaf_jacobi_kernel * 1 + x +                      \
   xdim1_tea_leaf_jacobi_kernel * (y))
#define OPS_ACC2(x, y)                                                         \
  (n_x * 1 + n_y * xdim2_tea_leaf_jacobi_kernel * 1 + x +                      \
   xdim2_tea_leaf_jacobi_kernel * (y))
#define OPS_ACC3(x, y)                                                         \
  (n_x * 1 + n_y * xdim3_tea_leaf_jacobi_kernel * 1 + x +                      \
   xdim3_tea_leaf_jacobi_kernel * (y))
#define OPS_ACC4(x, y)                                                         \
  (n_x * 1 + n_y * xdim4_tea_leaf_jacobi_kernel * 1 + x +                      \
   xdim4_tea_leaf_jacobi_kernel * (y))

// user function

void tea_leaf_jacobi_kernel_c_wrapper(
    double *restrict u1, const double *restrict Kx, const double *restrict Ky,
    const double *restrict un, const double *restrict u0, const double rx,
    const double ry, double *restrict error_g, int x_size, int y_size) {
  double error_v = *error_g;
#pragma omp parallel for reduction(+ : error_v)
  for (int n_y = 0; n_y < y_size; n_y++) {
    for (int n_x = 0; n_x < x_size; n_x++) {
      double *restrict error = &error_v;

      u1[OPS_ACC0(0, 0)] =
          (u0[OPS_ACC4(0, 0)] +
           (*rx) * (Kx[OPS_ACC1(1, 0)] * un[OPS_ACC3(1, 0)] +
                    Kx[OPS_ACC1(0, 0)] * un[OPS_ACC3(-1, 0)]) +
           (*ry) * (Ky[OPS_ACC2(0, 1)] * un[OPS_ACC3(0, 1)] +
                    Ky[OPS_ACC2(0, 0)] * un[OPS_ACC3(0, -1)])) /
          (1.0 + (*rx) * (Kx[OPS_ACC1(1, 0)] + Kx[OPS_ACC1(0, 0)]) +
           (*ry) * (Ky[OPS_ACC2(0, 1)] + Ky[OPS_ACC2(0, 0)]));

      *error = *error + fabs(u1[OPS_ACC0(0, 0)] - un[OPS_ACC3(0, 0)]);
    }
  }
  *error_g = error_v;
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
