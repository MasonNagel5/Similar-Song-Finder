#include "similar_song_finder.h"

Node* getinitialsong(Node* pHead) {
    if (pHead == NULL) {
        printf("No songs\n");
        return;
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
        return;
    }
    return pCur;
}
