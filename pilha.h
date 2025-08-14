#pragma once

#define MAX 65536 //64kb

#include"simulador.h"

//Pilha de Inteiros
typedef struct tagPilha{
	unsigned char valor[MAX];
//	int topo; ---> SP
}Pilha;

//Prototipos de funções envolvendo Pilha de Inteiros
void InicializaPilha(Pilha *p);
int PilhaVazia(Pilha *p);
void Empilha(unsigned char v, Pilha *p);
unsigned char Desempilha(Pilha *p);
unsigned char RetTopo(Pilha *p);