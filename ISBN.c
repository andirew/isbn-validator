/**************************************************************\
*                                                              *
* Name: Assign3.1.c                                            *
* Purpose:                                                     *
* This program is an ISBN validator. It will prompt the user   *
* to enter  an ISBN, and it will validate whether  or not it   *
* is a valid entry.                                            *
*                                                              *
*                                                              *
****************************************************************
* MODIFICATION HISTORY:                                        *
* 7/3/2017: Andrew Barsoom - created                           *
\**************************************************************/
#include<stdio.h>
#include<ctype.h>
#include <string.h>
//void remove(char*);
int testISBN(char*);
void validation(char*);
void display(char code[], int divisible);
void retrieve();
void flushKeyBoard();
#define MAX_INPUT 4098 //Max input, so program doesnt bug out and the buffer doesnt mess up.
/********************************************************************\
*                                                                    *
* Name       : main()                                                *
* Parameters :                                                       *
* Returns    : int                                                   *
* Description:                                                       *
* Function controller and calls retrieve function.                   *
**********************************************************************
* MODIFICATION HISTORY                                               *
*                                                                    *
* 7/3/2017 - Andrew Barsoom - Created                                *
*                                                                    *
\********************************************************************/
int main(void)
{

	retrieve(); //call  retrieve function to begin asking user for input
	return 0;
}
/********************************************************************\
*                                                                    *
* Name       : retrieve()                                            *
* Parameters :                                                       *
* Returns    : void                                                  *
* Description:                                                       *
* Asks  user to enter their  ISBN and will call the appropiate       *
* functions to validate the number.                                  *
**********************************************************************
* MODIFICATION HISTORY                                               *
*                                                                    *
* 7/3/2017 - Andrew Barsoom - Created                                *
*                                                                    *
\********************************************************************/
void retrieve() {
	int divisible;
	char code[15];//char  array to  hold  input



	printf("Enter an ISBN to validate:"); //ask user for  input
	if (fgets(code, 15, stdin) == NULL) { //returning what i get from fget, print error if NULL
		printf("Error");
	}
	validation(code); //call validate  function, passing code array
	divisible = testISBN(code);// testISBN to make sure the  math is correct, and  return if it is divisibleby 11 or  not.
	


	display(code,divisible); //pass  the return code for divisible, and the actual array for display  in the display  function.

}
/********************************************************************\
*                                                                    *
* Name       : display()                                             *
* Parameters : char  code[], int divisible                           *
* Returns    : void                                                  *
* Description:                                                       *
*Final display  function that will present the results of the        *
* validation                                                         *
**********************************************************************
* MODIFICATION HISTORY                                               *
*                                                                    *
* 7/3/2017 - Andrew Barsoom - Created                                *
*                                                                    *
\********************************************************************/
void display(char code[], int divisible) {
	size_t ln = strlen(code) - 1; //remove \n from code(fgets adds a \n at the end)
	if (*code && code[ln] == '\n')//Continuation of removing \n from code array
		code[ln] = '\0';

	if (divisible == 1) //if  its divisible by 11, 
		printf("The ISBN %s, is VALID \n", code);
	else
		printf("The ISBN %s, is NOT VALID \n", code);

}
/**************************************************************\
*                                                              *
* Name       : flushKeyBoard()                                 *
* Parameters : none                                            *
* Returns    : none                                            *
* Description:                                                 *
* This module empties the keyboard buffer so that the next     *
* time input is required there is no "old" data still present. *
*                                                              *
****************************************************************
* MODIFICATION HISTORY                                         *
*                                                              *
*  7/3/2017 - Andrew Barsoom - Created                         *
*                                                              *
\**************************************************************/
void flushKeyBoard()
{
	int ch;  // A dummy variable to read data into

	while ((ch = getc(stdin)) != EOF && ch != '\n') //clear input buffer
		;
}
/**************************************************************\
*                                                              *
* Name       : truelength()                                    *
* Parameters : num[]                                           *
* Returns    : int  finallenght                                *
* Description:                                                 *
* This function will remove  any  '-' from  a string to return *
* the true length of the  input                                *
*                                                              *
****************************************************************
* MODIFICATION HISTORY                                         *
*                                                              *
*  7/3/2017 - Andrew Barsoom - Created                         *
*                                                              *
\**************************************************************/
int truelength(char num[]) {
	int finallength = 0; //initialize length variable
	int i; //initialize  loop variable
	size_t len = strlen(num) -1; //get unofficial total  length  for char  array
	for (i = 0; i < len; i++){//This  will loop and increase finallength  by  1  only  if  current number  cycled is not '-'
	
				if (num[i] != '-') {
					 finallength += 1;
				}
			
		
}
	return finallength;
}
/**************************************************************\
*                                                              *
* Name       : validation()                                    *
* Parameters : num[]                                           *
* Returns    : void                                            *
* Description:                                                 *
* This the main validation function, it will confirm that      *
* the inputs match the requirments. *
*                                                              *
****************************************************************
* MODIFICATION HISTORY                                         *
*                                                              *
*  7/3/2017 - Andrew Barsoom - Created                         *
*                                                              *
\**************************************************************/
void validation(char num[]) {

	int loop = 0;
	int i;
	
	//Input validation function
	size_t len = strlen(num) - 1; //return total length (including -)
	int length = truelength(num); //truelength is a function that returns the TRUE length of a input, minus the '-' 
	while (loop == 0) { 
		for (i = 0; i < len; i++) //This while loop will act as the 'check' for every single digit entry. it will loop through each input and validate it individually.
		{			

			//This block of code will ensure that X is only present as the LAST entry, and that the proper requirments are met.
			//--------------------------------------------------------------------------------------------------------------------------
					if (num[i] != '-') { // Do not show error message if string contains a hyphen
						if (num[i] != 'X' || num[i] != 'x') { //Do not show error message if string contains a hypen
							if (num[i + 1] != num[len]) {		//Do not show error message if the last digit is X
								while (!(isdigit(num[i]))) { //if the character is not a digit, display an error mesage.
									printf("Invalid character entered, please re-enter: "); //Ask for correct value
									if (fgets(num, MAX_INPUT, stdin) == NULL) {
										printf("Error");
									}
									length = truelength(num); // Update the length to the new input.
									loop = 0;
								}
							}
						}
						while ((length != 10 && isdigit(num[i]) ) || length == 0) { //check if value is below 0, and print for another number.

							printf("Invalid data entered, too few/too many digits, please re-enter: "); //checks true length(minues hyphens)
							if (fgets(num, 20, stdin) == NULL) {
								printf("Error");
							}
							length = truelength(num);
							//len = strlen(num) - 1;
							loop = 0; //keep looping
						}
			}
			if ((isdigit(num[i]))) { // If current digit is valid
				loop = 2;
			}
			len = strlen(num) - 1;
		}

	}
	
}
/**************************************************************\
*                                                              *
* Name       : testISBN()                                      *
* Parameters : code[]                                          *
* Returns    : int                                             *
* Description:                                                 *
* This function will calculate all the digits provided to see  *
* if the inputs are a valid ISBN or not.                       *
*                                                              *
****************************************************************
* MODIFICATION HISTORY                                         *
*                                                              *
*  7/3/2017 - Andrew Barsoom - Created                         *
*                                                              *
\**************************************************************/
int testISBN(char code[])
{
	int i; // Variable for lopo
	int sum = 0; //variable to hold sum total
	int weight = 10; //variable for current digit weight
	int chVal = 0; // variable to hold current digit
	size_t len = strlen(code) - 1;
	for (i = 0; i<len; i++)
	{
		if ((i == (len - 1)) && (code[i] == 'x' || code[i] == 'X'))//If current number is 10 or X, assign the chvalue to be 10.
		{
			chVal = 10;
		}
		else
		{
			if (code[i] != '-') { // If a - is detected, set the chval to 0
				chVal = code[i] - '0';
			}
		}
	
		if (code[i] == '-') { // increase weight by 1 even if a - is detected.
			weight++;
		}

 		sum += chVal * weight; // accumlate the sum, multiplied by the weight.
		chVal = 0; //reset chVal
		weight--; 
	}
	return (sum % 11) == 0; //return the Modulus of the sum.
}
