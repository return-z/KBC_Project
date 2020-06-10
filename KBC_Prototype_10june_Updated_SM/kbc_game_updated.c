#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


/*	KBC GAME
	Style Guide : Please name functions in PascalCase (First letter of each word should be capital) just for neatness.
	PLEASE ADD COMMENTS IF YOU MAKE CHANGES.
	Test this code on your machine and tell if there are compatibility issues.
	Try to use functions wherever possible and reduce the use of global variables.
	Decide a proper monetary structure and implement in this code.
	Debugging of the code if left.
	Chances are that it works ONLY on GCC.
*/

//global variables
char Question[16][1000];
char Options[16][4][1000];
char CorrectChoice[16][5];

int FiftyFiftyUsed = 0;
int FlipTheQuestionUsed = 0;

//function to populate the global variables from the given input file
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
	printf("\n     		   We present to you!\n");

 	printf("		 __  ___  ______     ______\n") ;
	printf("		|  |/  / |   _  \\   /      |\n");
	printf("		|  '  /  |  |_)  | |  ,----'\n");
	printf("		|    <   |   _  <  |  |     \n");
	printf("		|  .  \\  |  |_)  | |  `----.\n");
	printf("		|__|\\__\\ |______/   \\______|\n");
	FILE *fp;//For opening and printnig the contents of the file containing Question and their respective Prize Money.
	fp=fopen("Question_PrizeMoney Scheme.txt","r");
	char c;
	c=fgetc(fp);
	printf("\n");
	while(c!=EOF){
		printf("%c",c);
		c=fgetc(fp);
	}
	printf("\n");
	fclose(fp);
	printf("\n	    This game consists of 15 questions.\n");
	printf("\n	    Press 'l' for using a Life-Line\n");
	printf("\n            You have 2 Life-Lines -Fifty-Fifty and Flip the Question.\n");
	printf("\n            You will have 2 safe points at 5th and 10th question respectively.\n");
	printf("\n            Losing after a safe point will take Prize money back to the last safe point instead of it turning to zero.\n");
	printf("\n	    Press ENTER key to begin!\n");            
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

//function for the life line 50-50
void FiftyFifty(int q){
	PrintQuestion(q);
	char OptionValue = 'A';
	int OptionsDisplayed = 1;
	for(int j=0;j<4;j++){
		if ((OptionValue==*CorrectChoice[q]) || ++OptionsDisplayed<=2){
			printf("%c. %s\n",OptionValue,Options[q][j]);
			OptionValue++;
		}
	}
}

//function for the lifeline flip the question
void FlipTheQuestion(int q){
	printf("\nHere's the FLIPPED Question No. %d\n",q+1);
	printf("%s\n",Question[15]);
	PrintOptions(15);
}

//function that dictates the use of life lines
void UseLifeLine(int q){
	if (FiftyFiftyUsed && FlipTheQuestionUsed){
		printf("No Lifelines are available!\n");
		return;
	}
	printf("\nFollowing Lifelines are available:\n");
	int num;
	char NextChar = '\n';
	if (!FiftyFiftyUsed && !FlipTheQuestionUsed){
		printf("1. FIFTY-FIFTY\n2. FLIP THE QUESTION\n3. Go back! I can solve this!\n");
		printf("Enter a choice : ");
		scanf("%d%c",&num,&NextChar);
		printf("%d\n",num);
		if (num == 1){
			FiftyFifty(q);
			FiftyFiftyUsed = 1;
			return;
		}
		else if (num == 2){
			FlipTheQuestion(q);
			FlipTheQuestionUsed = 1;
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
		scanf("%d%c",&num,&NextChar);
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
		scanf("%d%c",&num,&NextChar);
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

//Alternative to strcasecmp function. It is more reliable in my opinion
int ChoicesAreSame(char* a, char* b){
	if ((*a == *b) || abs(*a - *b) == 32)
		return 1;
	return 0;
}

//Function that defines safepoints
void SafePoints(int q){
	if((q>=4)&&(q<9))
		printf("You have won Rs 160000.\n");
	else if((q>=9)&&(q<15))
		printf("You have won Rs 5000000.\n");
	else
		printf("You have won Rs 0.\n");
}
		
int main(int argc, char *argv[]){
	//Input the questions from a txt file
	int old_stdin = dup(1);
	FILE *file;
	file = freopen("input.txt","r",stdin);
	int TotalQuestions = 15; //set this variable to the number of questions
	for(int i=0;i<16;i++){
		PrepareGame(i);
	}
	fclose(file);
	//Redirecting the input to stdin from the input file
	FILE *back;
	back = fdopen(old_stdin,"r");
	*stdin = *back;

	PrintBanner(); //Print a flashy game banner!
	while (getchar() != '\n');
	
	int MoneyEarned=5000;
	
	for(int i=0;i<TotalQuestions;i++){
		PrintQuestion(i);
		PrintOptions(i);
		char* LifeLineCall = "L";
		printf("Take you time to think! When ready enter your answer or use a Life Line! : ");
		char UserChoice[5];
		fgets(UserChoice,1000,stdin);
		while (ChoicesAreSame(LifeLineCall,UserChoice)){
			UseLifeLine(i);
			printf("Take you time to think! When ready enter your answer or use a Life Line! : ");
			fgets(UserChoice,1000,stdin);
		}
		if (ChoicesAreSame(UserChoice,CorrectChoice[i])){
			if(MoneyEarned==640000)
				MoneyEarned=1250000;
			else if(MoneyEarned==20000000)
				MoneyEarned=30000000;
			else if(MoneyEarned==30000000)
				MoneyEarned=50000000;
			else if(MoneyEarned==50000000)
				MoneyEarned=70000000;
			else
				MoneyEarned=MoneyEarned*2;
			printf("\nCongrats! You have answered correctly!\n");
			printf("You have won Rs %d so far\n",MoneyEarned);
			if(i!=14){
				printf("Press ENTER to continue\n");
				getc(stdin);
			}
			else
				printf("\nCongrats! You have won the game!!!!!!!\n");
		}
		else{
			printf("\nYou have answered incorrectly! You have lost the game!\n");
			SafePoints(i);
			break;
		}
		
	}
	
}
