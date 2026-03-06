#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;
using std::stoi;
using std::getline;
using std::to_string;
using std::ifstream;
using std::ofstream;
using std::stringstream;

#include "funkcijos.h"

int main() {
    cout << "3\n";
    srand(time(0));
    
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
            string failoPav = klauskFailo();

            cout << "Skaitomas failas...\n";
            ivestIsFailo(studentai, failoPav, klaida);
            if (klaida) continue;
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
        }
    }
    
    cout << "Programa sekmingai uzsidare.";
    return 0;
}

