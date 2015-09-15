/*
 * Main.cpp
 *
 *  Created on: 15-Sep-2015
 *      Author: anubhav
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "../include/GraphInfo.h"
#define TOP_TO_BOTTOM 1
#define BOTTOM_TO_TOP 2
using namespace std;

static string LIVE_INIT = "";
static string LIVE_BI = "";

string setToString(set<char> s) {
	string res = "";
	set<char>::iterator it;
	for (it = s.begin(); it != s.end(); ++it) {
		res.push_back(*it);
		res.push_back(',');
//		cout << *it << ",";
	}
	if (res.length() == 0) {
		res = "$";
	}
	return res;
}

set<char> unionSet(set<char> s1, set<char> s2) {
	set<char> uS;
	uS.insert(s1.begin(), s1.end());
	uS.insert(s2.begin(), s2.end());
	return uS;
}

set<char> unionSet(vector<set<char> > vsets) {
	set<char> uS;
	for (int i = 0; i < vsets.size(); i++) {
		uS.insert(vsets[i].begin(), vsets[i].end());
	}
	return uS;
}

set<char> intersectionSet(set<char> s1, set<char> s2) {
	set<char> iS;
	set<char>::iterator it;
	for (it = s1.begin(); it != s1.end(); ++it) {
		if (s2.find(*it) != s2.end()) {
			iS.insert(*it);
		}
	}
	return iS;
}

set<char> minusSet(set<char> s1, set<char> s2) {
	set<char> iS;
	set<char>::iterator it;
	for (it = s1.begin(); it != s1.end(); ++it) {
		if (s2.find(*it) == s2.end()) {
			iS.insert(*it);
		}
	}
	return iS;
}

//int dirOfTraversal = BOTTOM_TO_TOP;
int dirOfTraversal = TOP_TO_BOTTOM;

int main() {
	//TODO:
	//FileReader fr;
	//GraphInfo graph = fr.readGraph();


	int numNodes = 6;
	int numEntities = 4;
	GraphInfo graph(numNodes, numEntities);

	//TODO:
	//0. Read BI and INIT.

	graph.setInit("1234");
	graph.setBI("", 1, true);

	//1. Make adjacency matrix.
	graph.setEdge(1, 2);
	graph.setEdge(2, 3);
	graph.setEdge(2, 4);
	graph.setEdge(3, 5);
	graph.setEdge(4, 5);
	graph.setEdge(5, 2);
	graph.setEdge(5, 6);

//	//2. Enter Gen and Kill Info.
	graph.setGenInfo("12", 1);
	graph.setGenInfo("3", 2);
	graph.setGenInfo("", 3);
	graph.setGenInfo("", 4);
	graph.setGenInfo("14", 5);
	graph.setGenInfo("4", 6);

	graph.setKillInfo("", 1);
	graph.setKillInfo("", 2);
	graph.setKillInfo("23", 3);
	graph.setKillInfo("34", 4);
	graph.setKillInfo("", 5);
	graph.setKillInfo("", 6);

	/*
	 * for(int block=n; block>=1; block--){
	 *
	 * }
	 */

	if (dirOfTraversal == BOTTOM_TO_TOP) {
		cout << "Iteration " << 1 << " :" << endl;
		for (int b = numNodes; b >= 1; b--) {
			cout << "Block " << b << "=";
			cout << "\t" << setToString(graph.getOut(b));
			cout << "\t" << setToString(graph.getIn(b));
			cout << endl;

		}

		for (int iter = 2; iter <= 4; iter++) {
			cout << "\nIteration " << iter << " :" << endl;
			//Calculate new set of values.
			for (int b = numNodes; b >= 1; b--) {
				if (b != numNodes) {
					vector<int> succ = graph.getSuccessor(b);
					set<char> outb;
					for (int i = 0; i < succ.size(); i++) {
						outb = unionSet(graph.getIn(succ[i]), outb);
					}
					graph.setOut(outb, b);
				}
				graph.setIn(unionSet(graph.getGenInfo(b), minusSet(graph.getOut(b), graph.getKillInfo(b))), b);

				cout << "Block " << b << ":" << "\t";
				cout << setw(20) << left << setToString(graph.getOut(b));
				cout << setw(20) << left << setToString(graph.getIn(b));
				cout << endl;

			}

		}
	} else if (dirOfTraversal == TOP_TO_BOTTOM) {
		cout << "Iteration " << 1 << " :" << endl;
		for (int b = 1; b <= numNodes; b++) {
			cout << "Block " << b << "=";
			cout << "\t" << setToString(graph.getIn(b));
			cout << "\t" << setToString(graph.getOut(b));
			cout << endl;

		}

		for (int iter = 2; iter <= 4; iter++) {
			cout << "\nIteration " << iter << " :" << endl;
			//Calculate new set of values.
			for (int b = 1; b <= numNodes; b++) {
				if (b != 1) {
					vector<int> pred = graph.getPredecessor(b);
					set<char> inb = graph.getOut(pred[0]);
					for (int i = 0; i < pred.size(); i++) {
						inb = intersectionSet(graph.getOut(pred[i]), inb);
					}
					graph.setIn(inb, b);
				}

				graph.setOut(unionSet(graph.getGenInfo(b), minusSet(graph.getIn(b), graph.getKillInfo(b))), b);

				cout << "Block " << b << ":" << "\t";
				cout << setw(20) << left << setToString(graph.getIn(b));
				cout << setw(20) << left << setToString(graph.getOut(b));
				cout << endl;

			}

		}
	}

	return 0;
}
