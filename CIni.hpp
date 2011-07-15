#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef CINIHPP
#define CINIHPP 1

#include "CIniException.hpp"

using namespace std;
class iniNode;

class CIni {
	private:
		fstream file;
		map<string, iniNode*> nodes;
		string parent;
	public:
		friend ostream& operator << (ostream &out, CIni &c);
		CIni(string);
		~CIni();
		iniNode operator [] (string);
		operator string();
};

class iniNode {
	private:
		iniNode* parent;
		string name;
		string value;
		bool exist;
		bool array;
		void prepareString(string &s);

		int arrayLength;
	public:
		friend ostream& operator << (ostream &out, iniNode &c);
		friend ostream& operator << (ostream &out, iniNode c);
		map<string, iniNode*> child;
		iniNode(string, iniNode* parent = NULL);
		iniNode(string, string, iniNode* parent = NULL);

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
		string toString(int, string s = "");
		string path();
		string getName();
		string* toArray();

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

#endif