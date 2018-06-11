#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <wait.h>


//define
#define COMMAND1 "draw.out"
#define FAIL -1
#define TRUE 1
#define FALSE 0
#define SIZE 1
#define SPACE 32
#define A 65
#define Z 90
#define ARR_SIZE 2
#define ERROR "Error in system call\n"
#define STDERR 2
#define ERROR_SIZE 21

char getch();

int main() {
    int Pipe[2];
    //* Make our pipe *//*
    pipe(Pipe);

    int sonPid = callExecv(Pipe);
    char enteredChar;

    while ((enteredChar = getch())!='q') {
        if (enteredChar=='a'||enteredChar=='s'||enteredChar=='d'||enteredChar=='w') {
            printf("%c", enteredChar);
            if (write(Pipe[1], &enteredChar, 1) == FAIL) {
                handleFailure();
            }

            if (kill(sonPid, SIGUSR2) == FAIL) {
                handleFailure();
            }
        }

    }
    //write last time
    if (write(Pipe[1], &enteredChar, 1) == FAIL) {
        handleFailure();
    }

    if (kill(sonPid, SIGUSR2) == FAIL) {
        handleFailure();
    }

    printf("Hello, World!\n");
    return 0;
}

/**
 * callExecv function.
 * @param args - array for execvp function
 * @return
 */
int callExecv(int Pipe[ARR_SIZE]) {

    int stat, retCode;
    pid_t pid;
    pid = fork();
    if (pid == 0) {  // son
        /* Force our stdin to be the read side of the pipe we made */
        dup2(Pipe[0], 0);
        /*close(Pipe[0]);
        close(Pipe[1]);*/
        char* args[SPACE] = {"./draw.out",NULL};

        /* Execute our command */
        execvp(args[0], &args[0]);

        handleFailure();
    } else {   //father
        //dup2( Pipe[1], 1 );
        //dup2( Pipe[1], 1 );

        /* Close off all the pipes we no longer need */
        /*close( Pipe[0] );
        close( Pipe[1] );*/
        return pid;

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



char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
}