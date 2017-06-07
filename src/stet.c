#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    // gets attributes from terminal
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    
    struct termios raw = orig_termios;
    
    // Disable echo by clearing bit
    // ICANON: Disables canonical so that input is read per byte not per line
    raw.c_lflag &= ~(ECHO | ICANON);
    
    // set modified attributes to terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    
    enableRawMode();
    
    char c;
    
    while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    
    return 0;
}
