#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h> //used for the uname cmd to check what type of system we are running on 

/**
AUTHOR: Josh Nelsson-Smith
STARTED: Only god knows when (and git)
LAST UPDATED: 04/12/16
**/

int main(int argc, char **argv){
    char cmdArg[512];
    char input[256];
    pid_t pChild;
    struct utsname unameData;

    pChild = fork();

    if(pChild == 0){
        uname(&unameData);
        if (strcmp(argv[1], "git") == 0){
            system("git add .");
            strcpy(cmdArg, "git commit -m ");
            printf("please enter commit message: ");
            fgets(input, 256, stdin);
            input[strcspn(input, "\n")] = 0;
            strcat(cmdArg, input);
            system(cmdArg);
            system("git push -u origin master");

        } else if (strcmp(argv[1], "dev") == 0){
            if(strcmp(unameData.sysname, "Linux\n")){
                 system("code .");
            } else {
                system("atom ."); //because every mac user uses atom right?
            }
           

        } else if (strcmp(argv[1], "clone") == 0){
            char str[80];
            strcat(str, "git clone https://github.com/joshua-xavier/");
            strcat(str, argv[2]);
            system(str);

        } else if (strcmp(argv[1], "open") == 0){
            if(strcmp(unameData.sysname, "Linux") == 0){
                execlp("/usr/bin/nautilus", "nautilus", ".", NULL);
            } else {
                execlp("/usr/bin/open", "open", ".", NULL);
            }
    

        } else {
            printf("Im sorry cmd [%s] is not recognised\n", argv[1]);

        }
    } else if (pChild > 0){
        wait(NULL);
    } else {
        printf("Fatal Error creating process...\n");
        exit(1);
    }

}
