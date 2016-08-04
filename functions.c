#include "functions.h"
#include "biffle.h"
#include "stdio.h"

static int position= 0;
int stackp = 0;

void MOVE(int ad1, int ad2) {
  move(tmp1);
  printf("[-]");
  move(ad1);
  printf("[-]");

  move(ad2);
  printf("[");
  move(ad1);
  printf("+");
  move(tmp1);
  printf("+");
  move(ad2);
  printf("-]");

  move(tmp1);
  printf("[");
  move(ad2);
  printf("+");
  move(tmp1);
  printf("-]");
  stackp--;
}

void SET(int ad, int val) {
  move(ad);
  printf("[-]");
  char addc = '+';
  if( val == 0) return;
  else if(val < 0) addc = '-';

  for(int i=0; i < val; i++) printf("%c", addc);
}

void GETC(int dest)
{
  move(dest);
  printf(",");
}

void ADDI(int dest, int n)
{
  move(dest);
  int i;
  for (i = 0; i < n; i++)
	printf("+");
}

void SUBI(int dest, int n)
{
  move(dest);
  int i;
  for (i = 0; i < n; i++)
	printf("-");
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
  printf("<[->>>[>>]>+<<<[<<]<]>>>[>>]+[<<]");
  SET(32, 1);
}

void POP(int dest)
{
  SET(29, 0);
  SET(32, 1);
  SET(30, 0);
  printf(">>[>>]<[-<[<<]<+>>>[>>]<]<-<<[<<]");
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
  /**
set ein 123
;ones
set 15 0
;tens
set 16 0
;hundreds
set 17 0
set 20 10
.loop
mov tmp7 15
comp tmp7 20
bif tmp7 .inc10s
jump .end
.inc10s
inc 16
set 15 0
mov tmp7 16
comp tmp7 20
bif tmp7 .inc100s
jump .end
.inc100s
inc 17
set 16 0
.end
dec ein
inc 15
bif ein .loop
mov jcmp 17
call .pdigit
noop
mov jcmp 16
call .pdigit
noop
mov jcmp 15
call .pdigit
noop
hlt

.pdigit
set res 48
add res jcmp
put res
ret
  */
}

void ADD(int ad1, int ad2) {
  move(tmp1);
  printf("[-]");

  move(ad2);
  printf("[");
  move(ad1);
  printf("+");
  move(tmp1);
  printf("+");
  move(ad2);
  printf("-]");

  move(tmp1);
  printf("[");
  move(ad2);
  printf("+");
  move(tmp1);
  printf("-]");
  stackp-- ;
}

void SUB(int ad1, int ad2) {
  move(tmp1);
  printf("[-]");

  move(ad2);
  printf("[");
  move(ad1);
  printf("-");
  move(tmp1);
  printf("+");
  move(ad2);
  printf("-]");

  move(tmp1);
  printf("[");
  move(ad2);
  printf("+");
  move(tmp1);
  printf("-]");
  stackp-- ;
}

void MULT(int ad1, int ad2) {
  move(tmp1);
  printf("[-]");
  move(tmp2);
  printf("[-]");

  move(ad1);
  printf("["); {
    move(tmp2);
    printf("+");
    move(ad1);
    printf("-]");
  }

  move(tmp2);
  printf("["); {
    move(ad2);
    printf("["); {
      move(ad1);
      printf("+");
      move(tmp1);
      printf("+");
      move(ad2);
      printf("-]");
    }
    move(tmp1);
    printf("["); {
      move(ad2);
      printf("+");
      move(tmp1);
      printf("-]");
    }
    move(tmp2);
    printf("-]");
  }
  stackp -= 2;
}

void DIV(int ad1, int ad2) {
  move(tmp1);
  printf("[-]");
  move(tmp2);
  printf("[-]");
  move(tmp3);
  printf("[-]");
  move(tmp4);
  printf("[-]");

  move(ad1);
  printf("["); {
    move(tmp1);
    printf("+");
    move(ad1);
    printf("-]");
  }
  move(tmp1);
  printf("["); {
    move(ad2);
    printf("["); {
      move(tmp2);
      printf("+");
      move(tmp3);
      printf("+");
      move(ad2);
      printf("-]");
    }
    move(tmp3);
    printf("["); {
      move(ad2);
      printf("+");
      move(tmp3);
      printf("-]");
    }
    move(tmp2);
    printf("["); {
      move(tmp3);
      printf("+");
      move(tmp1);
      printf("-["); {
        move(tmp3);
        printf("[-]");
        move(tmp4);
        printf("+");
        move(tmp1);
        printf("-]");
      }
      move(tmp4);
      printf("["); {
        move(tmp1);
        printf("+");
        move(tmp4);
        printf("-]");
      }
      move(tmp3);
      printf("["); {
        move(tmp2);
        printf("-["); {
          move(ad1);
          printf("-");
          move(tmp2);
          printf("[-]]");
        }
        printf("+");
        move(tmp3);
        printf("-]");
      }
      move(tmp2);
      printf("-]");
    }
    move(ad1);
    printf("+");
    move(tmp1);
    printf("]");
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
  MOV(res, ad1); // a
  DIV(res, tmp2); // a / b
  MULT(res, tmp2); // (a/b) * b
  SUB(ad1, res);
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
  printf(">>>>>[>>>>>");
  move(4);
  printf("");
  MOV(9, 4);
  SUB(idx, 4);
  move(idx);
  printf("]");
  ADD(idx, 4);
  MOVE(4, data);
  move(idx);
  printf("[<<<<<");
  ADD(idx, 4);
  move(4);
  printf("");
  MOV(4, 9);
  move(5);
  printf("]");
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
  printf("[");
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
  printf(">>>>>[#>>>>>");
  MOV(6, 1);
  move(9);
  printf("#");
  MOV(14, 9);
  SUB(idx, 9);
  move(idx);
  printf("]#");
  ADD(idx, 9);
  MOVE(data, 6);
  move(idx);
  printf("[<<<<<#");
  ADD(idx, 4);
  move(idx);
  printf("#]");
  position = 95;
  tmp1 = oldtmp1;
  tmp2 = oldtmp2;
}


void COMP(int ad1, int ad2) {
  move(tmp1);
  printf("[-]");
  move(tmp2);
  printf("[-]");

  move(ad1);
  printf("["); {
    move(tmp2);
    printf("+");
    move(ad1);
    printf("-]+");
  }

  move(ad2);
  printf("["); {
    move(tmp2);
    printf("-");
    move(tmp1);
    printf("+");
    move(ad2);
    printf("-]");
  }

  move(tmp1);
  printf("["); {
    move(ad2);
    printf("+");
    move(tmp1);
    printf("-]");
  }

  move(tmp2);
  printf("["); {
    move(ad1);
    printf("-");
    move(tmp2);
    printf("[-]]");
  }
  move(ad1);

  stackp -= 2;
}
void CNE(int ad1, int ad2) {
  move(tmp1);
  printf("[-]");
  move(tmp2);
  printf("[-]");

  move(ad1);
  printf("["); {
    move(tmp2);
    printf("+");
    move(ad1);
    printf("-]");
  }

  move(ad2);
  printf("["); {
    move(tmp2);
    printf("-");
    move(tmp1);
    printf("+");
    move(ad2);
    printf("-]");
  }

  move(tmp1);
  printf("["); {
    move(ad2);
    printf("+");
    move(tmp1);
    printf("-]");
  }

  move(tmp2);
  printf("["); {
    move(ad1);
    printf("+");
    move(tmp2);
    printf("[-]]");
  }
  move(ad1);

  stackp -= 2;
}

void BIF(int ad, int jmp) {
  move(tmp1);
  printf("[-]");
  move(tmp2);
  printf("[-]");

  move(ad);
  printf("["); {
    move(tmp1);
    printf("+");
    move(tmp2);
    printf("+");
    move(ad);
    printf("-]");
  }

  move(tmp1);
  printf("["); {
    move(ad);
    printf("+");
    move(tmp1);
    printf("-]");
  }

  move(tmp2);
  printf("["); {
    JUMP(jmp);
    move(tmp2);
    printf("[-]]");
  }

  stackp -= 2;

}

void move(int ad) {
  int num = ad - position;
  char movc = '>';
  if(num == 0) return;
  else if( num < 0) {
   movc = '<';
   num *= -1;
  }

  for(int i=0; i < num; i++) printf("%c", movc);
  position = ad;
}
