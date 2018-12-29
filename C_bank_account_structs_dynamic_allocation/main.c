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
void Menu(BankAccount * acct);
BankAccount * FindUser(BankAccount * acct);

BankAccount * FindUser(BankAccount * acct) {
	//This is where we will look through the accounts file and find the user and their information
	//Everytime I find a goddamn parsing algorithm, someone says that its wrong. I'll come back to this later.
	FILE* stream = fopen("accounts.txt","r");
	char line[1024];
	char * tmp;
	while (fgets(line, 1024, stream)) {
		//gets the name and stores it in tmp
		tmp = strtok(line,",");
		//if name is the same as the name entered, get the acct number and balance
		if (strncmp(tmp,acct->name,sizeof(tmp)) == 0) {
			acct->acctNum = strtok(0,",");
			acct->balance = strtok(0,",");
			return acct;
		}
		
	}
	fclose(stream);
	//return the acct if not found. Check for acct num when returned. If 0, invalid name.
	return acct;
}

//Function that will handle deposits
void DepositFunc(BankAccount * acct, int * pdeposit) {
	FILE* updateBalance = fopen("accounts.txt","w");
	char * tmp;
	char line[1024];
	printf("\nEnter the amount that you want to deposit: ");
	fflush(stdout);
	scanf("%d", pdeposit);
	getchar();
	//works the same as adding to the actual value of balance because *balance is a dereferenced pointer to address
	//where actual balance variable is stored
	//when pdeposit is changed, so is acct->deposit, because pdeposit points to the address of acct->deposit
	acct->balance += acct->deposit;
	//loop through the file until correct account is found. Update the balance.
	while (fgets(line, 1024, updateBalance)) {
		tmp = strtok(line,",");
		//if name is the same as the name entered, will need to replace the line. Might use sed utility on linux and write a bash script to clone everything in file except old balance.
		//then I can just write the new entry in the file and it will basically be the same if I delete the old file.
		if (strncmp(tmp, acct->name, sizeof(tmp)) == 0) {
			//
			tmp = strtok(line,",");
			tmp = strtok(line,",");	
		}
	}
	printf("\n%d has been deposited into your account.", acct->deposit);
	fflush(stdout);
}

//Function that will handle checking of the balance
void CheckBalance(BankAccount * acct) {
	printf("\nYour balance is: %d", acct->balance);
	fflush(stdout);
}

//This is where the menu options will be.
//will run as long as the user doesn't quit
void menu(BankAccount * acct) {
	//char array to hold choice of user in while loop.
	char userChoice[20];
	//pointer for deposit, will be used to pass by reference. points to the address of acct->deposit
	int * pdeposit = &acct->deposit;
	while (1)
	{
		printf("\nWould you like to make a deposit, check your balance, or quit? ");
		fflush(stdout);
		//gets user input from stdin
		fgets(userChoice, sizeof(userChoice), stdin);
		//removes the newline from the end of the string and replaces it with a null character
		userChoice[strcspn(userChoice,"\n")] = 0;
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
}

int main() {
	//allocate space for BankAccount pointer
	BankAccount * acct = malloc(sizeof(BankAccount));
	acct->balance = 0;
	acct->deposit = 0;
	acct->acctNum = 0;
	//ask for user name
	printf("Enter your name: ");
	fflush(stdout);
	fgets(acct->name,sizeof(acct->name),stdin);
	fflush(stdout);
	//trim the newline from the end of name
	acct->name[strcspn(acct->name, "\n")] = 0;

	//search file for name. Retrieve balance and acct number
	BankAccount * acctInfo = FindUser(acct);
	//check if account name was valid, if not, try again.
	if (acctInfo->acctNum == 0) {
		printf("Invalid name, please try again...");
		while(acctInfo ->acctNum == 0) {
			//ask for user name
			printf("Enter your name: ");
			fflush(stdout);
			fgets(acct->name,sizeof(acct->name),stdin);
			fflush(stdout);
			//trim the newline from the end of name
			acct->name[strcspn(acct->name, "\n")] = 0;
			acctInfo = FindUser(acct);
		}
	}
	else {
		//print out user info
		printf("%s\n",acctInfo->name);
		fflush(stdout);
		printf("%s\n",acctInfo->acctNum);
		fflush(stdout);
		printf("%s\n",acctInfo->balance);
		fflush(stdout);
	}

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
	return 0;
}