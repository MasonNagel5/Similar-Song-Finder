#include "list.h"

/* ----- Standard Doubly-Linked-List Functions ----- */

void init_list(Node** pList) {
    *pList = NULL;
}
Node* create_node(Record new_data) {
    // try to allocate space for a new Node
    Node* pMem = malloc(sizeof(Node));

    // set attributes if it exists
    if (pMem != NULL) {
        pMem->pNext = NULL;
        pMem->pPrev = NULL;
        //pMem->data = new_data;
        set_node_data(pMem, new_data);
    }

    // return a possibly NULL pointer to a Node
    return pMem;
}
void set_node_data(Node* pList, Record new_data) {
    if (!pList) return;

    strcpy(pList->data.title, new_data.title);
    strcpy(pList->data.artist, new_data.artist);
    strcpy(pList->data.genre[0], new_data.genre[0]);
    strcpy(pList->data.genre[1], new_data.genre[1]);
    pList->data.year = new_data.year;
    pList->data.bpm = new_data.bpm;
    pList->data.length = new_data.length;
    pList->data.amount_of_words = new_data.amount_of_words;
    pList->data.is_happy = new_data.is_happy;
    strcpy(pList->data.language, new_data.language);
    pList->data.is_major = new_data.is_major;
}
int insert_front(Node** pList, Record new_data) {
    Node* pMem = create_node(new_data);
    int success = 0;

    if (pMem != NULL) {
        success = 1;

        // if list is empty, set *pList to pMem
        if (*pList == NULL) {
            *pList = pMem;
        }
        // otherwise add to front and adjust links
        else {
            pMem->pNext = *pList;
            (pMem->pNext)->pPrev = pMem;
            *pList = pMem;
        }
    }

    return success;
}
void destroy_list(Node** pList) {
    // recursive step
    if (*pList != NULL) {
        destroy_list(&(*pList)->pNext);
        // printf("freeing song %s\n", (*pList)->data.song);
        free(*pList);
        *pList = NULL;
    }
}
void print_list(Node* pList) {
    if (pList == NULL) {
        printf("-->\n");
    }
    else {
        printf("--> \"%s\" by \"%s\" ", pList->data.title, pList->data.artist);
        print_list(pList->pNext);
    }
}

/* ----- Custom Functions ----- */

int get_list_length(Node* pList) {
    int len = 0;
    while (pList != NULL) {
        len++;
        pList = pList->pNext;
    }
    return len;
}
Node* get_song_node(Node* pList, char* name) {
    if (pList == NULL) return NULL;

    if (strcmp(pList->data.title, name) == 0) return pList;

    return get_song_node(pList->pNext, name);
}
int get_artist_exists(Node* pList, char* artist) {
    if (pList == NULL) return 0;

    if (strcmp(pList->data.artist, artist) == 0) return 1;

    return get_artist_exists(pList->pNext, artist);
}
Node* get_nth_song_of_artist(Node* pList, char* artist, int n) {
    int cur_num = 1;

    while (pList != NULL) {
        if (strcmp(pList->data.artist, artist) == 0) {
            if (cur_num == n) return pList;  // current in artist matching n

            cur_num++;
        }

        pList = pList->pNext;
    }

    // return NULL if nth song doesn't exist
    return NULL;
}

// recursive, based on Martin's deleteContact function from Lab3
int remove_song(Node** pList, char* song_name) {
    // empty list
    if (!*pList) return 0;  // did not remove a song

    // delete the first element if it matches
    if (!strcmp((*pList)->data.title, song_name)) {
        Node* pTemp = *pList;

        *pList = (*pList)->pNext;

        if ((pTemp)->pNext) (pTemp)->pNext->pPrev = (pTemp)->pPrev;

        if ((pTemp)->pPrev) (pTemp)->pPrev->pNext = (pTemp)->pNext;

        free(pTemp);

        return 1;  // found a song and removed it
    }

    // recursive call
    return remove_song(&(*pList)->pNext, song_name);
}

void print_list_p(Node* pList) {
    if (pList == NULL) {
        putchar('\n');
    }
    else {
        printf("[%p <-- %p --> %p]\n", pList->pPrev, pList, pList->pNext);
        print_list_p(pList->pNext);
    }
}
