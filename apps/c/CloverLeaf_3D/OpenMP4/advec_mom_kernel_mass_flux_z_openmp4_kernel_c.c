//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_advec_mom_kernel_mass_flux_z;
extern int ydim0_advec_mom_kernel_mass_flux_z;
extern int xdim1_advec_mom_kernel_mass_flux_z;
extern int ydim1_advec_mom_kernel_mass_flux_z;

#undef OPS_ACC0
#undef OPS_ACC1

#define OPS_ACC0(x, y, z)                                                      \
  (x + xdim0_advec_mom_kernel_mass_flux_z * (y) +                              \
   xdim0_advec_mom_kernel_mass_flux_z * ydim0_advec_mom_kernel_mass_flux_z *   \
       (z))
#define OPS_ACC1(x, y, z)                                                      \
  (x + xdim1_advec_mom_kernel_mass_flux_z * (y) +                              \
   xdim1_advec_mom_kernel_mass_flux_z * ydim1_advec_mom_kernel_mass_flux_z *   \
       (z))

// user function

void advec_mom_kernel_mass_flux_z_c_wrapper(double *p_a0, int base0, int tot0,
                                            double *p_a1, int base1, int tot1,
                                            int x_size, int y_size,
                                            int z_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for num_teams(OPS_threads)        \
    thread_limit(OPS_threads_for_block) collapse(3) schedule(static, 1)
#endif
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {
        double *node_flux = p_a0 + base0 + n_x * 1 * 1 +
                            n_y * xdim0_advec_mom_kernel_mass_flux_z * 1 * 1 +
                            n_z * xdim0_advec_mom_kernel_mass_flux_z *
                                ydim0_advec_mom_kernel_mass_flux_z * 1;

        const double *mass_flux_z =
            p_a1 + base1 + n_x * 1 * 1 +
            n_y * xdim1_advec_mom_kernel_mass_flux_z * 1 * 1 +
            n_z * xdim1_advec_mom_kernel_mass_flux_z *
                ydim1_advec_mom_kernel_mass_flux_z * 1;

        node_flux[OPS_ACC0(0, 0, 0)] =
            0.125 *
            (mass_flux_z[OPS_ACC1(-1, 0, 0)] + mass_flux_z[OPS_ACC1(0, 0, 0)] +
             mass_flux_z[OPS_ACC1(-1, 0, 1)] + mass_flux_z[OPS_ACC1(0, 0, 1)] +
             mass_flux_z[OPS_ACC1(-1, -1, 0)] +
             mass_flux_z[OPS_ACC1(0, -1, 0)] +
             mass_flux_z[OPS_ACC1(-1, -1, 1)] +
             mass_flux_z[OPS_ACC1(0, -1, 1)]);
      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1