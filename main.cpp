#include "CIni.cpp"
#include <time.h>

/**
 * TODO:
 * - dodanie parsowania tablic
 * - count
 * - dodac nadpisywanie wartosci przez kolejne elementy
 *
 * DONE:
 * - dziedziczenie sekcji - 21.04.2011
 * - jeżeli nie ma wartosc = cos, a jest wartosc.wartosc1 = cos, to wartosc ma zwrocic array - 21.04.2011
 */

int main() {
	for(int i = 0; i < 999999; i++) {
		CIni c("config.ini");
		// cout << (string)c;
		// cout << endl << endl;
		cout << c["sekcja3"]["wartosc"]["wartosc"]["qwert1"][0].count();
	}

	// string name = "test";

	// iniNode n(name);
	// n.add("a.test2.test3 = 678nn.a.ad");

	// n.add("a.test3.test3[] = nn.a09.ad");
	// n.add("a.test3.test3[] = nn.a08.ad");
	// n.add("a.test3.test3[] = nn.a07.ad");
	// n.add("a.test3.test3[] = nn.a06.ad");
	// n.add("a.test3.test3[] = nn.a05.ad");

	// n.add("b.test4.test13 = 678nn.a.ad");
	// n.add("c.test5.test13 = 678nn.a.ad");
	// n.add("d.test6.test13 = 678nn.a.ad");


	// n.add("e.test7.test13[] = 678nn.a1.ad");
	// n.add("e.test7.test13[] = 678nn.a2.ad");
	// n.add("e.test7.test13[] = 678nn.a3.ad");
	// n.add("e.test7.test13[] = 678nn.a4.ad");
	// n.add("e.test7.test13[] = 678nn.a5.ad");
	// cout << (string)n;

	// cout << (string)n["a"]["test3"]["test3"][0] << endl;

	return 0;
}