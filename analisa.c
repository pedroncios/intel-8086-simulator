// AnalisaErro: tratar virgula.. 
// AnalisaVLD: arrumar contLocacao
// AnalisaInstrucao: mudar todos opcodes para hexa e arrumar endereçamento
// Deletar .txt após endereçamento? Pq é inutil


#include "montador.h"

char *Diretivas[] = { "db","dw", "equ", "proc", "endp", "hlt" }; //Keyword
char *Mnemonicos[] = {"mov","add","sub","div","mul","idiv","imul","and","or","xor","not","cmp","jmp","je","jne","jg","jge","jl","jle","ja","jae","jb","jbe","call","ret" };
char *Byte[] = { "al","bl","ah","bh" };
char *Word[] = { "ax","bx", "sp", "ip" };


/******************************************************************
							Funções
*******************************************************************/

void Enderecamento(char *p)
{
	if(IsMnemonico(p) != -1)
	{
		ContLocacao += 3;
		return;
	}

	p = strtok(NULL,"()[]{}<>?!\\; ,.-+'_*#@&$\n\t");
	if(strcmpi(p, "db") == 0)
	{
		ContLocacao += 1;
		return;
	}

	if(strcmpi(p, "dw") == 0)
	{
		ContLocacao += 2;
		return;
	}
	
	if(strcmpi(p, "equ") == 0)
	{
//		ContLocacao += 3;
		return;
	}

	if(strcmpi(p, "endp") == 0 || strcmpi(p, "proc") == 0)
		return;

	printf("Erro no enderecamento!\n");
}

char *TrataVirgula(char *p)
{
	int i, j, aux;
	char *newp = p;

	// Se está tudo OK
	if(strlen(p) == 2)
	{
		if( IsRegistrador8(p) != -1 || IsRegistrador16(p) != -1)
			return p;
	}
	// Retorna a string sem ','
	if(p[strlen(p) - 1] == ',')
	{
		aux = strlen(p) - 1;
		for(i=0; i < aux; i++)
			newp[i] = p[i];
		newp[aux] = '\0';
		return newp;
	}

	if(strlen(p) != 1 && p[0] == ',')
	{
		j=0;
		aux = strlen(p);
		for(i=1; i < aux; i++)
		{
			newp[j] = p[i];
			j++;
		}
		newp[j] = '\0';
		return newp;
	}

	printf("Erro na instrucao %s ou o final dela %c\n", p, p[strlen(p) - 1]);

	return p;
}

int VirgulaMid(char *p)
{
	int i, x;
	// strlen() - 2 pq -1 é tratado na outra funcao TrataVirgula
	x = (strlen(p)-2);
	for(i=0; i < x; i++)
	{
		if(p[i] == ',')
			return 1;
	}
	return 0;
}

int TemVirgula(char *p)
{
	int i, x;
	x = strlen(p);
	for(i=0; i < x; i++)
	{
		if(p[i] == ',')
			return 1;
	}
	return 0;
}

int IsDiretiva(char *p)
{
	int i;
	for(i=0;i<7;i++)
		if(strcmpi(p,Diretivas[i]) == 0)
			return i;
	return -1;
}

int IsRegistrador8(char *p)
{
	int i;
	for(i=0;i<4;i++)
		if(strcmpi(p,Byte[i]) == 0)
			return i;
	return -1;
}

int IsRegistrador16(char *p)
{
	int i;
	for(i=0;i<4;i++)
		if(strcmpi(p,Word[i]) == 0)
			return i;
	return -1;
}

int IsMnemonico(char *p)
{
	int i;
	for(i=0;i<25;i++)
		if(strcmpi(p,Mnemonicos[i]) == 0)
			return i;
	return -1;
}

int IsImediato(char *p)
{
	int i=0;

	while(p[i] != ' ')
	{
		if(p[i] > 47 && p[i] < 58)
		{
			i++;
			// 10 == ASCII de ' ' e 0 == ASCII ''
			if(p[i] == 10 || p[i] == 0)
				return 1;
			else
				continue;
		}
		else 
			return 0;
	}
	return 0;
}

int IsVariavel(int cont, char *p)
{
	int i;

	for(i=0; i<cont; i++)
	{
		if(strcmpi(var[i].nome, p) == 0)
			return i;
	}
	return -1;
}

int IsBinario(char *p)
{
	int i, aux;

	// no fim da string tem 'b', ex: 10011001b
	if(p[strlen(p) - 1] == 'b')
	{
		// testa todos os numeros se é 0 ou 1
		aux = strlen(p) - 1;
		for(i=0; i < aux; i++)
		{
			if( p[i] == '1' || p[i] == '0' )
				continue;
			else
				// se achar qualquer erro retorna 0
				return 0;
		}
		// se estiver tudo ok, retorna verdadeiro
		return 1;
	}
	else
		return 0;
}

void PreencheTabelaOpcodes()
{
	char line[20], *word;
	int i = 0;
	FILE *op = fopen("opcodesTable.txt","r");

	while(!feof(op))
	{
		fgets(line,20,op);
		word = strtok(line," \n\t");
		strcpy(tabelaInst[i].mnemonico,word);
		word = strtok(NULL," \n\t");
		tabelaInst[i].opcode = str2int(word);
		i++;
	}
	fclose(op);
}

int getOpcode(char *m)
{
	int i;
	for(i=0;i<150;i++)
	{
		if(strcmpi(tabelaInst[i].mnemonico,m)==0)
			return i;
	}
	return -1;
}

int recuperaVLD(char *op)
{
	int i;
	for(i=0;i<100;i++)
	{
		if(strcmpi(tabelaVLD[i].nome,op)==0)
			return i;
	}
	return -1;
}

int recuperaReg(char *reg)
{
	int i;
	for(i=0;i<8;i++)
	{
		if(strcmpi(tabelaREG[i].nome,reg)==0)
			return i;
	}
	return -1;
}

int bin2int(char *b)
{
	int x = 128;
	int r = 0;
	int i = 0;
	char tmp = b[i];
	while(tmp != 'b')
	{
		tmp = b[i];
		if(tmp == '1')
			r = r+x;
		i++;
		x = x/2;
	}
	return r;
}

int str2int(char *word)
{
	int valor = 0;
	int tam = strlen(word) - 1;
	int m = 1;

	if(IsImediato(word))
	{	
		while(tam >= 0)
		{
			valor = valor + (word[tam] - '0') * m;
			m = m * 10;
			tam--;
		}
		return valor;		
	}
	else
	{
		printf("\n\nErro: passada de string nao valida para funcao de conversao STR2INT\n\n");
		return -1;
	}
}