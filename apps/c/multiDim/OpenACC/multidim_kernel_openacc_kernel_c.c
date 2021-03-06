//
// auto-generated by ops.py
//
#include "./OpenACC/multidim_common.h"

#define OPS_GPU

int xdim0_multidim_kernel;
int ydim0_multidim_kernel;

#undef OPS_ACC_MD0

#define OPS_ACC_MD0(d, x, y)                                                   \
  ((x) + (xdim0_multidim_kernel * (y)) +                                       \
   (d)*xdim0_multidim_kernel * ydim0_multidim_kernel)
// user function
inline void multidim_kernel(double *val, int *idx) {
  val[OPS_ACC_MD0(0, 0, 0)] = (double)(idx[0]);
  val[OPS_ACC_MD0(1, 0, 0)] = (double)(idx[1]);
}

#undef OPS_ACC_MD0

void multidim_kernel_c_wrapper(double *p_a0, int *p_a1, int arg_idx0,
                               int arg_idx1, int x_size, int y_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0)
#pragma acc loop
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      int arg_idx[] = {arg_idx0 + n_x, arg_idx1 + n_y};
      multidim_kernel(p_a0 + n_x * 1 + n_y * xdim0_multidim_kernel * 1,
                      arg_idx);
    }
  }
}
