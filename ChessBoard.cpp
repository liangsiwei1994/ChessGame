#include <iostream>
#include "ChessBoard.h"

using namespace std;

ChessBoard::ChessBoard() {

    /* Initiate a NULL pointer for the all positions on the board */
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++)
            board[i][j] = NULL;
    }

    /* Construct the new ChessPieces for white team */
    board[0][0] = new RookPiece('w');
    board[0][7] = new RookPiece('w');
    board[0][1] = new KnightPiece('w');
    board[0][6] = new KnightPiece('w');
    board[0][2] = new BishopPiece('w');
    board[0][5] = new BishopPiece('w');
    board[0][3] = new QueenPiece('w');
    board[0][4] = new KingPiece('w');
    for (int i=0; i<8; i++) 
        board[1][i] = new PawnPiece('w');
    
    /* Construct the new ChessPieces for black team */
    board[7][0] = new RookPiece('b');
    board[7][7] = new RookPiece('b');
    board[7][1] = new KnightPiece('b');
    board[7][6] = new KnightPiece('b');
    board[7][2] = new BishopPiece('b');
    board[7][5] = new BishopPiece('b');
    board[7][3] = new QueenPiece('b');
    board[7][4] = new KingPiece('b');
    for (int i=0; i<8; i++)
        board[6][i] = new PawnPiece('b');

    /* Intialise the king pieces' locations */
    black_kings_location[0] = 7;
    black_kings_location[1] = 4;
    white_kings_location[0] = 0;
    white_kings_location[1] = 4;

    /* Initialise the bool variable to indicate that it's white team's turn first */
    white = true;

    /* Initialise the state of the game */
    game_over = false;

    cout << "A new chess game is started!" << endl;
}



bool ChessBoard::check_valid_str_position(string const old_position, string const new_position) const {
    
    /* Ensure that both positions' strings are of length 2 */
    if ((old_position.length() != 2) || (new_position.length() !=2))
        return false;
    /* Ensure that the source square's file is within A to H */
    if ((old_position[0] < 'A') || (old_position[0] > 'H'))
        return false;
    /* Ensure that the source square's rank is within 1 to 8 */
    if ((old_position[1] < '1') || (old_position[1] > '8'))
        return false;
    /* Ensure that the destination square's file is within A to H */
    if ((new_position[0] < 'A') || (new_position[0] > 'H'))
        return false;
    /* Ensure that the destination square's rank is within 1 to 8 */
    else if ((new_position[1] < '1') || (new_position[1] > '8'))
        return false;
    return true;
}



bool ChessBoard::check_king_test(int const king_rank, int const king_file) const {
    
    /* Identify the king piece we are looking at */
    ChessPiece* king_piece = board[king_rank][king_file];

    /* Iterate through the board and check if any of them can move to the king's position, based only on piece's logic and if is there an obstruction */
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            ChessPiece* test_piece = board[i][j];
            /* Begin checks if the position we are looking at 1. is not empty, 2. is not the king's position we are looking at, 3. contains an opponent's piece */
            if ((test_piece != NULL) && ((i != king_rank) || (j != king_file)) && (test_piece->get_team() != king_piece->get_team())) {
                /* Attempt to move the piece to the king position we are looking at. */
                if (test_piece->check_piece_logic(i, j, king_rank, king_file, board) && !(test_piece->check_obstruction(i, j, king_rank, king_file, board))) {
                    return true;
                }
            }
        }
    }
    return false;
};



void ChessBoard::temp_make_move(int const old_rank, int const old_file, int const new_rank, int const new_file, ChessPiece *(&temp)) {
        /* Temporarily store the new location to for undo_move() later */
        temp = board[new_rank][new_file];
        board[new_rank][new_file] = board[old_rank][old_file];
        /* Set the source position to point to null if it's not the same position. */
        if (!((new_rank == old_rank) && (new_file == old_file))) 
            board[old_rank][old_file] = NULL;
}



void ChessBoard::undo_temp_move(int const old_rank, int const old_file, int const new_rank, int const new_file, ChessPiece *(&temp)) {
        board[old_rank][old_file] = board[new_rank][new_file];
        /* Place the temporarile removed chess piece back to it's original position */
        board[new_rank][new_file] = temp;
}



void ChessBoard::make_move(int const old_rank, int const old_file, int const new_rank, int const new_file) {

    /* Get the characters of the rank and file of the source and destination squares for printing. */
    char old_rank_char = '1' + old_rank, 
    old_file_char = 'A' + old_file, 
    new_rank_char = '1' + new_rank, 
    new_file_char = 'A' + new_file;

    /* If the destination square is not empty. */
    if (board[new_rank][new_file] != NULL) {
        cout << board[old_rank][old_file]->get_team() << "'s " << board[old_rank][old_file]->get_cptype() << " moves from " << old_file_char << old_rank_char << " to " << new_file_char << new_rank_char << " taking " << board[new_rank][new_file]->get_team() << "'s " << board[new_rank][new_file]->get_cptype() << endl;
        /* Remove the opponent's piece. */
        delete board[new_rank][new_file];
        /* Make the destination source point to the moved chess piece. */
        board[new_rank][new_file] = board[old_rank][old_file];
        board[old_rank][old_file] = NULL;
        /* Increase the move counter of the moved piece. */
        board[new_rank][new_file]->increase_move_counter();
    }
    /* If the destination square is empty. */
    else {
        cout << board[old_rank][old_file]->get_team() << "'s " << board[old_rank][old_file]->get_cptype() << " moves from " << old_file_char << old_rank_char << " to " << new_file_char << new_rank_char << endl;
        board[new_rank][new_file] = board[old_rank][old_file];
        board[old_rank][old_file] = NULL;
        board[new_rank][new_file]->increase_move_counter();
    }
}



int ChessBoard::valid_move_counter(int const king_rank, int const king_file) {

    /* Initialize the counter which counts the number of valid move. */
    int counter = 0;
    /* Begin iterating through the board, where i and j representing the rank and file of the position where the chess piece (if exist), will be moved from. */
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            
            /* Check and only attempt to move the chess piece if the current location has an opponent's chess piece. */
            if (board[i][j] != NULL) {
                ChessPiece* test_piece = board[i][j];
                if (test_piece->get_team() == board[king_rank][king_file]->get_team()) {
                    
                    /* k and l represents the position we attempt to move the chess piece to. */
                    for (int k=0; k<8; k++){
                        for (int l=0; l<8; l++) {
                            
                            /* Check if the new position is valid based on the piece's logic, if there is obstruction and if there the destination is occupied by own team's chess piece. */
                            if ((test_piece->valid_move(i, j, k, l, *this))) {
                                
                                /* Create a temp piece to undo the simulated move. */
                                ChessPiece *temp_piece = NULL;
                                /* Simulate the final configuration after the move */
                                temp_make_move(i, j, k, l, temp_piece);

                                int temporary_king_rank, temporary_king_file;
                                
                                /* Temporarily obtain the location of the king for the check_king_test() if the current piece being checked is the opponent's king piece. */
                                if ((i==king_rank) && (j==king_file)) {
                                    temporary_king_rank = k;
                                    temporary_king_file = l;
                                }
                                else {
                                    temporary_king_rank = king_rank;
                                    temporary_king_file = king_file;
                                }
                                
                                /* If the simulated move for opponent's team does not leave it's own king in check (and is valid from above), increase count of valid move for opponent */
                                if (!(check_king_test(temporary_king_rank, temporary_king_file))) {
                                    counter++;
                                }

                                /* Undo the simulation */
                                undo_temp_move(i, j, k, l, temp_piece);
                            }
                        }
                    }
                }
            }
        }
    }
    return counter;
}



void ChessBoard::submitMove(string const old_position, string const new_position) {

    /* Check if the game is over */
    if (game_over) {
        cout << "Game is over, no move is allowed." << endl;
        return;
    }

    /* Check that both arguments passed for source and destination sqaures are valid */
    if(!(check_valid_str_position(old_position, new_position))) {
        cout << "Invalid position entered." << endl;
        return;
    }

    /* Get the integer value of the source and destination squares rank and file in numbers from 0 to 7. */
    int old_rank = old_position[1] - '1';
    int old_file = old_position[0] - 'A';
    int new_rank = new_position[1] - '1';
    int new_file = new_position[0] - 'A';

    /* Get the current team that is making the move. */
    string current_team;
    if (white)
        current_team = "White";
    else
        current_team = "Black";
    
    /* Get the chess piece being moved. */
    ChessPiece* moved_piece = board[old_rank][old_file];

    /* Check if there is a chess piece at the source square. */
    if (moved_piece == NULL) {
        cerr << "There is no piece at position " << old_position << "!" << endl;
        return;
    }

    /* Start castling check if moved piece is an unmoved king and position moved is 2 squares along the same rank. */
    if ((moved_piece->get_cptype() == "King") && (moved_piece->get_move_count() == 0) && (abs(old_file-new_file) == 2) && (moved_piece->get_team() == current_team)) {
        if (castling_check(old_file, new_file)) {
            make_castling_move(old_rank, old_file, new_rank, new_file);
        }
        /* If castling check fails, do nothing then exit for user to resubmit valid move. */
        else {
            return;
        }
    }
    /* Otherwise, perform normal checks */
    else {        
        /* Check if the current turn belongs to the team of the piece at the source square. */
        if (moved_piece->get_team() != current_team) {
            cout << "It is not " << moved_piece->get_team() << "'s turn to move!" << endl;
            return;
        }

        /* Boolean variables for the checks before making the move officially. */
        bool move_valid, own_king_check;
        
        /* Check if the move is valid based on the current piece's logic and if there is an obstruction along the way. */
        move_valid = moved_piece->valid_move(old_rank, old_file, new_rank, new_file, *this);
        
        /* Create a temporary piece for un-doing move later */
        ChessPiece* temp_piece = NULL;
        /* Simulate the board config after making the move */
        temp_make_move(old_rank, old_file, new_rank, new_file, temp_piece);

        /* Identify king's position based on whether or not the moved piece is a king chess piece. */
        int new_own_king_location[2];
        if (moved_piece->get_cptype() == "King"){
                new_own_king_location[0] = new_rank;
                new_own_king_location[1] = new_file;
        }
        else {
            if (moved_piece->get_team() == "White") {
                new_own_king_location[0] = white_kings_location[0];
                new_own_king_location[1] = white_kings_location[1];
            }
            else {
                new_own_king_location[0] = black_kings_location[0];
                new_own_king_location[1] = black_kings_location[1];
            }
        }

        /* Check if the move will leave it's own king in check. */
        own_king_check = check_king_test(new_own_king_location[0], new_own_king_location[1]);

        /* If move is valid and does not leave own king in check, make the move officially. */
        if (move_valid && !own_king_check) {
            undo_temp_move(old_rank, old_file, new_rank, new_file, temp_piece);
            make_move(old_rank, old_file, new_rank, new_file);
        }
        /* If the move is not valid, reject the move entirely and print the following error message. */
        else {
            undo_temp_move(old_rank, old_file, new_rank, new_file, temp_piece);
            cout << board[old_rank][old_file]->get_team() << "'s " << board[old_rank][old_file]->get_cptype() << " cannot move to "<< new_position << "!" << endl;
            return;
        }
    }

    moved_piece = board[new_rank][new_file];
    
    /* Update the kings position on the board if the moved chess piece is a king chess piece. */
    if ((moved_piece->get_cptype() == "King") && moved_piece->get_team() == "White") {
        white_kings_location[0] = new_rank;
        white_kings_location[1] = new_file;
    }
    else if ((moved_piece->get_cptype() == "King") && !(moved_piece->get_team() == "White")) {
        black_kings_location[0] = new_rank;
        black_kings_location[1] = new_file;
    }

    /* Identify opponent's king position. */
    int opponent_king_location[2];
    if (white) {
        opponent_king_location[0] = black_kings_location[0];
        opponent_king_location[1] = black_kings_location[1];
    }
    else {
        opponent_king_location[0] = white_kings_location[0];
        opponent_king_location[1] = white_kings_location[1];
    }

    /* Calculate the number of moves available for the opponent after current move. */
    int available_moves_after_this = valid_move_counter(opponent_king_location[0], opponent_king_location[1]);

    /* Check if the current move leaves opponent's king in check. */
    bool check = check_king_test(opponent_king_location[0], opponent_king_location[1]);

    /* If current move leaves the opponent's king in check and opponent has 0 valid move next, the current move checkmates the opponent. */
    if ((available_moves_after_this <= 0) && check) {
        cout << board[opponent_king_location[0]][opponent_king_location[1]]->get_team() << " is in checkmate" << endl;
        white = !white;
        game_over = true;
        return;
    }
    /* If current move leaves the opponent's king in check and opponent has more than 0 valid moves next, the current move checks the opponent. */
    if ((available_moves_after_this > 0) && check) {
        cout << board[opponent_king_location[0]][opponent_king_location[1]]->get_team() << " is in check" << endl;
        white = !white;
        return;
    }
    /* If current move does not leave the opponent's king in check and opponent 0 valid moves next, the game ends with a stalemate. */
    if ((available_moves_after_this <= 0) && !check) {
        cout << board[opponent_king_location[0]][opponent_king_location[1]]->get_team() << " has no move after this. Stalemate!" << endl;
        white = !white;
        game_over = true;
        return;
    }
    /* If current move does not leave the opponent's king in check and opponent has more than 0 valid moves next, the game continues per normal. */
    if ((available_moves_after_this > 0) && !check) {
        /* Update that the next move is to be made by team of another color. */
        white = !white;
        return;
    }

}



void ChessBoard::resetBoard() {

    /* Delete all the exsiting chess pieces the board is pointing to and set the pointer to null. */
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (board[i][j] != NULL) {
                delete board[i][j];
                board[i][j] = NULL;
            }
        }
    }

    /* Re-construct the new chess pieces for white team. */
    board[0][0] = new RookPiece('w');
    board[0][7] = new RookPiece('w');
    board[0][1] = new KnightPiece('w');
    board[0][6] = new KnightPiece('w');
    board[0][2] = new BishopPiece('w');
    board[0][5] = new BishopPiece('w');
    board[0][3] = new QueenPiece('w');
    board[0][4] = new KingPiece('w');
    for (int i=0; i<8; i++) 
        board[1][i] = new PawnPiece('w');

    /* Re-construct the new chess pieces for black team. */
    board[7][0] = new RookPiece('b');
    board[7][7] = new RookPiece('b');
    board[7][1] = new KnightPiece('b');
    board[7][6] = new KnightPiece('b');
    board[7][2] = new BishopPiece('b');
    board[7][5] = new BishopPiece('b');
    board[7][3] = new QueenPiece('b');
    board[7][4] = new KingPiece('b');
    for (int i=0; i<8; i++)
        board[6][i] = new PawnPiece('b');

    /* Re-initialise the king's location for both teams. */
    black_kings_location[0] = 7;
    black_kings_location[1] = 4;
    white_kings_location[0] = 0;
    white_kings_location[1] = 4;

    /* Re-initialise the indicator to show that it's white team's turn again. */
    white = true;

    /* Re-initialise the state of the game */
    game_over = false;

    cout << "A new chess game is started!" << endl;
}



ChessBoard::~ChessBoard() {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (board[i][j] != NULL) {
                /* Delete all existing chess pieces. */
                delete board[i][j];
                /* Set the chess piece pointer at each position to be null. */
                board[i][j] = NULL;
            }
        }
    }
}



/* Functions after here are for castling */

bool ChessBoard::castling_check(int const old_king_file, int const new_king_file) {
    
    int king_rank;
    
    /* Get the rank of the king chess piece */
    if (white) {
        king_rank = white_kings_location[0];
    }
    else {
        king_rank = black_kings_location[0];
    }

    /* Check if there is obstruction between the king and the rook */
    if (!(castling_obstruction_check(old_king_file, new_king_file, king_rank))) {
        cout << "There is obstruction between the king and the rook piece. Castling not valid." << endl;
        return false;
    };

    /* Check if there is a valid rook piece for castling */
    if (!(castling_rook_check(old_king_file, new_king_file, king_rank))) {
        cout << "There is no valid rook chess piece. Castling not valid." << endl;
        return false;
    };

    /* Check if the king will be checked from it's original position to the new position when castling */
    if (!(castling_king_check(old_king_file, new_king_file, king_rank))) {
        cout << "King get's checked while castling, castling is not valid." << endl;
        return false;
    };

    return true;
}



bool ChessBoard::castling_king_check(int const old_king_file, int const new_king_file, int const king_rank) {
    /* Create new file for iteration to check if the king is in check as it moves to and when it is at it's new position */
    int king_file_checked = old_king_file;

    /* When the king moves to the king side */
    if (old_king_file < new_king_file) {
        /* Move from the old position to the new position to see if the king piece will get checked */
        while (king_file_checked <= new_king_file) {
            /* Create a temporary piece for un-doing move later */
            ChessPiece *temp_piece;
            /* Simulate the board config after making the move */
            temp_make_move(king_rank, old_king_file, king_rank, king_file_checked, temp_piece);
            /* Check if the king can be checked as it moves along the rank */
            if (check_king_test(king_rank, king_file_checked)) {
                /* Undo the temporary move */
                undo_temp_move(king_rank, old_king_file, king_rank, king_file_checked, temp_piece);
                return false;
            }
            undo_temp_move(king_rank, old_king_file, king_rank, king_file_checked, temp_piece);
            king_file_checked++;
        }
    }

    /* When the king moves to the queen side */
    if (old_king_file > new_king_file) {
        /* Move from the old position to the new position to see if the king piece will get checked */
        while (king_file_checked >= new_king_file) {
            ChessPiece *temp_piece;
            temp_make_move(king_rank, old_king_file, king_rank, king_file_checked, temp_piece);
            if (check_king_test(king_rank, king_file_checked)) {
                undo_temp_move(king_rank, old_king_file, king_rank, king_file_checked, temp_piece);
                return false;
            }
            undo_temp_move(king_rank, old_king_file, king_rank, king_file_checked, temp_piece);
            king_file_checked--;
        }
    }
    return true;

}



bool ChessBoard::castling_obstruction_check(int const old_king_file, int const new_king_file, int const king_rank) const {
    /* When the king moves to the king side */
    if (old_king_file < new_king_file) {
        for (int i = old_king_file + 1; i<7; i++) {
            if(board[king_rank][i] != NULL)
                return false;
        }
    }

    /* When the king moves to the queen side */
    if (old_king_file > new_king_file) {
        for (int i = old_king_file - 1; i>0; i--) {
            if(board[king_rank][i] != NULL)
                return false;
        }
    }
    return true;
}



bool ChessBoard::castling_rook_check(int const old_king_file, int const new_king_file, int const king_rank) const {
    /* When the king moves to the king side */
    if (old_king_file < new_king_file) {
        if(board[king_rank][7] != NULL) {
            /* Make sure that the chess piece at rook's original position is a rook piece and it has not make any move yet. */
            if((board[king_rank][7]->get_cptype() != "Rook") || (board[king_rank][7]->get_move_count() != 0) || (board[king_rank][7]->get_team() != board[king_rank][old_king_file]->get_team()))
                return false;
        }
        else {
            /* The check fails if there is no chess piece to begin with at the corner */
            return false;
        }
    }

    /* Do the same as above when the king moves to the queen side */
    if (old_king_file > new_king_file) {
        if(board[king_rank][0] != NULL) {
            if((board[king_rank][0]->get_cptype() != "Rook") || (board[king_rank][0]->get_move_count() != 0) || (board[king_rank][0]->get_team() != board[king_rank][old_king_file]->get_team())) 
                return false;
        }
        else {
            return false;
        }
    }
    return true;
}



void ChessBoard::make_castling_move(int const old_rank, int const old_file, int const new_rank, int const new_file) {
    /* Get the characters of the rank and file of the source and destination squares for printing. */
    char old_rank_char = '1' + old_rank, 
    old_file_char = 'A' + old_file, 
    new_rank_char = '1' + new_rank, 
    new_file_char = 'A' + new_file;

    /* Print the castling message */
    if (old_file > new_file)
        cout << board[old_rank][old_file]->get_team() << "'s " << board[old_rank][old_file]->get_cptype() << " castles queen side from " << old_file_char << old_rank_char << " to " << new_file_char << new_rank_char << "." << endl;
    else
        cout << board[old_rank][old_file]->get_team() << "'s " << board[old_rank][old_file]->get_cptype() << " castles king side from " << old_file_char << old_rank_char << " to " << new_file_char << new_rank_char << "." << endl;
    
    /* Make move for king piece */
    /* Make the destination square point to the moved chess piece. */
    board[new_rank][new_file] = board[old_rank][old_file];
    board[old_rank][old_file] = NULL;
    /* Increase the move counter of the moved piece. */
    board[new_rank][new_file]->increase_move_counter();

    /* Make move for rook piece */
    /* When the king moves to the king side */
    if (old_file < new_file) {
        /* Increase the move counter of the rook piece. */
        board[old_rank][5] = board[old_rank][7];
        board[old_rank][7] = NULL;
        board[old_rank][5]->increase_move_counter(); 
    }
    /* When the king moves to the queen side */
    if (old_file > new_file) {
        board[old_rank][3] = board[old_rank][0];
        board[old_rank][0] = NULL;
        board[old_rank][3]->increase_move_counter(); 
    }
}



/* Not for marking: function that prints board for debugging. */
void ChessBoard::print_board() const {
    cout << "-------------------------------------" << endl;
    cout << "            Printing Board           " << endl;
    cout << "-------------------------------------" << endl;  
    cout << "    A   B   C   D   E   F   G   H" << endl;
    cout << "   -------------------------------" << endl;
    for (int i=7; i>=0 ; i--) {
        cout << i+1 << " |";
        for (int j=0; j<8; j++) {
            cout << " " << board[i][j] << " " << "|";
        }
        cout << " " << i+1;
        cout << endl;
        cout << "   -------------------------------" << endl;
    }
    cout << "    A   B   C   D   E   F   G   H" << endl;
}
