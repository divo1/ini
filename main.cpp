#include "CIni.hpp"
#include "CIni.cpp"
#include <time.h>

/**
 * TODO:
 * - dodanie parsowania tablic
 * - jeżeli nie ma wartosc = cos, a jest wartosc.wartosc1 = cos, to wartosc ma zwrocic array
 * - count
 * - dodac nadpisywanie wartosci przez kolejne elementy
 * - dziedziczenie sekcji
 */

int main() {
	CIni c("config.ini");
	cout << (string)c;
	
	/*
	string str = "test2.test3 = 2.5.6";
	iniNode n("test", str);
	str = "test2.test4 = aaa";
	n.add(str);
	n.add("test3", str);
	
	cout << (string)n["test2"]["test3"] << endl;
	cout << (string)n["test2"]["test4"] << endl;
	cout << (string)n["test3"]["test2"]["test4"] << endl;
	*/
	return 0;
}