#include<stdio.h>
#include<stdlib.h>
#include"app.h"
int main(){
	char choice;
	while(1){	
		printf("Which information do you want?\n");
		printf("Version(v),CPU(c),Memory(m),Time(t),All(a),Exit(e)?\n");
		scanf(" %c",&choice);
		switch(choice){
			case 'v':
				printf("Version:\n");
				break;
			case 'c':
				printf("CPU information:\n");
				break;
			case 'm':
				printf("Memory information:\n");
				break;
			case 't':
				printf("Time information:\n");
				break;
			case 'a':
				printf("Version:\n");
				printf("CPU information:\n");
				printf("Memory information:\n");
				printf("Time information:\n");
				break;
			case 'e':
				return 0;
				break;
			default:
				break;
		}
	}
	return 0;
}
