//
// auto-generated by ops.py//

//header
#include "ops_lib_cpp.h"
#include "ops_cuda_rt_support.h"
#include "ops_cuda_reduction.h"
#ifdef OPS_MPI
#include "ops_mpi_core.h"
#endif

// global constants

void ops_decl_const_char(int dim, char const *type,
int size, char *dat, char const *name){
  {
    printf("error: unknown const name\n"); exit(1);
  }
}


//user kernel files
#include "mblock_populate_kernel_cuda_kernel.cu"
