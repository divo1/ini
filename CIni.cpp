#include "CIni.hpp"

ostream& operator << (ostream& out, CIni &c) {
	out << (string)c;
}
ostream& operator << (ostream& out, iniNode &c) {
	out << c.toString(1);
}
ostream& operator << (ostream& out, iniNode c) {
	out << c.toString(1);
}

const std::string whiteSpaces(" \f\n\r\t\v");
void trimRight( std::string& str, const std::string& trimChars = whiteSpaces ) {
	std::string::size_type pos = str.find_last_not_of( trimChars );
	str.erase( pos + 1 );
}
void trimLeft( std::string& str, const std::string& trimChars = whiteSpaces ) {
	std::string::size_type pos = str.find_first_not_of( trimChars );
	str.erase( 0, pos );
}
void trim( std::string& str, const std::string& trimChars = whiteSpaces ) {
	trimRight( str, trimChars );
	trimLeft( str, trimChars );
}

CIni::CIni(string filepath) {
	this->file.open(filepath.c_str(), fstream::in);

	string temp;
	string name = "default";
	while(this->file.good()) {
		getline(this->file, temp);
		trim(temp);

		if(!temp.empty() && temp[0] != ';') {
			if(temp[0] == '[') {
				temp[0] = ' ';
				replace(temp.begin(), temp.end(), ']', ' ');
				trim(temp);
				size_t found = temp.find(':');
				if(found != string::npos) {
					name = temp.substr(0, found);
					string parent = temp.substr(found + 1);

					if(this->nodes.find(name) == this->nodes.end()) {
						this->nodes.insert(pair<string,iniNode*>(name, new iniNode(name)));
						this->nodes[name]->setValue("sekcja()");
						if(this->nodes.find(parent) != this->nodes.end()) {
							this->nodes[name]->copy(this->nodes[parent]);
						}
					}
				} else {
					name = temp;
					this->nodes.insert(pair<string,iniNode*>(temp, new iniNode(temp)));
					this->nodes[temp]->setValue("sekcja()");
				}
			} else {
				if(this->nodes.find(name) == this->nodes.end()) {
					this->nodes.insert(pair<string,iniNode*>(name, new iniNode(name, temp)));
				} else {
					this->nodes[name]->add(temp);
				}
			}
		}
	}
}
CIni::~CIni() {
	this->file.close();
}
iniNode CIni::operator [](string s) {
	if(this->nodes.find(s) == this->nodes.end()) {
		this->nodes.insert(pair<string,iniNode*>(s, new iniNode(s)));
		this->nodes[s]->setValue("empty()");
		this->nodes[s]->setExist(false);
	}
	return *this->nodes[s];
}
CIni::operator string() {
	map<string, iniNode*>::iterator it;
	string temp;
	for(it = this->nodes.begin(); it != this->nodes.end(); it++) {
		temp += "[" + ((string)(*it).first) + "]\n";
		map<string, iniNode*>::iterator it2;
		for(it2 = (*it).second->child.begin(); it2 != (*it).second->child.end(); it2++) {
			temp += (*it2).second->toString(1);
		}
	}
	return temp;
}


iniNode::iniNode(string name, iniNode* parent) {
	this->exist = true;
	trim(name);
	this->parent = parent;
	this->name = name;
	this->array = false;
	this->arrayLength = 0;

	//replace(this->value.begin(), this->value.end(), ',', '.');
}
iniNode::iniNode(string name, string s, iniNode* parent) {
	this->name = name;
	this->parent = parent;
	this->array = false;
	this->exist = true;
	this->arrayLength = 0;
	this->add(s);

	//replace(this->value.begin(), this->value.end(), ',', '.');
}

void iniNode::add(string &s) {
	int i = 0;
	string name = "";
	bool flaga = false;
	bool flaga2 = false;
	for(; i < s.length(); i++) {
		if(s[i] == '.' || s[i] == '=' || s[i] == '\0') {
			if(s[i] == '=') {
				flaga = true;
			}
			break;
		}
		if(s[i] == '[') {
			flaga2 = true;
			s[i] = ' ';
			if(i < s.length() - 1) {
				s[i + 1] = ' ';
			}

			string temp = s.substr(0, i);
			string temp2 = s.substr(i + 2);
			ostringstream ss;
			ss << this->arrayLength;
			this->arrayLength++;
			s = temp + "." + ss.str() + temp2;
			break;
		}
		name += s[i];
	}
	s.erase(0, i + 1);
	trim(name);
	trim(s);

	if(this->parent != NULL && this->parent->array) {
		this->array = true;
	}

	if(flaga) {
		this->value = "Array()";
		if(this->child.find(name) == this->child.end()) {
			this->child.insert(pair<string,iniNode*>(name, new iniNode(name, this)));
		}
		this->child[name]->setValue(s);
		if(flaga2) {
			this->child[name]->array = true;
		}
	} else {
		this->add(name, s);
		if(flaga2) {
			this->child[name]->array = true;
		}
	}
	/*
	if(this->parent != NULL) {
		this->parent->array = false;
	}*/
}

void iniNode::add(const char* s) {
	string temp(s);
	this->add(temp);
}
void iniNode::add(string name, string s) {
	this->value = "Array()";

	if(this->child.find(name) == this->child.end()) {
		if(this->arrayLength > 1) {
			this->arrayLength = 0;
		}
		this->child.insert(pair<string,iniNode*>(name, new iniNode(name, s, this)));
	} else {
		this->child[name]->add(s);
	}
}

void iniNode::copy(iniNode *n) {
	map<string, iniNode*>::iterator it;
	for(it = n->child.begin(); it != n->child.end(); it++) {
		this->child.insert(pair<string,iniNode*>((*it).first, new iniNode((*it).first, this)));
		this->child[(*it).first]->setValue((*it).second->value);
		this->child[(*it).first]->array = (*it).second->array;
		this->child[(*it).first]->parent = (*it).second->parent;
		this->child[(*it).first]->copy((*it).second);
	}
}

iniNode iniNode::operator [](string s) {
	if(this->child.find(s) == this->child.end()) {
		this->child.insert(pair<string,iniNode*>(s, new iniNode(s)));
		this->child[s]->setValue("empty()");
		this->child[s]->setExist(false);
	}
	return (*this->child.find(s)->second);
}
iniNode iniNode::operator [](int i) {
	ostringstream ss;
	ss << i;
	string s = ss.str();
	if(this->child.find(s) == this->child.end()) {
		this->child.insert(pair<string,iniNode*>(s, new iniNode(s)));
		this->child[s]->setValue("empty()");
		this->child[s]->setExist(false);
	}
	return (*this->child.find(s)->second);
}
string iniNode::getName() {
	return this->name;
}
string* iniNode::toArray() {
	string *s = new string[this->child.size()];
	int i = 0;
	for(map<string, iniNode*>::iterator it = this->child.begin(); it != this->child.end(); it++, i++) {
		s[i] = (*it).first;
	}
	return s;
}

iniNode::operator string() {
	string temp = this->toString(1);
	return temp;
}
string iniNode::toString(int i, string temp2) {
	i = i + 1;
	string temp = "";

	if(this->value != "Array()") {
		if(this->parent != NULL) {
			if(this->parent->array) {
				// temp = "\t" + this->parent->path() + "[" +this->name + "] = " + this->value + "\n";
				temp = "\t" + this->parent->path() + "[] = " + this->value + "\n";
			} else {
				temp = "\t" + this->parent->path() + this->name + " = " + this->value + "\n";
			}
		} else {
			temp = "\t" + this->name + " = " + this->value + "\n";
		}
	}
	map<string, iniNode*>::iterator it;
	for(it = this->child.begin(); it != this->child.end(); it++) {
		temp += temp2;
		temp += (*it).second->toString(i + 1, temp2);
	}
	return temp;
}
string iniNode::path() {
	if(this->parent == NULL) {
		return "";
	// } else if(this->child.size() == 0) {
		// return this->parent->path() + this->name;
	} else {
		if(this->parent->array) {
			return this->parent->path() + "[" + this->name + "]";
		} else if(this->array) {
			return this->parent->path() + this->name;
		} else {
			return this->parent->path() + this->name + ".";
		}
	}
}
void iniNode::prepareString(string &s) {

}
bool iniNode::empty() {
	return !this->exist;
}
void iniNode::setValue(string s) {
	this->value = s;
}
void iniNode::setExist(bool f) {
	this->exist = f;
}
int iniNode::count() {
	if(this->empty()) {
		return 0;
	} else if(this->value == "Array()") {
		return this->child.size();
	}
	return 1;
}


// gettery
string iniNode::get() throw(CIniException) {
	if(this->empty()) {
		throw CIniException("Pusty node bez domyślnej wartości.");
	}
	return this->value;
}
string iniNode::get(string s) {
	if(this->empty()) {
		return s;
	}
	return this->get();
}
int iniNode::get(int s) {
	if(this->empty()) {
		return s;
	}
	return atoi(this->get().c_str());
}
float iniNode::get(float s) {
	if(this->empty()) {
		return s;
	}
	return (float)atof(this->get().c_str());
}
double iniNode::get(double s) {
	if(this->empty()) {
		return s;
	}
	return atof(this->get().c_str());
}

string iniNode::getS() throw(CIniException) {
	return this->get();
}
int iniNode::getI() throw(CIniException) {
	return atoi(this->get().c_str());
}
float iniNode::getF() throw(CIniException) {
	return (float)atof(this->get().c_str());
}
double iniNode::getD() throw(CIniException) {
	return (double)atof(this->get().c_str());
}

string iniNode::getS(string s) {
	if(this->empty()) {
		return s;
	}
	return this->getS();
}
int iniNode::getI(int s) {
	if(this->empty()) {
		return s;
	}
	return this->getI();
}
float iniNode::getF(float s) {
	if(this->empty()) {
		return s;
	}
	return this->getF();
}
double iniNode::getD(double s) {
	if(this->empty()) {
		return s;
	}
	return this->getD();
}