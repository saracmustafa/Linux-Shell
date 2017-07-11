/*
* codesearch.h
*
* The final version of this code has been developed by Mustafa SARAÇ and Musa ÇIBIK as a project
* of Operating System (COMP 304) course. Koç University's code of ethics can be applied to this
* code and liability can not be accepted for any negative situation. Therefore, be careful when
* you get content from here.
*
* Description: Functions required for 'codesearch' operation
*
* You can also contact me at this email address: msarac13@ku.edu.tr
*/

#ifndef CODESEARCH_H_
#define CODESEARCH_H_

int isValidCode(char* code) {

	if (code[0] == '\0') {
		return 0;
	}

	if (code[1] == '\0' && code[0] == '\"') {

		return 0;
	}
	int i = 0;

	while (code[i] != '\0') {

		i++;
	}

	if (code[i - 1] == '\"' && code[0] == '\"' ) {

		return 1;
	}

	else {
		return 0;
	}

}

char* removeQuoCode(char* code) {

	char* empty = (char*)malloc(500);
	char* cpy = (char*)malloc(500);
	strcpy(cpy, code);

	if (isValidCode(cpy) ) {
		int i = 0;

		while (cpy[i] != '\0') {
			i++;
		}

		cpy[0] = ' ';
		cpy[i - 1] = ' ';

		return cpy;

	}

	else {
		printf("Please give a valid command to search. \n");
		return empty;
	}
}

char* codeSearch(char* code, int rec) {

	char* final_code = (char*)malloc(500);
	char* empty = (char*)malloc(500);


	if (strcmp(removeQuoCode(code), empty) == 0) {
		return empty;
	}

	else {

		char* path = (char*) malloc(200);
		if (rec == 1) {

			strcat(final_code, "grep -rns " );
			strcat(final_code, removeQuoCode(code));
			strcat(final_code, " --include \"*.c\" --include \"*.C\"  --include \"*.h\"  --include \"*.H\"  --include \"*.cpp\" --include \"*.c++\" ");
			//*.C *.h *.H *.cpp *.c++

		}
		else {
			strcat(final_code, "grep -ns " );
			strcat(final_code, removeQuoCode(code));
			strcat(final_code, " *.c *.C *.h *.H *.cpp *.c++ ");
		}

		if (rec == 1) {

			strcat(final_code, " | awk -F: \'{print $2 \": .\" $1 \" -> \" $3 }\' | tr -s [:space:] ");
		}

		else {
			strcat(final_code, " | awk -F: \'{print $2 \": ./\" $1 \" -> \" $3 }\' | tr -s [:space:] ");
		}



		return final_code;
	}
}

#endif