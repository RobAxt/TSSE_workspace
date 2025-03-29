#ifndef HANDLE_SERVER_UTIL_H
#define HANDLE_SERVER_UTIL_H

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "tcpServerUtil.h"

#define DELIMS      " \n\r"

#define OK_RESPONSE 2
#define OK          1
#define NOT_FOUND   -1
#define ERROR       -2

int handleCommand(char* cmnd, char* resp);

#endif  // HANDLE_SERVER_UTIL_H
