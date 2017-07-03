//
// auto-generated by ops.py
//
#include "./OpenMP4/tea_leaf_common.h"

#define OPS_GPU

extern int xdim0_tea_leaf_common_init_Kx_Ky_kernel;
extern int xdim1_tea_leaf_common_init_Kx_Ky_kernel;
extern int xdim2_tea_leaf_common_init_Kx_Ky_kernel;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2

#define OPS_ACC0(x, y) (x + xdim0_tea_leaf_common_init_Kx_Ky_kernel * (y))
#define OPS_ACC1(x, y) (x + xdim1_tea_leaf_common_init_Kx_Ky_kernel * (y))
#define OPS_ACC2(x, y) (x + xdim2_tea_leaf_common_init_Kx_Ky_kernel * (y))

// user function

void tea_leaf_common_init_Kx_Ky_kernel_c_wrapper(
    double *p_a0, int base0, int tot0, double *p_a1, int base1, int tot1,
    double *p_a2, int base2, int tot2, int x_size, int y_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for num_teams(OPS_threads)        \
    thread_limit(OPS_threads_for_block) schedule(static, 1)
#endif
  for (int i = 0; i < y_size * x_size; i++) {
    int n_x = i % x_size;
    int n_y = i / x_size;
    double *Kx = p_a0 + base0 + n_x * 1 * 1 +
                 n_y * xdim0_tea_leaf_common_init_Kx_Ky_kernel * 1 * 1;

    double *Ky = p_a1 + base1 + n_x * 1 * 1 +
                 n_y * xdim1_tea_leaf_common_init_Kx_Ky_kernel * 1 * 1;
    const double *w = p_a2 + base2 + n_x * 1 * 1 +
                      n_y * xdim2_tea_leaf_common_init_Kx_Ky_kernel * 1 * 1;

    Kx[OPS_ACC0(0, 0)] = (w[OPS_ACC2(-1, 0)] + w[OPS_ACC2(0, 0)]) /
                         (2.0 * w[OPS_ACC2(-1, 0)] * w[OPS_ACC2(0, 0)]);
    Ky[OPS_ACC1(0, 0)] = (w[OPS_ACC2(0, -1)] + w[OPS_ACC2(0, 0)]) /
                         (2.0 * w[OPS_ACC2(0, -1)] * w[OPS_ACC2(0, 0)]);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2