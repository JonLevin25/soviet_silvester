#include <Arduino.h>
#include "common.h"

const char MsgTypeText[] =
    "Ping\0"
    "Pong\0"
    "Start\0"
    "Sync\0"
    "End\0"
    "\0";


char *GetMsgType(unsigned char msgType)
{
    unsigned char t = 0;
    bool found = false;
    char * message = (char*)&MsgTypeText;

    while(!found && message[0]) {
        found = t == msgType;
        if(!found) {
            message = message + strlen(message) + 1;
            t++;
        }
    }
    if(!found) {
        return NULL;
    } else {
        return message;
    }
}