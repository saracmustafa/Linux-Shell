/*
* music.h
*
* The final version of this code has been developed by Mustafa SARAÇ and Musa ÇIBIK as a project
* of Operating System (COMP 304) course. Koç University's code of ethics can be applied to this
* code and liability can not be accepted for any negative situation. Therefore, be careful when
* you get content from here.
*
* Description: Functions required for 'muzik' operation
*
* You can also contact me at this email address: msarac13@ku.edu.tr
*/

#ifndef MUZIK_H_
#define MUZIK_H_

char* getTime(char* time) {

	int iter = 0;

	char* timeToken = strtok(time, ".");
	char* times[2];

	while (timeToken != NULL) {

		times[iter] = (char *)malloc(2);

		strcpy(times[iter], timeToken);
		timeToken = strtok(NULL, ".");

		iter++;
	}

	int hour;
	int min;
	char* _time = (char *)malloc(5);
	char* empty_time = (char *)malloc(5);

	if (times[0] != NULL) {

		if (times[1] != NULL) {

			hour = strtol(times[0], NULL, 10);
			min = strtol(times[1], NULL, 10);

			if ((hour >= 0 && hour <= 24) && (min >= 0 && min <= 60)) {

				strcat(_time, times[1]);
				strcat(_time, " ");
				strcat(_time, times[0]);

			} else {
				printf("Please give a valid time \n");
			}

		} else {
			printf("Please give a valid time \n");
		}
	} else {
		printf("Please give a valid time \n");
	}


	if (strcmp(_time, empty_time) == 0)
		return empty_time;
	else
		return _time;
}

void playSong(char* time, char* song) {

	char cwd[1024];
	char* dir = getcwd(cwd, sizeof(cwd));

	strcat(dir, "/");
	strcat(dir, song);

	FILE* f = fopen("crontab.txt", "a");

	if (f == NULL)
	{
		printf("Error opening crontab file!\n");
	}

	fprintf(f, "%s ", time);
	fprintf(f, "* * * ");
	fprintf(f, "play ");
	fprintf(f, "%s\n", dir);

	fclose(f);

}

void listSong() {

	FILE* f = fopen("crontab.txt", "r");
	char* _line = (char*)malloc(300);
	char* empty = (char *)malloc(300);

	if (f == NULL) { printf("Error opening crontab file!\n"); }

	//read line by line
	while (fgets(_line, 300, f) != NULL) {

		if (strcmp(_line, empty) != 0) {

			char* cpy_line = (char*)malloc(300);
			strcpy(cpy_line, _line);

			char* music_token = strtok(cpy_line, " ");
			int music_iter = 0;
			char* min = (char*)malloc(2);
			char* hr = (char*)malloc(2);
			char* path = (char*)malloc(200);

			while (music_token != NULL) {

				if (music_iter == 0) {
					strcpy(min, music_token);
				}

				if (music_iter == 1) {
					strcpy(hr, music_token);
				}

				if (music_iter == 6) {
					strcpy(path, music_token);
				}

				music_token = strtok(NULL, " ");
				music_iter++;

			}

			char* path_token = strtok(path, "/");
			int path_iter = 0;
			char* music_name = (char*)malloc(100);

			while (path_token != NULL) {

				if (strstr(path_token , ".wav") != NULL) {
					strcpy(music_name, path_token);
				}

				path_token = strtok(NULL, "/");
				path_iter++;

			}

			printf("%s.%s %s", hr, min, music_name );

		}

	}

}

void removeSong(char* time) {

	char* empty = (char *)malloc(5);

	if (strcmp(time, empty) != 0) {

		char* _line = (char*)malloc(300);

		FILE* f = fopen("crontab.txt", "r");

		if (f == NULL)
		{
			printf("Error opening crontab file!\n");
		}

		FILE* f_copy = fopen("crontab_copy.txt", "w");

		if (f_copy == NULL)
		{
			printf("Error opening crontab file!\n");
		}

		//read line by line
		while (fgets(_line, 300, f) != NULL) {

			if (strlen(time) == 4) {

				if (strncmp(_line, time, 4) != 0) {

					fprintf(f_copy, "%s", _line);

				}

			}
			else if (strlen(time) == 5) {

				if (strncmp(_line, time, 5) != 0) {

					fprintf(f_copy, "%s", _line);

				}
			}


		}

		free(_line);

		int success = rename("crontab.txt", "delete.txt");

		if (success != 0)
			printf("An error occurred..\n");

		int _success = rename("crontab_copy.txt", "crontab.txt");

		if (_success != 0)
			printf("An error occurred\n");

		int remove_success = remove("delete.txt");

		if (remove_success != 0)
			printf("An error occurred\n");

		fclose(f_copy);
		fclose(f);

	} else {
		printf("\nPlease specify the time properly!\n");
	}

}

#endif