#ifndef BIFFLE_OPS_H
#define BIFFLE_OPS_H
#include <stdio.h>
#define generic_op(op) void op_##op(int target1, int target2) {\
	gen_header();\
	bif_##op(target1, target2);\
	footer();\
  }

#define single_op(op) void op_##op(int target) {\
	gen_header();\
	bif_##op(target);\
	footer();\
}

#define dummy(fun) void bif_##fun(int one, int two) {\
	printf("%s %d %d\n", #fun, one, two);\
  }

static int op_idx = 0;

void gen_header();

void footer();
  
dummy(move);
generic_op(move);
dummy(add);
generic_op(add);
dummy(sub);
generic_op(sub);
dummy(mult);
generic_op(mult);
dummy(div);
generic_op(div);
dummy(set);
generic_op(set);
dummy(comp);
generic_op(comp);
dummy(jmp);
generic_op(jmp);
dummy(bif);
generic_op(bif);

void op_hlt()
{
  gen_header();
  bif_set(hlt, 0);
  footer();
}
void gen_header()
{
  bif_set(tmp1, op_idx);
  bif_comp(tmp1, pc);
  printf("[");
}
void footer()
{
  bif_add(pc, 1);
  bif_move(zero, 0);
  printf("]\n");
}
#endif
