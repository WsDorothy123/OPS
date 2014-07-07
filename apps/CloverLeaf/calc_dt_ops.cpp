//
// auto-generated by ops.py on 2014-07-07 13:31
//



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include  "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_calc_dt_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_calc_dt_kernel_min(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg );

void ops_par_loop_calc_dt_kernel_get(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_calc_dt_kernel_print(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );



#include "data.h"
#include "definitions.h"

//#include "calc_dt_kernel.h"

void calc_dt(double* local_dt, char* local_control,
             double* xl_pos, double* yl_pos, int* jldt, int* kldt)
{
  int small;
  double jk_control = 1.1;

  *local_dt = g_big;
  small = 0;

  int dtl_control;

  int x_cells = grid.x_cells;
  int y_cells = grid.y_cells;
  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;

  int rangexy_inner[] = {x_min,x_max,y_min,y_max};

  ops_par_loop_calc_dt_kernel("calc_dt_kernel", clover_grid, 2, rangexy_inner,
               ops_arg_dat(celldx, S2D_00_P10_STRID2D_X, "double", OPS_READ),
               ops_arg_dat(celldy, S2D_00_0P1_STRID2D_Y, "double", OPS_READ),
               ops_arg_dat(soundspeed, S2D_00, "double", OPS_READ),
               ops_arg_dat(viscosity, S2D_00, "double", OPS_READ),
               ops_arg_dat(density0, S2D_00, "double", OPS_READ),
               ops_arg_dat(xvel0, S2D_00_P10_0P1_P1P1, "double", OPS_READ),
               ops_arg_dat(xarea, S2D_00_P10, "double", OPS_READ),
               ops_arg_dat(volume, S2D_00, "double", OPS_READ),
               ops_arg_dat(yvel0, S2D_00_P10_0P1_P1P1, "double", OPS_READ),
               ops_arg_dat(yarea, S2D_00_0P1, "double", OPS_READ),
               ops_arg_dat(work_array1, S2D_00, "double", OPS_WRITE));

  ops_par_loop_calc_dt_kernel_min("calc_dt_kernel_min", clover_grid, 2, rangexy_inner,
               ops_arg_dat(work_array1, S2D_00, "double", OPS_READ),
               ops_arg_gbl(local_dt, 1, "double", OPS_MIN));


  dtl_control = 10.01 * (jk_control - (int)(jk_control));
  jk_control = jk_control - (jk_control - (int)(jk_control));


  *jldt = ((int)jk_control)%(x_max-2);
  *kldt = 1 + (jk_control/(x_max-2));

  int rangexy_getpoint[] = {*jldt-1+2,*jldt+2,*kldt-1+2,*kldt+2};

  int rangexy_getpointx[] = {*jldt-1+2,*jldt+2,y_min-2,y_max+2};
  int rangexy_getpointy[] = {x_min-2,x_max+2,*kldt-1+2,*kldt+2};

  if(*local_dt < dtmin) small = 1;

  ops_par_loop_calc_dt_kernel_get("calc_dt_kernel_getx", clover_grid, 2, rangexy_getpoint,
               ops_arg_dat(cellx, S2D_00_STRID2D_X, "double", OPS_READ),
               ops_arg_dat(celly, S2D_00_STRID2D_Y, "double", OPS_READ),
               ops_arg_gbl(xl_pos, 1, "double", OPS_INC),
               ops_arg_gbl(yl_pos, 1, "double", OPS_INC));

  if(small != 0) {
    ops_printf("Timestep information:\n");
    ops_printf("j, k                 : %d, %d\n",*jldt,*kldt);
    ops_printf("x, y                 : %lf, %lf\n",*xl_pos,*xl_pos);
    ops_printf("timestep : %lf\n",*local_dt);

    double output[12] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    ops_par_loop_calc_dt_kernel_print("calc_dt_kernel_print", clover_grid, 2, rangexy_getpoint,
                 ops_arg_dat(xvel0, S2D_10_M10_01_0M1, "double", OPS_READ),
                 ops_arg_dat(yvel0, S2D_10_M10_01_0M1, "double", OPS_READ),
                 ops_arg_dat(density0, S2D_00, "double", OPS_READ),
                 ops_arg_dat(energy0, S2D_00, "double", OPS_READ),
                 ops_arg_dat(pressure, S2D_00, "double", OPS_READ),
                 ops_arg_dat(soundspeed, S2D_00, "double", OPS_READ),
                 ops_arg_gbl(output, 12, "double", OPS_INC));

    ops_printf("Cell velocities:\n");
    ops_printf("%E, %E \n",output[0],output[1]);
    ops_printf("%E, %E \n",output[2],output[3]);
    ops_printf("%E, %E \n",output[4],output[5]);
    ops_printf("%E, %E \n",output[6],output[7]);

    ops_printf("density, energy, pressure, soundspeed = %lf, %lf, %lf, %lf \n",
        output[8], output[9], output[10], output[11]);
  }

  if(dtl_control == 1) sprintf(local_control, "sound");
  if(dtl_control == 2) sprintf(local_control, "xvel");
  if(dtl_control == 3) sprintf(local_control, "yvel");
  if(dtl_control == 4) sprintf(local_control, "div");

}
