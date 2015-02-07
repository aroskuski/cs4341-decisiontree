/*
 * Coords.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: andrew
 */

#include "Coords.h"
using namespace std;


Coords::Coords(int row, int col) {
	// TODO Auto-generated constructor stub
	this->row = row;
	this->col = col;
}

Coords::~Coords() {
	// TODO Auto-generated destructor stub
}


bool Coords::operator == (const Coords &Ref) const{
	if((Ref.row == this->row) && (Ref.col == this->col)){
		return true;
	} else {
		return false;
	}
}
