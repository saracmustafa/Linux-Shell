/*
* myshell.c
*
* The final version of this code has been developed by Mustafa SARAÇ and Musa ÇIBIK as a project
* of Operating System (COMP 304) course. Koç University's code of ethics can be applied to this
* code and liability can not be accepted for any negative situation. Therefore, be careful when
* you get content from here.
*
* Description: Main program
*
* You can also contact me at this email address: msarac13@ku.edu.tr
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include "history.h"
#include "bookmark.h"
#include "music.h"
#include "codesearch.h"
#include "xox.h"

#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */

char* history[10];
char* bookmarks[MAX_NUM_BOOKMARK];
int gameTable[ROW_SIZE][COLUMN_SIZE];

int parseCommand(char inputBuffer[], char *args[], int *background);

int main(void) {

  char inputBuffer[MAX_LINE];           /* buffer to hold the command entered */
  int background;                       /* equals 1 if a command is followed by '&' */
  char *args[MAX_LINE / 2 + 1];       /* command line (of 80) has max of 40 arguments */
  pid_t child;                /* process id of the child process */
  int status;               /* result from execv system call*/
  int shouldrun = 1;

  int i, upper;

  char* possiblePaths = getenv("PATH");
  char* pathsToken;

  initHistory(history);
  initBookmarks(bookmarks);
  initGameTable(gameTable);

  while (shouldrun) /* Program terminates normally inside setup */
  {

    background = 0;

    shouldrun = parseCommand(inputBuffer, args, &background);     /* get next command */

    if (strncmp(inputBuffer, "exit", 4) == 0)
      shouldrun = 0;     /* Exiting from myshell*/

    if (shouldrun) {

      // After reading user input:

      if (args[0] !=  NULL) {

CHECK_AGAIN:

        if (strcmp(args[0] , "cd") == 0) {

          if (args[1] != NULL) {

            if (chdir(args[1]) == 0) {
              char cwd[1024];
              char* dir = getcwd(cwd, 1024);
              printf("%s>\n", dir);
            } else {
              printf("%s is not a valid directory. Please enter a valid directory.\n", args[1]);
            }

          }

        } // End of CD

        else if (strcmp(args[0] , "codesearch") == 0) {

          char* code_cmd = (char*)malloc(500);
          char* empty = (char*)malloc(500);

          if (strstr(args[1], "-r") != NULL) {

            strcpy(code_cmd, codeSearch(args[2], 1));

            if (strcmp(code_cmd , empty) != 0) {

              system(code_cmd);

            } else {

              int iter = 0;

              while (args[iter] != NULL) {
                args[iter] = (char*)malloc(80);
                iter++;
              }

            }

          } else {

            strcpy(code_cmd, codeSearch(args[1], 0));

            if (strcmp(code_cmd , empty) != 0) {

              system(code_cmd);

            } else {

              int iter = 0;

              while (args[iter] != NULL) {
                args[iter] = (char*)malloc(80);
                iter++;
              }

            }


          }

        }   // End of CODESEARCH

        else if (strcmp(args[0] , "bookmark") == 0) {

          if (strcmp(args[1] , "-l") == 0) {

            if (args[2] == NULL)
              printBookmarks(bookmarks);
            else
              printf("Enter a valid command.\n");

          } else if (strcmp(args[1] , "-i") == 0) {

            if (args[2] != NULL) {

              char* empty = (char *)malloc(BOOKMARK_MAX);
              char* bookmark_cmd = (char*)malloc(BOOKMARK_MAX);

              if (strcmp(getBookmarkAtInd(bookmarks, args[2]) , empty) != 0) {

                bookmark_cmd = getBookmarkAtInd(bookmarks, args[2]);
                char* cmd_copy = (char *)malloc(BOOKMARK_MAX);
                strcpy(cmd_copy, bookmark_cmd);
                char* argsToken = strtok(cmd_copy, " ");

                int args_iter = 0;
                int remove_args = 0;

                while (args[remove_args] != NULL) {

                  args[remove_args] = NULL;
                  remove_args++;

                }

                while (argsToken != NULL) {

                  args[args_iter] = (char *)malloc(80);

                  strcpy(args[args_iter], argsToken);
                  argsToken = strtok(NULL, " ");
                  args_iter++;

                }

                addCommand(history, bookmark_cmd);
                goto CHECK_AGAIN;

              }

            } else
              printf("Enter a valid index to execute.\n");

          } else if (strcmp(args[1] , "-d") == 0) {

            if (args[2] != NULL)
              deleteBookmark(bookmarks, args[2]);
            else
              printf("Enter a valid index to delete.\n");

          } else {

            if (args[1] != NULL) {

              char* entries_bookmark = (char*)malloc(BOOKMARK_MAX);
              int t = 1;

              while (args[t] != NULL) {
                strcat(entries_bookmark, args[t]);
                if (args[t + 1] != NULL)
                  strcat(entries_bookmark, " ");
                t++;
              }

              addBookmark(bookmarks, entries_bookmark);

            } else
              printf("Enter a valid bookmark to add. \n");

          }

        } // end of BOOKMARK

        else if (args[0][0] == '!') {

          if (args[0][1] == '!' && args[0][2] == '\0') {

            char* most_recent_command = malloc(80);

            strcpy(most_recent_command, getMostRecent(history));

            if (strcmp(most_recent_command, (char *)malloc(80))) {

              printf("%s\n", most_recent_command);
              addCommand(history, most_recent_command);

              char* argsToken = strtok(most_recent_command, " ");

              int args_iter = 0;

              while (argsToken != NULL) {

                args[args_iter] = (char *)malloc(80);
                strcpy(args[args_iter], argsToken);
                argsToken = strtok(NULL, " ");
                args_iter++;

              }

            } else {
              strcpy(args[0], " ");
            }

          } else if (args[0][1] != '\0') { // !n part

            char* n_value = malloc(10);
            int n_iter = 1;
            int nth = 0;

            while (args[0][n_iter] != '\0') {

              char c = args[0][n_iter];
              char str[2] = {c, '\0'};
              strcat(n_value, str);
              n_iter++;

            }

            nth = (int)strtol(n_value, NULL, 10);
            char* nth_command = (char *)malloc(80);
            strcpy(nth_command, getCommandAtIndex(history, nth));

            if (strcmp(nth_command, (char *)malloc(80))) {

              printf("%s\n", nth_command);
              addCommand(history, nth_command);

              char* argsToken = strtok(nth_command, " ");
              int args_iter = 0;

              while (argsToken != NULL) {

                args[args_iter] = (char *)malloc(80);
                strcpy(args[args_iter], argsToken);
                argsToken = strtok(NULL, " ");
                args_iter++;

              }

            } else {
              strcpy(args[0], " ");
            }

          }

          goto CHECK_AGAIN;

        }  // end of ! functions part

        else if (!strcmp(args[0], "history")) {

          if (args[1] == NULL) {

            printHistory(history);

          } else if (!strcmp(args[1], "-c")) {

            clearHistory(history);

          }

        } // end of HISTORY part

        else if (!strcmp(args[0], "muzik")) {

          char* time_r = (char *)malloc(5);
          char* time_add = (char *)malloc(5);
          char* song = (char *)malloc(80);

          if (args[1] != NULL) {

            if (strcmp(args[1], "-r") == 0) {

              strcpy(time_r, getTime(args[2]));
              removeSong(time_r);

              int rem_args = 0;

              while (args[rem_args] != NULL) {

                args[rem_args] = NULL;
                rem_args++;

              }

              args[0] = (char *)malloc(10);
              args[1] = (char *)malloc(20);

              strcpy(args[0], "crontab");
              strcpy(args[1], "crontab.txt");

            } else if (strcmp(args[1], "-l") == 0) {
              if (args[2] == NULL)
                listSong();
              else
                printf("Please give a valid command to list all the music details");

            } else {

              time_add = getTime(args[1]);

              if (strcmp(time_add, (char *)malloc(5)) != 0) {

                if (args[2] != NULL) {

                  strcpy(song, args[2]);
                  playSong(time_add, song);

                  int rem_args = 0;

                  while (args[rem_args] != NULL) {

                    args[rem_args] = NULL;
                    rem_args++;

                  }

                  args[0] = (char *)malloc(10);
                  args[1] = (char *)malloc(20);

                  strcpy(args[0], "crontab");
                  strcpy(args[1], "crontab.txt");

                }

              }

            }


          }

        } // end of MUZIK part

        else if (!strcmp(args[0], "xox")) {

          if (args[1] != NULL) {

            if (!strcmp(args[1], "start")) {

              startNewGame(gameTable);

            } else if (!strcmp(args[1], "clear")) {

              clearGameTable(gameTable);

            } else if (!strcmp(args[1], "print")) {

              printGameTable(gameTable);

            } else {

              char* coordinates = (char *)malloc(5);
              char* empty = (char *)malloc(5);
              strcpy(coordinates, args[1]);

              if (strcmp(coordinates, empty) != 0) {
                // keep playing game
                playGame(gameTable, coordinates);
              }
            }

          } else {

            printf("If you'd like to start a new game, type 'xox start' \n");
            printf("If you are already playing, please give coordinates properly\n");

          }

        } // end of XOX function part

      } // end of 'if(args[0] !=  NULL)'

      // Forking a child process
      pid_t pid;
      pid = fork();

      if (pid == 0) {

        // the child process will invoke execv()
        pathsToken = strtok(possiblePaths, ":");

        while (pathsToken != NULL) {

          char command[80];
          strcpy(command, pathsToken);
          strcat(command, "/");
          strcat(command, args[0]);

          execv(command, args);
          pathsToken = strtok(NULL, ":");

        }

        exit(0);

      } else {

        if (background == 0) // if command included &, parent will invoke wait()
        {
          // Option with '0' value means that wait for any child process
          // whose process group ID is equal to that of the calling process.
          waitpid(pid, &background, 0);
        }

      }

    } // end of 'IF SHOULDRUN'

  } // end of 'WHILE SHOULDRUN'

  return 0;
}

/**
 * The parseCommand function below will not return any value, but it will just: read
 * in the next command line; separate it into distinct arguments (using blanks as
 * delimiters), and set the args array entries to point to the beginning of what
 * will become null-terminated, C-style strings.
 */
int parseCommand(char inputBuffer[], char *args[], int *background)
{
  int length,   /* # of characters in the command line */
      i,    /* loop index for accessing inputBuffer array */
      start,    /* index where beginning of next command parameter is */
      ct,         /* index of where to place the next parameter into args[] */
      command_number; /* index of requested command number */

  ct = 0;

  /* read what the user enters on the command line */
  do {
    printf("myshell>");
    fflush(stdout);
    length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
  }
  while (inputBuffer[0] == '\n'); /* swallow newline characters */

  // adding the whole command line input
  // to history before even parsing or executing.

  char* hist = malloc(80);
  int k = 0;

  while (inputBuffer[k] != '\n') {
    char c = inputBuffer[k];
    char str[2] = {c, '\0'};

    strcat(hist, str);
    k++;
  }

  if (strncmp(hist, "!!", 2) == 0) {
    // not adding !! to the history
  } else if (strncmp(hist, "!", 1) == 0) {
    // not adding !n to the history
  } else {
    addCommand(history, hist);
  }

  /**
   *  0 is the system predefined file descriptor for stdin (standard input),
   *  which is the user's screen in this case. inputBuffer by itself is the
   *  same as &inputBuffer[0], i.e. the starting address of where to store
   *  the command that is read, and length holds the number of characters
   *  read in. inputBuffer is not a null terminated C-string.
   */

  start = -1;
  if (length == 0)
    exit(0);            /* ^d was entered, end of user command stream */

  /**
   * the <control><d> signal interrupted the read system call
   * if the process is in the read() system call, read returns -1
   * However, if this occurs, errno is set to EINTR. We can check this  value
   * and disregard the -1 value
   */

  if ( (length < 0) && (errno != EINTR) ) {
    perror("error reading the command");
    exit(-1);           /* terminate with error code of -1 */
  }

  /**
   * Parse the contents of inputBuffer
   */

  for (i = 0; i < length; i++) {
    /* examine every character in the inputBuffer */
    switch (inputBuffer[i]) {
    case ' ':

    case '\t' :    /* argument separators */

      if (start != -1) {
        args[ct] = &inputBuffer[start];    /* set up pointer */
        ct++;
      }
      inputBuffer[i] = '\0'; /* add a null char; make a C string */
      start = -1;
      break;

    case '\n':   /* should be the final char examined */

      if (start != -1) {
        args[ct] = &inputBuffer[start];
        ct++;
      }
      inputBuffer[i] = '\0';
      args[ct] = NULL; /* no more arguments to this command */
      break;

    default :             /* some other character */

      if (start == -1)
        start = i;

      if (inputBuffer[i] == '&') {
        *background  = 1;
        inputBuffer[i - 1] = '\0';
      }

    } /* end of switch */

  }    /* end of for */

  /**
   * If we get &, don't enter it in the args array
   */

  if (*background)
    args[--ct] = NULL;

  args[ct] = NULL; /* just in case the input line was > 80 */

  return 1;

} /* end of parseCommand routine */