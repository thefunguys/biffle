#include <stdlib.h>
#include <string.h>
#include "biffle.h"
#include "ops.h"
#define match(s1, s2) strcmp(s1, s2) == 0

void assemble_op(char* opstr)
{
  char* opname = strtok(opstr, " ");
  char* starget1 = strtok(NULL, " ");
  char* starget2 = starget1 ? strtok(NULL, " ") : NULL;
  int target1 = 0;
  int target2 = 0;
  if (starget1 != NULL)
	target1 = atoi(starget1);
  if (starget2 != NULL)
	target2 = atoi(starget2);
  if (match(opname, "add"))
	op_add(target1, target2);
  else if (match(opname, "sub"))
	op_sub(target1, target2);
  else if (match(opname, "set"))
	op_set(target1, target2);
  else if (match(opname, "mult"))
	op_mult(target1, target2);
  else if (match(opname, "div"))
	op_div(target1, target2);
  else if (match(opname, "comp"))
	op_comp(target1, target2);
  else if (match(opname, "bif"))
	op_bif(target1, target2);
  else if (match(opname, "jump"))
	op_jmp(target1, target2);
  else if (match(opname, "hlt"))
	op_hlt();
  op_idx++;
}

void assemble_program()
{
  char line[1024] = {0};
  bif_set(hlt, 1);
  printf("[");
  while (1) {
	fgets(line, sizeof(line), stdin);
	if (strcmp(line, "\n") == 0)
	  break;
	assemble_op(line);
  }
  printf("]");
}

int main(void)
{
  assemble_program();
}
