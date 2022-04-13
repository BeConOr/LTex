#include "math_methods.h"
#include <stdio.h>
#include <stdlib.h>

char my_getc();

int main(void)
{
	//It's a simple computing app.
	double (*func[])(double, double) = {[(int)'+']=my_sum, [(int)'-']=my_sub, [(int)'/']=my_div, [(int)'*']=my_mul};
	printf("Insert m if you want to read a manual or any key if don't: ");
	char man_flag = my_getc(); //manage flag
	if(man_flag == 'm'){
		printf("Firstly, input number. Then input symbol +-/* and then number.\n");
		printf("You can do a computing sequence inputing symbol +-/* or stop computing when input =.\n");
	}
	int numb_flag = 1;
	double first_it = 0.0;
	double second_it = 0.0;
	char symb = 0;
	do{
		if(numb_flag){
			scanf("%lf", &first_it);
			numb_flag = 0;
		}
		symb = my_getc();
		if(symb == '='){
			printf("Result: %f\n", first_it);
			printf("Input 'c' if you want to close app: ");
			man_flag = my_getc();
			if(man_flag == 'c') return 0;
			numb_flag = 1;
			continue;
		}
		scanf("%lf", &second_it);
		int incor_flag = 0;
		do{
			incor_flag = 0;
			switch(symb){
				case '+':
				case '-':
				case '/':{
					if((second_it-0.0) < 0.00000000000000001){
						printf("Error: division by zero.\n");
						printf("Input all arguments again.\n");
						numb_flag = 1;
						break;
					}
				}
				case '*':{
					first_it = func[(int)symb](first_it, second_it);
					break;
				}
				default:{
					printf("Incorrect symb was input. Input symb again: ");
					symb = my_getc();
					incor_flag = 1;
				}
			}
		}while(incor_flag);
	}while(1);
	return 0;
}

char my_getc()
{
	char choice;
	do{
		choice = getchar();
	}while (choice == '\n');
	getchar();
	return choice;
}