#include <termio.h>
#include <stdio.h>
#include "getch.h"
int getch(void) {
    int cr;
    struct termios nts, ots;

    if (tcgetattr(0, &ots) < 0)
        return EOF;

    nts = ots;
    cfmakeraw(&nts);
    if (tcsetattr(0, TCSANOW, &nts) < 0)
        return EOF;

    cr = getchar();
    if (tcsetattr(0, TCSANOW, &ots) < 0)
        return EOF;

    return cr;
}
