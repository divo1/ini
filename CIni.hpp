#include <iostream>
#include <fstream>
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
		void prepareString(string &s);

		int arrayLength;
	public:
		map<string, iniNode*> child;
		iniNode(string);
		iniNode(string, string);

		void add(const char*);
		void add(string&); // metoda do dodawania stringa do configa
		void add(string, string);

		void copy(iniNode*);

		void setValue(string);
		void setExist(bool);
		int count();

		iniNode operator [] (string);
		iniNode operator [] (int);
		bool empty();
		operator string();
		string toString(int i);
		string getName();

		// gettery
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