//
// auto-generated by ops.py
//
#include "./MPI_inline/tea_leaf_common.h"

int xdim0_tea_leaf_common_init_Kx_Ky_kernel;
int xdim1_tea_leaf_common_init_Kx_Ky_kernel;
int xdim2_tea_leaf_common_init_Kx_Ky_kernel;

#define OPS_ACC0(x, y)                                                         \
  (n_x * 1 + n_y * xdim0_tea_leaf_common_init_Kx_Ky_kernel * 1 + x +           \
   xdim0_tea_leaf_common_init_Kx_Ky_kernel * (y))
#define OPS_ACC1(x, y)                                                         \
  (n_x * 1 + n_y * xdim1_tea_leaf_common_init_Kx_Ky_kernel * 1 + x +           \
   xdim1_tea_leaf_common_init_Kx_Ky_kernel * (y))
#define OPS_ACC2(x, y)                                                         \
  (n_x * 1 + n_y * xdim2_tea_leaf_common_init_Kx_Ky_kernel * 1 + x +           \
   xdim2_tea_leaf_common_init_Kx_Ky_kernel * (y))

// user function

void tea_leaf_common_init_Kx_Ky_kernel_c_wrapper(double *restrict Kx,
                                                 double *restrict Ky,
                                                 const double *restrict w,
                                                 int x_size, int y_size) {
#pragma omp parallel for
  for (int n_y = 0; n_y < y_size; n_y++) {
    for (int n_x = 0; n_x < x_size; n_x++) {

      Kx[OPS_ACC0(0, 0)] = (w[OPS_ACC2(-1, 0)] + w[OPS_ACC2(0, 0)]) /
                           (2.0 * w[OPS_ACC2(-1, 0)] * w[OPS_ACC2(0, 0)]);
      Ky[OPS_ACC1(0, 0)] = (w[OPS_ACC2(0, -1)] + w[OPS_ACC2(0, 0)]) /
                           (2.0 * w[OPS_ACC2(0, -1)] * w[OPS_ACC2(0, 0)]);
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
