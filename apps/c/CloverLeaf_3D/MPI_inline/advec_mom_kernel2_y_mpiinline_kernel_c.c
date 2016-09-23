//
// auto-generated by ops.py
//
#include "./MPI_inline/clover_leaf_common.h"

int xdim0_advec_mom_kernel2_y;
int ydim0_advec_mom_kernel2_y;
int xdim1_advec_mom_kernel2_y;
int ydim1_advec_mom_kernel2_y;
int xdim2_advec_mom_kernel2_y;
int ydim2_advec_mom_kernel2_y;
int xdim3_advec_mom_kernel2_y;
int ydim3_advec_mom_kernel2_y;

#define OPS_ACC0(x,y,z) (n_x*1+n_y*xdim0_advec_mom_kernel2_y*1+n_z*xdim0_advec_mom_kernel2_y*ydim0_advec_mom_kernel2_y*1+x+xdim0_advec_mom_kernel2_y*(y)+xdim0_advec_mom_kernel2_y*ydim0_advec_mom_kernel2_y*(z))
#define OPS_ACC1(x,y,z) (n_x*1+n_y*xdim1_advec_mom_kernel2_y*1+n_z*xdim1_advec_mom_kernel2_y*ydim1_advec_mom_kernel2_y*1+x+xdim1_advec_mom_kernel2_y*(y)+xdim1_advec_mom_kernel2_y*ydim1_advec_mom_kernel2_y*(z))
#define OPS_ACC2(x,y,z) (n_x*1+n_y*xdim2_advec_mom_kernel2_y*1+n_z*xdim2_advec_mom_kernel2_y*ydim2_advec_mom_kernel2_y*1+x+xdim2_advec_mom_kernel2_y*(y)+xdim2_advec_mom_kernel2_y*ydim2_advec_mom_kernel2_y*(z))
#define OPS_ACC3(x,y,z) (n_x*1+n_y*xdim3_advec_mom_kernel2_y*1+n_z*xdim3_advec_mom_kernel2_y*ydim3_advec_mom_kernel2_y*1+x+xdim3_advec_mom_kernel2_y*(y)+xdim3_advec_mom_kernel2_y*ydim3_advec_mom_kernel2_y*(z))

//user function



void advec_mom_kernel2_y_c_wrapper(
  double * restrict vel1,
  const double * restrict node_mass_post,
  const double * restrict node_mass_pre,
  const double * restrict mom_flux,
  int x_size, int y_size, int z_size) {
  #pragma omp parallel for
  for ( int n_z=0; n_z<z_size; n_z++ ){
    for ( int n_y=0; n_y<y_size; n_y++ ){
      for ( int n_x=0; n_x<x_size; n_x++ ){
        

  vel1[OPS_ACC0(0,0,0)] = ( vel1[OPS_ACC0(0,0,0)] * node_mass_pre[OPS_ACC2(0,0,0)]  +
    mom_flux[OPS_ACC3(0,-1,0)] - mom_flux[OPS_ACC3(0,0,0)] ) / node_mass_post[OPS_ACC1(0,0,0)];

      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
