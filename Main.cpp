//============================================================================
// Name        : 1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "Net.h"
#include<cstring>

int main(int argc, char* argv[]) {
	Net* n = new Net;

	try {
		n->getInput(argc, argv);
	} catch (...) {
		cerr << "Error reading input files..\n";
		exit(1);
	}

	string line, command, argu_1, argu_2;

	do{
		cin >> command;
		if(command.compare("load") == 0){
		cin >> argu_1;
			char file[argu_1.size() + 1];
			strcpy(file, argu_1.c_str());
			try{
				n->updateTime(file);
			}catch (...){
				cerr << "ERROR opening the specified file.\n";
			}
		} else if (command.compare("outbound") == 0){
			cin >> argu_1;
			n->outbound(argu_1);
		} else if (command.compare("inbound") == 0){
			cin >> argu_1;
			n->inbound(argu_1);
		} else if(command.compare("uniExpress") == 0){
			cin >> argu_1 >> argu_2;
			n->uniExpress(argu_1, argu_2);
		} else if(command.compare("multiExpress") == 0){
			cin >> argu_1 >> argu_2;
			n->multiExpress(argu_1, argu_2);
		} else if (command.compare("print") == 0)
			n->print();
	}while(command.compare("QUIT") != 0);



	delete n;
	return 0;
}
