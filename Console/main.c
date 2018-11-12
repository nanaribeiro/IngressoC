#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "T1.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	//Acentuacao
	setlocale(LC_ALL,"");
	//Decoracao
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
	//rotina principal
	menuPrincipal();
	//Como saber qual o dia da semana dada uma data
	int day = dayofweek(30, 10, 2018); 
    printf ("%d", day);
	
}

  

