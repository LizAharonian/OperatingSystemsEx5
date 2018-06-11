//
// Created by liz on 11/06/18.
//

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


/*
int main() {

    while (1) {
        printf("process son\n");
signal(SIGUSR2, sigHandle);
        pause();
        

    }


    printf("Hello, World!\n");
    return 0;
}*/



void sigHandle(int num)
{
    printf("enter sigHandle\n");

    char enteredChar;
    scanf("%c", &enteredChar);
    //printf("the char is:","%c",enteredChar);
    signal(SIGUSR2,sigHandle);
}
