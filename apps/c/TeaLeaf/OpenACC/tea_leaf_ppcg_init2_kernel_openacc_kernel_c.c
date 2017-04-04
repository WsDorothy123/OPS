//
// auto-generated by ops.py
//
#include "./OpenACC/tea_leaf_common.h"

#define OPS_GPU

int xdim0_tea_leaf_ppcg_init2_kernel;
int xdim1_tea_leaf_ppcg_init2_kernel;
int xdim2_tea_leaf_ppcg_init2_kernel;
int xdim3_tea_leaf_ppcg_init2_kernel;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3

#define OPS_ACC0(x, y) (x + xdim0_tea_leaf_ppcg_init2_kernel * (y))
#define OPS_ACC1(x, y) (x + xdim1_tea_leaf_ppcg_init2_kernel * (y))
#define OPS_ACC2(x, y) (x + xdim2_tea_leaf_ppcg_init2_kernel * (y))
#define OPS_ACC3(x, y) (x + xdim3_tea_leaf_ppcg_init2_kernel * (y))

// user function
inline void tea_leaf_ppcg_init2_kernel(double *sd, double *rtemp, double *utemp,
                                       const double *r, const double *theta_r) {
  sd[OPS_ACC0(0, 0)] = r[OPS_ACC3(0, 0)] * (*theta_r);
  rtemp[OPS_ACC1(0, 0)] = r[OPS_ACC3(0, 0)];
  utemp[OPS_ACC2(0, 0)] = sd[OPS_ACC0(0, 0)];
}

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3

void tea_leaf_ppcg_init2_kernel_c_wrapper(double *p_a0, double *p_a1,
                                          double *p_a2, double *p_a3,
                                          double p_a4, int x_size, int y_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1, p_a2, p_a3)
#pragma acc loop
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      tea_leaf_ppcg_init2_kernel(
          p_a0 + n_x * 1 * 1 + n_y * xdim0_tea_leaf_ppcg_init2_kernel * 1 * 1,
          p_a1 + n_x * 1 * 1 + n_y * xdim1_tea_leaf_ppcg_init2_kernel * 1 * 1,
          p_a2 + n_x * 1 * 1 + n_y * xdim2_tea_leaf_ppcg_init2_kernel * 1 * 1,
          p_a3 + n_x * 1 * 1 + n_y * xdim3_tea_leaf_ppcg_init2_kernel * 1 * 1,
          &p_a4);
    }
  }
}
