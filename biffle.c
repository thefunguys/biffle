#include <stdlib.h>
#include <string.h>
#include "biffle.h"
#include "ops.h"
#define match(s1, s2) strncmp(s1, s2, sizeof(s2) - 1) == 0

FILE* fp = 0;

int arg_value(char* arg)
{
  if (match(arg, "zero"))
	return 0;
  if (match(arg, "hlt"))
	return 1;
  if (match(arg, "pc"))
	return 2;
  if (match(arg, "jcmp"))
	return 3;
  if (match(arg, "res"))
	return 4;
  if (match(arg, "ein"))
	return 5;
  if (match(arg, "zwei"))
	return 6;
  if (match(arg, "sc"))
	return 7;
  if (match(arg, "tmp1"))
	return 8;
  if (match(arg, "tmp2"))
	return 9;
  return atoi(arg);
}

void assemble_op(char* opstr)
{
  char* opname = strtok(opstr, " \n");
  char* starget1 = strtok(NULL, " \n");
  char* starget2 = starget1 ? strtok(NULL, " \n") : NULL;
  int target1 = 0;
  int target2 = 0;
  if (starget1 != NULL)
	target1 = arg_value(starget1);
  if (starget2 != NULL)
	target2 = arg_value(starget2);
  if (match(opname, "add"))
	op_ADD(target1, target2);
  else if (match(opname, "sub"))
	op_SUB(target1, target2);
  else if (match(opname, "set"))
	op_SET(target1, target2);
  else if (match(opname, "mult"))
	op_MULT(target1, target2);
  else if (match(opname, "div"))
	op_DIV(target1, target2);
  else if (match(opname, "comp"))
	op_COMP(target1, target2);
  else if (match(opname, "bif"))
	op_BIF(target1, target2);
  else if (match(opname, "jump"))
	op_JUMP(target1);
  else if (match(opname, "put"))
	op_PUT(target1);
  else if (match(opname, "hlt"))
	op_hlt();
  op_idx++;
}

void assemble_program()
{
  char line[1024] = {0};
  SET(hlt, 1);
  printf("[");
  while (1) {
	fgets(line, sizeof(line), fp);
	if (strcmp(line, "\n") == 0)
	  break;
	assemble_op(line);
  }
  printf("]");
}

int main(int argc, char** argv)
{
  if (argc > 1) {
	fp = fopen(argv[1], "r");
  }
  assemble_program();
}
