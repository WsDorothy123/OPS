//
// auto-generated by ops.py
//
#include "./MPI_inline/tea_leaf_common.h"

int xdim0_tea_leaf_recip3_kernel;
int xdim1_tea_leaf_recip3_kernel;

#define OPS_ACC0(x, y)                                                         \
  (n_x * 1 + n_y * xdim0_tea_leaf_recip3_kernel * 1 + x +                      \
   xdim0_tea_leaf_recip3_kernel * (y))
#define OPS_ACC1(x, y)                                                         \
  (n_x * 1 + n_y * xdim1_tea_leaf_recip3_kernel * 1 + x +                      \
   xdim1_tea_leaf_recip3_kernel * (y))

// user function

void tea_leaf_recip3_kernel_c_wrapper(double *restrict z,
                                      const double *restrict x,
                                      const double *restrict theta, int x_size,
                                      int y_size) {
#pragma omp parallel for
  for (int n_y = 0; n_y < y_size; n_y++) {
    for (int n_x = 0; n_x < x_size; n_x++) {

      z[OPS_ACC0(0, 0)] = x[OPS_ACC1(0, 0)] / (*theta);
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
