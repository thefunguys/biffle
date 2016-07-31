#ifndef BIFFLE_OPS_H
#define BIFFLE_OPS_H
#include <stdio.h>
#include "biffle.h"
static int op_idx;

void gen_header()
{
  set(tmp1, op_idx);
  compare(tmp1, pc);
  printf("[");
}

void footer()
{
  add(pc, 1);
  move(zero);
  printf("]");
}
  

void op_add(int target1, int target2)
{
  add(target1, target2);
}
  
  
#endif
