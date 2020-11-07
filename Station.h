/*
 * Station.h
 *
 *  Created on: 24 במאי 2020
 *      Author: Harel
 */

#ifndef STATION_H_
#define STATION_H_
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <set>
#include <limits>
#include "Vehicle.h"
#include <stack>
#include <utility>
using namespace std;


class Station {
private:
	struct Ways{
		shared_ptr<Station> target;
		int time;
	};
	struct Line{
		shared_ptr<Vehicle> v;
		vector<Ways*> ws;
	};
	vector<Line*> dest;
	vector<Line*> source;
	string type;
	string name;
	int waiting;
	int id;
	int findPos(string vehicle);
	typedef pair<int, Station*> pi;
	void printExpress(vector<pair<int,string>>& way, Station* st, string& vehicle, string& s);
	void printS(string& s);
	void setWays(string vehicle, priority_queue<pi, vector<pi>, greater<pi>>& stat, vector<pair<int,string>>& way, Station* target, int pos);
public:
	Station() = default; // @suppress("Class members should be properly initialized")
	Station(int time, string t, string name);
	Station(shared_ptr<Station>& rhs, string name);
	virtual int stopWaiting() {return waiting;}
	void setTime(int time) {waiting = time;}
	void addDestination(const shared_ptr<Vehicle>& vehicle, shared_ptr<Station>& target, int time);
	void addSource(const shared_ptr<Vehicle>& vehicle, const shared_ptr<Station>& target, int time);
	int findStation(vector<Line*>& v, int i, string station);
	int findVehicle(vector<Line*>& v,  string vehicle);
	void createLine(const shared_ptr<Vehicle>& vehicle, const shared_ptr<Station>& target, vector<Line*>& v, int time);
	bool printByVehicle(string kind, set<Station*>& s, const char& direction);
	bool printWay(vector<Line*>& v,string kind, set<Station*>& s, const char& direction);
	void uniExpressByVehicle(string vehicle, priority_queue<pi, vector<pi>, greater<pi>>& stat, vector<pair<int,string>>& way, Station* target);
	int multiExpress(priority_queue<pi, vector<pi>, greater<pi>>& stat, vector<pair<int,string>>& way, Station* target, int pos);
	friend std:: ostream& operator<<(ostream& os, const Station& v);
	const string& getType() const {
				return type;
			}
	const string& getName() const {
				return name;
			}
	int getId() const {
		return id;
	}

	void setId(int id) {
		this->id = id;
	}
	void setName(const string& name) {
		this->name = name;
	}

	virtual ~Station();
};

#endif /* STATION_H_ */
