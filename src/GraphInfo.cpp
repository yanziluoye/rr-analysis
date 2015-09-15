/*
 * GraphInfo.cpp
 *
 *  Created on: 15-Sep-2015
 *      Author: anubhav
 */

#include <iostream>
#include "../include/GraphInfo.h"
using namespace std;

GraphInfo::GraphInfo(int n, int e) {
	numNodes = n;
	numEntities = e;
	graphMatrix.reserve(n+1);
	localGenInfo.reserve(n);
	localKillInfo.reserve(n);
	mIn.reserve(n);
	mOut.reserve(n);

	for (int i = 0; i <= n; i++) {
		set<char> sCharsG;
		set<char> sCharsK;
		set<char> sCharsI;
		set<char> sCharsO;
		localGenInfo.push_back(sCharsG);
		localKillInfo.push_back(sCharsK);
		mIn.push_back(sCharsI);
		mOut.push_back(sCharsO);
		vector<bool> vec;
		vec.reserve(n+1);
		for(int j=0; j<=n; j++){
			vec.push_back(0);
		}

		graphMatrix.push_back(vec);
	}
	//mInit.insert('a');
}

GraphInfo::~GraphInfo() {
}

void GraphInfo::setGenInfo(std::string genString, int blockNum) {
	for (int i = 0; i < genString.length(); i++) {
		localGenInfo[blockNum].insert((char) genString[i]);
	}
}

void GraphInfo::setKillInfo(std::string killString, int blockNum) {
	for (int i = 0; i < killString.length(); i++) {
		localKillInfo[blockNum].insert((char) killString[i]);
	}
}

std::set<char> GraphInfo::getGenInfo(int blockNum) {
	return localGenInfo[blockNum];
}

std::set<char> GraphInfo::getKillInfo(int blockNum) {
	return localKillInfo[blockNum];
}

void GraphInfo::setEdge(int i, int j) {
	graphMatrix[i][j] = true;
}

bool GraphInfo::isConnected(int i, int j) {
	return graphMatrix[i][j];
}

void GraphInfo::setBI(std::string bstr, int blockNum, bool in) {
	if (bstr.length() == 0) {
		//mBI.insert('$');
	} else {
		for (int i = 0; i < bstr.length(); i++) {
			mBI.insert((char) bstr[i]);
		}
	}
	if (in) {
		mIn[blockNum].clear();
		//mIn[blockNum].insert(mBI.begin(), mBI.end());
	} else {
		mOut[blockNum].clear();
		//mOut[blockNum].insert(mBI.begin(), mBI.end());
	}
}

void GraphInfo::setInit(std::string initStr) {
	for (int i = 0; i < initStr.length(); i++) {
		mInit.insert((char) initStr[i]);
	}

	for (int i = 0; i <= numNodes; i++) {
		mIn[i].insert(mInit.begin(), mInit.end());
		mOut[i].insert(mInit.begin(), mInit.end());
	}
}

std::set<char> GraphInfo::getBI() {
	return mBI;
}

std::set<char> GraphInfo::getInit() {
	return mInit;
}

std::set<char> GraphInfo::getIn(int blockNum) {
	return mIn[blockNum];
}

std::set<char> GraphInfo::getOut(int blockNum) {
	return mOut[blockNum];
}

void GraphInfo::setIn(std::set<char> inSet, int blockNum) {
	mIn[blockNum] = inSet;
}

void GraphInfo::setOut(std::set<char> outSet, int blockNum) {
	mOut[blockNum] = outSet;
}

vector<int> GraphInfo::getSuccessor(int i) {
	vector<int> res;
	for (int j = 0; j < graphMatrix.size(); j++) {
		if (graphMatrix[i][j] == true) {
			res.push_back(j);
		}
	}
	return res;
}

void GraphInfo::printGraph(){
	for(int i=0; i<graphMatrix.size(); i++){
		for(int j=0; j<graphMatrix.size(); j++){
			cout<<graphMatrix[i][j]<<",";
		}
		cout<<endl;
	}
}

vector<int> GraphInfo::getPredecessor(int j) {
	vector<int> res;
	for (int i = 0; i < graphMatrix.size(); i++) {
		if (graphMatrix[i][j] == true) {
			res.push_back(i);
		}
	}
	return res;
}
