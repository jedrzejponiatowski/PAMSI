#ifndef TICTACTOE_HH
#define TICTACTOE_HH

#include <iostream>
#include <vector>

using namespace std;


/* it does what ya think it does*/
typedef struct{
    int x,y,score;
} choice;


#define WIN 1000
#define	DRAW 0
#define LOSS -1000

#define AI 'O'
#define PLAYER 'X'
#define SPACE ' '


/*!
    \brief Minmax algorithm with alpha-beta pruning
    \param board double dimensional array
    \param dim dimension of the board
    \param num_in_row number of markers in winning sequence
    \param marker Your opponent marker
    \param depth Starting depth
    \param alpha minimal limit for pruning (LOSS value)
    \param beta maximal limit for pruning (WIN value) 
*/
choice minimax_optimization(char **board, int dim, int num_in_row, char marker, int depth, int alpha, int beta);



/*!
    \brief Print the final result of the game
    \param state WIN,DRAW or LOSS
    */
void print_game_state(int state);



/*!
    \brief Allocation of the DIM x DIM board
    \param dim dimension of the board
*/
char ** allocation(int dim);



/*!
    \brief Print the board of chosen dimension
    \param board double dimensional array
    \param dim dimenion of the board
*/
void print_board(char **board, int dim);



/*!
    \brief Get all of the legal moves on the board
    \return vector of structs choice (x,y,score)
    \param board double dimensional array
    \param dim dimension of the board
*/
vector<choice> get_legal_moves(char **board,int dim);



/*!
    \brief Check if the posision is occupied
    \param board double dimensional array
    \param dim dimension of the board
    \param pos struct to check if is occupied
*/
bool position_occupied(char **board, int dim, choice pos);



/*! 
    \brief Check if the board is full
    \param board double dimensional array
    \param dim dimension of the board
*/
bool board_is_full(char **board, int dim);



/*!
    \brief Check if the game has been won
    \param board double dimensional array
    \param marker check if that marker made a winning sequence
    \param dim dimension of the board
    \param num_in_row number of markers in winning sequence
*/
bool game_is_won(char **board, char marker, int dim, int num_in_row);

   

/*!
    \brief It returns the opponent marker
    \param marker actual marker (PLAYER or AI) 
*/
char get_opponent(char marker);



/*!
    \brief Check if someone has won or lost
    \param board double dimensional array
    \param dim dimension of the board
    \param num_in_row number of markers in winning sequence
    \param marker check if that marker made a winning sequence
*/
int get_board_state(char **board, int dim, int num_in_row, char marker);



/*!
    \brief Check if the game is finished
     \param board double dimensional array
    \param dim dimension of the board
    \param num_in_row number of markers in winning sequence
*/
bool game_is_done(char **board, int dim, int num_in_row);








#endif