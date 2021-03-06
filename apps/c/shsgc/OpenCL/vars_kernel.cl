//
// auto-generated by ops.py
//

#ifdef OCL_FMA
#pragma OPENCL FP_CONTRACT ON
#else
#pragma OPENCL FP_CONTRACT OFF
#endif
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#include "ops_opencl_reduction.h"

#ifndef MIN
#define MIN(a, b) ((a < b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a > b) ? (a) : (b))
#endif
#ifndef SIGN
#define SIGN(a, b) ((b < 0.0) ? (a * (-1)) : (a))
#endif
#define OPS_READ 0
#define OPS_WRITE 1
#define OPS_RW 2
#define OPS_INC 3
#define OPS_MIN 4
#define OPS_MAX 5
#define ZERO_double 0.0;
#define INFINITY_double INFINITY;
#define ZERO_float 0.0f;
#define INFINITY_float INFINITY;
#define ZERO_int 0;
#define INFINITY_int INFINITY;
#define ZERO_uint 0;
#define INFINITY_uint INFINITY;
#define ZERO_ll 0;
#define INFINITY_ll INFINITY;
#define ZERO_ull 0;
#define INFINITY_ull INFINITY;
#define ZERO_bool 0;

#undef OPS_ACC_MD0
#undef OPS_ACC_MD1
#undef OPS_ACC_MD2
#undef OPS_ACC_MD3
#undef OPS_ACC_MD4

#define OPS_ACC_MD0(d, x) ((x)*3 + (d))
#define OPS_ACC_MD1(d, x) ((x)*3 + (d))
#define OPS_ACC_MD2(d, x) ((x)*3 + (d))
#define OPS_ACC_MD3(d, x) ((x)*3 + (d))
#define OPS_ACC_MD4(d, x) ((x)*3 + (d))

// user function
void vars_kernel(const __global double *restrict alam,
                 const __global double *restrict al,
                 const __global double *restrict gt,
                 __global double *restrict cmp, __global double *restrict cf,
                 const double del2, const double con)

{

  double anu, aaa, ga, qf, ww;
  for (int m = 0; m < 3; m++) {
    anu = alam[OPS_ACC_MD0(m, 0)];
    aaa = al[OPS_ACC_MD1(m, 0)];
    ga = aaa * (gt[OPS_ACC_MD2(m, 1)] - gt[OPS_ACC_MD2(m, 0)]) /
         (pow(aaa, 2.0) + del2);
    qf = sqrt(con + pow(anu, 2.0));
    cmp[OPS_ACC_MD3(m, 0)] = 0.50 * qf;
    ww = anu + cmp[OPS_ACC_MD3(m, 0)] * ga;
    qf = sqrt(con + pow(ww, 2.0));
    cf[OPS_ACC_MD4(m, 0)] = qf;
  }
}

__kernel void ops_vars_kernel(__global const double *restrict arg0,
                              __global const double *restrict arg1,
                              __global const double *restrict arg2,
                              __global double *restrict arg3,
                              __global double *restrict arg4, const double del2,
                              const double con, const int base0,
                              const int base1, const int base2, const int base3,
                              const int base4, const int size0) {

  int idx_x = get_global_id(0);

  if (idx_x < size0) {
    vars_kernel(&arg0[base0 + idx_x * 1 * 3], &arg1[base1 + idx_x * 1 * 3],
                &arg2[base2 + idx_x * 1 * 3], &arg3[base3 + idx_x * 1 * 3],
                &arg4[base4 + idx_x * 1 * 3], del2, con);
  }
}
