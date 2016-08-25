//
// auto-generated by ops.py//

// header
#define OPS_ACC_MD_MACROS
#define OPS_2D
#include "ops_lib_cpp.h"
#include "ops_opencl_rt_support.h"
#include "stdio.h"
#include "stdlib.h"
#ifdef OPS_MPI
#include "ops_mpi_core.h"
#endif
// global constants

extern ops_opencl_core OPS_opencl_core;

// this needs to be a platform specific copy symbol to device function
void ops_decl_const_char(int dim, char const *type, int typeSize, char *dat,
                         char const *name) {
  cl_int ret = 0;
  if (OPS_opencl_core.constant == NULL) {
    OPS_opencl_core.constant = (cl_mem *)malloc((0) * sizeof(cl_mem));
    for (int i = 0; i < 0; i++) {
      OPS_opencl_core.constant[i] = NULL;
    }
  }
  {
    printf("error: unknown const name\n");
    exit(1);
  }
}

extern ops_opencl_core OPS_opencl_core;

void buildOpenCLKernels() {
  static bool isbuilt = false;

  if (!isbuilt) {
    // clSafeCall( clUnloadCompiler() );

    OPS_opencl_core.n_kernels = 0;
    OPS_opencl_core.kernel = (cl_kernel *)malloc(0 * sizeof(cl_kernel));
  }
  isbuilt = true;
}

// user kernel files
