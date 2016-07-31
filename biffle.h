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
  tmp2
};
enum ops {
  add = 0,
  sub,
  mul,
  div,
  jmp,
  beq,
  bne,
  mov,
  dat,
  ret,
};

typedef enum registers register_t;
typedef enum ops operation_t;
#endif
