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
	// struct stat buff;
	
	// while((cin.get() != 'x')) {
		// if(-1 != stat("config.ini", &buff)) {
			// static char s[30];
			// struct tm *time_struct;
			// time_t cal_time = buff.st_mtime;
			
			// time_struct = localtime(&cal_time);
			// strftime(s, sizeof s, "%H:%M\n", time_struct);
			// cout << s;
		// }
	// }



	CIni c("config.ini");
	cout << c["sekcja1"]["sekcja4"];
	return 0;
}