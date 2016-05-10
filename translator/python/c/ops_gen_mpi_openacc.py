
# Open source copyright declaration based on BSD open source template:
# http://www.opensource.org/licenses/bsd-license.php
#
# This file is part of the OPS distribution.
#
# Copyright (c) 2013, Mike Giles and others. Please see the AUTHORS file in
# the main source directory for a full list of copyright holders.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
# Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
# The name of Mike Giles may not be used to endorse or promote products
# derived from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED BY Mike Giles ''AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL Mike Giles BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

"""
OPS OpenMP code generator

This routine is called by ops.py which parses the input files

It produces a file xxx_omp_kernel.cpp for each kernel,
plus a master kernel file

"""

import re
import datetime
import os
import glob

import util
import config

para_parse = util.para_parse
comment_remover = util.comment_remover
remove_trailing_w_space = util.remove_trailing_w_space
parse_signature = util.parse_signature_openacc
check_accs = util.check_accs
mult = util.mult

comm = util.comm
code = util.code
FOR = util.FOR
FOR2 = util.FOR2
WHILE = util.WHILE
ENDWHILE = util.ENDWHILE
ENDFOR = util.ENDFOR
IF = util.IF
ELSEIF = util.ELSEIF
ELSE = util.ELSE
ENDIF = util.ENDIF

def ops_gen_mpi_openacc(master, date, consts, kernels):

  OPS_ID   = 1;  OPS_GBL   = 2;

  OPS_READ = 1;  OPS_WRITE = 2;  OPS_RW  = 3;
  OPS_INC  = 4;  OPS_MAX   = 5;  OPS_MIN = 6;

  accsstring = ['OPS_READ','OPS_WRITE','OPS_RW','OPS_INC','OPS_MAX','OPS_MIN' ]

  NDIM = 2 #the dimension of the application is hardcoded here .. need to get this dynamically


##########################################################################
#  create new kernel file
##########################################################################

  for nk in range (0,len(kernels)):
    arg_typ  = kernels[nk]['arg_type']
    name  = kernels[nk]['name']
    nargs = kernels[nk]['nargs']
    dim   = kernels[nk]['dim']
    dims  = kernels[nk]['dims']
    stens = kernels[nk]['stens']
    var   = kernels[nk]['var']
    accs  = kernels[nk]['accs']
    typs  = kernels[nk]['typs']
    NDIM = int(dim)
    #parse stencil to locate strided access
    stride = [1] * nargs * NDIM

    restrict = [1] * nargs
    prolong = [1] * nargs

    if NDIM == 2:
      for n in range (0, nargs):
        if str(stens[n]).find('STRID2D_X') > 0:
          stride[NDIM*n+1] = 0
        elif str(stens[n]).find('STRID2D_Y') > 0:
          stride[NDIM*n] = 0

    if NDIM == 3:
      for n in range (0, nargs):
        if str(stens[n]).find('STRID3D_X') > 0:
          stride[NDIM*n+1] = 0
          stride[NDIM*n+2] = 0
        elif str(stens[n]).find('STRID3D_Y') > 0:
          stride[NDIM*n] = 0
          stride[NDIM*n+2] = 0
        elif str(stens[n]).find('STRID3D_Z') > 0:
          stride[NDIM*n] = 0
          stride[NDIM*n+1] = 0

    ### Determine if this is a MULTI_GRID LOOP with
    ### either restrict or prolong
    MULTI_GRID = 0
    for n in range (0, nargs):
      restrict[n] = 0
      prolong[n] = 0
      if str(stens[n]).find('RESTRICT') > 0:
        restrict[n] = 1
        MULTI_GRID = 1
      if str(stens[n]).find('PROLONG') > 0 :
        prolong[n] = 1
        MULTI_GRID = 1

    reduct = 0
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_gbl' and accs[n] <> OPS_READ:
        reduct = 1

    config.file_text = ''
    config.depth = 0
    n_per_line = 2

    if NDIM==3:
      n_per_line = 1

    i = name.find('kernel')
    name2 = name[0:i-1]

    reduction = False
    ng_args = 0

    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_gbl':
        reduction = True
      else:
        ng_args = ng_args + 1


    arg_idx = 0
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_idx':
        arg_idx = 1

##########################################################################
#  generate constants and MACROS
##########################################################################

    code('#include "./OpenACC/'+master.split('.')[0]+'_common.h"')
    code('')
    if not (('generate_chunk' in name) or ('calc_dt_kernel_print' in name)):
      if not (NDIM==3 and 'field_summary' in name):
        code('#define OPS_GPU')
        code('')
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        code('int xdim'+str(n)+'_'+name+';')
        if NDIM==3:
          code('int ydim'+str(n)+'_'+name+';')
#        code('#pragma acc declare create(xdim'+str(n)+'_'+name+')')
    code('')

    code('')
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        if int(dims[n]) == 1:
          code('#undef OPS_ACC'+str(n))
    code('')
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        if int(dims[n]) > 1:
          code('#undef OPS_ACC_MD'+str(n))
    code('')

    #code('#define OPS_ACC_MACROS')
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        if int(dims[n]) == 1:
          if NDIM==1:
            code('#define OPS_ACC'+str(n)+'(x) (x)')
          if NDIM==2:
            code('#define OPS_ACC'+str(n)+'(x,y) (x+xdim'+str(n)+'_'+name+'*(y))')
          if NDIM==3:
            code('#define OPS_ACC'+str(n)+'(x,y,z) (x+xdim'+str(n)+'_'+name+'*(y)+xdim'+str(n)+'_'+name+'*ydim'+str(n)+'_'+name+'*(z))')
    code('')

    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        if int(dims[n]) > 1:
          if NDIM==1:
            code('#define OPS_ACC_MD'+str(n)+'(d,x) ((x)*'+str(dims[n])+'+(d))')
          if NDIM==2:
            code('#define OPS_ACC_MD'+str(n)+'(d,x,y) ((x)*'+str(dims[n])+'+(d)+(xdim'+str(n)+'_'+name+'*(y)*'+str(dims[n])+'))')
          if NDIM==3:
            code('#define OPS_ACC_MD'+str(n)+'(d,x,y,z) ((x)*'+str(dims[n])+'+(d)+(xdim'+str(n)+'_'+name+'*(y)*'+str(dims[n])+')+(xdim'+str(n)+'_'+name+'*ydim'+str(n)+'_'+name+'*(z)*'+str(dims[n])+'))')



##########################################################################
#  generate headder
##########################################################################

    comm('user function')
    found = 0
    for files in glob.glob( "*.h" ):
      f = open( files, 'r' )
      for line in f:
        if name in line:
          file_name = f.name
          found = 1;
          break
      if found == 1:
        break;

    if found == 0:
      print "COUND NOT FIND KERNEL", name

    fid = open(file_name, 'r')
    text = fid.read()

    fid.close()
    text = comment_remover(text)
    text = remove_trailing_w_space(text)

    p = re.compile('void\\s+\\b'+name+'\\b')
    i = p.search(text).start()

    if(i < 0):
      print "\n********"
      print "Error: cannot locate user kernel function: "+name+" - Aborting code generation"
      exit(2)

    i = text[0:i].rfind('\n') #reverse find
    j = text[i:].find('{')
    k = para_parse(text, i+j, '{', '}')
    m = text.find(name)
    l = text[i:m].find('inline')
    if(l<0):
      code('inline'+text[i:k+2])
    else:
      code(text[i:k+2])
    code('')


    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        if int(dims[n]) == 1:
          code('#undef OPS_ACC'+str(n))
    code('')
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        if int(dims[n]) > 1:
          code('#undef OPS_ACC_MD'+str(n))
    code('')
    code('')

##########################################################################
#  generate C wrapper
##########################################################################
    code('void '+name+'_c_wrapper(')
    config.depth = config.depth+2
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_gbl' and accs[n] == OPS_READ and dims[n].isdigit() and int(dims[n])==1:
        code(typs[n]+' p_a'+str(n)+',')
      else:
        code(typs[n]+' *p_a'+str(n)+',')
        if restrict[n] or prolong[n]:
          code('int *stride_'+str(n)+',')
    if arg_idx:
      if NDIM == 1:
        code('int arg_idx0,')
      elif NDIM == 2:
        code('int arg_idx0, int arg_idx1,')
      elif NDIM == 3:
        code('int arg_idx0, int arg_idx1, int arg_idx2,')

    if MULTI_GRID:
      if NDIM == 1:
        code('int global_idx0,')
      elif NDIM == 2:
        code('int global_idx0, int global_idx1,')
      elif NDIM == 3:
        code('int global_idx0, int global_idx1, int global_idx2,')

    if NDIM == 1:
      code('int x_size) {')
    elif NDIM == 2:
      code('int x_size, int y_size) {')
    elif NDIM == 3:
      code('int x_size, int y_size, int z_size) {')


    for n in range (0,nargs):
      if arg_typ[n] == 'ops_arg_gbl':
        if accs[n] <> OPS_READ:
          #if dims[n].isdigit() and int(dims[n]) == 1:
          #  code(typs[n]+' p_a'+str(n)+'_l = *p_a'+str(n)+';')
          #else:
          for d in range(0,int(dims[n])):
            code(typs[n]+' p_a'+str(n)+'_'+str(d)+' = p_a'+str(n)+'['+str(d)+'];')
      if restrict[n] or prolong[n]:
        code('int stride_'+str(n)+'0 = stride_'+str(n)+'[0];')
        if NDIM >= 2:
          code('int stride_'+str(n)+'1 = stride_'+str(n)+'[1];')
        if NDIM >= 3:
          code('int stride_'+str(n)+'2 = stride_'+str(n)+'[2];')

    line = '#pragma acc parallel deviceptr('
    for n in range (0,nargs):
      if arg_typ[n] == 'ops_arg_dat':
        line = line + 'p_a'+str(n)+','
      if arg_typ[n] == 'ops_arg_gbl':
        if accs[n] == OPS_READ and (not dims[n].isdigit() or int(dims[n])>1):
          line = line + 'p_a'+str(n)+','
    line = line[:-1]+')'
    for n in range (0,nargs):
      if arg_typ[n] == 'ops_arg_gbl':
        if accs[n] == OPS_MIN:
          for d in range(0,int(dims[n])):
            line = line + ' reduction(min:p_a'+str(n)+'_'+str(d)+')'
        if accs[n] == OPS_MAX:
          for d in range(0,int(dims[n])):
            line = line + ' reduction(max:p_a'+str(n)+'_'+str(d)+')'
        if accs[n] == OPS_INC:
          for d in range(0,int(dims[n])):
            line = line + ' reduction(+:p_a'+str(n)+'_'+str(d)+')'
        if accs[n] == OPS_WRITE: #this may not be correct ..
          for d in range(0,int(dims[n])):
            line = line + ' reduction(+:p_a'+str(n)+'_'+str(d)+')'
    code('#ifdef OPS_GPU')
    code(line)
    line = '#pragma acc loop'
    for n in range (0,nargs):
      if arg_typ[n] == 'ops_arg_gbl':
        if accs[n] == OPS_MIN:
          for d in range(0,int(dims[n])):
            line = line + ' reduction(min:p_a'+str(n)+'_'+str(d)+')'
        if accs[n] == OPS_MAX:
          for d in range(0,int(dims[n])):
            line = line + ' reduction(max:p_a'+str(n)+'_'+str(d)+')'
        if accs[n] == OPS_INC:
          for d in range(0,int(dims[n])):
            line = line + ' reduction(+:p_a'+str(n)+'_'+str(d)+')'
        if accs[n] == OPS_WRITE: #this may not be correct
          for d in range(0,int(dims[n])):
            line = line + ' reduction(+:p_a'+str(n)+'_'+str(d)+')'
    code(line)
    code('#endif')
    if NDIM==3:
      FOR('n_z','0','z_size')
      code('#ifdef OPS_GPU')
      code(line)
      code('#endif')
      FOR('n_y','0','y_size')
      code('#ifdef OPS_GPU')
      code(line)
      code('#endif')
    if NDIM==2:
      FOR('n_y','0','y_size')
      code('#ifdef OPS_GPU')
      code(line)
      code('#endif')

    FOR('n_x','0','x_size')
    if arg_idx:
      if NDIM==1:
        code('int arg_idx[] = {arg_idx0+n_x};')
      elif NDIM==2:
        code('int arg_idx[] = {arg_idx0+n_x, arg_idx1+n_y};')
      elif NDIM==3:
        code('int arg_idx[] = {arg_idx0+n_x, arg_idx1+n_y, arg_idx2+n_z};')

    for n in range (0,nargs):
      if arg_typ[n] == 'ops_arg_gbl':
        if accs[n] == OPS_MIN and int(dims[n])>1:
          code(typs[n]+' p_a'+str(n)+'_local['+str(dims[n])+'];')
          for d in range(0,int(dims[n])):
            code('p_a'+str(n)+'_local['+str(d)+'] = p_a'+str(n)+'['+str(d)+'];') #need +INFINITY_ change to
        if accs[n] == OPS_MAX and int(dims[n])>1:
          code(typs[n]+' p_a'+str(n)+'_local['+str(dims[n])+'];')
          for d in range(0,int(dims[n])):
            code('p_a'+str(n)+'_local['+str(d)+'] = p_a'+str(n)+'['+str(d)+'];') #need -INFINITY_ change to
        if accs[n] == OPS_INC and int(dims[n])>1:
          code(typs[n]+' p_a'+str(n)+'_local['+str(dims[n])+'];')
          for d in range(0,int(dims[n])):
            code('p_a'+str(n)+'_local['+str(d)+'] = ZERO_'+typs[n]+';')
        if accs[n] == OPS_WRITE and int(dims[n])>1: #this may not be correct
          code(typs[n]+' p_a'+str(n)+'_local['+str(dims[n])+'];')
          for d in range(0,int(dims[n])):
            code('p_a'+str(n)+'_local['+str(d)+'] = ZERO_'+typs[n]+';')
    #code('')


    text = name+'( '
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        if restrict[n] == 1:
            n_x = 'n_x*stride_'+str(n)+'0'
            n_y = 'n_y*stride_'+str(n)+'1'
            n_z = 'n_z*stride_'+str(n)+'2'
        elif prolong[n] == 1:
          n_x = '(n_x+global_idx0%stride_'+str(n)+'0)/stride_'+str(n)+'0'
          n_y = '(n_y+global_idx1%stride_'+str(n)+'1)/stride_'+str(n)+'1'
          n_z = '(n_z+global_idx2%stride_'+str(n)+'2)/stride_'+str(n)+'2'
        else:
          n_x = 'n_x'
          n_y = 'n_y'
          n_z = 'n_z'

        if NDIM == 1:
          text = text +' p_a'+str(n)+' + '+n_x+'*'+str(stride[NDIM*n])+'*'+str(dims[n])
        elif NDIM == 2:
          text = text +' p_a'+str(n)+' + '+n_x+'*'+str(stride[NDIM*n])+'*'+str(dims[n])+\
          ' + '+n_y+'*xdim'+str(n)+'_'+name+'*'+str(stride[NDIM*n+1])+'*'+str(dims[n])
        elif NDIM == 3:
          text = text +' p_a'+str(n)+' + '+n_x+'*'+str(stride[NDIM*n])+'*'+str(dims[n])+' + '+n_y+'*xdim'+str(n)+'_'+name+'*'+str(stride[NDIM*n+1])+'*'+str(dims[n])
          text = text + ' + '+n_z+'*xdim'+str(n)+'_'+name+'*ydim'+str(n)+'_'+name+'*'+str(stride[NDIM*n+2])
      elif arg_typ[n] == 'ops_arg_gbl':
        if accs[n] == OPS_READ:
          if dims[n].isdigit() and int(dims[n])==1:
            text = text +' &p_a'+str(n)+''
          else:
            text = text +' p_a'+str(n)+''
        else:
          if dims[n].isdigit() and int(dims[n]) == 1:
            text = text +' &p_a'+str(n)+'_0'
          else:
            text = text +' p_a'+str(n)+'_local'
      elif arg_typ[n] == 'ops_arg_idx':
        text = text +'arg_idx'

      if nargs <> 1 and n != nargs-1:
        text = text + ','
      else:
        text = text +' );\n'
      if n%n_per_line == 0 and n <> nargs-1:
        text = text +'\n          '
    code(text);

    for n in range (0,nargs):
      if arg_typ[n] == 'ops_arg_gbl':
        if accs[n] == OPS_MIN and int(dims[n])>1:
          for d in range(0,int(dims[n])):
            code('p_a'+str(n)+'_'+str(d)+' = MIN(p_a'+str(n)+'_'+str(d)+',p_a'+str(n)+'_local['+str(d)+']);')
        if accs[n] == OPS_MAX and int(dims[n])>1:
          for d in range(0,int(dims[n])):
            code('p_a'+str(n)+'_'+str(d)+' = MAX(p_a'+str(n)+'_'+str(d)+'p_a'+str(n)+'_local['+str(d)+']);')
        if accs[n] == OPS_INC and int(dims[n])>1:
          for d in range(0,int(dims[n])):
            code('p_a'+str(n)+'_'+str(d)+' +=p_a'+str(n)+'_local['+str(d)+'];')
        if accs[n] == OPS_WRITE and int(dims[n])>1: #this may not be correct
          for d in range(0,int(dims[n])):
            code('p_a'+str(n)+'_'+str(d)+' +=p_a'+str(n)+'_local['+str(d)+'];')


    ENDFOR()
    if NDIM==2:
      ENDFOR()
    if NDIM==3:
      ENDFOR()
      ENDFOR()

    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_gbl':
        if accs[n] <> OPS_READ:
          #if dims[n].isdigit() and int(dims[n]) == 1:
          #  code('*p_a'+str(n)+' = p_a'+str(n)+'_l;')
          #else:
          for d in range(0,int(dims[n])):
            code('p_a'+str(n)+'['+str(d)+'] = p_a'+str(n)+'_'+str(d)+';')

    config.depth = config.depth-2
    code('}')

##########################################################################
#  output individual kernel file
##########################################################################
    if not os.path.exists('./OpenACC'):
      os.makedirs('./OpenACC')
    fid = open('./OpenACC/'+name+'_openacc_kernel_c.c','w')
    date = datetime.datetime.now()
    fid.write('//\n// auto-generated by ops.py\n//\n')
    fid.write(config.file_text)
    fid.close()
    config.file_text = ''
##########################################################################
#  now host stub
##########################################################################

    code('#include "./OpenACC/'+master.split('.')[0]+'_common.h"')
    code('')
    if not (('generate_chunk' in name) or ('calc_dt_kernel_print' in name)):
      if not (NDIM==3 and 'field_summary' in name):
        code('#define OPS_GPU')
        code('')
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        code('extern int xdim'+str(n)+'_'+name+';')
        code('int xdim'+str(n)+'_'+name+'_h = -1;')
        if NDIM==3:
          code('extern int ydim'+str(n)+'_'+name+';')
          code('int ydim'+str(n)+'_'+name+'_h = -1;')
    code('')

    code('#ifdef __cplusplus')
    code('extern "C" {')
    code('#endif')
    code('void '+name+'_c_wrapper(')
    config.depth = config.depth+2
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_gbl' and accs[n] == OPS_READ and dims[n].isdigit() and int(dims[n])==1:
        code(typs[n]+' p_a'+str(n)+',')
      else:
        code(typs[n]+' *p_a'+str(n)+',')
        if restrict[n] or prolong[n]:
          code('int *stride_'+str(n)+',')
    if arg_idx:
      if NDIM == 1:
        code('int arg_idx0,')
      elif NDIM == 2:
        code('int arg_idx0, int arg_idx1,')
      elif NDIM == 3:
        code('int arg_idx0, int arg_idx1, int arg_idx2,')

    if MULTI_GRID:
      if NDIM == 1:
        code('int global_idx0,')
      elif NDIM == 2:
        code('int global_idx0, int global_idx1,')
      elif NDIM == 3:
        code('int global_idx0, int global_idx1, int global_idx2,')

    if NDIM == 1:
      code('int x_size);')
    elif NDIM == 2:
      code('int x_size, int y_size);')
    elif NDIM == 3:
      code('int x_size, int y_size, int z_size);')
    config.depth = config.depth-2
    code('')
    code('#ifdef __cplusplus')
    code('}')
    code('#endif')
    code('')
    comm(' host stub function')

    code('void ops_par_loop_'+name+'(char const *name, ops_block block, int dim, int* range,')
    text = ''
    for n in range (0, nargs):

      text = text +' ops_arg arg'+str(n)
      if nargs <> 1 and n != nargs-1:
        text = text +','
      else:
        text = text +') {'
      if n%n_per_line == 3 and n <> nargs-1:
         text = text +'\n'
    code(text);
    config.depth = 2

    code('');
    comm('Timing')
    code('double t1,t2,c1,c2;')

    text ='ops_arg args['+str(nargs)+'] = {'
    for n in range (0, nargs):
      text = text +' arg'+str(n)
      if nargs <> 1 and n != nargs-1:
        text = text +','
      else:
        text = text +'};\n'
      if n%n_per_line == 5 and n <> nargs-1:
        text = text +'\n                    '
    code(text);
    code('')
    code('#ifdef CHECKPOINTING')
    code('if (!ops_checkpointing_before(args,'+str(nargs)+',range,'+str(nk)+')) return;')
    code('#endif')
    code('')

    IF('OPS_diags > 1')
    code('ops_timing_realloc('+str(nk)+',"'+name+'");')
    code('OPS_kernels['+str(nk)+'].count++;')
    code('ops_timers_core(&c1,&t1);')
    ENDIF()

    code('')
    comm('compute localy allocated range for the sub-block')
    comm('')
    code('int start['+str(NDIM)+'];')
    code('int end['+str(NDIM)+'];')


    code('#ifdef OPS_MPI')
    code('sub_block_list sb = OPS_sub_block_list[block->index];')
    code('#endif //OPS_MPI')

    code('')
    code('int arg_idx['+str(NDIM)+'];')
    code('int arg_idx_base['+str(NDIM)+'];')


    code('#ifdef OPS_MPI')
    code('if (compute_ranges(args, '+str(nargs)+',block, range, start, end, arg_idx) < 0) return;')
    code('#else //OPS_MPI')
    FOR('n','0',str(NDIM))
    code('start[n] = range[2*n];end[n] = range[2*n+1];')
    code('arg_idx[n] = start[n];')
    ENDFOR()
    code('#endif //OPS_MPI')
    FOR('n','0',str(NDIM))
    code('arg_idx_base[n] = arg_idx[n];')
    ENDFOR()

    if MULTI_GRID:
      code('int global_idx['+str(NDIM)+'];')
      code('#ifdef OPS_MPI')
      for n in range (0,NDIM):
        code('global_idx['+str(n)+'] = arg_idx['+str(n)+'];')
      code('#else //OPS_MPI')
      for n in range (0,NDIM):
        code('global_idx['+str(n)+'] = start['+str(n)+'];')
      code('#endif //OPS_MPI')
      code('')

    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        code('int dat'+str(n)+' = args['+str(n)+'].dat->elem_size;')


    GBL_READ = False
    GBL_READ_MDIM = False
    GBL_INC = False
    GBL_MAX = False
    GBL_MIN = False
    GBL_WRITE = False

    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_gbl':
        if accs[n] == OPS_READ:
          GBL_READ = True
          if not dims[n].isdigit() or int(dims[n])>1:
            GBL_READ_MDIM = True
        if accs[n] == OPS_INC:
          GBL_INC = True
        if accs[n] == OPS_MAX:
          GBL_MAX = True
        if accs[n] == OPS_MIN:
          GBL_MIN = True
        if accs[n] == OPS_WRITE:
          GBL_WRITE = True

    code('')
    for n in range (0, nargs):
        if arg_typ[n] == 'ops_arg_gbl':
          if accs[n] <> OPS_READ or (accs[n] == OPS_READ and (not dims[n].isdigit() or int(dims[n])>1)):
            #code(''+typs[n]+' *arg'+str(n)+'h = ('+typs[n]+' *)args['+str(n)+'].data;')
            if (accs[n] == OPS_READ):
              code(''+typs[n]+' *arg'+str(n)+'h = ('+typs[n]+' *)arg'+str(n)+'.data;')
            else:
              code('#ifdef OPS_MPI')
              code(typs[n]+' *arg'+str(n)+'h = ('+typs[n]+' *)(((ops_reduction)args['+str(n)+'].data)->data + ((ops_reduction)args['+str(n)+'].data)->size * block->index);')
              code('#else //OPS_MPI')
              code(typs[n]+' *arg'+str(n)+'h = ('+typs[n]+' *)(((ops_reduction)args['+str(n)+'].data)->data);')
              code('#endif //OPS_MPI')
    if GBL_READ == True and GBL_READ_MDIM == True:
      comm('Upload large globals')
      code('#ifdef OPS_GPU')
      code('int consts_bytes = 0;')
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_gbl':
        if accs[n] == OPS_READ and (not dims[n].isdigit() or int(dims[n])>1):
          code('consts_bytes += ROUND_UP('+str(dims[n])+'*sizeof('+typs[n]+'));')
    if GBL_READ == True and GBL_READ_MDIM == True:
      code('reallocConstArrays(consts_bytes);')
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_gbl':
        if accs[n] == OPS_READ and (not dims[n].isdigit() or int(dims[n])>1):
          code('consts_bytes = 0;')
          code('args['+str(n)+'].data = OPS_consts_h + consts_bytes;')
          code('args['+str(n)+'].data_d = OPS_consts_d + consts_bytes;')
          code('for (int d=0; d<'+str(dims[n])+'; d++) (('+typs[n]+' *)args['+str(n)+'].data)[d] = arg'+str(n)+'h[d];')
          code('consts_bytes += ROUND_UP('+str(dims[n])+'*sizeof(int));')
    if GBL_READ == True and GBL_READ_MDIM == True:
      code('mvConstArraysToDevice(consts_bytes);')
      code('#endif //OPS_GPU')

    #some custom logic for multigrid
    if MULTI_GRID:
      for n in range (0, nargs):
        if restrict[n]  == 1 :
          code('int start_'+str(n)+'['+str(NDIM)+']; int end_'+str(n)+'['+str(NDIM)+']; int stride_'+str(n)+'['+str(NDIM)+'];')
          FOR('n','0',str(NDIM))
          code('stride_'+str(n)+'[n] = args['+str(n)+'].stencil->mgrid_stride[n];')
          code('start_'+str(n)+'[n]  = start[n]*stride_'+str(n)+'[n];')
          code('end_'+str(n)+'[n]    = end[n];')
          ENDFOR()
        elif prolong[n] == 1:
          comm('This arg has a prolong stencil - so create different ranges')
          code('int start_'+str(n)+'[2]; int end_'+str(n)+'['+str(NDIM)+']; int stride_'+str(n)+'['+str(NDIM)+'];int d_size_'+str(n)+'['+str(NDIM)+'];')
          code('#ifdef OPS_MPI')
          FOR('n','0',str(NDIM))
          code('sub_dat *sd'+str(n)+' = OPS_sub_dat_list[args['+str(n)+'].dat->index];')
          code('stride_'+str(n)+'[n] = args['+str(n)+'].stencil->mgrid_stride[n];')
          code('d_size_'+str(n)+'[n] = args['+str(n)+'].dat->d_m[n] + sd'+str(n)+'->decomp_size[n] - args['+str(n)+'].dat->d_p[n];')
          code('start_'+str(n)+'[n] = global_idx[n]/stride_'+str(n)+'[n] - sd'+str(n)+'->decomp_disp[n] + args['+str(n)+'].dat->d_m[n];')
          code('end_'+str(n)+'[n] = start_'+str(n)+'[n] + d_size_'+str(n)+'[n];')
          ENDFOR()
          code('#else')
          FOR('n','0',str(NDIM))
          code('stride_'+str(n)+'[n] = args['+str(n)+'].stencil->mgrid_stride[n];')
          code('d_size_'+str(n)+'[n] = args['+str(n)+'].dat->d_m[n] + args['+str(n)+'].dat->size[n] - args['+str(n)+'].dat->d_p[n];')
          code('start_'+str(n)+'[n] = global_idx[n]/stride_'+str(n)+'[n];')
          code('end_'+str(n)+'[n] = start_'+str(n)+'[n] + d_size_'+str(n)+'[n];')
          ENDFOR()
          code('#endif')

    comm('')
    comm('set up initial pointers and exchange halos if necessary')
    code('int d_m[OPS_MAX_DIM];')
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        code('#ifdef OPS_MPI')
        code('for (int d = 0; d < dim; d++) d_m[d] = args['+str(n)+'].dat->d_m[d] + OPS_sub_dat_list[args['+str(n)+'].dat->index]->d_im[d];')
        code('#else //OPS_MPI')
        code('for (int d = 0; d < dim; d++) d_m[d] = args['+str(n)+'].dat->d_m[d];')
        code('#endif //OPS_MPI')
        code('int base'+str(n)+' = dat'+str(n)+' * 1 *')
        if prolong[n] == 1:
          code('  ((start_'+str(n)+'[0]) * args[0].stencil->stride[0] - args[0].dat->base[0]- d_m[0]);')
        elif restrict[n] == 1:
          code('  ((start_'+str(n)+'[0]) * args['+str(n)+'].stencil->stride[0] - args['+str(n)+'].dat->base[0] - d_m[0]);')
        else:
          code('  (start[0] * args['+str(n)+'].stencil->stride[0] - args['+str(n)+'].dat->base[0] - d_m[0]);')

        for d in range (1, NDIM):
          line = 'base'+str(n)+' = base'+str(n)+'+ dat'+str(n)+' *\n'
          for d2 in range (0,d):
            line = line + config.depth*' '+'  args['+str(n)+'].dat->size['+str(d2)+'] *\n'
          code(line[:-1])
          if prolong[n] == 1:
            code('  ((start_'+str(n)+'['+str(d)+']) * args['+str(n)+'].stencil->stride['+str(d)+'] - args['+str(n)+'].dat->base['+str(d)+'] - d_m['+str(d)+']);')
          elif restrict[n] == 1:
            code('  ((start_'+str(n)+'['+str(d)+']) * args['+str(n)+'].stencil->stride['+str(d)+'] - args['+str(n)+'].dat->base['+str(d)+'] - d_m['+str(d)+']);')
          else:
            code('  (start['+str(d)+'] * args['+str(n)+'].stencil->stride['+str(d)+'] - args['+str(n)+'].dat->base['+str(d)+'] - d_m['+str(d)+']);')


        code('#ifdef OPS_GPU')
        code(typs[n]+' *p_a'+str(n)+' = ('+typs[n]+' *)((char *)args['+str(n)+'].data_d + base'+str(n)+');')
        code('#else')
        code(typs[n]+' *p_a'+str(n)+' = ('+typs[n]+' *)((char *)args['+str(n)+'].data + base'+str(n)+');')
        code('#endif')
        code('')
      elif arg_typ[n] == 'ops_arg_gbl':
        if accs[n] == OPS_READ:
          if dims[n].isdigit() and int(dims[n])==1:
            code(typs[n]+' *p_a'+str(n)+' = ('+typs[n]+' *)args['+str(n)+'].data;')
          else:
            code('#ifdef OPS_GPU')
            code(typs[n]+' *p_a'+str(n)+' = ('+typs[n]+' *)args['+str(n)+'].data_d;')
            code('#else')
            code(typs[n]+' *p_a'+str(n)+' = arg'+str(n)+'h;')
            code('#endif')
        else:
          code(typs[n]+' *p_a'+str(n)+' = arg'+str(n)+'h;')
      else:
        code(typs[n]+' *p_a'+str(n)+' = NULL;')
        code('')

    #iteration range size
    code('')
    code('int x_size = MAX(0,end[0]-start[0]);')
    if NDIM==2:
      code('int y_size = MAX(0,end[1]-start[1]);')
    if NDIM==3:
      code('int y_size = MAX(0,end[1]-start[1]);')
      code('int z_size = MAX(0,end[2]-start[2]);')
    code('')

    comm("initialize global variable with the dimension of dats")
    #array sizes
    for n in range (0,nargs):
      if arg_typ[n] == 'ops_arg_dat':
        code('xdim'+str(n)+' = args['+str(n)+'].dat->size[0];')#*args['+str(n)+'].dat->dim;')
        if NDIM==3:
          code('ydim'+str(n)+' = args['+str(n)+'].dat->size[1];')

    #array sizes - upload to GPU
    condition = ''
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        condition = condition + 'xdim'+str(n)+' != xdim'+str(n)+'_'+name+'_h || '
        if NDIM==3:
          condition = condition + 'ydim'+str(n)+' != ydim'+str(n)+'_'+name+'_h || '
    condition = condition[:-4]
    IF(condition)

    #array sizes - upload to GPU
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        code('xdim'+str(n)+'_'+name+' = xdim'+str(n)+';')
        code('xdim'+str(n)+'_'+name+'_h = xdim'+str(n)+';')
        if NDIM==3:
          code('ydim'+str(n)+'_'+name+' = ydim'+str(n)+';')
          code('ydim'+str(n)+'_'+name+'_h = ydim'+str(n)+';')
    ENDIF()
    code('')

    comm('Halo Exchanges')
    code('')
    code('#ifdef OPS_GPU')
    code('ops_H_D_exchanges_device(args, '+str(nargs)+');')
    code('#else')
    code('ops_H_D_exchanges_host(args, '+str(nargs)+');')
    code('#endif')
    code('ops_halo_exchanges(args,'+str(nargs)+',range);')
    code('')
    code('#ifdef OPS_GPU')
    code('ops_H_D_exchanges_device(args, '+str(nargs)+');')
    code('#else')
    code('ops_H_D_exchanges_host(args, '+str(nargs)+');')
    code('#endif')

    IF('OPS_diags > 1')
    code('ops_timers_core(&c2,&t2);')
    code('OPS_kernels['+str(nk)+'].mpi_time += t2-t1;')
    ENDIF()
    code('')


    code(name+'_c_wrapper(')
    config.depth = config.depth+2
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_gbl' and accs[n] == OPS_READ and dims[n].isdigit() and int(dims[n])==1:
        code('*p_a'+str(n)+',')
      else:
        code('p_a'+str(n)+',')
        if restrict[n] or prolong[n]:
          code('stride_'+str(n)+',')

    if arg_idx:
      if NDIM==1:
        code('arg_idx[0],')
      elif NDIM==2:
        code('arg_idx[0], arg_idx[1],')
      elif NDIM==3:
        code('arg_idx[0], arg_idx[1], arg_idx[2],')
    if MULTI_GRID:
      if NDIM==1:
        code('global_idx[0],')
      elif NDIM==2:
        code('global_idx[0], global_idx[1],')
      elif NDIM==3:
        code('global_idx[0], global_idx[1], global_idx[2],')

    if NDIM == 1:
      code('x_size);')
    if NDIM == 2:
      code('x_size, y_size);')
    if NDIM == 3:
      code('x_size, y_size, z_size);')

    config.depth = config.depth-2





    # for n in range (0, nargs):
    #   if arg_typ[n] == 'ops_arg_gbl':
    #     if accs[n] <> OPS_READ:
    #       code('*('+typs[n]+' *)args['+str(n)+'].data = *p_a'+str(n)+';')
    code('')
    IF('OPS_diags > 1')
    code('ops_timers_core(&c1,&t1);')
    code('OPS_kernels['+str(nk)+'].time += t1-t2;')
    ENDIF()

    # if reduction == 1 :
    #   for n in range (0, nargs):
    #     if arg_typ[n] == 'ops_arg_gbl' and accs[n] != OPS_READ:
    #       #code('ops_mpi_reduce(&arg'+str(n)+',('+typs[n]+' *)args['+str(n)+'].data);')
    #   code('ops_timers_core(&c1,&t1);')
    #   code('OPS_kernels['+str(nk)+'].mpi_time += t1-t2;')

    code('#ifdef OPS_GPU')
    code('ops_set_dirtybit_device(args, '+str(nargs)+');')
    code('#else')
    code('ops_set_dirtybit_host(args, '+str(nargs)+');')
    code('#endif')
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat' and (accs[n] == OPS_WRITE or accs[n] == OPS_RW or accs[n] == OPS_INC):
        code('ops_set_halo_dirtybit3(&args['+str(n)+'],range);')

    code('')
    IF('OPS_diags > 1')
    comm('Update kernel record')
    code('ops_timers_core(&c2,&t2);')
    code('OPS_kernels['+str(nk)+'].mpi_time += t2-t1;')
    for n in range (0, nargs):
      if arg_typ[n] == 'ops_arg_dat':
        code('OPS_kernels['+str(nk)+'].transfer += ops_compute_transfer(dim, range, &arg'+str(n)+');')
    ENDIF()
    config.depth = config.depth - 2
    code('}')


##########################################################################
#  output individual kernel file
##########################################################################
    if not os.path.exists('./OpenACC'):
      os.makedirs('./OpenACC')
    fid = open('./OpenACC/'+name+'_openacc_kernel.cpp','w')
    date = datetime.datetime.now()
    fid.write('//\n// auto-generated by ops.py\n//\n')
    fid.write(config.file_text)
    fid.close()

# end of main kernel call loop

##########################################################################
#  output one master kernel file
##########################################################################

  config.file_text =''
  config.depth = 0
  comm('header')
  code('#define OPS_ACC_MD_MACROS')
  if NDIM==2:
    code('#define OPS_2D')
  if NDIM==3:
    code('#define OPS_3D')
  code('#ifdef __cplusplus')
  code('#include "ops_lib_cpp.h"')
  code('#endif')
  code('#ifdef OPS_MPI')
  code('#include "ops_mpi_core.h"')
  code('#endif')
  code('#include "ops_cuda_rt_support.h"')
  if os.path.exists('./user_types.h'):
    code('#include "user_types.h"')
  code('')

  comm(' global constants')
  for nc in range (0,len(consts)):
    if consts[nc]['dim'].isdigit() and int(consts[nc]['dim'])==1:
      code('extern '+consts[nc]['type']+' '+(str(consts[nc]['name']).replace('"','')).strip()+';')
#      code('#pragma acc declare create('+(str(consts[nc]['name']).replace('"','')).strip()+')')
    else:
      if consts[nc]['dim'].isdigit() and consts[nc]['dim'] > 0:
        num = str(consts[nc]['dim'])
        code('extern '+consts[nc]['type']+' '+(str(consts[nc]['name']).replace('"','')).strip()+'['+num+'];')
#        code('#pragma acc declare create('+(str(consts[nc]['name']).replace('"','')).strip()+')')
      else:
        code('extern '+consts[nc]['type']+' *'+(str(consts[nc]['name']).replace('"','')).strip()+';')
#        code('#pragma acc declare create('+(str(consts[nc]['name']).replace('"','')).strip()+')')

  fid = open('./OpenACC/'+master.split('.')[0]+'_common.h','w')
  fid.write('//\n// auto-generated by ops.py\n//\n')
  fid.write(config.file_text)
  fid.close()
  config.file_text =''
  code('#include "./OpenACC/'+master.split('.')[0]+'_common.h"')
  code('')
  code('')
  code('void ops_decl_const_char(int dim, char const *type,')
  code('int size, char *dat, char const *name){')
  config.depth = config.depth + 2

  for nc in range(0,len(consts)):
    IF('!strcmp(name,"'+(str(consts[nc]['name']).replace('"','')).strip()+'")')
    if consts[nc]['dim'].isdigit() and int(consts[nc]['dim'])==1:
      code((str(consts[nc]['name']).replace('"','')).strip()+' = *('+consts[nc]['type']+'*)dat;')
    else:
      code((str(consts[nc]['name']).replace('"','')).strip()+' = ('+consts[nc]['type']+'*)dat;')
    ENDIF()
    code('else')

  code('{')
  config.depth = config.depth + 2
  code('printf("error: unknown const name\\n"); exit(1);')
  ENDIF()

  config.depth = config.depth - 2
  code('}')

  #code('')
  #comm('user kernel files')

  #kernel_name_list = ['generate_chunk_kernel']

  #for nk in range(0,len(kernels)):
  #  if kernels[nk]['name'] not in kernel_name_list :
  #    code('#include "'+kernels[nk]['name']+'_openacc_kernel.cpp"')
  #    kernel_name_list.append(kernels[nk]['name'])

  fid = open('./OpenACC/'+master.split('.')[0]+'_kernels.cpp','w')
  fid.write('//\n// auto-generated by ops.py//\n\n')
  fid.write(config.file_text)
  fid.close()
