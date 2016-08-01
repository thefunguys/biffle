void MOVE(int, int);
void SET(int, int);
void ADD(int, int);
void SUB(int, int);
void MULT(int, int);
void DIV(int, int);
void COMP(int, int);
void JUMP(int);
void BIF(int, int);
void move(int);



int position= 0;
int stackp = 0;

void MOVE(int ad1, int ad2) {
  int temp = stackp++;
  move(temp);
  printf("[-]");
  move(ad1);
  printf("[-]");

  move(ad2);
  printf("[");
  move(ad1);
  printf("+");
  move(temp);
  printf("+");
  move(ad2);
  printf("-]");

  move(temp);
  printf("[");
  move(ad2);
  printf("+");
  move(temp);
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

void ADD(int ad1, int ad2) {
  int temp = stackp++;
  move(temp);
  printf("[-]");

  move(ad2);
  printf("[");
  move(ad1);
  printf("+");
  move(temp);
  printf("+");
  move(ad2);
  printf("-]");

  move(temp);
  printf("[");
  move(ad2);
  printf("+");
  move(temp);
  printf("-]");
  stackp-- ;
}

void SUB(int ad1, int ad2) {
  int temp = stackp++;
  move(temp);
  printf("[-]");

  move(ad2);
  printf("[");
  move(ad1);
  printf("-");
  move(temp);
  printf("+");
  move(ad2);
  printf("-]");

  move(temp);
  printf("[");
  move(ad2);
  printf("+");
  move(temp);
  printf("-]");
  stackp-- ;
}

void MULT(int ad1, int ad2) {
  int temp1 = stackp++;
  int temp2 = stackp++;
  move(temp1);
  printf("[-]");
  move(temp2);
  printf("[-]");

  move(ad1);
  printf("["); {
    move(temp2);
    printf("+");
    move(ad1);
    printf("-]");
  }

  move(temp2);
  printf("["); {
    move(ad2);
    printf("["); {
      move(ad1);
      printf("+");
      move(temp1);
      printf("+");
      move(ad2);
      printf("-]");
    }
    move(temp1);
    printf("["); {
      move(ad2);
      printf("+");
      move(temp1);
      printf("-]");
    }
    move(temp2);
    printf("-]");
  }
  stackp -= 2;
}

void DIV(int ad1, int ad2) {
  int temp1 = stackp++;
  int temp2 = stackp++;
  int temp3 = stackp++;
  int temp4 = stackp++;
  move(temp1);
  printf("[-]");
  move(temp2);
  printf("[-]");
  move(temp3);
  printf("[-]");
  move(temp4);
  printf("[-]");

  move(ad1);
  printf("["); {
    move(temp1);
    printf("+");
    move(ad1);
    printf("-]");
  }
  move(temp1);
  printf("["); {
    move(ad2);
    printf("["); {
      move(temp2);
      printf("+");
      move(temp3);
      printf("+");
      move(ad2);
      printf("-]");
    }
    move(temp3);
    printf("["); {
      move(ad2);
      printf("+");
      move(temp3);
      printf("-]");
    }
    move(temp2);
    printf("["); {
      move(temp3);
      printf("+");
      move(temp1);
      printf("-["); {
        move(temp3);
        printf("[-]");
        move(temp4);
        printf("+");
        move(temp1);
        printf("-]");
      }
      move(temp4);
      printf("["); {
        move(temp1);
        printf("+");
        move(temp4);
        printf("-]");
      }
      move(temp3);
      printf("["); {
        move(temp2);
        printf("-["); {
          move(ad1);
          printf("-");
          move(temp2);
          printf("[-]]");
        }
        printf("+");
        move(temp3);
        printf("-]");
      }
      move(temp2);
      printf("-]");
    }
    move(ad1);
    printf("+");
    move(temp1);
    printf("]");
  }

  stackp -= 4;
}

void JUMP(int ad) {}

void COMP(int ad1, int ad2) {
  int temp1 = stackp++;
  int temp2 = stackp++;
  move(temp1);
  printf("[-]");
  move(temp2);
  printf("[-]");

  move(ad1);
  printf("["); {
    move(temp2);
    printf("+");
    move(ad1);
    printf("-]+");
  }

  move(ad2);
  printf("["); {
    move(temp2);
    printf("-");
    move(temp1);
    printf("+");
    move(ad2);
    printf("-]");
  }

  move(temp1);
  printf("["); {
    move(ad2);
    printf("+");
    move(temp1);
    printf("-]");
  }

  move(temp2);
  printf("["); {
    move(ad1);
    printf("-");
    move(temp2);
    printf("[-]]");
  }

  stackp -= 2;
}

void BIF(int ad, int jmp) {
  int temp1 = stackp++;
  int temp2 = stackp++;
  move(temp1);
  printf("[-]");
  move(temp2);
  printf("[-]");

  move(ad);
  printf("["); {
    move(temp1);
    printf("+");
    move(temp2);
    printf("+");
    move(ad);
    printf("-]");
  }

  move(temp1);
  printf("["); {
    move(ad);
    printf("+");
    move(temp1);
    printf("-]");
  }

  move(temp2);
  printf("["); {
    jump(jmp);
    move(temp2);
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
