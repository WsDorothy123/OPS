//
// auto-generated by ops.py
//

#ifdef OCL_FMA_SWITCH_ON
#define OCL_FMA 1
#else
#define OCL_FMA 0
#endif

static bool isbuilt_field_summary_kernel = false;

void buildOpenCLKernels_field_summary_kernel(int xdim0, int xdim1, int xdim2,
                                             int xdim3) {

  // int ocl_fma = OCL_FMA;
  if (!isbuilt_field_summary_kernel) {
    buildOpenCLKernels();
    // clSafeCall( clUnloadCompiler() );
    cl_int ret;
    char *source_filename[1] = {(char *)"./OpenCL/field_summary_kernel.cl"};

    // Load the kernel source code into the array source_str
    FILE *fid;
    char *source_str[1];
    size_t source_size[1];

    for (int i = 0; i < 1; i++) {
      fid = fopen(source_filename[i], "r");
      if (!fid) {
        fprintf(stderr, "Can't open the kernel source file!\n");
        exit(1);
      }

      source_str[i] = (char *)malloc(4 * 0x1000000);
      source_size[i] = fread(source_str[i], 1, 4 * 0x1000000, fid);
      if (source_size[i] != 4 * 0x1000000) {
        if (ferror(fid)) {
          printf("Error while reading kernel source file %s\n",
                 source_filename[i]);
          exit(-1);
        }
        if (feof(fid))
          printf("Kernel source file %s succesfuly read.\n",
                 source_filename[i]);
        // printf("%s\n",source_str[i]);
      }
      fclose(fid);
    }

    printf("Compiling field_summary_kernel %d source -- start \n", OCL_FMA);

    // Create a program from the source
    OPS_opencl_core.program = clCreateProgramWithSource(
        OPS_opencl_core.context, 1, (const char **)&source_str,
        (const size_t *)&source_size, &ret);
    clSafeCall(ret);

    // Build the program
    char buildOpts[255 * 8];
    char *pPath = NULL;
    pPath = getenv("OPS_INSTALL_PATH");
    if (pPath != NULL)
      if (OCL_FMA)
        sprintf(buildOpts, "-cl-mad-enable -DOCL_FMA -I%s/c/include "
                           "-DOPS_WARPSIZE=%d  -Dxdim0_field_summary_kernel=%d "
                           " -Dxdim1_field_summary_kernel=%d  "
                           "-Dxdim2_field_summary_kernel=%d  "
                           "-Dxdim3_field_summary_kernel=%d ",
                pPath, 32, xdim0, xdim1, xdim2, xdim3);
      else
        sprintf(buildOpts, "-cl-mad-enable -I%s/c/include -DOPS_WARPSIZE=%d  "
                           "-Dxdim0_field_summary_kernel=%d  "
                           "-Dxdim1_field_summary_kernel=%d  "
                           "-Dxdim2_field_summary_kernel=%d  "
                           "-Dxdim3_field_summary_kernel=%d ",
                pPath, 32, xdim0, xdim1, xdim2, xdim3);
    else {
      sprintf((char *)"Incorrect OPS_INSTALL_PATH %s\n", pPath);
      exit(EXIT_FAILURE);
    }

    ret = clBuildProgram(OPS_opencl_core.program, 1, &OPS_opencl_core.device_id,
                         buildOpts, NULL, NULL);

    if (ret != CL_SUCCESS) {
      char *build_log;
      size_t log_size;
      clSafeCall(clGetProgramBuildInfo(
          OPS_opencl_core.program, OPS_opencl_core.device_id,
          CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size));
      build_log = (char *)malloc(log_size + 1);
      clSafeCall(clGetProgramBuildInfo(
          OPS_opencl_core.program, OPS_opencl_core.device_id,
          CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL));
      build_log[log_size] = '\0';
      fprintf(
          stderr,
          "=============== OpenCL Program Build Info ================\n\n%s",
          build_log);
      fprintf(stderr,
              "\n========================================================= \n");
      free(build_log);
      exit(EXIT_FAILURE);
    }
    printf("compiling field_summary_kernel -- done\n");

    // Create the OpenCL kernel
    OPS_opencl_core.kernel[0] = clCreateKernel(
        OPS_opencl_core.program, "ops_field_summary_kernel", &ret);
    clSafeCall(ret);

    isbuilt_field_summary_kernel = true;
  }
}

// host stub function
void ops_par_loop_field_summary_kernel(char const *name, ops_block block,
                                       int dim, int *range, ops_arg arg0,
                                       ops_arg arg1, ops_arg arg2, ops_arg arg3,
                                       ops_arg arg4, ops_arg arg5, ops_arg arg6,
                                       ops_arg arg7) {

  // Timing
  double t1, t2, c1, c2;

  ops_arg args[8] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 8, range, 0))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(0, "field_summary_kernel");
    OPS_kernels[0].count++;
    ops_timers_core(&c1, &t1);
  }

  // compute locally allocated range for the sub-block
  int start[2];
  int end[2];
#ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned)
    return;
  for (int n = 0; n < 2; n++) {
    start[n] = sb->decomp_disp[n];
    end[n] = sb->decomp_disp[n] + sb->decomp_size[n];
    if (start[n] >= range[2 * n]) {
      start[n] = 0;
    } else {
      start[n] = range[2 * n] - start[n];
    }
    if (sb->id_m[n] == MPI_PROC_NULL && range[2 * n] < 0)
      start[n] = range[2 * n];
    if (end[n] >= range[2 * n + 1]) {
      end[n] = range[2 * n + 1] - sb->decomp_disp[n];
    } else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n] == MPI_PROC_NULL &&
        (range[2 * n + 1] > sb->decomp_disp[n] + sb->decomp_size[n]))
      end[n] += (range[2 * n + 1] - sb->decomp_disp[n] - sb->decomp_size[n]);
  }
#else
  for (int n = 0; n < 2; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }
#endif

  int x_size = MAX(0, end[0] - start[0]);
  int y_size = MAX(0, end[1] - start[1]);

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];

  // build opencl kernel if not already built

  buildOpenCLKernels_field_summary_kernel(xdim0, xdim1, xdim2, xdim3);

  // set up OpenCL thread blocks
  size_t globalWorkSize[3] = {
      ((x_size - 1) / OPS_block_size_x + 1) * OPS_block_size_x,
      ((y_size - 1) / OPS_block_size_y + 1) * OPS_block_size_y, 1};
  size_t localWorkSize[3] = {OPS_block_size_x, OPS_block_size_y, 1};

#ifdef OPS_MPI
  double *arg4h =
      (double *)(((ops_reduction)args[4].data)->data +
                 ((ops_reduction)args[4].data)->size * block->index);
#else
  double *arg4h = (double *)(((ops_reduction)args[4].data)->data);
#endif
#ifdef OPS_MPI
  double *arg5h =
      (double *)(((ops_reduction)args[5].data)->data +
                 ((ops_reduction)args[5].data)->size * block->index);
#else
  double *arg5h = (double *)(((ops_reduction)args[5].data)->data);
#endif
#ifdef OPS_MPI
  double *arg6h =
      (double *)(((ops_reduction)args[6].data)->data +
                 ((ops_reduction)args[6].data)->size * block->index);
#else
  double *arg6h = (double *)(((ops_reduction)args[6].data)->data);
#endif
#ifdef OPS_MPI
  double *arg7h =
      (double *)(((ops_reduction)args[7].data)->data +
                 ((ops_reduction)args[7].data)->size * block->index);
#else
  double *arg7h = (double *)(((ops_reduction)args[7].data)->data);
#endif

  int nblocks = ((x_size - 1) / OPS_block_size_x + 1) *
                ((y_size - 1) / OPS_block_size_y + 1);
  int maxblocks = nblocks;
  int reduct_bytes = 0;

  reduct_bytes += ROUND_UP(maxblocks * 1 * sizeof(double));
  reduct_bytes += ROUND_UP(maxblocks * 1 * sizeof(double));
  reduct_bytes += ROUND_UP(maxblocks * 1 * sizeof(double));
  reduct_bytes += ROUND_UP(maxblocks * 1 * sizeof(double));

  reallocReductArrays(reduct_bytes);
  reduct_bytes = 0;

  int r_bytes4 = reduct_bytes / sizeof(double);
  arg4.data = OPS_reduct_h + reduct_bytes;
  arg4.data_d = OPS_reduct_d; // + reduct_bytes;
  for (int b = 0; b < maxblocks; b++)
    for (int d = 0; d < 1; d++)
      ((double *)arg4.data)[d + b * 1] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks * 1 * sizeof(double));

  int r_bytes5 = reduct_bytes / sizeof(double);
  arg5.data = OPS_reduct_h + reduct_bytes;
  arg5.data_d = OPS_reduct_d; // + reduct_bytes;
  for (int b = 0; b < maxblocks; b++)
    for (int d = 0; d < 1; d++)
      ((double *)arg5.data)[d + b * 1] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks * 1 * sizeof(double));

  int r_bytes6 = reduct_bytes / sizeof(double);
  arg6.data = OPS_reduct_h + reduct_bytes;
  arg6.data_d = OPS_reduct_d; // + reduct_bytes;
  for (int b = 0; b < maxblocks; b++)
    for (int d = 0; d < 1; d++)
      ((double *)arg6.data)[d + b * 1] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks * 1 * sizeof(double));

  int r_bytes7 = reduct_bytes / sizeof(double);
  arg7.data = OPS_reduct_h + reduct_bytes;
  arg7.data_d = OPS_reduct_d; // + reduct_bytes;
  for (int b = 0; b < maxblocks; b++)
    for (int d = 0; d < 1; d++)
      ((double *)arg7.data)[d + b * 1] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks * 1 * sizeof(double));

  mvReductArraysToDevice(reduct_bytes);

  // set up initial pointers
  int d_m[OPS_MAX_DIM];
#ifdef OPS_MPI
  for (int d = 0; d < dim; d++)
    d_m[d] =
        args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
#else
  for (int d = 0; d < dim; d++)
    d_m[d] = args[0].dat->d_m[d];
#endif
  int base0 = 1 * 1 * (start[0] * args[0].stencil->stride[0] -
                       args[0].dat->base[0] - d_m[0]);
  base0 = base0 +
          args[0].dat->size[0] * 1 * (start[1] * args[0].stencil->stride[1] -
                                      args[0].dat->base[1] - d_m[1]);

#ifdef OPS_MPI
  for (int d = 0; d < dim; d++)
    d_m[d] =
        args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
#else
  for (int d = 0; d < dim; d++)
    d_m[d] = args[1].dat->d_m[d];
#endif
  int base1 = 1 * 1 * (start[0] * args[1].stencil->stride[0] -
                       args[1].dat->base[0] - d_m[0]);
  base1 = base1 +
          args[1].dat->size[0] * 1 * (start[1] * args[1].stencil->stride[1] -
                                      args[1].dat->base[1] - d_m[1]);

#ifdef OPS_MPI
  for (int d = 0; d < dim; d++)
    d_m[d] =
        args[2].dat->d_m[d] + OPS_sub_dat_list[args[2].dat->index]->d_im[d];
#else
  for (int d = 0; d < dim; d++)
    d_m[d] = args[2].dat->d_m[d];
#endif
  int base2 = 1 * 1 * (start[0] * args[2].stencil->stride[0] -
                       args[2].dat->base[0] - d_m[0]);
  base2 = base2 +
          args[2].dat->size[0] * 1 * (start[1] * args[2].stencil->stride[1] -
                                      args[2].dat->base[1] - d_m[1]);

#ifdef OPS_MPI
  for (int d = 0; d < dim; d++)
    d_m[d] =
        args[3].dat->d_m[d] + OPS_sub_dat_list[args[3].dat->index]->d_im[d];
#else
  for (int d = 0; d < dim; d++)
    d_m[d] = args[3].dat->d_m[d];
#endif
  int base3 = 1 * 1 * (start[0] * args[3].stencil->stride[0] -
                       args[3].dat->base[0] - d_m[0]);
  base3 = base3 +
          args[3].dat->size[0] * 1 * (start[1] * args[3].stencil->stride[1] -
                                      args[3].dat->base[1] - d_m[1]);

  ops_H_D_exchanges_device(args, 8);
  ops_halo_exchanges(args, 8, range);
  ops_H_D_exchanges_device(args, 8);

  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[0].mpi_time += t2 - t1;
  }

  int nthread = OPS_block_size_x * OPS_block_size_y;

  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 0, sizeof(cl_mem),
                            (void *)&arg0.data_d));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 1, sizeof(cl_mem),
                            (void *)&arg1.data_d));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 2, sizeof(cl_mem),
                            (void *)&arg2.data_d));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 3, sizeof(cl_mem),
                            (void *)&arg3.data_d));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 4, sizeof(cl_mem),
                            (void *)&arg4.data_d));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 5,
                            nthread * sizeof(double), NULL));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 6, sizeof(cl_int),
                            (void *)&r_bytes4));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 7, sizeof(cl_mem),
                            (void *)&arg5.data_d));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 8,
                            nthread * sizeof(double), NULL));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 9, sizeof(cl_int),
                            (void *)&r_bytes5));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 10, sizeof(cl_mem),
                            (void *)&arg6.data_d));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 11,
                            nthread * sizeof(double), NULL));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 12, sizeof(cl_int),
                            (void *)&r_bytes6));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 13, sizeof(cl_mem),
                            (void *)&arg7.data_d));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 14,
                            nthread * sizeof(double), NULL));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 15, sizeof(cl_int),
                            (void *)&r_bytes7));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 16, sizeof(cl_int),
                            (void *)&base0));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 17, sizeof(cl_int),
                            (void *)&base1));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 18, sizeof(cl_int),
                            (void *)&base2));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 19, sizeof(cl_int),
                            (void *)&base3));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 20, sizeof(cl_int),
                            (void *)&x_size));
  clSafeCall(clSetKernelArg(OPS_opencl_core.kernel[0], 21, sizeof(cl_int),
                            (void *)&y_size));

  // call/enque opencl kernel wrapper function
  clSafeCall(clEnqueueNDRangeKernel(
      OPS_opencl_core.command_queue, OPS_opencl_core.kernel[0], 3, NULL,
      globalWorkSize, localWorkSize, 0, NULL, NULL));
  if (OPS_diags > 1) {
    clSafeCall(clFinish(OPS_opencl_core.command_queue));
  }

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[0].time += t1 - t2;
  }

  mvReductArraysToHost(reduct_bytes);
  for (int b = 0; b < maxblocks; b++) {
    for (int d = 0; d < 1; d++) {
      arg4h[d] = arg4h[d] + ((double *)arg4.data)[d + b * 1];
    }
  }
  arg4.data = (char *)arg4h;

  for (int b = 0; b < maxblocks; b++) {
    for (int d = 0; d < 1; d++) {
      arg5h[d] = arg5h[d] + ((double *)arg5.data)[d + b * 1];
    }
  }
  arg5.data = (char *)arg5h;

  for (int b = 0; b < maxblocks; b++) {
    for (int d = 0; d < 1; d++) {
      arg6h[d] = arg6h[d] + ((double *)arg6.data)[d + b * 1];
    }
  }
  arg6.data = (char *)arg6h;

  for (int b = 0; b < maxblocks; b++) {
    for (int d = 0; d < 1; d++) {
      arg7h[d] = arg7h[d] + ((double *)arg7.data)[d + b * 1];
    }
  }
  arg7.data = (char *)arg7h;

  ops_set_dirtybit_device(args, 8);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[0].mpi_time += t2 - t1;
    OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg3);
  }
}
