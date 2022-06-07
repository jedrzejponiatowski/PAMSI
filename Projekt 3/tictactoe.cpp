#include "tictactoe.hh"

int COUNTER1, COUNTER2;

int MAX_DEPTH;



void print_game_state(int state)
{
	if (WIN == state) { cout << "WIN" << endl; }
	else if (DRAW == state) { cout << "DRAW" << endl; }
	else if (LOSS == state) { cout << "LOSS" << endl; }
}




char ** allocation(int dim){
    char ** array = new char *[dim];
    for(int i=0;i<dim;i++){
        array[i]=new char[dim];
    }
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++)
            array[i][j]=SPACE;
    }
    return array;
}




void print_board(char **board, int dim){
    cout << endl;
    for(int i=0; i<dim; i++){
        cout << "\t";
        for(int j=0; j<dim; j++){
            cout << board[i][j];
            if(j!=dim-1)
                cout << "|";
            if(j==dim-1 && i!=dim-1){
            cout << endl;
            cout << "\t";
            for(int k=0; k<dim*2;k++)
                cout<<"-";
            cout<< endl;
            }
        }
    }
    cout << endl << endl;
}



std::vector<choice> get_legal_moves(char **board,int dim){

    vector<choice> legal_moves;
    for(int i=0; i<dim; i++){
        for(int j=0;j<dim;j++){
            if(board[i][j]==SPACE)
                legal_moves.push_back(choice{i,j,0});
        }
    }
    return legal_moves;
}



bool position_occupied(char **board, int dim, choice pos){
	std::vector<choice> legal_moves = get_legal_moves(board,dim);

	for (int i = 0; i < legal_moves.size(); i++){
		if (pos.x == legal_moves[i].x && pos.y == legal_moves[i].y)
			return false;
	}

	return true;
}



bool board_is_full(char **board, int dim)
{
	std::vector<choice> legal_moves = get_legal_moves(board, dim);

	if (0 == legal_moves.size())
		return true;
	else
		return false;
	
}



bool game_is_won(char **board, char marker, int dim, int num_in_row) 
{
    int counter=0;

    //horizontal
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(board[i][j]==marker){
                counter++;
                if(counter==num_in_row)
                    return true;
            }
            else counter=0;
        }
        counter=0;
    }

    counter=0;
    //vertical
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(board[j][i]==marker){
                counter++;
                if(counter==num_in_row)
                    return true;
            }
            else counter=0;
        }
        counter=0;
    }

    counter=0;
    bool tmp;
    //diagonal v1
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(board[i][j]==marker){
                int k=i;
                int m=j;
                tmp=true;
                counter++;
                while(tmp){
                    if( (k<(dim-1)) && (m<(dim-1)) ){
                        if(board[k+1][m+1]==marker){
                            counter++;
                            k++; m++;
                            if(counter==num_in_row)
                                return true;
                        }
                        else {
                            counter=0;
                            break;
                        }
                    }
                    else {
                        counter=0;
                        break; 
                    }
                }
            }
            else counter=0;
        }
       
    }

    //diagonal v2
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(board[i][j]==marker){
                int k=i;
                int m=j;
                tmp=true;
                counter++;
                while(tmp){
                    if( (k<(dim-1)) && (m>0) ){
                        if(board[k+1][m-1]==marker){
                            counter++;
                            k++; m--;
                            if(counter==num_in_row)
                                return true;
                        }
                        else {
                            counter=0;
                            break;
                        }
                    }
                    else {
                        counter=0;
                        break; 
                    }
                }
            }
            else counter=0;
        }
    }

    return false;
	
}



char get_opponent(char marker){
	if (marker == PLAYER)
        return AI;
    else return PLAYER;
}



int get_board_state(char **board, int dim, int num_in_row, char marker)
{

	char opponent = get_opponent(marker);

	bool won = game_is_won(board,marker,dim,num_in_row);

	if (won)
		return WIN;
	 
    won = game_is_won(board,opponent,dim,num_in_row);

	if (won)
		return LOSS;
	
	return DRAW;
}




choice minimax_optimization(char **board, int dim, int num_in_row, char marker, int depth, int alpha, int beta)
{
    COUNTER1++;
	choice best_move{-1,-1,-1};
	int best_score = (marker == AI) ? LOSS : WIN;


	if (board_is_full(board,dim) || DRAW != get_board_state(board,dim, num_in_row, AI) || depth==MAX_DEPTH)
	{
		best_score = get_board_state(board,dim,num_in_row, AI);
		return choice{best_move.x, best_move.y, best_score};
	}

	std::vector<choice> legal_moves = get_legal_moves(board,dim);

	for (int i = 0; i < legal_moves.size(); i++)
	{
		choice curr_move = legal_moves[i];
		board[curr_move.x][curr_move.y] = marker;

	
		if (marker == AI)
		{
			int score = minimax_optimization(board,dim,num_in_row, PLAYER, depth + 1, alpha, beta).score;

			
			if (best_score < score)
			{
				best_score = score - depth * 10;
				best_move = curr_move;

				
				alpha = std::max(alpha, best_score);
				board[curr_move.x][curr_move.y] = SPACE;
				if (beta <= alpha){ 
                    COUNTER2++;
					break; 
				}
			}

		} 
		else
		{
			int score = minimax_optimization(board,dim,num_in_row, AI, depth + 1, alpha, beta).score;

			if (best_score > score)
			{
				best_score = score + depth * 10;
				best_move = curr_move;


				beta = std::min(beta, best_score);
				board[curr_move.x][curr_move.y] = SPACE;
                
				if (beta <= alpha){ 
                    COUNTER2++;
					break; 
				}
			}

		}

		board[curr_move.x][curr_move.y] = SPACE; 

	}

	return choice{best_move.x,best_move.y,best_score};
}



bool game_is_done(char **board, int dim, int num_in_row)
{
	if (board_is_full(board,dim))
		return true;
	

	if (DRAW != get_board_state(board,dim,num_in_row, AI))
		return true;
	

	return false;
}