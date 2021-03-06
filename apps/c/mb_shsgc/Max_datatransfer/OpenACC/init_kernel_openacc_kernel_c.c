//
// auto-generated by ops.py
//
#include "./OpenACC/shsgc_common.h"

#define OPS_GPU

int xdim0_init_kernel;
int xdim1_init_kernel;
int xdim2_init_kernel;
int xdim3_init_kernel;
int xdim4_init_kernel;
int xdim5_init_kernel;
int xdim6_init_kernel;
int xdim7_init_kernel;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7

#define OPS_ACC0(x) (x)
#define OPS_ACC1(x) (x)
#define OPS_ACC2(x) (x)
#define OPS_ACC3(x) (x)
#define OPS_ACC4(x) (x)
#define OPS_ACC5(x) (x)
#define OPS_ACC6(x) (x)
#define OPS_ACC7(x) (x)

// user function
inline void init_kernel(const double *x, double *rho_new, double *rhou_new,
                        double *rhoE_new, double *rhoin, double *rho_old,
                        double *rhou_old, double *rhoE_old) {
  if (x[OPS_ACC0(0)] >= -4.0) {
    rho_new[OPS_ACC1(0)] = 1.0 + eps * sin(lambda * x[OPS_ACC0(0)]);
    rhou_new[OPS_ACC2(0)] = ur * rho_new[OPS_ACC1(0)];
    rhoE_new[OPS_ACC3(0)] =
        (pr / gam1) +
        0.5 * pow(rhou_new[OPS_ACC2(0)], 2) / rho_new[OPS_ACC1(0)];
  } else {
    rho_new[OPS_ACC1(0)] = rhol;
    rhou_new[OPS_ACC2(0)] = ul * rho_new[OPS_ACC1(0)];
    rhoE_new[OPS_ACC3(0)] =
        (pl / gam1) +
        0.5 * pow(rhou_new[OPS_ACC2(0)], 2) / rho_new[OPS_ACC1(0)];
  }
  rho_old[OPS_ACC5(0)] = rho_new[OPS_ACC1(0)];
  rhou_old[OPS_ACC6(0)] = rhou_new[OPS_ACC2(0)];
  rhoE_old[OPS_ACC7(0)] = rhoE_new[OPS_ACC3(0)];

  rhoin[OPS_ACC4(0)] = rho_new[OPS_ACC1(0)];
}

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7

void init_kernel_c_wrapper(double *p_a0, double *p_a1, double *p_a2,
                           double *p_a3, double *p_a4, double *p_a5,
                           double *p_a6, double *p_a7, int x_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1, p_a2, p_a3, p_a4, p_a5, p_a6, p_a7)
#pragma acc loop
#endif
  for (int n_x = 0; n_x < x_size; n_x++) {
    init_kernel(p_a0 + n_x * 1 * 1, p_a1 + n_x * 1 * 1, p_a2 + n_x * 1 * 1,
                p_a3 + n_x * 1 * 1, p_a4 + n_x * 1 * 1, p_a5 + n_x * 1 * 1,
                p_a6 + n_x * 1 * 1, p_a7 + n_x * 1 * 1);
  }
}
