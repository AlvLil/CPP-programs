#include <iostream> 				// std::cout
#include <iomanip>					// std::setw, std::setfill
#include <limits>					// std::numeric_limits
#include <string>					// std::string, std::to_string

using namespace std;

float positiivne_arv(string kusimus = "Sisesta positiivne reaalarv") {
	// Deklareerime muutuja, millesse täisarv sisse lugeda
	float arv;
	// Küsime kasutajalt sisendit nii kaua, kuni sisestatakse täisarv
	bool vigane_sisend;
	do {
		// Eeldame, et kasutaja sisestab korrektse täisarvu
		vigane_sisend = false;
		// Esitame kasutajale küsimuse ja loeme sisse ühe täisarvu
		cout << kusimus << ": ";
		cin >> arv;
		// Kui sisend läks katki, siis ei sisestatud täisarvu
		// Sel juhul väljastame veateate, määrame sisendi vigaseks, et seda
		// uuesti küsitaks, ning puhastame sisendvoo veaseisundi
		if (cin.fail()) {
			cout << "Viga! Tegu pole positiivse arvuga." << endl;
			vigane_sisend = true;
			cin.clear();
		}
        else if(arv<0){
            cout << "Viga! Tegu pole positiivse arvuga." << endl;
			vigane_sisend = true;
			cin.clear();
        }
		// Tühjendame kõik, mis sisendvoogu jäänud
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (vigane_sisend);
	// Kui kasutaja sisestas nõuetekohase täisarvu, tagastame selle
	return arv;
}



int main() {
    bool raha_liikumine = 0;
    int kask = 0;
    int i = 0;
   float raha_kontol;
   raha_kontol = positiivne_arv("Sisesta rahasumma kontol ");

while (i <= 2){
    cout << "1. raha sisse"<< endl;
    cout << "2. raha valja"<< endl;
    cout << "0. valju"<< endl;
    kask = positiivne_arv("vali [0-2]");
    while ( kask < 0  || kask > 2){
        kask = positiivne_arv("vali [0-2]");
    }

   if (kask == 1){
       cout << "raha sisse "<< endl;
       raha_kontol += positiivne_arv();
       i = 1;
   }
   else if (kask == 2){
       cout <<" raha valja "<< endl;
       float valja_votta = positiivne_arv();
       // raha_kontol -= positiivne_arv();
       if (raha_kontol < valja_votta){
       cout<< " teil ei ole nii palju raha: "<<endl;
       }
       i = 1;
}
   else if (kask == 0){
       cout << " aitah! "<< endl;
       break;
   }
   else{
       cout << " vastus ei sobi "<< endl;
   }
}


    return 0;
}
