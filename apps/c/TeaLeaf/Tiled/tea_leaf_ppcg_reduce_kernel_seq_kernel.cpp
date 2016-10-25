//
// auto-generated by ops.py
//
#define OPS_ACC0(x,y) (n_x*1+n_y*xdim0_tea_leaf_ppcg_reduce_kernel*1+x+xdim0_tea_leaf_ppcg_reduce_kernel*(y))
#define OPS_ACC1(x,y) (n_x*1+n_y*xdim1_tea_leaf_ppcg_reduce_kernel*1+x+xdim1_tea_leaf_ppcg_reduce_kernel*(y))
#define OPS_ACC2(x,y) (n_x*1+n_y*xdim2_tea_leaf_ppcg_reduce_kernel*1+x+xdim2_tea_leaf_ppcg_reduce_kernel*(y))


//user function

// host stub function
void ops_par_loop_tea_leaf_ppcg_reduce_kernel_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[4] = { arg0, arg1, arg2, arg3};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,4,range,48)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(48,"tea_leaf_ppcg_reduce_kernel");
    OPS_kernels[48].count++;
    ops_timers_core(&c2,&t2);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "tea_leaf_ppcg_reduce_kernel");
  #endif



  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  const double * __restrict__ rstore = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  const double * __restrict__ r = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset;
  const double * __restrict__ z = (double *)(args[2].data + base2);

  #ifdef OPS_MPI
  double * __restrict__ p_a3 = (double *)(((ops_reduction)args[3].data)->data + ((ops_reduction)args[3].data)->size * block->index);
  #else //OPS_MPI
  double * __restrict__ p_a3 = (double *)((ops_reduction)args[3].data)->data;
  #endif //OPS_MPI



  //initialize global variable with the dimension of dats
  int xdim0_tea_leaf_ppcg_reduce_kernel = args[0].dat->size[0];
  int xdim1_tea_leaf_ppcg_reduce_kernel = args[1].dat->size[0];
  int xdim2_tea_leaf_ppcg_reduce_kernel = args[2].dat->size[0];

  //Halo Exchanges
  ops_H_D_exchanges_host(args, 4);
  ops_halo_exchanges(args,4,range);
  ops_H_D_exchanges_host(args, 4);

  if (OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_kernels[48].mpi_time += t1-t2;
  }

  double p_a3_0 = p_a3[0];
  #pragma omp parallel for reduction(+:p_a3_0)
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
#ifdef intel
#pragma omp simd reduction(+ : p_a3_0)
#else
#pragma simd reduction(+ : p_a3_0)
#endif
    for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
      double *rnn = &p_a3_0;
      
  *rnn = *rnn + (r[OPS_ACC1(0,0)] - rstore[OPS_ACC0(0,0)]) * z[OPS_ACC2(0,0)];

    }
  }
  p_a3[0] = p_a3_0;
  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[48].time += t2-t1;
  }
  ops_set_dirtybit_host(args, 4);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c1,&t1);
    OPS_kernels[48].mpi_time += t1-t2;
    OPS_kernels[48].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[48].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[48].transfer += ops_compute_transfer(dim, start, end, &arg2);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2


void ops_par_loop_tea_leaf_ppcg_reduce_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 48;
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<2; n++ ){
    desc->range[2*n] = sb->decomp_disp[n];desc->range[2*n+1] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (desc->range[2*n] >= range[2*n]) {
      desc->range[2*n] = 0;
    }
    else {
      desc->range[2*n] = range[2*n] - desc->range[2*n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) desc->range[2*n] = range[2*n];
    if (desc->range[2*n+1] >= range[2*n+1]) {
      desc->range[2*n+1] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      desc->range[2*n+1] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      desc->range[2*n+1] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else //OPS_MPI
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
  }
  #endif //OPS_MPI
  desc->nargs = 4;
  desc->args = (ops_arg*)malloc(4*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->args[1] = arg1;
  desc->args[2] = arg2;
  desc->args[3] = arg3;
  desc->function = ops_par_loop_tea_leaf_ppcg_reduce_kernel_execute;
  ops_enqueue_kernel(desc);
  }
