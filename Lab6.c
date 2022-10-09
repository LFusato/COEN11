#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 10         //how many spots on waiting list
#define LENGTH 20       //how long the reservation name can be
#define ENTRY struct node
#define LIST struct list

struct node {
	char name[LENGTH];
	int size;
	ENTRY *next;
};

struct list {
	ENTRY *head;
	ENTRY *tail;
};

LIST list[4] ={{NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL}};


int duplicate(char * enterName) {	//for duplicate name inputs
	int spot = 0;
	ENTRY *p = list[spot].head;
	for (spot = 0; spot < 4; spot++) {
		p = list[spot].head;
        	while (p != NULL) {		
			if (strcmp(enterName, p->name) == 0) {		//if name matches with one already listed, return to insert
        	        	return 0;
			}
			p = p->next;
        	}
	}
	return 1;
}

void insert(void) {
	ENTRY *temp;
	int spot;
	
	temp = (ENTRY*)malloc(sizeof(ENTRY));	//allocate space for new entry

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
	
	if (enterSize <= 2) {		//1-2 size
		spot = 0;
	}
	else if (enterSize <= 4) {	//3-4 size
		spot = 1;
	}
	else if (enterSize <= 6) {	//5-6 size
		spot = 2;
	} 
	else {			//6+ size
		spot = 3;
	}

	strcpy(temp->name, enterName);
	temp->size = enterSize;			//size in temp is the entered size

	if (list[spot].head == NULL){		//when there is nothing in the list
		list[spot].head = temp;		//new entry is the head
		list[spot].tail = temp;		//new entry is the tail, since only one entry
		list[spot].tail->next = NULL;	//next potential entry is NULL
	} else {			//when there are items in the list
		list[spot].tail->next = temp;	//the last entry on list points to next new entry
		list[spot].tail = temp;		//new tail of list is the new entry
		list[spot].tail->next = NULL;	//next poential entry is NULL
	}

        printf("Added %s party of %d into list %d.\n", temp->name, temp->size, spot);
}

void delete(void) {
	int spot = 0;
	int emptylists = 0;
	ENTRY *p, *q;
	p = list[spot].head;

        int openSeats, startSeats;                                                         //spots that can be filled
	
	for (spot = 0; spot < 4; spot++) {
		if (list[spot].head == NULL) { //if the list is empty
			emptylists++;
		}
	}
	if (emptylists == 4) {
		printf("List is empty.\n");
		return;
	}

        printf("How many seats are currently open?");
        scanf("%d", &openSeats);                                                //ask for amount of open seats
	startSeats = openSeats;
	
	int startPart;
	if (openSeats > 6) {
		startPart = 4;
	} else if (openSeats > 4) {
		startPart = 3;
	} else if (openSeats > 2) {
		startPart = 2;
	} else {
		startPart = 1;
	}
	
	int i;
	spot = 0;

	for (spot = 0; spot < startPart; spot++) {
		p = list[spot].head;
	      	while (p != NULL) {                                                  //runs through current list
	          	if (p->size <= openSeats) {                                    //if the party has less people than the open seats
	                       	openSeats = openSeats - p->size;                       //remove party seat number from open seats
	                       	printf("Seating %s, party of %d\n", p->name, p->size);
					
				if (p == list[spot].head) {		//Front of list
					list[spot].head = list[spot].head->next;
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
	}
	if (openSeats == startSeats) {			//if the number is not found
               	printf("No parties can fit the current amount of seats available\n");
	}
}

void waitList(void) {
	int spot = 0;
	int emptylists = 0;
	ENTRY *p = list[spot].head;
	for (spot = 0; spot < 4; spot++) {
		p = list[spot].head;
	        while (p != NULL) {
        	        printf("%s, %d\n", p->name, p->size);                         //list names in order from oldest to newest
       			p = p->next;
		}
        	if (list[spot].head == NULL) {                                                       //when there is no one on waiting list
        	        emptylists++;
		} else {
			printf("\n");
		}
	}
	if (emptylists == 4) {
		printf("There is no one on the waiting list\n");
	}
}

void fit_in(void) {
	int searchSize, emptylists, spot;				//size you are requesting to be found
	int printed = 0;
	ENTRY *p = list[spot].head;

	for (spot = 0; spot < 4; spot++) {
		if (list[spot].head == NULL) {
			emptylists++;
		}
	}
	if (emptylists == 4) {
		printf("List is empty.\n");
		return;
	}		

	printf("Party size you are requesting:");
	scanf("%d", &searchSize);
	for (spot = 0; spot < 4; spot++) {
		p = list[spot].head;
		while (p != NULL) {			//run through loop for finding size
			if (searchSize >= p->size) {
				printf("%s, %d\n", p->name, p->size);
				printed = 1;			//says that at least one party of that size was found
			}
			p = p->next;
		}
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
                        case 0: {
				int spot;
				ENTRY *p = list[spot].head, *q;
				for (spot = 0; spot < 4; spot++) {
					p = list[spot].head;
					while (p != NULL) {
						q = p;
						p = p->next;
						free(q);						
					}
				}
                                return 0;
			}
                }
        }
}



