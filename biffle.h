#ifndef BIFFLE_H
#define BIFFLE_H
#include <string.h>
#include <ctype.h>

enum registers {
  zero = 0,
  hlt,
  pc,
  jcmp,
  res,
  ein,
  zwei,
  sc,
  sp,
  tmp1,
  tmp2,
  tmp3,
  tmp4,
  tmp5,
  tmp6,
  tmp7,
  tmp8
};

typedef enum registers bifreg_t;
typedef enum ops operation_t;

void assemble_op(char* opstr);
void assemble_program();

char *trimwhitespace(char *str);
#endif
