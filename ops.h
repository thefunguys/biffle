#ifndef BIFFLE_OPS_H
#define BIFFLE_OPS_H
#include <stdio.h>
#include "functions.h"
#define generic_op(op) void op_##op(int target1, int target2) {\
	printf("\n%s %d %d\n", #op, target1, target2);\
	gen_header();\
	op(target1, target2);\
	footer();\
  }

#define single_op(op) void op_##op(int target) {\
	printf("\n%s %d\n", #op, target);\
	gen_header();\
	op(target);\
	footer();\
}

#define dummy(fun) void bif_##fun(int one, int two) {\
	printf("%s %d %d\n", #fun, one, two);\
  }

static int op_idx = 0;
int ret_pos = 0;

void gen_header();

void footer();
  
single_op(move);
generic_op(ADD);
generic_op(SUB);
generic_op(MULT);
generic_op(DIV);
generic_op(SET);
generic_op(COMP);
generic_op(BIF);
generic_op(MOD);
generic_op(MOV);
single_op(PUT);
single_op(INC);
single_op(DEC);

void op_JUMP(int target)
{
  gen_header();
  JUMP(target);
  footer();
}

void op_hlt()
{
  gen_header();
  SET(hlt, 0);
  SET(pc, 0);
  footer();
}


void op_NOOP()
{
  gen_header();
  footer();
}

void op_CALL(int target)
{
  gen_header();
  JUMP(target);
  SET(sc, op_idx + 1);
  footer();
}

void op_RET()
{
  gen_header();
  SET(pc, 0);
  ADD(pc, sc);
  footer();
}
void gen_header()
{
  SET(tmp3, op_idx);
  SET(tmp4, 0);
  ADD(tmp4, pc);
  COMP(tmp3, tmp4);
  move(pc);
  printf("#");
  move(tmp3);
  printf("#[");
}
void footer()
{
  move(pc);
  printf("+");
  move(tmp3);
  SET(tmp3, 0);
  printf("]\n");
}
#endif
