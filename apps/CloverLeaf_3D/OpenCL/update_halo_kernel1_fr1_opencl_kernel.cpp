//
// auto-generated by ops.py on 2014-07-15 12:35
//


static bool isbuilt_update_halo_kernel1_fr1 = false;

void buildOpenCLKernels_update_halo_kernel1_fr1(int xdim0,
 int xdim1,
 int xdim2,
 int xdim3,
 int xdim4,
 int xdim5,
 int xdim6) {
  
  if(!isbuilt_update_halo_kernel1_fr1) {
    buildOpenCLKernels();
    //clSafeCall( clUnloadCompiler() );       
    cl_int ret;
    char* source_filename[1] = {"./OpenCL/update_halo_kernel1_fr1.cl"};

    // Load the kernel source code into the array source_str
    FILE *fid;
    char *source_str[1];
    size_t source_size[1];

    for(int i=0; i<1; i++) {
      fid = fopen(source_filename[i], "r");
      if (!fid) {
        fprintf(stderr, "Can't open the kernel source file!\n");
        exit(1);
      }
      
      source_str[i] = (char*)malloc(4*0x1000000);
      source_size[i] = fread(source_str[i], 1, 4*0x1000000, fid);
      if(source_size[i] != 4*0x1000000) {
        if (ferror(fid)) {
          printf ("Error while reading kernel source file %s\n", source_filename[i]);
          exit(-1);
        }
        if (feof(fid))
          printf ("Kernel source file %s succesfuly read.\n", source_filename[i]);
          //printf("%s\n",source_str[i]);
      }
      fclose(fid);
    }
    
    printf("Compiling update_halo_kernel1_fr1 source -- start \n");

      // Create a program from the source
      OPS_opencl_core.program = clCreateProgramWithSource(OPS_opencl_core.context, 1, (const char **) &source_str, (const size_t *) &source_size, &ret);
      clSafeCall( ret );

      // Build the program
      char buildOpts[255*8];
      char* pPath = NULL;
      pPath = getenv ("OPS_INSTALL_PATH");
      if (pPath!=NULL)
        sprintf(buildOpts,"-cl-mad-enable -I%s/include -DOPS_WARPSIZE=%d  -Dxdim0_update_halo_kernel1_fr1=%d -Dxdim1_update_halo_kernel1_fr1=%d -Dxdim2_update_halo_kernel1_fr1=%d -Dxdim3_update_halo_kernel1_fr1=%d -Dxdim4_update_halo_kernel1_fr1=%d -Dxdim5_update_halo_kernel1_fr1=%d -Dxdim6_update_halo_kernel1_fr1=%d", pPath, 32,xdim0,xdim1,xdim2,xdim3,xdim4,xdim5,xdim6);
      else {
        sprintf("Incorrect OPS_INSTALL_PATH %s\n",pPath);
        exit(EXIT_FAILURE);
      }
      
      ret = clBuildProgram(OPS_opencl_core.program, 1, &OPS_opencl_core.device_id, buildOpts, NULL, NULL);

      if(ret != CL_SUCCESS) {
        char* build_log;
        size_t log_size;
        clSafeCall( clGetProgramBuildInfo(OPS_opencl_core.program, OPS_opencl_core.device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size) );
        build_log = (char*) malloc(log_size+1);
        clSafeCall( clGetProgramBuildInfo(OPS_opencl_core.program, OPS_opencl_core.device_id, CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL) );
        build_log[log_size] = '\0';
        fprintf(stderr, "=============== OpenCL Program Build Info ================\n\n%s", build_log);
        fprintf(stderr, "\n========================================================= \n");
        free(build_log);
        exit(EXIT_FAILURE);
      }
      printf("compiling update_halo_kernel1_fr1 -- done\n");

    // Create the OpenCL kernel
    OPS_opencl_core.kernel[52] = clCreateKernel(OPS_opencl_core.program, "ops_update_halo_kernel1_fr1", &ret);
    clSafeCall( ret );
      
    isbuilt_update_halo_kernel1_fr1 = true;
  }
  
}  


// host stub function
void ops_par_loop_update_halo_kernel1_fr1(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {
  ops_arg args[8] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};

  sub_block_list sb = OPS_sub_block_list[Block->index];
  //compute localy allocated range for the sub-block
  int start_add[3];
  int end_add[3];
  for ( int n=0; n<3; n++ ){
    start_add[n] = sb->istart[n];end_add[n] = sb->iend[n]+1;
    if (start_add[n] >= range[2*n]) {
      start_add[n] = 0;
    }
    else {
      start_add[n] = range[2*n] - start_add[n];
    }
    if (end_add[n] >= range[2*n+1]) {
      end_add[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end_add[n] = sb->sizes[n];
    }
  }


  int x_size = MAX(0,end_add[0]-start_add[0]);
  int y_size = MAX(0,end_add[1]-start_add[1]);
  int z_size = MAX(0,end_add[2]-start_add[2]);

  int xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  int ydim0 = args[0].dat->block_size[1];
  int xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;
  int ydim1 = args[1].dat->block_size[1];
  int xdim2 = args[2].dat->block_size[0]*args[2].dat->dim;
  int ydim2 = args[2].dat->block_size[1];
  int xdim3 = args[3].dat->block_size[0]*args[3].dat->dim;
  int ydim3 = args[3].dat->block_size[1];
  int xdim4 = args[4].dat->block_size[0]*args[4].dat->dim;
  int ydim4 = args[4].dat->block_size[1];
  int xdim5 = args[5].dat->block_size[0]*args[5].dat->dim;
  int ydim5 = args[5].dat->block_size[1];
  int xdim6 = args[6].dat->block_size[0]*args[6].dat->dim;
  int ydim6 = args[6].dat->block_size[1];

  //build opencl kernel if not already built

  buildOpenCLKernels_update_halo_kernel1_fr1(
  xdim0,
  xdim1,
  xdim2,
  xdim3,
  xdim4,
  xdim5,
  xdim6);

  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(52,"update_halo_kernel1_fr1");
  ops_timers_core(&c2,&t2);

  //set up OpenCL thread blocks
  size_t globalWorkSize[3] = {((x_size-1)/OPS_block_size_x+ 1)*OPS_block_size_x, ((y_size-1)/OPS_block_size_y + 1)*OPS_block_size_y, z_size};
  size_t localWorkSize[3] =  {OPS_block_size_x,OPS_block_size_y,1};


  int *arg7h = (int *)arg7.data;
  int consts_bytes = 0;

  consts_bytes += ROUND_UP(NUM_FIELDS*sizeof(int));

  reallocConstArrays(consts_bytes);

  consts_bytes = 0;
  arg7.data = OPS_consts_h + consts_bytes;
  arg7.data_d = OPS_consts_d + consts_bytes;
  for (int d=0; d<NUM_FIELDS; d++) ((int *)arg7.data)[d] = arg7h[d];
  consts_bytes += ROUND_UP(NUM_FIELDS*sizeof(int));
  mvConstArraysToDevice(consts_bytes);
  int dat0 = args[0].dat->size;
  int dat1 = args[1].dat->size;
  int dat2 = args[2].dat->size;
  int dat3 = args[3].dat->size;
  int dat4 = args[4].dat->size;
  int dat5 = args[5].dat->size;
  int dat6 = args[6].dat->size;

  //set up initial pointers
  int base0 = 1 * 
  (start_add[0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0 + args[0].dat->block_size[0] * 
  (start_add[1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  base0 = base0 + args[0].dat->block_size[1] * 
  (start_add[2] * args[0].stencil->stride[2] - args[0].dat->offset[2]);

  //set up initial pointers
  int base1 = 1 * 
  (start_add[0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
  base1 = base1 + args[1].dat->block_size[0] * 
  (start_add[1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
  base1 = base1 + args[1].dat->block_size[1] * 
  (start_add[2] * args[1].stencil->stride[2] - args[1].dat->offset[2]);

  //set up initial pointers
  int base2 = 1 * 
  (start_add[0] * args[2].stencil->stride[0] - args[2].dat->offset[0]);
  base2 = base2 + args[2].dat->block_size[0] * 
  (start_add[1] * args[2].stencil->stride[1] - args[2].dat->offset[1]);
  base2 = base2 + args[2].dat->block_size[1] * 
  (start_add[2] * args[2].stencil->stride[2] - args[2].dat->offset[2]);

  //set up initial pointers
  int base3 = 1 * 
  (start_add[0] * args[3].stencil->stride[0] - args[3].dat->offset[0]);
  base3 = base3 + args[3].dat->block_size[0] * 
  (start_add[1] * args[3].stencil->stride[1] - args[3].dat->offset[1]);
  base3 = base3 + args[3].dat->block_size[1] * 
  (start_add[2] * args[3].stencil->stride[2] - args[3].dat->offset[2]);

  //set up initial pointers
  int base4 = 1 * 
  (start_add[0] * args[4].stencil->stride[0] - args[4].dat->offset[0]);
  base4 = base4 + args[4].dat->block_size[0] * 
  (start_add[1] * args[4].stencil->stride[1] - args[4].dat->offset[1]);
  base4 = base4 + args[4].dat->block_size[1] * 
  (start_add[2] * args[4].stencil->stride[2] - args[4].dat->offset[2]);

  //set up initial pointers
  int base5 = 1 * 
  (start_add[0] * args[5].stencil->stride[0] - args[5].dat->offset[0]);
  base5 = base5 + args[5].dat->block_size[0] * 
  (start_add[1] * args[5].stencil->stride[1] - args[5].dat->offset[1]);
  base5 = base5 + args[5].dat->block_size[1] * 
  (start_add[2] * args[5].stencil->stride[2] - args[5].dat->offset[2]);

  //set up initial pointers
  int base6 = 1 * 
  (start_add[0] * args[6].stencil->stride[0] - args[6].dat->offset[0]);
  base6 = base6 + args[6].dat->block_size[0] * 
  (start_add[1] * args[6].stencil->stride[1] - args[6].dat->offset[1]);
  base6 = base6 + args[6].dat->block_size[1] * 
  (start_add[2] * args[6].stencil->stride[2] - args[6].dat->offset[2]);


  ops_H_D_exchanges_cuda(args, 8);

  ops_timers_core(&c1,&t1);
  OPS_kernels[52].mpi_time += t1-t2;


  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 0, sizeof(cl_mem), (void*) &arg0.data_d ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 1, sizeof(cl_mem), (void*) &arg1.data_d ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 2, sizeof(cl_mem), (void*) &arg2.data_d ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 3, sizeof(cl_mem), (void*) &arg3.data_d ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 4, sizeof(cl_mem), (void*) &arg4.data_d ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 5, sizeof(cl_mem), (void*) &arg5.data_d ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 6, sizeof(cl_mem), (void*) &arg6.data_d ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 7, sizeof(cl_mem), (void*) &arg7.data_d ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 8, sizeof(cl_int), (void*) &base0 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 9, sizeof(cl_int), (void*) &base1 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 10, sizeof(cl_int), (void*) &base2 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 11, sizeof(cl_int), (void*) &base3 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 12, sizeof(cl_int), (void*) &base4 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 13, sizeof(cl_int), (void*) &base5 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 14, sizeof(cl_int), (void*) &base6 ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 15, sizeof(cl_int), (void*) &x_size ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 16, sizeof(cl_int), (void*) &y_size ));
  clSafeCall( clSetKernelArg(OPS_opencl_core.kernel[52], 17, sizeof(cl_int), (void*) &z_size ));

  //call/enque opencl kernel wrapper function
  clSafeCall( clEnqueueNDRangeKernel(OPS_opencl_core.command_queue, OPS_opencl_core.kernel[52], 3, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL) );
  if (OPS_diags>1) {
    clSafeCall( clFinish(OPS_opencl_core.command_queue) );
  }

  ops_set_dirtybit_opencl(args, 8);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[52].count++;
  OPS_kernels[52].time += t2-t1;
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg4);
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg5);
  OPS_kernels[52].transfer += ops_compute_transfer(dim, range, &arg6);
}
