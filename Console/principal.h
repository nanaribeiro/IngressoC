#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit() functio
void menuPrincipal()
{
	int opcao;
	printf("___________$$$$$$$$$$$$$$$______________\n");
	printf("________$$$$______$$$$$$$$______________\n");
	printf("______$$$_____$$$$$$_$$_$$______________\n");
	printf("_____$____$$$$$$$$$__$__$$______________\n");
	printf("___$$___$$$$$$$$$___$___$$______________\n");
	printf("__$$__$$$$$$$$$$___$____$$______________\n");
	printf("__$$$$$$$$$$$_____$$_____$$____$$$$$$___\n");
	printf("$$$$$$$__________$$_______$$_$$$$$$$$$$_\n");
	printf("_________$$$$$__$$$____$$__$__$$$$$$$$$_\n");
	printf("______$$$$$$$$$_$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("_____$$$$$$$$$$$$__$$$$$__$$$$$$$$$$$$$$\n");
	printf("____$$$__$$$$$$$$$$$$$$$$__$$$$$$$$$__$$\n");
	printf("____$$___$$$$$$$$$$$$$$$$$_$$$$$$$$$__$$\n");
	printf("____$$__$$$$$$$$$$$$$$$$$$_$$$$$$$$$_$$_\n");
	printf("____$$$_$$$$$$$$$$$$$$$$$$_$$$$$$$$$$$__\n");
	printf("____$$$__$$$$$$$$$$$$$$$$_$$$$$$$$$$$___\n");
	printf("_____$$$$$$$$$$$$$$$$$$$__$$$$$$$$$_____\n");
	printf("_____$$$$$$$$$$$$$$$$$$$________________\n");
	printf("_______$$$$$$$$$$$$$$$__________________\n");
	printf("__________$$$$$$$$$$____________________\n\n");
	printf("Ingressos Theather\n");
	printf("Bem Vindo! Selecione uma opção: \n");
	printf("1 - Comprar Ingresso\n");
	printf("2 - Fechar Caixa\n");
	printf("3 - Sair\n\n");
	scanf("%d", &opcao);
	//Condicional do menu principal
	while(opcao != 0 && opcao != 1 && opcao != 2)
	{
		printf("Opção invalida! Digite novamente: \n");
		scanf("%d", &opcao);
	}
	//Pode trocar o if por um switch
	//Menu principal, passar para uma rotina, vai poder voltar nele
	if(opcao == 0)
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
