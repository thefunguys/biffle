#include <stdlib.h>
#include <string.h>
#include "biffle.h"
#include "hashmap.h"
#include "ops.h"
#define match(s1, s2) strncmp(s1, s2, sizeof(s2)) == 0

typedef struct label_s {
  char label_name[256];
  int pos;
} label_t;

FILE* fp = 0;
map_t label_map;

int arg_value(char* arg)
{
  trimwhitespace(arg);
  if (arg[0] == '.') {
	int* pos = malloc(sizeof(int) + 1);
	*pos = 0;
	int error = hashmap_get(label_map, arg, (void**)(&pos));
	int ret = 0;
	if (error == MAP_OK) ret = *pos;
	return ret;
  }
  if (arg[0] == '\'')
	return (int) arg[1];
  if (arg[0] == '%')
	return 30 + atoi(arg++);
  if (match(arg, "zero"))
	return zero;
  if (match(arg, "hlt"))
	return hlt;
  if (match(arg, "pc"))
	return pc;
  if (match(arg, "jcmp"))
	return jcmp;
  if (match(arg, "res"))
	return res;
  if (match(arg, "ein"))
	return ein;
  if (match(arg, "zwei"))
	return zwei;
  if (match(arg, "sc"))
	return sc;
  if (match(arg, "sp"))
	return sp;
  if (match(arg, "tmp1"))
	return tmp1;
  if (match(arg, "tmp2"))
	return tmp2;
  if (match(arg, "tmp3"))
	return tmp3;
  if (match(arg, "tmp4"))
	return tmp4;
  if (match(arg, "tmp5"))
	return tmp5;
  if (match(arg, "tmp6"))
	return tmp6;
  if (match(arg, "tmp7"))
	return tmp7;
  if (match(arg, "tmp8"))
	return tmp8;
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
  else if (match(opname, "addi"))
	op_ADDI(target1, target2);
  else if (match(opname, "subi"))
	op_SUBI(target1, target2);
  else if (match(opname, "set"))
	op_SET(target1, target2);
  else if (match(opname, "mult"))
	op_MULT(target1, target2);
  else if (match(opname, "div"))
	op_DIV(target1, target2);
  else if (match(opname, "mod"))
	op_MOD(target1, target2);
  else if (match(opname, "getc"))
	op_GETC(target1);
  else if (match(opname, "mov"))
	op_MOV(target1, target2);
  else if (match(opname, "comp"))
	op_COMP(target1, target2);
  else if (match(opname, "bif"))
	op_BIF(target1, target2);
  else if (match(opname, "jump"))
	op_JUMP(target1);
  else if (match(opname, "put"))
	op_PUT(target1);
  else if (match(opname, "inc"))
	op_INC(target1);
  else if (match(opname, "dec"))
	op_DEC(target1);
  else if (match(opname, "hlt"))
	op_hlt();
  else if (match(opname, "ret"))
	op_RET();
  else if (match(opname, "noop"))
	op_NOOP();
  else if (match(opname, "call"))
	op_CALL(target1);
  else if (match(opname, "push"))
	op_PUSH(target1);
  else if (match(opname, "pop"))
	op_POP(target1);
  op_idx++;
}

void assemble_program()
{
  size_t len = 0;
  char * line = NULL;
  ssize_t read;
  int idx = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
	if (read == 1) continue;
	trimwhitespace(line);
	if (line[0] == ';') continue;
	if (line[0] == '.') {
	  char* lcpy = malloc(len);
	  int* midx = malloc(sizeof(int));
	  *midx = idx;
	  strncpy(lcpy, line, len);
	  hashmap_put(label_map, lcpy, midx);
	} else {
	  idx ++;
	}
  }
  rewind(fp);
  SET(hlt, 1);
  printf("[");
  while ((read = getline(&line, &len, fp)) != -1) {
	if (read == 1) continue;
	trimwhitespace(line);
	if (line[0] == ';') continue;
	if (line[0] == '.') continue;
	assemble_op(line);
  }
  move(hlt);
  printf("]");
}

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

int main(int argc, char** argv)
{
  if (argc > 1) {
	fp = fopen(argv[1], "r");
  } else {
	fp = stdin;
  }
  label_map = hashmap_new();
  assemble_program();
}
