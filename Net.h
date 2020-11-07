/*
 * Net.h
 *
 *  Created on: 24 במאי 2020
 *      Author: Harel
 */

#ifndef NET_H_
#define NET_H_
#include <fstream>
#include <sstream>
#include "Bus.h"
#include "Centraal.h"
#include "Sprinter.h"
#include "Tram.h"
#include "Intercity.h"
#include "Rail.h"
#include "Stad.h"
#include <vector>


class Net {
public:
	Net();
	void getInput(int argc, char* argv[]);
	void updateTime(const char* file);
	void addLine(string source, string target, int time, string vehicle);
	shared_ptr<Vehicle>& getVehicle(string name);
	void outbound(string source);
	void inbound(string target);
	void uniExpress(string source, string target);
	void multiExpress(string source, string target);
	void print();
	friend std:: ostream& operator<<(ostream& os, const Net& n);
	virtual ~Net();
	typedef pair<int, Station*> pi;
private:
	void inputI(const char* file);
	void printPath(Station* stat, string vehicle, set<Station*> s,	const char& dir);
	shared_ptr<Station>& findStation(string s);
	shared_ptr<Station>& createStation(string type);
	bool stationExists(string station);
	vector<shared_ptr<Vehicle>> v;
	vector<shared_ptr<Station>> sResource;
	vector<shared_ptr<Station>> sN;
	int id;
	ofstream toFile;
};

#endif /* NET_H_ */
