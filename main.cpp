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
	CIni c("config.ini");
	cout << (string)c;
	
	return 0;
}