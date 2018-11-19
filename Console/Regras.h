#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit() function
#include <time.h>

//declarando as funcoes
void menuPrincipal(void);
void menuPecas(void);
void escreverAssentos(char[]);
int converter(char[], int);
void substituirEspaco(char[]);
void selecionarSessao(char[]);
void tipoUsuario(void);
void fecharCaixa(void);
//Caminho relativo
const char* filePath = "../";
//Caminho para o arquivo das pecas disponiveis
const char* arquivoPecas = "../test.txt";
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
	
	printf("\nBem Vindo! Selecione uma opção: \n");
	printf("1 - Comprar Ingresso\n");
	printf("2 - Fechar Caixa\n");
	printf("3 - Sair\n\n");
	scanf("%d", &opcao);
	//Condicional do menu principal
	while(opcao != 3 && opcao != 1 && opcao != 2)
	{
		printf("Opção invalida! Digite novamente: \n");
		scanf("%d", &opcao);
	}
	//Menu principal, se digitar 3 entao sai do programa
	if(opcao == 3)
	{
		exit(1);
	}
	//Se digitar um entao vai para a escolha do tipo de cliente
	else if(opcao == 1)
	{
		//Chamar rotina de tipo de usuario
		tipoUsuario();		
	}
	//Opcao para fechar o caixa
	else if(opcao == 2)
	{
		//chamar rotina para fechar o caixa
		fecharCaixa();
	}
}
/*Rotina para escolher o tipo de usuario*/
void tipoUsuario()
{
	//Opcao escolhida pelo usuario
	int usuario;
	
	printf("\nEscolha o tipo de usuário: \n");
	printf("1 - Estudante\n");
	printf("2 - Criança de 02 a 12 anos\n");
	printf("3 - Adulto com idade igual ou superior a 60 anos\n");
	printf("4 - Professor da rede publica\n");
	printf("5 - Outro\n");
	
	//Como saber qual o dia atual
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	//Calcula o dia da semana dado o dia, mes e ano
	int dia = dayofweek(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	//Se o dia da semana for terca entao exibe mais uma opcao para o usuario
	if(dia == Terca)
	{
		printf("6 - Estudante de baixa renda da rede pública\n");
	}
	printf("\n");
	//Le o que o usuario digitou
	scanf("%d", &usuario);
	//Verifica se a opcao que o usuario digitou e valida
	while(usuario != 3 && usuario != 1 && usuario != 2 && usuario != 4 && usuario != 5 && usuario!=6)
	{
		//Se a opcao for invalida pede para o usuario digitar novamente a opcao, ate que ela seja valida
		printf("Opção invalida! Digite novamente: \n");
		scanf("%d", &usuario);
	}

	//Grava o tipo de entrada na variavel global
	switch(usuario)
	{
		//Se o usuario escolher 1,2,3 ou 4 entao sera meia entra
		case 1: case 2: case 3: case 4:
			meiaEntrada = 1;
			break;
		//Se o usuario escolher 0 entao pagara o valor total(inteira)
		case 5:
			meiaEntrada = 0;
			break;
		//Se for a opcao 6 entao nao pagara entrada
		case 6:
			meiaEntrada = 2;
			break;
	}
	//Vai para o proximo menu
	menuPecas();
}
/*Rotina que faz o gerenciamento da compra do ingresso, lendo os arquivos com as informacoes
No arquivo principal tem as informacoes das pecas em cartaz
Ao selecionar a peca tem que fazer a leitura do arquivo com a informacao sobre as sessoes disponiveis para a peca selecionada
Apos selecionar a sessao faz-se a leitura do arquivo com as informacoes dos assentos
Pode-se voltar ao menu principal digitando 0
*/
void menuPecas()
{
	//Quantidade de pecas em cartaz
    int quantidadeTeatral;
    //Variavel para captar opcao escolhida pelo usuario
    int sessao;
    //Variavel de controle para o loop FOR
    int peca = 0;
    //Arquivo com as pecas disponiveis
    FILE *fptr;
    //Variavel para armazenar o nome dos arquivos com as sessoes de cada peca
	char *sessoes[1000];
	//Variavel para armazenar o nome de todas as pecas contidas no arquivo
	char *nome[1000];
	//Faz a abetura do arquivo das pecas disponiveis
    if ((fptr = fopen(arquivoPecas, "r")) == NULL)
    {
    	//Se o arquivo nao existir ou nao puder ser aberto o sistema sera fechado
        printf("Error! opening file");
        exit(1);         
    }

    //Le a primeira linha do texto do arquivo e grava na variavel
    fscanf(fptr,"%d", &quantidadeTeatral);
    //Percorre as peças teatrais para pegar as informações de cada uma
    printf("Escolha uma peca de teatro : \n\n");
     for (peca = 0; peca < quantidadeTeatral; peca++)
    {
    	//Array dinamico para armazenar o nome das pecas
    	nome[peca] = malloc(sizeof(char) * 1024);
    	//Array dinamico para armazenar o nome dos arquivos das sessoes de cada peca
	    sessoes[peca] = malloc(sizeof(char) * 1024);
	    //Faz leitura do nome e do arquivo com as pecas contidas no arquivo
	    fscanf(fptr,"%s %s", nome[peca], sessoes[peca]);
    	//Faz um replace na string
    	substituirEspaco(nome[peca]);
    	printf("%d - %s\n", peca+1, nome[peca]);
    }
	//Fecha o arquivo com as pecas
    fclose(fptr);
    printf("0 - Voltar para o menu principal\n");
    //Faz leitura da opcao digitada pelo usuario
    scanf("%d", &sessao);
    //Verifica se a opcao digitada e valida
    while(sessao < 0 || sessao > quantidadeTeatral)
	{
		//Enquanto a opcao for invalida, pede para o usuario digitar novamente
		printf("Opção invalida! Digite novamente: \n");
		scanf("%d", &sessao);
	}
	//Se a opcao digitada for igual a zero, o sistema volta ao menu principal
	if(sessao == 0)
	{
		menuPrincipal();
	}
	//se a opcao selecionada for de uma das pecas
	else
	{
		//Grava o nome da peca na variavel global
		sprintf(nomeDaPeca, nome[sessao-1]);
		//Fazer concatenacao para montar o nome do arquivo com seu respectivo caminho
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
    //Variavel para armazenar a quantidade de sessoes armazenadas no arquivo
    int quantidadeSessoes;
    //Array dinamico para armazenar a hora de todas as sessoes contidas no arquivo
    char *hora[1000];
    //Array dinamico para armazenar o nome do arquivo com os assentos de cada sessao
    char *cadeiras[1000];
    //Faz leitura da quantidade de sessoes armazenadas no arquivo
    fscanf(fptr,"%d", &quantidadeSessoes);
    //Array para armqzenar o valor de cada sessao
    int valor[quantidadeSessoes];
    printf("Selecione uma sessao:\n");
    //Variavel auxiliar para o loop
    int aux;
    for(aux = 0; aux < quantidadeSessoes; aux++)
    {
    	cadeiras[aux] = malloc(sizeof(char) * 1024);
    	hora[aux] = malloc(sizeof(char) * 1024);
		fscanf(fptr,"%s %s %d", hora[aux], cadeiras[aux], &valor[aux]);   	
    	printf("%d - Hora: %s\n", aux+1,hora[aux]);
	}
	printf("0 - Voltar para o menu principal\n\n");
	//Fechar o arquivo com as sessoes
	fclose(fptr);
	int sessaoEscolhida;
	scanf("%d", &sessaoEscolhida);
	//Validar entrada do Usuario
	 while(sessaoEscolhida < 0 || sessaoEscolhida > quantidadeSessoes)
	{
		printf("Opção invalida! Digite novamente: \n");
		scanf("%d", &sessaoEscolhida);
	}
	if(sessaoEscolhida == 0)
	{
		menuPrincipal();
	}
	else
	{	
		//Grava a hora da sessao na variavel global	
		sprintf(horaTicket,hora[sessaoEscolhida-1]);
		//Grava o valor da peca para a sessao escolhida na variavel global
		valorTicket = valor[sessaoEscolhida-1];
		//Vai para o proximo passo da compra de ingressos
		escreverAssentos(cadeiras[sessaoEscolhida-1]);    
	}
	
}
	
void escreverAssentos(char arquivo[])
{
	//Variaveis para montar o caminho do arquivo a ser lido
	char str1[50];
	char str2[50];
	char cat[100];
	//Poltrona selecionada pelo usuario
	char assentoEscolhido[2];
	
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
	//Variaveis para armazenar a quantidade de filas e colunas disponiveis no teatro
	int fileiras, colunas;
	//Faz a leitura no arquivo das filas e colunas
	fscanf(fptr,"%d %d", &fileiras, &colunas);
	//Variaveis auxiliares para o loop
	int linha, cadeira;
	//Array multidimensional para armazenar as poltronas
	int assentos[fileiras][colunas];
	//Variavel para armazenar 0 ou 1 no array de poltronas...
	//Se teste or igual a 1 entao a poltrona esta ocupada, se for igual a zero entao esta desocupada
	int teste;
	//Variavel para ajudar a transformar o numero da fileira em letra
	char helper;
	//Variavel para verificar a quantidade de assentos disponiveis
	int assentosDisponiveis = 0;
	//Contar quantos assentos disponiveis tem
	//Se não houver assento disponivel, avisar o usuário e
	//voltar para o menu de selecao de pacas para selecionar uma outra peca ou sessao
	for(linha = 0; linha < fileiras; linha ++)
	{
		for(cadeira = 0; cadeira < colunas; cadeira++)
		{
			//Le o valor de cada poltrona no arquivo
			fscanf(fptr,"%d", &teste);
			assentos[linha][cadeira] = teste;
			//Se a poltrona estiver marcada com 0 significa que esta disponivel
			if(teste == 0)
			{
				assentosDisponiveis ++;
			}
			//Ao somar o numero da linha com o caracter A temos a conversao do numero em letra alfabetica
			helper = 'A' + linha;
			printf("%c%d ", helper,cadeira+1);
		}
		printf("\n");
	}
	printf("\n0 - Voltar ao menu principal\n\n");
	//Se nao houver assentos disponiveis avisar o usuario e voltar a selecao das pecas
	if(assentosDisponiveis == 0)
	{
		//Voltar a seleção das pecas
		printf("Nao existe assentos disponiveis para essa sessao. Por favor escolha outra sessao: \n\n");
		menuPecas();
	}
	else
	{
		//Oferecer opção de ir para a home
		printf("\n");
		scanf("%s", assentoEscolhido);
	
		if(assentoEscolhido[0] == '0')
		{
			//Voltar ao menu principal
			menuPrincipal();
		}
		else
		{
			//Se houver assentos disponiveis verifica se o assento e valido
			//Variaveis para armazenar a conversao de char para int do assento escolhido pelo usuario
			int row, column;
			//Faz a conversao de char para int
			row = converter(assentoEscolhido, 0);
			column = converter(assentoEscolhido, 1);
			//Variavel auxiliar para o loop while
			int t = 0;
			//Enquanto t for igual a zero o loop continuara	
			while(t == 0)
			{
				//Se o assento nao for valido entao o usuario tera que digitar novamente o assento desejado
				if(row+1 < 1 || row+1 > fileiras || column < 1 || column > cadeira)
				{
					printf("Assento inválido! Digite novamente: \n");
					scanf("%s", assentoEscolhido);
					row = converter(assentoEscolhido, 0);
					column = converter(assentoEscolhido, 1);
				}
				//Verifica se o assento esta disponivel, se estiver indisponivel pede para digitar novamente
				else if (assentos[row][column-1]==1)
				{
					printf("Assento indisponível! Por favor escolha outro assento: \n");
					scanf("%s", assentoEscolhido);
					row = converter(assentoEscolhido, 0);
					column = converter(assentoEscolhido, 1);	
				}
				//Se finalmente o usuario digitar um assento valido o loop sera finalizado
				else
				{
					assentos[row][column-1] = 1;
					t=1;
				}
			}
			
			//Atualizar o arquivo de assentos
			//Volta para o começo do arquivo
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
		    		//Escreve no arquivo de assentos, atualizando-o
		    		fprintf(fptr, "%d ", assentos[linha][cadeira]);
				}
			}
		
		}
	
	}
	fclose(fptr);
	//Gravar em arquivo o ticket comprado com data, hora, nome da peca e valor
	//Verificar se o arquivo existe, se nao existir criar
	//Variavel para armazenar a quantidade de ingressos vendidas
	int numberOfTickets;
	int lerTickets;	
	fptr = fopen("../tickets.txt", "r+");
	if (fptr==NULL)
	{
	    fptr = fopen("../tickets.txt", "w");
		numberOfTickets = 0;        
	}
	else
	{
		fscanf(fptr,"%d", &numberOfTickets);
	}
	//Data atual para gravar a data do dia que o ingresso foi comprado
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char data[1000];
	//Variavel para armazenar o nome da peca trocando os espacos por -
	char nomePecaSemEspaco[1000];
	sprintf(data,"%d/%d/%d",tm.tm_mday,tm.tm_mon + 1, tm.tm_year + 1900);
	//Substituir o espaco em branco por travessao
	size_t tamanho = 0;
	tamanho = strlen(nomeDaPeca);
	int replace = 0;
	sprintf(nomePecaSemEspaco, nomeDaPeca);
	for(replace = 0; replace < tamanho; replace++)
	{
		if(nomePecaSemEspaco[replace] == ' ')
		{
			nomePecaSemEspaco[replace] = '-';
		}
	}
	//Gravar o primeiro ticket comprado
	if(numberOfTickets == 0)
	{
		fprintf(fptr, "%d", 1);
		fprintf(fptr, "%c", '\n');
		fprintf(fptr, "%s %s %s %d", data, horaTicket, nomePecaSemEspaco, calcularValorTicket(meiaEntrada, valorTicket));
		fprintf(fptr, "%c", '\n');
	}
	//Se ja tiver arquivo gravado entao atualizar o contador de ingressos e 
	//adicionar o ingresso no final do arquivo
	else
	{
		numberOfTickets++;
		fseek(fptr, 0, SEEK_SET);
		fprintf(fptr, "%d", numberOfTickets);
		fseek(fptr, -1, SEEK_END);
		fprintf(fptr, "%c", '\n');
		fprintf(fptr, "%s %s %s %d", data, horaTicket, nomePecaSemEspaco, calcularValorTicket(meiaEntrada, valorTicket));
		fprintf(fptr, "%c", '\n');
	}
	fclose(fptr);
	/*Mostra o Ingresso na tela finalizando a compra
	com data, hora, nome da peca e numero de poltrona*/
	printf("\nIngresso\n");
	printf("Data: %s\n", data);
	printf("Horário: %s\n", horaTicket);
	printf("Peça: %s\n", nomeDaPeca);
	printf("Poltrona: %s\n", assentoEscolhido);
	printf("\nDigite 0 para voltar ao menu principal\n");
	//Verifica se o usuario que voltar ao menuprincipal ou sair do programa
	//Para sair do programa e so digitar qualquer coisa diferente de 0
	int voltar;
	scanf("%d", &voltar);
	if(voltar == 0)
	{
		//Volta ao inicio
		menuPrincipal();
	}
	else
	{
		//Sai do programa
		exit(1);
	}
}
//Rotina para converter char em int
//A variavel linha e para identificar se esta convertendo a linha ou a coluna 
//Se linha for igual a 0 significa que o caracter a ser convertido sera uma letra do alfabeto
//Se linha for igual a 1 significa que ira converter um caracter numerico em int		
int converter(char t[], int linha)
{
	if(linha == 0)
		return t[0] - 'A';
	else if(linha == 1)
		return t[1] - '0';
}
//Calcula o valor final do ticket verificando o tipo de usuario
int calcularValorTicket(int tipoEntrada, int valor)
{
	switch(tipoEntrada)
	{
		//Inteira
		case 0:
			return valor;
			break;
		//Meia entrada	
		case 1:
			return valor * 0.5;
			break;
		//Tercas livre aos alunos de escola publica carentes	
		case 2:
			return 0;
			break;
	}
}
//Calcula o dia da semana do d- dia, m - mes e y - ano informados
/*O retorno e numerico, sendo
1 - Segunda
2 - Teca
3 - Quarta
4 - Quinta
5 - Sexta
6 - Sabado
7 - Domingo
*/
int dayofweek(int d, int m, int y) 
{ 
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; 
    y -= m < 3; 
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7; 
} 
//Troca espaco por travessao de uma string
void substituirEspaco(char texto[])
{
	size_t tamanho = 0;
	tamanho = strlen(texto);
	int replace = 0;
	for(replace = 0; replace < tamanho; replace++)
	{
		if(texto[replace] == '-')
		{
			texto[replace] = ' ';
		}
	}
}
//Rotina para fechamento do caixa
void fecharCaixa()
{
	//Abrir arquivo com os tickets vendidos
	FILE *fptr;
	if ((fptr = fopen("../tickets.txt", "r+")) == NULL)
	{
	    printf("Error! opening file");
	    // Program exits if file pointer returns NULL.
	    exit(1);         
	}
	int totalTickets;
	fscanf(fptr,"%d", &totalTickets);
	int ticket;
	int saldoTotal = 0;
	char data[100];
	char horario[100];
	char nome[1000];
	int valor;
	printf("\n.:.:.Movimentações.:.:.\n");
	//Percorrer os tickets vendidos
	for(ticket = 0; ticket < totalTickets; ticket++)
	{
		fscanf(fptr, "%s %s %s %d", data, horario, nome, &valor);
		substituirEspaco(nome);
		printf("%s %s %s %d\n", data, horario, nome, valor);
		//Soma os valores dos ingressos para apresentar o saldo total do dia
		saldoTotal += valor;
	}
	printf("SALDO TOTAL: %d\n", saldoTotal);
	fclose(fptr); 
	printf("\nDigite 0 para voltar ao menu principal\n");
	int voltar;
	scanf("%d", &voltar);
	if(voltar == 0)
	{
		menuPrincipal();
	}
	else
	{
		exit(1);
	}

}

