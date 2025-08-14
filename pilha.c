#include"pilha.h"

void InicializaPilha(Pilha *p)
{
	int i;
	SP = MAX;
	for(i=0;i<MAX;i++)
		p->valor[i] = 0;
}

int PilhaVazia(Pilha *p)
{
	if(SP == MAX)
		return 1;
	else
		return 0;
}

int PilhaCheia(Pilha *p)
{
	if(SP == 0)
		return 1;
	else
		return 0;
}

void Empilha(unsigned char v, Pilha *p)
{
	if(!PilhaCheia(p))
	{
		SP--;
		p->valor[SP] = v;
	}
	else
		printf("\nStack Overflow\n");
}

unsigned char Desempilha(Pilha *p)
{
	unsigned char v;
	if(!PilhaVazia(p))
	{
		v = p->valor[SP];
		p->valor[SP] = 0;
		SP++;
		return v;
	}
	else
	{
		printf("\nStack Underflow\n");
		return 0;
	}
}

unsigned char RetTopo(Pilha *p)
{
	return p->valor[SP];
}