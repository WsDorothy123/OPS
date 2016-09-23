//
// auto-generated by ops.py
//
#include "./MPI_inline/clover_leaf_common.h"

int xdim0_reset_field_kernel1;
int ydim0_reset_field_kernel1;
int xdim1_reset_field_kernel1;
int ydim1_reset_field_kernel1;
int xdim2_reset_field_kernel1;
int ydim2_reset_field_kernel1;
int xdim3_reset_field_kernel1;
int ydim3_reset_field_kernel1;

#define OPS_ACC0(x,y,z) (n_x*1+n_y*xdim0_reset_field_kernel1*1+n_z*xdim0_reset_field_kernel1*ydim0_reset_field_kernel1*1+x+xdim0_reset_field_kernel1*(y)+xdim0_reset_field_kernel1*ydim0_reset_field_kernel1*(z))
#define OPS_ACC1(x,y,z) (n_x*1+n_y*xdim1_reset_field_kernel1*1+n_z*xdim1_reset_field_kernel1*ydim1_reset_field_kernel1*1+x+xdim1_reset_field_kernel1*(y)+xdim1_reset_field_kernel1*ydim1_reset_field_kernel1*(z))
#define OPS_ACC2(x,y,z) (n_x*1+n_y*xdim2_reset_field_kernel1*1+n_z*xdim2_reset_field_kernel1*ydim2_reset_field_kernel1*1+x+xdim2_reset_field_kernel1*(y)+xdim2_reset_field_kernel1*ydim2_reset_field_kernel1*(z))
#define OPS_ACC3(x,y,z) (n_x*1+n_y*xdim3_reset_field_kernel1*1+n_z*xdim3_reset_field_kernel1*ydim3_reset_field_kernel1*1+x+xdim3_reset_field_kernel1*(y)+xdim3_reset_field_kernel1*ydim3_reset_field_kernel1*(z))

//user function



void reset_field_kernel1_c_wrapper(
  double * restrict density0,
  const double * restrict density1,
  double * restrict energy0,
  const double * restrict energy1,
  int x_size, int y_size, int z_size) {
  #pragma omp parallel for
  for ( int n_z=0; n_z<z_size; n_z++ ){
    for ( int n_y=0; n_y<y_size; n_y++ ){
      for ( int n_x=0; n_x<x_size; n_x++ ){
        

  density0[OPS_ACC0(0,0,0)]  = density1[OPS_ACC1(0,0,0)] ;
  energy0[OPS_ACC2(0,0,0)]  = energy1[OPS_ACC3(0,0,0)] ;


      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
