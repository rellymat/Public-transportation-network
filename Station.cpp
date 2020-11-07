/*
 * Station.cpp
 *
 *  Created on: 24 במאי 2020
 *      Author: Harel
 */

#include "Station.h"

void Station::addDestination(const shared_ptr<Vehicle>& vehicle,
		shared_ptr<Station>& target, int time) {
	int i, j;
	if ((i = findVehicle(dest, vehicle.get()->getType())) == -1) {
		createLine(vehicle, target, dest, time);
	} else if ((j = findStation(dest, i, target.get()->getName())) == -1) {
		Ways* w = new Ways;
		w->target = target;
		w->time = time;
		dest[i]->ws.push_back(w);
	} else if (dest[i]->ws[j]->time > time)
		dest[i]->ws[j]->time = time;

}

Station::Station(shared_ptr<Station>& rhs, string name) {
	this->dest = rhs.get()->dest;
	this->type = rhs.get()->type;
	this->waiting = rhs.get()->waiting;
	this->name = name;
	id = 0;
}

bool Station::printByVehicle(string kind, set<Station*>& s,
		const char& direction) {
	if (direction == 's')
		return printWay(source, kind, s, direction);
	else
		return printWay(dest, kind, s, direction);
}

void Station::addSource(const shared_ptr<Vehicle>& vehicle,
		const shared_ptr<Station>& target, int time) {
	int i, j;
	if ((i = findVehicle(source, vehicle.get()->getType())) == -1) {
		createLine(vehicle, target, source, time);
	} else if ((j = findStation(source, i, vehicle.get()->getType())) == -1) {
		Ways* w = new Ways;
		w->target = target;
		w->time = time;
		source[i]->ws.push_back(w);
	} else if (source[i]->ws[j]->time > time)
		source[i]->ws[j]->time = time;
}

int Station::findStation(vector<Line*>& v, int i, string station) {
	for (int j = 0; j < (int) v[i]->ws.size(); ++j) {
		if (v[i]->ws[j]->target.get()->getName().compare(station) == 0)
			return j;
	}
	return -1;
}

int Station::findVehicle(vector<Line*>& v, string vehicle) {
	for (int i = 0; i < (int) v.size(); ++i) {
		if (v[i]->v.get()->getType().compare(vehicle) == 0)
			return i;
	}
	return -1;
}

void Station::createLine(const shared_ptr<Vehicle>& vehicle,
		const shared_ptr<Station>& target, vector<Line*>& v, int time) {
	Line* line = new Line;
	Ways* w = new Ways;
	line->v = vehicle;
	w->time = time;
	w->target = target;
	line->ws.push_back(w);
	v.push_back(line);
}

bool Station::printWay(vector<Line*>& v, string kind, set<Station*>& s,
		const char& direction) {
	for (int i = 0; i < (int) v.size(); ++i) {
		if (v[i]->v.get()->getType().compare(kind) == 0)
			for (int j = 0; j < (int) v[i]->ws.size(); ++j) {
				if (s.find(v[i]->ws[j]->target.get()) == s.end()) {
					s.insert(v[i]->ws[j]->target.get());
					v[i]->ws[j]->target.get()->printByVehicle(kind, s,
							direction);
					return true;
				}
			}
	}
	return false;
}

void Station::uniExpressByVehicle(string vehicle,
		priority_queue<pi, vector<pi>, greater<pi>>& stat,
		vector<pair<int, string>>& way, Station* target) {
	int pos = -1;
	setWays(vehicle, stat, way, target, pos);
	if (!stat.empty()) {
		Station* s = stat.top().second;
		stat.pop();
		s->uniExpressByVehicle(vehicle, stat, way, target);
	}

}

void Station::setWays(string vehicle,
		priority_queue<pi, vector<pi>, greater<pi>>& stat,
		vector<pair<int, string>>& way, Station* target, int pos) {
	int vehNumber, index = 4, newPos;
	if(pos == -1){
		index = 1;
		pos = 0;
	}
	if ((vehNumber = findVehicle(dest, vehicle)) != -1)
		for (int i = 0; i < (int) dest[vehNumber]->ws.size(); ++i) {
			int wayTime = way[this->getId() * index + pos].first
					+ dest[vehNumber]->ws[i]->time;
			if (way[this->getId() * index + pos].first != 0) {
				if (way[this->getId() * index + pos].second.compare(vehicle) == 0)
					wayTime += dest[vehNumber]->v.get()->stopWaiting();
				else
					wayTime += this->stopWaiting();
			}
			if(index == 1){
				newPos = 0;
			}else
				newPos = findPos(vehicle);
			if (way[dest[vehNumber]->ws[i]->target.get()->getId() * index + newPos].first
					> wayTime) {
				int time = wayTime*10+ findPos(vehicle);
				way[dest[vehNumber]->ws[i]->target.get()->getId()*index + newPos] = {wayTime,vehicle};
				stat.push( {time,dest[vehNumber]->ws[i]->target.get()});
			}
		}
	}

int Station::multiExpress(priority_queue<pi, vector<pi>, greater<pi>>& stat,
		vector<pair<int, string>>& way, Station* target, int pos) {

	for (int i = 0; i < (int) dest.size(); ++i) {
		setWays(dest[i]->v.get()->getType(), stat, way, target, pos);
	}
	if (!stat.empty()) {
		pair<int,Station*> top = stat.top();
		string vehName = way[top.second->getId()*4 +top.first%10].second;
		int newPos = findPos(vehName);
		stat.pop();
		if (top.second == target){
			string s;
			target->printExpress(way,target,vehName, s);
			return newPos;
		}

		return top.second->multiExpress(stat, way, target,newPos);
	}
	return -1;
}

int Station::findPos(string vehicle) {
	if (vehicle.compare("rail") == 0)
		return 0;
	else if (vehicle.compare("bus") == 0)
		return 1;
	else if (vehicle.compare("sprinter") == 0)
		return 2;
	else
		return 3;
}

void Station::printExpress(vector<pair<int, string> >& way,Station* st, string& vehicle, string& s) {
	s += " --" + vehicle +  "-->" + this->getName();
	int sourceVeh = findVehicle(st->source,vehicle);
	int wayTimeDest = way[st->getId()*4 + findPos(vehicle)].first;
	for (int i = 0; i < (int)source[sourceVeh]->ws.size(); ++i) {
		Station* station = st->source[sourceVeh]->ws[i]->target.get();
		for (int j = 0; j < 4; ++j) {
			int wayTimeSource = wayTimeDest - this->source[sourceVeh]->ws[i]->time;
			if(way[station->getId()*4 +j].first != 0 && way[station->getId()*4 +j].first != numeric_limits<int>::max()){
				if(way[station->getId()*4 +j].second.compare(vehicle) != 0)
					wayTimeSource -= station->stopWaiting();
				else{
					int index = station->findVehicle(station->source,way[station->getId()*4 +j].second);
					int vehWait = station->source[index]->v.get()->stopWaiting();
					wayTimeSource -= vehWait;
				}
			}
			if(way[station->getId()*4 + j].first == wayTimeSource){
				if(wayTimeSource == 0){
					s += " " + station->getName();
					printS(s);
					return;
				}else
	    			station->printExpress(way, station, way[station->getId()*4 +j].second,  s);
			}
		}

	}

}

void Station::printS(string& s) {
	stack<string> stack;
	stringstream ss(s);
	string temp;
	while(ss >> temp)
		stack.push(temp);
	cout << "The fastest route is:\n";
	while(!stack.empty()){
		cout << stack.top();
		stack.pop();
	}
	cout << endl;
}

Station::~Station() {
	// TODO Auto-generated destructor stub
}

Station::Station(int time, string t, string name) {
	this->waiting = time;
	this->type = t;
	this->name = name;
	id = 0;
}

std::ostream& operator<<(ostream& os, const Station& s) {
	if (s.dest.size() == 0) {
		return (os << s.getName() << " routes's unavailable\n" << endl);
	}
	os << s.getName() << " routes's -" << endl;
	for (int i = 0; i < (int) s.dest.size(); i++) {
		os << '\t' << s.dest[i]->v.get()->getType() << ":\n";
		for (int j = 0; j < (int) s.dest[i]->ws.size(); ++j) {
			os << '\t' << "    to: "
					<< s.dest[i]->ws[j]->target.get()->getName();
			os << ", Time: " << s.dest[i]->ws[j]->time << " minutes" << endl;
		}
	}
	return os;
}
