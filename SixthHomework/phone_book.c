#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_NAME 20
#define MAX_TEL 12
#define MAX_SURNAME 20

int main(void){
	struct user{
		char name[MAX_NAME];
		char surname[MAX_SURNAME];
		char tel[MAX_TEL];
	};
	
	struct user* start = NULL;
	size_t users_counter = 0;
	int flag = 0;
	
	do{
		printf("It's the first version of phonebook. Please, choose one of the following acts, and insert its number:\n");
		printf("1) Look over users list.\n");
		printf("2) Add new user.\n");
		printf("3) Delete user.\n");
		printf("4) Find user by phone number.\n");
		printf("5) Find user by name.\n");
		printf("6) Find user by surname.\n");
		printf("Insert another key for exit.\n");
		int choice;
		do{
			choice = getchar();
		}while (choice == '\n');
		choice -= '0';
		getchar();
		switch(choice){
			case 1:
				{
					if(users_counter > 0){
						for(size_t i = 0; i < users_counter; ++i){
							printf("User #%d:\n", i+1);
							printf("\tName: %s\n", start[i].name);
							printf("\tSurname: %s\n", start[i].surname);
							printf("\tPhone number: %s\n\n", start[i].tel);
						}
					}else{
						printf("Users list is clear.\n");
					}
				}
				break;
			case 2:
				{
					++users_counter;
					if(users_counter > 0){
						start = realloc(start, sizeof(struct user)*(users_counter));
					}else{
						start = malloc(sizeof(struct user));
					}
					if(start == NULL){
						printf("Ошибка выделения памяти!\n");
						exit (1);
					}
					printf("Adding new user:\n");
					printf("\tInput name: ");
					fgets(start[users_counter-1].name, MAX_NAME, stdin);
					printf("\tInput surname: ");
					fgets(start[users_counter-1].surname, MAX_SURNAME, stdin);
					printf("\tInput phone number: ");
					fgets(start[users_counter-1].tel, MAX_TEL, stdin);
				}
				break;
			case 3:
				{
					if(users_counter > 0){
						--users_counter;
						start = realloc(start, users_counter);
						printf("The last user is deleted.\n");
					}else{
						printf("Users list is clear.\n");
					}
				}
				break;
			case 4:
				{
					if(users_counter > 0){
						printf("Searching user by phone number:\n");
						printf("\tInsert phone number: ");
						char ser_tel[MAX_TEL] = {'0'};
						fgets(ser_tel, MAX_TEL, stdin);
						int ser_flag = 0;
						for(size_t i = 0; i < users_counter; ++i){
							int curr_flag = 0;
							for(int j = 0; j < MAX_TEL; ++j){
								if(start[i].tel[j] != ser_tel[j]){
									curr_flag = 1;
									break;
								}
							}
							if(curr_flag == 0){
								ser_flag = i+1;
								break;
							}
						}
						if(ser_flag != 0){
							printf("User found (#%d):\n", ser_flag);
							printf("\tName: %s\n", start[ser_flag-1].name);
							printf("\tSurname: %s\n", start[ser_flag-1].surname);
							printf("\tPhone number: %s\n\n", start[ser_flag-1].tel);
						}else{
							printf("User is not found.\n");
						}
					}else{
						printf("Users list is clear.\n");
					}
				}
				break;
			case 5:
				{
					if(users_counter > 0){
						printf("Searching user by name:\n");
						printf("\tInsert name: ");
						char ser_name[MAX_NAME] = {'0'};
						fgets(ser_name, MAX_NAME, stdin);
						int ser_flag = 0;
						for(size_t i = 0; i < users_counter; ++i){
							int curr_flag = 0;
							for(int j = 0; j < MAX_NAME; ++j){
								if((start[i].name[j] == '\n') || (ser_name[j] == '\n')){
									if(start[i].name[j] != ser_name[j]){
										curr_flag = 1;
									}
									break;
								}
								if(start[i].name[j] != ser_name[j]){
									curr_flag = 1;
									break;
								}
							}
							if(curr_flag == 0){
								ser_flag = 1;
								printf("User found (#%d):\n", i+1);
								printf("\tName: %s\n", start[i].name);
								printf("\tSurname: %s\n", start[i].surname);
								printf("\tPhone number: %s\n\n", start[i].tel);
							}
						}
						if(ser_flag == 0){
							printf("User is not found.\n");
						}
					}else{
						printf("Users list is clear.\n");
					}
				}
				break;
			case 6:
				{
					if(users_counter > 0){
						printf("Searching user by surname:\n");
						printf("\tInsert surname: ");
						char ser_surname[MAX_SURNAME] = {'0'};
						fgets(ser_surname, MAX_SURNAME, stdin);
						int ser_flag = 0;
						for(size_t i = 0; i < users_counter; ++i){
							int curr_flag = 0;
							for(int j = 0; j < MAX_SURNAME; ++j){
								if((start[i].surname[j] == '\n') || (ser_surname[j] == '\n')){
									if(start[i].surname[j] != ser_surname[j]){
										curr_flag = 1;
									}
									break;
								}
								if(start[i].surname[j] != ser_surname[j]){
									curr_flag = 1;
									break;
								}
							}
							if(curr_flag == 0){
								ser_flag = 1;
								printf("User found (#%d):\n", i+1);
								printf("\tName: %s\n", start[i].name);
								printf("\tSurname: %s\n", start[i].surname);
								printf("\tPhone number: %s\n\n", start[i].tel);
							}
						}
						if(ser_flag == 0){
							printf("User is not found.\n");
						}
					}else{
						printf("Users list is clear.\n");
					}
				}
				break;
			default: break;
		}
		flag = choice;
	}while((flag < 7) && (flag > 0));
	if(start != NULL) free(start);
	return 0;
}