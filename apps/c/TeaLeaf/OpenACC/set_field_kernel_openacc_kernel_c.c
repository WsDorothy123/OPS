//
// auto-generated by ops.py
//
#include "./OpenACC/tea_leaf_common.h"

#define OPS_GPU

int xdim0_set_field_kernel;
int xdim1_set_field_kernel;

#undef OPS_ACC0
#undef OPS_ACC1

#define OPS_ACC0(x, y) (x + xdim0_set_field_kernel * (y))
#define OPS_ACC1(x, y) (x + xdim1_set_field_kernel * (y))

// user function
inline void set_field_kernel(const double *energy0, double *energy1) {
  energy1[OPS_ACC1(0, 0)] = energy0[OPS_ACC0(0, 0)];
}

#undef OPS_ACC0
#undef OPS_ACC1

void set_field_kernel_c_wrapper(double *p_a0, double *p_a1, int x_size,
                                int y_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1)
#pragma acc loop
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      set_field_kernel(
          p_a0 + n_x * 1 * 1 + n_y * xdim0_set_field_kernel * 1 * 1,
          p_a1 + n_x * 1 * 1 + n_y * xdim1_set_field_kernel * 1 * 1);
    }
  }
}
