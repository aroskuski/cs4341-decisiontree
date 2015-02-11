/*
 * GameBoard.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: andrew
 */
#include <iostream>
#include <sstream>
using namespace std;
#include "GameBoard.h"
#include "Coords.h"

//initializes all the values
GameBoard::GameBoard(int board[], int winner) {


	int i, j;

	for(i = 0; i < 6; i++){
		for(j = 0; j < 7; j++){
			this->board[i][j] = board[i*6 + j];
		}
	}

	this->winner = winner;

	this->imminentwin = 0;
	this->imminentlosses = 0;
	this->p1open = 0;
	this->p2open = 0;
	this->opencomb = 0;
	this->center = 0;
	this->left = 0;
	this->right = 0;
	this->side = 0;
	this->top = 0;
	this->columns = 0;

	this->computefeatures();

}

GameBoard::~GameBoard() {

}

//prints this object on the stdout
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

//computes the features on this object
void GameBoard::computefeatures(){

	analyzeOpen();
	if (opencomb > 4){
		opencomb = 1;
	} else if (opencomb < -4){
		opencomb = -1;
	} else {
		opencomb = 0;
	}

	centercontrol();
	leftcontrol();
	rightcontrol();
	side = left + right;
	if (side > 2){
		side = 1;
	} else if (side < -2){
		side = -1;
	} else {
		side = 0;
	}

	columncontrol();
}


//determines which player controls more columns
void GameBoard::columncontrol(){
	for (int i = 0; i < 7; i++){
		bool p1 = false;
		bool p2 = false;
		for(int j = 0; j < 6; j++){
			if(board[j][i] == 1 && !p1){
				columns++;
				p1 = true;
			} else if (board[j][i] == 2 && !p2){
				columns--;
				p2 = true;
			}
		}
	}
	if (columns > 1){
		columns = 1;
	} else if(columns < -1){
		columns = -1;
	} else {
		columns = 0;
	}

}


//NOT USED
// computes which player controls more of the top
void GameBoard::topcontrol(){
	for(int i = 0; i < 7; i++){
		int next = nextOpenRow(i);
		if (next < 5){
			if(board[next][i] == 1){
				top++;
			} else if(board[next][i] == 2){
				top--;
			}
		}
	}
	if (top > 0){
			top = 1;
		} else if (top < 0){
			top = -1;
		} else {
			top = 0;
		}
}


// Computes which player controls more of the center 5 columns of the board
void GameBoard::centercontrol(){
	for (int j = 1; j <= 5; j++){
		for (int i = 0; i < 6; i++){
			if(board[i][j] == 1){
				center++;
			} else if(board[i][j] == 2) {
				center--;
			}
		}
	}
	if(center > 1){
		center = 1;
	} else if (center < 1){
		center = -1;
	} else {
		center = 0;
	}
}

//computes which player controls more of the left 2 columns of the board
void GameBoard::leftcontrol(){
	for (int j = 0; j <= 1; j++){
		for (int i = 0; i < 6; i++){
			if(board[i][j] == 1){
				left++;
			} else if(board[i][j] == 2) {
				left--;
			}
		}
	}
}

//computes which player controls more of the right 2 columns of the board
void GameBoard::rightcontrol(){
	for (int j = 5; j < 7; j++){
		for (int i = 0; i < 6; i++){
			if(board[i][j] == 1){
				right++;
			} else if(board[i][j] == 2) {
				right--;
			}
		}
	}
}

//Analyzes how many open moves each player has
void GameBoard::analyzeOpen(){
	list<Coords> visitedVertical;
	list<Coords> visitedHorizontal;
	list<Coords> visitedDownDiag;
	list<Coords> visitedUpDiag;


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

	opencomb = p1open - p2open;
	//cout << "p1open: " << p1open << "\n";
	//cout << "p2open: " << p2open << "\n";
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
		if (connected == 3){
			if (board[row][col] == 1){
				imminentwin++;
			} else {
				imminentlosses++;
			}
		}
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
		if (connected == 3){
			if (board[row][col] == 1){
				bool usable = false;
				if(openleft){
					if(nextOpenRow(col - 1) == row){
						usable = true;
					}
				}
				if(openright){
					if(nextOpenRow(col + 1) == row){
						usable = true;
					}
				}
				if (usable){
					imminentwin = 1;
				}
			}
		}
		if (openleft && openright){
			return connected*2;
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
		if (connected == 3){
			if (board[row][col] == 1){
				bool usable = false;
				if(openleft){
					if(nextOpenRow(col - 1) == row - 1){
						usable = true;
					}
				}
				if(openright){
					if(nextOpenRow(col + 1) == row + 1){
						usable = true;
					}
				}
				if (usable){
					imminentwin = 1;
				}
			}
		}
		if (openleft && openright){
			return connected*2;
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
		if (connected == 3){
			if (board[row][col] == 1){
				bool usable = false;
				if(openleft){
					if(nextOpenRow(col - 1) == row + 1){
						usable = true;
					}
				}
				if(openright){
					if(nextOpenRow(col + 1) == row - 1){
						usable = true;
					}
				}
				if (usable){
					imminentwin = 1;
				}
			}
		}
		if (openleft && openright){
			return connected*2;
		} else {
			return connected;
		}
	} else {
		return 0;
	}
}

//returns true if the list contains an equal Coords object
bool GameBoard::contains(list<Coords> visited, Coords c){
	for(std::list<Coords>::iterator it = visited.begin(); it != visited.end(); it++){
		if (*it == c){
			return true;
		}
	}
	return false;
}

//Returns the next open row for a column
int GameBoard::nextOpenRow(int col){
	for (int i = 0; i < 6; i++){
		if(board[i][col] != 0){
			return i - 1;
		}
	}
	return 5;
}

//Returns a string containing the board state and it's generated features
string GameBoard::printFeatures(){
	stringstream ss;
	int i,j;
	for(i = 0; i < 6; i++){
		for(j = 0; j < 7; j++){
			ss << board[i][j] << ",";
		}
	}
	ss << imminentwin << "," << center << "," << side << "," << columns << "," << opencomb << "," << winner << "\n";
	return ss.str();

}
