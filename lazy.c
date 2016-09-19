#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){
    char cmdArg[512];
    char input[256];
    pid_t pChild;

    pChild = fork();

    if(pChild == 0){
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
            system("atom .");

        } else if (strcmp(argv[1], "open") == 0){
            execlp("/usr/bin/open", "open", ".", NULL);

        } else if (strcmp(argv[1], "timewaster") == 0){
            system("/usr/bin/open -a \"/Applications/Google Chrome.app\" 'http://facebook.com/' 'http://reddit.com' 'https://news.ycombinator.com/' 'https://github.com/' 'https://www.youtube.com/'");

        } else if (strcmp(argv[1], "study") == 0){
            system("/usr/bin/open -a \"/Applications/Google Chrome.app\" 'https://my.monash.edu.au/' 'http://moodle.vle.monash.edu/my/' 'https://drive.google.com/drive/u/1/my-drive' 'https://mail.google.com/mail/u/1/#inbox'");
            
        } else if (strcmp(argv[1], "poop") == 0){
            if(strcmp(argv[2], "bomb") == 0){
                for (int i=0; i < 1000; i++){
                    printf("💩 ");
                }
                printf("have a nice day! \n");
            } else {
                //pass
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
