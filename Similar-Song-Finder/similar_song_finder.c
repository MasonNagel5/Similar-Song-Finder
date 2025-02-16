#include "similar_song_finder.h"

Node* getinitialsong(Node* pHead) {
    if (pHead == NULL) {
        printf("No songs\n");
        return NULL;
    }

    char song[100];
    printf("Enter song title to start playing: ");
    fgets(song, sizeof(song), stdin);
    song[strcspn(song, "\n")] = '\0'; // Remove newline char

    Node* pCur = pHead;
    do {
        if (pCur == NULL) {
            printf("That song does not exist! Please try another.\n");
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
void getValidInput(char* choice, const char* validChars) {
    int valid;
    do {
        scanf(" %c", choice);
        valid = strchr(validChars, *choice) != NULL;  // Check if input is in validChars
        if (!valid) {
            printf("Invalid input. Enter one of these options: %s: ", validChars);
        }
    } while (!valid);
}
Preferences getPreferences() {
    char choice;
    Preferences pref;


    printf("Do you prefer to hear songs from this artist? (y/n)\n");
    getValidInput(&choice, "yn");
    pref.artist = (choice == 'y');

    printf("Do you prefer songs of a similar genre? (y/n)\n");
    getValidInput(&choice, "yn");
    pref.genre = (choice == 'y');

    printf("BPM is the beats per minute. Do you prefer a FAST BPM, Medium BPM, or SLOW BPM? (f/m/s)\n");
    getValidInput(&choice, "fms");
    pref.bpm = (choice == 'f') ? FAST : (choice == 'm') ? MEDIUM : SLOW;

    printf("Do you prefer Happy or Sad Music? (h/s)\n");
    getValidInput(&choice, "hs");
    pref.is_happy = (choice == 'h');

    printf("Do you prefer the current song language? (y/n)\n");
    getValidInput(&choice, "yn");
    pref.language = (choice == 'y');

    return pref;
}

Node* traverse_through_available(Node** pHead) {
	Node* chosen_song = NULL;
	while (chosen_song == NULL) {
		chosen_song = getinitialsong(*pHead);
	}
	printf("Chosen song p: %p\n", chosen_song);
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
