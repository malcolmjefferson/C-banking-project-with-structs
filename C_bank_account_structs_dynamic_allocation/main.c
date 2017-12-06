#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Will allow the user to input an amount of money that they want to add to their bank account
//Will also allow the user to query for how much money is in their bank account
//Want to turn into a very very secure banking console app... We'll see how that goes.

typedef struct {
	int balance;
	int deposit;
} BankAccount;

typedef struct {
	char name[15];
	char userChoice[20];
} Person;

void DepositFunc(BankAccount * acct, int * pdeposit);
void CheckBalance(BankAccount * acct);

//Function that will handle deposits
void DepositFunc(BankAccount * acct, int * pdeposit) {
	printf("\nEnter the amount that you want to deposit: ");
	fflush(stdout);
	scanf_s("%d", pdeposit);
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
	//allocate space for BankAccount pointer and Person pointer
	BankAccount * acct = malloc(sizeof(BankAccount));
	acct->balance = 0;
	acct->deposit = 0;
	Person * myperson = malloc(sizeof(Person));

	//pointer for deposit, will be used to pass by reference
	int * pdeposit = &acct->deposit;

	//initial query and deposit
	printf("Enter the amount that you want to deposit: ");
	//flush stdout buffer so no strings bump into each other
	fflush(stdout);
	scanf_s("%d", pdeposit);
	//getchar to capture the newline on the end from pressing the enter key
	getchar();
	acct->balance += acct->deposit;
	printf("\n%d has been deposited into your account.\n", acct->deposit);
	fflush(stdout);

	//will run as long as the user doesn't quit
	while (1)
	{
		printf("\nWould you like to make another deposit, check your balance, or quit? ");
		fflush(stdout);
		//gets user input from stdin
		fgets(myperson->userChoice, sizeof(myperson->userChoice), stdin);
		//removes the newline from the end of the string and replaces it with a null character
		myperson->userChoice[strlen(myperson->userChoice) - 1] = '\0';
		//compares the strings, if eq 0 then they are the same
		if (strncmp(myperson->userChoice, "make deposit", sizeof(myperson->userChoice)) == 0) {
			DepositFunc(acct,pdeposit);
		}
		else if (strncmp(myperson->userChoice, "check balance", sizeof(myperson->userChoice)) == 0) {
			CheckBalance(acct);
			printf("\n%d", acct->balance);
		}
		else if (strncmp(myperson->userChoice, "quit", sizeof(myperson->userChoice)) == 0) {
			free(acct);
			free(myperson);
			return 0;
		}
		else {
			printf("Try again...\n");
			fflush(stdout);
		}
	}
	return 0;
}