/*
 * Coords.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: andrew
 */

#include "Coords.h"
using namespace std;


Coords::Coords(int row, int col) {

	this->row = row;
	this->col = col;
}

Coords::~Coords() {

}

//Overload the == operator to so we can compare these more simply
bool Coords::operator == (const Coords &Ref) const{
	if((Ref.row == this->row) && (Ref.col == this->col)){
		return true;
	} else {
		return false;
	}
}
