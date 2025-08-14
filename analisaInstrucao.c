/******************************************************************
							Análisa Instrução
*******************************************************************/

#include"montador.h"

void AnalisaInstrucao(FILE *f)
{
	char Linha[200],type[10];
	char *op1, *op2, *op3;
	int e1 = 0, e2 = 0;
	int opcode = 0;

	FILE *obj;

	obj = fopen("prog.code","w");
	printf("\n");
	
	//While "linha por linha"
	while(!feof(f))
	{
		//Pega Linha
		fgets(Linha, 200, f);
		//Pega primeira palavra da linha
		op1 = strtok(Linha,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
		//Trata caso apareça uma linha em branco
		if(op1 == NULL)
			continue;
		//Caso a linha seja um comentário
		if( op1[0] == '%' )
			continue;  //(pega a proxima linha)
		
		//Diretiva HLT
		else if(strcmpi(op1,"hlt")==0)
		{
			opcode = tabelaInst[getOpcode(op1)].opcode;
			fprintf(obj,"0x%x\n",opcode);
//			printf("0x%x\n",opcode);
		}
		//Instrução CALL
		else if(strcmpi(op1,"call")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			//Busca OP2 na tabela de endereços e recupera o endereço do proc pra variável e1
			e1 = tabelaVLD[recuperaVLD(op2)].valor;
			opcode = tabelaInst[getOpcode(op1)].opcode;
			fprintf(obj,"0x%x 0x%x\n",opcode,e1);
//			printf("0x%x 0x%x\n",opcode,e1);
		}
		//Instrução RET
		else if(strcmpi(op1,"ret")==0)
		{
			opcode = tabelaInst[getOpcode(op1)].opcode;
			fprintf(obj,"0x%x\n",opcode);
//			printf("0x%x\n",opcode);
		}
		//Instrução NOT
		else if(strcmpi(op1,"not")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			
			strcpy(type,"NOT");

			if(IsRegistrador8(op2)!=-1 || IsRegistrador16(op2)!=-1)
			{
				sprintf(type,"%sR",type);
				e1 = recuperaReg(op2);
			}
			else if(tabelaVLD[recuperaVLD(op2)].tipo == 'b' || tabelaVLD[recuperaVLD(op2)].tipo == 'w')
			{
				sprintf(type,"%sM",type);
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			}
			opcode = tabelaInst[getOpcode(type)].opcode;
			fprintf(obj,"0x%x 0x%x\n",opcode,e1);
//			printf("0x%x 0x%x\n",opcode,e1);
		}
		//Instrução MOV
		else if(strcmpi(op1,"mov")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			op3 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			
			strcpy(type,"MOV");

			if(IsRegistrador8(op2)!=-1 || IsRegistrador16(op2)!=-1)
			{
				sprintf(type,"%sR",type);
				e1 = recuperaReg(op2);
			}
			else if(tabelaVLD[recuperaVLD(op2)].tipo == 'b' || tabelaVLD[recuperaVLD(op2)].tipo == 'w')
			{
				sprintf(type,"%sM",type);
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			}

			if(IsRegistrador8(op3)!=-1 || IsRegistrador16(op3)!=-1)
			{
				sprintf(type,"%sR",type);
				e2 = recuperaReg(op3);
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'b' || tabelaVLD[recuperaVLD(op3)].tipo == 'w')	
			{
				sprintf(type,"%sM",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'd')
			{
				sprintf(type,"%sI",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(IsBinario(op3))
			{
				sprintf(type,"%sI",type);
				e2 = bin2int(op3);
			}
			else if(IsImediato(op3))
			{
				sprintf(type,"%sI",type);
				e2 = str2int(op3);
			}

			//Procurar o opcode com getOpcode(type)
			opcode = tabelaInst[getOpcode(type)].opcode;
			/*
			{ Recuperar endereços de op2 e op3 pra por no arquivo junto com o opcode (usar e1 e e2 talvez)
 Usado acima{ Se for registrador/memória guarda o endereço (índice tabela)
			{ Se for imediato coloca o valor direto. */
			fprintf(obj,"0x%x 0x%x 0x%x\n",opcode,e1,e2);
//			printf("0x%x 0x%x 0x%x\n",opcode,e1,e2);
			//Fazer os mesmos procedimentos para o resto das funções que seguem esse padrão <------------------------				
		}
		//Instrução ADD
		else if(strcmpi(op1,"add")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			op3 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			
			strcpy(type,"ADD");

			if(IsRegistrador8(op2)!=-1 || IsRegistrador16(op2)!=-1)
			{
				sprintf(type,"%sR",type);
				e1 = recuperaReg(op2);
			}
			else if(tabelaVLD[recuperaVLD(op2)].tipo == 'b' || tabelaVLD[recuperaVLD(op2)].tipo == 'w')
			{
				sprintf(type,"%sM",type);
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			}

			if(IsRegistrador8(op3)!=-1 || IsRegistrador16(op3)!=-1)
			{
				sprintf(type,"%sR",type);
				e2 = recuperaReg(op3);
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'b' || tabelaVLD[recuperaVLD(op3)].tipo == 'w')	
			{
				sprintf(type,"%sM",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'd')
			{
				sprintf(type,"%sI",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(IsBinario(op3))
			{
				sprintf(type,"%sI",type);
				e2 = bin2int(op3);
			}
			else if(IsImediato(op3))
			{
				sprintf(type,"%sI",type);
				e2 = str2int(op3);
			}

			//Procurar o opcode com getOpcode(type)
			opcode = tabelaInst[getOpcode(type)].opcode;
			fprintf(obj,"0x%x 0x%x 0x%x\n",opcode,e1,e2);
//			printf("0x%x 0x%x 0x%x\n",opcode,e1,e2);
		}
		//Instrução SUB
		else if(strcmpi(op1,"sub")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			op3 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			
			strcpy(type,"SUB");

			if(IsRegistrador8(op2)!=-1 || IsRegistrador16(op2)!=-1)
			{
				sprintf(type,"%sR",type);
				e1 = recuperaReg(op2);
			}
			else if(tabelaVLD[recuperaVLD(op2)].tipo == 'b' || tabelaVLD[recuperaVLD(op2)].tipo == 'w')
			{
				sprintf(type,"%sM",type);
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			}

			if(IsRegistrador8(op3)!=-1 || IsRegistrador16(op3)!=-1)
			{
				sprintf(type,"%sR",type);
				e2 = recuperaReg(op3);
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'b' || tabelaVLD[recuperaVLD(op3)].tipo == 'w')	
			{
				sprintf(type,"%sM",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'd')
			{
				sprintf(type,"%sI",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(IsBinario(op3))
			{
				sprintf(type,"%sI",type);
				e2 = bin2int(op3);
			}
			else if(IsImediato(op3))
			{
				sprintf(type,"%sI",type);
				e2 = str2int(op3);
			}

			//Procurar o opcode com getOpcode(type)
			opcode = tabelaInst[getOpcode(type)].opcode;
			fprintf(obj,"0x%x 0x%x 0x%x\n",opcode,e1,e2);					
//			printf("0x%x 0x%x 0x%x\n",opcode,e1,e2);
		}
		//Instrução AND
		else if(strcmpi(op1,"and")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			op3 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			
			strcpy(type,"AND");

			if(IsRegistrador8(op2)!=-1 || IsRegistrador16(op2)!=-1)
			{
				sprintf(type,"%sR",type);
				e1 = recuperaReg(op2);
			}
			else if(tabelaVLD[recuperaVLD(op2)].tipo == 'b' || tabelaVLD[recuperaVLD(op2)].tipo == 'w')
			{
				sprintf(type,"%sM",type);
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			}

			if(IsRegistrador8(op3)!=-1 || IsRegistrador16(op3)!=-1)
			{
				sprintf(type,"%sR",type);
				e2 = recuperaReg(op3);
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'b' || tabelaVLD[recuperaVLD(op3)].tipo == 'w')	
			{
				sprintf(type,"%sM",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'd')
			{
				sprintf(type,"%sI",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(IsBinario(op3))
			{
				sprintf(type,"%sI",type);
				e2 = bin2int(op3);
			}
			else if(IsImediato(op3))
			{
				sprintf(type,"%sI",type);
				e2 = str2int(op3);
			}

			//Procurar o opcode com getOpcode(type)
			opcode = tabelaInst[getOpcode(type)].opcode;
			fprintf(obj,"0x%x 0x%x 0x%x\n",opcode,e1,e2);	
//			printf("0x%x 0x%x 0x%x\n",opcode,e1,e2);
		}
		//Instrução OR
		else if(strcmpi(op1,"or")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			op3 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			
			strcpy(type,"OR");

			if(IsRegistrador8(op2)!=-1 || IsRegistrador16(op2)!=-1)
			{
				sprintf(type,"%sR",type);
				e1 = recuperaReg(op2);
			}
			else if(tabelaVLD[recuperaVLD(op2)].tipo == 'b' || tabelaVLD[recuperaVLD(op2)].tipo == 'w')
			{
				sprintf(type,"%sM",type);
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			}

			if(IsRegistrador8(op3)!=-1 || IsRegistrador16(op3)!=-1)
			{
				sprintf(type,"%sR",type);
				e2 = recuperaReg(op3);
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'b' || tabelaVLD[recuperaVLD(op3)].tipo == 'w')	
			{
				sprintf(type,"%sM",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'd')
			{
				sprintf(type,"%sI",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(IsBinario(op3))
			{
				sprintf(type,"%sI",type);
				e2 = bin2int(op3);
			}
			else if(IsImediato(op3))
			{
				sprintf(type,"%sI",type);
				e2 = str2int(op3);
			}

			//Procurar o opcode com getOpcode(type)
			opcode = tabelaInst[getOpcode(type)].opcode;
			fprintf(obj,"0x%x 0x%x 0x%x\n",opcode,e1,e2);		
//			printf("0x%x 0x%x 0x%x\n",opcode,e1,e2);
		}
		//Instrução XOR
		else if(strcmpi(op1,"xor")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			op3 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			
			strcpy(type,"XOR");

			if(IsRegistrador8(op2)!=-1 || IsRegistrador16(op2)!=-1)
			{
				sprintf(type,"%sR",type);
				e1 = recuperaReg(op2);
			}
			else if(tabelaVLD[recuperaVLD(op2)].tipo == 'b' || tabelaVLD[recuperaVLD(op2)].tipo == 'w')
			{
				sprintf(type,"%sM",type);
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			}

			if(IsRegistrador8(op3)!=-1 || IsRegistrador16(op3)!=-1)
			{
				sprintf(type,"%sR",type);
				e2 = recuperaReg(op3);
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'b' || tabelaVLD[recuperaVLD(op3)].tipo == 'w')	
			{
				sprintf(type,"%sM",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'd')
			{
				sprintf(type,"%sI",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(IsBinario(op3))
			{
				sprintf(type,"%sI",type);
				e2 = bin2int(op3);
			}
			else if(IsImediato(op3))
			{
				sprintf(type,"%sI",type);
				e2 = str2int(op3);
			}

			//Procurar o opcode com getOpcode(type)
			opcode = tabelaInst[getOpcode(type)].opcode;
			fprintf(obj,"0x%x 0x%x 0x%x\n",opcode,e1,e2);	
//			printf("0x%x 0x%x 0x%x\n",opcode,e1,e2);
		}
		//Instrução CMP
		else if(strcmpi(op1,"cmp")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			op3 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			
			strcpy(type,"CMP");

			if(IsRegistrador8(op2)!=-1 || IsRegistrador16(op2)!=-1)
			{
				sprintf(type,"%sR",type);
				e1 = recuperaReg(op2);
			}
			else if(tabelaVLD[recuperaVLD(op2)].tipo == 'b' || tabelaVLD[recuperaVLD(op2)].tipo == 'w')
			{
				sprintf(type,"%sM",type);
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			}

			if(IsRegistrador8(op3)!=-1 || IsRegistrador16(op3)!=-1)
			{
				sprintf(type,"%sR",type);
				e2 = recuperaReg(op3);
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'b' || tabelaVLD[recuperaVLD(op3)].tipo == 'w')	
			{
				sprintf(type,"%sM",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(tabelaVLD[recuperaVLD(op3)].tipo == 'd')
			{
				sprintf(type,"%sI",type);
				e2 = tabelaVLD[recuperaVLD(op3)].valor;
			}
			else if(IsBinario(op3))
			{
				sprintf(type,"%sI",type);
				e2 = bin2int(op3);
			}
			else if(IsImediato(op3))
			{
				sprintf(type,"%sI",type);
				e2 = str2int(op3);
			}

			//Procurar o opcode com getOpcode(type)
			opcode = tabelaInst[getOpcode(type)].opcode;
			fprintf(obj,"0x%x 0x%x 0x%x\n",opcode,e1,e2);	
//			printf("0x%x 0x%x 0x%x\n",opcode,e1,e2);
		}
		//Instrução MUL
		else if(strcmpi(op1,"mul")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			
			strcpy(type,"MUL");

			if(IsRegistrador8(op2)!=-1 || IsRegistrador16(op2)!=-1)
			{
				sprintf(type,"%sR",type);
				e1 = recuperaReg(op2);
			}
			else if(tabelaVLD[recuperaVLD(op2)].tipo == 'b' || tabelaVLD[recuperaVLD(op2)].tipo == 'w')
			{
				sprintf(type,"%sM",type);
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			}
			opcode = tabelaInst[getOpcode(type)].opcode;
			fprintf(obj,"0x%x 0x%x\n",opcode,e1);
//			printf("0x%x 0x%x\n",opcode,e1);
		}
		//Instrução DIV
		else if(strcmpi(op1,"div")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			
			strcpy(type,"DIV");

			if(IsRegistrador8(op2)!=-1 || IsRegistrador16(op2)!=-1)
			{
				sprintf(type,"%sR",type);
				e1 = recuperaReg(op2);
			}
			else if(tabelaVLD[recuperaVLD(op2)].tipo == 'b' || tabelaVLD[recuperaVLD(op2)].tipo == 'w')
			{
				sprintf(type,"%sM",type);
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			}
			opcode = tabelaInst[getOpcode(type)].opcode;
			fprintf(obj,"0x%x 0x%x\n",opcode,e1);
//			printf("0x%x 0x%x\n",opcode,e1);
		}
		//Instrução IMUL
		else if(strcmpi(op1,"imul")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			
			strcpy(type,"IMUL");

			if(IsRegistrador8(op2)!=-1 || IsRegistrador16(op2)!=-1)
			{
				sprintf(type,"%sR",type);
				e1 = recuperaReg(op2);
			}
			else if(tabelaVLD[recuperaVLD(op2)].tipo == 'b' || tabelaVLD[recuperaVLD(op2)].tipo == 'w')
			{
				sprintf(type,"%sM",type);
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			}
			opcode = tabelaInst[getOpcode(type)].opcode;
			fprintf(obj,"0x%x 0x%x\n",opcode,e1);
//			printf("0x%x 0x%x\n",opcode,e1);
		}
		//Instrução IDIV
		else if(strcmpi(op1,"idiv")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");
			
			strcpy(type,"IDIV");

			if(IsRegistrador8(op2)!=-1 || IsRegistrador16(op2)!=-1)
			{
				sprintf(type,"%sR",type);
				e1 = recuperaReg(op2);
			}
			else if(tabelaVLD[recuperaVLD(op2)].tipo == 'b' || tabelaVLD[recuperaVLD(op2)].tipo == 'w')
			{
				sprintf(type,"%sM",type);
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			}
			opcode = tabelaInst[getOpcode(type)].opcode;
			fprintf(obj,"0x%x 0x%x\n",opcode,e1);
//			printf("0x%x 0x%x\n",opcode,e1);
		}
		//Instrução JPM'SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSsssssssssssssssssssssssssssssssssssss
		else if(strcmpi(op1,"jmp")==0 || strcmpi(op1,"je")==0 || strcmpi(op1,"jne")==0 || 
			strcmpi(op1,"jge")==0 || strcmpi(op1,"jle")==0 || strcmpi(op1,"jg")==0 || 
			strcmpi(op1,"jl")==0 || strcmpi(op1,"ja")==0 || strcmpi(op1,"jae")==0 || 
			strcmpi(op1,"jb")==0 || strcmpi(op1,"jbe")==0)
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n\t");

			if(tabelaVLD[recuperaVLD(op2)].tipo == 'l')
				e1 = tabelaVLD[recuperaVLD(op2)].valor;
			opcode = tabelaInst[getOpcode(op1)].opcode;
			fprintf(obj,"0x%x 0x%x\n",opcode,e1);
//			printf("0x%x 0x%x\n",opcode,e1);
		}

		//Pensar como fazer os que não seguem o padrão de "primeira palavra", ou seja, os que a primeira palavra da
		//linha (instrução) não são mnemonicos (podem ser qualquer coisa, como o nome de um proc ou variável).

		else
		{
			op2 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n");
			if(op2 != NULL)
			{
				if(strcmpi(op2,"db")==0 || strcmpi(op2,"dw")==0)
				{
					op3 = strtok(NULL,"(){}<>?!\\;: ,.-+'_*#@&$\n");
					if(strcmpi(op3,"?")==0)
						opcode = 0;
					else
						opcode = str2int(op3);
					fprintf(obj,"0x%x\n",opcode);
//					printf("0x%x\n",opcode);
				}
			}
		}
	}
	fclose(obj);
	printf("Arquivo de instrucoes criado com sucesso.\n");
}