#ifndef CHESSPIECES_H
#define CHESSPIECES_H
#include <iostream>
#include <cstring>
#include"ChessBoard.h"

using namespace std;

class ChessBoard;

class ChessPiece {
    /* ChessBoard is a friend of chesspiece (and all derived classes) as it will be accessing functions (e.g. functions to increase move counter of the chess piece), which will not be accesible to all classes. */
    friend class ChessBoard;

    protected:
        /* Variables of ChessPiece class is defined in this section */

        /* Boolean type variable which indicates if the chess piece belongs to the white (true) or black (false) team. */
        bool white;

        /* Enum type which indicates the chess piece type. */
        enum cptypes {king, queen, rook, bishop, knight, pawn};
        cptypes cptype;
        
        /* Counter that stores the number of move made by the chess piece into the game. */
        int move_counter;

        /* Member functions of ChessPiece class */

        /* Method check if the new position is occupied by a similar team's piece. 
        @param: new_rank, new_file: the destination square's rank and file respectively.
        @oaram ChessBoard: the chessboard the chess piece is on. 
        @return true if there is no piece or it is occupied by chess piece of different team, false if the destination square is occupied by a piece of the same team. */
        bool check_destination_team(int new_rank, int new_file, ChessBoard const &chessboard) const;
        
        /* Virtual method 1: Check if the move from the source square to the destination square obeys the piece's movement logic (each type of chess piece will implement their own logic).
        @param old_rank, old_file: the source square's rank and file respectively.
        @param new_rank, new_file: the destination square's rank and file respectively. 
        @oaram board: the board the chess piece is on. 
        @return true if the logic is correct based on the chess piece, false otherwise. */
        virtual bool check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const = 0;
        
        /* Virtual method 2: Run through the movement path of the chess piece and check for obstruction. 
        @param: old_rank, old_file represents the original rank and file of the chess piece
        @param: new_rank, new_file represents the new rank and file of the chess piece submitted
        @return True if there is obstruction in the path, False if there is no obstruction in the path */
        virtual bool check_obstruction(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const = 0;
        
        /* Method check if 1) the destination square is not occupied by a piece that belongs to the same team (check_destination_team()), 
        2) the move from the source square to the destination square obeys the piece's movement logic (check_piece_logic()),
        3) there is no obstruction along the way (check_obstruction()).
        @param old_rank, old_file: the source square's rank and file respectively.
        @param new_rank, new_file: the destination square's rank and file respectively. 
        @oaram ChessBoard: the current configuration of chessboard. 
        @return true all of the 3 conditions above are met, false otherwise. */
        bool valid_move(int old_rank, int old_file, int new_rank, int new_file, ChessBoard const &chessboard) const;
        
        /* Method to increase counter tracked by the variable 'move_counter' after every move made by the chess piece. */
        void increase_move_counter();

        /* Constructor and virtual destructor for abstract class ChessPiece. */
        
        /* Constructor of ChessPiece which takes in the team and the type of chess piece 
        @param _team: the color of the team the chess piece is in ('w' for white team, 'b' for black team). 
        @param _file, _rank: the current rank and file the chess piece is initialized, and the enum value for type chess piece initialised. */
        ChessPiece(char _team, cptypes _cptype);
        
        virtual ~ChessPiece() = default;

    public:
        string get_cptype() const;
        
        string get_team() const;
        
        int get_move_count() const;

    /* Not for marking. Function prints out a symbol of the chess piece based on the chess piece type */
    friend ostream& operator<<(ostream& os, ChessPiece* piece);
};



class KingPiece : private ChessPiece {
    friend class ChessBoard;
    private:
        /* 1 arg constructor that takes in the color of the king piece's team 
        @param _team: the team of the king chess piece (i.e. 'w' for white, 'b' for black). (similar for all other derived classes) */
        KingPiece(char _team);
        /* For this and the remaining subclasses of ChessPiece, refer to the virtual function check_piece_logic() found under abstract class chess piece for full description. */
        bool check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const override;
        /* Function returns false all the time as the king only moves 1 square at a time. The only possible obstruction occurs when the king piece moves to a destination square that contains it's own team chess piece, which would have been detected by the check_destination_team() method of the base class. */
        bool check_obstruction(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const override;
};



class RookPiece : private ChessPiece {
    friend class ChessBoard;
    private:
        RookPiece(char _team);
        bool check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const override;
        /* For this and the remaining subclasses of ChessPiece (except knight), refer to the virtual function check_obstruction() found under abstract class chess piece for full description. */
        bool check_obstruction(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const override;
};



class BishopPiece : private ChessPiece {
    friend class ChessBoard;
    private:
        BishopPiece(char _team);
        bool check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const override;
        bool check_obstruction(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const override;
};



class QueenPiece : private ChessPiece {
    friend class ChessBoard;
    private:
        QueenPiece(char _team);
        bool check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const override;
        bool check_obstruction(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const override;
};



class KnightPiece : private ChessPiece {
    friend class ChessBoard;
    private:
        KnightPiece(char _team);
        bool check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const override;
        /* Function that checks obstruction for knight piece. 
        @return false all the time because it can leap over all pieces */
        bool check_obstruction(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const override;
};



class PawnPiece : private ChessPiece {
    friend class ChessBoard;
    private:
        PawnPiece(char _team);
        bool check_piece_logic(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const override;
        bool check_obstruction(int old_rank, int old_file, int new_rank, int new_file, const ChessPiece *const board[8][8]) const override;
};

#endif