//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_advec_cell_kernel3_ydir;
extern int xdim1_advec_cell_kernel3_ydir;
extern int xdim2_advec_cell_kernel3_ydir;
extern int xdim3_advec_cell_kernel3_ydir;
extern int xdim4_advec_cell_kernel3_ydir;
extern int xdim5_advec_cell_kernel3_ydir;
extern int xdim6_advec_cell_kernel3_ydir;
extern int xdim7_advec_cell_kernel3_ydir;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7

#define OPS_ACC0(x, y) (x + xdim0_advec_cell_kernel3_ydir * (y))
#define OPS_ACC1(x, y) (x + xdim1_advec_cell_kernel3_ydir * (y))
#define OPS_ACC2(x, y) (x + xdim2_advec_cell_kernel3_ydir * (y))
#define OPS_ACC3(x, y) (x + xdim3_advec_cell_kernel3_ydir * (y))
#define OPS_ACC4(x, y) (x + xdim4_advec_cell_kernel3_ydir * (y))
#define OPS_ACC5(x, y) (x + xdim5_advec_cell_kernel3_ydir * (y))
#define OPS_ACC6(x, y) (x + xdim6_advec_cell_kernel3_ydir * (y))
#define OPS_ACC7(x, y) (x + xdim7_advec_cell_kernel3_ydir * (y))

// user function

void advec_cell_kernel3_ydir_c_wrapper(
    double *p_a0, int base0, int tot0, double *p_a1, int base1, int tot1,
    int *p_a2, int base2, int tot2, double *p_a3, int base3, int tot3,
    double *p_a4, int base4, int tot4, double *p_a5, int base5, int tot5,
    double *p_a6, int base6, int tot6, double *p_a7, int base7, int tot7,
    int x_size, int y_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for num_teams(OPS_threads)        \
    thread_limit(OPS_threads_for_block) schedule(static, 1)
#endif
  for (int i = 0; i < y_size * x_size; i++) {
    int n_x = i % x_size;
    int n_y = i / x_size;
    const double *vol_flux_y = p_a0 + base0 + n_x * 1 * 1 +
                               n_y * xdim0_advec_cell_kernel3_ydir * 1 * 1;

    const double *pre_vol = p_a1 + base1 + n_x * 1 * 1 +
                            n_y * xdim1_advec_cell_kernel3_ydir * 1 * 1;
    const int *yy = p_a2 + base2 + n_x * 0 * 1 +
                    n_y * xdim2_advec_cell_kernel3_ydir * 1 * 1;

    const double *vertexdy = p_a3 + base3 + n_x * 0 * 1 +
                             n_y * xdim3_advec_cell_kernel3_ydir * 1 * 1;
    const double *density1 = p_a4 + base4 + n_x * 1 * 1 +
                             n_y * xdim4_advec_cell_kernel3_ydir * 1 * 1;

    const double *energy1 = p_a5 + base5 + n_x * 1 * 1 +
                            n_y * xdim5_advec_cell_kernel3_ydir * 1 * 1;
    double *mass_flux_y = p_a6 + base6 + n_x * 1 * 1 +
                          n_y * xdim6_advec_cell_kernel3_ydir * 1 * 1;

    double *ener_flux = p_a7 + base7 + n_x * 1 * 1 +
                        n_y * xdim7_advec_cell_kernel3_ydir * 1 * 1;

    double sigmat, sigmav, sigmam, sigma3, sigma4;
    double diffuw, diffdw, limiter;
    double one_by_six = 1.0 / 6.0;

    int y_max = field.y_max;

    int upwind, donor, downwind, dif;

    if (vol_flux_y[OPS_ACC0(0, 0)] > 0.0) {
      upwind = -2;
      donor = -1;
      downwind = 0;
      dif = donor;
    } else if (yy[OPS_ACC2(0, 1)] < y_max + 2 - 2) {
      upwind = 1;
      donor = 0;
      downwind = -1;
      dif = upwind;
    } else {
      upwind = 0;
      donor = 0;
      downwind = -1;
      dif = upwind;
    }

    sigmat = fabs(vol_flux_y[OPS_ACC0(0, 0)]) / pre_vol[OPS_ACC1(0, donor)];
    sigma3 = (1.0 + sigmat) *
             (vertexdy[OPS_ACC3(0, 0)] / vertexdy[OPS_ACC3(0, dif)]);
    sigma4 = 2.0 - sigmat;

    sigmav = sigmat;

    diffuw = density1[OPS_ACC4(0, donor)] - density1[OPS_ACC4(0, upwind)];
    diffdw = density1[OPS_ACC4(0, downwind)] - density1[OPS_ACC4(0, donor)];

    if ((diffuw * diffdw) > 0.0)
      limiter =
          (1.0 - sigmav) * SIGN(1.0, diffdw) *
          MIN(MIN(fabs(diffuw), fabs(diffdw)),
              one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
    else
      limiter = 0.0;

    mass_flux_y[OPS_ACC6(0, 0)] =
        (vol_flux_y[OPS_ACC0(0, 0)]) * (density1[OPS_ACC4(0, donor)] + limiter);

    sigmam = fabs(mass_flux_y[OPS_ACC6(0, 0)]) /
             (density1[OPS_ACC4(0, donor)] * pre_vol[OPS_ACC1(0, donor)]);
    diffuw = energy1[OPS_ACC5(0, donor)] - energy1[OPS_ACC5(0, upwind)];
    diffdw = energy1[OPS_ACC5(0, downwind)] - energy1[OPS_ACC5(0, donor)];

    if ((diffuw * diffdw) > 0.0)
      limiter =
          (1.0 - sigmam) * SIGN(1.0, diffdw) *
          MIN(MIN(fabs(diffuw), fabs(diffdw)),
              one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
    else
      limiter = 0.0;

    ener_flux[OPS_ACC7(0, 0)] =
        mass_flux_y[OPS_ACC6(0, 0)] * (energy1[OPS_ACC5(0, donor)] + limiter);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7