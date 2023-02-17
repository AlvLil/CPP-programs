/**
 * Programmeerimine (RAM0620)
 * TalTech Tartu kolledž
 * Kodutöö 03: Kasutajasüsteem
 * Abifunktsioonid käsurealt sisendi lugemiseks
 * Ants-Oskar Mäesalu
 * 2022-04-03
*/

#ifndef _H_SISEND_
#define _H_SISEND_

#include <iostream>			// std::cout
#include <limits>			// std::numeric_limits
#include <string>			// std::string, std::to_string

// Funktsioon, mis esitab kasutajale küsimuse ja loeb käsurealt sisse ühe
// täisarvu
/**
 * Funktsioon, mis esitab kasutajale küsimuse ja loeb käsurealt sisse ühe
 * täisarvu
 * @param  kusimus Kasutajale esitatav küsimus
 * @return Käsurealt sisseloetud täisarv
 */
int loe_taisarv(const std::string& kusimus = "Sisesta taisarv") {
	// Deklareerime muutuja, millesse täisarv sisse lugeda
	int arv;
	// Küsime kasutajalt sisendit nii kaua, kuni sisestatakse täisarv
	bool vigane_sisend;
	do {
		// Eeldame, et kasutaja sisestab korrektse täisarvu
		vigane_sisend = false;
		// Esitame kasutajale küsimuse ja loeme sisse ühe täisarvu
		std::cout << kusimus << ": ";
		std::cin >> arv;
		// Kui sisend läks katki, siis ei sisestatud täisarvu
		// Sel juhul väljastame veateate, määrame sisendi vigaseks, et seda
		// uuesti küsitaks, ning puhastame sisendvoo veaseisundi
		if (std::cin.fail()) {
			std::cout << "Viga! Tegu pole taisarvuga." << std::endl;
			vigane_sisend = true;
			std::cin.clear();
		}
		// Tühjendame kõik, mis sisendvoogu jäänud
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (vigane_sisend);
	// Kui kasutaja sisestas nõuetekohase täisarvu, tagastame selle
	return arv;
}

/**
 * Funktsioon, mis esitab kasutajale küsimuse ja loeb käsurealt sisse ühe
 * täisarvu määratud vahemikus
 * @param  alumine Täisarvu lubatud minimaalne väärtus
 * @param  ulemine Täisarvu lubatud maksimaalne väärtus
 * @param  kusimus Kasutajale esitatav küsimus
 * @return Käsurealt sisseloetud täisarv
 */
int loe_taisarv_vahemikus(int alumine, int ulemine, std::string kusimus = "Sisesta taisarv") {
	// Lisame küsimuse lõppu vahemiku
	kusimus += " (vahemikus " + std::to_string(alumine) + " ... " + std::to_string(ulemine) + ")";
	// Deklareerime muutuja, millesse täisarv sisse lugeda
	int arv;
	// Küsime kasutajalt sisendit nii kaua, kuni sisestatakse täisarv sobivas
	// vahemikus
	bool vigane_sisend;
	do {
		// Eeldame, et kasutaja sisestab täisarvu korrektses vahemikus
		vigane_sisend = false;
		// Esitame kasutajale küsimuse ja loeme sisse ühe täisarvu
		arv = loe_taisarv(kusimus);
		// Kui sisend ei ole õiges vahemikus, väljastame veateate ning märgime
		// sisendi vigaseks, et seda uuesti küsitaks
		if (arv < alumine || arv > ulemine) {
			std::cout << "Viga! Arv ei ole vahemikus " << alumine << " ... " << ulemine << "." << std::endl;
			vigane_sisend = true;
		}
	} while (vigane_sisend);
	// kui kasutaja sisestas nõuetekohase täisarvu, tagastame selle
	return arv;
}

std::string loe_rida(const std::string& kusimus) {
	// Esitame kasutajale küsimuse
	std::cout << kusimus << ": ";
	// Loeme sisse terve rea
	std::string rida;
	std::getline(std::cin, rida);
	// Tagastame sisseloetud rea
	return rida;
}

#endif // _H_SISEND_
