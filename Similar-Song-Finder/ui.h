#ifndef UI_H
#define UI_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

/* ----- System Functions ----- */
void clear_scr();

/* ----- Math/Calculation Abstractions ----- */
int get_max_len_of_mutliline(char* multiline_input);

/* ----- Window Abstractions ----- */
void horiz_border(int width);
void h_pad_border(int width);
void l_border();
void r_border();
void bordered_text(int width, char* text);

/* ----- Particular Windows ----- */
// general text-displaying screen
void simple_text_screen(char *text);

// welcome screen - describe the program's purpose
void welcome_screen();

// main menu- choose whether to list songs or make a playlist based on a song
int main_menu(Node *pHead);

// print all songs, and allow for "scrolling"
void print_song_menu(Node *pHead);

/* ----- Input Getting ----- */
void enter_wait();
int get_valid_pos_range_int(char *prompt, int min, int max);
char get_valid_char(char* prompt, char *choice, char* valid_chars);

#endif