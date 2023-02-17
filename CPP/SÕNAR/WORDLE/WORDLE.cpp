#include <iostream>	 				// std::cout, std::cin
#include <fstream>					// std::ifstream
#include <limits>					// std::numeric_limits
#include <cstring>					// std::string
#include<cctype>


using namespace std;

void kirjuta_tulemus_faili(string mangja, string pakutud_sonad[6], string arvatav_s6na, int pakkumiste_arv, bool voideti){
	ofstream file;
	file.open("mangud.txt", std::ios_base::app);
	file << mangja;
	if(voideti){
		file << " voitis"<< endl;
	}
	else{
		file << " kautas "<< endl;
	}
	file << " arvatav s6na oli "<< arvatav_s6na<< endl<< " pakuti " << pakkumiste_arv << ". korda" << endl;
	for(int i=0; i <= pakkumiste_arv; i++){
		file << pakutud_sonad[i] << endl;
		}
}

void loe_andmebaas(const string& failinimi, string*& massiiv, unsigned int& kogus) {
	// Avame sisendfaili
	ifstream sisend(failinimi);
	// Kui faili avamine ebaõnnestus, väljastame veateate ja lõpetame
	// funktsiooni töö
	if (!sisend.is_open()) {
		cout << "Viga! Faili '" << failinimi << "' ei saanud avada." << endl;
		return;
	}
	// Loeme sisse arvude koguse
	sisend >> kogus;
	// Eraldame arvude massiivile mälu nii mitme arvu salvestamiseks
	massiiv = new string[kogus];
	// Loeme sisse nii mitu arvu ja salvestame need massiivi
	for (unsigned int koht = 0; koht < kogus; koht++) {
		// Loeme sisse järgmise arvu ja salvestame selle massiivi
		sisend >> massiiv[koht];
	}
}
int genereeri_juhuarv(int alumine, int ulemine) {
	// Funktsioon rand() genereerib juhuarvu vahemikus [0; RAND_MAX]
	// Jagamisel tekkiva jäägi leidmisel piirame selle vahemikku [0; jagaja - 1]
	// Jagaja peaks seega olema juhuarvude vahemiku suurus
	// Kui tulemusele juurde liita mingi arv, nihutab see tervet vahemikku
	return rand() % (ulemine - alumine + 1) + alumine;
}
string suurtahtedena(string sona){
	string str = sona;
	for(int i= 0; i<str.length(); i++){
		str[i] = toupper(str[i]);
	}
	return str;
}
string loe_sone(string kusimus = " Sisesta 5-tahelise sona :") {
	string sona;
	cout << kusimus;
	cin >> sona;
	return suurtahtedena(sona);
}
bool sisaldab(string* str, const int kogus, string otsitav) {
	// Vaatleme järjestikuselt massiivi iga elementi
	for (int koht = 0; koht < kogus; koht++) {
		// Kui massiivis vaadeldaval kohal asuva elemendi väärtus on võrdne
		// otsitava elemendi väärtusega, siis asub otsitav element massiivis
		// sellel kohal
		if (suurtahtedena(str[koht]) == otsitav){
			return true;
		}
	}
	cout << " Sona ei kuulu lubatud pakkumiste hulka "<< endl;
	// Kui massiivi ühegi elemendi väärtus polnud otsitava väärtusega võrdne,
	// siis ei leidu massiivis seda väärtust
	return false;
}
bool on_sobiv(string sona){
	if (sona.length() != 5){
		cout << " Ei sisestatud 5-tahelist s6na "<< endl;
		return false;
	}
	for(int i=0; i < sona.length(); i++){
		if ((sona[i]>=65 && sona[i]<=90)||
		(sona[i]>=97 && sona[i]<=122)){
			continue;
		}
		else{
			cout << " s6nas on sobimatuid marke "<< endl;
			return false;
		}
	}
	return true;
}
void valjasta_tabel(string tabel[6][5], string pakutud_sonad[6]){
	for (unsigned int rida = 0; rida < 6; rida++) {
		cout << (rida+1) << ". " << pakutud_sonad[rida] << endl;
    	for (unsigned int veerg = 0; veerg < 5; veerg++) {
        	cout <<" "<< tabel[rida][veerg];
    	}
    cout << endl;
	}
}
void leia_vordlus(string vastus, string pakkumine, string margid[6][5], int rida){
	string muutuv_vastus = vastus;
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			if(pakkumine[i]==muutuv_vastus[j]){
				if (margid[rida][i]=="+"){
					continue;
				}
				else if (i==j){
					margid[rida][i]="+";

				}
				else if(pakkumine[j]==muutuv_vastus[j]){
					margid[rida][j]="+";
				}
				else{
					margid[rida][i]="?";
				}
			}
		}
	}
}
void uus_tabel(string tabel[6][5], string pakutud_sonad[6]){
	for(int rida = 0; rida<6; rida++){
		pakutud_sonad[rida]=" ";
		for(int veerg =0; veerg <5 ; veerg++){
			tabel[rida][veerg]="_";
		}
	}
}
int soovib_uuesti(string pakutud_sonad[6], string &sona,string tabel[6][5], string& arvatav_s6na, string* lahendus_soned,const int kogus){
	int juhuslik_koht = genereeri_juhuarv(0, kogus);
	arvatav_s6na = suurtahtedena(lahendus_soned[juhuslik_koht]);

	int vastus;
	cout << "Kui soovite uuesti sisestage 1 kui ei soovi sisestage 0" << endl;
	cin >> vastus;
	if (vastus == 1){
		sona = loe_sone();
		uus_tabel(tabel, pakutud_sonad);
		return -1;
	}
	else{
		return 6;
	}
}
void mangutsukkel(string mangja, string *pakkumis_soned, string arvatav_s6na, int pakkumis_s6ne_kogus, string *lahendus_soned, int kogus){
	string sona = loe_sone();
	string pakutud_sonad[6]={" "," "," "," "," "," "};
	string tabel[6][5]= {
							{"_","_","_","_","_"},
							{"_","_","_","_","_"},
							{"_","_","_","_","_"},
							{"_","_","_","_","_"},
							{"_","_","_","_","_"},
							{"_","_","_","_","_"}
							};


	for (int rida = 0; rida <= 5; rida++){
		while(!on_sobiv(sona)&& !sisaldab(pakkumis_soned, pakkumis_s6ne_kogus, sona)){
			sona = loe_sone();
		}
		leia_vordlus(arvatav_s6na, sona, tabel, rida);
		pakutud_sonad[rida]= sona;
		valjasta_tabel(tabel, pakutud_sonad);
		if (arvatav_s6na == sona){
			cout << "Tubli too!!!" << endl;
			bool voideti = true;
			kirjuta_tulemus_faili( mangja, pakutud_sonad,  arvatav_s6na,rida , voideti);
			rida = soovib_uuesti(pakutud_sonad, sona, tabel, arvatav_s6na, lahendus_soned, kogus);
		}
		cout << endl;
		if (rida!=5){
			sona = loe_sone("");
			while(!on_sobiv(sona)&& !sisaldab(pakkumis_soned, pakkumis_s6ne_kogus, sona)){
				sona = loe_sone();
			}
		}
		cout << endl;
		if(rida==5){
			bool voideti = false;
			cout << " mang on labi! koik proovitud korrad on kasutatud "<< endl;
			kirjuta_tulemus_faili(mangja, pakutud_sonad,  arvatav_s6na, rida, voideti);
			rida = soovib_uuesti(pakutud_sonad, sona, tabel, arvatav_s6na, lahendus_soned, kogus);
		}
	}
}
int main() {
    srand(time(NULL));

	string mangja;
	cout << "Sisestage kes mangib: "<< endl;
	cin >> mangja;
	cout << endl;
    string lahendused = "lahendused.txt";
	string pakkumised = "pakkumised.txt";

	// Loeme failist sisse N arvu ja salvestame need dünaamilisse massiivi
	string* lahendus_soned = nullptr;
	unsigned int kogus = 0;

	string* pakkumis_soned = nullptr;
	unsigned int pakkumis_s6ne_kogus = 0;
	string pakutud_sonad[6]={" "," "," "," "," "," "};

	loe_andmebaas(lahendused, lahendus_soned, kogus);
	loe_andmebaas(pakkumised, pakkumis_soned, pakkumis_s6ne_kogus);

    int juhuslik_koht = genereeri_juhuarv(0, kogus);
    string arvatav_s6na = suurtahtedena(lahendus_soned[juhuslik_koht]);

	mangutsukkel(mangja, pakkumis_soned, arvatav_s6na, pakkumis_s6ne_kogus, lahendus_soned, kogus);
    delete[] lahendus_soned;
	delete[] pakkumis_soned;
    return 0;
}
