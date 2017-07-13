// if using OOP, this program is actually not so pain in the ass to write..

/*  shahril : 18-jan-2016

    piece of advises to those "forces" who want to read my code

   - code very mess up (this was written 1 year ago)

   - this game isn't "computer vs human", it's "human vs human", the reason is my internal implementation
     isn't compatible with chess engines that available online

   - code is combination of C++ and C, so contains many weird C tricks, such as pointer, etc etc

   - not fully working inside Windows (you will see lots of rubbish characters),
     bcoz unicode is second class citizen in CMD, believe me I tried everything and none of it works,
     so if u really wanna try this, go find cmd alternative that support unicode better, such as "console2"
     if you're using linux (i build this on ubuntu linux), then no worries, same goes for macOSX too :)

   - There's no magic, all those chess pieces that you see is all Unicode characters
     (unicode contains lots of weird characters...)
     you can google it if you wanna see yourself, using keyword "unicode characters list"

     here is link to chess unicode (if u wanna see it urself) :
     https://en.wikipedia.org/wiki/Chess_symbols_in_Unicode */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

/*
 player 1 = 0 (black) (down of the board)
 player 2 = 1 (white) (top of the board)
*/
char unicodePieces[2][6][5] =
{
	{ "\u2654", "\u2655", "\u2656", "\u2657", "\u2658", "\u2659" },
	{ "\u265A", "\u265B", "\u265C", "\u265D", "\u265E", "\u265F" }
};

// initialize all pieces into our board
//
// format is like this :-
// {X coordinate, status (1 = alive or 0 = dead), position inside unicodePieces array}
//
int pieces_initial_position[9][3] =
{
	{5, 1, 0}, // king (klau status = 0, nnti program crash)
	{4, 1, 1}, // queen
	{3, 1, 3}, // bishop 0
	{6, 1, 3}, // bishop 1
	{2, 1, 4}, // knight 0
	{7, 1, 4}, // knight 1
	{1, 1, 2}, // rook 0
	{8, 1, 2}, // rook 1
	{-1, 1, 5} // all pawns (-1 because its going to loop for its own position)
};

typedef struct pieceinfo
{
	// coordinate x & y on graph
	int x, y;

	// 1 = alive, 0 = dead
	int status;

	// belong to which player number (0 or 1)
	int belong;

	// location at unicodePieces
	// also present as which piece this struct is
	int pos;

} PieceInfo;

typedef struct chessplayer
{
	PieceInfo king, queen, rooks[2], knights[2], bishops[2];

	// pawns start from left to right from 1 until 8
	PieceInfo pawns[8];

} ChessPlayer;

// functions definition
void init_chess(ChessPlayer *, unsigned char, int, int, int [][3]);
PieceInfo *get_player_at_coordinate(ChessPlayer *, int, int);
int check_dest_can_move(ChessPlayer *, int, int, int, int);
int if_move_have_barrier(ChessPlayer *, int, int, int, int, double *, int, int);
void display_board(ChessPlayer *, int);
int is_king_dead(ChessPlayer *);

int main()
{
	char clear[10];

#ifdef _WIN32

	// make cmd to support unicode
	SetConsoleOutputCP(65001);

	// internal struct to hold information of current Console
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 16;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"DejaVu Sans Mono");

	// communicate with Windows API to set current console into DejaVu Sans Mono font
	// this was meant to enable Windows Command Prompt to support unicode characters
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	strcpy(clear, "cls"); // window$ use 'cls' to clear screen

#else

	strcpy(clear, "clear"); // unix use 'clear' to clear the screen

#endif

	ifstream inputFile;
	inputFile.open("chess.dat", ios::binary);

	int cond = 0;

	if(inputFile)
	{
		while(1)
		{
			char get_choose;

			cout << endl << endl << " Save file 'chess.dat' found. Want to load save file? [Y/N] : ";
			cin >> get_choose;

			if(get_choose == 'y' || get_choose == 'Y')
			{
				cond = 1;
			}
			else if(get_choose == 'n' || get_choose == 'N')
			{
				remove("chess.dat");
			}
			else
			{
				cout << " Please enter the correct option!" << endl;
				continue;
			}

			break;
		}
	}

	/*
		0 - player 1
		1 - player 2
	*/
	ChessPlayer player[2];

	int src_x, src_y, dest_x, dest_y, turn, get_winner;
	char input_scanf[3];
	PieceInfo *get, *get_temp;

	if(cond == 1)
	{
		// read structs data
		inputFile.read((char *)&player[0], sizeof(ChessPlayer));
		inputFile.read((char *)&player[1], sizeof(ChessPlayer));

		// read variable data
		inputFile.read((char *)&turn, sizeof(int));
		inputFile.read((char *)&src_x, sizeof(int));
		inputFile.read((char *)&src_y, sizeof(int));
		inputFile.read((char *)&dest_x, sizeof(int));
		inputFile.read((char *)&dest_y, sizeof(int));
	}
	else
	{
		turn = 0;

		init_chess(&player[0], 0, 1, 2, pieces_initial_position);
		init_chess(&player[1], 1, 8, 7, pieces_initial_position);

		// initial initialization
		src_x = src_y = dest_x = dest_y = -1;
	}

	while(1) // will always true, and this is infinite loop (until break instruction is called)
	{
		system(clear);

		// get 1 space
		cout << endl;

		// display the board below here
		display_board(player, 1);

		if(src_x != -1)
		{
			get = get_player_at_coordinate(player, dest_x, dest_y);

			cout << endl << "Previous move : " << (char)(src_x + 96) << src_y << " to " << (char)(dest_x + 96) << dest_y << " with "
			<< unicodePieces[get->belong][get->pos] << endl;
		}

		if((get_winner = is_king_dead(player)) != -2)
		{
			cout << endl << "Player " << unicodePieces[get_winner-1][player[get_winner-1].pawns[0].pos]
			<< " [" << get_winner << "] win!" << endl << endl;

			remove("chess.dat");

			break;
		}

		cout << endl << "Player " << unicodePieces[turn][player[turn].pawns[0].pos] << " 's  turn..\n";

		while(1)
		{
			cout << "Please enter source coordinate of your piece : ";

			// very bad method, but whos care?
			scanf("%2s", input_scanf);
			src_x = input_scanf[0] - 96;
			src_y =	input_scanf[1] - 48;

			get = get_player_at_coordinate(player, src_x, src_y);

			if(src_x > 8 || src_y > 8 || get == NULL)
			{
				cout << endl << "Error! Invalid source coordinate [" << src_x << "] [" << src_y << "]" << endl << endl;
				continue;
			}
			else if(get->belong != turn)
			{
				cout << endl << "Sorry! That piece isn't belong to you!" << endl <<endl;
				continue;
			}

			break;
		}

		cout << "You had selected -> " << unicodePieces[get->belong][get->pos] << "  at " << (char)(get->x + 96) << get->y << "\n";

		while(1)
		{
			cout << "Please enter destination coordinate : ";

			// very bad method, but who care?
			scanf("%2s", input_scanf);
			dest_x = input_scanf[0] - 96;
			dest_y = input_scanf[1] - 48;

			if(dest_x > 8 || dest_y > 8)
			{
				cout << endl << "Error! Invalid destination coordinate [" << (char)(dest_x + 96) << "] [" << dest_y << "]" << endl << endl;
				continue;
			}

			// check for common mistakes made by player
			if(!check_dest_can_move(player, src_x, src_y, dest_x, dest_y)) continue;

			break;
		}

		if((get_temp = get_player_at_coordinate(player, dest_x, dest_y)) != NULL)
		{
			get_temp->status = 0;
		}

		get->x = dest_x, get->y = dest_y;  // assign new destination for selected piece

		// if pawns managed to reach top most side of their
		// opponent, then that player can replace that piece with 4 powerful pieces
		if(get->pos == 5 && (get->belong == 0 && get->y == 8) || (get->belong == 1 && get->y == 1))
		{
			system(clear);

			int choose_to_claim, powerful_pieces[4] = { 1, 3, 4, 2 };

			cout << endl; // add 1 space

			for(int i = 0; i < 4; i++)
			{
				cout << " [" << (i+1) << "] " << unicodePieces[get->belong][powerful_pieces[i]] << endl;
			}

			while(1)
			{
				cout << endl << " Please choose one of powerful piece that you want to claim : ";
				cin >> choose_to_claim;

				if(choose_to_claim <= 0 || choose_to_claim > 4)
				{
					cout << endl << " Please choose correct piece to claim!" << endl;
					continue;
				}
				else break;
			}

			get->pos = powerful_pieces[--choose_to_claim];
		}

		// xor with 1 to switch between first & second player
		turn ^= 1;

		remove("chess.dat");

		ofstream outputFile;
		outputFile.open("chess.dat", ios::out | ios::app | ios::binary);

		// write to save file
		outputFile.write((char *)&player[0], sizeof(ChessPlayer));
		outputFile.write((char *)&player[1], sizeof(ChessPlayer));

		// write variable data
		outputFile.write((char *)&turn, sizeof(int));
		outputFile.write((char *)&src_x, sizeof(int));
		outputFile.write((char *)&src_y, sizeof(int));
		outputFile.write((char *)&dest_x, sizeof(int));
		outputFile.write((char *)&dest_y, sizeof(int));
	}
}

void init_chess(ChessPlayer *chess_struct, unsigned char player_num, int first, int second, int init_pos[][3])
{
	for(int z = 0, i = 1; z < 16; z++)
	{
		PieceInfo *each_piece = (PieceInfo *)((char *)chess_struct + (z * sizeof(PieceInfo)));

		int x_orig = (z >= 8) ? i++ : init_pos[z][0];
		int z_orig = (z >= 8) ? 8 : z;
		int y_orig = (z >= 8) ? second : first;

		each_piece->x = x_orig;
		each_piece->y = y_orig;
		each_piece->status = init_pos[z_orig][1];
		each_piece->belong = player_num;
		each_piece->pos = init_pos[z_orig][2];
	}
}

//
// get pointer to PieceInfo struct
// else return NULL if not exist
//
// this function is involving pointer, so ignore this if you can't understand
//
PieceInfo *get_player_at_coordinate(ChessPlayer *player, int x, int y)
{
	for(int i = 0; i < 2; i++)
	{
		for(int z = 0, each_chessplayer = sizeof(ChessPlayer) / sizeof(PieceInfo); z < each_chessplayer; z++)
		{
			PieceInfo *each_piece = (PieceInfo *)((char *)(player + i) + (z * sizeof(PieceInfo)));

			if(each_piece->x == x && each_piece->y == y && each_piece->status == 1)
			{
				return each_piece;
			}
		}
	}

	return NULL;
}

int is_king_dead(ChessPlayer *player)
{
	for(int i = 0; i < 2; i++)
	{
		for(int z = 0, each_chessplayer = sizeof(ChessPlayer) / sizeof(PieceInfo); z < each_chessplayer; z++)
		{
			PieceInfo *each_piece = (PieceInfo *)((char *)(player + i) + (z * sizeof(PieceInfo)));

			if(each_piece->pos == 0 && each_piece->status == 0)
			{
				return each_piece->belong;
			}
		}
	}

	return -2;
}

int check_dest_can_move(ChessPlayer *player, int src_x, int src_y, int dest_x, int dest_y)
{
	PieceInfo *get, *get_temp, *castling;

	get = get_player_at_coordinate(player, src_x, src_y);
	get_temp = get_player_at_coordinate(player, dest_x, dest_y);

	char replace_error[] = "Error! You can't place step into your own piece!";

	if(get_temp != NULL && get_temp->belong == get->belong)
	{
		cout << endl << replace_error << endl << endl;
		return 0;
	}
	else if(get->pos == 0) //king
	{
		// if castling
		if(abs(src_x - dest_x) == 2 && get->x == 5 &&
			((get->belong == 0 && get->y == 1) || ((get->belong == 1 && get->y == 8))))
		{
			if((dest_x > src_x && ((castling = get_player_at_coordinate(player, 8, get->y)) != NULL
				&& castling->pos == 2))
				||
				(dest_x < src_x && (castling = get_player_at_coordinate(player, 1, get->y)) != NULL
				&& castling->pos == 2 && get_player_at_coordinate(player, get->x, 2) == NULL))
			{
				castling->x = (dest_x > src_x) ? 6 : 4;
			}

			return 1;
		}
		else if(abs(src_y - dest_y) > 1 || abs(src_x - dest_x) > 1) // king can't move more than 1 step
		{
			cout << endl << "Error! King can only move 1 step!" << endl << endl;
			return 0;
		}
	}
	else if(get->pos == 1) // queen
	{
		double gradients[3] = { -1, 1, 0};

		int check = if_move_have_barrier(player, src_x, src_y, dest_x, dest_y, gradients, 3, 1);

		if(check != 1)
		{
			return 0;
		}
	}
	else if(get->pos == 2) // bishop
	{
		double gradients[1] = {0};

		int check = if_move_have_barrier(player, src_x, src_y, dest_x, dest_y, gradients, 1, 1);

		if(check != 1)
		{
			return 0;
		}
	}
	else if(get->pos == 3) // rooks
	{
		double gradients[2] = {-1, 1};

		int check = if_move_have_barrier(player, src_x, src_y, dest_x, dest_y, gradients, 2, 0);

		if(check != 1)
		{
			return 0;
		}
	}
	else if(get->pos == 4) // knight
	{
		// knight have 8 possible movements with L shape
		int move[8][2] =
		{
			{-2, 1}, {-1, 2}, {1, 2},
			{2, 1}, {2, -1}, {1, -2},
			{-1, -2}, {-2, -1}
		};
		int check = 0;

		for(int i = 0; i < 8 && !check; i++)
		{
			if((src_x + move[i][0]) == dest_x && (src_y + move[i][1]) == dest_y)
			{
				check++;
			}
		}

		if(!check)
		{
			cout << endl << "Error! Knight movement must equivalent to L shape movement!" << endl << endl;
			return 0;
		}
	}
	else // pawns
	{
		char movetwosteps[] = "Error! Pawn can only move 2 steps at the initial of the game!";
		char cantmovepawn[] = "Error! You can't move into that position!";

		// check if pawn try to move backward, if true then give user a warning
		if((get->belong == 0 && src_y >= dest_y) || (get->belong == 1 && src_y <= dest_y))
		{
			cout << endl << "Error! Pawn can only move forward!" << endl << endl;
			return 0;
		}

		// dats lot of logics :P
		// check if pawn try to move diagonal while there's no piece there (give warning)
		if((get->belong == 0 && (((src_x - 1) == dest_x && (src_y + 1) == dest_y) || ((src_x + 1) == dest_x && (src_y + 1) == dest_y))) ||
			(get->belong == 1 && (((src_x - 1) == dest_x && (src_y - 1) == dest_y) || ((src_x + 1) == dest_x && (src_y - 1) == dest_y))))
		{
			if(get_temp == NULL)
			{
				cout << endl << cantmovepawn << endl << endl;
				return 0;
			}
			else if(get->belong == get_temp->belong)
			{
				cout << endl << replace_error << endl << endl;
				return 0;
			}
		}

		//
		// abs = absolute value, because distant is always positive
		//
		if(abs(dest_y - src_y) == 2)
		{
			if((get->belong == 0 && src_y != 2) || (get->belong == 1 && src_y != 7))
			{
				cout << endl << movetwosteps << endl << endl;
				return 0;
			}
			else if(get->belong == 1 && src_y != 7)
			{
				cout << endl << movetwosteps << endl << endl;
				return 0;
			}
		}
		else if(abs(dest_y - src_y) > 2)
		{
			cout << endl << "Error! Pawn can only move 1 step! (or 2 at beginning) " << endl << endl;
			return 0;
		}
		else if(abs(dest_y - src_y) == 1 && src_x == dest_x && get_temp != NULL)
		{
			cout << endl << cantmovepawn << endl << endl;
			return 0;
		}

	}

	return 1;
}

/*
  return code value :-

   1 = no problem at all :)
  -3 = has problem(s)
*/
int if_move_have_barrier(ChessPlayer *player, int src_x, int src_y, int dest_x, int dest_y, double *gradients, int size_gradients, int check_x)
{

	char invalid_coordinate[] = "Error! Invalid destination coordinate! Please check again.";
	char barrier_error[] = "Error! Piece can't move because there's a barrier before destination.";

	// only 3 gradients, 1 is undefined (have to check manually)
	double m = 0, check = 0;
	PieceInfo *get;
	int test = 0;

	if(check_x && src_x == dest_x) // if same line at x, then +1 into check variable
	{
		check = 10.0, test++; // 10 = special gradient value
	}
	else if(src_x != dest_x)
	{
		m = (dest_y - src_y)/(dest_x - src_x);
	}

	for(int i = 0; i < size_gradients && !test; i++)
	{
		if(m == gradients[i])
		{
			check = gradients[i], test++;
		}
	}

	if(!test)
	{
		cout << endl << invalid_coordinate << endl << endl;
		return -3;
	}
	else if(check == 10.0 || check == -1.0 || check == 1.0 || check == 0.0) // if 4 graph gradients direction (10 is special value)
	{
		for(int i = 0; !(src_y == dest_y && src_x == dest_x); )
		{
			if(i++ && get_player_at_coordinate(player, src_x, src_y) != NULL)
			{
				cout << endl << barrier_error << endl << endl;
				return -3;
			}

			if(check) // if gradient is not zero (which is 1 ,-1 or 10)
			{
				if(dest_y > src_y)
				{
					src_y++;

					if(check == -1.0) src_x--;
					else if(check == 1.0) src_x++;
				}
				else
				{
					src_y--;

					if(check == 1.0) src_x--;
					else if(check == -1.0) src_x++;
				}
			}
			else
			{
				if(src_x < dest_x) src_x++;
				else src_x--;
			}
		}
	}

	return 1;

}

//
// u can make ur own board if u want :)
//
void display_board(ChessPlayer *player, int display_line)
{
	PieceInfo *get;

	char alphabet[] = "     a   b   c   d   e   f   g   h";
	char line[] = "   ---------------------------------";

	cout << alphabet << endl;

	if(display_line)
	{
		cout << line << endl;
	}

	for(int i = 1; i <= 8; i++) // y-axis
	{
		cout << " " << (9-i) << " |";

		for(int z = 1; z <= 8; z++) // x-axis
		{
			get = get_player_at_coordinate(player, z, 9 - i);

			if(get == NULL || !get->status)
			{
				cout << "   |";
			}
			else
			{
				cout << " " << unicodePieces[get->belong][get->pos] << " |";
			}
		}

		cout << " " << (9-i) << endl;

		if(display_line)
		{
			cout << line << endl;
		}
	}

	cout << alphabet << endl;
}
