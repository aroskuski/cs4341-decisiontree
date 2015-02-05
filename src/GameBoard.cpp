/*
 * GameBoard.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: andrew
 */
#include <iostream>
using namespace std;
#include "GameBoard.h"

GameBoard::GameBoard(int board[], int winner) {
	// TODO Auto-generated constructor stub

	int i, j;

	for(i = 0; i < 6; i++){
		for(j = 0; j < 7; j++){
			this->board[i][j] = board[i*6 + j];
		}
	}

	this->winner = winner;

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
