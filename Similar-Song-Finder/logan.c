#include "similar_song_finder.h"

void traverse_through_available(Node** pHead) {
	Node* chosen_song = getinitialsong(*pHead);
	printf("Chosen song p: %p\n", chosen_song);
	Node* pCur = *pHead;
	insert_front(pHead, chosen_song->data);
	while (pCur != NULL) {
		if (strcmp(pCur->data.title, chosen_song->data.title) == 0) {
			deleteNode(pHead, pCur->data);
		}
		pCur = pCur->pNext;
	}

	
}