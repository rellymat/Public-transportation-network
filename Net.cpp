/*
 * Net.cpp
 *
 *  Created on: 24 במאי 2020
 *      Author: Harel
 */

#include "Net.h"

Net::Net() {
	v.push_back(shared_ptr<Vehicle>(new Bus));
	v.push_back(shared_ptr<Vehicle>(new Rail));
	v.push_back(shared_ptr<Vehicle>(new Sprinter));
	v.push_back(shared_ptr<Vehicle>(new Tram));
	sResource.push_back(shared_ptr<Station>(new Centraal()));
	sResource.push_back(shared_ptr<Station>(new Intercity()));
	sResource.push_back(shared_ptr<Station>(new Stad()));
	id = 0;
}

void Net::updateTime(const char* file) {
	ifstream f;
	int time;
	string name, line;
	f.open(file);
	getline(f, line);
	stringstream ss(line);
	ss >> name >> time;
	if(time < 1)
		throw exception();

	for (int i = 0; i < (int) v.size(); i++) {
		if (v[i].get()->getType().compare(name) == 0) {
			v[i].get()->setWaiting(time);
			f.close();
			return;
		}
	}

	for (int i = 0; i < (int) sResource.size(); i++) {
		if (sResource[i]->getType().compare(name) == 0) {
			sResource[i]->setTime(time);
			f.close();
			return;
		}
	}

	f.close();
	throw exception();
}

void Net::addLine(string source, string target, int time, string vehicle) {
	shared_ptr<Station> s, t;

	s = findStation(source);
	t = findStation(target);

	s.get()->addDestination(getVehicle(vehicle), t, time);
	t.get()->addSource(getVehicle(vehicle), s, time);
}

shared_ptr<Station>& Net::findStation(string s) {
	for (int i = 0; i < (int) sN.size(); ++i) {
		if (sN[i].get()->getName().compare(s) == 0)
			return sN[i];
	}

	return createStation(s);
}

shared_ptr<Station>& Net::createStation(string type) {
	if (type.substr(0, 2).compare("IC") == 0) {
		shared_ptr<Station> t(new Intercity(sResource[1], type));
		t.get()->setId(id++);
		sN.push_back(t);
		return sN[sN.size() - 1];
	}
	if (type.substr(0, 2).compare("CS") == 0) {
		shared_ptr<Station> t(new Centraal(sResource[0], type));
		t.get()->setId(id++);
		sN.push_back(t);
		return sN[sN.size() - 1];
	}
	shared_ptr<Station> t(new Stad(sResource[2], type));
	t.get()->setId(id++);
	sN.push_back(t);
	return sN[sN.size() - 1];
}

shared_ptr<Vehicle>& Net::getVehicle(string name) {
	for (int i = 0; i < (int) v.size(); ++i) {
		if (v[i].get()->getType().compare(name) == 0)
			return v[i];
	}
	throw new exception();
}

void Net::multiExpress(string source, string target) {
	if (stationExists(source) && stationExists(target)) {
		Station* s = findStation(source).get();
		Station* t = findStation(target).get();
		priority_queue<pi, vector<pi>, greater<pi>> stat;
		vector<pair<int, string>> shortPath(sN.size()*4,
				make_pair(numeric_limits<int>::max(), "A"));
		for (int i = 0; i < 4; ++i)
			shortPath[s->getId()*4 + i] = {0,""};

		int pos = s->multiExpress(stat, shortPath, t,0);
		if (pos != -1)
			cout << "Route time is: " << shortPath[t->getId()*4 + pos].first
					<< " minutes" << endl;
		else
			cout << "route unavailable\n";
	}
}

void Net::getInput(int argc, char* argv[]) {
	if(argc < 3)
		throw exception();

	bool input = false;
	for (int i = 1; i < argc; ++i) {
		string name = argv[i];
		if(name == "-i"){
			int j = i + 1;
			if(argv[j][0] == '-')
				throw exception();
			while(j < argc && argv[j][0] != '-'){
				inputI(argv[j++]);
			}
			input = true;
			i = j -1;
		} else if (name == "-c"){
			if(argv[++i][0] == '-')
				throw exception();
			updateTime(argv[i]);
		}
		else if (name == "-o"){
			if(argv[++i][0] == '-')
				throw exception();
			if(!toFile.is_open()){
				toFile.open(argv[i]);
			}
			else
				throw exception();
		}
		else
			throw exception();
	}
	if(!input)
		throw exception();
	if(!toFile.is_open())
		toFile.open("output.dat");
}

void Net::inputI(const char* file) {
	ifstream f;
	f.open(file);
	int time, count = 0;
	string line, vehicle = file, source, target;
	for (int i = 0; i < (int)v.size(); ++i) {
		if(vehicle.find(v[i].get()->getType()) != string::npos){
			vehicle = v[i].get()->getType();
			break;
		}
		if(i == (int)v.size() -1){
			throw exception();
		}
	}

	while(getline(f, line)){
	stringstream ss(line);
	while(count < 3){
		switch(count++){
		case 0:
			ss >> source;
			break;
		case 1:
			ss >> target;
			break;
		case 2:
			ss >> time;
			break;
		}
	}
	count = 0;
	if(time < 1 || source.empty() || target.empty() || source == target)
		throw exception();
	addLine(source, target, time, vehicle);
	}
	f.close();
}

void Net::print() {
	toFile << *this;
}

bool Net::stationExists(string station) {
	for (int i = 0; i < (int) sN.size(); ++i) {
		if (sN[i].get()->getName().compare(station) == 0)
			return true;
	}
	cout << station << " does not exist in the current network.\n";
	return false;
}

void Net::outbound(string source) {
	if (stationExists(source)) {
		Station* temp = findStation(source).get();
		set<Station*> s;
		cout << source << endl;
		printPath(temp, "bus", s, 't');
		printPath(temp, "tram", s, 't');
		printPath(temp, "sprinter", s, 't');
		printPath(temp, "rail", s, 't');
	}
}

Net::~Net() {
	toFile.close();
	// TODO Auto-generated destructor stub
}

void Net::inbound(string target) {
	if (stationExists(target)) {
		cout << target << endl;
		Station* temp = findStation(target).get();
		set<Station*> s;
		printPath(temp, "bus", s, 's');
		printPath(temp, "tram", s, 's');
		printPath(temp, "sprinter", s, 's');
		printPath(temp, "rail", s, 's');
	}
}

void Net::uniExpress(string source, string target) {
	if (stationExists(source) && stationExists(target)) {
		Station* s = findStation(source).get();
		Station* t = findStation(target).get();
		priority_queue<pi, vector<pi>, greater<pi>> stat;
		for (int i = 0; i < (int) v.size(); i++) {
			vector<pair<int, string>> shortPath(sN.size(),
					make_pair(numeric_limits<int>::max(), "A"));
			shortPath[s->getId()] = {0,""};
			s->uniExpressByVehicle(v[i].get()->getType(), stat, shortPath, t);
			cout << v[i].get()->getType() << ": ";
			if (shortPath[t->getId()].first != numeric_limits<int>::max())
				cout << shortPath[t->getId()].first << endl;
			else
				cout << "route unavailable\n";
		}
	}
}

void Net::printPath(Station* stat, string vehicle, set<Station*> s,
		const char& dir) {
	cout << vehicle + ": ";
	if (stat->printByVehicle(vehicle, s, dir)) {
		s.erase(stat);
		for (Station* const & stat : s) {
			cout << '\t' << stat->getName();
		}
		cout << " . . .\n";
	} else if (dir == 't')
		cout << "no outbound travel\n";
	else
		cout << "no inbound travel\n";
	s.clear();
}

std::ostream& operator<<(ostream& os, const Net& n) {
	for (int i = 0; i < (int) n.sN.size(); ++i) {
		os << *(n.sN[i].get()) << endl;
	}
	return os;
}
