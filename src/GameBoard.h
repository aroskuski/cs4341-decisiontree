/*
 * GameBoard.h
 *
 *  Created on: Feb 4, 2015
 *      Author: andrew
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_
#include <list>
#include "Coords.h"


class GameBoard {
public:
	GameBoard(int board[], int winner);
	virtual ~GameBoard();
	void printboard();
	string tostring();
private:
	int board[6][7];
	int winner;
	int p1open;
	int p2open;
	void computefeatures();
	void analyzeOpen();
	bool contains(list<Coords> visited, Coords c);
	int analyzeVertical(int row, int col, list<Coords> visited);
	int analyzeHorizontal(int row, int col, list<Coords> visited);
	int analyzeUpDiag(int row, int col, list<Coords> visited);
	int analyzeDownDiag(int row, int col, list<Coords> visited);
	int nextOpenRow(int col);
};

#endif /* GAMEBOARD_H_ */
