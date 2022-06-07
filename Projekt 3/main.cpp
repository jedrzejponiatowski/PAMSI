#include <iostream>
#include <vector>
#include <array>
#include "tictactoe.hh"

using namespace std;

extern int COUNTER1, COUNTER2;
extern int MAX_DEPTH;

int depth_array[]={7,6,5,4,4,4,4};

int main()
{
    cout << "\n************************************" << endl
         << "            TIC TAC TOE             " << endl << endl;

    int dim;
    cout << "  Enter the dimension of the board [3-9]   >";
    cin >> dim;

    while(dim>9 || dim<3){
        cout << "  Wrong dimension. Type a number between 3-9.  >";
        cin >> dim;
    }
    cout << endl;
    
    int num_in_row;
    cout << "  Enter the number of markers in row to win [3-" << dim <<"]   >";
    cin >> num_in_row;

    while(num_in_row>dim || num_in_row<3){
        cout << "  Wrong. Type a number between [3-" << dim <<"]   >";
        cin >> num_in_row;
    }
    cout << endl;

    MAX_DEPTH=depth_array[dim-3];

	char **board = allocation(dim);
	print_board(board,dim);

	while (!game_is_done(board,dim,num_in_row))
	{
		int row, col;
		cout << "  your play 'X': \"row col\" > ";
		cin >> row;
		cin >> col;
		cout << endl << endl;

		if (position_occupied(board,dim, choice{row-1,col-1,0})){
			cout << "  The position (" << row << ", " << col << ") is occupied. Try another one..." << endl;
			continue;
		}
		else
		{
			board[row-1][col-1] = PLAYER;
		}

        if(game_is_done(board,dim,num_in_row))
            break;

		choice ai_move = minimax_optimization(board,dim,num_in_row, AI, 0, LOSS, WIN);

		board[ai_move.x][ai_move.y] = AI;

		print_board(board,dim);
	}

	print_board(board,dim);

	cout << "********** GAME OVER **********" << endl << endl;

	int player_state = get_board_state(board,dim,num_in_row, PLAYER);

	cout << "  PLAYER "; print_game_state(player_state);

    cout << endl << "  Number of alpha-beta pruning:  " << COUNTER2 << endl << endl;

	return 0;

}

