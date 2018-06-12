/**
 * Liz Aharonian.
 * 316584960.
 */
#include <printf.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define SIZE 20
#define FAIL -1
#define FAIL -1
#define ARR_SIZE 2
#define ERROR "Error in system call\n"
#define STDERR 2
#define ERROR_SIZE 21

//enum
enum State {STAND, LAY};

//structs
typedef struct Point {
    int x;
    int y;
}Point;

typedef struct Player {
    Point point;
    enum State state;
}Player;

/**
 * sigHandle function.
 * scans the char and moves the player.
 */
void sigHandle();

/**
 * handleFailure function.
 * prints error and exits the program.
 */

void handleFailure();

/**
 * printBoard function.
 * prints the board.
 */
void printBoard();

/**
 * moveRight function.
 * moves the game player right.
 */
void moveRight();

/**
 * moveDown function.
 * moves the player down.
 */
void moveDown();

/**
 * moveLeft function.
 * moves the player left.
 */
void moveLeft();

/**
 * changeState function.
 * changes the state of the player.
 */
void changeState();

/**
 * alarm_hand function.
 * moves the player down every second.
 */
void alarm_hand();

Player player;

int main() {
    //initialize new player
    Point point;
    point.x = 0;
    point.y = 10;
    player.point = point;
    player.state = LAY;
    //define sigAlarm
    signal(SIGALRM, alarm_hand);
    //call alarm_hand every second
    alarm(1);
    //define SIGUSR2
    signal(SIGUSR2, sigHandle);
    while (1) {
        //wait for signals
        pause();
    }
}

void alarm_hand (){
    alarm(1);
    signal(SIGALRM,alarm_hand);
    moveDown();
    printBoard();

}

void changeState() {
    if(player.state==STAND) {
        if (player.point.x == 0) {
            player.point.x += 1;
        }
        if (player.point.y==1) {
            player.point.y+=1;
        } else if (player.point.y==18) {
            player.point.y-=1;
        }
    }
    //change state
    player.state =(player.state == LAY) ? STAND:LAY;
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

void printBoard() {
    if (system("clear")==FAIL) {
        handleFailure();
    }
    //initialize new clear board
    char gameBoard[SIZE][SIZE];
    int i;
    for (i = 0; i <SIZE ; ++i) {
        int j;
        for (j = 0; j < SIZE; ++j) {
            gameBoard[i][j] = ' ';
        }
    }
    //initialize the board and player
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
    //print the board
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

void handleFailure() {
    write(STDERR, ERROR, ERROR_SIZE);
    exit(FAIL);
}

void sigHandle()
{
    char enteredChar;
    //scan the char from the pipe
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
    }
    printBoard();
    //define the signal again
    signal(SIGUSR2,sigHandle);
}
