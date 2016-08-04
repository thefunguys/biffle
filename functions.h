#ifndef BIF_FUNCTIONS_H
#define BIF_FUNCTIONS_H
void MOVE(int, int);
void SET(int, int);
void ADD(int, int);
void INC(int);
void SUB(int, int);
void MULT(int, int);
void DIV(int, int);
void COMP(int, int);
void CNE(int, int);
void LOAD(int, int);
void STORE(int, int);
void MEM_INIT();
void cell_add(int);
void cell_sub(int);
void cell_move_r(int);
void cell_move_l(int);
void cell_while();
void cell_end();
void cell_zero();
void JUMP(int);
void BIF(int, int);
void move(int);
void PUT(int);
void NUM(int);
void MOD(int, int);
void MOV(int, int);
void ADDI(int, int);
void SUBI(int, int);
void DEC(int);
void PRINTN(int);
void PRINT(char*);
void GETC(int);
void PUSH(int);
void POP(int);
#endif

