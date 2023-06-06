chess: ChessMain.o ChessBoard.o ChessPieces.o
	g++ -g ChessMain.o ChessBoard.o ChessPieces.o -o chess -std=c++17

ChessMain.o: ChessMain.cpp ChessBoard.h ChessPieces.h
	g++ -Wall -g -c ChessMain.cpp -std=c++17

ChessBoard.o: ChessBoard.cpp ChessBoard.h
	g++ -Wall -g -c ChessBoard.cpp -std=c++17

ChessPieces.o: ChessPieces.cpp ChessPieces.h
	g++ -Wall -g -c ChessPieces.cpp -std=c++17

clean:
	rm -f *.o ChessMain
