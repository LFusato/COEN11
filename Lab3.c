#include<stdio.h>
#include<string.h>

#define SIZE 10         //how many spots on waiting list
#define LENGTH 20       //how long the reservation name can be

typedef struct entry {
	char name[LENGTH];
	int size;
} ENTRY;

ENTRY list[SIZE];
int counter = 0;

int duplicate(char * tempName) {	//for duplicate name inputs
        ENTRY *p = list;
        int i;

        for(i = 0; i < counter; i++) {		
		if (strcmp(tempName, p->name) == 0) {		//if name matches with one already listed, return to insert
                	return 0;
		}
		p++;
        }
	return 1;	//if there are no duplicates
}

void insert(void) {
	ENTRY *p = list;
	for (int i = 0; i < counter; i++) {
		p++;
	}

        char tempName[LENGTH];          //holds most current name
	int enterSize;

        if (counter < SIZE) {           //if there is still spots on the waiting list, ask for reservation
                printf("Please enter your name:");
                scanf("%s", tempName);                  //saves name to tempName

		duplicate(tempName);			//run check for duplicates
		while (duplicate(tempName) == 0) {
			printf("Name is already taken, choose another name: ");
			scanf("%s", tempName);
			duplicate(tempName);		//runs duplicate again to check
		}

                strcpy(list[counter].name, tempName);       //copes name to name array

                printf("How many in your party?");
                scanf("%d", &enterSize);           //asks for party number and adds to coresponding spot
		list[counter].size = enterSize;

                printf("Added %s party of %d into position %d.\n", p->name, p->size, counter+1);
                counter++;                              //increment counter to show one more space is full
		p++;
        } else {
                printf("The waiting list is full, try again later.\n");
        }
}

void delete(void) {
	ENTRY *p = list;
        int openSeats;                                                          //spots that can be filled
        int initialList = counter;                                              //counter to see how many parties are taken
	int i;
        int j;

        if(counter == 0) {                                                              //no one on the waiting list to seat
                printf("There is no one on the waiting list.\n");
        }else{
                printf("How many seats are currently open?");
                scanf("%d", &openSeats);                                                //ask for amount of open seats

                while (i < counter) {                                                   //runs through current list
                        if (list[i].size <= openSeats) {                                    //if the party has less people than the open seats
                                openSeats = openSeats - list[i].size;                       //remove party seat number from open seats
                                printf("Seating %s, party of %d\n", list[i].name, list[i].size);

                                j = i;
                                while (j < counter) {                                   //move up remaining names after seating party
                                        strcpy(list[j].name,list[j+1].name);
                                        list[j].size = list[j+1].size;
                                        j++;
                                }

                                counter--;                                              //open 1 spot on the waiting list
                                i--;
                        }
                        i++;
                }

                if (initialList == counter) {                                           //if all parties are too big
                        printf("No parties can fit the current amount of seats available\n");
                }
        }
}

void waitList(void) {
	ENTRY *p = list;
        int i = 0;

        while (i < counter) {
                printf("%s, %d\n", p->name, p->size);                         //list names in order from oldest to newest
                i++;
		p++;
        }
        if (counter == 0)                                                       //when there is no one on waiting list
                printf("There are no people on the waiting list.\n");
}

void fit_in(void) {
	ENTRY *p = list;
	int searchSize;				//size you are requesting to be found
	int i;
	int printed = 0;

	if (counter == 0) {			//when list is empty
		printf("There are no people on the waiting list.\n");
		return;
	}

	printf("Party size you are requesting:");
	scanf("%d", &searchSize);

	for (i = 0; i < counter; i++) {			//run through loop for finding size
		if (searchSize >= list[i].size) {
			printf("%s, %d\n", p->name, p->size);
			printed = 1;			//says that at least one party of that size was found
		}
		p++;
	}
	if (printed == 0) {				//if there is no found parties
		printf("No parties of that size or smaller found.\n");
	}
}

int main(){
        int response;
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
                                insert();
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
                                return 0;
                }
        }
}



