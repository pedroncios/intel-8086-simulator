#include "montador.h"

void printIntro()
{
	printf("#######################################################\n");
	printf("#                                                     #\n");
	printf("#                   SIMULADOR 8086                    #\n");
	printf("#                                                     #\n");
	printf("#  .Jeferson Amend                                    #\n");
	printf("#  .Pedro Yamada Bondal                               #\n");
	printf("#  .Thiago Leite Ribeiro                              #\n");
	printf("#                                                     #\n");
	printf("#  ~ 2o ano - Ciencia da Computacao - PUCPR - 2007 ~  #\n");
	printf("#                                                     #\n");
	printf("#   Professor: Altair Olivo Santin                    #\n");
	printf("#                                                     #\n");
	printf("#######################################################\n");
}

int AnalisaArquivo()
{
	FILE *f;
	char FileName[30], tmp[30], copy[250], del[150], path[200];
	int i, x;

	printIntro();

	printf("\nInsira o nome do arquivo-fonte: ");
	scanf("%s", FileName);
	printf("\nInsira o caminho do arquivo: ");
	scanf("%s",path);
	strcpy(tmp, FileName);

	x = strlen(tmp);
	for(i = 0; i < x; i++)
	{
		if(tmp[i] == '.')
		{
			tmp[i+1] = 't';
			tmp[i+2] = 'x';
			tmp[i+3] = 't';
			tmp[i+4] = '\0';
			break;
		}
	}
	
	sprintf(copy, "copy %s\\%s %s", path, FileName, tmp);
	sprintf(del, "del %s", tmp);
	system(del);
	system(copy);
	system("cls");

	printIntro();

	f = fopen(tmp, "r");
	if(f == NULL)
	{
		printf("\nErro na abertura do arquivo, execucao abortada.\n\n");
		system("pause");
		return 0;
	}
	else
		printf("\nArquivo aberto com sucesso.\n");

	AnalisaErros(f);
	if(OK == 1)
	{
		rewind(f);
		AnalisaVLD(f);
		rewind(f);
		PreencheTabelaOpcodes();
		AnalisaInstrucao(f);
	}
	else
	{
		printf("O arquivo fonte possui erros, execucao abortada.\n\n");
		system("pause");
		return 0;
	}

	printf("\n");
//	system("PAUSE");
	fclose(f);
	system(del);
	return 1;
}
