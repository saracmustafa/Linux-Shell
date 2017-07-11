/*
* xox.h
*
* The final version of this code has been developed by Mustafa SARAÇ and Musa ÇIBIK as a project
* of Operating System (COMP 304) course. Koç University's code of ethics can be applied to this
* code and liability can not be accepted for any negative situation. Therefore, be careful when
* you get content from here.
*
* Description: Functions required for 'xox' operation
*
* You can also contact me at this email address: msarac13@ku.edu.tr
*/

#ifndef XOX_H_
#define XOX_H_

#define ROW_SIZE 3
#define COLUMN_SIZE 3

typedef int bool;
#define true 1
#define false 0

int counter;
int zeros[3] = {0, 0, 0};

void initGameTable(int table[ROW_SIZE][COLUMN_SIZE]) {
	counter = 0; // even values of counter is o's turn.
	// odd values of counter is x's turn.

	table = malloc(ROW_SIZE * sizeof * table + (ROW_SIZE * (COLUMN_SIZE * sizeof **table)));

	for (int i = 0; i < ROW_SIZE; i++)
		for (int j = 0; j < COLUMN_SIZE; j++)
			table[i][j] = 0;

}

void clearGameTable(int table[ROW_SIZE][COLUMN_SIZE]) {
	counter = 0;

	for (int i = 0; i < ROW_SIZE; i++)
		for (int j = 0; j < COLUMN_SIZE; j++)
			table[i][j] = 0;

}

void introGameTable() {
	printf("\n\nWelcome to XOX Game!\n\n");
	printf("The player who succeeds in placing three of their marks in a \nhorizontal, vertical, or diagonal row wins the game. \n");
	printf("Please please ");
	printf("IMPORTANT: Please play your turn as typing like the following:\n 'xox 1.2' or 'xox 0.1' \n");
	printf("Game is starting now..\n\n");
	printf("It's x's turn.. \n\n");
}

void startNewGame(int table[ROW_SIZE][COLUMN_SIZE]) {

	clearGameTable(table);
	introGameTable();

}

char getCharacter(int i) {
	char c = ' ';

	if (i == 1)
		c = 'x';
	else if (i == 2)
		c = 'o';
	else
		c = ' ';

	return c;
}

void printGameTable(int table[ROW_SIZE][COLUMN_SIZE]) {
	printf("\n   0   1   2 ");
	printf("\n0  %c | %c | %c\n", getCharacter(table[0][0]), getCharacter(table[0][1]), getCharacter(table[0][2]));
	printf("  -----------\n");
	printf("1  %c | %c | %c\n", getCharacter(table[1][0]), getCharacter(table[1][1]), getCharacter(table[1][2]));
	printf("  -----------\n");
	printf("2  %c | %c | %c\n\n", getCharacter(table[2][0]), getCharacter(table[2][1]), getCharacter(table[2][2]));
}

int whosTurn(int count) {
	// finding which player's turn
	if (count % 2 == 0)
		return 0; // o's turn
	else
		return 1; // x's turn

}

bool checkInput(char* input) {
	bool result = false;

	if (input[0] != '\0') {
		if (input[1] != '\0') {
			if (input[2] != '\0') {
				if (input[3] == '\0') {
					result = true;
				}
			}
		}
	}

	return result;
}

bool checkCoordinate(int table[ROW_SIZE][COLUMN_SIZE], int i, int j) {
	bool result = false;

	if ((i >= 0 && i <= 2) && (j >= 0 && j <= 2)) {
		if (table[i][j] == 0)
			result = true;
	} else {
		printf("\nPlease give a valid coordinate \n");
	}

	return result;
}

void addCoordinateValue(int table[ROW_SIZE][COLUMN_SIZE], char* coordinate) {
	int i;
	int j;

	if (checkInput(coordinate) != false) {
		i = coordinate[0] - '0';
		j = coordinate[2] - '0';

		if (checkCoordinate(table, i, j) != false) {

			int playerTurn = whosTurn(counter);

			if (playerTurn == 0) {
				table[i][j] = 1;
			} else if (playerTurn == 1) {
				table[i][j] = 2;
			}

			counter++;

		} else {
			printf("\nThere's already a mark. Please put your mark to another place\n");
		}

	} else {
		printf("\nPlease give your input as stated.\n");
	}

}

bool isWin(int table[ROW_SIZE][COLUMN_SIZE]) {
	bool result = false;

	for (int i = 0; i < ROW_SIZE; i++) {

		// checking rows
		if ((table[i][0] == table[i][1]) && (table[i][0] == table[i][2]) && table[i][0] != 0)
			result = true;

		// checking columns
		if ((table[0][i] == table[1][i]) && (table[0][i] == table[2][i]) && table[0][i] != 0)
			result = true;

	}

	// checking diagonals
	if ((table[0][0] == table[1][1]) && (table[0][0] == table[2][2]) && table[0][0] != 0)
		result = true;

	if ((table[0][2] == table[1][1]) && (table[0][2] == table[2][0]) && table[0][2] != 0)
		result = true;

	return result;
}

bool isTie(int counter) {
	if (counter == 9)
		return true;
	else
		return false;
}

void playGame(int table[ROW_SIZE][COLUMN_SIZE], char* coordinate) {
	int playerTurn;

	addCoordinateValue(table, coordinate);

	if (isWin(table) == true) {

		playerTurn = whosTurn(--counter);

		if (playerTurn == 0) {

			printf("\nCongratulations! 'x' wins the game!\n\n");
			printGameTable(table);

			clearGameTable(table);

		} else if (playerTurn == 1) {

			printf("\nCongratulations! 'o' wins the game!\n\n");
			printGameTable(table);

			clearGameTable(table);

		}

	} else {
		// continuing the game

		playerTurn = whosTurn(counter);
		printGameTable(table);

		if (isTie(counter)) {
			printf("\nOoh! It's a tie!\n\nIn order to start a new game type 'xox start'\n\n");
			clearGameTable(table);
		} else {
			if (playerTurn == 0)
				printf("\nIt's x's turn.. \n\n");
			else if (playerTurn == 1)
				printf("\nIt's o's turn.. \n\n");
		}


	}

}

#endif