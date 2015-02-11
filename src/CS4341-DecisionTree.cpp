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

	//open input file
	ifstream infile(argv[1]);
	//infile.open(argv[1]);

	if(!infile.is_open()){
		return 1;
	}

	//parse file, this step fills the list and analyzes the data
	parsefile(infile);
	//int i = 0;

	//open output file
	ofstream outfile(argv[2]);

	if(!outfile.is_open()){
		return 1;
	}

	// print out headers
	outfile << "f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16,f17,f18,f19,f20,f21,f22,f23,f24,f25,f26,f27,f28,f29,f30,f31,f32,f33,f34,f35,f36,f37,f38,f39,f40,f41,f42,imminentwin,center,side,columns,opencomb,winlose\n";
	//print each line
	for (std::list<GameBoard>::iterator it = trainingList.begin(); it !=trainingList.end(); it++){
		outfile << it->printFeatures();
	}

	return 0;
}

//Parse the input file and load it into GameBoards
// This also analyzes the data, since that is in the GameBoard constructor
void parsefile(ifstream &in){
	char buf[100];
	int board[42];
	int winner;
	int i;
	//GameBoard &temp;

	in.getline(buf, 100);

	while(!in.eof()){
		for(i = 0; i < 42; i++){
			board[i] = buf[i*2] - '0';//this works because all the number caracters are in order in ascii
		}
		winner = buf[i*2] - '0';
		GameBoard *temp = new GameBoard(board, winner);
		trainingList.push_back(*temp);
		//delete temp;
		in.getline(buf,100);
	}

}
