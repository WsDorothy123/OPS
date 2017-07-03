//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_generate_chunk_kernel;
extern int xdim1_generate_chunk_kernel;
extern int xdim2_generate_chunk_kernel;
extern int xdim3_generate_chunk_kernel;
extern int xdim4_generate_chunk_kernel;
extern int xdim5_generate_chunk_kernel;
extern int xdim6_generate_chunk_kernel;
extern int xdim7_generate_chunk_kernel;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7

#define OPS_ACC0(x, y) (x + xdim0_generate_chunk_kernel * (y))
#define OPS_ACC1(x, y) (x + xdim1_generate_chunk_kernel * (y))
#define OPS_ACC2(x, y) (x + xdim2_generate_chunk_kernel * (y))
#define OPS_ACC3(x, y) (x + xdim3_generate_chunk_kernel * (y))
#define OPS_ACC4(x, y) (x + xdim4_generate_chunk_kernel * (y))
#define OPS_ACC5(x, y) (x + xdim5_generate_chunk_kernel * (y))
#define OPS_ACC6(x, y) (x + xdim6_generate_chunk_kernel * (y))
#define OPS_ACC7(x, y) (x + xdim7_generate_chunk_kernel * (y))

// user function

void generate_chunk_kernel_c_wrapper(
    double *p_a0, int base0, int tot0, double *p_a1, int base1, int tot1,
    double *p_a2, int base2, int tot2, double *p_a3, int base3, int tot3,
    double *p_a4, int base4, int tot4, double *p_a5, int base5, int tot5,
    double *p_a6, int base6, int tot6, double *p_a7, int base7, int tot7,
    int x_size, int y_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for num_teams(OPS_threads)        \
    thread_limit(OPS_threads_for_block) schedule(static, 1)
#endif
  for (int i = 0; i < y_size * x_size; i++) {
    int n_x = i % x_size;
    int n_y = i / x_size;
    const double *vertexx =
        p_a0 + base0 + n_x * 1 * 1 + n_y * xdim0_generate_chunk_kernel * 0 * 1;

    const double *vertexy =
        p_a1 + base1 + n_x * 0 * 1 + n_y * xdim1_generate_chunk_kernel * 1 * 1;
    double *energy0 =
        p_a2 + base2 + n_x * 1 * 1 + n_y * xdim2_generate_chunk_kernel * 1 * 1;

    double *density0 =
        p_a3 + base3 + n_x * 1 * 1 + n_y * xdim3_generate_chunk_kernel * 1 * 1;
    double *xvel0 =
        p_a4 + base4 + n_x * 1 * 1 + n_y * xdim4_generate_chunk_kernel * 1 * 1;

    double *yvel0 =
        p_a5 + base5 + n_x * 1 * 1 + n_y * xdim5_generate_chunk_kernel * 1 * 1;
    const double *cellx =
        p_a6 + base6 + n_x * 1 * 1 + n_y * xdim6_generate_chunk_kernel * 0 * 1;

    const double *celly =
        p_a7 + base7 + n_x * 0 * 1 + n_y * xdim7_generate_chunk_kernel * 1 * 1;

    double radius, x_cent, y_cent;
    int is_in = 0;
    int is_in2 = 0;

    energy0[OPS_ACC2(0, 0)] = states[0].energy;
    density0[OPS_ACC3(0, 0)] = states[0].density;
    xvel0[OPS_ACC4(0, 0)] = states[0].xvel;
    yvel0[OPS_ACC5(0, 0)] = states[0].yvel;

    for (int i = 1; i < number_of_states; i++) {

      x_cent = states[i].xmin;
      y_cent = states[i].ymin;
      is_in = 0;
      is_in2 = 0;

      if (states[i].geometry == g_rect) {
        for (int i1 = -1; i1 <= 0; i1++) {
          for (int j1 = -1; j1 <= 0; j1++) {
            if (vertexx[OPS_ACC0(1 + i1, 0)] >= states[i].xmin &&
                vertexx[OPS_ACC0(0 + i1, 0)] < states[i].xmax) {
              if (vertexy[OPS_ACC1(0, 1 + j1)] >= states[i].ymin &&
                  vertexy[OPS_ACC1(0, 0 + j1)] < states[i].ymax) {
                is_in = 1;
              }
            }
          }
        }
        if (vertexx[OPS_ACC0(1, 0)] >= states[i].xmin &&
            vertexx[OPS_ACC0(0, 0)] < states[i].xmax) {
          if (vertexy[OPS_ACC1(0, 1)] >= states[i].ymin &&
              vertexy[OPS_ACC1(0, 0)] < states[i].ymax) {
            is_in2 = 1;
          }
        }
        if (is_in2) {
          energy0[OPS_ACC2(0, 0)] = states[i].energy;
          density0[OPS_ACC3(0, 0)] = states[i].density;
        }
        if (is_in) {
          xvel0[OPS_ACC4(0, 0)] = states[i].xvel;
          yvel0[OPS_ACC5(0, 0)] = states[i].yvel;
        }
      } else if (states[i].geometry == g_circ) {
        for (int i1 = -1; i1 <= 0; i1++) {
          for (int j1 = -1; j1 <= 0; j1++) {
            radius = sqrt((cellx[OPS_ACC6(i1, 0)] - x_cent) *
                              (cellx[OPS_ACC6(i1, 0)] - x_cent) +
                          (celly[OPS_ACC7(0, j1)] - y_cent) *
                              (celly[OPS_ACC7(0, j1)] - y_cent));
            if (radius <= states[i].radius) {
              is_in = 1;
            }
          }
        }
        if (radius <= states[i].radius)
          is_in2 = 1;

        if (is_in2) {
          energy0[OPS_ACC2(0, 0)] = states[i].energy;
          density0[OPS_ACC3(0, 0)] = states[i].density;
        }

        if (is_in) {
          xvel0[OPS_ACC4(0, 0)] = states[i].xvel;
          yvel0[OPS_ACC5(0, 0)] = states[i].yvel;
        }
      } else if (states[i].geometry == g_point) {
        for (int i1 = -1; i1 <= 0; i1++) {
          for (int j1 = -1; j1 <= 0; j1++) {
            if (vertexx[OPS_ACC0(i1, 0)] == x_cent &&
                vertexy[OPS_ACC1(0, j1)] == y_cent) {
              is_in = 1;
            }
          }
        }
        if (vertexx[OPS_ACC0(0, 0)] == x_cent &&
            vertexy[OPS_ACC1(0, 0)] == y_cent)
          is_in2 = 1;

        if (is_in2) {
          energy0[OPS_ACC2(0, 0)] = states[i].energy;
          density0[OPS_ACC3(0, 0)] = states[i].density;
        }

        if (is_in) {
          xvel0[OPS_ACC4(0, 0)] = states[i].xvel;
          yvel0[OPS_ACC5(0, 0)] = states[i].yvel;
        }
      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7