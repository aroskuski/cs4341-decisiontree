/*
 * GameBoard.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: andrew
 */
#include <iostream>
using namespace std;
#include "GameBoard.h"
#include "Coords.h"

GameBoard::GameBoard(int board[], int winner) {
	// TODO Auto-generated constructor stub

	int i, j;

	for(i = 0; i < 6; i++){
		for(j = 0; j < 7; j++){
			this->board[i][j] = board[i*6 + j];
		}
	}

	this->winner = winner;

	this->computefeatures();

}

GameBoard::~GameBoard() {
	// TODO Auto-generated destructor stub
}

void GameBoard::printboard(){
	int i, j;
	for(i = 0; i < 6; i++){

			for(j = 0; j < 7; j++){
				if(j != 0){
					cout << " ";
				}
				cout << board[i][j];
			}
			cout << "\n";

	}

	cout << "Winner: " << winner << "\n";
}

void GameBoard::computefeatures(){
	analyzeOpen();
}

void GameBoard::analyzeOpen(){
	list<Coords> visitedVertical;
	list<Coords> visitedHorizontal;
	list<Coords> visitedDownDiag;
	list<Coords> visitedUpDiag;
	p1open = 0;
	p2open = 0;
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 7; j++){
			if(board[i][j] == 1){
				p1open += analyzeVertical(i, j, visitedVertical);
				p1open += analyzeHorizontal(i, j, visitedHorizontal);
				p1open += analyzeDownDiag(i,j, visitedDownDiag);
				p1open += analyzeUpDiag(i,j, visitedUpDiag);
			} else if (board[i][j] == 2){
				p2open += analyzeVertical(i, j, visitedVertical);
				p2open += analyzeHorizontal(i, j, visitedHorizontal);
				p2open += analyzeDownDiag(i,j, visitedDownDiag);
				p2open += analyzeUpDiag(i,j, visitedUpDiag);
			}
		}
	}
	cout << "p1open: " << p1open << "\n";
	cout << "p2open: " << p2open << "\n";
}


// Analyze a vertical chain of pieces.
	// Given a coord, we look up and down from that piece.
	// If we find pieces of a similar player, we add to the chain.
	 int GameBoard::analyzeVertical(int row, int col, list<Coords> visited){
		int connected = 1; // Start with initial chain of 1 for the starting piece.

		// If we've already visited this spot, back out.
		if (contains(visited, Coords(row, col))){
			return 0;
		}
		// Add this spot to our "visited" data.
		visited.push_back(Coords(row, col));
		// Look at the rows above first.
		for(int i = row - 1; i > -1; i--){
			if(board[i][col] == board[row][col]){
				connected++;
				visited.push_back(Coords(i, col));
			} else {
				break;
			}
		}
		// Look at the rows below
		for(int i = row + 1; i < 6; i++){
			if(board[i][col] == board[row][col]){
				connected++;
				visited.push_back(Coords(i, col));
			} else {
				break;
			}
		}
		// If the row at the top of the chain is free, return the amount connected.
		// Else, the chain is blocked, so no score.
		if(nextOpenRow(col) == row - 1){
			return connected;
		} else {
			return 0;
		}
	}

	// Analyze a horizontal chain of pieces.
	// Given a coord, we look right and left from that piece.
	// If we find pieces of a similar player, we add to the chain.
	int GameBoard::analyzeHorizontal(int row, int col, list<Coords> visited){
		int connected = 1;
		bool openleft = false;
		bool openright = false;
		// If we've already visited this spot, back out.
		if (contains(visited, Coords(row, col))){
					return 0;
		}
		// Add this spot to our "visited" list.
		visited.push_back(Coords(row, col));

		// Look at the pieces to the left, keeping track of whether a piece can be dropped to the end
		for(int i = col - 1; i > -1; i--){
			if(board[row][i] == board[row][col]){
				connected++;
				visited.push_back(Coords(row, i));
			} else if(board[row][i] == 0){
				openright = true;
				break;
			} else {
				break;
			}
		}

		// Look at the pieces to the right, keeping track of whether a piece can be dropped to the end
		for(int i = col + 1; i < 7; i++){
			if(board[row][i] == board[row][col]){
				connected++;
				visited.push_back(Coords(row, i));
			} else if(board[row][i] == 0){
				openleft = true;
				break;
			} else {
				break;
			}
		}

		// If the chain is open, return the number of pieces connected, else it is blocked, so no score.
		if(openleft || openright){
			if (openleft && openright){
				return connected * 2;
			} else {
				return connected;
			}
		} else {
			return 0;
		}
	}

	// Analyze a chain of pieces going up diagonally (from left to right).
	// Given a coord, we look around that piece.
	// If we find pieces of a similar player, we add to the chain.
	int GameBoard::analyzeUpDiag(int row, int col, list<Coords> visited){
		// Base chain size of 1 for starting piece
		int connected = 1;
		bool openleft = false;
		bool openright = false;
		// If we've already visited this spot, back out.
		if (contains(visited, Coords(row, col))){
					return 0;
		}
		// Else add it to visited.
		visited.push_back(Coords(row, col));
		// Search up and to the right for pieces connected diagonally.
		for(int i = 1; row + i < 6 && col -i > - 1 ; i++){
			if(board[row + i][col - i] == board[row][col]){
				connected++;
				visited.push_back(Coords(row + i, col - i));
			} else if(board[row + i][col - i] == 0){
				openleft = true;
				break;
			} else {
				break;
			}
		}
		// Search down and to the left for pieces connected diagonally.
		for(int i = 1; row - i > -1 && col + i < 7; i++){
			if(board[row - i][col + i] == board[row][col]){
				connected++;
				visited.push_back(Coords(row - i, col + i));
			} else if(board[row - i][col + i] == 0){
				openright = true;
				break;
			} else {
				break;
			}
		}
		// If a piece can be dropped into place to continue the chain, return the number connected.
		// Else it is blocked, so no score.
		if(openleft || openright){
			if (openleft && openright){
				return connected * 2;
			} else {
				return connected;
			}
		} else {
			return 0;
		}
	}

	// Analyze a chain of pieces going down diagonally (from left to right).
	// Given a coord, we look around that piece.
	// If we find pieces of a similar player, we add to the chain.
	int GameBoard::analyzeDownDiag(int row, int col, list<Coords> visited){
		// Initial chain size of 1. You know the drill by now :)
		int connected = 1;
		bool openleft = false;
		bool openright = false;
		// If the given coord is in our "visited" list, skip it.
		if (contains(visited, Coords(row, col))){
					return 0;
		}
		// Else add it to our list and continue
		visited.push_back(Coords(row, col));

		// Look down and to the right for connected pieces
		for(int i = 1; row - i > -1 && col -i > - 1 ; i++){
			if(board[row - i][col - i] == board[row][col]){
				connected++;
				visited.push_back(Coords(row - i, col - i));
			} else if(board[row - i][col - i] == 0){
				openleft = true;
				break;
			} else {
				break;
			}
		}
		// Search up and to the left for connected pieces.
		for(int i = 1; row + i < 6 && col + i < 7; i++){
			if(board[row + i][col + i] == board[row][col]){
				connected++;
				visited.push_back(Coords(row + i, col + i));
			} else if(board[row + i][col + i] == 0){
				openright = true;
				break;
			} else {
				break;
			}
		}
		// If the chain is open, return the number of pieces connected. Else, score = 0.
		if(openleft || openright){
			if (openleft && openright){
				return connected * 2;
			} else {
				return connected;
			}
		} else {
			return 0;
		}
	}

	bool GameBoard::contains(list<Coords> visited, Coords c){
		for(std::list<Coords>::iterator it = visited.begin(); it != visited.end(); it++){
			if (*it == c){
				return true;
			}
		}
		return false;
	}

	int GameBoard::nextOpenRow(int col){
		for (int i = 0; i < 6; i++){
			if(board[i][col] != 0){
				return i - 1;
			}
		}
		return 5;
	}
