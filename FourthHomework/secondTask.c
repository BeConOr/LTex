#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 20
#define MAX_TEL 11
#define MAX_SURNAME 20
#define USERS_NUMBER 10

int main(void){
	struct user{
		char name[MAX_NAME];
		char surname[MAX_SURNAME];
		char tel[MAX_TEL];
	};
	
	struct user users[USERS_NUMBER];
	int users_counter = 0;
	
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
		while ( choice == '\n' && choice == EOF ){
                choice = getchar() - '0';
        }
		switch(choice){
			case 1:
				{
					if(users_counter != 0){
						for(int i = 0; i < users_counter; ++i){
							printf("User #%d:\n", i+1);
							printf("\tName: %s\n", users[i].name);
							printf("\tSurname: %s\n", users[i].surname);
							printf("\tPhone number: %s\n\n", users[i].tel);
						}
					}else{
						printf("Users list is clear.\n");
					}
				}
				break;
			case 2:
				{
					if(users_counter < USERS_NUMBER){
						printf("Adding new user:\n");
						printf("\tInput name: ");
						fgets(users[users_counter].name, MAX_NAME, stdin);
						printf("\tInput surname: ");
						fgets(users[users_counter].surname, MAX_SURNAME, stdin);
						printf("\tInput phone number: ");
						fgets(users[users_counter].tel, MAX_TEL, stdin);
						++users_counter;
					}else{
						printf("Users list is full.\n");
					}
				}
				break;
			case 3:
				{
					if(users_counter > 0){
						--users_counter;
					}else{
						printf("Users list is clear.\n");
					}
				}
				break;
			case 4:
				{
					if(users_counter != 0){
						printf("Searching user by phone number:\n");
						printf("\tInsert phone number: ");
						char ser_tel[MAX_TEL];
						fgets(ser_tel, MAX_TEL, stdin);
						int ser_flag = 0;
						for(int i = 0; i < users_counter; ++i){
							int curr_flag = 0;
							for(int j = 0; j < MAX_TEL; ++j){
								if(users[i].tel[j] != ser_tel[j]){
									curr_flag = 1;
									break;
								}
							}
							if(curr_flag == 0){
								ser_flag = i;
								break;
							}
						}
						if(ser_flag != 0){
							printf("User found (#%d):\n", ser_flag);
							printf("\tName: %s\n", users[ser_flag].name);
							printf("\tSurname: %s\n", users[ser_flag].surname);
							printf("\tPhone number: %s\n\n", users[ser_flag].tel);
						}
					}else{
						printf("Users list is clear.\n");
					}
				}
				break;
			case 5:
				{
					if(users_counter != 0){
						printf("Searching user by name:\n");
						printf("\tInsert name: ");
						char ser_name[MAX_NAME];
						fgets(ser_name, MAX_NAME, stdin);
						int ser_flag = 0;
						for(int i = 0; i < users_counter; ++i){
							int curr_flag = 0;
							for(int j = 0; j < MAX_NAME; ++j){
								if(users[i].name[j] != ser_name[j]){
									curr_flag = 1;
									break;
								}
							}
							if(curr_flag == 0){
								ser_flag = i;
								break;
							}
						}
						if(ser_flag != 0){
							printf("User found (#%d):\n", ser_flag);
							printf("\tName: %s\n", users[ser_flag].name);
							printf("\tSurname: %s\n", users[ser_flag].surname);
							printf("\tPhone number: %s\n\n", users[ser_flag].tel);
						}
					}else{
						printf("Users list is clear.\n");
					}
				}
				break;
			case 6:
				{
					if(users_counter != 0){
						printf("Searching user by surname:\n");
						printf("\tInsert name: ");
						char ser_surname[MAX_SURNAME];
						fgets(ser_surname, MAX_SURNAME, stdin);
						int ser_flag = 0;
						for(int i = 0; i < users_counter; ++i){
							int curr_flag = 0;
							for(int j = 0; j < MAX_SURNAME; ++j){
								if(users[i].surname[j] != ser_surname[j]){
									curr_flag = 1;
									break;
								}
							}
							if(curr_flag == 0){
								ser_flag = i;
								break;
							}
						}
						if(ser_flag != 0){
							printf("User found (#%d):\n", ser_flag);
							printf("\tName: %s\n", users[ser_flag].name);
							printf("\tSurname: %s\n", users[ser_flag].surname);
							printf("\tPhone number: %s\n\n", users[ser_flag].tel);
						}
					}else{
						printf("Users list is clear.\n");
					}
				}
				break;
			default: break;
		}
		flag = choice;
	}while((flag < 9) && (flag > 0));
	return 0;
}