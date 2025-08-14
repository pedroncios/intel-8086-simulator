#include"montador.h"
#include"simulador.h"

void main()
{

	int i;
	ContLocacao = ContLinha = ContInst = ContVLD = OK = 0;

	// Inicializa a tabela de registradores (montador)
	strcpy(tabelaREG[0].nome, "al");
	strcpy(tabelaREG[1].nome, "ah");
	strcpy(tabelaREG[2].nome, "bl");
	strcpy(tabelaREG[3].nome, "bh");
	strcpy(tabelaREG[4].nome, "ax");
	strcpy(tabelaREG[5].nome, "bx");
	strcpy(tabelaREG[6].nome, "sp"); //Não vai na estrutura de registradores
	strcpy(tabelaREG[7].nome, "ip"); //Não vai na estrutura de registradores

	for(i=0; i<8; i++)
		tabelaREG[i].valor = 0;

	//Inicialização FLAGS/Barramento/tmp's da ULA -> simulador
	IR = IP = SP = OV = CF = SF = ZF = 0;
	aBus = tmp1 = tmp2 = 0;

	/**********************************/

	if(AnalisaArquivo())
		SimulaFonte();	
}