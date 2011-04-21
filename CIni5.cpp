CIni::CIni(string filepath) {
	this->file.open(filepath.c_str(), fstream::in | fstream::out);
	
	char buf[255];
	while(this->file.good()) {
		file.getline(buf, 255);
		cout << buf << endl;
	}
}
iniNode::iniNode() {  }
iniNode::iniNode(string name, bool flaga) {
	this->name = this->trim(name);
	this->value = "[empty]";
	this->exist = false;
}
iniNode::iniNode(string &s) {
	this->name = "";
	this->trim(s);
	if(!s.empty()) {
		int i = 0;
		for(; i < s.length(); i++) {
			if(s[i] == '.' || s[i] == '=' || s[i] == '\0') {
				break;
			}
			this->name += s[i];
		}
		s.erase(0, i + 1);
	}
}
iniNode::iniNode(string name, string &s) {
	this->name = this->trim(name);
	this->trim(s);
	this->value = "";
	this->exist = true;
	bool flaga = false;
	if(!s.empty()) {
		int i = 0;
		for(; i < s.length(); i++) {
			if(s[i] == '.' || s[i] == '=' || s[i] == '\0') {
				if(s[i] == '=') {
					flaga = true;
				}
				break;
			}
			this->value += s[i];
		}
		s.erase(0, i + 1);
	}
	
	if(flaga) {
		for(int i = 0; i < s.length(); i++) {
			if(s[i] == '.') {
				s[i] = ',';
			}
		}
	}
	this->add(this->value, s);
	for(int i = 0; i < this->value.length(); i++) {
		if(this->value[i] == ',') {
			this->value[i] = '.';
		}
	}
}
void iniNode::add(string name, string s) {
	if(!s.empty()) {
		this->trim(name);
		if(this->child.find(name) == this->child.end()) {
			this->child.insert(pair<string,iniNode*>(name, new iniNode(name, s)));
		} else {
			string names = "";
			int i = 0;
			for(; i < s.length(); i++) {
				if(s[i] == '.' || s[i] == '=' || s[i] == '\0') {
					break;
				}
				names += s[i];
			}
			s.erase(0, i + 1);
			
			this->child[name]->add(names, s);
		}
	}
}
iniNode iniNode::operator [](string s) {
	if(this->child.find(s) == this->child.end()) {
		this->child.insert(pair<string,iniNode*>(s, new iniNode(s)));
	}
	return *this->child[s];
}
string iniNode::getName() {
	return this->name;
}
iniNode::operator string() {
	return this->value;
}
string iniNode::trim(string &s) {
	int k = 0, l = 1;
	for(int i = 0; i < s.length(); i++) {
		if(s[i] != ' ' && s[i] != '\t' && k == 0) {
			k = i;
			break;
		}
	}
	if(k != 0) {
		s.erase(0, k);
	}
	if(!s.empty()) {
		for(int j = s.length() - 1; j >= 0; --j) {
			if(s[j] != ' ' && s[j] != '\t' && l == 1) {
				l = j;
				break;
			}
		}
		if(l != 1) {
			s.erase(l + 1);
		}
	}
	return s;
}
bool iniNode::empty() {
	return this->exist;
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