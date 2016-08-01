#include "functions.h"
#include "biffle.h"
#include "stdio.h"

int position= 0;
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
  printf("\nSET %d %d\n", ad, val);
  move(ad);
  printf("[-]");
  char addc = '+';
  if( val == 0) return;
  else if(val < 0) addc = '-';

  for(int i=0; i < val; i++) printf("%c", addc);
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

void COMP(int ad1, int ad2) {
  printf("\nCOMP %d %d\n", ad1, ad2);
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
  if (ad == 2)
	printf("\nMOVE to PC\n");
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
