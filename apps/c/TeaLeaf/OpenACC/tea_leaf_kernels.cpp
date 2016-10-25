//
// auto-generated by ops.py//

#include "./OpenACC/tea_leaf_common.h"


void ops_decl_const_char(int dim, char const *type,
int size, char *dat, char const *name){
  if (!strcmp(name,"field")) {
    field = *(field_type*)dat;
  }
  else
  if (!strcmp(name,"grid")) {
    grid = *(grid_type*)dat;
  }
  else
  if (!strcmp(name,"number_of_states")) {
    number_of_states = *(int*)dat;
  }
  else
  if (!strcmp(name,"states")) {
    states = (state_type*)dat;
  }
  else
  if (!strcmp(name,"g_circ")) {
    g_circ = *(int*)dat;
  }
  else
  if (!strcmp(name,"g_point")) {
    g_point = *(int*)dat;
  }
  else
  if (!strcmp(name,"g_rect")) {
    g_rect = *(int*)dat;
  }
  else
  {
    printf("error: unknown const name\n"); exit(1);
  }
}
