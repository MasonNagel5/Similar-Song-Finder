#include "similar_song_finder.h"
#include "list.h"
int main(void) {
	// welcome message then wait for enter
	welcome_screen();
	enter_wait();

	FILE* infile = NULL;

	infile = fopen("song_data.csv", "r");

	Node* phead;

	init_list(&phead);

	loadSongs(infile, &phead);

	fclose(infile);

	// user main loop
	int choice = 0;
	while (choice != 3) {
		choice = main_menu(phead);

		// print songs
		if (choice == 1) {
			//print_list(phead);
			clear_scr();
			print_song_menu(phead);
			enter_wait();
		}
		// make playlist
		else if (choice == 2) {
			Node* chosen_song = traverse_through_available(&phead);

			if (chosen_song == NULL) return -1;

			phead = makePlaylist(&phead, chosen_song);

			clear_scr();
			print_song_menu(phead);
			enter_wait();
		}
		// exit
		else if (choice == 3) {
			return 0;
		}
	}















	














	return 0;
}