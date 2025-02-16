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

Preferences getPreferences() {
    printf("Do prefer to hear songs from this artist y/n?\n");
    char choice;
    Preferences pref;
    scanf("%c", &choice);
    if (choice == 'y') {
        pref.artist = 1;
    }
    if (choice == 'n') {
        pref.artist = 0;
    }
    else {
        printf("Invalid input, enter y/n.\n");
    }
    printf("Do you prefer songs of a similar genre?\n");
    scanf("%c", &choice);
    if (choice == 'y') {
        pref.genre = 1;
    }
    if (choice == 'n') {
        pref.genre = 0;
    }
    else {
        printf("Invalid input, enter y/n.\n");
    }
    printf("BPM is the beats per minute. Do you prefer a FAST BPM, Medium BPM, or SLOW BPM? Enter f, m, or s.\n");
    scanf("%c", &choice);
    if (choice == 'f') {
        pref.bpm = FAST;
    }
    if (choice == 'm') {
        pref.bpm = MEDIUM;
    }
    if (choice == 's') {
        pref.bpm = SLOW;
    }
    else {
        printf("Invalid input, enter f, m, or s.\n");
    }
    printf("Do you prefer Happy or Sad Music? Enter h or s.\n");
    scanf("%c", &choice);
    if (choice == 'h') {
        pref.is_happy = 1;
    }
    if (choice == 's') {
        pref.is_happy = 0;
    }
    else {
        printf("Invalid input, enter y/n.\n");
    }
    printf("Do you prefer the current song language? y/n?\n");
    scanf("%c", &choice);
    if (choice == 'y') {
        pref.language = 1;
    }
    if (choice == 'n') {
        pref.language = 0;
    }
    else {
        printf("Invalid input, enter y/n.\n");
    }
    return pref;
}