#include <stdio.h>

int main()
{
	char D[2], M[2], Y[4], name[100]; // char string
	
	printf("Please enter your birthdate (DDMMYYYY): ");
	scanf("%2s%2s%4s", D, M, Y);
	
	printf("Please enter your name : ");
	scanf("%100s", name); // 100 is used to specify maximum size of string
	
	// first rule
	char first_digit  = D[1];
	
	// second rule
	// % (modulo) is used here to extract last digit from any integer (including single integer)
	// example, 764, we module with 10, we will get last digit, which is 4
	int second_digit = ((D[0] - '0') * (Y[2] - '0') * (Y[3] - '0')) % 10;
	
	// third rule
	int third_digit = 2; // default value
	
	if(name[0] == 'A' || name[0] == 'U')
		third_digit = 0;
		
	else if(name[0] == 'I' || name[0] == 'E')
		third_digit = 1;
		
	printf("\nYour secret code : %c%d%d\n\n", first_digit, second_digit, third_digit);
}

