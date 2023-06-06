#include "ChessPieces.h"

/* Member functions for all chess pieces */

bool ChessPiece::check_destination_team(int new_rank, int new_file, ChessBoard const &chessboard) const {
    /* get the new position's chess piece */
    ChessPiece *new_position_piece = chessboard.board[new_rank][new_file];
    /* if new position is occupied */
    if (new_position_piece != NULL) {
        /* if it is occupied by a piece of the same team */
        if (this->get_team() == new_position_piece->get_team()) 
            return false;
    }
    return true;
}

bool ChessPiece::valid_move(int old_rank, int old_file, int new_rank, int new_file, ChessBoard const &chessboard) const {
    /* check if the destination square is occupeid by a piece of the same team */
    if (!check_destination_team(new_rank, new_file, chessboard)) {
        return false;
    }	
    /* check if the move matches the logic of the chess piece without looking at obstructions first */
    if (!check_piece_logic(old_rank, old_file, new_rank, new_file, chessboard.board)) {
        return false;
    }
    /* check if the move faces an obstacle along the way */
    if (check_obstruction(old_rank, old_file, new_rank, new_file, chessboard.board)) {
        return false;
    }
    return true;
}

string ChessPiece::get_cptype() const {
   /* switch statment which returns the string describing the chess piece type based on the enum value (cptype) of the chess piece. */
    switch(cptype) {
        case ChessPiece::king:
            return "King";
            break;
        case ChessPiece::queen:
            return "Queen";
            break;
        case ChessPiece::rook:
            return "Rook";
            break;
        case ChessPiece::bishop:
            return "Bishop";
            break;
        case ChessPiece::knight:
            return "Knight";
            break;
        case ChessPiece::pawn:
            return "Pawn";
            break;
        default:
            return "Empty Position";
            break;
    }
}

string ChessPiece::get_team() const {
    /* return the string "White" if the bool value of white, which labels the color team of the chess piece, is true. */
    if (white)
        return "White";
    else
        return "Black";
}

void ChessPiece::increase_move_counter() {
    /* increase move counter of chess piece. */
    move_counter++;
}

int ChessPiece::get_move_count() const {
    /* return the number of moves made by the chess piece */
    return move_counter;
}

ChessPiece::ChessPiece(char _team, cptypes _cptype) : cptype(_cptype)  {
    /* define the team the chess piece belongs to based on the constructor parameters provided. */
    if (_team == 'w')
        white = true;
    else
        white = false;
    
    move_counter = 0;
}



/******************** Member functions specific to king piece ********************/

KingPiece::KingPiece(char _team) : ChessPiece(_team, king) {};

bool KingPiece::check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const {
    /* define the vertical distance (unsigned), horizontal distance (unsigned) and total distance (vertical + horizontal distance) moved by the king chess */
    int vertical_distance, horizontal_distance, total_distance; 
    vertical_distance = abs(old_rank-new_rank);
    horizontal_distance = abs(old_file-new_file); 
    total_distance = vertical_distance + horizontal_distance;
    /* move is valid only if the vertical distance and horizontal distance are less than 2, and the total distance must add up to be either 2 (diagonal movement) or 1 (vertical/horizontal movement). */
    if ((vertical_distance <= 1) && (horizontal_distance <= 1) && (total_distance <= 2) && (total_distance >= 1))
        return true;
    return false;
 }

 bool KingPiece::check_obstruction (int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const {
    /* always false as it moves only a square and the check_destination_team() source code would have captured any obstruction before this function is called. */
    return false;
 }



/* Member functions specific to rook piece */

RookPiece::RookPiece(char _team) : ChessPiece(_team, rook) {};

bool RookPiece::check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const {
    /* return true only when the rook piece is moving in the same rank (horizontally) or same file (vertically) */
    if ((new_rank == old_rank) || (new_file == old_file))
        return true;
    return false;
}

bool RookPiece::check_obstruction(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const {
    /* check if the chess piece faces any obstruction if it is moving rightwards along the same rank */
    if ((new_rank == old_rank) && (new_file > old_file)) {
        for (int i=old_file+1; i<new_file; i++) {
            if (board[old_rank][i] != NULL)
            return true;
        }
    }
    /* check if the chess piece faces any obstruction if it is moving leftwards along the same rank */
    else if ((new_rank == old_rank) && (new_file < old_file)) {
        for (int i=old_file-1; i>new_file; i--) {
            if (board[old_rank][i] != NULL)
            return true;
        }
    }
    /* check if the chess piece faces any obstruction if it is moving upwards along the same file */
    else if ((new_file == old_file) && (new_rank > old_rank)) {
        for (int i=old_rank+1; i<new_rank; i++) {
            if (board[i][old_file] != NULL)
            return true;
        }
    }
    /* check if the chess piece faces any obstruction if it is moving downwards along the same file */
    else if ((new_file == old_file) && (new_rank < old_rank)) {
        for (int i=old_rank-1; i>new_rank; i--) {
            if (board[i][old_file] != NULL)
            return true;
        }
    }
    return false;
}



/* Member functions specific to bishop piece */

BishopPiece::BishopPiece(char _team) : ChessPiece(_team, bishop) {};

/* CHECK THIS: all directions ok? */
bool BishopPiece::check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const {
    /* return true only when the bishop piece moves diagonally (only when the vertical distance and the horizontal distance is the same) */
    if (abs(old_rank-new_rank) == abs(old_file-new_file))
        return true;
    return false;
}

bool BishopPiece::check_obstruction(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const {
    int i = old_rank, j = old_file;
    /* checks for obstruction when the bishop piece moves to a higher rank and higher file */
    if ((old_rank < new_rank) && (old_file < new_file)) {
        /* move in advance to next sqaure */
        i++;
        j++;
        while ((i!=new_rank) && (j!=new_file)) {
            if (board[i][j] != NULL) {
                return true;
            }
            i++;
            j++;
        }
    }
    /* checks for obstruction when the bishop piece moves to a higher rank and lower file */
    else if ((old_rank < new_rank) && (old_file > new_file)) {
        /* move in advance to next sqaure */
        i++;
        j--;
        while ((i!=new_rank) && (j!=new_file)) {
            if (board[i][j] != NULL) {
                return true;
            }
            i++;
            j--;
        }
    }
    /* checks for obstruction when the bishop piece moves to a lower rank and lower file */
    else if ((old_rank > new_rank) && (old_file > new_file)) {
        /* move in advance to next sqaure */
        i--;
        j--;
        while ((i!=new_rank) && (j!=new_file)) {
            if (board[i][j] != NULL) {
                return true;
            }
            i--;
            j--;
        }
    }
    /* checks for obstruction when the bishop piece moves to a lower rank and higher file */
    else if ((old_rank > new_rank) && (old_file < new_file)) {
        /* move in advance to next sqaure */
        i--;
        j++;
        while ((i!=new_rank) && (j!=new_file)) {
            if (board[i][j] != NULL) {
                return true;
            }
            i--;
            j++;
        }
    }
    return false;
}



/*Member functions specific to queen piece */

QueenPiece::QueenPiece(char _team) : ChessPiece(_team, queen) {};

bool QueenPiece::check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const {
    /* Check to ensure that the move is strictly diagonal (vertical distance == horizontal distance), vertical (new_rank == old_rank) and horizontal (new_file == old_file) */
    if ((abs(old_rank-new_rank) == abs(old_file-new_file)) || ((new_rank == old_rank) || (new_file == old_file)))
        /* it is valid if the check above passes. */
        return true;
    return false;
}

 bool QueenPiece::check_obstruction (int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const {
    /* Following 26 lines uses rook piece's method to check for obstruction if the queen piece was moved similarly to a rook piece (refer to RookPiece's check_obstruction() method for full description). */
    if ((old_rank == new_rank) || (old_file == new_file)) {
        if ((new_rank == old_rank) && (new_file > old_file)) {
            for (int i=old_file+1; i<new_file; i++) {
                if (board[old_rank][i] != NULL)
                return true;
            }
        }
        else if ((new_rank == old_rank) && (new_file < old_file)) {
            for (int i=old_file-1; i>new_file; i--) {
                if (board[old_rank][i] != NULL)
                return true;
            }
        }
        else if ((new_file == old_file) && (new_rank > old_rank)) {
            for (int i=old_rank+1; i<new_rank; i++) {
                if (board[i][old_file] != NULL)
                return true;
            }
        }
        else if ((new_file == old_file) && (new_rank < old_rank)) {
            for (int i=old_rank-1; i>new_rank; i--) {
                if (board[i][old_file] != NULL)
                return true;
            }
        }
    }
    /* Following 50 lines uses bishop piece's method to check for obstruction if the queen piece was moved similarly to a bishop piece (refer to BishopPiece's check_obstruction() method for full description). */
    if (abs(old_rank-new_rank) == abs(old_file-new_file)) {
        int i = old_rank, j = old_file;
        if ((old_rank < new_rank) && (old_file < new_file)) {
            i++;
            j++;
            while ((i!=new_rank) && (j!=new_file)) {
                if (board[i][j] != NULL) {
                    return true;
                }
                i++;
                j++;
            }
        }
        else if ((old_rank < new_rank) && (old_file > new_file)) {
            i++;
            j--;
            while ((i!=new_rank) && (j!=new_file)) {
                if (board[i][j] != NULL) {
                    return true;
                }
                i++;
                j--;
            }
        }
        else if ((old_rank > new_rank) && (old_file > new_file)) {
            i--;
            j--;
            while ((i!=new_rank) && (j!=new_file)) {
                if (board[i][j] != NULL) {
                    return true;
                }
                i--;
                j--;
            }
        }
        else if ((old_rank > new_rank) && (old_file < new_file)) {
            i--;
            j++;
            while ((i!=new_rank) && (j!=new_file)) {
                if (board[i][j] != NULL) {
                    return true;
                }
                i--;
                j++;
            }
        }
    }
    return false;
 }



/* Member functions specific to knight piece */

KnightPiece::KnightPiece(char _team) : ChessPiece(_team, knight) {};

bool KnightPiece::check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const {
    /* Returns true if the knight piece moves 2 squares vertically and 1 square horizontally. */
    if ((abs(old_rank-new_rank) == 2) && (abs(old_file-new_file) == 1))
        return true;
    /* Returns true if the knight piece moves 1 square vertically and 2 squares horizontally. */
    if ((abs(old_rank-new_rank) == 1) && (abs(old_file-new_file) == 2))
        return true;
    return false;
}

bool KnightPiece::check_obstruction(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const {
    /* Always return false as there is no obstruction for knight piece. */
    return false; 
}



/*Member functions specific to pawn piece */

PawnPiece::PawnPiece(char _team) : ChessPiece(_team, pawn) {};

bool PawnPiece::check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const {
    /* Check that is the piece at the new position, as it is allowed to move diagonally if it is occupied by an opponent's piece. */
    const ChessPiece * new_position_piece = board[new_rank][new_file];
    /* Perform the next 2 checks if the new position has a chess piece */
    if (new_position_piece != NULL) {
        /* For white pawn piece: check if the new position moves diagonally up (1 square horizontally and vertically) from original position and there is a black team chess piece there */
        if (white) {
            if ((abs(new_rank-old_rank) == 1) && (abs(new_file-old_file) == 1) && (new_rank > old_rank) && !(new_position_piece->get_team() == "White") ) {
                return true;
                }
        }

        /* For black pawn piece: check if the new position move diagonally down (1 square horizontally and vertically) from original position and there is a white team chess piece there */
        if (!white) {
            if ((abs(old_rank-new_rank) == 1) && (abs(new_file-old_file) == 1) && (new_rank < old_rank) && (new_position_piece->get_team() == "White")) {
                return true;
                }
        }
    }

    /* if the above conditions are not met, the pawn piece will have to stay within the file */
    if (old_file == new_file) {
        /* For white pawn piece: check if the new position is one position up */
        if ((new_rank == old_rank+1) && (white)) {
            return true;
        }
        /* For black pawn picec: check if the new position is one position down */
        if ((new_rank == old_rank-1) && !(white)) {
            return true;
        }
        /* For white pawn piece: if the move is it's first move, check if the new position is two position up */
        if ((move_counter == 0) && (new_rank == old_rank+2) && (white)) {
            return true;
        }
        /* For black pawn piece: if the move is it's first move, check if the new position is two position down */
        if ((move_counter == 0) && (new_rank == old_rank-2) && !(white)) {
            return true;
        }
    }
    return false;
}

bool PawnPiece::check_obstruction(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const {
    /* return true if there is no obstruction for white pawn when it is moving up from the source square to the destination square. */
    if ((white) && (old_file == new_file)) {
        for (int i=old_rank+1; i<=new_rank; i++) {
            if (board[i][old_file] != NULL) {
                return true;
            }
        }
    }
    /* return true if there is no obstruction for black pawn when it is moving down from the source square to the destination square. */
    if (!(white) && (old_file == new_file)){
        for (int i=old_rank-1; i>=new_rank; i--) {
            if (board[i][old_file] != NULL) {
                return true;
            }
        }
    }

    return false; 
}



/* Not for marking: extra function to print chesspiece symbol */

ostream& operator<<(ostream& os, ChessPiece* piece) {
   
   if (piece == NULL)
    return os << " ";
   
   switch(piece->cptype) {
        case ChessPiece::king:
            if (piece->white == true)
                os << "\u2654";
            else
                os << "\u265A";
            break;
        case ChessPiece::queen:
            if (piece->white == true)
                os << "\u2655";
            else
                os << "\u265B";
            break;
        case ChessPiece::rook:
            if (piece->white == true)
                os << "\u2656";
            else
                os << "\u265C";
            break;
        case ChessPiece::bishop:
            if (piece->white == true)
                os << "\u2657";
            else
                os << "\u265D";
            break;
        case ChessPiece::knight:
            if (piece->white == true)
                os << "\u2658";
            else
                os << "\u265E";
            break;
        case ChessPiece::pawn:
            if (piece->white == true)
                os << "\u2659";
            else
                os << "\u265F";
            break;
        default:
            os << " ";
            break;
    }

    return os;
}