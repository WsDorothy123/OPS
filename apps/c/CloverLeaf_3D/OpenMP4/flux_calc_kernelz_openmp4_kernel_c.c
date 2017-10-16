//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_flux_calc_kernelz;
extern int ydim0_flux_calc_kernelz;
extern int xdim1_flux_calc_kernelz;
extern int ydim1_flux_calc_kernelz;
extern int xdim2_flux_calc_kernelz;
extern int ydim2_flux_calc_kernelz;
extern int xdim3_flux_calc_kernelz;
extern int ydim3_flux_calc_kernelz;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3

#define OPS_ACC0(x, y, z)                                                      \
  (x + xdim0_flux_calc_kernelz * (y) +                                         \
   xdim0_flux_calc_kernelz * ydim0_flux_calc_kernelz * (z))
#define OPS_ACC1(x, y, z)                                                      \
  (x + xdim1_flux_calc_kernelz * (y) +                                         \
   xdim1_flux_calc_kernelz * ydim1_flux_calc_kernelz * (z))
#define OPS_ACC2(x, y, z)                                                      \
  (x + xdim2_flux_calc_kernelz * (y) +                                         \
   xdim2_flux_calc_kernelz * ydim2_flux_calc_kernelz * (z))
#define OPS_ACC3(x, y, z)                                                      \
  (x + xdim3_flux_calc_kernelz * (y) +                                         \
   xdim3_flux_calc_kernelz * ydim3_flux_calc_kernelz * (z))

// user function

void flux_calc_kernelz_c_wrapper(double *p_a0, int base0, int tot0,
                                 double *p_a1, int base1, int tot1,
                                 double *p_a2, int base2, int tot2,
                                 double *p_a3, int base3, int tot3, int x_size,
                                 int y_size, int z_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for num_teams(OPS_threads)        \
    thread_limit(OPS_threads_for_block) collapse(3) schedule(static, 1)
#endif
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {
        double *vol_flux_z =
            p_a0 + base0 + n_x * 1 * 1 + n_y * xdim0_flux_calc_kernelz * 1 * 1 +
            n_z * xdim0_flux_calc_kernelz * ydim0_flux_calc_kernelz * 1;

        const double *zarea =
            p_a1 + base1 + n_x * 1 * 1 + n_y * xdim1_flux_calc_kernelz * 1 * 1 +
            n_z * xdim1_flux_calc_kernelz * ydim1_flux_calc_kernelz * 1;

        const double *zvel0 =
            p_a2 + base2 + n_x * 1 * 1 + n_y * xdim2_flux_calc_kernelz * 1 * 1 +
            n_z * xdim2_flux_calc_kernelz * ydim2_flux_calc_kernelz * 1;

        const double *zvel1 =
            p_a3 + base3 + n_x * 1 * 1 + n_y * xdim3_flux_calc_kernelz * 1 * 1 +
            n_z * xdim3_flux_calc_kernelz * ydim3_flux_calc_kernelz * 1;

        vol_flux_z[OPS_ACC0(0, 0, 0)] =
            0.125 * dt * (zarea[OPS_ACC1(0, 0, 0)]) *
            (zvel0[OPS_ACC2(0, 0, 0)] + zvel0[OPS_ACC2(1, 0, 0)] +
             zvel0[OPS_ACC2(1, 0, 0)] + zvel0[OPS_ACC2(1, 1, 0)] +
             zvel1[OPS_ACC3(0, 0, 0)] + zvel1[OPS_ACC3(1, 0, 0)] +
             zvel1[OPS_ACC3(0, 1, 0)] + zvel1[OPS_ACC3(1, 1, 0)]);
      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3