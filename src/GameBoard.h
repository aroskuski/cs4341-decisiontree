/*
 * GameBoard.h
 *
 *  Created on: Feb 4, 2015
 *      Author: andrew
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

class GameBoard {
public:
	GameBoard(int board[], int winner);
	virtual ~GameBoard();
	void printboard();
private:
	int board[6][7];
	int winner;
};

#endif /* GAMEBOARD_H_ */
