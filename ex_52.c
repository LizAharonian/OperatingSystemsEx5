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
#define SIZE 20
#define FAIL -1
#define COMMAND1 "draw.out"
#define FAIL -1
#define TRUE 1
#define FALSE 0
#define SPACE 32
#define A 65
#define Z 90
#define ARR_SIZE 2
#define ERROR "Error in system call\n"
#define STDERR 2
#define ERROR_SIZE 21

void sigHandle(int num);
char enteredChar;


typedef struct Point {
    int x;
    int y;
}Point;
enum State {STAND, LAY};

typedef struct Player {
    Point point;
    enum State state;


}Player;
void handleFailure();
void printBoard();

void moveRight();

void moveDown();

void changeState();
void alarm_hand (int sig);

//global
Player player;


int main() {
    //initialize new player
    enteredChar = ' ';
    Point point;
    point.x = 0;
    point.y = 10;
    player.point = point;
    player.state = LAY;
    printBoard(player);
    if (system("clear")==FAIL) {
        handleFailure();
    }

    signal(SIGALRM,alarm_hand);
    alarm(1);
    signal(SIGUSR2, sigHandle);
    while (1) {
        pause();
    }
}

void alarm_hand (int sig){
    alarm(1);
    signal(SIGALRM,alarm_hand);
    moveDown();
    printBoard(player);

}


void changeState() {
    player.state =(player.state == LAY) ?STAND:LAY;
    if (player.point.x ==0) {
        player.point.x+=1;

    }

}

void moveDown() {
    if (player.state==LAY) {
        if(player.point.x<=17) {
            player.point.x+=1;
        }
    } else if(player.state==STAND) {
        if(player.point.x<=16) {
            player.point.x+=1;
        }
    }
}

void moveRight() {
    if (player.state==LAY) {
        if(player.point.y<=16) {
            player.point.y+=1;
        }
    } else if(player.state==STAND) {
        if(player.point.y<=17) {
            player.point.y+=1;
        }
    }
}

void moveLeft() {
    if (player.state==LAY) {
        if(player.point.y>=3) {
            player.point.y-=1;
        }
    } else if(player.state==STAND) {
        if(player.point.y>=2) {
            player.point.y-=1;
        }
    }
}

//todo:make sure enter this function with x and y bigger then 1!!!
void printBoard() {
    if (system("clear")==FAIL) {
        handleFailure();
    }

    char gameBoard[SIZE][SIZE];
    int i;
    for (i = 0; i <SIZE ; ++i) {
        int j;
        for (j = 0; j < SIZE; ++j) {
            gameBoard[i][j] = ' ';
        }
    }

    for (i = 0; i <SIZE ; ++i) {
        int j;
        for (j = 0; j < SIZE; ++j) {
            if(i==19||j==0||j==19){
                gameBoard[i][j]='*';
            }
            if (i==player.point.x&&j==player.point.y) {
                gameBoard[i][j] = '-';
                if (player.state==LAY) {
                    gameBoard[i][j-1] ='-';
                    gameBoard[i][j+1]='-';
                } else if (player.state==STAND) {
                    gameBoard[i-1][j] = '-';
                    gameBoard[i+1][j] = '-';
                }
            }
        }
    }

    for (i = 0; i <SIZE ; ++i) {
        int j;
        for (j = 0; j < SIZE; ++j) {
            printf("%c", gameBoard[i][j]);
        }
        printf("\n");
    }

    if (player.state == LAY) {
        if(player.point.x>=18) {
            player.point.x =0;
            player.point.y=10;
            printBoard();
        }

    } else if (player.state==STAND) {
        if(player.point.x>=17) {
            player.point.x =0;
            player.point.y=10;
            player.state=LAY;
            printBoard();
        }
    }
}

/**
 * handleFailure function.
 * prints error and exits the program.
 */

void handleFailure() {
    write(STDERR, ERROR, ERROR_SIZE);
    exit(FAIL);
}






void sigHandle(int num)
{
    char enteredChar;
    scanf("%c", &enteredChar);
    switch(enteredChar) {
        case 'a':
            moveLeft();

            break;
        case 'd':
            moveRight();
            break;
        case 's':
            moveDown();
            break;
        case 'w':
            changeState();
            break;
        case 'q':
            exit(0);
            break;
    }
    printBoard(player);

    signal(SIGUSR2,sigHandle);
}
