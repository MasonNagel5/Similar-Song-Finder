#include "ui.h"

/* ----- System Functions ----- */
void clear_scr() { system("cls"); }

/* ----- Math/Calculation Abstractions ----- */
int get_max_len_of_mutliline(char* multiline_input) {
	int max = 0, cur=0;

	char* cur_char = multiline_input;
	while (*cur_char != '\0') {
		if (*cur_char == '\n') {
			if (cur > max) max = cur;
			cur = 0;
		}
		cur_char++;
		cur++;
	}
	if (cur > max) max = cur;
	
	return max;
}

/* ----- Window Abstractions ----- */
void horiz_border(int width) {
	putchar('X');

	for (int i = 1; i <= width - 2; i++) {
		putchar('-');
	}

	putchar('X');
	putchar('\n');
}
void h_pad_border(int width) {
	putchar('|');

	for (int i = 1; i <= width - 2; i++) {
		putchar(' ');
	}

	putchar('|');
	putchar('\n');
}
void l_border() { printf("|  "); }
void r_border() { puts("  |"); }
void bordered_text(int width, char* text) {
	int text_len = width - 6;

	char *line = strtok(text, "\n");
	while (line != NULL) {
		char to_print[128] = "";
		strncpy(to_print, line, text_len);
		to_print[text_len] = '\0';

		int line_len = strlen(to_print);
		int spacing_needed = text_len - line_len;

		l_border();
		printf("%s", to_print);

		while (spacing_needed > 0) {
			putchar(' ');
			spacing_needed -= 1;
		}

		r_border();

		line = strtok(NULL, "\n");
	}
}

/* ----- Particular Windows ----- */

// general text-displaying screen
void simple_text_screen(char* text) {
	int text_wid = get_max_len_of_mutliline(text);
	int win_wid = text_wid + 6;

	horiz_border(win_wid);
	h_pad_border(win_wid);
	bordered_text(win_wid, text);
	h_pad_border(win_wid);
	horiz_border(win_wid);
}

// welcome screen - describe the program's purpose
void welcome_screen() {
	// i'm so sorry for this horrible line
	char text[400] = "Welcome to the Similar - Song - Finder!\n \n   By : Mason N.\n        Grayson F.\n        Logan M.\n \n Team : FTWF\n \nEvent : Hackathon 2025\n \n  This program will allow you to choose a song start from\nand create a playlist sorted by similarity to that song, \nfrom most similar to least similar.\n \n  You will be able to add things you prefer over other\nfactors, like same artist, similar BPM range, etc.";

	simple_text_screen(text);
}

// main menu- choose whether to list songs or make a playlist based on a song
int main_menu(Node *pHead) {
	clear_scr();
	
	int num_songs = get_list_length(pHead);
	
	char text[200] = "";
	sprintf(text, "You have %d songs! Would you like to:\n  1. Print songs\n  2. Make customized playlist\n  3. Exit program", num_songs);

	simple_text_screen(text);
	putchar('\n');

	return get_valid_pos_range_int("> Enter choice here [1-3]: ", 1, 3);
}

// print all songs, and allow for "scrolling"
void print_song_menu(Node *pHead) {
	// first, find longest line to be printed
	int longest_line_wid = 0, song_num = 0;

	Node* pCur = pHead;
	while (pCur != NULL) {
		song_num++;

		char line[128] = "";
		sprintf(line, "%3d - %s, %s, %s, %d, %d, %d:%d, %d, %d, %s, %d, %d", song_num, pCur->data.title, pCur->data.artist, pCur->data.genre[0], pCur->data.year, pCur->data.bpm, pCur->data.length.minutes, pCur->data.length.seconds, pCur->data.amount_of_words, pCur->data.is_happy, pCur->data.language, pCur->data.is_major, pCur->data.similarity_score);
		
		int line_len = strlen(line);
		if (line_len > longest_line_wid) longest_line_wid = line_len;

		pCur = pCur->pNext;
	}

	int win_wid = longest_line_wid + 6;
	horiz_border(win_wid);
	h_pad_border(win_wid);
	
	song_num = 0;
	pCur = pHead;

	while (pCur != NULL) {
		song_num++;
		char line[128] = "";
		sprintf(line, "%3d - %s, %s, %s, %d, %d, %d:%d, %d, %d, %s, %d, %d", song_num, pCur->data.title, pCur->data.artist, pCur->data.genre[0], pCur->data.year, pCur->data.bpm, pCur->data.length.minutes, pCur->data.length.seconds, pCur->data.amount_of_words, pCur->data.is_happy, pCur->data.language, pCur->data.is_major, pCur->data.similarity_score);

		bordered_text(win_wid, line);

		pCur = pCur->pNext;
	}

	h_pad_border(win_wid);
	horiz_border(win_wid);
}

/* ----- Input Getting ----- */
void enter_wait() {
	char line[20];

	printf("\nPress enter to continue...");

	fgets(line, sizeof(line), stdin);
}
int get_valid_pos_range_int(char* prompt, int min, int max) {
	int choice = -1;
	
	while (choice == -1) {
		printf("%s", prompt);

		char line[50] = "";

		fgets(line, sizeof(line), stdin);

		int success = sscanf(line, "%d", &choice);

		if (success == 1) {
			if (choice >= min && choice <= max) return choice;
			else printf("- Invalid input! Please enter a number between %d and %d!!\n", min, max);
		}
		else printf("- Invalid input! Please enter a *number*!!\n");
		choice = -1;
	}

	return choice;
}
char get_valid_char(char* prompt, char *choice, char* valid_chars) {
	int valid;
	do {
		printf("%s", prompt);
		char line[50] = "";
		fgets(line, sizeof(line), stdin);
		int scan_success = sscanf(line, " %c", choice);
		valid = strchr(valid_chars, *choice) != NULL;  // Check if input is in validChars
		if (!valid) {
			puts("Invalid input, not a character that's expected");
		}
	} while (!valid);
}