#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 10         //how many spots on waiting list
#define LENGTH 20       //how long the reservation name can be
#define ENTRY struct entry

struct entry {
	char name[LENGTH];
	int size;
	ENTRY *next;
};

ENTRY *head = NULL;
ENTRY *tail = NULL;

int duplicate(char * enterName) {	//for duplicate name inputs
        ENTRY *p = head;

        while (p != NULL) {		
		if (strcmp(enterName, p->name) == 0) {		//if name matches with one already listed, return to insert
                	return 0;
		}
		p = p->next;
        }
	return 1;	//if there are no duplicates
}
void insert(char *,int);

void minput(void) {	//runs when user wants to input an entry
	int i;
	
        char enterName[LENGTH];          //holds most current name
	int enterSize;

        printf("Please enter your name:");
        scanf("%s", enterName);                  //saves name to enterName
	
	while (duplicate(enterName) == 0) {
		printf("Name is already taken, choose another name: ");
		scanf("%s", enterName);
		duplicate(enterName);		//runs duplicate again to check
	}

        printf("How many in your party?");
        scanf("%d", &enterSize);           //asks for party number and adds to coresponding spot

	insert(enterName, enterSize);
}

void insert(char rname[], int rsize) {	//runs when you want to add to list, takes from manual entry or file
	ENTRY *temp;
	
	temp = (ENTRY*)malloc(sizeof(ENTRY));		//allocate memory

	strcpy(temp->name, rname);
	temp->size = rsize;

	if (head == NULL) {			//list is empty
		head = temp;
		tail = temp;
		tail->next = NULL;
	} else {
		tail->next = temp;
		tail = temp;
		tail->next = NULL;
	}
	printf("Added %s party of %d into position.\n", temp->name, temp->size);
}

void delete(void) {
	ENTRY *p, *q;
	p = head;

        int openSeats, startSeats;                                                          //spots that can be filled

        if(head == NULL) {                                                              //no one on the waiting list to seat
                printf("There is no one on the waiting list.\n");
        }else{
                printf("How many seats are currently open?");
                scanf("%d", &openSeats);                                                //ask for amount of open seats
		startSeats = openSeats;

                while (p != NULL) {                                                   //runs through current list
                        if (p->size <= openSeats) {                                    //if the party has less people than the open seats
                                openSeats = openSeats - p->size;                       //remove party seat number from open seats
                                printf("Seating %s, party of %d\n", p->name, p->size);
				
				if (p == head) {		//Front of list
					head = head->next;
				}
				else if (p->next == NULL) {	//End of List
					q->next = NULL;
				}
				else {				//Middle of List
					q->next = p->next;
				}
                      		free(p);			//free memory
                        }
			q = p;		//q is previous p
                        p = p->next;	//p is next link
                }
		if (openSeats == startSeats) {			//if the number is not found
        	        printf("No parties can fit the current amount of seats available\n");
		}
        }
}


void waitList(void) {
	ENTRY *p = head;

        while (p != NULL) {
                printf("%s, %d\n", p->name, p->size);                         //list names in order from oldest to newest
       		p = p->next;
	 }
        if (head == NULL) {                                                       //when there is no one on waiting list
                printf("There are no people on the waiting list.\n");
	}
}

void fit_in(void) {
	ENTRY *p = head;
	int searchSize;				//size you are requesting to be found
	int printed = 0;

	if (head == NULL) {			//when list is empty
		printf("There are no people on the waiting list.\n");
		return;
	}

	printf("Party size you are requesting:");
	scanf("%d", &searchSize);

	while (p != NULL) {			//run through loop for finding size
		if (searchSize >= p->size) {
			printf("%s, %d\n", p->name, p->size);
			printed = 1;			//says that at least one party of that size was found
		}
		p = p->next;
	}
	if (printed == 0) {				//if there is no found parties
		printf("No parties of that size or smaller found.\n");
	}
}

void read_file(char *file_name) {
	FILE *fp;
	char readName[50];
	int readSize;
	
	fp = fopen(file_name, "r");	//open data file
	if (fp == NULL) {			//if the file is empty
		return;
	}

	while (fscanf(fp, "%s\t%d",readName, &readSize) == 2) {		//while its reading 2 values...
		insert(readName, readSize);				//call insert to add to linked list
	}
	fclose(fp);							//close file
}

void write_file(char *file_name) {
	FILE *fp;			//file pointer
	fp = fopen(file_name, "w");	//open file to write
	ENTRY *p = head;	
	
	while (p != NULL) {		//iterate list
		fprintf(fp, "%s\t%d\n", p->name, p->size);		//should write to file as: NAME		SIZE
		free(p);						//free space
		p = p->next;	
	}
	fclose(fp);		//close file
}

int main(int argc, char *argv[]){
        int response;
	
	if(argc != 2) {								//if there is no file called in execution
		printf("Command should read: ./a.out file_name\n");
		return 1;
	}

	read_file(argv[1]);							//read file names

        while(1){                                                               //print menu
                printf("           MENU\n");
                printf("        1 - Insert\n");
                printf("        2 - Delete\n");
                printf("        3 - List\n");
		printf("	4 - Search Size\n");
                printf("        0 - Exit\n");
                printf("Select an option: ");
                scanf("%d", &response);

                switch(response) {                                              //conditionals for what you input
                        case 1:
                                minput();
                                break;
                        case 2:
                                delete();
                                break;
                        case 3:
                                waitList();
                                break;
			case 4:
				fit_in();
				break;
                        case 0:
				write_file(argv[1]);
                                return 0;
                }
        }
}



