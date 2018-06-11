//
// Created by liz on 11/06/18.
//

#include <printf.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <wait.h>
void sigHandle(int num);


/*int main() {
    while (1) {

        signal(SIGUSR2, sigHandle);
    }


    printf("Hello, World!\n");
    return 0;
}*/

void sigHandle(int num)
{
    char enteredChar;
    scanf("%c", &enteredChar);
    printf("enter sigHandle\n");
    /*char buf[8]="hello";
    int count=0;
    buf[5]=(char)(counter+'0');
    count=write(fda[1],buf,6);
    counter++;*/
    signal(SIGUSR2,sigHandle);
}