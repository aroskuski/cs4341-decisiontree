//============================================================================
// Name        : CS4341-DecisionTree.cpp
// Author      : Andrew Roskuski & Connor Porell
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <list>
using namespace std;
#include "GameBoard.h"

list<GameBoard> trainingList;

void parsefile(ifstream &in);

int main(int argc, char** argv) {
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	if(argc != 3){
		cout << "expected arguments: <infile> <outfile>\n";
		return 1;
	}
	ifstream infile(argv[1]);
	//infile.open(argv[1]);

	if(!infile.is_open()){
		return 1;
	}

	parsefile(infile);
	//int i = 0;

	ofstream outfile(argv[2]);

	if(!outfile.is_open()){
		return 1;
	}

	outfile << "imminentwin,center,side,top,opencomb,winlose\n";
	for (std::list<GameBoard>::iterator it = trainingList.begin(); it !=trainingList.end(); it++){
		outfile << it->printFeatures();
	}

	return 0;
}

void parsefile(ifstream &in){
	char buf[100];
	int board[42];
	int winner;
	int i;
	//GameBoard &temp;

	in.getline(buf, 100);

	while(!in.eof()){
		for(i = 0; i < 42; i++){
			board[i] = buf[i*2] - '0';
		}
		winner = buf[i*2] - '0';
		GameBoard *temp = new GameBoard(board, winner);
		trainingList.push_back(*temp);
		delete temp;
		in.getline(buf,100);
	}

}
