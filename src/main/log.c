#include "log.h"

#include <stdio.h>

int LOGLEVEL = DEBUG;

void set_loglevel(int loglevel) {
    LOGLEVEL = loglevel;
}

void LOGGER(char* file, int line, int loglevel, const char* message) {
    if(loglevel < LOGLEVEL) {
        return;
    }

    const char * level = "UNKNOWN";
    switch(loglevel) {
        case DEBUG:
            level = "DEBUG";
            break;

        case WARN:
            level = "WARN ";
            break;

        case ERROR:
            level = "ERROR";
            break;
    }

    fprintf(stdout, "%s:%-4d %s [%s]\n", file, line, level, message);
}