/**
 * Programmeerimine (RAM0620)
 * TalTech Tartu kolledž
 * Kodutöö 03: Kasutajasüsteem
 * Alver Lillepea
 * 2022-04-03
*/

#include <iostream>			// std::cout, std::cin, std::ostream, std::istream
#include <fstream>			// std::ifstream, std::ofstream
#include <vector>			// std::vector
#include "lib/sisend.hpp"	// loe_taisarv_vahemikus, loe_rida
#include <algorithm>		// size_t
#include <string>
#include <iomanip>
#include <sstream>
#include "lib/sha512/sha512.hh"		// sw::sha512::calculate




// TODO: Kasutaja klass
class  Kasutaja{
	friend std::ostream& operator<<(std::ostream& valjund, const Kasutaja& Kasutaja);
public:
	Kasutaja(std::string ID, std::string nimi, std::string parool, std::string eesnimi, std::string perekonnanimi);
	friend class Kasutajasusteem;
private:
	std::string ID;
	std::string nimi;
	std::string parool;
	std::string eesnimi;
	std::string perekonnanimi;
};

Kasutaja::Kasutaja(std::string ID, std::string nimi, std::string parool, std::string eesnimi, std::string perekonnanimi){
	this->ID = ID;
	this->nimi = nimi;
	this->parool = parool;
	this->eesnimi = eesnimi;
	this->perekonnanimi = perekonnanimi;
}
std::ostream& operator<<(std::ostream& valjund, const Kasutaja& Kasutaja){
	valjund << Kasutaja.ID<< " | " << Kasutaja.nimi << " | " << Kasutaja.eesnimi<< " | " << Kasutaja.perekonnanimi << std::endl;

	return valjund;
}

class Kasutajasusteem {

public:
	Kasutajasusteem(const std::string& failinimi);
	void maaraFail(const std::string& failinimi);
	void kaivita();
private:
	int onSisseLogitudKonto;
	std::string failinimi;
	std::vector<Kasutaja> Kasutajad;

	// TODO: Sisselogitud kasutaja talletamine
	bool onSisseLogitud;

	void loeKasutajad();
	void kirjutaKasutajad();

	void kuvaPealkiri(const std::string& pealkiri);
	void kuvaMenuu();
	void kuvaLopetus();

	int loeKasklus();
	bool taidaKasklus(int kasklus);
	void ootaKasutajat();

	void registreeri();
	void logiSisse();
	void logiValja();
	void kuvaProfiil();
	void muudaParool();
	void kuvaNimekiri();

};


Kasutajasusteem::Kasutajasusteem(const std::string& failinimi) {
	maaraFail(failinimi);
	onSisseLogitud = false;
}

void Kasutajasusteem::maaraFail(const std::string& failinimi) {
	this->failinimi = failinimi;
	loeKasutajad();
}

void Kasutajasusteem::kaivita() {
	bool jatka;
	do {
		jatka = true;
		kuvaPealkiri("MENUU");
		kuvaMenuu();
		std::cout << std::endl;
		int kasklus = loeKasklus();
		std::cout << std::endl;
		jatka = taidaKasklus(kasklus);
		std::cout << std::endl;
	} while (jatka);
}


void Kasutajasusteem::loeKasutajad() {
	const std::string WHITESPACE = " \n\r\t\f\v";

	std::string s6na;
	// Avame sisendfaili
	std::ifstream sisend(failinimi);
	// Kui faili avamine ebaõnnestus, väljastame veateate ja lõpetame
	// funktsiooni töö
	if (!sisend.is_open()) {
		std::cout << "Viga! Faili '" << failinimi << "' ei saanud avada." << std::endl;
	}
    int ridaloendur = 0;
    while(getline(sisend, s6na)){
        ridaloendur++;
    }
	sisend.clear();
	sisend.seekg(0);

	int read = 0;
	std::string id;
	std::string kasutajanimi;
	std::string parool;
	std::string eesnimi;
	std::string perekonnanimi;

	while(read < ridaloendur){

		std::getline(sisend, id, '|');
		id.pop_back();

		std::getline(sisend, kasutajanimi, '|');
		kasutajanimi.pop_back();
		kasutajanimi.erase(kasutajanimi.begin());

		std::getline(sisend, parool, '|');
		parool.pop_back();
		parool.erase(parool.begin());



		std::getline(sisend, eesnimi, '|');
		eesnimi.pop_back();
		eesnimi.erase(eesnimi.begin());
		read++;


		std::getline(sisend, perekonnanimi);{
			//https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/#:~:text=We%20can%20use%20a%20combination,functions%20to%20trim%20the%20string.
			if(perekonnanimi!=""){
				size_t start = perekonnanimi.find_first_not_of(WHITESPACE);
    			perekonnanimi = (start == std::string::npos) ? "" : perekonnanimi.substr(start);

				size_t end = perekonnanimi.find_last_not_of(WHITESPACE);
    			perekonnanimi = (end == std::string::npos) ? "" : perekonnanimi.substr(0, end + 1);

			}
		}

		Kasutajad.push_back(Kasutaja(id, kasutajanimi, parool, eesnimi, perekonnanimi));

	}

}

void Kasutajasusteem::kirjutaKasutajad() {
	std::ofstream valjund(failinimi, std::ofstream::trunc);
	if (!valjund.is_open()) {
		std::cout << "Viga! Faili '" << failinimi << "' ei saanud avada." << std::endl;
	}
	for (unsigned int i = 0 ; i < Kasutajad.size(); i++){
		valjund << Kasutajad[i].ID<< " | " << Kasutajad[i].nimi<< " | " << Kasutajad[i].parool << " | " << Kasutajad[i].eesnimi<< " | " << Kasutajad[i].perekonnanimi << std::endl;
	};
	valjund.close();
}


void Kasutajasusteem::kuvaMenuu() {
	if (onSisseLogitud) {
		std::cout << "Tere, " <<Kasutajad[onSisseLogitudKonto].nimi<< std::endl << std::endl;

		// TODO: Viita tervituses kasutaja nimele
		std::cout << "1. Kuva profiil" << std::endl;
		std::cout << "2. Muuda parooli" << std::endl;
		std::cout << "0. Logi valja" << std::endl;
	} else {
		std::cout << "1. Logi sisse" << std::endl;
		std::cout << "2. Registreeri" << std::endl;
		std::cout << "3. Kasutajate nimekiri" << std::endl;
		std::cout << "0. Valju" << std::endl;
	}
}

void Kasutajasusteem::kuvaPealkiri(const std::string& pealkiri) {
	for (unsigned int i = 0; i < pealkiri.size(); i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
	std::cout << pealkiri << std::endl;
	for (unsigned int i = 0; i < pealkiri.size(); i++) {
		std::cout << "-";
	}
	std::cout << std::endl << std::endl;
}

void Kasutajasusteem::kuvaLopetus() {
	std::cout << "Taname, et kasutasite meie programmi!" << std::endl;
}

int Kasutajasusteem::loeKasklus() {
	unsigned int menuus_valikuid = onSisseLogitud ? 3 : 4;
	return loe_taisarv_vahemikus(0, menuus_valikuid - 1, "Sisesta valik menuus");
}

bool Kasutajasusteem::taidaKasklus(int kasklus) {
	if (onSisseLogitud) {
		switch (kasklus) {
			case 1:
				kuvaPealkiri("MINU PROFIIL");
				kuvaProfiil();
				std::cout << std::endl;
				ootaKasutajat();
				return true;
			case 2:
				kuvaPealkiri("PAROOLI VAHETAMINE");
				muudaParool();
				std::cout << std::endl;
				return true;
			case 0:
			default:
				kuvaPealkiri("VALJALOGIMINE");
				logiValja();
				std::cout << std::endl;
				return true;
		}
	} else {
		switch (kasklus) {
			case 1:
				kuvaPealkiri("SISSELOGIMINE");
				logiSisse();
				std::cout << std::endl;
				return true;
			case 2:
				kuvaPealkiri("REGISTREERIMINE");
				registreeri();
				std::cout << std::endl;
				return true;
			case 3:
				kuvaPealkiri("KASUTAJATE NIMEKIRI");
				kuvaNimekiri();
				std::cout << std::endl;
				ootaKasutajat();
				return true;
			case 0:
			default:
				kuvaPealkiri("PROGRAMMI SULGEMINE");
				kuvaLopetus();
				return false;
		}
	}
}

void Kasutajasusteem::ootaKasutajat() {
	loe_rida("Vajuta ENTERit, et jatkata");
}


void Kasutajasusteem::registreeri() {
	bool kasutaja_sobib = false;
	bool parool_sobib = false;
	bool nimi_sobib = false;
	int id = 0;
	for(unsigned int i = 1; i < Kasutajad.size(); i++){
		int iD = std::stoi(Kasutajad[i].ID);
		if(iD >= id){
			id = iD+1;
		}
	}
	std::string kasutajanimi;
	std::string parool;
	std::string eesnimi = "";
	std::string perekonnanimi = "";
	while(!kasutaja_sobib){
		std::cout << " Sisestage kasutaja nimi " << std::endl;
		getline(std::cin, kasutajanimi);
		for (unsigned int i = 0 ; i < Kasutajad.size(); i++){
			if (Kasutajad[i].nimi == kasutajanimi){
				kasutaja_sobib = false;
				std::cout<<"kasutaja on juba olemas" << std::endl;

				break;
			}
			else{
				kasutaja_sobib = true;
			}
		}
	}
	while(!parool_sobib){
		std::cout << "Sisestage parool mis on vähemalt 5 elementi" << std::endl;
		getline(std::cin, parool);
			if (parool.size() >= 6){
				parool = sw::sha512::calculate(parool);
				parool_sobib = true;
				break;
			}
			else{
				std::cout<<"Parool on v2iksem kui 5 kirjamarki" << std::endl;
				parool_sobib = false;
		}
	}
	while(!nimi_sobib){
		std::cout << "Sisestage eesnimi "<< std::endl;
		getline(std::cin, eesnimi);
		std::cout << "Sisestage perekonnanimi " << std::endl;
		getline(std::cin, perekonnanimi);
		while(perekonnanimi == "" && eesnimi == ""){
			std::cout<<"vahemalt uks nimedest tuleb maarata"<<std::endl;
			std::cout << "Sisestage eesnimi "<< std::endl;
			getline(std::cin, eesnimi);
			std::cout << "Sisestage perekonnanimi " << std::endl;
			getline(std::cin, perekonnanimi);
		}
		nimi_sobib = true;
	}
	Kasutajad.push_back(Kasutaja(std::to_string(id), kasutajanimi, parool, eesnimi, perekonnanimi));
	kirjutaKasutajad();

}

void Kasutajasusteem::logiSisse() {
	std::string kasutaja_nimi;
	std::string parool;
	bool oige_nimi = false;
	bool oige_parool = false;
	std::cout << " Sisestage Kasutajanimi ja parool" << std::endl;
	std::cin >> kasutaja_nimi >> parool;
	for (unsigned int i = 0 ; i < Kasutajad.size(); i++){
		if (Kasutajad[i].nimi == kasutaja_nimi && Kasutajad[i].parool == sw::sha512::calculate(parool)){
			onSisseLogitud = true;
			onSisseLogitudKonto = i;
			oige_nimi = true;
			oige_parool = true;
		}
	}
	for (unsigned int i = 0 ; i < Kasutajad.size(); i++){
		if (Kasutajad[i].nimi == kasutaja_nimi && Kasutajad[i].parool != sw::sha512::calculate(parool)){
			oige_nimi = true;
			oige_parool = false;
		}
	}
	for (unsigned int i = 0 ; i < Kasutajad.size(); i++){
		if (Kasutajad[i].nimi != kasutaja_nimi && Kasutajad[i].parool == sw::sha512::calculate(parool)){
			oige_nimi = false;
			oige_parool = true;
		}
	}
	if (oige_nimi == false){
		std::cout<< " Sisestatud kasutaja nimi on vale "<< std::endl;
	}
	if (oige_parool == false){
		std::cout<< " Sisestatud parool on vale "<< std::endl;
	}
}

void Kasutajasusteem::logiValja() {
	std::cout << "Olete edukalt valja logitud!" << std::endl;
	onSisseLogitud = false;
	onSisseLogitudKonto = 0;
}

void Kasutajasusteem::kuvaProfiil() {
	std::cout << Kasutajad[onSisseLogitudKonto] << std::endl;
}

void Kasutajasusteem::muudaParool() {
	bool parool_sobib = false;
	std::string demp_parool;
	std::cout << "Sisestage oma praegune parool" << std::endl;
	std::cin >> demp_parool;
	while (Kasutajad[onSisseLogitudKonto].parool != sw::sha512::calculate(demp_parool)){
		std::cout << "Sisestasite vale parooli"<< std::endl << std::endl;
		std::cout << "Sisestage uuesti praegune parool" << std::endl;
		std::cin >> demp_parool;
	}
	demp_parool = "";
	std::string demp_parool_2;
	while(!parool_sobib){
		std::cout << "Sisestage oma uus parool, mis on vahemalt 6 tahemarki pikk" << std::endl;
		std::cin >> demp_parool;
		while(demp_parool.size()<6){
			std::cout << "Sisestage oma uus parool, mis on vahemalt 6 tahemarki pikk" << std::endl;
			std::cin >> demp_parool;
		}
		std::cout << "Korrake oma parool"<<std::endl;
		std::cin >> demp_parool_2;
		if (demp_parool == demp_parool_2){
			std::cout<<"Parool muudetud"<< std::endl;
			parool_sobib = true;
			Kasutajad[onSisseLogitudKonto].parool = sw::sha512::calculate(demp_parool);
			kirjutaKasutajad();
		}
	}
}

void Kasutajasusteem::kuvaNimekiri(){
	for (unsigned int i = 0 ; i < Kasutajad.size(); i++){
		std::cout << Kasutajad[i] << std::endl;
	}
}


int main() {

	Kasutajasusteem kasutajasusteem("data/kasutajad.txt");
	kasutajasusteem.kaivita();
	return 0;
}
