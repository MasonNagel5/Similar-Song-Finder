#ifndef LIST_H
#define LIST_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 64
#define MAX_LINE_LEN ((MAX_NAME_LEN*4) + 16)
#define PLAYLIST_FILE "musicPlayList.csv"

typedef struct duration {
    int minutes;
    int seconds;
} Duration;

typedef struct record {
    char title[MAX_NAME_LEN];
    char artist[MAX_NAME_LEN];
    char genre[2][MAX_NAME_LEN];
    int year;
    int bpm;
    Duration length;
    int amount_of_words;
    int is_happy;
    char language[MAX_NAME_LEN];
    int is_major;
} Record;

typedef struct node {
    Record data;
    struct node* pNext;
    struct node* pPrev;
} Node;

/* ----- Standard Doubly-Linked-List Functions ----- */

/*
 * Function: init_list
 * --------------------
 *   Sets *pList to NULL
 *
 *   Parameters:
 *   - **pList: pointer to list to edit
*/
void init_list(Node** pList);

/*
 * Function: create_node
 * --------------------
 *   Creates new node in heap and assigns new data
 *
 *   Parameters:
 *   - new_data: new data to set to new Node's data
 *
 *   Returns:
 *   - pointer to new Node on heap
*/
Node* create_node(Record new_data);

/*
 * Function: set_node_data
 * --------------------
 *   Copies values into node, including strcpy'ing the strings
 *
 *   Parameters:
 *   - *pList: the node to copy data into
 *   - new_data: new data to set to new Node's data
 *
*/
void set_node_data(Node* pList, Record new_data);

/*
 * Function: insert_front
 * --------------------
 *   Creates a new Node and inserts it at the front of the list
 *
 *   Parameters:
 *   - **pList: poitner to list to edit
 *   - new_data: new data to set to new Node's data
 *
 *   Returns:
 *   - success value; 1 for success, 0 for fail
*/
int insert_front(Node** pList, Record new_data);

/*
 * Function: destroy_list
 * --------------------
 *   Frees entire list
 *
 *   Parameters:
 *   - **pList: pointer to list to edit and delete list of
*/
void destroy_list(Node** pList);

/*
 * Function: print_list
 * --------------------
 *   Prints the raw list nicely, should not be used for UI
 *
 *   Parameters:
 *   - *pList: pointer to list to print
 *
*/
void print_list(Node* pList);

/* ----- Custom Functions ----- */

/*
 * Function: get_list_length
 * --------------------
 *   Get the length of the list
 *
 *   Parameters:
 *   - *pList: pointer to list to get length of
 *
 *   Returns:
 *   - length of the list
*/
int get_list_length(Node* pList);

/*
 * Function: get_song_node
 * --------------------
 *   Given a name, find (if possible) the pointer to the node matching that song name
 *
 *   Parameters:
 *   - *pList: pointer to list to find song in
 *   - name: string for song name
 *
 *   Returns:
 *   - pointer to Node matching that song name
*/
Node* get_song_node(Node* pList, char* name);

/*
 * Function: get_artist_exists
 * --------------------
 *   See if there exists a record with the given artist's name
 *
 *   Parameters:
 *   - *pList: pointer to list to find song in
 *   - artist: string for artist name
 *
 *   Returns:
 *   - 1 for success and exists, 0 for fail and not exist
*/
int get_artist_exists(Node* pList, char* artist);

/*
 * Function: get_nth_song_of_artist
 * --------------------
 *   Get the nth song from a matching artist
 *
 *   Parameters:
 *   - *pList: pointer to list to find songs in
 *   - artist: string for artist name
 *   - n: song number
 *
 *   Returns:
 *   - pointer to corresponding record, NULL if not found
*/
Node* get_nth_song_of_artist(Node* pList, char* artist, int n);

/*
 * Function: remove_song
 * --------------------
 *   Removes the first occurence of a record with matching song name
 *
 *   Parameters:
 *   - *pList: pointer to list to find song in
 *   - song_name: string for song name
 *
 *   Returns:
 *   - 1 for found and removed, 0 for not found
*/
int remove_song(Node** pList, char* song_name);

/*
 * Function: print_list_p
 * --------------------
 *   Ugly printing of list, you see the exact pointers for debugging
 *
 *   Parameters:
 *   - *pList: pointer to list to print
 *
*/
void print_list_p(Node* pList);

#endif