//
// auto-generated by ops.py
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPS_2D
#include "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_advec_cell_kernel1_xdir(char const *, ops_block, int, int *,
                                          ops_arg, ops_arg, ops_arg, ops_arg,
                                          ops_arg);

void ops_par_loop_advec_cell_kernel2_xdir(char const *, ops_block, int, int *,
                                          ops_arg, ops_arg, ops_arg, ops_arg);

void ops_par_loop_advec_cell_kernel3_xdir(char const *, ops_block, int, int *,
                                          ops_arg, ops_arg, ops_arg, ops_arg,
                                          ops_arg, ops_arg, ops_arg, ops_arg);

void ops_par_loop_advec_cell_kernel4_xdir(char const *, ops_block, int, int *,
                                          ops_arg, ops_arg, ops_arg, ops_arg,
                                          ops_arg, ops_arg, ops_arg, ops_arg,
                                          ops_arg, ops_arg, ops_arg);

void ops_par_loop_advec_cell_kernel1_ydir(char const *, ops_block, int, int *,
                                          ops_arg, ops_arg, ops_arg, ops_arg,
                                          ops_arg);

void ops_par_loop_advec_cell_kernel2_ydir(char const *, ops_block, int, int *,
                                          ops_arg, ops_arg, ops_arg, ops_arg);

void ops_par_loop_advec_cell_kernel3_ydir(char const *, ops_block, int, int *,
                                          ops_arg, ops_arg, ops_arg, ops_arg,
                                          ops_arg, ops_arg, ops_arg, ops_arg);

void ops_par_loop_advec_cell_kernel4_ydir(char const *, ops_block, int, int *,
                                          ops_arg, ops_arg, ops_arg, ops_arg,
                                          ops_arg, ops_arg, ops_arg, ops_arg,
                                          ops_arg, ops_arg, ops_arg);

#include "data.h"
#include "definitions.h"
//#include "advec_cell_kernel.h"

void advec_cell(int sweep_number, int dir) {

  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;

  int rangexy[] = {x_min - 2, x_max + 2, y_min - 2, y_max + 2};
  int rangexy_inner[] = {x_min, x_max, y_min, y_max};

  int rangexy_inner_plus2x[] = {x_min, x_max + 2, y_min, y_max};
  int rangexy_inner_plus2y[] = {x_min, x_max, y_min, y_max + 2};

  if (dir == g_xdir) {

    if (sweep_number == 1) {
      ops_par_loop_advec_cell_kernel1_xdir(
          "advec_cell_kernel1_xdir", clover_grid, 2, rangexy,
          ops_arg_dat(work_array1, 1, S2D_00, "double", OPS_WRITE),
          ops_arg_dat(work_array2, 1, S2D_00, "double", OPS_WRITE),
          ops_arg_dat(volume, 1, S2D_00, "double", OPS_READ),
          ops_arg_dat(vol_flux_x, 1, S2D_00_P10, "double", OPS_READ),
          ops_arg_dat(vol_flux_y, 1, S2D_00_0P1, "double", OPS_READ));
    } else {
      ops_par_loop_advec_cell_kernel2_xdir(
          "advec_cell_kernel2_xdir", clover_grid, 2, rangexy,
          ops_arg_dat(work_array1, 1, S2D_00, "double", OPS_WRITE),
          ops_arg_dat(work_array2, 1, S2D_00, "double", OPS_WRITE),
          ops_arg_dat(volume, 1, S2D_00, "double", OPS_READ),
          ops_arg_dat(vol_flux_x, 1, S2D_00_P10, "double", OPS_READ));
    }

    ops_par_loop_advec_cell_kernel3_xdir(
        "advec_cell_kernel3_xdir", clover_grid, 2, rangexy_inner_plus2x,
        ops_arg_dat(vol_flux_x, 1, S2D_00, "double", OPS_READ),
        ops_arg_dat(work_array1, 1, S2D_00_M10, "double", OPS_READ),
        ops_arg_dat(xx, 1, S2D_00_P10_STRID2D_X, "int", OPS_READ),
        ops_arg_dat(vertexdx, 1, S2D_00_P10_M10_STRID2D_X, "double", OPS_READ),
        ops_arg_dat(density1, 1, S2D_00_P10_M10_M20, "double", OPS_READ),
        ops_arg_dat(energy1, 1, S2D_00_P10_M10_M20, "double", OPS_READ),
        ops_arg_dat(mass_flux_x, 1, S2D_00, "double", OPS_WRITE),
        ops_arg_dat(work_array7, 1, S2D_00, "double", OPS_WRITE));

    ops_par_loop_advec_cell_kernel4_xdir(
        "advec_cell_kernel4_xdir", clover_grid, 2, rangexy_inner,
        ops_arg_dat(density1, 1, S2D_00, "double", OPS_RW),
        ops_arg_dat(energy1, 1, S2D_00, "double", OPS_RW),
        ops_arg_dat(mass_flux_x, 1, S2D_00_P10, "double", OPS_READ),
        ops_arg_dat(vol_flux_x, 1, S2D_00_P10, "double", OPS_READ),
        ops_arg_dat(work_array1, 1, S2D_00, "double", OPS_READ),
        ops_arg_dat(work_array2, 1, S2D_00, "double", OPS_READ),
        ops_arg_dat(work_array3, 1, S2D_00, "double", OPS_WRITE),
        ops_arg_dat(work_array4, 1, S2D_00, "double", OPS_WRITE),
        ops_arg_dat(work_array5, 1, S2D_00, "double", OPS_WRITE),
        ops_arg_dat(work_array6, 1, S2D_00, "double", OPS_WRITE),
        ops_arg_dat(work_array7, 1, S2D_00_P10, "double", OPS_READ));

  } else {

    if (sweep_number == 1) {
      ops_par_loop_advec_cell_kernel1_ydir(
          "advec_cell_kernel1_ydir", clover_grid, 2, rangexy,
          ops_arg_dat(work_array1, 1, S2D_00, "double", OPS_WRITE),
          ops_arg_dat(work_array2, 1, S2D_00, "double", OPS_WRITE),
          ops_arg_dat(volume, 1, S2D_00, "double", OPS_READ),
          ops_arg_dat(vol_flux_x, 1, S2D_00_P10, "double", OPS_READ),
          ops_arg_dat(vol_flux_y, 1, S2D_00_0P1, "double", OPS_READ));
    } else {

      ops_par_loop_advec_cell_kernel2_ydir(
          "advec_cell_kernel2_ydir", clover_grid, 2, rangexy,
          ops_arg_dat(work_array1, 1, S2D_00, "double", OPS_WRITE),
          ops_arg_dat(work_array2, 1, S2D_00, "double", OPS_WRITE),
          ops_arg_dat(volume, 1, S2D_00, "double", OPS_READ),
          ops_arg_dat(vol_flux_y, 1, S2D_00_0P1, "double", OPS_READ));
    }

    ops_par_loop_advec_cell_kernel3_ydir(
        "advec_cell_kernel3_ydir", clover_grid, 2, rangexy_inner_plus2y,
        ops_arg_dat(vol_flux_y, 1, S2D_00, "double", OPS_READ),
        ops_arg_dat(work_array1, 1, S2D_00_0M1, "double", OPS_READ),
        ops_arg_dat(yy, 1, S2D_00_0P1_STRID2D_Y, "int", OPS_READ),
        ops_arg_dat(vertexdy, 1, S2D_00_0P1_0M1_STRID2D_Y, "double", OPS_READ),
        ops_arg_dat(density1, 1, S2D_00_0P1_0M1_0M2, "double", OPS_READ),
        ops_arg_dat(energy1, 1, S2D_00_0P1_0M1_0M2, "double", OPS_READ),
        ops_arg_dat(mass_flux_y, 1, S2D_00, "double", OPS_WRITE),
        ops_arg_dat(work_array7, 1, S2D_00, "double", OPS_WRITE));

    ops_par_loop_advec_cell_kernel4_ydir(
        "advec_cell_kernel4_ydir", clover_grid, 2, rangexy_inner,
        ops_arg_dat(density1, 1, S2D_00, "double", OPS_RW),
        ops_arg_dat(energy1, 1, S2D_00, "double", OPS_RW),
        ops_arg_dat(mass_flux_y, 1, S2D_00_0P1, "double", OPS_READ),
        ops_arg_dat(vol_flux_y, 1, S2D_00_0P1, "double", OPS_READ),
        ops_arg_dat(work_array1, 1, S2D_00, "double", OPS_READ),
        ops_arg_dat(work_array2, 1, S2D_00, "double", OPS_READ),
        ops_arg_dat(work_array3, 1, S2D_00, "double", OPS_WRITE),
        ops_arg_dat(work_array4, 1, S2D_00, "double", OPS_WRITE),
        ops_arg_dat(work_array5, 1, S2D_00, "double", OPS_WRITE),
        ops_arg_dat(work_array6, 1, S2D_00, "double", OPS_WRITE),
        ops_arg_dat(work_array7, 1, S2D_00_0P1, "double", OPS_READ));
  }
}
