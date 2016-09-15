#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef enum {FALSE, TRUE} Bool;

void start();
void generateAccounts();
void validatePIN();
Bool processCommand();
void depositFunds();
void withdrawFunds();
void queryFunds();
void transferFunds();
void cancel();



enum {SAVINGS, CHECKING};

int currentAccount; 

struct {
	int accountNumber;
	float balance;
} savings, checking;

int PIN;

int main(void) {

	generateAccounts();

	printf("\n======================================\n");
	printf("PIN: %d\n", PIN);
	printf("Checking Account Number: %d\n", checking.accountNumber);
	printf("Savings Account Number: %d", savings.accountNumber);
	printf("\n======================================\n\n");
	
	start();
	

	return 0;
}

void start() {
	
	validatePIN();

	while (TRUE) {

		printf("Enter one of the following commands:\n");
		printf("Action:\t\tCommand:\n");
		printf("Deposit\t\tD\n");
		printf("Withdraw\tW\n");
		printf("Query\t\tQ\n");
		printf("Transfer\tT\n");
		printf("Cancel\t\tC\n\n");
	
		while (!processCommand()) {}
	
	}

}

void generateAccounts() {

	srand(time(NULL));

	savings.accountNumber = (int)((rand() % 90000) + 10000);
	savings.balance = (double)(rand() % 1000000);
	checking.accountNumber = (int)((rand() % 90000) + 10000);
	checking.balance = (double)(rand() % 100000);

	PIN = (int)((rand() % 9000)+1000);

}

void validatePIN() {

	int i = 0;
	for (; i < 3; i++) {

		int inputPIN, inputAccountNum;

		printf("Enter your PIN for this bank: ");
		scanf("%d", &inputPIN);

		if (inputPIN != PIN) {
			printf("Incorrect PIN\n");
			continue;
		}

		printf("Enter an account number: ");
		scanf("%d", &inputAccountNum);

		if (inputAccountNum == savings.accountNumber) {
			printf("SUCCESS...\n\n");
			currentAccount = SAVINGS;
			return;
		} else if (inputAccountNum == checking.accountNumber) {
			printf("SUCCESS...\n\n");
			currentAccount = CHECKING;
			return;
		} else {
			printf("Incorrect account number.\n\n");
		}

	}
	printf("Transaction Cancelled.\n\n");
	exit(0);

}

Bool processCommand() {

	char command;
	printf("> ");
	scanf(" %c", &command);

	switch (command) {

		case 'D': depositFunds(); break;
		case 'W': withdrawFunds(); break;
		case 'Q': queryFunds(); break;
		case 'T': transferFunds(); break;
		case 'C': cancel(); break;

		default: printf("Invalid Command.\n"); return FALSE;
	}

	return TRUE;

}

void depositFunds() {


	float amount;

	printf("Enter the amount to deposit into account %d: ", (currentAccount == SAVINGS) ? savings.accountNumber : checking.accountNumber);
	scanf("%f", &amount);

	if (currentAccount == SAVINGS) {
		savings.balance += amount;
	} else {
		checking.balance += amount;
	}

	int accNum = (currentAccount == SAVINGS) ? savings.accountNumber : checking.accountNumber;
	float accBal = (currentAccount == SAVINGS) ? savings.balance : checking.balance;
	printf("New balance for account %d: %.2f\n\n", accNum, accBal);

}

void withdrawFunds() {


	float amount;

	printf("Enter the amount to withdraw from account %d: ", (currentAccount == SAVINGS) ? savings.accountNumber : checking.accountNumber);
	scanf("%f", &amount);

	float balance = (currentAccount == SAVINGS) ? savings.balance : checking.balance;
	if (amount > balance) {
		printf("Insufficient Funds. Sorry, get a job.\n\n");
		return;
	} else {
		if (currentAccount == SAVINGS) {
			savings.balance -= amount;

		} else {
			checking.balance -= amount;
		}
		int accNum = (currentAccount == SAVINGS) ? savings.accountNumber : checking.accountNumber;
		float accBal = (currentAccount == SAVINGS) ? savings.balance : checking.balance;
		printf("New balance for account %d: %.2f\n\n", accNum, accBal);
	}

}

void queryFunds() {

	int accNum = (currentAccount == SAVINGS) ? savings.accountNumber : checking.accountNumber;
	float accBal = (currentAccount == SAVINGS) ? savings.balance : checking.balance;
	printf("Balance for account %d: %.2f\n", accNum, accBal);
	int accNum2 = (currentAccount != SAVINGS) ? savings.accountNumber : checking.accountNumber;
	float accBal2 = (currentAccount != SAVINGS) ? savings.balance : checking.balance;
	printf("Balance for account %d: %.2f\n\n", accNum2, accBal2);

}

void transferFunds() {

	int accNum;
	float amount;
	printf("Enter the account number that you want to transfer to: ");
	scanf("%d", &accNum);
	printf("Enter the amount that you want to transfer: ");
	scanf("%f", &amount);


	float balance = (currentAccount == SAVINGS) ? savings.balance : checking.balance;
	if (amount > balance) {
		printf("Insufficient Funds. Sorry, get a job.\n");
		return;
	}
	if (accNum != savings.accountNumber && accNum != checking.accountNumber) {
		printf("Invalid account number.\n");
		return;
	}
	if (currentAccount == SAVINGS) {
		savings.balance -= amount;
	} else {
		checking.balance -= amount;
	}

	if (accNum == savings.accountNumber) {
		savings.balance += amount;
		printf("Balance for account %d: %.2f\n", accNum, savings.balance);
		printf("Balance for account %d: %.2f\n\n", checking.accountNumber, checking.balance);
	} else if (accNum == checking.accountNumber) {
		checking.balance += amount;
		printf("Balance for account %d: %.2f\n", accNum, checking.balance);
		printf("Balance for account %d: %.2f\n\n", savings.accountNumber, savings.balance);
	}

}

void cancel() {
	printf("Transaction Cancelled.\n\n");
	exit(0);
}

















