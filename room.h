#ifndef ROOM_H
#define ROOM_H

struct room
{
    int lighted;
    int left, right, top, bottom;
    int rsi; /* index into roomname switch */
};

#endif // ROOM_H
