//
// auto-generated by op2.py on 2014-07-07 13:31
//

//header
#include "stdlib.h"
#include "stdio.h"
#include "ops_lib_cpp.h"
#include "ops_opencl_rt_support.h"
#include "user_types.h"
//global constants
extern double g_small;
extern double g_big;
extern double dtc_safe;
extern double dtu_safe;
extern double dtv_safe;
extern double dtdiv_safe;
extern field_type field;
extern grid_type grid;
extern int number_of_states;
extern state_type *states;
extern int g_circ;
extern int g_point;
extern int g_rect;
extern double dt;

extern ops_opencl_core OPS_opencl_core;

//this needs to be a platform specific copy symbol to device function
void ops_decl_const_char( int dim, char const * type, int typeSize, char * dat, char const * name ) {
  cl_int ret = 0;
  if (OPS_opencl_core.constant == NULL) {
    OPS_opencl_core.constant = (cl_mem*) malloc((14)*sizeof(cl_mem));
    for ( int i=0; i<14; i++ ){
      OPS_opencl_core.constant[i] = NULL;
    }
  }
  if (!strcmp(name,"g_small")) {
    if (OPS_opencl_core.constant[0] == NULL) {
      OPS_opencl_core.constant[0] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[0], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"g_big")) {
    if (OPS_opencl_core.constant[1] == NULL) {
      OPS_opencl_core.constant[1] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[1], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"dtc_safe")) {
    if (OPS_opencl_core.constant[2] == NULL) {
      OPS_opencl_core.constant[2] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[2], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"dtu_safe")) {
    if (OPS_opencl_core.constant[3] == NULL) {
      OPS_opencl_core.constant[3] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[3], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"dtv_safe")) {
    if (OPS_opencl_core.constant[4] == NULL) {
      OPS_opencl_core.constant[4] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[4], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"dtdiv_safe")) {
    if (OPS_opencl_core.constant[5] == NULL) {
      OPS_opencl_core.constant[5] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[5], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"field")) {
    if (OPS_opencl_core.constant[6] == NULL) {
      OPS_opencl_core.constant[6] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[6], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"grid")) {
    if (OPS_opencl_core.constant[7] == NULL) {
      OPS_opencl_core.constant[7] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[7], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"number_of_states")) {
    if (OPS_opencl_core.constant[8] == NULL) {
      OPS_opencl_core.constant[8] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[8], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"states")) {
    if (OPS_opencl_core.constant[9] == NULL) {
      OPS_opencl_core.constant[9] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[9], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"g_circ")) {
    if (OPS_opencl_core.constant[10] == NULL) {
      OPS_opencl_core.constant[10] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[10], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"g_point")) {
    if (OPS_opencl_core.constant[11] == NULL) {
      OPS_opencl_core.constant[11] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[11], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"g_rect")) {
    if (OPS_opencl_core.constant[12] == NULL) {
      OPS_opencl_core.constant[12] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[12], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  if (!strcmp(name,"dt")) {
    if (OPS_opencl_core.constant[13] == NULL) {
      OPS_opencl_core.constant[13] = clCreateBuffer(OPS_opencl_core.context, CL_MEM_READ_ONLY, dim*typeSize, NULL, &ret);
      clSafeCall( ret );
    }
    //Write the new constant to the memory of the device
    clSafeCall( clEnqueueWriteBuffer(OPS_opencl_core.command_queue, OPS_opencl_core.constant[13], CL_TRUE, 0, dim*typeSize, (void*) dat, 0, NULL, NULL) );
    clSafeCall( clFlush(OPS_opencl_core.command_queue) );
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }
  else
  {
    printf("error: unknown const name\n"); exit(1);
  }
}

extern ops_opencl_core OPS_opencl_core;

void buildOpenCLKernels() {
  static bool isbuilt = false;

  if(!isbuilt) {
    //clSafeCall( clUnloadCompiler() );

    OPS_opencl_core.n_kernels = 81;
    OPS_opencl_core.kernel = (cl_kernel*) malloc(81*sizeof(cl_kernel));
  }
  isbuilt = true;
}  
  
//user kernel files
#include "viscosity_kernel_opencl_kernel.cpp"
#include "accelerate_kernel_opencl_kernel.cpp"
#include "revert_kernel_opencl_kernel.cpp"
#include "reset_field_kernel1_opencl_kernel.cpp"
#include "reset_field_kernel2_opencl_kernel.cpp"
#include "PdV_kernel_predict_opencl_kernel.cpp"
#include "PdV_kernel_nopredict_opencl_kernel.cpp"
#include "ideal_gas_kernel_opencl_kernel.cpp"
#include "flux_calc_kernelx_opencl_kernel.cpp"
#include "flux_calc_kernely_opencl_kernel.cpp"
#include "advec_mom_kernel_x1_opencl_kernel.cpp"
#include "advec_mom_kernel_y1_opencl_kernel.cpp"
#include "advec_mom_kernel_x2_opencl_kernel.cpp"
#include "advec_mom_kernel_y2_opencl_kernel.cpp"
#include "advec_mom_kernel_mass_flux_x_opencl_kernel.cpp"
#include "advec_mom_kernel_post_pre_advec_x_opencl_kernel.cpp"
#include "advec_mom_kernel1_x_nonvector_opencl_kernel.cpp"
#include "advec_mom_kernel2_x_opencl_kernel.cpp"
#include "advec_mom_kernel_mass_flux_y_opencl_kernel.cpp"
#include "advec_mom_kernel_post_pre_advec_y_opencl_kernel.cpp"
#include "advec_mom_kernel1_y_nonvector_opencl_kernel.cpp"
#include "advec_mom_kernel2_y_opencl_kernel.cpp"
#include "advec_cell_kernel1_xdir_opencl_kernel.cpp"
#include "advec_cell_kernel2_xdir_opencl_kernel.cpp"
#include "advec_cell_kernel3_xdir_opencl_kernel.cpp"
#include "advec_cell_kernel4_xdir_opencl_kernel.cpp"
#include "advec_cell_kernel1_ydir_opencl_kernel.cpp"
#include "advec_cell_kernel2_ydir_opencl_kernel.cpp"
#include "advec_cell_kernel3_ydir_opencl_kernel.cpp"
#include "advec_cell_kernel4_ydir_opencl_kernel.cpp"
#include "update_halo_kernel1_b2_opencl_kernel.cpp"
#include "update_halo_kernel1_b1_opencl_kernel.cpp"
#include "update_halo_kernel1_t2_opencl_kernel.cpp"
#include "update_halo_kernel1_t1_opencl_kernel.cpp"
#include "update_halo_kernel1_l2_opencl_kernel.cpp"
#include "update_halo_kernel1_l1_opencl_kernel.cpp"
#include "update_halo_kernel1_r2_opencl_kernel.cpp"
#include "update_halo_kernel1_r1_opencl_kernel.cpp"
#include "update_halo_kernel2_xvel_plus_4_a_opencl_kernel.cpp"
#include "update_halo_kernel2_xvel_plus_2_a_opencl_kernel.cpp"
#include "update_halo_kernel2_xvel_plus_4_b_opencl_kernel.cpp"
#include "update_halo_kernel2_xvel_plus_2_b_opencl_kernel.cpp"
#include "update_halo_kernel2_xvel_minus_4_a_opencl_kernel.cpp"
#include "update_halo_kernel2_xvel_minus_2_a_opencl_kernel.cpp"
#include "update_halo_kernel2_xvel_minus_4_b_opencl_kernel.cpp"
#include "update_halo_kernel2_xvel_minus_2_b_opencl_kernel.cpp"
#include "update_halo_kernel2_yvel_minus_4_a_opencl_kernel.cpp"
#include "update_halo_kernel2_yvel_minus_2_a_opencl_kernel.cpp"
#include "update_halo_kernel2_yvel_minus_4_b_opencl_kernel.cpp"
#include "update_halo_kernel2_yvel_minus_2_b_opencl_kernel.cpp"
#include "update_halo_kernel2_yvel_plus_4_a_opencl_kernel.cpp"
#include "update_halo_kernel2_yvel_plus_2_a_opencl_kernel.cpp"
#include "update_halo_kernel2_yvel_plus_4_b_opencl_kernel.cpp"
#include "update_halo_kernel2_yvel_plus_2_b_opencl_kernel.cpp"
#include "update_halo_kernel3_plus_4_a_opencl_kernel.cpp"
#include "update_halo_kernel3_plus_2_a_opencl_kernel.cpp"
#include "update_halo_kernel3_plus_4_b_opencl_kernel.cpp"
#include "update_halo_kernel3_plus_2_b_opencl_kernel.cpp"
#include "update_halo_kernel3_minus_4_a_opencl_kernel.cpp"
#include "update_halo_kernel3_minus_2_a_opencl_kernel.cpp"
#include "update_halo_kernel3_minus_4_b_opencl_kernel.cpp"
#include "update_halo_kernel3_minus_2_b_opencl_kernel.cpp"
#include "update_halo_kernel4_minus_4_a_opencl_kernel.cpp"
#include "update_halo_kernel4_minus_2_a_opencl_kernel.cpp"
#include "update_halo_kernel4_minus_4_b_opencl_kernel.cpp"
#include "update_halo_kernel4_minus_2_b_opencl_kernel.cpp"
#include "update_halo_kernel4_plus_4_a_opencl_kernel.cpp"
#include "update_halo_kernel4_plus_2_a_opencl_kernel.cpp"
#include "update_halo_kernel4_plus_4_b_opencl_kernel.cpp"
#include "update_halo_kernel4_plus_2_b_opencl_kernel.cpp"
#include "field_summary_kernel_opencl_kernel.cpp"
#include "calc_dt_kernel_opencl_kernel.cpp"
#include "calc_dt_kernel_min_opencl_kernel.cpp"
#include "calc_dt_kernel_get_opencl_kernel.cpp"
#include "calc_dt_kernel_print_opencl_kernel.cpp"
