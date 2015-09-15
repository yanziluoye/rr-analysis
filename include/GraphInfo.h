/*
 * GraphInfo.h
 *
 *  Created on: 15-Sep-2015
 *      Author: anubhav
 */

#ifndef INCLUDE_GRAPHINFO_H_
#define INCLUDE_GRAPHINFO_H_

#include <vector>
#include <set>
#include <string>

class GraphInfo {
	int numNodes;    //Num of nodes in CFG
	int numEntities; //Num of variables/expressions

	std::set<char> mBI;
	std::set<char> mInit;

	std::vector<std::vector<bool> > graphMatrix;
	std::vector<std::set<char> > localGenInfo;
	std::vector<std::set<char> > localKillInfo;

	std::vector<std::set<char> > mIn;
	std::vector<std::set<char> > mOut;

public:

	GraphInfo(int, int);
	virtual ~GraphInfo();

	void setGenInfo(std::string, int);
	void setKillInfo(std::string, int);
	std::set<char> getGenInfo(int);
	std::set<char> getKillInfo(int);

	void setEdge(int, int);
	bool isConnected(int, int);
	std::vector<int> getSuccessor(int);
	std::vector<int> getPredecessor(int);
	void printGraph();

	void setBI(std::string,int,bool);
	void setInit(std::string);
	std::set<char> getBI();
	std::set<char> getInit();

	std::set<char> getIn(int);
	std::set<char> getOut(int);
	void setIn(std::set<char>,int);
	void setOut(std::set<char>,int);

};

#endif /* INCLUDE_GRAPHINFO_H_ */
