/*
 * Coords.h
 *
 *  Created on: Feb 6, 2015
 *      Author: andrew
 */

#ifndef COORDS_H_
#define COORDS_H_



class Coords {
public:
	Coords(int row, int col);
	virtual ~Coords();
	bool operator == (const Coords &Ref) const;
private:
	int row;
	int col;
};



#endif /* COORDS_H_ */
