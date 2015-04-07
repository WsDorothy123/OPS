//
// auto-generated by ops.py
//
#include "./OpenACC/clover_leaf_common.h"

//#define OPS_GPU

int xdim0_advec_mom_kernel_mass_flux_z;
int ydim0_advec_mom_kernel_mass_flux_z;
int xdim1_advec_mom_kernel_mass_flux_z;
int ydim1_advec_mom_kernel_mass_flux_z;

#define OPS_ACC0(x,y,z) (x+xdim0_advec_mom_kernel_mass_flux_z*(y)+xdim0_advec_mom_kernel_mass_flux_z*ydim0_advec_mom_kernel_mass_flux_z*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_advec_mom_kernel_mass_flux_z*(y)+xdim1_advec_mom_kernel_mass_flux_z*ydim1_advec_mom_kernel_mass_flux_z*(z))

//user function

inline void advec_mom_kernel_mass_flux_z( double *node_flux, const double *mass_flux_z) {


  node_flux[OPS_ACC0(0,0,0)] = 0.125 * ( mass_flux_z[OPS_ACC1(-1,0,0)] + mass_flux_z[OPS_ACC1(0,0,0)] +
                                         mass_flux_z[OPS_ACC1(-1,0,1)] + mass_flux_z[OPS_ACC1(0,0,1)] +
                                         mass_flux_z[OPS_ACC1(-1,-1,0)] + mass_flux_z[OPS_ACC1(0,-1,0)] +
                                         mass_flux_z[OPS_ACC1(-1,-1,1)] + mass_flux_z[OPS_ACC1(0,-1,1)] );
}


#undef OPS_ACC0
#undef OPS_ACC1



void advec_mom_kernel_mass_flux_z_c_wrapper(
  double *p_a0,
  double *p_a1,
  int x_size, int y_size, int z_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1)
  #pragma acc loop
  #endif
  for ( int n_z=0; n_z<z_size; n_z++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_y=0; n_y<y_size; n_y++ ){
      #ifdef OPS_GPU
      #pragma acc loop
      #endif
      for ( int n_x=0; n_x<x_size; n_x++ ){
        advec_mom_kernel_mass_flux_z(  p_a0 + n_x*1*1 + n_y*xdim0_advec_mom_kernel_mass_flux_z*1*1 + n_z*xdim0_advec_mom_kernel_mass_flux_z*ydim0_advec_mom_kernel_mass_flux_z*1,
           p_a1 + n_x*1*1 + n_y*xdim1_advec_mom_kernel_mass_flux_z*1*1 + n_z*xdim1_advec_mom_kernel_mass_flux_z*ydim1_advec_mom_kernel_mass_flux_z*1 );

      }
    }
  }
}