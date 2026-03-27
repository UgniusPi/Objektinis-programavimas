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

    while (true) {
        vector<Studentas> studentai, vargsiukai, galvociai;
        Nustatymai nustatymai;
        bool testi, klaida;
        
        klauskEigos(testi, nustatymai);
        if (!testi) break;

        if (nustatymai.ivestSaltinis == 1) {
            ivestEkr(studentai, nustatymai.rndPaz, nustatymai.rndVard);
        }
        else {
            string failoKelias = klauskFailo(klaida);
            if (klaida) return 1;

            cout << "Skaitomas failas...\n";
            ivestIsFailo(studentai, failoKelias, klaida);
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

        skirstyk(studentai, vargsiukai, galvociai);

        if (nustatymai.isvestVieta == 1) {
            isvestEkr(studentai, nustatymai.pasirink);
        }
        else {
            cout << "Rezultatas rasomas i failus...\n";
            isvestIFaila(vargsiukai, nustatymai.pasirink, "vargsiukai.txt");
            isvestIFaila(galvociai, nustatymai.pasirink, "galvociai.txt");
            cout << "\n\n";
        }
    }
    
    cout << "Programa sekmingai uzsidare.";
    return 0;
}

