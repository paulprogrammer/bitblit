//
// Created by Paul Williams on 12/27/23.
//

#ifndef BITBLIT_LOG_H
#define BITBLIT_LOG_H

#define DEBUG 0
#define WARN 1
#define ERROR 2

void set_loglevel(int loglevel);

void LOGGER(char* file, int line, int loglevel, const char* message);
#define logger(loglevel, message) LOGGER(__FILE_NAME__ , __LINE__ , loglevel, message);

#endif //BITBLIT_LOG_H
