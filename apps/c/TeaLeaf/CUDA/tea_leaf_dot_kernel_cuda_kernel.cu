//
// auto-generated by ops.py
//
__constant__ int xdim0_tea_leaf_dot_kernel;
int xdim0_tea_leaf_dot_kernel_h = -1;
int ydim0_tea_leaf_dot_kernel_h = -1;
__constant__ int xdim1_tea_leaf_dot_kernel;
int xdim1_tea_leaf_dot_kernel_h = -1;
int ydim1_tea_leaf_dot_kernel_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1


#define OPS_ACC0(x,y) (x+xdim0_tea_leaf_dot_kernel*(y))
#define OPS_ACC1(x,y) (x+xdim1_tea_leaf_dot_kernel*(y))

//user function
__device__

void tea_leaf_dot_kernel_gpu (const double * r, const double * p, double *rro) {
  *rro = *rro + r[OPS_ACC0(0,0)] * p[OPS_ACC1(0,0)];
}



#undef OPS_ACC0
#undef OPS_ACC1


__global__ void ops_tea_leaf_dot_kernel(
const double* __restrict arg0,
const double* __restrict arg1,
double* __restrict arg2,
int size0,
int size1 ){

  double arg2_l[1];
  for (int d=0; d<1; d++) arg2_l[d] = ZERO_double;

  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * xdim0_tea_leaf_dot_kernel;
  arg1 += idx_x * 1*1 + idx_y * 1*1 * xdim1_tea_leaf_dot_kernel;

  if (idx_x < size0 && idx_y < size1) {
    tea_leaf_dot_kernel_gpu(arg0, arg1, arg2_l);
  }
  for (int d=0; d<1; d++)
    ops_reduction_cuda<OPS_INC>(&arg2[d+(blockIdx.x + blockIdx.y*gridDim.x)*1],arg2_l[d]);

}

// host stub function
void ops_par_loop_tea_leaf_dot_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[3] = { arg0, arg1, arg2};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,3,range,18)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(18,"tea_leaf_dot_kernel");
    OPS_kernels[18].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<2; n++ ){
    start[n] = sb->decomp_disp[n];end[n] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) start[n] = range[2*n];
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      end[n] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif

  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];

  if (xdim0 != xdim0_tea_leaf_dot_kernel_h || xdim1 != xdim1_tea_leaf_dot_kernel_h) {
    cudaMemcpyToSymbol( xdim0_tea_leaf_dot_kernel, &xdim0, sizeof(int) );
    xdim0_tea_leaf_dot_kernel_h = xdim0;
    cudaMemcpyToSymbol( xdim1_tea_leaf_dot_kernel, &xdim1, sizeof(int) );
    xdim1_tea_leaf_dot_kernel_h = xdim1;
  }


  #ifdef OPS_MPI
  double *arg2h = (double *)(((ops_reduction)args[2].data)->data + ((ops_reduction)args[2].data)->size * block->index);
  #else
  double *arg2h = (double *)(((ops_reduction)args[2].data)->data);
  #endif

  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,1);

  int nblocks = ((x_size-1)/OPS_block_size_x+ 1)*((y_size-1)/OPS_block_size_y + 1);
  int maxblocks = nblocks;
  int reduct_bytes = 0;
  int reduct_size = 0;

  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));
  reduct_size = MAX(reduct_size,sizeof(double)*1);

  reallocReductArrays(reduct_bytes);
  reduct_bytes = 0;

  arg2.data = OPS_reduct_h + reduct_bytes;
  arg2.data_d = OPS_reduct_d + reduct_bytes;
  for (int b=0; b<maxblocks; b++)
  for (int d=0; d<1; d++) ((double *)arg2.data)[d+b*1] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));


  mvReductArraysToDevice(reduct_bytes);
  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;

  char *p_a[3];

  //set up initial pointers
  int d_m[OPS_MAX_DIM];
  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
  #endif
  int base0 = dat0 * 1 *
  (start[0] * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1] - args[0].dat->base[1] - d_m[1]);
  p_a[0] = (char *)args[0].data_d + base0;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d];
  #endif
  int base1 = dat1 * 1 *
  (start[0] * args[1].stencil->stride[0] - args[1].dat->base[0] - d_m[0]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1] - args[1].dat->base[1] - d_m[1]);
  p_a[1] = (char *)args[1].data_d + base1;


  ops_H_D_exchanges_device(args, 3);
  ops_halo_exchanges(args,3,range);

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[18].mpi_time += t2-t1;
  }

  int nshared = 0;
  int nthread = OPS_block_size_x*OPS_block_size_y;

  nshared = MAX(nshared,sizeof(double)*1);

  nshared = MAX(nshared*nthread,reduct_size*nthread);

  //call kernel wrapper function, passing in pointers to data
  ops_tea_leaf_dot_kernel<<<grid, tblock, nshared >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)arg2.data_d,x_size, y_size);

  mvReductArraysToHost(reduct_bytes);
  for ( int b=0; b<maxblocks; b++ ){
    for ( int d=0; d<1; d++ ){
      arg2h[d] = arg2h[d] + ((double *)arg2.data)[d+b*1];
    }
  }
  arg2.data = (char *)arg2h;

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[18].time += t1-t2;
  }

  ops_set_dirtybit_device(args, 3);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[18].mpi_time += t2-t1;
    OPS_kernels[18].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[18].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}
