//
// auto-generated by ops.py on 2013-10-17 15:26
//

#include "lib.h"
//user function
#include "revert_kernel.h"

// host stub function
void ops_par_loop_revert_kernel(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {

  char **p_a[4];
  int  offs[4][2];
  int  count[dim];

  ops_arg args[4] = { arg0, arg1, arg2, arg3};


  for ( int i=0; i<4; i++ ){
    if (args[i].stencil!=NULL) {
      offs[i][0] = 1;  //unit step in x dimension
      offs[i][1] = ops_offs_set(range[0],range[2]+1, args[i]) - ops_offs_set(range[1],range[2], args[i]) +1;
      //stride in y as x stride is 0
      if (args[i].stencil->stride[0] == 0) {
        offs[i][0] = 0;
        offs[i][1] = args[i].dat->block_size[0];
      }
      //stride in x as y stride is 0
      else if (args[i].stencil->stride[1] == 0) {
        offs[i][0] = 1;
        offs[i][1] = -( range[1] - range[0] ) +1;
      }
    }
  }
  //store index of non_gbl args

  int non_gbl[4] = {0, 0, 0, 0};
  int g = 0;

  for ( int i=0; i<4; i++ ){
    if (args[i].argtype == OPS_ARG_DAT) {
      p_a[i] = (char **)malloc(args[i].stencil->points * sizeof(char *));
      non_gbl[g++] = i;
    }
    else if (args[i].argtype == OPS_ARG_GBL) {
      p_a[i] = (char **)malloc(args[i].dim * sizeof(char *));
    }
  }
  int total_range = 1;
  for ( int m=0; m<dim; m++ ){
    //number in each dimension
    count[m] = range[2*m+1]-range[2*m];
    total_range *= count[m];
  }
  //extra in last to ensure correct termination
  count[dim-1]++;


  //set up initial pointers
  ops_args_set(range[0], range[2], 4, args,p_a); //set up the initial possition


  for ( int nt=0; nt<total_range; nt++ ){
    //call kernel function, passing in pointers to data

    revert_kernel(  (double **)p_a[0], (double **)p_a[1], (double **)p_a[2],
           (double **)p_a[3] );

    //decrement counter
    count[0]--;

    //max dimension with changed index
    int m = 0;
    while ( (count[m]==0) ){
      count[m] = range[2*m+1]-range[2*m]; // reset counter
      m++;                                // next dimension
      count[m]--;                         // decrement counter
    }

    int a = 0;
    //shift pointers to data
    for ( int i=0; i<g; i++ ){
      a = non_gbl[i];
      for ( int np=0; np<args[a].stencil->points; np++ ){
        p_a[a][np] = p_a[a][np] + (args[a].dat->size * offs[a][m]);
      }
    }
  }

  for ( int i=0; i<4; i++ ){
    free(p_a[i]);
  }
}
