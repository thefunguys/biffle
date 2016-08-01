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

void gen_header();

void footer();
  
single_op(move);
generic_op(ADD);
generic_op(SUB);
generic_op(MULT);
generic_op(DIV);
generic_op(SET);
generic_op(COMP);
single_op(JUMP);
generic_op(BIF);
single_op(PUT);

void op_hlt()
{
  gen_header();
  SET(hlt, 0);
  footer();
}
void gen_header()
{
  SET(tmp3, op_idx);
  COMP(tmp3, pc);
  move(tmp3);
  printf("[");
}
void footer()
{
  move(pc);
  printf("+");
  move(zero);
  printf("]\n");
}
#endif
