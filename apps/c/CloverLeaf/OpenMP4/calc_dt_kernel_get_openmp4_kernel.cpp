//
// auto-generated by ops.py
//
#include "./OpenMP4/calc_dt_kernel_get_openmp4_kernel_c.c"
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

int xdim0_calc_dt_kernel_get;
int xdim0_calc_dt_kernel_get_h = -1;
int xdim1_calc_dt_kernel_get;
int xdim1_calc_dt_kernel_get_h = -1;

void ops_par_loop_calc_dt_kernel_get(char const *name, ops_block block, int dim,
                                     int *range, ops_arg arg0, ops_arg arg1,
                                     ops_arg arg2, ops_arg arg3) {

  // Timing
  double t1, t2, c1, c2;
  ops_arg args[4] = {arg0, arg1, arg2, arg3};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 4, range, 29))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(29, "calc_dt_kernel_get");
    OPS_kernels[29].count++;
    ops_timers_core(&c1, &t1);
  }

  // compute localy allocated range for the sub-block

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

  xdim0 = args[0].dat->size[0];
  xdim1 = args[1].dat->size[0];
  if (xdim0 != xdim0_calc_dt_kernel_get_h ||
      xdim1 != xdim1_calc_dt_kernel_get_h) {
    xdim0_calc_dt_kernel_get = xdim0;
    xdim0_calc_dt_kernel_get_h = xdim0;
    xdim1_calc_dt_kernel_get = xdim1;
    xdim1_calc_dt_kernel_get_h = xdim1;
  }

  int tot0 = 1;
  for (int i = 0; i < args[0].dat->block->dims; i++)
    tot0 = tot0 * args[0].dat->size[i];
  int tot1 = 1;
  for (int i = 0; i < args[1].dat->block->dims; i++)
    tot1 = tot1 * args[1].dat->size[i];
#ifdef OPS_MPI
  double *arg2h =
      (double *)(((ops_reduction)args[2].data)->data +
                 ((ops_reduction)args[2].data)->size * block->index);
#else
  double *arg2h = (double *)(((ops_reduction)args[2].data)->data);
#endif
#ifdef OPS_MPI
  double *arg3h =
      (double *)(((ops_reduction)args[3].data)->data +
                 ((ops_reduction)args[3].data)->size * block->index);
#else
  double *arg3h = (double *)(((ops_reduction)args[3].data)->data);
#endif

  // set up initial pointers
  int base0 = args[0].dat->base_offset +
              args[0].dat->elem_size * start[0] * args[0].stencil->stride[0];
  base0 = base0 +
          args[0].dat->elem_size * args[0].dat->size[0] * start[1] *
              args[0].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a0 = (double *)((char *)args[0].data);
#else
  double *p_a0 = (double *)((char *)args[0].data + base0);
#endif

  int base1 = args[1].dat->base_offset +
              args[1].dat->elem_size * start[0] * args[1].stencil->stride[0];
  base1 = base1 +
          args[1].dat->elem_size * args[1].dat->size[0] * start[1] *
              args[1].stencil->stride[1];
#ifdef OPS_GPU
  double *p_a1 = (double *)((char *)args[1].data);
#else
  double *p_a1 = (double *)((char *)args[1].data + base1);
#endif

  double *p_a2 = arg2h;
  double *p_a3 = arg3h;

#ifdef OPS_GPU
  for (int n = 0; n < 4; n++)
    if (args[n].argtype == OPS_ARG_DAT && args[n].dat->dirty_hd == 1) {
      int size = 1;
      for (int i = 0; i < args[n].dat->block->dims; i++)
        size += size * args[n].dat->size[i];
#pragma omp target update to(args[n].dat->data[0 : size])
      args[n].dat->dirty_hd = 0;
    }
// ops_H_D_exchanges_device(args, 4);
#else
  for (int n = 0; n < 4; n++)
    if (args[n].argtype == OPS_ARG_DAT && args[n].dat->dirty_hd == 2) {
      int size = 1;
      for (int i = 0; i < args[n].dat->block->dims; i++)
        size += size * args[n].dat->size[i];
#pragma omp target update from(args[n].dat->data[0 : size])
      args[n].dat->dirty_hd = 0;
    }
// ops_H_D_exchanges_host(args, 4);
#endif
  ops_halo_exchanges(args, 4, range);

#ifdef OPS_GPU
// ops_H_D_exchanges_device(args, 4);
#else
// ops_H_D_exchanges_host(args, 4);
#endif
  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[29].mpi_time += t2 - t1;
  }

  calc_dt_kernel_get_c_wrapper(p_a0, base0 / args[0].dat->elem_size, tot0, p_a1,
                               base1 / args[1].dat->elem_size, tot1, p_a2, p_a3,
                               x_size, y_size);

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[29].time += t1 - t2;
  }
#ifdef OPS_GPU
  // for (int n = 0; n < 4; n++) {
  // if ((args[n].argtype == OPS_ARG_DAT) &&
  //(args[n].acc == OPS_INC || args[n].acc == OPS_WRITE ||
  // args[n].acc == OPS_RW)) {
  // args[n].dat->dirty_hd = 2;
  //}
  //}
  ops_set_dirtybit_device(args, 4);
#else
  // for (int n = 0; n < 4; n++) {
  // if ((args[n].argtype == OPS_ARG_DAT) &&
  //(args[n].acc == OPS_INC || args[n].acc == OPS_WRITE ||
  // args[n].acc == OPS_RW)) {
  // args[n].dat->dirty_hd = 1;
  //}
  //}
  ops_set_dirtybit_host(args, 4);
#endif

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[29].mpi_time += t2 - t1;
    OPS_kernels[29].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[29].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}