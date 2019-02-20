#ifndef TYPE_H
#define TYPE_H


typedef enum {
    NUL = 0,
    WHITE = 1,
    BLACK = 2,
}CHESS_PIECES;

typedef enum {
    NEW,
    PLAYING,
    WINING,
    END,
}PLAY_STATUS;

typedef enum {
    CUSTOM = 0,
    MAN_MACHiNE = 1,
    MAN_MAN = 2,
}PALY_TYPE;

typedef enum {
    SLEEP_2     = 20,
    ACTIVE_2    = 100,
    SLEEP_3     = 100,
    ACTIVE_3    = 1000,
    POUND_4     = 1000,
    ACTIVE_4    = 10000,
    LINK_5      = 100000,
}SCORE_RANK;

typedef struct
{
    int INDEX_X;
    int INDEX_Y;
}CHESS_PIECES_POSITION;

#endif // TYPE_H
