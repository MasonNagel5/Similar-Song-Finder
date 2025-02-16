#include "similar_song_finder.h"
#include "list.h"
int main(void) {


	FILE* infile = NULL;

	infile = fopen("song_data.csv", "r");

	Node* phead;

	init_list(&phead);

	loadSongs(infile, &phead);

	fclose(infile);


	traverse_through_available(&phead);
	
	makePlaylist(&phead);

















	














	return 0;
}