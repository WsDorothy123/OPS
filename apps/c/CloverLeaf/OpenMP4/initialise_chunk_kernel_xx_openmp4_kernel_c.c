//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_initialise_chunk_kernel_xx;

#undef OPS_ACC0

#define OPS_ACC0(x, y) (x + xdim0_initialise_chunk_kernel_xx * (y))

// user function

void initialise_chunk_kernel_xx_c_wrapper(int *p_a0, int base0, int tot0,
                                          int *p_a1, int arg_idx0, int arg_idx1,
                                          int x_size, int y_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for num_teams(OPS_threads)        \
    thread_limit(OPS_threads_for_block) schedule(static, 1)
#endif
  for (int i = 0; i < y_size * x_size; i++) {
    int arg_idx[] = {arg_idx0 + i % x_size, arg_idx1 + i / x_size};
    int n_x = i % x_size;
    int n_y = i / x_size;
    int *xx = p_a0 + base0 + n_x * 1 * 1 +
              n_y * xdim0_initialise_chunk_kernel_xx * 0 * 1;

    int *idx = arg_idx;

    xx[OPS_ACC0(0, 0)] = idx[0] - 2;
  }
}
#undef OPS_ACC0