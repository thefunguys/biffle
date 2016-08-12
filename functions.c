#include "functions.h"
#include "biffle.h"
#include "stdio.h"

#define CELL_SIZE 3
#define twobytecells 1

static int position= 0;
int stackp = 0;


void cell_add(int n)
{
  int i;
  for (i = 0; i < n; ++i)
	//printf("+<[-]+ >>>>[-] <<<[ <- >[>>>+<<<-]]>>>[<<<+>>>-]<<<<[>>+<<-]>#");
	#ifdef twobytecells
	printf("+[<+>>>+<<-]<[>+<-]+>>>[<<<->>>[-]]<<<[->>+<<]>");
    #else
    printf("+");
	#endif
}
void cell_sub(int n)
{
  int i;
  for (i = 0; i < n; ++i)
	#ifdef twobytecells
	printf("[<+>>>+<<-]<[>+<-]+>>>[<<<->>>[-]]<<<[->>-<<]>-");
    #else
	printf("-");
	#endif
}

void cell_move_r(int n)
{
  int i, j;
  for (i = 0; i < n; ++i)
	for (j = 0; j < CELL_SIZE; ++j)
	  putchar('>');
}

void cell_move_l(int n)
{
  int i, j;
  for (i = 0; i < n; ++i)
	for (j = 0; j < CELL_SIZE; ++j)
	  putchar('<');
}

void cell_while()
{
  //printf("[");
  #ifdef twobytecells
  printf("[>>+>>>+<<<<<-]>>>>>[<<<<<+>>>>>-]<<<[[-]<<<+>>>]<[>+>>>+<<<<-]>>>>[<<<<+>>>>-]<<<[[-]<<<+>>>]<<<[[-]>");
  #else
  printf("[");
  #endif
}

void cell_end()
{
  #ifdef twobytecells
  printf("[>>+>>>+<<<<<-]>>>>>[<<<<<+>>>>>-]<<<[[-]<<<+>>>]<[>+>>>+<<<<-]>>>>[<<<<+>>>>-]<<<[[-]<<<+>>>]<<<]>");
  #else
  printf("]");
  #endif
}

void cell_zero()
{
  printf("[-]>[-]<");
}

void MOVE(int ad1, int ad2) {
  move(tmp1);
  cell_zero();
  move(ad1);
  cell_zero();

  move(ad2);
  cell_while();
  move(ad1);
  cell_add(1);
  move(tmp1);
  cell_add(1);
  move(ad2);
  cell_sub(1);
cell_end();

  move(tmp1);
  cell_while();
  move(ad2);
  cell_add(1);
  move(tmp1);
  cell_sub(1);
cell_end();
  stackp--;
}

void SET(int ad, int val) {
  move(ad);
  cell_zero();
  cell_add(val);
}

void GETC(int dest)
{
  move(dest);
  printf(",");
}

void ADDI(int dest, int n)
{
  move(dest);
  cell_add(n);
}

void SUBI(int dest, int n)
{
  move(dest);
  cell_sub(n);
}

void INC(int dest)
{
  ADDI(dest, 1);
}

void DEC(int dest)
{
  SUBI(dest, 1);
}

void PUSH(int dest)
{
  MOV(29, dest);
  SET(30, 0);
  SET(32, 1);
  move(30);
  //printf("<[->>>[>>]>+<<<[<<]<]>>>[>>]+[<<]");
  cell_move_l(1);
  cell_while();
  cell_sub(1);
  cell_move_r(3);
  cell_while();
  cell_move_r(2);
  cell_end();
  cell_move_r(1);
  cell_add(1);
  cell_move_l(3);
  cell_while();
  cell_move_l(2);
  cell_end();
  cell_move_l(1);
  cell_end();
  cell_move_r(3);
  cell_while();
  cell_move_r(2);
  cell_end();
  cell_add(1);
  cell_while();
  cell_move_l(2);
  cell_end();
  SET(32, 1);
}

void POP(int dest)
{
  SET(29, 0);
  SET(32, 1);
  SET(30, 0);
  //printf(">>[>>]<[-<[<<]<+>>>[>>]<]<-<<[<<]");
  cell_move_r(2);
  cell_while();
  cell_move_r(2);
  cell_end();
  cell_move_l(1);
  cell_while();
  cell_sub(1);
  cell_move_l(1);
  cell_while();
  cell_move_l(2);
  cell_end();
  cell_move_l(1);
  cell_add(1);
  cell_move_r(3);
  cell_while();
  cell_move_r(2);
  cell_end();
  cell_move_l(1);
  cell_end();
  cell_move_l(1);
  cell_sub(1);
  cell_move_l(2);
  cell_while();
  cell_move_l(2);
  cell_end();
  
  SET(32, 1);
  MOV(dest, 29);
}

void PRINT(char* str)
{
  int i = 0;
  size_t len = strlen(str);
  while(i < len) {
	SET(tmp5, (int) str[i]);
	PUT(tmp5);
	i++;
  }
}


void PRINTN(int n)
{
  MOV(tmp5, n);
  SET(tmp7, 10);
  SET(tmp8, 0);
  move(tmp5);
  cell_while();
  INC(tmp8);
  MOV(tmp6, tmp5);
  MOD(tmp6, tmp7);
  PUSH(tmp6);
  DIV(tmp5, tmp7);
  move(tmp5);
  cell_end();
  SET(tmp7, 48);
  move(tmp8);
  cell_while();
  DEC(tmp8);
  POP(tmp6);
  ADD(tmp6, tmp7);
  PUT(tmp6);
  move(tmp8);
  cell_end();
}

void ADD(int ad1, int ad2) {
  move(tmp1);
  cell_zero();

  move(ad2);
  cell_while();
  move(ad1);
  cell_add(1);
  move(tmp1);
  cell_add(1);
  move(ad2);
  cell_sub(1);
  cell_end();

  move(tmp1);
  cell_while();
  move(ad2);
  cell_add(1);
  move(tmp1);
  cell_sub(1);
  cell_end();
  stackp-- ;
}

void SUB(int ad1, int ad2) {
  move(tmp1);
  cell_zero();

  move(ad2);
  cell_while();
  move(ad1);
  cell_sub(1);
  move(tmp1);
  cell_add(1);
  move(ad2);
  cell_sub(1);
  cell_end();

  move(tmp1);
  cell_while();
  move(ad2);
  cell_add(1);
  move(tmp1);
  cell_sub(1);
  cell_end();
  stackp-- ;
}

void MULT(int ad1, int ad2) {
  move(tmp1);
  cell_zero();
  move(tmp2);
  cell_zero();

  move(ad1);
  cell_while(); {
    move(tmp2);
    cell_add(1);
    move(ad1);
    cell_sub(1);
	cell_end();
  }

  move(tmp2);
  cell_while(); {
    move(ad2);
    cell_while(); {
      move(ad1);
      cell_add(1);
      move(tmp1);
      cell_add(1);
      move(ad2);
      cell_sub(1);
	  cell_end();
    }
    move(tmp1);
    cell_while(); {
      move(ad2);
      cell_add(1);
      move(tmp1);
      cell_sub(1);
	  cell_end();
    }
    move(tmp2);
    cell_sub(1);
	cell_end();
  }
  stackp -= 2;
}

void DIV(int ad1, int ad2) {
  move(tmp1);
  cell_zero();
  move(tmp2);
  cell_zero();
  move(tmp3);
  cell_zero();
  move(tmp4);
  cell_zero();

  move(ad1);
  cell_while(); {
    move(tmp1);
    cell_add(1);
    move(ad1);
    cell_sub(1);
	cell_end();
  }
  move(tmp1);
  cell_while(); {
    move(ad2);
    cell_while(); {
      move(tmp2);
      cell_add(1);
      move(tmp3);
      cell_add(1);
      move(ad2);
      cell_sub(1);
	  cell_end();
    }
    move(tmp3);
    cell_while(); {
      move(ad2);
      cell_add(1);
      move(tmp3);
      cell_sub(1);
	  cell_end();
    }
    move(tmp2);
    cell_while(); {
      move(tmp3);
      cell_add(1);
      move(tmp1);
	  cell_sub(1);
	  cell_while();
	  {
        move(tmp3);
        cell_zero();
        move(tmp4);
        cell_add(1);
        move(tmp1);
        cell_sub(1);
		cell_end();
      }
      move(tmp4);
      cell_while(); {
        move(tmp1);
        cell_add(1);
        move(tmp4);
        cell_sub(1);
		cell_end();
      }
      move(tmp3);
      cell_while(); {
        move(tmp2);
		cell_sub(1);
		cell_while(); {
          move(ad1);
		  cell_sub(1);
          move(tmp2);
		  cell_zero();
		  cell_end();
        }
        cell_add(1);
        move(tmp3);
        cell_sub(1);
		cell_end();
      }
      move(tmp2);
      cell_sub(1);
      cell_end();
    }
    move(ad1);
    cell_add(1);
    move(tmp1);
	cell_end();
  }

  stackp -= 4;
}

void JUMP(int ad) {
  SET(pc, ad - 1);
}

void PUT(int lov) {
  move(lov);
  printf(".");
}

void MOV(int dest, int src)
{
  SET(dest, 0);
  ADD(dest, src);
}

void MOD(int ad1, int ad2) {
  MOV(tmp5, ad1); // a
  DIV(tmp5, ad2); // a / b
  MULT(tmp5, ad2); // (a/b) * b
  SUB(ad1, tmp5);
  /*
set ein 76
set zwei 11
div ein zwei
mult ein zwei
set zwei 76
sub zwei ein
put ein
put zwei
  */
}

void NUM(int num) {
}

void MEM_INIT()
{
  int memx = 101;
  int cell_idx = 1;
  while (memx < HEAP_MAX) {
	move(memx);
	if (memx % 5 == 0)
	  SET(memx, cell_idx++);
	memx++;
  }
}
  
void LOAD(int dest, int src) {
  move(95);
  int oldpos = position;
  int oldtmp1 = tmp1;
  int oldtmp2 = tmp2;
  int idx = 5;
  int data = 8;
  MOV(104, src);
  MOV(99, src);
  SET(94, 0);
  SET(95, 0);
  SET(100, 1);
  tmp1 = 6;
  tmp2 = 7;
  move(95);
  position = idx;
  cell_move_r(5);
  cell_while();
  cell_move_r(5);
  MOV(9, 4);
  SUB(idx, 4);
  move(idx);
  cell_end();
  ADD(idx, 4);
  MOVE(4, data);
  move(idx);
  cell_while();
  cell_move_l(5);
  ADD(idx, 4);
  MOV(4, 9);
  move(5);
  cell_end();
  position = 95;
  tmp1 = oldtmp1;
  tmp2 = oldtmp2;
  MOV(dest, 94);
  /*
  SET(96, 0);
  SET(100, 1);
  SET(104, 2);
  SET(108, 3);
  MOV(97, src);
  SET(98, 1);
  move(98);
  tmp1 = 2;
  tmp2 = 6;
  position = 6;
  printf("start load");
  printf("#[>>>>");
  MOV(5, 1);
  CNE(1, 4);
  MOV(6, 1);
  move(6);
  printf("]");
  printf("copy target");
  MOV(5, 7);
  move(4);
  cell_while();
  MOV(1, 5);
  move(1);
  printf("#");
  move(4);
  printf("<<<<]");
  position = oldpos;
  tmp1 = oldtmp1;
  tmp2 = oldtmp2;
  MOV(dest, 97);
  */
}

void STORE(int dest, int src)
{
  int idx = 10;
  int data = 13;
  int oldpos = position;
  int oldtmp1 = tmp1;
  int oldtmp2 = tmp2;
  MOV(104, src);
  MOV(99, src);
  MOV(96, dest);
  MOV(101, dest);
  SET(94, 0);
  SET(95, 0);
  SET(100, 1);
  tmp1 = 11;
  tmp2 = 12;
  move(95);
  position = idx;
  cell_move_r(5);
  cell_while();
  cell_move_r(5);
  MOV(6, 1);
  move(9);
  printf("");
  MOV(14, 9);
  SUB(idx, 9);
  move(idx);
  cell_end();
  ADD(idx, 9);
  MOVE(data, 6);
  move(idx);
  cell_while();
  cell_move_l(5);
  ADD(idx, 4);
  move(idx);
  cell_end();
  position = 95;
  tmp1 = oldtmp1;
  tmp2 = oldtmp2;
}


void COMP(int ad1, int ad2) {
  move(tmp1);
  cell_zero();
  move(tmp2);
  cell_zero();

  move(ad1);
  cell_while(); {
    move(tmp2);
    cell_add(1);
    move(ad1);
	cell_sub(1);
	cell_end();
	cell_add(1);
  }

  move(ad2);
  cell_while(); {
    move(tmp2);
	cell_sub(1);
    move(tmp1);
    cell_add(1);
    move(ad2);
	cell_sub(1);
	cell_end();
  }

  move(tmp1);
  cell_while(); {
    move(ad2);
    cell_add(1);
    move(tmp1);
	cell_sub(1);
	cell_end();
  }

  move(tmp2);
  cell_while(); {
    move(ad1);
	cell_sub(1);
    move(tmp2);
	cell_zero();
	cell_end();
  }
  move(ad1);

  stackp -= 2;
}
void CNE(int ad1, int ad2) {
  move(tmp1);
  cell_zero();
  move(tmp2);
  cell_zero();

  move(ad1);
  cell_while(); {
    move(tmp2);
    cell_add(1);
    move(ad1);
	cell_sub(1);
	cell_end();
  }

  move(ad2);
  cell_while(); {
    move(tmp2);
	cell_sub(1);
    move(tmp1);
    cell_add(1);
    move(ad2);
	cell_sub(1);
	cell_end();
  }

  move(tmp1);
  cell_while(); {
    move(ad2);
    cell_add(1);
    move(tmp1);
	cell_sub(1);
	cell_end();
  }

  move(tmp2);
  cell_while(); {
    move(ad1);
    cell_add(1);
    move(tmp2);
	cell_zero();
	cell_end();
  }
  move(ad1);

  stackp -= 2;
}

void BIF(int ad, int jmp) {
  move(tmp1);
  cell_zero();
  move(tmp2);
  cell_zero();

  move(ad);
  cell_while(); {
    move(tmp1);
    cell_add(1);
    move(tmp2);
    cell_add(1);
    move(ad);
	cell_sub(1);
	cell_end();
  }

  move(tmp1);
  cell_while(); {
    move(ad);
    cell_add(1);
    move(tmp1);
	cell_sub(1);
	cell_end();
  }

  move(tmp2);
  cell_while(); {
    JUMP(jmp);
    move(tmp2);
	cell_zero();
	cell_end();
  }

  stackp -= 2;

}

void move(int ad) {
  int num = ad - position;
  if (num > 0)
	cell_move_r(num);
  else
	cell_move_l(-1*num);
  position = ad;
}
