#include "similar_song_finder.h"

Node* getinitialsong(Node* pHead) {
    if (pHead == NULL) { return NULL; }

    char song[100];
    simple_text_screen("Enter song title to start playing:");
    printf("\n> ");
    fgets(song, sizeof(song), stdin);
    song[strcspn(song, "\n")] = '\0'; // Remove newline char

    Node* pCur = pHead;
    do {
        if (pCur == NULL) {
            putchar('\n');
            simple_text_screen("!! That song does not exist! Please try another !!");
            enter_wait();
            return NULL;
        }
        if (strcmp(pCur->data.title, song) == 0) {
            break;
        }
        pCur = pCur->pNext;
    } while (pCur != pHead); // Prevents the infinite loop

    if (pCur == pHead && strcmp(pCur->data.title, song) != 0) {
        printf("Song not found.\n");
        return NULL;
    }
    return pCur;
}
Preferences getPreferences() {
    char choice;
    Preferences pref;

    clear_scr();
    simple_text_screen("Do you prefer to hear songs from this artist?");
    get_valid_char("(y/n): ", & choice, "yn");
    pref.artist = (choice == 'y');

    clear_scr();
    simple_text_screen("Do you prefer songs of a similar genre?");
    get_valid_char("(y/n): ", &choice, "yn");
    pref.genre = (choice == 'y');

    clear_scr();
    char bpm_text[150] = "BPM is the beats per minute. Which do you prefer?\n  - FAST BPM (f)\n  - Medium BPM (m)\n  - SLOW BPM (s)";
    simple_text_screen(bpm_text);
    get_valid_char("(f/m/s): ", &choice, "fms");
    pref.bpm = (choice == 'f') ? FAST : (choice == 'm') ? MEDIUM : SLOW;

    clear_scr();
    simple_text_screen("Do you prefer Happy (h) or Sad (s) Music?");
    get_valid_char("(h/s): ", &choice, "hs");
    pref.is_happy = (choice == 'h');

    clear_scr();
    simple_text_screen("Do you prefer the current song language?");
    get_valid_char("(y/n): ", &choice, "yn");
    pref.language = (choice == 'y');

    return pref;
}

Node* traverse_through_available(Node** pHead) {
    clear_scr();

    // first, check for no songs in the list
    if (pHead == NULL || *pHead == NULL || get_list_length(*pHead) == 0) {
        char err_msg[80] = "You have no songs loaded!\n \nPlease check your `song_data.csv` file and retry.";
        clear_scr();
        simple_text_screen(err_msg);
        enter_wait();
        return NULL;
    }
    
    // then, try getting initial song until one is found
    Node* chosen_song = NULL;
	while (chosen_song == NULL) {
		chosen_song = getinitialsong(*pHead);
        clear_scr();
	}
	Node* pCur = *pHead;
	insert_front(pHead, chosen_song->data);
	Preferences User_Preferences;
	User_Preferences = getPreferences();
	while (pCur != NULL) {
		if (strcmp(pCur->data.title, chosen_song->data.title) == 0) {
			deleteNode(pHead, pCur->data);
		}
		pCur = pCur->pNext;
	}

	pCur = *pHead;

	while (pCur != NULL) {

		score_record(pCur, chosen_song, User_Preferences);

		pCur = pCur->pNext;
	}

	return chosen_song;
}

void score_record(Node* pHead, Node* chosen_song, Preferences preference) {
	int score = 0;

	if (strcmp(chosen_song->data.artist, pHead->data.artist) == 0) score += (preference.artist) ? 1 : 0;

	if (strcmp(chosen_song->data.genre[0], pHead->data.genre[0])) score += (preference.genre) ? 1 : 0;
	if (strcmp(chosen_song->data.genre[1], pHead->data.genre[1])) score += (preference.genre) ? 1 : 0;

	if (preference.bpm == FAST && chosen_song->data.bpm > 140) score += 1;
	if (preference.bpm == MEDIUM && chosen_song->data.bpm < 140 && chosen_song->data.bpm > 100) score += 1;
	if (preference.bpm == SLOW && chosen_song->data.bpm < 100) score += 1;

	if (pHead->data.length.minutes >= chosen_song->data.length.minutes - 1 && pHead->data.length.minutes <= chosen_song->data.length.minutes + 1) score += 1;

	if (pHead->data.amount_of_words >= chosen_song->data.amount_of_words - 100 && pHead->data.amount_of_words <= chosen_song->data.amount_of_words + 100) score += 1;

	if (pHead->data.is_happy == preference.is_happy) score += 1;
	if (strcmp(pHead->data.language, chosen_song->data.language) == 0 && preference.language) score += 1;
	if (pHead->data.is_major == chosen_song->data.is_major) score += 1;

	pHead->data.similarity_score = score;
}
