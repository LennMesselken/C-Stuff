// includes

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>

// data

struct termios orig_termios;

// terminal 

void die(const char* s) {
    perror(s);
    exit(1);
}

void disableRawMode(void){
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode(void){
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr"); //Get Terminal Attributes and store it in a struct
    atexit(disableRawMode); 
    struct termios raw = orig_termios; //Make Copy of struct
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); //Set Flags
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); //Set Flags 
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");//Set Terminal Attributes 
}

// init

int main(void){
    enableRawMode();
    while (1){
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
        read(STDIN_FILENO, &c, 1);
        if (iscntrl(c)){
            printf("%d\r\n", c);
        } else {
            printf("%d ('%c')\r\n", c, c);
        }
        if (c == 'q') break;
    }
    return 0;
}
