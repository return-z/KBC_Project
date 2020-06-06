#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

//global variables
char Question[15][1000];
char Options[15][4][1000];
char CorrectChoice[15][5];

//function to populate the global variables
void PrepareGame(int a){
	char question[1000];
	fgets(question,1000,stdin);
	strcpy(Question[a],question);
	for(int i=0;i<4;i++){
		char option[1000];
		fgets(option,1000,stdin);
		strcpy(Options[a][i],option);
	}
	char correct[5];
	fgets(correct,5,stdin);
	strcpy(CorrectChoice[a],correct);
}

//function to print a banner
void PrintBanner(){
	printf("\n     We present to you!\n");

 	printf(" __  ___  ______     ______\n") ;
	printf("|  |/  / |   _  \\   /      |\n");
	printf("|  '  /  |  |_)  | |  ,----'\n");
	printf("|    <   |   _  <  |  |     \n");
	printf("|  .  \\  |  |_)  | |  `----.\n");
	printf("|__|\\__\\ |______/   \\______|\n");
                            

	printf("\nThis game consists of 15 questions.");
	printf("\nPress ENTER key to begin!\n");
}

//function to print a question by its number
void PrintQuestion(int q){
	printf("\nHere's Question No. %d\n",q+1);
	printf("%s\n",Question[q]);
}

//function to print options for a given question
void PrintOptions(int q){
	char OptionValue = 'A';
	for(int j=0;j<4;j++){
		printf("%c. %s\n",OptionValue++,Options[q][j]);
	}
}

int main(){
	//Input the questions from a txt file
	int old_stdin = dup(1);
	FILE *file;
	file = freopen("input.txt","r",stdin);
	int TotalQuestions = 2; //set this variable to the number of questions
	for(int i=0;i<TotalQuestions;i++){
		PrepareGame(i);
	}
	fclose(file);
	//Redirecting the input to stdin from the input file
	FILE *back;
	back = fdopen(old_stdin,"r");
	stdin = back;

	PrintBanner(); //Print a flashy game banner!
	while (getchar() != '\n');
	
	int MoneyEarned = 0;
	
	for(int i=0;i<TotalQuestions;i++){
		PrintQuestion(i);
		PrintOptions(i);
		printf("Take you time to think! When ready enter your answer : ");
		char UserChoice[5];
		fgets(UserChoice,1000,stdin);
		if (!strcasecmp(UserChoice,CorrectChoice[i])){
			MoneyEarned += 100;
			printf("Congrats! You have answered correctly! You have won $100\n");
			printf("You have won $%d so far\n",MoneyEarned);
			printf("Press ENTER to continue\n");
			getc(stdin);
		}
		else{
			printf("You have answered incorrectly! You have lost the game!\n");
			break;
		}
		
	}
	
}