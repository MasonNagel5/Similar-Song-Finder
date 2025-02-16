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