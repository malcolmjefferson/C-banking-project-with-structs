#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Will allow the user to input an amount of money that they want to add to their bank account
//Will also allow the user to query for how much money is in their bank account
//Want to turn into a very very secure banking console app... We'll see how that goes.

//want to start the user at a menu and make them enter their name. Use that to search already created acct. Go from there.
typedef struct {
	int balance;
	int deposit;
	char name[30];
	unsigned long acctNum;
} BankAccount;

void DepositFunc(BankAccount * acct, int * pdeposit);
void CheckBalance(BankAccount * acct);
BankAccount * FindUser(BankAccount * acct);

BankAccount * FindUser(BankAccount * acct) {
	//This is where we will look through the accounts file and find the user and their information
	//Everytime I find a goddamn parsing algorithm, someone says that its wrong. I'll come back to this later.
	/* FILE* stream = fopen("accounts.txt","r");
	char line[1024];
	while (fgets(line, 1024, stream)) {
		char *tmp;
		tmp = strtok (line,",");
		
	} */
}

//Function that will handle deposits
void DepositFunc(BankAccount * acct, int * pdeposit) {
	printf("\nEnter the amount that you want to deposit: ");
	fflush(stdout);
	scanf("%d", pdeposit);
	getchar();
	//works the same as adding to the actual value of balance because *balance is a dereferenced pointer to address
	//where actual balance variable is stored
	acct->balance += acct->deposit;
	printf("\n%d has been deposited into your account.", acct->deposit);
	fflush(stdout);
}

//Function that will handle checking of the balance
void CheckBalance(BankAccount * acct) {
	printf("\nYour balance is: %d", acct->balance);
	fflush(stdout);
}

int main() {
	//allocate space for BankAccount pointer
	BankAccount * acct = malloc(sizeof(BankAccount));
	acct->balance = 0;
	acct->deposit = 0;
	//char array to hold choice of user in while loop.
	char userChoice[20];
	//pointer for deposit, will be used to pass by reference
	int * pdeposit = &acct->deposit;
	//ask for user name
	printf("Enter your name: ");
	fflush(stdout);
	fgets(acct->name,sizeof(acct->name),stdin);
	getchar();
	fflush(stdout);

	//search file for name. Retrieve balance and acct number
	BankAccount * acctInfo = FindUser(acct);

	/* //initial query for name
	printf("Enter your name: ");
	//flush stdout buffer so no strings bump into each other
	fflush(stdout);
	//get the input
	fgets(acct->name, sizeof(acct->name), stdin);
	//gets the newline
	getchar();
	//using the current time as seed, generate random number for account number
	srand(time(0)); 
	acct->acctNum = rand();
	fflush(stdout);
	//initial deposit
	printf("Enter the amount that you want to deposit: ");
	fflush(stdout);
	scanf("%d", pdeposit);
	getchar();
	acct->balance += acct->deposit;
	printf("\n%d has been deposited into your account.\n", acct->deposit);
	fflush(stdout); */

	//will run as long as the user doesn't quit
	while (1)
	{
		printf("\nWould you like to make a deposit, check your balance, or quit? ");
		fflush(stdout);
		//gets user input from stdin
		fgets(userChoice, sizeof(userChoice), stdin);
		//removes the newline from the end of the string and replaces it with a null character
		userChoice[strlen(userChoice) - 1] = '\0';
		//compares the strings, if eq 0 then they are the same
		if (strncmp(userChoice, "make deposit", sizeof(userChoice)) == 0) {
			DepositFunc(acct,pdeposit);
		}
		else if (strncmp(userChoice, "check balance", sizeof(userChoice)) == 0) {
			CheckBalance(acct);
			printf("\n%d", acct->balance);
		}
		else if (strncmp(userChoice, "quit", sizeof(userChoice)) == 0) {
			free(acct);
			return 0;
		}
		else {
			printf("Try again...\n");
			fflush(stdout);
		}
	}
	return 0;
}