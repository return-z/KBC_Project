#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_BUFFER 50 //maximum input characters the user can give. For larger inputs program will crash

/*	KBC GAME
	Style Guide : Please name functions in PascalCase (First letter of each word should be capital) just for neatness.
	PLEASE ADD COMMENTS IF YOU MAKE CHANGES.
	Test this code on your machine and tell if there are compatibility issues.
	Try to use functions wherever possible and reduce the use of global variables.
	Works on all OS'es I could work on!
*/

//global variables
char Question[16][1000];
char Options[16][4][1000];
char CorrectChoice[16][5];

int FiftyFiftyUsed = 0;
int FlipTheQuestionUsed = 0;
int CurrentQuestion;

//function to populate the global variables from the given input file
void PrepareGame(int a,FILE *fp){
	char question[1000];
	fgets(question,1000,fp);
	strcpy(Question[a],question);
	for(int i = 0;i < 4; i++){
		char option[1000];
		fgets(option,1000,fp);
		strcpy(Options[a][i],option);
	}
	char correct[5];
	fgets(correct,5,fp);
	strcpy(CorrectChoice[a],correct);
}

//function to print a banner
void PrintBanner(){
	printf("\nWe present to you!\n");

 	printf(" __  ___  ______     ______\n") ;
	printf("|  |/  / |   _  \\   /      |\n");
	printf("|  '  /  |  |_)  | |  ,----'\n");
	printf("|    <   |   _  <  |  |     \n");
	printf("|  .  \\  |  |_)  | |  `----.\n");
	printf("|__|\\__\\ |______/   \\______|\n");

	printf("\nHere's your chance to be a Crorepati!\n");
	
	//For opening and printnig the contents of the file containing Question and their respective Prize Money.
	FILE *fp;
	fp = fopen("Question_PrizeMoney Scheme.txt","r");
	char c;
	c = fgetc(fp);
	printf("\n");
	while(c != EOF){
		printf("%c",c);
		c = fgetc(fp);
	}
	printf("\n");
	fclose(fp);

	printf("\nThis game consists of 15 questions.\n");
	printf("\nPress 'l' for using a Life-Line\n");
	printf("\nYou have 2 Life-Lines -Fifty-Fifty and Flip the Question.\n");
	printf("\nYou will have 2 safe points at 5th and 10th question respectively.\n");
	printf("\nLosing after a safe point will take Prize money back to the last safe point instead of it turning to zero.\n");
	printf("\nPress ENTER key to begin!\n");            
}

//function to print a question by its number
void PrintQuestion(int q){
	if (q < 15){
		printf("\nHere's Question No. %d\n",q+1);
		printf("%s\n",Question[q]);
	}
	else{
		printf("\n%s\n",Question[CurrentQuestion]);
	}
}

//function to print options for a given question
void PrintOptions(int q){
	char OptionValue = 'A';
	for(int j=0;j<4;j++){
		printf("%c. %s\n",OptionValue++,Options[q][j]);
	}
}

//function for the life line 50-50
void FiftyFifty(int q){
	PrintQuestion(q);
    char OptionValue = 'A';
	int IncorrectOptionPrinted = 0;
	for(int j=0;j<4;j++){
		if (OptionValue != *CorrectChoice[q] && !IncorrectOptionPrinted){
			printf("%c. %s\n",OptionValue,Options[q][j]);
			IncorrectOptionPrinted = 1;
		}
		if (OptionValue == *CorrectChoice[q])
			printf("%c. %s\n",OptionValue,Options[q][j]);  
        OptionValue++;
	}
}

//function for the lifeline flip the question
void FlipTheQuestion(int q){
	printf("\nHere's the FLIPPED Question No. %d\n",q+1);
	printf("%s\n",Question[15]);
	PrintOptions(15);
}

//function that dictates the use of life lines
int ValidLifeLineInput(){
	char* input; //Take user's input as string and use the first letter to derefernce choice
	int InvalidInput = 4; //Handles bad input
	fgets(input,INPUT_BUFFER,stdin);
	if (strlen(input) < 3)
		return *input - '0'; //Derefernce the pointer and subtract the '0' char to get integer value
	return InvalidInput;
}


void UseLifeLine(int q){
	if (FiftyFiftyUsed && FlipTheQuestionUsed){
		printf("\nNo Lifelines are available!\n\n");
		return;
	}
	printf("\nFollowing Lifelines are available:\n");

	int num; //Takes the user's input as a character

	if (!FiftyFiftyUsed && !FlipTheQuestionUsed){
		printf("1. FIFTY-FIFTY\n2. FLIP THE QUESTION\n3. Go back! I can solve this!\n");
		printf("Enter a choice : ");

		num = ValidLifeLineInput();

		if (num == 1){
			FiftyFifty(q);
			FiftyFiftyUsed = 1;
			return;
		}
		else if (num == 2){
			FlipTheQuestion(q);
			FlipTheQuestionUsed = 1;
			CurrentQuestion = 15;
			return;
		}
		else if (num ==3){
			PrintQuestion(q);
			PrintOptions(q);
			return;
		}
		else{
			printf("Invalid choice!\n");
			PrintQuestion(q);
			PrintOptions(q);
			return;
		}
	}
	if (!FiftyFiftyUsed){
		printf("1. FIFTY-FIFTY\n2. Go back! I can solve this!\n");
		printf("Enter a choice : ");

		num = ValidLifeLineInput();

		if (num == 1){
			FiftyFifty(q);
			FiftyFiftyUsed = 1;
			return;
		}	
		else if (num == 2){
			PrintQuestion(q);
			PrintOptions(q);
			return;
		}
		else{
			printf("Invalid choice!\n");
			PrintQuestion(q);
			PrintOptions(q);
			return;
		}
	}
	if (!FlipTheQuestionUsed){
		printf("1. FLIP THE QUESTION\n2. Go back! I can solve this!\n");
		printf("Enter a choice : ");

		num = ValidLifeLineInput();

		if (num == 1){
			FlipTheQuestion(q);
			FlipTheQuestionUsed = 1;
			return;
		}	
		else if (num == 2){
			PrintQuestion(q);
			PrintOptions(q);
			return;
		}
		else{
			printf("Invalid choice!\n");
			PrintQuestion(q);
			PrintOptions(q);
			return;
		}
	}
}

//Alternative to strcasecmp function for characters.
int ChoicesAreSame(char* a, char* b){
	if ((*a == *b) || abs(*a - *b) == 32)
		return 1;
	return 0;
}

//Function that defines safepoints
void SafePoints(int q){
	if ((q >= 4) && (q < 9))
		printf("\nCongrats! You have won Rs 160000.\n");
	else if ((q >= 9) && (q < 15))
		printf("\nCongrats! You have won Rs 5000000.\n");
	else
		printf("\nSorry! You have won Rs 0.\n");
}

void Greeting(int q){
    if (q != 4 && q != 9)
        return;
    int level;
    if (q == 4)
        level = 1;
    if (q == 9)
        level = 2;
    printf("\nYOU'RE PLAYING LIKE A BOSS! You have cleared Safepoint %d\n",level);
    printf("\n");
}

int MoneyCalculator(int MoneyEarned){
	if(MoneyEarned==640000)
		return 1250000;
	else if(MoneyEarned==20000000)
		return 30000000;
	else if(MoneyEarned==30000000)
		return 50000000;
	else if(MoneyEarned==50000000)
		return 70000000;
	else
		return MoneyEarned*2;
}

int IsValidInput(char* input){
	if (strlen(input) <= 2){
		if (ChoicesAreSame(input,"A") || ChoicesAreSame(input,"B") || ChoicesAreSame(input,"C") || ChoicesAreSame(input,"D") || ChoicesAreSame(input,"L") || ChoicesAreSame(input,"Q"))
			return 1;
	}
	return 0;
}

void TakeValidInput(char* input){
	printf("Take you time to think! When ready enter your answer or use a Life Line! : ");
	fgets(input,INPUT_BUFFER,stdin);
	while(!IsValidInput(input)){
		printf("\nInvalid Input!\n\n");
		printf("Take you time to think! When ready enter your answer or use a Life Line! : ");
		fgets(input,INPUT_BUFFER,stdin);
	}
}

		
int main(int argc, char *argv[]){

	//Reading the game content from the input file
	FILE *file;
	file = fopen("input.txt","r");
	int TotalQuestions = 15;
	for(int i = 0; i < 16; i++){
		PrepareGame(i,file);
	}
	fclose(file);
	
	/* ************* Game starts from here******************* */

	PrintBanner(); //Print a flashy game banner!
	while (getchar() != '\n' && getchar() != EOF);
	
	int MoneyEarned=5000;
	
	for(int i = 0; i < TotalQuestions; i++){
		
		CurrentQuestion = i; //Why is this done?

		PrintQuestion(CurrentQuestion);
		PrintOptions(CurrentQuestion);
		
		char* LifeLineCall = "L";
		char* ExitCall = "Q";
		char UserChoice[INPUT_BUFFER];
		
		//Take VALID input from the user
		TakeValidInput(UserChoice);
		
		//user wants to opt for a lifeline
		while (ChoicesAreSame(LifeLineCall,UserChoice)){
			UseLifeLine(CurrentQuestion);
			TakeValidInput(UserChoice);
		}
		
		//one of the options are entered by the user
		if (ChoicesAreSame(UserChoice,CorrectChoice[CurrentQuestion])){
           	MoneyEarned = MoneyCalculator(MoneyEarned);
			printf("\nCongrats! You have answered correctly!\n");
			printf("You have won Rs %d so far\n",MoneyEarned);
            Greeting(CurrentQuestion); //called only on questions 5 and 10
			if(i != 14){
				printf("Press ENTER to continue\n");
				getc(stdin);
			}
			else
				printf("\nCongrats! You have won the game!!!!!!!\n");
		}
		
		//user wishes to exit the game
		else if (ChoicesAreSame(UserChoice,ExitCall)){
			char reply[INPUT_BUFFER];
			printf("\nAre you sure you want to quit? (y or n)\n");
			if (!i)
				printf("If you quit, you'll be going home empty handed!\n");
			else
				printf("If you quit, you'll be going home with Rs %d\n",MoneyEarned);
			//puts(UserChoice);
			fgets(reply,INPUT_BUFFER,stdin);
			while(!ChoicesAreSame("y",reply) && !ChoicesAreSame("n",reply) && strlen(reply) > 2){
				printf("\nInvalid input!\n");
				printf("\nAre you sure you want to quit? (y or n)\n");
				fgets(reply,INPUT_BUFFER,stdin);
			}	
			if (ChoicesAreSame("y",reply))
				break;
			else
				i--;
		}
		
		//user entered the wrong answer
		else{
			printf("\nYou have answered incorrectly! You have lost the game!\n");
			SafePoints(i);
            printf("\n");
            system("pause"); //UNCOMMENT THIS LINE IF YOU'RE USING LINUX
			break;
		}
		
	}
	
}
