#include<stdio.h>
#include<string.h>

#define SIZE 10		//how many spots on waiting list
#define LENGTH 20	//how long the reservation name can be

char names[SIZE][LENGTH];	//reservation name array
int party[SIZE];		//party size array
int counter = 0;		//current open spot on waitlist

void insert(void) {
	char tempName[LENGTH];		//holds most current name

	if (counter < SIZE) {		//if there is still spots on the waiting list, ask for reservation
		printf("Please enter your name:");
		scanf("%s", tempName);			//saves name to tempName

		strcpy(names[counter], tempName);	//copes name to name array
	
		printf("How many in your party?");	
		scanf("%d", &party[counter]);		//asks for party number and adds to coresponding spot
	
		printf("Added %s party of %d into position %d.\n", names[counter], party[counter], counter+1);
		counter++;				//increment counter to show one more space is full
	} else {
		printf("The waiting list is full, try again later.\n");
	}
}

void delete(void) {
	int openSeats;								//spots that can be filled
	int initialList = counter;						//counter to see how many parties are taken
	int i = 0;
	int j;

	if(counter == 0) {								//no one on the waiting list to seat
		printf("There is no one on the waiting list.\n");
	}else{
		printf("How many seats are currently open?");
		scanf("%d", &openSeats);						//ask for amount of open seats
	
		while (i < counter) {							//runs through current list
			if (party[i] <= openSeats) {					//if the party has less people than the open seats
				openSeats = openSeats - party[i];			//remove party seat number from open seats
				printf("Seating %s, party of %d\n", names[i], party[i]);
			
				j = i;
				while (j < counter) {					//move up remaining names after seating party
					strcpy(names[j],names[j+1]);
					party[j] = party[j+1];
					j++;
				}

				counter--;						//open 1 spot on the waiting list
				i--;
			}
			i++;
		}

		if (initialList == counter) {						//if all parties are too big
			printf("No parties can fit the current amount of seats avaliable\n");
		}
	}
}

void list(void) {
	int i = 0;

	while (i < counter) {
		printf("%s, %d\n", names[i], party[i]);				//list names in order from oldest to newest
		i++;
	}
	if (counter == 0)							//when there is no one on waiting list
		printf("There are no people on the waiting list.\n");
}


int main(){
	int response;
	while(1){								//print menu
		printf("	   MENU\n");
		printf("	1 - Insert\n");
		printf("	2 - Delete\n");
		printf("	3 - List\n");
		printf("	0 - Exit\n");
		printf("Select an option: ");
		scanf("%d", &response);

		switch(response) {						//conditionals for what you input
			case 1:
				insert();
				break;
			case 2:
				delete();
				break;
			case 3:
				list();
				break;
			case 0:
				return 0;
		}
	}
}
