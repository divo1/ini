#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>

#include "CIniException.hpp"

using namespace std;
class iniNode;

class CIni {
	private:
		fstream file;
		map<string, iniNode*> nodes;
		string parent;
	public:
		CIni(string);
		iniNode operator [] (string);
		operator string();
};

class iniNode {
	private:
		string name;
		string value;
		bool exist;
		string trim(string &);
	public:
		map<string, iniNode*> child;
		iniNode();
		iniNode(string&);
		iniNode(string, bool);
		iniNode(string, string&);
		iniNode(string, string, bool);

		void add(string);
		void add(string, string);
		
		void copy(iniNode*);

		string getName();
		iniNode operator [] (string);
		bool empty();
		operator string();

		string get() throw(CIniException);
		string get(string);
		int get(int);
		double get(double);
		float get(float);

		string getS() throw(CIniException);
		string getS(string);

		int getI() throw(CIniException);
		int getI(int);

		float getF() throw(CIniException);
		float getF(float);

		double getD() throw(CIniException);
		double getD(double);
};