#ifndef SIMILARSONGFINDER_H
#define SIMILARSONGFINDER_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
Node* getinitialsong(Node* pHead);
void traverse_through_available(Node** pHead, Node** pPlaylist);



#endif