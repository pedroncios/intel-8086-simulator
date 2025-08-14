/******************************************************************
							Análisa Erros
*******************************************************************/

#include "montador.h"

int IsImediatoTipo(int im)
{
	if(im >= -128 && im <= 255)
		return 8;
	else if(im >= -32768 && im <= 65535)
		return 16;
	else
		return 0;
}

// Condição TRUE:
// IsRegistrador16(palavraAnt) != -1
// IsRegistrador8(palavraAnt) != -1
// IsMnemonico(palavraAnt) != -1
// IsImediato(palavraAnt) == 1
// IsVariavel(vet, cont, palavra) != -1

void AnalisaErros(FILE *f)
{
	char *palavra, *aux;
	char Linha[200], linha[200], palavraAnt[20], tmp1[20], tmp2[20];
	int x, i, j, auxint, ControlaErro = 0, cont = 0, ContErros = 0, ControlaVirgula = 0;

	printf("\n");
	goto ProxLinha;
	
RestoLinha:
	while(palavra != NULL)
	{
		palavra = strtok (NULL," \n\t");
		if(palavra == 0)
			goto ProxLinha;
		else if(palavra != NULL && palavra[0] != '%')
		{
			ContErros++;
			printf("Erro na linha %d! Instrucao '%s' nao reconhecida!\n", ContLinha, palavra);
		}
		else
			ControlaErro = 0;
	}

ProxLinha:
	while(!feof(f))
	{
		ContLinha++;
		fgets(Linha, 200, f);
		strcpy(linha, Linha);

		palavra = strtok (Linha," \n\t");

		while(palavra != NULL)
		{
			// Ignora os comentarios do arquivo
			if( palavra[0] == '%' ){
				if(ControlaErro == 1){
					ContErros++;
					printf("Erro na linha %d! Instrucao '%s' nao reconhecida!\n", ContLinha, palavraAnt);
					goto ProxLinha;
				}
				else
					goto ProxLinha;
			}

			// Trata erro: labels
			x = strlen(palavra);
			if(palavra[x-1] == ':')	
				goto RestoLinha;

			// Trata "endp"
			if(strcmpi(palavra, "endp") == 0)
			{
				palavraAnt[0] = 0;
				ControlaErro = 0;
				goto RestoLinha;
			}


			// Trata erros: db, dw, equ, proc
			if(strcmpi(palavra, "db") == 0 || strcmpi(palavra, "dw") == 0 || strcmpi(palavra, "equ") == 0 || strcmpi(palavra, "proc") == 0) 
			{
				// Nome == registrador?
				if(IsRegistrador16(palavraAnt) != -1 || IsRegistrador8(palavraAnt) != -1)
				{
					ContErros++;
					printf("Erro na linha %d! Palavra '%s' nao pode ter o nome de um registrador!\n", ContLinha, palavraAnt);
					ControlaErro = 0;
					goto ProxLinha;
				}

				// Nome == mnemonico?
				if(IsMnemonico(palavraAnt) != -1)
				{
					ContErros++;
					printf("Erro na linha %d! Palavra '%s' nao pode ter o nome de um mnemonico!\n", ContLinha, palavraAnt);
					ControlaErro = 0;
					goto ProxLinha;
				}
				
				// Nome == diretiva?
				if(IsDiretiva(palavraAnt) != -1)
				{
					ContErros++;
					printf("Erro na linha %d! Palavra '%s' nao pode ter o nome de uma diretiva!\n", ContLinha, palavraAnt);
					ControlaErro = 0;
					goto ProxLinha;
				}

				// Guardar as variaveis num vetor para la 
				// pra baixo poder comparar se existe a variavel
				if(strcmpi(palavra, "db") == 0 || strcmpi(palavra, "dw") == 0 || strcmpi(palavra, "equ") == 0)
				{
					aux = strtok(NULL," \n\t");
					auxint = str2int(aux);

					if(strcmpi(palavra, "db") == 0)
						var[cont].tipo = 'b';
					else if(strcmpi(palavra, "dw") == 0)
						var[cont].tipo = 'w';
					else if(strcmpi(palavra, "equ") == 0)
						var[cont].tipo = 'e';

					strcpy(var[cont].nome, palavraAnt);
					cont++;

					// Testa entrada permitida DB
					if(strcmpi(palavra, "db") == 0)
					{
						if(auxint < -128 || auxint > 255)
						{
							ContErros++;
							printf("Erro na linha %d! Variavel %s nao pode ter valor acima de 8 bits", ContLinha, palavraAnt);
							ControlaErro = 0;
							goto RestoLinha;
						}
					}

					// Testa entrada permitida DW
					if(strcmpi(palavra, "dw") == 0)
					{
						if(auxint < -32768 || auxint > 65535)
						{
							ContErros++;
							printf("Erro na linha %d! Variavel %s nao pode ter valor acima de 16 bits", ContLinha, palavraAnt);
							ControlaErro = 0;
							goto RestoLinha;
						}
					}

					// Atributo == imediato?
					if(IsImediato(aux) == 1)
					{
						ControlaErro = 0;
						goto RestoLinha;
					}
					else{
						ContErros++;
						printf("Erro na linha %d! '%s' nao e imediato\n", ContLinha, aux);
						ControlaErro = 0;
						goto ProxLinha;
					}
				}

				if(strcmpi(palavra, "proc") == 0)
				{
					ControlaErro = 0;
					goto ProxLinha;
				}
				
				else{
					// Zerar o ControlaErro pra nao dar erro a mais
					ControlaErro = 0;
					printf("OK na linha %d\n", ContLinha);
					goto ProxLinha;
				}
			}

			// Trata erros dos mnemonicos:
			// "mov","add","sub","div","mul","and","or","xor","not","cmp",
			// "jmp","je","jne","jg","jge","jl","jle","call","ret"

			// 0 operador: ret
			// 1 operador: div e mul, not, jumps, call
			// 2 operadores: mov, add, sub, and, or, xor, cmp

			/************* 0 operador *************/

			// Trata Ret
			if(strcmpi(palavra, "ret") == 0)
				goto RestoLinha;


			/************* 1 operador *************/

			// Trata Not
			if(strcmpi(palavraAnt, "not") == 0)
			{
				palavraAnt[0] = 0;
				if(IsRegistrador16(palavra) != -1 || IsRegistrador8(palavra) != -1 || IsVariavel(cont, palavra) != -1 )
				{
					ControlaErro = 0;
					goto RestoLinha;
				}

				else{
					ContErros++;
					ControlaErro = 0;
					printf("Erro na linha %d! Instrucao '%s' nao reconhecida!\n", ContLinha, palavra);
					goto RestoLinha;
				}
			}

			// Trata Jumps
			if(strcmpi(palavraAnt, "jmp") == 0 || strcmpi(palavraAnt, "je") == 0 || 
				strcmpi(palavraAnt, "jne") == 0 || strcmpi(palavraAnt, "jg") == 0 || 
				strcmpi(palavraAnt, "jge") == 0 || strcmpi(palavraAnt, "jl") == 0 || 
				strcmpi(palavraAnt, "jle") == 0 || strcmpi(palavraAnt, "ja") == 0 || 
				strcmpi(palavraAnt, "jae") == 0 || strcmpi(palavraAnt, "jb") == 0 || strcmpi(palavraAnt, "jbe") == 0)
			{
				// Tratar o endereçamento? Senao erro!
				palavraAnt[0] = 0;
				ControlaErro = 0;
				goto RestoLinha;
			}

			// Trata Call
			if(strcmpi(palavraAnt, "call") == 0)
			{
				// Tratar o endereçamento? Senao erro!
				palavraAnt[0] = 0;
				ControlaErro = 0;
				goto RestoLinha;
			}

			// Trata Div e Mul
			if(strcmpi(palavraAnt, "div") == 0 || strcmpi(palavraAnt, "mul") == 0 ||
				strcmpi(palavraAnt, "idiv") == 0 || strcmpi(palavraAnt, "imul") == 0)
			{
				palavraAnt[0] = 0;
				if(IsRegistrador16(palavra) != -1 || IsRegistrador8(palavra) != -1 || IsVariavel(cont, palavra) != -1)
				{
					ControlaErro = 0;
					goto RestoLinha;
				}

				else{
					ContErros++;
					ControlaErro = 0;
					printf("Erro na linha %d! Instrucao '%s' nao reconhecida!\n", ContLinha, palavra);
					goto ProxLinha;
				}
			}

			/************* 2 operadores *************/

			// Trata MOV, ADD, SUB, CMP
			if(strcmpi(palavraAnt, "mov") == 0 || strcmpi(palavraAnt, "add") == 0 || strcmpi(palavraAnt, "sub") == 0 || strcmpi(palavraAnt, "cmp") == 0)
			{
				palavraAnt[0] = 0;

				// Trata virgula no meio com as 2 strings
				ControlaVirgula = VirgulaMid(palavra);
				if(ControlaVirgula == 1)
				{
					i=0;
					while(palavra[i] != ',')
					{
						tmp1[i] = palavra[i];
						i++;
					}
					tmp1[i] = '\0';

					i++;
					x = strlen(palavra);
					j=0;
					while(i != x)
					{
						tmp2[j] = palavra[i];
						i++;
						j++;
					}
					tmp2[j] = '\0';

					strcpy(palavra, tmp1);
					strcpy(palavraAnt, tmp2);
				}

				if(ControlaVirgula == 0 && TemVirgula(palavra) == 1)
					// Trata virgula no começo
					palavra = TrataVirgula(palavra);

				// Verifica se é REG 8
				if(IsRegistrador8(palavra) != -1)
				{
					if(ControlaVirgula == 0)
						strcpy(palavraAnt, strtok (NULL," \n\t"));

					if(ControlaVirgula == 0 && TemVirgula(palavraAnt) == 1)
						// Trata virgula no começo
						TrataVirgula(palavraAnt);

					// Trata a virgula no final do 2° operando
					if(palavraAnt[strlen(palavraAnt)-1] == ',')
					{
						ContErros++;
						ControlaErro = 0;
						printf("Erro na linha %d! ',' a mais!\n\n", ContLinha);
						goto ProxLinha;
					}

					// Trata virgula no meio
					if(palavraAnt[0] == ',')
						strcpy(palavraAnt, strtok (NULL," \n\t"));

					//////////////////////////////////////////////////////////////////////

					if(IsImediato(palavraAnt) == 1 && IsImediatoTipo(str2int(palavraAnt))==0)
					{	
						ContErros++;
						printf("Erro na linha %d! Incompatibilidade de tipos, nao e de 8 bits nem 16 bits\n", ContLinha);
						ControlaErro = 0;
						goto RestoLinha;
					}

					// Incompatibilidade de tipos
					if(IsRegistrador16(palavraAnt) != -1 || (IsVariavel(cont, palavraAnt) != -1 && var[IsVariavel(cont, palavraAnt)].tipo == 'w') || (IsImediato(palavraAnt) == 1 && IsImediatoTipo(str2int(palavraAnt))==16) )
					{
						ContErros++;
						printf("Erro na linha %d! Incompatibilidade de tipos(8 bits com 16 bits)\n", ContLinha);
						ControlaErro = 0;
						goto RestoLinha;
					}

					// Verifica se é de REG/REG || REG/IMED || REG/MEM
					if(IsRegistrador8(palavraAnt) != -1 || 
						(IsImediato(palavraAnt) == 1 && IsImediatoTipo(str2int(palavraAnt)) == 8) || 
						(IsVariavel(cont, palavraAnt) != -1 && var[IsVariavel(cont, palavraAnt)].tipo != 'w') || IsBinario(palavraAnt) == 1)
					{
						ControlaErro = 0;
						goto RestoLinha;
					}
					else{
						ContErros++;
						ControlaErro = 0;
						printf("Erro na linha %d! Instrucao '%s' nao reconhecida!\n", ContLinha, palavraAnt);
						goto ProxLinha;
					}
				}

				// Verifica se é REG 16
				if(IsRegistrador16(palavra) != -1)
				{
					if(ControlaVirgula == 0)
						strcpy(palavraAnt, strtok (NULL," \n\t"));

					if(ControlaVirgula == 0 && TemVirgula(palavraAnt) == 1)
						// Trata virgula no começo
						TrataVirgula(palavraAnt);

					// Trata a virgula no final do 2° operando
					if(palavraAnt[strlen(palavraAnt)-1] == ',')
					{
						ContErros++;
						ControlaErro = 0;
						printf("Erro na linha %d! ',' a mais!\n\n", ContLinha);
						goto ProxLinha;
					}

					// Trata virgula no meio
					if(palavraAnt[0] == ',')
						strcpy(palavraAnt, strtok (NULL," \n\t"));

					//////////////////////////////////////////////////////////////////////

					// Incompatibilidade
					if(IsRegistrador8(palavraAnt) != -1 || (IsVariavel(cont, palavraAnt) != -1 && var[IsVariavel(cont, palavraAnt)].tipo == 'b'))
					{	
						ContErros++;
						printf("Erro na linha %d! Incompatibilidade de tipos(16 bits com 8 bits)\n", ContLinha);
						ControlaErro = 0;
						goto RestoLinha;
					}

					// Verifica se é de REG/REG || REG/IMED || REG/MEM
					if(IsRegistrador16(palavraAnt) != -1 || IsImediato(palavraAnt) == 1 || (IsVariavel(cont, palavraAnt) != -1 && var[IsVariavel(cont, palavraAnt)].tipo == 'w') || IsBinario(palavraAnt) == 1)
					{
						ControlaErro = 0;
						goto RestoLinha;
					}
					else{
						ContErros++;
						ControlaErro = 0;
						printf("Erro na linha %d! Instrucao '%s' nao reconhecida!\n", ContLinha, palavraAnt);
						goto ProxLinha;
					}
				}

				// Verifica se é MEM 8 bits
				else if(IsVariavel(cont, palavra) != -1 && var[IsVariavel(cont, palavra)].tipo == 'b')
				{
					if(ControlaVirgula == 0)
						strcpy(palavraAnt, strtok (NULL," \n\t"));

					if(ControlaVirgula == 0 && TemVirgula(palavraAnt) == 1)
						// Trata virgula no começo
						TrataVirgula(palavraAnt);

					// Trata a virgula no final do 2° operando
					if(palavraAnt[strlen(palavraAnt)-1] == ',')
					{
						ContErros++;
						ControlaErro = 0;
						printf("Erro na linha %d! ',' a mais!\n\n", ContLinha);
						goto ProxLinha;
					}

					// Trata virgula no meio
					if(palavraAnt[0] == ',')
						strcpy(palavraAnt, strtok (NULL," \n\t"));

					//////////////////////////////////////////////////////////////////////

					if(IsImediato(palavraAnt) == 1 && IsImediatoTipo(str2int(palavraAnt))==0)
					{	
						ContErros++;
						printf("Erro na linha %d! Incompatibilidade de tipos, nao e de 8 bits nem 16 bits\n", ContLinha);
						ControlaErro = 0;
						goto RestoLinha;
					}
					
					// Incompatibilidade de tipos
					if(IsRegistrador16(palavraAnt) != -1 || (IsImediato(palavraAnt) == 1 && IsImediatoTipo(str2int(palavraAnt))==16) )
					{
						ContErros++;
						printf("Erro na linha %d! Incompatibilidade de tipos(8 bits com 16 bits)\n", ContLinha);
						ControlaErro = 0;
						goto RestoLinha;
					}

					// Verifica se é de MEM/REG || MEM/IMED
					if(IsRegistrador8(palavraAnt) != -1 || (IsImediato(palavraAnt) == 1 && IsImediatoTipo(str2int(palavraAnt))==8 ) || IsBinario(palavraAnt) == 1)
					{
						ControlaErro = 0;
						goto RestoLinha;
					}
					else{
						ContErros++;
						ControlaErro = 0;
						printf("Erro na linha %d! Instrucao '%s' nao reconhecida!\n", ContLinha, palavraAnt);
						goto ProxLinha;
					}
				}


				// Verifica se é MEM 16 bits
				else if(IsVariavel(cont, palavra) != -1 && var[IsVariavel(cont, palavra)].tipo == 'w')
				{
					if(ControlaVirgula == 0)
						strcpy(palavraAnt, strtok (NULL," \n\t"));

					if(ControlaVirgula == 0 && TemVirgula(palavraAnt) == 1)
						// Trata virgula no começo
						TrataVirgula(palavraAnt);

					// Trata a virgula no final do 2° operando
					if(palavraAnt[strlen(palavraAnt)-1] == ',')
					{
						ContErros++;
						ControlaErro = 0;
						printf("Erro na linha %d! ',' a mais!\n\n", ContLinha);
						goto ProxLinha;
					}

					// Trata virgula no meio
					if(palavraAnt[0] == ',')
						strcpy(palavraAnt, strtok (NULL," \n\t"));

					//////////////////////////////////////////////////////////////////////

					if(IsVariavel(cont, palavra) != -1)
					{	
						ContErros++;
						printf("Erro na linha %d! Operacao de MEM/MEM nao permitida!\n", ContLinha);
						ControlaErro = 0;
						goto RestoLinha;
					}

					// Incompatibilidade
					if(IsRegistrador8(palavraAnt) != -1)
					{	
						ContErros++;
						printf("Erro na linha %d! Incompatibilidade de tipos(16 bits com 8 bits)\n", ContLinha);
						ControlaErro = 0;
						goto RestoLinha;
					}

					// Verifica se é de MEM/REG || MEM/IMED
					if(IsRegistrador16(palavraAnt) != -1 || IsImediato(palavraAnt) == 1 || IsBinario(palavraAnt) == 1)
					{
						ControlaErro = 0;
						goto RestoLinha;
					}
					else{
						ContErros++;
						ControlaErro = 0;
						printf("Erro na linha %d! Instrucao '%s' nao reconhecida!\n", ContLinha, palavraAnt);
						goto ProxLinha;
					}
				}

				else{
					ContErros++;
					ControlaErro = 0;
					printf("Erro na linha %d! Instrucao '%s' nao reconhecida!\n", ContLinha, palavra);
					goto ProxLinha;
				}
			}
			
			// Trata AND, OR, XOR
			if( strcmpi(palavraAnt, "and") == 0 || strcmpi(palavraAnt, "or") == 0 || strcmpi(palavraAnt, "xor") == 0 )
			{
				palavraAnt[0] = 0;

				// Trata virgula no meio com as 2 strings
				ControlaVirgula = VirgulaMid(palavra);
				if(ControlaVirgula == 1)
				{
					i=0;
					while(palavra[i] != ',')
					{
						tmp1[i] = palavra[i];
						i++;
					}
					tmp1[i] = '\0';

					i++;
					x = strlen(palavra);
					j=0;
					while(i != x)
					{
						tmp2[j] = palavra[i];
						i++;
						j++;
					}
					tmp2[j] = '\0';

					strcpy(palavra, tmp1);
					strcpy(palavraAnt, tmp2);
				}

				if(ControlaVirgula == 0 && TemVirgula(palavra) == 1)
					// Trata virgula no começo
					palavra = TrataVirgula(palavra);

				// Verifica se é REG
				if(IsRegistrador16(palavra) != -1 || IsRegistrador8(palavra) != -1)
				{
					if(ControlaVirgula == 0)
						strcpy(palavraAnt, strtok (NULL," \n\t"));

					if(ControlaVirgula == 0 && TemVirgula(palavraAnt) == 1)
						// Trata virgula no começo
						TrataVirgula(palavraAnt);

					// Trata a virgula no final do 2° operando
					if(palavraAnt[strlen(palavraAnt)-1] == ',')
					{
						ContErros++;
						ControlaErro = 0;
						printf("Erro na linha %d! ',' a mais!\n\n", ContLinha);
						goto ProxLinha;
					}

					// Trata virgula no meio
					if(palavraAnt[0] == ',')
						strcpy(palavraAnt, strtok (NULL," \n\t"));

					// Verifica se é de REG/REG || IMED/REG || MEM\REG
					if(IsRegistrador16(palavraAnt) != -1 || IsRegistrador8(palavraAnt) != -1 || IsImediato(palavraAnt) == 1 || IsBinario(palavraAnt) == 1 || IsVariavel(cont, palavraAnt) != -1)
					{
						ControlaErro = 0;
						goto RestoLinha;
					}
					else{
						ContErros++;
						ControlaErro = 0;
						printf("Erro na linha %d! Instrucao '%s' nao reconhecida!\n", ContLinha, palavraAnt);
						goto ProxLinha;
					}
				}

				// Verifica se é Memória
				else if(IsVariavel(cont, palavra) != -1)
				{
					if(ControlaVirgula == 0)
						strcpy(palavraAnt, strtok (NULL," \n\t"));

					if(ControlaVirgula == 0 && TemVirgula(palavraAnt) == 1)
						// Trata virgula no começo
						TrataVirgula(palavraAnt);

					// Trata a virgula no final do 2° operando
					if(palavraAnt[strlen(palavraAnt)-1] == ',')
					{
						ContErros++;
						ControlaErro = 0;
						printf("Erro na linha %d! ',' a mais!\n\n", ContLinha);
						goto ProxLinha;
					}

					// Trata virgula no meio
					if(palavraAnt[0] == ',')
						strcpy(palavraAnt, strtok (NULL," \n\t"));

					// Verifica se é de REG/MEM || IMED/MEM
					if(IsRegistrador16(palavraAnt) != -1 || IsRegistrador8(palavraAnt) != -1 || IsImediato(palavraAnt) == 1 || IsBinario(palavraAnt) == 1)
					{
						ControlaErro = 0;
						goto RestoLinha;
					}
					else{
						ContErros++;
						ControlaErro = 0;
						printf("Erro na linha %d! Instrucao '%s' nao reconhecida!\n", ContLinha, palavraAnt);
						goto ProxLinha;
					}
				}

				else{
					ContErros++;
					ControlaErro = 0;
					printf("Erro na linha %d! Instrucao '%s' nao reconhecida!\n", ContLinha, palavra);
					goto ProxLinha;
				}
			}

			/************* Tratamento de Erros *************/

			// Trata se a primeira palavra é invalida, 
			// podendo a segunda validá-la(declaração de variavel e rotina)
			if(ControlaErro == 1){
				ContErros++;
				ControlaErro = 0;
				printf("Erro na linha %d! Instrucao: %s\n", ContLinha, Linha);
				strcpy(palavraAnt, palavra);
				palavra = strtok (NULL," \n\t");
				goto ProxLinha;
			}
			
			// Se a palavra nao for reconhecida
			ControlaErro = 1;

			// Pega proxima palavra e mantem uma string palavraAnt pra palavra anterior
			strcpy(palavraAnt, palavra);
			palavra = strtok (NULL," \n\t");
		}
	}
	if(ContErros == 0)
		OK = 1;
	printf("\nAnalise de Erros Concluida!\n\n");
	printf(" *******************************\n*\tLinhas Analisadas: %d\t*\n*\tErros Encontrados: %d\t*\n *******************************\n\n", ContLinha, ContErros);
}