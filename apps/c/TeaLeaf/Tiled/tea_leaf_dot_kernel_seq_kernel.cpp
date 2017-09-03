//
// auto-generated by ops.py
//
#define OPS_ACC0(x,y) (n_x*1+n_y*xdim0_tea_leaf_dot_kernel*1+x+xdim0_tea_leaf_dot_kernel*(y))
#define OPS_ACC1(x,y) (n_x*1+n_y*xdim1_tea_leaf_dot_kernel*1+x+xdim1_tea_leaf_dot_kernel*(y))


//user function

// host stub function
void ops_par_loop_tea_leaf_dot_kernel_execute(ops_kernel_descriptor *desc) {
  ops_block block = desc->block;
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[3] = { arg0, arg1, arg2};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,3,range,18)) return;
  #endif

  if (OPS_diags > 1) {
    OPS_kernels[18].count++;
    ops_timers_core(&c2,&t2);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "tea_leaf_dot_kernel");
  #endif



  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  const double * __restrict__ r = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  const double * __restrict__ p = (double *)(args[1].data + base1);

  #ifdef OPS_MPI
  double * __restrict__ p_a2 = (double *)(((ops_reduction)args[2].data)->data + ((ops_reduction)args[2].data)->size * block->index);
  #else //OPS_MPI
  double * __restrict__ p_a2 = (double *)((ops_reduction)args[2].data)->data;
  #endif //OPS_MPI



  //initialize global variable with the dimension of dats
  int xdim0_tea_leaf_dot_kernel = args[0].dat->size[0];
  int xdim1_tea_leaf_dot_kernel = args[1].dat->size[0];

  if (OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_kernels[18].mpi_time += t1-t2;
  }

  double p_a2_0 = p_a2[0];
  #pragma omp parallel for reduction(+:p_a2_0)
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #ifdef intel
    #pragma loop_count(10000)
    #pragma omp simd reduction(+:p_a2_0) aligned(r,p)
    #else
    #pragma simd reduction(+:p_a2_0)
    #endif
    for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
      double *rro = &p_a2_0;
      
  *rro = *rro + r[OPS_ACC0(0,0)] * p[OPS_ACC1(0,0)];

    }
  }
  p_a2[0] = p_a2_0;
  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[18].time += t2-t1;
  }

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c1,&t1);
    OPS_kernels[18].mpi_time += t1-t2;
    OPS_kernels[18].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[18].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1


void ops_par_loop_tea_leaf_dot_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 18;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 18;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 3;
  desc->args = (ops_arg*)malloc(3*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  desc->function = ops_par_loop_tea_leaf_dot_kernel_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(18,"tea_leaf_dot_kernel");
  }
  ops_enqueue_kernel(desc);
  }
