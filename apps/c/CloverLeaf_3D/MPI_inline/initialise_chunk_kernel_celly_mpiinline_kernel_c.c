//
// auto-generated by ops.py
//
#include "./MPI_inline/clover_leaf_common.h"

int xdim0_initialise_chunk_kernel_celly;
int ydim0_initialise_chunk_kernel_celly;
int xdim1_initialise_chunk_kernel_celly;
int ydim1_initialise_chunk_kernel_celly;
int xdim2_initialise_chunk_kernel_celly;
int ydim2_initialise_chunk_kernel_celly;

#define OPS_ACC0(x,y,z) (n_x*0+n_y*xdim0_initialise_chunk_kernel_celly*1+n_z*xdim0_initialise_chunk_kernel_celly*ydim0_initialise_chunk_kernel_celly*0+x+xdim0_initialise_chunk_kernel_celly*(y)+xdim0_initialise_chunk_kernel_celly*ydim0_initialise_chunk_kernel_celly*(z))
#define OPS_ACC1(x,y,z) (n_x*0+n_y*xdim1_initialise_chunk_kernel_celly*1+n_z*xdim1_initialise_chunk_kernel_celly*ydim1_initialise_chunk_kernel_celly*0+x+xdim1_initialise_chunk_kernel_celly*(y)+xdim1_initialise_chunk_kernel_celly*ydim1_initialise_chunk_kernel_celly*(z))
#define OPS_ACC2(x,y,z) (n_x*0+n_y*xdim2_initialise_chunk_kernel_celly*1+n_z*xdim2_initialise_chunk_kernel_celly*ydim2_initialise_chunk_kernel_celly*0+x+xdim2_initialise_chunk_kernel_celly*(y)+xdim2_initialise_chunk_kernel_celly*ydim2_initialise_chunk_kernel_celly*(z))

//user function



void initialise_chunk_kernel_celly_c_wrapper(
  const double * restrict vertexy,
  double * restrict celly,
  double * restrict celldy,
  int x_size, int y_size, int z_size) {
  #pragma omp parallel for
  for ( int n_z=0; n_z<z_size; n_z++ ){
    for ( int n_y=0; n_y<y_size; n_y++ ){
      for ( int n_x=0; n_x<x_size; n_x++ ){
        
  double d_y = (grid.ymax - grid.ymin)/(double)grid.y_cells;
  celly[OPS_ACC1(0,0,0)]  = 0.5*( vertexy[OPS_ACC0(0,0,0)] + vertexy[OPS_ACC0(0,1,0)] );
  celldy[OPS_ACC2(0,0,0)]  = d_y;
  if(celldy[OPS_ACC2(0,0,0)] < 0) {


  }

      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
