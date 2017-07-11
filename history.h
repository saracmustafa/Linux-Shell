/*  
* history.h
* 
* The final version of this code has been developed by Mustafa SARAÇ and Musa ÇIBIK as a project
* of Operating System (COMP 304) course. Koç University's code of ethics can be applied to this
* code and liability can not be accepted for any negative situation. Therefore, be careful when
* you get content from here.
*
* Description: Functions required for 'history' operation
*
* You can also contact me at this email address: msarac13@ku.edu.tr
*/

#ifndef HISTORY_H_
#define HISTORY_H_

#define HISTORY_MAX  10
#define CMD_MAX  80

int entries = 0;

void initHistory(char* history[]){
	
	for(int i=0; i < HISTORY_MAX; i++){
		history[i] = (char *)malloc(80);
	}
	
} 

void shiftLeft(char* history[]){
	
	for(int i=1; i <= HISTORY_MAX-1; i++){
		strcpy(history[i-1], history[i]);
	}
		strcpy(history[HISTORY_MAX - 1], "");
	
}

void addCommand(char* history[], char* command){

	entries++;

	if(entries > HISTORY_MAX){
		shiftLeft(history);
		strcpy(history[HISTORY_MAX - 1], command);
	} else {
		strcpy(history[entries - 1], command);
	}

	
}

char* getNext(char* history[], int current){

	char* empty = (char *)malloc(80);

	if(!strcmp(history[current], empty)){
		printf("No commands in the history. \n");
		return NULL;
	}
	
	current++;
	
	// checking whether the next one is empty or not
	// where the history is not full, such as the last
	// command is at index 5.
	if(!strcmp(history[current], empty)){
		current = 0;
	}
	
	// returning the first index if we are at the
	// last index of the history
	if(current > HISTORY_MAX -1)
		current = 0;
	
	return history[current];
}

char* getPrev(char* history[], int current){
	
	char* empty = (char *)malloc(80);

	if(!strcmp(history[current], empty)){
		printf("No commands in the history. \n");
		return NULL;
	}
	
	current --;
	
	// returning the last index if we are at the
	// first index of the history
	if(current < 0 ){
		current = HISTORY_MAX -1;

		while(!strcmp(history[current], empty)){
			current--;
		}
	}
	
	return history[current];
}

void printHistory(char* history[]){

	for(int i=HISTORY_MAX - 1; i >= 0; i--){
		if(!strcmp(history[i], (char *)malloc(80))){
			// nothing to do
		} else {

			if(entries >= HISTORY_MAX ){
				printf("%d %s\n", i+entries-HISTORY_MAX+1 , history[i] );
			}
			else{
				printf("%d %s\n", i+1 , history[i]);
			}
		}
		
	}
}

void clearHistory(char* history[]){

	entries = 0;

	for(int i=0; i<HISTORY_MAX; i++){
		strcpy(history[i], (char *)malloc(80));
	}
}

char* getCommandAtIndex(char* history[], int index){

	char* empty = (char *)malloc(80);

	if(index == 0){
		// any character different from number after '!'

		printf("Please give a valid command. \n");
		return empty;

	} else {
		

		if(entries < HISTORY_MAX){
			// history not full
			
			if(index <= entries){

				return history[--index];
			} else {

				printf("No such command in history. \n");
				return empty;
			}

		} else {

			// history is full 
			
			if(index <= entries - HISTORY_MAX){
				printf("Command is overwritten in history. \n");
				return empty;

			} else if(index > entries){
				printf("No such command in history. \n");
				return empty;

			} else {

				index = index - (entries - HISTORY_MAX + 1);

				return history[index];
			}

		}

	}


}

char* getMostRecent(char* history[]){

	char* empty = (char *)malloc(80);

	int most_recent = 0;

	if(entries > HISTORY_MAX - 1){
		return history[HISTORY_MAX-1];
	} else {

		while(strcmp(history[most_recent], empty) != 0)
			most_recent++;	

		if( most_recent == 0){

			printf("No such command in history. \n");
			return empty;

		} else {

			return history[--most_recent];
		}

	}


}

#endif