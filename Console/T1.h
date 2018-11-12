#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit() function
#include <time.h>

//declarando as funcoes
void menuPrincipal(void);
void menuPecas(void);
void escreverAssentos(char[]);
int converter(char[], int);
void selecionarSessao(char[]);
//Caminho relativo
const char* filePath = "../";
//Criar variaveis globais data, hora, nome da peca e numero do assento
enum week{Segunda = 1, Terca, Quarta, Quinta, Sexta, Sabado, Domingo};
int meiaEntrada;
char horaTicket[1000];
int valorTicket;
char nomeDaPeca[1000];

//Esse e o menu principal do programa com todas as opcoes disponiveis
void menuPrincipal()
{
	//Opcao escolhida pelo usuario
	int opcao;
	
	printf("\nBem Vindo! Selecione uma op��o: \n");
	printf("1 - Comprar Ingresso\n");
	printf("2 - Fechar Caixa\n");
	printf("3 - Sair\n\n");
	scanf("%d", &opcao);
	//Condicional do menu principal
	while(opcao != 3 && opcao != 1 && opcao != 2)
	{
		printf("Op��o invalida! Digite novamente: \n");
		scanf("%d", &opcao);
	}
	//Pode trocar o if por um switch
	//Menu principal, passar para uma rotina, vai poder voltar nele
	if(opcao == 3)
	{
		exit(1);
	}
	else if(opcao == 1)
	{
		//Chamar rotina de compra de ingresso
		tipoUsuario();		
	}
	else if(opcao == 2)
	{
		//chamar rotina para fechar o caixa
	}
}
/*Rotina para escolher o tipo de usuario*/
void tipoUsuario()
{
	//Opcao escolhida pelo usuario
	int usuario;
	
	printf("\nEscolha o tipo de usu�rio: \n");
	printf("1 - Estudante\n");
	printf("2 - Crian�a de 02 a 12 anos\n");
	printf("3 - Adulto com idade igual ou superior a 60 anos\n");
	printf("4 - Professor da rede publica\n");
	printf("5 - Outro\n");
	
	//Como saber qual o dia atual
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int dia = dayofweek(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	
	if(dia == Terca)
	{
		printf("6 - Estudante de baixa renda da rede p�blica\n");
	}
	printf("\n");

	scanf("%d", &usuario);
	//Condicional do menu principal
	while(usuario != 3 && usuario != 1 && usuario != 2 && usuario != 4 && usuario != 5 && usuario!=6)
	{
		printf("Op��o invalida! Digite novamente: \n");
		scanf("%d", &usuario);
	}
	//Pode trocar o if por um switch
	//Menu principal, passar para uma rotina, vai poder voltar nele
	switch(usuario)
	{
		case 1: case 2: case 3: case 4:
			meiaEntrada = 1;
			break;
		
		case 5:
			meiaEntrada = 0;
			break;
		
		case 6:
			meiaEntrada = 2;
			break;
	}
	
	menuPecas();
}
/*Rotina que faz o gerenciamento da compra do ingresso, lendo os arquivos com as informacoes
No arquivo principal tem as informacoes das pecas em cartaz
Ao selecionar a peca tem que fazer a leitura do arquivo com a informacao sobre as sessoes disponiveis para a peca selecionada
Apos selecionar a sessao faz-se a leitura do arquivo com as informacoes dos assentos
Pode-se voltar ao menu anterior digitando 0
*/
void menuPecas()
{
    int quantidadeTeatral;
    int sessao;
    int peca = 0;
    FILE *fptr;
	char *sessoes[1000];
	char *nome[1000];
	
    if ((fptr = fopen("../test.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }

    // reads text until newline 
    fscanf(fptr,"%d", &quantidadeTeatral);
    //Percorre as pe�as teatrais para pegar as informa��es de cada uma
    printf("Escolha uma peca de teatro : \n\n");
     for (peca = 0; peca < quantidadeTeatral; peca++)
    {
    	nome[peca] = malloc(sizeof(char) * 1024)	;
	    sessoes[peca] = malloc(sizeof(char) * 1024);
	    fscanf(fptr,"%s %s", nome[peca], sessoes[peca]);
    	//Faz um replace na string
    	size_t tamanho = 0;
    	tamanho = strlen(nome[peca]);
    	int replace = 0;
    	for(replace = 0; replace < tamanho; replace++)
		{
    		if(nome[peca][replace] == '-')
    		{
    			nome[peca][replace] = ' ';
			}
		}
    	printf("%d - %s\n", peca+1, nome[peca]);
    }

    fclose(fptr);
    printf("0 - Voltar\n");
    scanf("%d", &sessao);
    
    while(sessao < 0 || sessao > quantidadeTeatral)
	{
		printf("Op��o invalida! Digite novamente: \n");
		scanf("%d", &sessao);
	}
	if(sessao == 0)
	{
		menuPrincipal();
	}
	else
	{
		sprintf(nomeDaPeca, nome[sessao-1]);
		char str1[50];
	    char str2[50];
	    char cat[100];
	
	    sprintf(str1,filePath);
	    sprintf(str2,sessoes[sessao-1]);
	    sprintf(cat,"%s%s",str1, str2);
		//Rotina para selecionar as sessoes	 
	    selecionarSessao(cat);	    
	}
}

void selecionarSessao(char sessio[])
{

	FILE *fptr;
	/*Abrir arquivo das informacoes das sessoes da peca escolhida*/
	 if ((fptr = fopen(sessio, "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }
    int quantidadeSessoes;
    char *hora[1000];
    char *cadeiras[1000];
    fscanf(fptr,"%d", &quantidadeSessoes);
    int valor[quantidadeSessoes];
    printf("Selecione uma sessao:\n");
    
    int aux;
    for(aux = 0; aux < quantidadeSessoes; aux++)
    {
    	cadeiras[aux] = malloc(sizeof(char) * 1024);
    	hora[aux] = malloc(sizeof(char) * 1024);
		fscanf(fptr,"%s %s %d", hora[aux], cadeiras[aux], &valor[aux]);
		//Separar a data em dia, mes e ano e descobrir qual o dia da semana	    	
    	printf("%d - Hora: %s\n", aux+1,hora[aux]);
	}
	printf("0 - Voltar\n\n");
	fclose(fptr);
	int sessaoEscolhida;
	scanf("%d", &sessaoEscolhida);
	//Validar entrada do Usuario
	 while(sessaoEscolhida < 0 || sessaoEscolhida > quantidadeSessoes)
	{
		printf("Op��o invalida! Digite novamente: \n");
		scanf("%d", &sessaoEscolhida);
	}
	if(sessaoEscolhida == 0)
	{
		menuPecas();
	}
	else
	{
		sprintf(horaTicket,hora[sessaoEscolhida-1]);
		valorTicket = valor[sessaoEscolhida-1];
		escreverAssentos(cadeiras[sessaoEscolhida-1]);    
	}
	
}
	
void escreverAssentos(char arquivo[])
{
	char str1[50];
	char str2[50];
	char cat[100];
	
	sprintf(str1,filePath);
	sprintf(str2,arquivo);
	sprintf(cat,"%s%s",str1, str2);
	
	FILE *fptr;
	if ((fptr = fopen(cat, "r+")) == NULL)
	{
	    printf("Error! opening file");
	    // Program exits if file pointer returns NULL.
	    exit(1);         
	}
	printf("Selecione um assento: \n\n");
	
	int fileiras, colunas;
	fscanf(fptr,"%d %d", &fileiras, &colunas);
	int linha, cadeira;
	int assentos[fileiras][colunas];
	int teste;
	char helper;
	int assentosDisponiveis = 0;
	//Contar quantos assentos disponiveis tem
	//Se n�o houver assento disponivel, avisar o usu�rio e
	//voltar para o menu anterior e selecionar outra sess�o
	for(linha = 0; linha < fileiras; linha ++)
	{
		for(cadeira = 0; cadeira < colunas; cadeira++)
		{
			fscanf(fptr,"%d", &teste);
			assentos[linha][cadeira] = teste;
			
			if(teste == 0)
			{
				assentosDisponiveis ++;
			}
			
			helper = 'A' + linha;
			printf("%c%d ", helper,cadeira+1);
		}
		printf("\n");
	}
	printf("\n0 - Voltar\n\n");
	
	if(assentosDisponiveis == 0)
	{
		//Voltar a sele��o de sessao
		printf("Nao existe assentos disponiveis para essa sessao. Por favor escolha outra sessao: \n\n");
		menuPecas();
	}
	else
	{
		//Oferecer op��o de ir para a home
		char assentoEscolhido[2];
		printf("\n");
		scanf("%s", assentoEscolhido);
	
		if(assentoEscolhido[0] == '0')
		{
			//Voltar ao menu anterior -- working on it!
			menuPecas();
		}
		else
		{
			int row, column;
			row = converter(assentoEscolhido, 0);
			column = converter(assentoEscolhido, 1);
		
			int t = 0;
				
			while(t == 0)
			{
				if(row+1 < 1 || row+1 > fileiras || column < 1 || column > cadeira)
				{
					printf("Assento inv�lido! Digite novamente: \n");
					scanf("%s", assentoEscolhido);
					row = converter(assentoEscolhido, 0);
					column = converter(assentoEscolhido, 1);
				}
				//Verifica se o assento esta disponivel
				else if (assentos[row][column-1]==1)
				{
					printf("Assento indispon�vel! Por favor escolha outro assento: \n");
					scanf("%s", assentoEscolhido);
					row = converter(assentoEscolhido, 0);
					column = converter(assentoEscolhido, 1);	
				}
				else
				{
					assentos[row][column-1] = 1;
					t=1;
				}
			}
			
			//Atualizar o arquivo de assentos
			//Volta para o come�o do arquivo
			fseek(fptr, 0, SEEK_SET);
			fprintf(fptr, "%d ", fileiras);
			fprintf(fptr, "%d", colunas);
			
			//Percorre a matriz e escreve no arquivo, atualizando os assentos
			for(linha = 0; linha < fileiras; linha ++)
		    {
		    	//Proxima linha
		    	fprintf(fptr, "%c", '\n');
		    	for(cadeira = 0; cadeira < colunas; cadeira++)
		    	{
		    		fprintf(fptr, "%d ", assentos[linha][cadeira]);
				}
			}
			
			//Selecionar o valor do ingresso (o programa n�o ir� validar)
			//Decidir se os pre�os irao variar por pe�a de teatro, se sim montar um array de struct do tipo pre�o, ou um array
		}
	
	}
	fclose(fptr);
	
	printf("Selecione o tipo de ingresso:\n\n");
	printf("1 - Inteira\n");
	printf("2 - Meia\n");
	printf("3 - Terca aluno escola publica \n");
	int tipoIngresso;
	scanf("%d", &tipoIngresso);
}
		
int converter(char t[], int linha)
{
	if(linha == 0)
		return t[0] - 'A';
	else if(linha == 1)
		return t[1] - '0';
}

int dayofweek(int d, int m, int y) 
{ 
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; 
    y -= m < 3; 
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7; 
} 



