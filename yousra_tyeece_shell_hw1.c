/*Tyeece Hensley(tkh265), Yousra El Hassan(yeh218)
  OS Assignment 1
  Simple C Implementation of a shell without for */

#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 
#include <errno.h>
#include <dirent.h>
#include <ctype.h>


void runPwd();
void runCd();
void runLs();
void runExit();
void readInput(); 
void parseInput();

char *  input_array[100];
char user_input[80];

int main(int argc, char **argv){

  
  char* commands[4];
  int i,inlen,cdlen,index;
  //an array of the basic commands
  commands[0]="exit";
  commands[1]="cd";
  commands[2]="ls";
  commands[3]="pwd";

  printf(" ---- UNIX SHELL ---  \n");
  do{
    readInput();
    parseInput();
    
    index=0;//iitializes index 
    inlen=(strlen(input_array[0])-1);

    for (i=0; i<4; i++){
      if (strncmp(input_array[0], commands[i],2)==0){//checks for which basic command was entered by the user
        cdlen=strlen(commands[i]);
        if(inlen<=cdlen){//checks if they are the same length 
          index = i+1;
          break; 
        }     
      }
    }
    //prompts user to try again if command is not found or calls the appropriate fuction
    if(index==0){
      printf("command not found");
    }
    else{
      switch(index) {//switched to the correct basic function
      case 1:
        runExit();
        break;
      case 2:
        runCd();
        break;
      case 3: 
        runLs();
        break;
      case 4: 
        runPwd();
        break;
      }
    }
  }while(1);

  return 0;
}


void readInput(){
  /* take in command as user input*/
  printf("\n>>: ");
  if (fgets(user_input,80,stdin) == NULL){//checks if ctr+D was pressed and exits 
    printf("Goodbye!");
    exit(0);
  }
}

void parseInput(){
  /* parse through user input and stores them in an array*/
  const char delimiter[2] = " ";
  char * input_tokens;
  int element_counter = 0;
  

  input_tokens = strtok(user_input, delimiter);
  
  while( input_tokens != NULL ) {
    input_array[element_counter] = input_tokens;
    element_counter++ ;
    input_tokens = strtok(NULL, delimiter);
  }
}


void runExit(){//exits the shell when called
  printf("Goodbye");
  exit(0);
}

void runPwd(){//prints working directory using system function
  char pwd[1024];
  getcwd(pwd, sizeof(pwd));
  printf( "%s", pwd); 
}

void runCd(){
    int status;
    //adds the null character to the end of the parsed string
    char* directory = input_array[1];
    directory[strlen(directory)-1] = '\0';

    status = chdir(directory);//chages path to the new directory

    if (status == -1){
      if (isspace(*input_array[1]))//checks if its a space
      {
        printf("Missing argument");
      }
      else if(strcmp(input_array[1],"")==0){//checks if it is null
        printf("Missing argument");
      }
      else{
        printf("Command failed: No such file or directory");
      } 
    }
}



void runLs(){ //lists the directories and files in the working directory

  struct dirent **filenames;
	int n;

	n=scandir(".",&filenames,NULL,alphasort);

	if(n < 0)
	{
		perror("scandir");
	}
		else
	{
		while (n-- && n > 1)
		{
			printf("\n%s",filenames[n]->d_name);
			free(filenames[n]);
		}
		free(filenames);
	}
}

