#ifndef BIFFLE_H
#define BIFFLE_H
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define HEAP_MAX 256

static int zero = 0;
static int hlt = 1;
static int pc = 2;
static int jcmp = 3;
static int res = 4;
static int ein = 5;
static int zwei = 6;
static int sc = 7;
static int sp = 8;
static int tmp1 = 9;
static int tmp2 = 10;
static int tmp3 = 11;
static int tmp4 = 12;
static int tmp5 = 13;
static int tmp6 = 14;
static int tmp7 = 15;
static int tmp8 = 16;

typedef enum registers bifreg_t;
typedef enum ops operation_t;

void assemble_op(char* opstr);
void assemble_program();

char *trimwhitespace(char *str);
char* get_dir_name(char* file);
char* get_file_name(char* file);
#endif
