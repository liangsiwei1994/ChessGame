#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include <string>
#include <cstring>
#include "ChessPieces.h"

using namespace std;

class ChessPiece;

class ChessBoard {
    /* All piece types is made friend class of the ChessBoard class to access the board's current configuration as it needs to check (e.g. for obstruction) when moving. */
    friend class ChessPiece;
    friend class KingPiece;
    friend class QueenPiece;
    friend class RookPiece;
    friend class BishopPiece;
    friend class KnightPiece;
    friend class PawnPiece;

    private:
        /* Variables of chess board is declared in this section */
        
        /* A 8x8 board for the chess pieces pointer */
        ChessPiece *board[8][8];
        
        /* Boolean variable indicates the current team that is making the move (i.e. true if it is white's turn, false otherwise). */
        bool white;
        
        /* Store black king's location (black_kings_location[0] is the rank, black_kings_location[1] is the file). */
        int black_kings_location[2];
        
        /* Store white king's location (white_kings_location[0] is the rank, white_kings_location[1] is the file). */
        int white_kings_location[2];

        /* Store the state of the game */
        bool game_over;

        /* Methods of chess board is declared in this section */

        /* A function that checks if the new and old position, for the destination and source sqaure positions submitted respectively, is a valid position.
        @param old_position: string representing the source square.
        @param new_position: string representing the destination square.
        @return true if both old_position and new_position passes the above checks, false otherwise. */
        bool check_valid_str_position(string const old_position, string const new_position) const;
        
        /* Check if all opponent's pieces can move to the king piece position, who's rank and file is passed into the function as parameters.
        @param: king_rank, king_file: the rank and file of the king piece we are looking to check if the other team is able to reach respectively.
        @param copied_board: The board which simulates after moving the chesspiece to the new position (usually a copied board using the board_copy() method).
        @return true if it the king that is being looked into is in check, false otherwise. */
        bool check_king_test(int const king_rank, int const king_file) const;
        
        /* A function that officiates the move by moving the piece from the source square to the destination sqaure, deleteing the piece at the destination square (after all checks).
        @param old_rank, old_file: represents the source square's rank and file respectively.
        @param new_rank, new_file: represents the destination square's rank and file respectively.
        @return: method returns nothing, but prints out the message that describes the move made and what opponent chess piece is captured after the move. Although there is no return value, the configuration of the board is now changed permanently. */
        void make_move(int const old_rank, int const old_file, int const new_rank, int const new_file);
        
        /* A function that simulates making the move.
        @param old_rank, old_file: represents the source square's rank and file respectively.
        @param new_rank, new_file: represents the destination square's rank and file respectively.
        @param temp: temporarily store the destination square's value for undo-ing later.
        @return: return nothing but modifies the state of the board. */
        void temp_make_move(int const old_rank, int const old_file, int const new_rank, int const new_file, ChessPiece *(&temp));

        /* Undo the move made temporarily in the temp_make_move() method
        @param old_rank, old_file: represents the source square's rank and file respectively.
        @param new_rank, new_file: represents the destination square's rank and file respectively.
        @param temp: previous value of destination square stored for undo-ing.
        @return: return nothing but modifies the state of the board. */
        void undo_temp_move(int const old_rank, int const old_file, int const new_rank, int const new_file, ChessPiece *(&temp));

        /* Function that counts the possible number of moves for the opponent (of the king at the king_rank and king_file passed as paramaters) after the move is made,.
        @param king_rank, king_file: opponent's king position, which will be used to decide will move made by the opponent will leave it's own king in check.
        @return: the number of valid moves for the opponent after current move. */
        int valid_move_counter(int const king_rank, int const king_file);
        
        /* Function that checks if there is an obstruction between the king and rook piece
        @param: old_king_file: the original file of the king
        @param: new_king_file: the file to be moved to by the king
        @param: king_rank: which is the rank of the king (either 1 or 8)
        @return true if the obstruction check passes, false otherwise. */
        bool castling_obstruction_check(int const old_king_file, int const new_king_file, int const king_rank) const;
        
        /* Function that checks if there is a valid rook for the castling to happen
        @param: old_king_file: the original file of the king
        @param: new_king_file: the file to be moved to by the king
        @param: king_rank: which is the rank of the king (either 1 or 8) 
        @return true if there is a valid rook piece available for castling at the side the king is castling to, false otherwise. */
        bool castling_rook_check(int const old_king_file, int const new_king_file, int const king_rank) const;
        
        /* Function that checks if the king will be in check from it's starting to ending position
        @param: old_king_file: the original file of the king
        @param: new_king_file: the file to be moved to by the king
        @param: king_rank: which is the rank of the king (either 1 or 8) 
        return true if the king passes the check and will not be in check, false otherwise */
        bool castling_king_check(int const old_king_file, int const new_king_file, int const king_rank);

        /* Perform all checks to see if the castling move is valid
        @param: old_king_file: the original file of the king
        @param: new_king_file: the file to be moved to by the king
        @return true if all castling checks pass, false otherwise. */
        bool castling_check(int const old_king_file, int const new_king_file);
        
        /* Function that make move for castling by shifting the king to it's new position and adjust the relevant rook piece accordingly. 
        Function also prints out a unique message for castling */
        void make_castling_move(int const old_rank, int const old_file, int const new_rank, int const new_file);

    public:
        /* Default constructor that constructs the board and instantiate all chess pieces, at their default position, and variables such that it indicated white team making the first move, followed by printing out the game start message. */
        ChessBoard();
       
        /* Method which conducts the following multiple checks on the input and move validity before making the move submitted officially.
        If the move passes all checks, check if the current move will result in a check, checkmate, stalemate or should the game continue as per normal.
        @return: method returns nothing. However, update will only be done on the baord if the current move is valid.  */
        void submitMove(string const old_position, string const new_position);
       
        /* Function resets the board by deleting existing chess pieces, setting all new chess pieces at their original positions and set all variables of the ChessBoard class to their initial values. */
        void resetBoard();
       
        /* Default destructor that deletes all chesspieces created dyanmically before deleting the chessboard. */
        ~ChessBoard();

        /* Not for marking: Method that prints out the board for visualisation and debugging. */
        void print_board() const ;
};

#endif