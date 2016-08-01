#ifndef BIFFLE_H
#define BIFFLE_H

enum registers {
  zero = 0,
  hlt,
  pc,
  jcmp,
  res,
  ein,
  zwei,
  sc,
  tmp1,
  tmp2,
  tmp3,
  tmp4
};

typedef enum registers bifreg_t;
typedef enum ops operation_t;

void assemble_op(char* opstr);
void assemble_program();
#endif
