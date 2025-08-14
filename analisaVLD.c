/******************************************************************
			Análisa VLD(Variaveis, labels e diretivas)
*******************************************************************/

#include"montador.h"

void AnalisaVLD(FILE *f)
{
	char *palavra, *p;
	char Linha[200], linha[200], palavraAnt[100];  
	int x;
	
	while(!feof(f))
	{
		fgets(Linha, 200, f);
		strcpy(linha, Linha);

		palavra = strtok (Linha,"()[]{}<>?!\\; ,.-+'_*#@&$\n\t");
		if(palavra != NULL && palavra[0] == '%')
			continue;

		while(palavra != NULL)
		{
			
			// trata db e dw
			if(strcmpi(palavra, "db") == 0 || strcmpi(palavra, "dw") == 0) 
			{
				// armazena os dados na tabela
				if(strcmpi(palavra, "db") == 0)
				{
					strcpy(tabelaVLD[ContVLD].nome, palavraAnt);
					palavra = strtok (NULL,"()[]{}<>?!\\;: ,.-+'_*#@&$\n\t"); // pega o valor da variavel ex. X db 0(a terceira string)
					tabelaVLD[ContVLD].valor = ContLocacao;
					tabelaVLD[ContVLD].tipo = 'b';
					ContVLD++;
					break;
				}
				else if(strcmpi(palavra, "dw") == 0)
				{
					strcpy(tabelaVLD[ContVLD].nome, palavraAnt);
					palavra = strtok (NULL,"()[]{}<>?!\\;: ,.-+'_*#@&$\n\t"); // pega o valor da variavel ex. X db 0(a terceira string)
					tabelaVLD[ContVLD].valor = ContLocacao;
					tabelaVLD[ContVLD].tipo = 'w';
					ContVLD++;
					break;
				}
			}
			
			// trata Proc Near
			if(strcmpi(palavra, "proc") == 0) 
			{
				// armazena os dados na tabela
				strcpy(tabelaVLD[ContVLD].nome, palavraAnt);
				tabelaVLD[ContVLD].valor = ContLocacao; // receber endereço
				tabelaVLD[ContVLD].tipo = 'd';
				ContVLD++;
				break;
			}
			
			// trata equ
			if(strcmpi(palavra, "equ") == 0)
			{
				//armazena dados na tabela
				strcpy(tabelaVLD[ContVLD].nome, palavraAnt);
				palavra = strtok (NULL,"()[]{}<>?!\\;: ,.-+'_*#@&$\n\t"); // pega o valor da variavel ex. X db 0(a terceira string)
				tabelaVLD[ContVLD].valor = str2int(palavra);
				tabelaVLD[ContVLD].tipo = 'd';
				ContVLD++;
				break;
			}

			strcpy(palavraAnt, palavra);
			palavra = strtok (NULL,"()[]{}<>?!\\; ,.-+'_*#@&$\n\t");
		}

		p = strtok (linha,"()[]{}<>?!\\; ,.-+'_*#@&$\n\t");
		if(p != NULL && p[0] != '%')
		{
			// trata labels
			x = strlen(p);
			if(p[x-1] == ':')
			{
				// tira da string o ':' ficando só o nome do label
				p[x-1] = p[x];
				// armazena os dados na tabela
				strcpy(tabelaVLD[ContVLD].nome, p);
				tabelaVLD[ContVLD].valor = ContLocacao; //receber endereço
				tabelaVLD[ContVLD].tipo = 'l';
				ContVLD++;
				continue;
			}
			else if(strcmpi(p, "hlt") != 0)
				Enderecamento(p);
		}
	}
	printf("Enderecamento Concluido!\n");
}
