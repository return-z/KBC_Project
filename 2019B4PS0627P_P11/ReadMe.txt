#############################################################
ReadMe for assignment submitted by 2019B4PS0627P
Practical section number: P11
Asignment question attempted: 1
#############################################################
Team:
1. 2019B4PS0627P   Saksham Mahajan
2. 2019B2PS1008P   Vinayak Tyagi
3. 2019A2PS0648P   Parth Daga
#############################################################
Description of how to run the code and observe the output: 
1. The c file is called 2019B4PS0627P_P11.c . It is a KBC Game.
2. To compile the c file use the command: gcc -o 2019B4PS0627P_P11.exe 2019B4PS0627P_P11.c 
3. It will result in a file named 2019B4PS0627P_P11.exe which can be executed using ./2019B4PS0627P_P11.exe 
4. The input files are input.txt and intro.txt used for entering the questions to be asked and primary information, such as the total number of questions,
   prize money with respect to each question, available life lines and intermediate question levels/safepoints respectively to the c program.
5. When you run the program,a flashy kbc banner will appear along with all the instructions after which it will prompt you to press enter to start the game. 
6. Once the question appears, further there would be a prompt which will ask you to select one of the following according to choice:
     i)Enter an option to answer the question.
    ii)Enter either 'q' or 'Q' to quit the game along with the prize money won till that question.
   iii)Enter either 'l' or 'L' to use the lifelines. 
7. If an option has been entered,the next prompt will show you whether your answer is right or wrong.If the answer is correct, a prompt would inform you about
   prize money won till that point and the game will continue when the user presses enter key.If the answer turns out to be wrong, the program will inform the user
   about money won and the game will end automatically. 
8. If quit option is chosen, a prompt will ask the user to confirm quitting the game.If the confirmation is provided, the game will end with the money won till 
   previous question. If the confirmation is denied(To take in account accidental button press) the question is printed on the screen once again for user to 
   continue playing. 
9. Two lifelines have been provided which are '50-50' and 'Flip the Question'.
10. If the user decides to avail a lifeline,it can be done through the number keys as displayed on the screen or else if the button has been pressed by mistake 
   then the user has the option to go back and answer the question without using lifeline help.
11. Two intermediate question levels/safepoints have been provided at 5th and 10th question respectively. Losing after a safepoint will take the prize money back
   to the last safepoint instead of it turning to zero.
12. The interface is quite user-friendly and shows 'Invalid output' upon entering any other input other than what the user is prompted for.
13. Any other required information is provided to the user in the program as and when required. 

*******NOTE:Maximum length of user input that is acceptable for the program to run is 999 which can be changed if INPUT_BUFFER variable value is changed.**************
*******NOTE: To compile the c file use the command: gcc -o 2019B4PS0627P_P11.exe 2019B4PS0627P_P11.c                  *************************************************
*******      It will result in a file named 2019B4PS0627P_P11.exe which can be executed using ./2019B4PS0627P_P11.exe *************************************************
*******NOTE: To run the code on windows just uncomment 'system("pause");' which is the second last line of code.*******************************************************
*******NOTE: This program has been tested successfully on Ubuntu virtual machine with Ubuntu 18.04 LTS and Linux OS version 
############################################################
No known limitations of the code
#############################################################
Contributions of the team members:
=>Saksham Mahajan worked on modules 1 and 4 and also helped in module 3 along with debugging and commenting in the program.
=>Vinayak Tyagi worked on modules 2,3 and 5 and also helped in debugging and commenting in the program.
=>Parth Daga worked on module 6 and also helped in debugging and commenting in the program. 
#############################################################