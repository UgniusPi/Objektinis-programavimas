#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "funkcijos.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;

int main() {
    srand(time(0));

    kurkFaila(100, 12);
    skirstyk("stud100.txt");

    while (true) {
        vector<Studentas> studentai;
        Nustatymai nustatymai;
        bool testi, klaida;
        
        klauskEigos(testi, nustatymai);
        if (!testi) break;

        if (nustatymai.ivestSaltinis == 1) {
            ivestEkr(studentai, nustatymai.rndPaz, nustatymai.rndVard);
        }
        else {
            string failoPav = klauskFailo(klaida);
            if (klaida) return 1;

            cout << "Skaitomas failas...\n";
            ivestIsFailo(studentai, failoPav, klaida);
            if (klaida) return 1;
        }
        
        if (nustatymai.isvestVieta == 2) {
            cout << "Skaiciuojami studentu galutiniai balai...\n";
        }
        skaicGal(studentai, nustatymai.pasirink);

        if (nustatymai.isvestVieta == 2) {
            cout << "Rusiuojami studentai...\n";
        }
        rusiuok(studentai, nustatymai.rusBudas);

        if (nustatymai.isvestVieta == 1) {
            isvestEkr(studentai, nustatymai.pasirink);
        }
        else {
            cout << "Rezultatas rasomas i faila...\n";
            isvestIFaila(studentai, nustatymai.pasirink);
            cout << "\n\n";
        }
    }
    
    cout << "Programa sekmingai uzsidare.";
    return 0;
}

