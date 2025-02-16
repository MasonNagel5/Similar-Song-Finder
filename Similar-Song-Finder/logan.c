#include "similar_song_finder.h"

void traverse_through_available(Node** pHead) {
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
}

void score_record(Node *pHead, Node *chosen_song, Preferences preference) {
	int score = 0;

	if (strcmp(chosen_song->data.artist, pHead->data.artist) == 0) score += (preference.artist) ? 2 : 1;

	if(strcmp(chosen_song->data.genre[0], pHead->data.genre[0])) score += (preference.genre) ? 2 : 1;
	if(strcmp(chosen_song->data.genre[1], pHead->data.genre[1])) score += (preference.genre) ? 2 : 1;

	if (preference.bpm == FAST && chosen_song->data.bpm > 140) score += 2;
	if (preference.bpm == MEDIUM && chosen_song->data.bpm < 140 && chosen_song->data.bpm > 100) score += 2;
	if (preference.bpm == SLOW && chosen_song->data.bpm < 100) score += 2;

	if (pHead->data.length.minutes >= chosen_song->data.length.minutes-1 && pHead->data.length.minutes <= chosen_song->data.length.minutes+1) score += 2;

	if (pHead->data.amount_of_words >= chosen_song->data.amount_of_words-100 && pHead->data.amount_of_words <= chosen_song->data.amount_of_words+100) score += 2;

	if (pHead->data.is_happy == preference.is_happy) score += 2;
	if(strcmp(pHead->data.language, chosen_song->data.language) == 0 && preference.language) score += 2;
	if(pHead->data.is_major == chosen_song->data.is_major) score += 2;

	pHead->data.similarity_score = score;
}
