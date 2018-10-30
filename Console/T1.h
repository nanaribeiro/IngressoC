#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit() function

//declarando as funcoes
void menuPrincipal(void);
void menuPecas(void);
void escreverAssentos(char[]);
int converter(char[], int);

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
	//Pode trocar o if por um switch
	//Menu principal, passar para uma rotina, vai poder voltar nele
	if(opcao == 3)
	{
		exit(1);
	}
	else if(opcao == 1)
	{
		//Chamar rotina de compra de ingresso
		menuPecas();		
	}
	else if(opcao == 2)
	{
		//chamar rotina para fechar o caixa
	}
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
	
    if ((fptr = fopen("D:\\PIM4\\test.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }

    // reads text until newline 
    fscanf(fptr,"%d", &quantidadeTeatral);
    //Percorre as peças teatrais para pegar as informações de cada uma
    printf("Escolha uma peca de teatro : \n\n");
     for (peca = 0; peca < quantidadeTeatral; peca++)
    {
    	char nome[1000];
	    sessoes[peca] = malloc(quantidadeTeatral);
    	fscanf(fptr,"%s %s", nome, sessoes[peca]);
    	//Faz um replace na string
    	size_t tamanho = 0;
    	tamanho = strlen(nome);
    	int replace = 0;
    	for(replace = 0; replace < tamanho; replace++)
		{
    		if(nome[replace] == '-')
    		{
    			nome[replace] = ' ';
			}
		}
    	printf("%d - %s\n", peca+1, nome);
    }

    fclose(fptr);
    printf("0 - Voltar\n");
    scanf("%d", &sessao);
    
    while(sessao < 0 || sessao > quantidadeTeatral)
	{
		printf("Opção invalida! Digite novamente: \n");
		scanf("%d", &sessao);
	}
	if(sessao == 0)
	{
		menuPrincipal();
	}
	else
	{
		char str1[50];
	    char str2[50];
	    char cat[100];
	
	    sprintf(str1,"D:\\PIM4\\");
	    sprintf(str2,sessoes[sessao-1]);
	    sprintf(cat,"%s%s",str1, str2);

		 /*Abrir arquivo das informacoes das sessoes da peca escolhida*/
		 if ((fptr = fopen(cat, "r")) == NULL)
	    {
	        printf("Error! opening file");
	        // Program exits if file pointer returns NULL.
	        exit(1);         
	    }
	    int quantidadeSessoes;
	    char data[100];
	    char hora[100];
	    char *cadeiras[1000];
	    fscanf(fptr,"%d", &quantidadeSessoes);
	    
	    printf("Selecione uma sessao:\n");
	    
	    int aux;
	    for(aux = 0; aux < quantidadeSessoes; aux++)
	    {
	    	cadeiras[aux] = malloc(quantidadeSessoes);
			fscanf(fptr,"%s %s %s", data, hora, cadeiras[aux]);	    	
	    	printf("%d - Data: %s Hora: %s\n", aux+1,data, hora);
		}
		
		fclose(fptr);
		int sessaoEscolhida;
		scanf("%d", &sessaoEscolhida);
		escreverAssentos(cadeiras[sessaoEscolhida-1]);
	    	    
	}
}
	
	void escreverAssentos(char arquivo[])
	{
		char str1[50];
	    char str2[50];
	    char cat[100];
	
	    sprintf(str1,"D:\\PIM4\\");
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
	    //Se não houver assento disponivel, avisar o usuário e
	    //voltar para o menu anterior e selecionar outra sessão
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
		printf("0 - Voltar\n\n");
		
		if(assentosDisponiveis == 0)
		{
			//Voltar a seleção de sessao
		}
		else
		{
			//Oferecer opção de ir para a home
		char assentoEscolhido[2];
		printf("\n");
		scanf("%s", assentoEscolhido);
		int row, column;
		row = converter(assentoEscolhido, 0);
		column = converter(assentoEscolhido, 1);
		
		int t = 0;
			
		while(t == 0)
		{
			if(row+1 < 1 || row+1 > fileiras || column < 1 || column > cadeira)
			{
				printf("Assento inválido! Digite novamente: \n");
				scanf("%s", assentoEscolhido);
				row = converter(assentoEscolhido, 0);
				column = converter(assentoEscolhido, 1);
			}
			//Verifica se o assento esta disponivel
			else if (assentos[row][column-1]==1)
			{
				printf("Assento indisponível! Por favor escolha outro assento: \n");
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
	    		fprintf(fptr, "%d ", assentos[linha][cadeira]);
			}
		}
		
		//Selecionar o valor do ingresso (o programa não irá validar)
		//Decidir se os preços irao variar por peça de teatro, se sim montar um array de struct do tipo preço, ou um array
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



