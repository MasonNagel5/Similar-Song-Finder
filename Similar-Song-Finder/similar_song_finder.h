#ifndef SIMILARSONGFINDER_H
#define SIMILARSONGFINDER_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef enum bpm_range {
    FAST,  // >140
    MEDIUM,  // 100-140
    SLOW  // <100
} BPM_RANGE;

typedef struct preferences {
    int artist;  // 1 for prefers same artist, 0 otherwise
    int genre;  // 1 for prefers same genre, 0 otherwise
    BPM_RANGE bpm;  // etc
    int is_happy;  // etc
    int language;
} Preferences;

Node* getinitialsong(Node* pHead);
void traverse_through_available(Node** pHead);
void score_record(Node *pHead, Node *chosen_song, Preferences priority);


#endif