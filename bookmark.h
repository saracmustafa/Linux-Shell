/*
* bookmark.h
*
* The final version of this code has been developed by Mustafa SARAÇ and Musa ÇIBIK as a project
* of Operating System (COMP 304) course. Koç University's code of ethics can be applied to this
* code and liability can not be accepted for any negative situation. Therefore, be careful when
* you get content from here.
*
* Description: Functions required for 'bookmark' operation
*
* You can also contact me at this email address: msarac13@ku.edu.tr
*/

#ifndef BOOKMARK_H_
#define BOOKMARK_H_

#define MAX_NUM_BOOKMARK  100
#define BOOKMARK_MAX  100

typedef int bool;
#define true 1
#define false 0

int entries_bookmark = 0;

void initBookmarks(char* bookmarks[]) {

	for (int i = 0; i < MAX_NUM_BOOKMARK; i++) {
		bookmarks[i] = (char *)malloc(BOOKMARK_MAX);
	}

}

void shiftLeftBookmark(char* bookmarks[], int  index) {
	char* empty = (char *)malloc(BOOKMARK_MAX);
	int i = index;

	while (strcmp(bookmarks[i], empty) != 0 ) {
		strcpy(bookmarks[i], bookmarks[i + 1]);
		i++;
	}

}

void clearBookmarks(char* bookmarks[]) {
	entries_bookmark = 0;

	for (int i = 0; i < MAX_NUM_BOOKMARK; i++) {
		strcpy(bookmarks[i], (char *)malloc(BOOKMARK_MAX));
	}
}

void deleteBookmark(char* bookmarks[], char*  index) {
	char* empty = (char *)malloc(BOOKMARK_MAX);

	if (strcmp(index, "*") == 0) {
		clearBookmarks(bookmarks);
	} else if (strcmp(index, "0") == 0) {

		if (strcmp(bookmarks[0], empty) == 0 ) {
			printf("Nothing to delete at index: 0\n");
		} else {
			shiftLeftBookmark(bookmarks, 0);
			entries_bookmark--;
		}

	} else {

		int ind = strtol(index, NULL, 10);

		if (ind == 0) {
			printf("Please enter a valid index to delete. \n");
		} else {
			if (strcmp(bookmarks[ind], empty) == 0 ) {
				printf("Nothing to delete at index: %d\n", ind);
			} else {
				shiftLeftBookmark(bookmarks, ind);
				entries_bookmark--;
			}
		}

	}

}

bool isString(char* bookmark) {

	if (bookmark[0] == '\0') { return false; }

	if (bookmark[1] == '\0' && bookmark[0] == '\"') { return false; }

	int i = 0;

	while (bookmark[i] != '\0') {	i++; }

	if (bookmark[i - 1] == '\"' && bookmark[0] == '\"' ) {
		return true;
	} else {
		return false;
	}

}

void addBookmark(char* bookmarks[], char* bookmark) {

	if (isString(bookmark)) {
		strcpy(bookmarks[entries_bookmark], bookmark);
		entries_bookmark++;
	} else {
		printf("Please type the bookmark you want to add in quatation marks \"example\"\n");
	}

}

void printBookmarks(char* bookmarks[]) {
	int i = 0;
	char* empty = (char *)malloc(BOOKMARK_MAX);

	while (strcmp(bookmarks[i], empty) != 0 ) {
		printf("\t%d %s\n", i, bookmarks[i]);
		i++;
	}
}

char* removeQuo(char* bookmark) {
	int i = 0;

	while (bookmark[i] != '\0') { i++; }

	bookmark[0] = ' ';
	bookmark[i - 1] = ' ';

	return bookmark;
}


char* getBookmarkAtInd(char* bookmarks[], char* index) {
	char* empty = (char *)malloc(BOOKMARK_MAX);

	if (strcmp(index, "0") == 0) {
		if (strcmp(bookmarks[0], empty) == 0 ) {
			printf("No such entry in the bookmarks at index: 0\n");
			return empty;
		} else {
			char* bookmark = (char *)malloc(BOOKMARK_MAX);
			bookmark = removeQuo(bookmarks[0]);
			return bookmark;
		}

	} else {
		int ind = strtol(index, NULL, 10);

		if (ind == 0) {
			printf("Please enter a valid index to execute. \n");
			return empty;
		} else {
			if (strcmp(bookmarks[ind], empty) == 0 ) {
				printf("No such entry in the bookmarks at index: %d \n", ind);
				return empty;
			} else {
				char* bookmark = (char *)malloc(BOOKMARK_MAX);
				bookmark = removeQuo(bookmarks[ind]);
				return bookmark;
			}
		}

	}

}

#endif