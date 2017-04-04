//
// auto-generated by ops.py
//
#include "./MPI_inline/tea_leaf_common.h"

int xdim0_tea_leaf_common_init_u_u0_kernel;
int xdim1_tea_leaf_common_init_u_u0_kernel;
int xdim2_tea_leaf_common_init_u_u0_kernel;
int xdim3_tea_leaf_common_init_u_u0_kernel;

#define OPS_ACC0(x, y)                                                         \
  (n_x * 1 + n_y * xdim0_tea_leaf_common_init_u_u0_kernel * 1 + x +            \
   xdim0_tea_leaf_common_init_u_u0_kernel * (y))
#define OPS_ACC1(x, y)                                                         \
  (n_x * 1 + n_y * xdim1_tea_leaf_common_init_u_u0_kernel * 1 + x +            \
   xdim1_tea_leaf_common_init_u_u0_kernel * (y))
#define OPS_ACC2(x, y)                                                         \
  (n_x * 1 + n_y * xdim2_tea_leaf_common_init_u_u0_kernel * 1 + x +            \
   xdim2_tea_leaf_common_init_u_u0_kernel * (y))
#define OPS_ACC3(x, y)                                                         \
  (n_x * 1 + n_y * xdim3_tea_leaf_common_init_u_u0_kernel * 1 + x +            \
   xdim3_tea_leaf_common_init_u_u0_kernel * (y))

// user function

void tea_leaf_common_init_u_u0_kernel_c_wrapper(double *restrict u,
                                                double *restrict u0,
                                                const double *restrict energy,
                                                const double *restrict density,
                                                int x_size, int y_size) {
#pragma omp parallel for
  for (int n_y = 0; n_y < y_size; n_y++) {
    for (int n_x = 0; n_x < x_size; n_x++) {

      u[OPS_ACC0(0, 0)] = energy[OPS_ACC2(0, 0)] * density[OPS_ACC3(0, 0)];
      u0[OPS_ACC1(0, 0)] = energy[OPS_ACC2(0, 0)] * density[OPS_ACC3(0, 0)];
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
