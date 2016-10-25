//
// auto-generated by ops.py
//
#include "./MPI_inline/tea_leaf_common.h"

int xdim0_field_summary_kernel;
int xdim1_field_summary_kernel;
int xdim2_field_summary_kernel;
int xdim3_field_summary_kernel;

#define OPS_ACC0(x, y)                                                         \
  (n_x * 1 + n_y * xdim0_field_summary_kernel * 1 + x +                        \
   xdim0_field_summary_kernel * (y))
#define OPS_ACC1(x, y)                                                         \
  (n_x * 1 + n_y * xdim1_field_summary_kernel * 1 + x +                        \
   xdim1_field_summary_kernel * (y))
#define OPS_ACC2(x, y)                                                         \
  (n_x * 1 + n_y * xdim2_field_summary_kernel * 1 + x +                        \
   xdim2_field_summary_kernel * (y))
#define OPS_ACC3(x, y)                                                         \
  (n_x * 1 + n_y * xdim3_field_summary_kernel * 1 + x +                        \
   xdim3_field_summary_kernel * (y))

// user function

void field_summary_kernel_c_wrapper(
    const double *restrict volume, const double *restrict density,
    const double *restrict energy, const double *restrict u,
    double *restrict vol_g, double *restrict mass_g, double *restrict ie_g,
    double *restrict temp_g, int x_size, int y_size) {
  double vol_v = *vol_g;
  double mass_v = *mass_g;
  double ie_v = *ie_g;
  double temp_v = *temp_g;
#pragma omp parallel for reduction(+ : vol_v) reduction(+ : mass_v) reduction( \
    + : ie_v) reduction(+ : temp_v)
  for (int n_y = 0; n_y < y_size; n_y++) {
    for (int n_x = 0; n_x < x_size; n_x++) {
      double *restrict vol = &vol_v;
      double *restrict mass = &mass_v;
      double *restrict ie = &ie_v;
      double *restrict temp = &temp_v;

      double cell_vol, cell_mass;

      cell_vol = volume[OPS_ACC0(0, 0)];
      cell_mass = cell_vol * density[OPS_ACC1(0, 0)];
      *vol = *vol + cell_vol;
      *mass = *mass + cell_mass;
      *ie = *ie + cell_mass * energy[OPS_ACC2(0, 0)];
      *temp = *temp + cell_mass * u[OPS_ACC3(0, 0)];
    }
  }
  *vol_g = vol_v;
  *mass_g = mass_v;
  *ie_g = ie_v;
  *temp_g = temp_v;
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
