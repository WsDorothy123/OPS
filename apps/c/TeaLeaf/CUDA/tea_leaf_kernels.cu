//
// auto-generated by ops.py//

//header
#define OPS_ACC_MD_MACROS
#define OPS_2D
#include "ops_lib_cpp.h"

#include "ops_cuda_rt_support.h"
#include "ops_cuda_reduction.h"

#include <cuComplex.h>

#include "user_types.h"
#ifdef OPS_MPI
#include "ops_mpi_core.h"
#endif
// global constants
__constant__ field_type field;
__constant__ grid_type grid;
__constant__ int number_of_states;
__constant__ state_type *states;
__constant__ int g_circ;
__constant__ int g_point;
__constant__ int g_rect;

void ops_decl_const_char(int dim, char const *type,
int size, char *dat, char const *name){
  if (!strcmp(name,"field")) {
    cutilSafeCall(cudaMemcpyToSymbol(field, dat, dim*size));
  }
  else
  if (!strcmp(name,"grid")) {
    cutilSafeCall(cudaMemcpyToSymbol(grid, dat, dim*size));
  }
  else
  if (!strcmp(name,"number_of_states")) {
    cutilSafeCall(cudaMemcpyToSymbol(number_of_states, dat, dim*size));
  }
  else
  if (!strcmp(name,"states")) {
    char *temp; cutilSafeCall(cudaMalloc((void**)&temp,dim*size));
    cutilSafeCall(cudaMemcpy(temp,dat,dim*size,cudaMemcpyHostToDevice));
    cutilSafeCall(cudaMemcpyToSymbol(states, &temp, sizeof(char *)));
  }
  else
  if (!strcmp(name,"g_circ")) {
    cutilSafeCall(cudaMemcpyToSymbol(g_circ, dat, dim*size));
  }
  else
  if (!strcmp(name,"g_point")) {
    cutilSafeCall(cudaMemcpyToSymbol(g_point, dat, dim*size));
  }
  else
  if (!strcmp(name,"g_rect")) {
    cutilSafeCall(cudaMemcpyToSymbol(g_rect, dat, dim*size));
  }
  else
  {
    printf("error: unknown const name\n"); exit(1);
  }
}


//user kernel files
#include "field_summary_kernel_cuda_kernel.cu"
#include "generate_chunk_kernel_cuda_kernel.cu"
#include "initialise_chunk_kernel_zero_cuda_kernel.cu"
#include "initialise_chunk_kernel_zero_x_cuda_kernel.cu"
#include "initialise_chunk_kernel_zero_y_cuda_kernel.cu"
#include "initialise_chunk_kernel_xx_cuda_kernel.cu"
#include "initialise_chunk_kernel_yy_cuda_kernel.cu"
#include "initialise_chunk_kernel_x_cuda_kernel.cu"
#include "initialise_chunk_kernel_y_cuda_kernel.cu"
#include "initialise_chunk_kernel_cellx_cuda_kernel.cu"
#include "initialise_chunk_kernel_celly_cuda_kernel.cu"
#include "initialise_chunk_kernel_volume_cuda_kernel.cu"
#include "set_field_kernel_cuda_kernel.cu"
#include "tea_leaf_init_zero2_kernel_cuda_kernel.cu"
#include "tea_leaf_yeqx_kernel_cuda_kernel.cu"
#include "tea_leaf_dot_kernel_cuda_kernel.cu"
#include "tea_leaf_cg_calc_w_reduce_kernel_cuda_kernel.cu"
#include "tea_leaf_axpy_kernel_cuda_kernel.cu"
#include "tea_leaf_cg_calc_ur_r_reduce_kernel_cuda_kernel.cu"
#include "tea_leaf_axpby_kernel_cuda_kernel.cu"
#include "tea_leaf_cheby_init_kernel_cuda_kernel.cu"
#include "tea_leaf_recip3_kernel_cuda_kernel.cu"
#include "tea_leaf_xpy_kernel_cuda_kernel.cu"
#include "tea_leaf_common_init_u_u0_kernel_cuda_kernel.cu"
#include "tea_leaf_recip_kernel_cuda_kernel.cu"
#include "tea_leaf_common_init_Kx_Ky_kernel_cuda_kernel.cu"
#include "tea_leaf_init_zero_kernel_cuda_kernel.cu"
#include "tea_leaf_common_init_kernel_cuda_kernel.cu"
#include "tea_leaf_recip2_kernel_cuda_kernel.cu"
#include "tea_leaf_common_residual_kernel_cuda_kernel.cu"
#include "tea_leaf_norm2_kernel_cuda_kernel.cu"
#include "tea_leaf_common_init_diag_init_kernel_cuda_kernel.cu"
#include "tea_leaf_zeqxty_kernel_cuda_kernel.cu"
#include "tea_leaf_jacobi_kernel_cuda_kernel.cu"
#include "tea_leaf_ppcg_init1_kernel_cuda_kernel.cu"
#include "tea_leaf_ppcg_init2_kernel_cuda_kernel.cu"
#include "tea_leaf_ppcg_inner1_kernel_cuda_kernel.cu"
#include "tea_leaf_ppcg_inner2_kernel_cuda_kernel.cu"
#include "tea_leaf_ppcg_reduce_kernel_cuda_kernel.cu"
#include "update_halo_kernel1_b2_cuda_kernel.cu"
#include "update_halo_kernel1_b1_cuda_kernel.cu"
#include "update_halo_kernel1_t2_cuda_kernel.cu"
#include "update_halo_kernel1_t1_cuda_kernel.cu"
#include "update_halo_kernel1_l2_cuda_kernel.cu"
#include "update_halo_kernel1_l1_cuda_kernel.cu"
#include "update_halo_kernel1_r2_cuda_kernel.cu"
#include "update_halo_kernel1_r1_cuda_kernel.cu"
