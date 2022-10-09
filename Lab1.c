#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void) {
	srand((int)time(NULL));						//establishing for random to work

	int quot;
	int denom;
	int divid;
	int answer;
	int numCorrect;
	int percent;

	for(int i=0; i<10; i++) {					//repeat creating questions 10x
 		denom = rand() % 12 + 1;				//generate random denominator, cannot be 0
		quot = rand() % 13;					//generate random quotient
		divid = denom * quot;					//create denominator
		printf("%d / %d = ",divid, denom);			//show user equation
		scanf("%d",&answer);					//ask for answer
		if(answer == quot) {					//if correct
			printf("Correct.\n");
			numCorrect++;					//add 1 to correct counter
		} else {						//if wrong
			printf("The correct answer is %d.\n",quot);	//provide correct ans
		}	
	}
	percent = numCorrect * 10;					//calculate percentage correct
	printf("You got %d%% correct.\n",percent);			//display percentage
}
