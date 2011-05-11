#include "CIni.hpp"
#include <time.h>

/**
 * TODO:
 * - dodanie parsowania tablic
 * - jeżeli nie ma wartosc = cos, a jest wartosc.wartosc1 = cos, to wartosc ma zwrocic array
 * - count
 * - dodac nadpisywanie wartosci przez kolejne elementy
 *
 * DONE:
 * - dziedziczenie sekcji - 21.04.2011
 */

int main() {

	CIni c("config.ini");
	cout << (string)c;

/*
	string str = "test2.test3 = 2.5.6";
	iniNode n("test", str);
	str = "test4.test5 = aaa";
	n.add(str);
	str = "test8.test9 = aaa";
	n.add("test7", str);
	
	str = "test16.test17 = 3.6.9";
	iniNode n2("qwerty", str);
	
	cout << (string)n << endl << endl;
	
	cout << (string)n2 << endl << endl;
	n2.copy(&n);
	cout << endl;
	cout << (string)n2 << endl;*/
	return 0;
}