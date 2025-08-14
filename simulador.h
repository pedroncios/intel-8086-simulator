#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

//memória
short int memory[1000];

//Registradores
#define AL 0
#define AH 1
#define BL 0
#define BH 1

typedef union tagReg {
	short int Reg16;
	char Reg8[2];
}Reg;

Reg AX;
Reg BX;

int IR; //instruction register -> guarda opcode
int IP; //instruction pointer -> aponta para a próxima instrução
int SP; //stack pointer -> aponta para o topo da pilha (guarda endereço de retorno)

//Flags
int OV; //Overflow
int CF; //carry flag
int SF; //signal flag
int ZF; //zero flag

int aBus; //barramento
int tmp1; //temporário 1 da ULA 
int tmp2; //temporário 2 da ULA

/******************************************************************
							Protótipos
*******************************************************************/

void SimulaFonte();
void Ciclo();

void ULA(char *inst, int *op1, int *op2, char *reg1, char *reg2, int tipo);
int TestaFlags_8Bits(int op1, int op2, int result);
int TestaFlags_16Bits(int op1, int op2, int result);