#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_BUFFER 1000 //maximum input characters the user can give. For larger inputs program will crash

/*	KBC GAME
	Style Guide : Please name functions in PascalCase (First letter of each word should be capital) just for neatness.
	PLEASE ADD COMMENTS IF YOU MAKE CHANGES.
	Test this code on your machine and tell if there are compatibility issues.
	Try to use functions wherever possible and reduce the use of global variables.
	Works on all OS'es I could work on!
*/

//global variables
int FiftyFiftyUsed = 0;
int FlipTheQuestionUsed = 0;
int CurrentQuestion;

//Basic unit of the game is an Object. An Object consists of the question,options and correct choice for the question.
struct Object{
	char Question[INPUT_BUFFER];
	char Options[4][INPUT_BUFFER];
	char CorrectChoice[INPUT_BUFFER];
}Object[16];

//*********************FUNCTIONS FOR PREPARING THE GAME ENVIORNMENT****************//

//function to populate the structure
void PrepareGame(int a,FILE *fp){
	fgets(Object[a].Question,INPUT_BUFFER,fp);
	for(int i=0;i<4;i++)
		fgets(Object[a].Options[i],INPUT_BUFFER,fp);
	fgets(Object[a].CorrectChoice,INPUT_BUFFER,fp);
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
}

// *******************GENERAL USE FUNCTIONS (FOR PRINTING QUESTIONS AND OPTIONS)****************//

//function to print a question by its number
void PrintQuestion(int q){
	if (q < 15){
		printf("\nHere's Question No. %d\n",q+1);
		printf("%s\n",Object[q].Question);
	}
	else{
		printf("\n%s\n",Object[q].Question);//Left for the flip the question lifeline
	}
}

//function to print options for a given question
void PrintOptions(int q){
	char OptionValue = 'A';
	for(int j=0;j<4;j++){
		printf("%c. %s\n",OptionValue++,Object[q].Options[j]);
	}
}

//********************FUNCTIONS DEFINED FOR LIFELINES***************************//

//function for the life line 50-50
void FiftyFifty(int q){
	PrintQuestion(q);
    char OptionValue = 'A';
	int IncorrectOptionPrinted = 0;
	for(int j=0;j<4;j++){
		if (OptionValue != *Object[q].CorrectChoice && !IncorrectOptionPrinted){
			printf("%c. %s\n",OptionValue,Object[q].Options[j]);
			IncorrectOptionPrinted = 1;
		}//This loop finds the correct option
		if (OptionValue == *Object[q].CorrectChoice)
			printf("%c. %s\n",OptionValue,Object[q].Options[j]);  
        OptionValue++;
	}//It prints just the next option
}

//function for the lifeline flip the question
void FlipTheQuestion(int q){
	printf("\nHere's the FLIPPED Question No. %d\n",q+1);
	printf("%s\n",Object[15].Question);
	PrintOptions(15);
}

//*************************FUNCTIONS TO ALLOW VALID INPUT ONLY************************//

//Alternative to strcasecmp function for characters.
int ChoicesAreSame(char* a, char* b){
	if ((*a == *b) || abs(*a - *b) == 32)// For comparing both the lowercase and uppercase inputs 
		return 1;
	return 0;
}

int ValidLifeLineInput(){
	char* input; //Take user's input as string and use the first letter to derefernce choice
	int InvalidInput = 4; //Handles bad input
	fgets(input,INPUT_BUFFER,stdin);
	if (strlen(input) < 3)
		return *input - '0'; //Derefernce the pointer and subtract the '0' char to get integer value
	return InvalidInput;
}

//To check if the choice is correct and allows to enter 'l' for lifeline and 'q' for quitting 
int IsValidInput(char* input){
	if (strlen(input) <= 2){
		if (ChoicesAreSame(input,"A") || ChoicesAreSame(input,"B") || ChoicesAreSame(input,"C") || ChoicesAreSame(input,"D") || ChoicesAreSame(input,"L") || ChoicesAreSame(input,"Q"))
			return 1;
	}
	return 0;
}

//Function to reassure the player
void TakeValidInput(char* input){
	printf("Take you time to think! When ready enter your answer or use a Life Line! or Quit the game: ");
	fgets(input,INPUT_BUFFER,stdin);
	while(!IsValidInput(input)){
		printf("\nInvalid Input!\n\n");
		printf("Take you time to think! When ready enter your answer or use a Life Line! or Quit the game: ");
		fgets(input,INPUT_BUFFER,stdin);
	}
}

//FUNCTION DESCRIBING THE USE OF LIFELINES
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

//*******************************MISC HELPER FUNCTIONS*************************//

//Function that defines safepoints
void SafePoints(int q){
	if ((q >= 4) && (q < 9))
		printf("\nCongrats! You have won Rs 160000.\n");
	else if ((q >= 9) && (q < 15))
		printf("\nCongrats! You have won Rs 5000000.\n");
	else
		printf("\nSorry! You have won Rs 0.\n");
}

//Function disclosing more about safepoints once the player has reached one
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

//Function calculating the money earned
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
		
int main(int argc, char *argv[]){

	//Reading the game content from the input filechoice
	FILE *file;
	file = fopen("input.txt","r");//Opens the input.txt which contains all the questions, options and correct answers.
	int TotalQuestions = 15;//For storing 16 questions
	for(int i = 0; i < 16; i++){
		PrepareGame(i,file);
	}
	fclose(file);
	
	/* ************* Game starts from here******************* */

	PrintBanner(); //Print a flashy game banner!
	while (getchar() != '\n' && getchar() != EOF);
	
	int MoneyEarned = 5000;
	
	for(int i = 0; i < TotalQuestions; i++){
		
		CurrentQuestion = i;

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
		if (ChoicesAreSame(UserChoice,Object[CurrentQuestion].CorrectChoice)){
           	MoneyEarned = MoneyCalculator(MoneyEarned);//Calculates the prize money earned till now.
			printf("\nCongrats! You have answered correctly!\n");
			printf("You have won Rs %d so far\n",MoneyEarned);
            Greeting(i); //called only on questions 5 and 10 for congratulating the player
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
				printf("If you quit, you'll be going home empty handed!\n");//If player quits on the very first question
			else
				printf("If you quit, you'll be going home with Rs %d\n",MoneyEarned);//For all other cases
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
            system("pause"); //COMMENT THIS LINE IF YOU'RE USING LINUX
			break;
		}
		
	}
	
}
