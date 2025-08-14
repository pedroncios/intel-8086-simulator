#include"simulador.h"
#include"montador.h"
#include"pilha.h"

Pilha p;

char naoULA[14][5] = {"jmp","je","jne","jg","jge","jl","jle","ja","jae","jb","jbe","call","ret","hlt"};

char twoOperands[35][6] = {
	"MOVRM","MOVMR","MOVRR","MOVMI","MOVRI",
	"ADDRM","ADDMR","ADDRR","ADDMI","ADDRI",
	"SUBRM","SUBMR","SUBRR","SUBMI","SUBRI",
	"ANDRM","ANDMR","ANDRR","ANDMI","ANDRI",
	"ORRM","ORMR","ORRR","ORMI","ORRI",
	"XORRM","XORMR","XORRR","XORMI","XORRI",
	"CMPRM","CMPMR","CMPRR","CMPMI","CMPRI"
};

int goToULA(char *inst)
{
	int i;
	for(i=0;i<14;i++)
	{
		if(!strcmpi(inst,naoULA[i]))
			return 0;
	}
	return 1;
}

int IsTwoOperands(char *inst)
{
	int i;
	for(i=0;i<35;i++)
	{
		if(!strcmpi(inst,twoOperands[i]))
			return 1;
	}
	return 0;
}

char * recuperaVLD_indice(int opcode1, char tipo)
{
	int i;
	for(i=0;i<100;i++)
	{
		if(tabelaVLD[i].valor == opcode1 && tabelaVLD[i].tipo == tipo)
			return tabelaVLD[i].nome;
	}
	return NULL;
}

void getNextInstruction()
{
	char inst[10], instAux[10];
	int opcode1, opcode2, aux, it;
	it = memory[IP];
	strcpy(inst,tabelaInst[it-1].mnemonico);

	if(!goToULA(inst))
	{
		opcode1 = memory[IP+1];

		if(!strcmpi("HLT",inst))
			printf("HLT");
		else if(!strcmpi("CALL",inst))
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'d'));
		else if(!strcmpi("RET",inst))
			printf("RET");
		else if(!strcmpi("JMP",inst) ||
				!strcmpi("JE",inst) ||
				!strcmpi("JNE",inst) ||
				!strcmpi("JG",inst) ||
				!strcmpi("JGE",inst) ||
				!strcmpi("JL",inst) ||
				!strcmpi("JLE",inst) ||
				!strcmpi("JA",inst) ||
				!strcmpi("JAE",inst) ||
				!strcmpi("JB",inst) ||
				!strcmpi("JBE",inst))
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'l'));
	}
	else
	{
		strcpy(instAux,inst);
		aux = strlen(instAux);
		
		if(IsTwoOperands(inst))
		{
			instAux[aux-2] = 0;
			printf("%s ",instAux);

			aux = strlen(inst);	
			opcode1 = memory[IP+1];
			opcode2 = memory[IP+2];

			if(inst[aux-2] == 'R')
			{
				if(strcmpi(tabelaREG[opcode1].nome,"ax")==0)
					printf("AX,");
				else if(strcmpi(tabelaREG[opcode1].nome,"bx")==0)
					printf("BX,");
				else if(strcmpi(tabelaREG[opcode1].nome,"ah")==0)
					printf("AH,");
				else if(strcmpi(tabelaREG[opcode1].nome,"al")==0)
					printf("AL,");
				else if(strcmpi(tabelaREG[opcode1].nome,"bh")==0)
					printf("BH,");
				else if(strcmpi(tabelaREG[opcode1].nome,"bl")==0)
					printf("BL,");
			}
			else //memória (variavel)
			{
				for(it=0;it<100;it++)
				{
					if(tabelaVLD[it].tipo == 'b' || tabelaVLD[it].tipo == 'w')
					{
						if(tabelaVLD[it].valor == opcode1)
						{
							printf("%s,",tabelaVLD[it].nome);
							break;
						}
					}
				}
			}					
			if(inst[aux-1] == 'R')
			{
				if(strcmpi(tabelaREG[opcode2].nome,"ax")==0)
					printf("AX");
				else if(strcmpi(tabelaREG[opcode2].nome,"bx")==0)
					printf("BX");
				else if(strcmpi(tabelaREG[opcode2].nome,"ah")==0)
					printf("AH");
				else if(strcmpi(tabelaREG[opcode2].nome,"al")==0)
					printf("AL");
				else if(strcmpi(tabelaREG[opcode2].nome,"bh")==0)
					printf("BH");
				else if(strcmpi(tabelaREG[opcode2].nome,"bl")==0)
					printf("BL");
			}
			else if(inst[aux-1] == 'M')
			{
				for(it=0;it<100;it++)
				{
					if(tabelaVLD[it].tipo == 'b' || tabelaVLD[it].tipo == 'w')
					{
						if(tabelaVLD[it].valor == opcode2)
						{
							printf("%s",tabelaVLD[it].nome);
							break;
						}
					}
				}
			}
			else
				printf("%d",opcode2);
		}
		else // Senão é somente 1 operando
		{
			instAux[aux-1] = 0;
			printf("%s ",instAux);

			opcode1 = memory[IP+1];
			aux = strlen(inst);
			
			if(inst[aux-1] == 'R')
			{
				if(strcmpi(tabelaREG[opcode1].nome,"ax")==0)
					printf("AX");
				else if(strcmpi(tabelaREG[opcode1].nome,"bx")==0)
					printf("BX");
				else if(strcmpi(tabelaREG[opcode1].nome,"ah")==0)
					printf("AH");
				else if(strcmpi(tabelaREG[opcode1].nome,"al")==0)
					printf("AL");
				else if(strcmpi(tabelaREG[opcode1].nome,"bh")==0)
					printf("BH");
				else if(strcmpi(tabelaREG[opcode1].nome,"bl")==0)
					printf("BL");
			}
			else
			{
				for(it=0;it<100;it++)
				{
					if(tabelaVLD[it].tipo == 'b' || tabelaVLD[it].tipo == 'w')
					{
						if(tabelaVLD[it].valor == opcode1)
						{
							printf("%s",tabelaVLD[it].nome);
							break;
						}
					}
				}
			}
		}
	}
}

void SimulaFonte()
{
	FILE *f = fopen("prog.code","r");
	int i,j,aux = -1,isVar;
	char inst[10];
	int it;

	int op, end_of_instructions = 0;

	if(f == NULL)
	{
		printf("\nErro na abertura do arquivo.\n");
		return;
	}

	for(i=0;i<1000;i++)
		memory[i] = -1;

	InicializaPilha(&p);

	AX.Reg16 = 0;
	BX.Reg16 = 0;

	i = 0;
	//Passa tudo que tem no fonte para o vetorzão memory
	while(!feof(f))
	{
		isVar = 0;
		//Testa se é uma variável
		for(j=0;j<100;j++)
		{
			if(tabelaVLD[j].tipo == 'b')
			{
				if(tabelaVLD[j].valor == i)
				{
					fscanf(f,"%x",&aux);
					memory[i] = aux;
					i++;
					isVar = 1;
					break;
				}
			}
			else if(tabelaVLD[j].tipo == 'w')
			{
				if(tabelaVLD[j].valor == i)
				{
					fscanf(f,"%x",&aux);
					memory[i] = aux;
					i++;
					i++;
					isVar = 1;
					break;
				}
			}
		}

		if(isVar)
			continue;

		fscanf(f,"%x",&aux);
		memory[i] = aux;
		i++;
		if(aux <= 35) //2 operandos
		{
			fscanf(f,"%x",&aux);
			memory[i] = aux;
			i++;
			fscanf(f,"%x",&aux);
			memory[i] = aux;
			i++;
		}
		else if(aux >= 36 && aux <= 57) //1 operando
		{
			fscanf(f,"%x",&aux);
			memory[i] = aux;
			i = i+2;
		}
		else
		{
			if(aux == getOpcode("hlt")+1)
				break;
			else
				i = i+2;
		}
	}

	fclose(f);

	//Interface com o USER das opções
	printf("\n\nOpcoes de execucao:");
	printf("\n1. Execucao Direta.");
	printf("\n2. Execucao Passo-a-Passo.");

backToTop:
	printf("\n\nOpcao: ");
	scanf("%d",&op);

	if(op == 1)
	{	
		//Execução direta
		printf("\n\nExecutando instrucoes: \n\n");
		while(strcmpi("hlt",inst))
		{
			printf("Instrucao em Execucao: ");
			Ciclo(inst);
			printf("\nProxima instrucao: ");
			getNextInstruction();
			printf("\n\nRegistradores:\tAX: %x\tAH: %x\tAL: %x",AX.Reg16,AX.Reg8[AH],AX.Reg8[AL]);
			printf("\n\t\tBX: %x\tBH: %x\tBL: %x",BX.Reg16,BX.Reg8[BH],AX.Reg8[BL]);
			printf("\n\nVariaveis:\t");
			for(it=0;it<100;it++)
			{
				if(tabelaVLD[it].tipo == 'b' || tabelaVLD[it].tipo == 'w')
					printf("%s: %x\t",tabelaVLD[it].nome,memory[tabelaVLD[it].valor]);
			}
			printf("\n\nFlags:\tOF: %d\tCF: %d\tSF: %d\tZF: %d\t",OV,CF,SF,ZF);
			printf("\n\nIP: %x\tIR: %x\tSP: %x\n\n\n",IP,IR,SP);
			
			Sleep(3000);
		}
		printf("\n\n-----\t\tFim da execucao\t\t-----");
		getch();
	}
	else if(op == 2)
	{
		while(!end_of_instructions)
		{
			printf("Instrucao em Execucao: ");
			Ciclo(inst);
			printf("\nProxima instrucao: ");
			getNextInstruction();
			printf("\n\nRegistradores:\tAX: %x\tAH: %x\tAL: %x",AX.Reg16,AX.Reg8[AH],AX.Reg8[AL]);
			printf("\n\t\tBX: %x\tBH: %x\tBL: %x",BX.Reg16,BX.Reg8[BH],AX.Reg8[BL]);
			printf("\n\nVariaveis:\t");
			for(it=0;it<100;it++)
			{
				if(tabelaVLD[it].tipo == 'b' || tabelaVLD[it].tipo == 'w')
					printf("%s: %x\t",tabelaVLD[it].nome,memory[tabelaVLD[it].valor]);
			}
			printf("\n\nFlags:\tOF: %d\tCF: %d\tSF: %d\tZF: %d\t",OV,CF,SF,ZF);
			printf("\n\nIP: %x\tIR: %x\tSP: %x\n\n",IP,IR,SP);
			system("pause");
			printf("\n\n");
			if(strcmpi(inst,"hlt")==0)
				end_of_instructions = 1;
		}
	}
	else
	{
		printf("\nOpcao invalida");
		goto backToTop;
	}
}

void BuscaInstrucao()
{
	IR = memory[IP];
	IP = IP + 3;
}

void DecodificaInstrucao(char *inst)
{
	strcpy(inst,tabelaInst[IR-1].mnemonico);
}

void BuscaOperandos(int *opcode1, int *opcode2, int quantOP)
{
	if(quantOP == 2)
	{
		*opcode1 = memory[IP-2];
		*opcode2 = memory[IP-1];
	}
	else if(quantOP == 1)
		*opcode1 = memory[IP-2];
	else
		printf("\nErro na Busca de operandos\n");
}

void Ciclo(char *inst)
{
	int opcode1, opcode2;
	int *op1, *op2;
	int aux;

	int tipo;
	char *reg1, *reg2;

	int it;

	char instAux[10];

	BuscaInstrucao();
	DecodificaInstrucao(inst);
	if(!goToULA(inst))
	{
		//execução HLT
		if(!strcmpi("HLT",inst))
		{
			printf("HLT");
			return;
		}
		
		//execução CALL
		else if(!strcmpi("CALL",inst))
		{
			Empilha((unsigned char)IP,&p);
			BuscaOperandos(&opcode1,&opcode2,1);
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'d'));
			IP = opcode1;
		}

		//execução RET
		else if(!strcmpi("RET",inst))
		{
			printf("RET");
			IP = (int)Desempilha(&p);
		}

		//execução dos JMP's
		//
		//JMP
		else if(!strcmpi("JMP",inst))
		{
			BuscaOperandos(&opcode1,&opcode2,1);
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'l'));
			IP = opcode1;
		}
		//JE (=) [signed and unsigned]
		else if(!strcmpi("JE",inst))
		{
			BuscaOperandos(&opcode1,&opcode2,1);
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'l'));
			if(ZF == 1)
				IP = opcode1;
		}
		//JNE (!=) [signed and unsigned]
		else if(!strcmpi("JNE",inst))
		{
			BuscaOperandos(&opcode1,&opcode2,1);
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'l'));
			if(ZF == 0)
				IP = opcode1;
		}
		//JG (>) [signed]
		else if(!strcmpi("JG",inst))
		{
			BuscaOperandos(&opcode1,&opcode2,1);
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'l'));
			if(ZF == 0 && SF == OV)
				IP = opcode1;
		}
		//JGE (>=) [signed]
		else if(!strcmpi("JGE",inst))
		{
			BuscaOperandos(&opcode1,&opcode2,1);
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'l'));
			if(SF == OV)
				IP = opcode1;
		}
		//JL (<) [signed]
		else if(!strcmpi("JL",inst))
		{
			BuscaOperandos(&opcode1,&opcode2,1);
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'l'));
			if(SF != OV)
				IP = opcode1;
		}
		//JLE (<=) [signed]
		else if(!strcmpi("JLE",inst))
		{
			BuscaOperandos(&opcode1,&opcode2,1);
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'l'));
			if(ZF == 1 || SF != OV)
				IP = opcode1;
		}
		//JA (>) [unsigned]
		else if(!strcmpi("JA",inst))
		{
			BuscaOperandos(&opcode1,&opcode2,1);
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'l'));
			if(CF == 1 && ZF == 0)
				IP = opcode1;
		}
		//JAE (>=) [unsigned]
		else if(!strcmpi("JAE",inst))
		{
			BuscaOperandos(&opcode1,&opcode2,1);
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'l'));
			if(CF == 0)
				IP = opcode1;
		}
		//JB (<) [unsigned]
		else if(!strcmpi("JB",inst))
		{
			BuscaOperandos(&opcode1,&opcode2,1);
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'l'));
			if(CF == 1)
				IP = opcode1;
		}
		//JBE (<=) [unsigned]
		else if(!strcmpi("JBE",inst))
		{
			BuscaOperandos(&opcode1,&opcode2,1);
			printf("%s %s",inst,recuperaVLD_indice(opcode1,'l'));
			if(CF == 1 || ZF == 1)
				IP = opcode1;
		}
	}
	else
	{
		// Busca operandos e pega os ponteiros dependendo do que for
		//
		// - Ver qual "inst" que é e separar juntando as que terminam com R,M,I
		//	 para dividir qual tem 2 operandos e qual tem apenas 1
		//
		// - Recuperar os valores dependendo do que eles forem (R,M,I)
		//   e jogá-los em op1 e op2
		//
		// -> chama ULA() passando os parametros diretos

		strcpy(instAux,inst);
		aux = strlen(instAux);

		if(IsTwoOperands(inst))
		{
			instAux[aux-2] = 0;
			printf("%s ",instAux);
			BuscaOperandos(&opcode1,&opcode2,2);
			aux = strlen(inst);
			
			if(inst[aux-2] == 'R')
			{
				if(strcmpi(tabelaREG[opcode1].nome,"ax")==0)
				{
					op1 = (int*)&AX.Reg16;
					tipo = 16;
					printf("AX,");
				}
				else if(strcmpi(tabelaREG[opcode1].nome,"bx")==0)
				{
					op1 = (int*)&BX.Reg16;
					tipo = 16;
					printf("BX,");
				}
				else if(strcmpi(tabelaREG[opcode1].nome,"ah")==0)
				{
					reg1 = &AX.Reg8[AH];
					tipo = 8;
					printf("AH,");
				}
				else if(strcmpi(tabelaREG[opcode1].nome,"al")==0)
				{
					reg1 = &AX.Reg8[AL];
					tipo = 8;
					printf("AL,");
				}
				else if(strcmpi(tabelaREG[opcode1].nome,"bh")==0)
				{
					reg1 = &BX.Reg8[BH];
					tipo = 8;
					printf("BH,");
				}
				else if(strcmpi(tabelaREG[opcode1].nome,"bl")==0)
				{
					reg1 = &BX.Reg8[BL];
					tipo = 8;
					printf("BL,");
				}
			}
			else //memória (variavel)
			{
				for(it=0;it<100;it++)
				{
					if(tabelaVLD[it].tipo == 'b' || tabelaVLD[it].tipo == 'w')
					{
						if(tabelaVLD[it].valor == opcode1)
						{
							printf("%s,",tabelaVLD[it].nome);
							break;
						}
					}
				}
				op1 = (int*)&memory[opcode1];
			}
						
			if(inst[aux-1] == 'R')
			{
				if(strcmpi(tabelaREG[opcode2].nome,"ax")==0)
				{
					op2 = (int*)&AX.Reg16;
					tipo = 16;
					printf("AX");
				}
				else if(strcmpi(tabelaREG[opcode2].nome,"bx")==0)
				{
					op2 = (int*)&BX.Reg16;
					tipo = 16;
					printf("BX");
				}
				else if(strcmpi(tabelaREG[opcode2].nome,"ah")==0)
				{
					reg2 = &AX.Reg8[AH];
					tipo = 8;
					printf("AH");
				}
				else if(strcmpi(tabelaREG[opcode2].nome,"al")==0)
				{
					reg2 = &AX.Reg8[AL];
					tipo = 8;
					printf("AL");
				}
				else if(strcmpi(tabelaREG[opcode2].nome,"bh")==0)
				{
					reg2 = &BX.Reg8[BH];
					tipo = 8;
					printf("BH");
				}
				else if(strcmpi(tabelaREG[opcode2].nome,"bl")==0)
				{
					reg2 = &BX.Reg8[BL];
					tipo = 8;
					printf("BL");
				}
			}
			else if(inst[aux-1] == 'M')
			//	op2 = &memory[opcode2];
			{
				for(it=0;it<100;it++)
				{
					if(tabelaVLD[it].tipo == 'b' || tabelaVLD[it].tipo == 'w')
					{
						if(tabelaVLD[it].valor == opcode2)
						{
							printf("%s",tabelaVLD[it].nome);
							break;
						}
					}
				}
				op2 = (int*)&memory[opcode2];
			}
			else
			{
				printf("%d",opcode2);
				op2 = &opcode2;
			}
		}
		else // Senão é somente 1 operando
		{
			instAux[aux-1] = 0;
			printf("%s ",instAux);
			BuscaOperandos(&opcode1,&opcode2,1);
			aux = strlen(inst);
			
			if(inst[aux-1] == 'R')
			{
				if(strcmpi(tabelaREG[opcode1].nome,"ax")==0)
				{
					op1 = (int*)&AX.Reg16;
					tipo = 16;
					printf("AX");
				}
				else if(strcmpi(tabelaREG[opcode1].nome,"bx")==0)
				{
					op1 = (int*)&BX.Reg16;
					tipo = 16;
					printf("BX");
				}
				else if(strcmpi(tabelaREG[opcode1].nome,"ah")==0)
				{
					reg1 = &AX.Reg8[AH];
					tipo = 8;
					printf("AH");
				}
				else if(strcmpi(tabelaREG[opcode1].nome,"al")==0)
				{
					reg1 = &AX.Reg8[AL];
					tipo = 8;
					printf("AL");
				}
				else if(strcmpi(tabelaREG[opcode1].nome,"bh")==0)
				{
					reg1 = &BX.Reg8[BH];
					tipo = 8;
					printf("BH");
				}
				else if(strcmpi(tabelaREG[opcode1].nome,"bl")==0)
				{
					reg1 = &BX.Reg8[BL];
					tipo = 8;
					printf("BL");
				}
			}
			else
			{
				for(it=0;it<100;it++)
				{
					if(tabelaVLD[it].tipo == 'b' || tabelaVLD[it].tipo == 'w')
					{
						if(tabelaVLD[it].valor == opcode1)
						{
							printf("%s",tabelaVLD[it].nome);
							break;
						}
					}
				}
				op1 = (int*)&memory[opcode1];
			}
		}

		// MOV
		if(strcmpi(inst,"movrm")==0 || strcmpi(inst,"movmr")==0 || strcmpi(inst,"movri")==0 || 
			strcmpi(inst,"movmi")==0 || strcmpi(inst,"movrr")==0 )
		{
			aux = strlen(inst);
			if(inst[aux-2] == 'R')
			{
				if(tipo == 8)
				{
					if(inst[aux-1] == 'R')
						*reg1 = *reg2;
					else
						*reg1 = *op2;
				}
				else
					*op1 = *op2;
			}
			else
			{
				if(inst[aux-1] == 'R')
				{
					if(tipo == 8)
						*op1 = *reg2;
					else
						*op1 = *op2;
				}
				else
					*op1 = *op2;
			}
		}
		else
			ULA(inst,op1,op2,reg1,reg2,tipo);
	}
	
}