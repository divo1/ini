CIni::CIni(string filepath) {
	this->file.open(filepath.c_str(), fstream::in | fstream::out);
	
	string temp;
	string name = "default";
	while(this->file.good()) {
		getline(this->file, temp);
		if(!temp.empty()) {
			if(temp[0] == '[' && temp[temp.length() - 1] == ']') {
				int flag = 0;
				this->parent = "";
				for(int i = 0; i < temp.length(); i++) {
					if(temp[i] == ':') {
						flag = i;
						break;
					}
				}
				
				if(flag) {
					name = temp.substr(1, flag - 1);
					this->parent = temp.substr(flag + 1, temp.length() - flag - 2);
					if(this->nodes.find(name) == this->nodes.end() && this->nodes.find(this->parent) != this->nodes.end()) {
						iniNode *temp = new iniNode(name, this->nodes[this->parent]->get(""), true);
						temp->copy(this->nodes[this->parent]);
						this->nodes.insert(pair<string,iniNode*>(name, temp));
					} /*else if(this->nodes.find(this->parent) == this->nodes.end()) {
						throw new CIniException("Brak parenta");
					}*/
				} else {
					name = temp.substr(1, temp.length() - 2);
				}
			} else if(temp[0] != ';') {
				if(this->nodes.find(name) == this->nodes.end()) {
					this->nodes.insert(pair<string,iniNode*>(name, new iniNode(name, temp)));
				} else {
					string names = "";
					int i = 0;
					for(; i < temp.length(); i++) {
						if(temp[i] == '.' || temp[i] == '=' || temp[i] == '\0') {
							break;
						}
						names += temp[i];
					}
					temp.erase(0, i + 1);
					
					this->nodes[name]->add(names, temp);
				}
			}
		}
	}
}
iniNode CIni::operator [](string s) {
	if(this->nodes.find(s) == this->nodes.end()) {
		this->nodes.insert(pair<string,iniNode*>(s, new iniNode(s, true)));
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
			temp += "\t" + (*it2).first + " : " + (*it2).second->get() + "\n";
			temp += (*it2).second->toString(2);
		}
	}
	return temp;
}

iniNode::iniNode() {  }
iniNode::iniNode(string name, bool flaga) {
	this->name = this->trim(name);
	this->value = "[empty]";
	this->exist = false;
}
iniNode::iniNode(string &s) {
	this->name = "";
	this->value = "";
	this->exist = true;
	bool flaga = false;
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
	string temp = "";
	if(!s.empty()) {
		int i = 0;
		for(; i < s.length(); i++) {
			if(s[i] == '.' || s[i] == '=' || s[i] == '\0') {
				if(s[i] == '=') {
					flaga = true;
				}
				break;
			}
			temp += s[i];
		}
		s.erase(0, i + 1);
	}
	
	if(flaga) {
		replace(s.begin(), s.end(), '.', ',');
	}
	this->value = temp;
	this->add(this->value, s);

	if(!flaga) {
		this->value = "[Array]";
	}
	replace(this->value.begin(), this->value.end(), ',', '.');
}
iniNode::iniNode(string name, string &s) {
	this->name = this->trim(name);
	this->trim(s);
	this->value = "[Array]";
	this->exist = true;
	bool flaga = false;
	string temp = "";
	int i = 0;
	for(; i < s.length(); i++) {
		if(s[i] == '.' || s[i] == '=' || s[i] == '\0') {
			if(s[i] == '=') {
				flaga = true;
			}
			break;
		}
		temp += s[i];
	}
	s.erase(0, i + 1);
	
	if(flaga) {
		replace(s.begin(), s.end(), '.', ',');
	}
	this->value = temp;
	this->add(temp, s);
	replace(this->value.begin(), this->value.end(), ',', '.');
}
iniNode::iniNode(string name, string s, bool flag) {
	this->name = this->trim(name);
	this->value = s;
	this->exist = flag;
}

void iniNode::add(string s) {
	if(!s.empty()) {
		int i = 0;
		string name = "";
		for(; i < s.length(); i++) {
			if(s[i] == '.' || s[i] == '\0') {
				break;
			}
			name += s[i];
		}
		s.erase(0, i + 1);
		
		if(!s.empty()) {
			this->add(name, s);
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

			if(!s.empty()) {
				this->child[name]->add(names, s);
			} else {
				this->child[name]->value = names;
				map<string,iniNode*> temp;
				this->child[name]->child = temp;
			}
		}
	}
}

void iniNode::copy(iniNode *n) {
	map<string, iniNode*>::iterator it;
	for(it = n->child.begin(); it != n->child.end(); it++) {
		this->child.insert(pair<string,iniNode*>((*it).first, new iniNode((*it).first, (*it).second->value, true)));
		this->child[(*it).first]->copy((*it).second);
	}
}

iniNode iniNode::operator [](string s) {
	if(this->child.find(s) == this->child.end()) {
		this->child.insert(pair<string,iniNode*>(s, new iniNode(s, true)));
	}
	//cout << this->child[s]->empty();
	return (*this->child[s]);
}
string iniNode::getName() {
	return this->name;
}
iniNode::operator string() {
	string temp;
	map<string, iniNode*>::iterator it;
	for(it = this->child.begin(); it != this->child.end(); it++) {
		temp += (*it).first + " : " + ((*it).second->value);
	}
	return temp;
}
string iniNode::toString(int i) {
	string temp;
	map<string, iniNode*>::iterator it;
	for(it = this->child.begin(); it != this->child.end(); it++) {
		for(int j = 0; j < i; j++) {
			temp += '\t';
		}
		temp += (*it).first + " : " + ((string)(*it).second->get("empty")) + '\n';
		temp += (*it).second->toString(i + 1);
	}
	return temp;
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
	return !this->exist;
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