#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>


/******************************************************************
							Estruturas
*******************************************************************/

typedef struct tagVLD // Variaveis, labels ,diretivas e registradores
{
	char nome[50];
	int valor;
	char tipo;
}VLD;

typedef struct tagInstrucao
{
	char mnemonico[10];
	int opcode;
}Instrucao;

typedef struct tagVarTmp
{
	char nome[30];
	char tipo;
}VarTmp;

/******************************************************************
							Variaveis Globais
*******************************************************************/

int OK;
int ContLocacao;
int ContLinha;  // numero de linhas
int ContInst;
int ContVLD;

Instrucao tabelaInst[100]; // -> SIMULADOR
VLD tabelaVLD[100];
VLD tabelaREG[8];

VarTmp var[30]; // vetor de variaveis(para a funcao analisa erro)

/******************************************************************
							Protótipos
*******************************************************************/

void printIntro();

int AnalisaArquivo();
void AnalisaErros(FILE *f);
void AnalisaInstrucao(FILE *f);
void AnalisaVLD(FILE *f);

int IsDiretiva(char *p);
int IsRegistrador8(char *p);
int IsRegistrador16(char *p);
int IsMnemonico(char *p);
int IsImediato(char *p);
int IsVariavel(int cont, char *p);
int IsBinario(char *p);


void Enderecamento(char *p);
char *TrataVirgula(char *p);
int VirgulaMid(char *p);
int TemVirgula(char *p);

int str2int(char *word);
int bin2int(char *b); //somente para 1 byte

void PreencheTabelaOpcodes();
int getOpcode(char *m);

int recuperaVLD(char *op);
int recuperaReg(char *reg);