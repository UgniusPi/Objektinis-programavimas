#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>

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

struct Studentas {
    string vard;
    string pav;
    vector<int> tarp;
    int egz;
    double gal;
};

void ivestis(vector<Studentas> &studentai, int &pasirink, bool &testi);
void isvestis(vector<Studentas> &studentai, int pasirink);
void skaicGal(vector<Studentas> &studentai, int pasirink);
bool isInt(string inp);
int validInput(string prompt);
int validRange(int from, int to, string prompt);
string validLength(int maxLength, string prompt);
string rndVardas(int from, int to);

int main() {
    srand(time(0));
    bool testi = true;
    
    while (true) {
        vector<Studentas> studentai;
        int pasirink;
        
        ivestis(studentai, pasirink, testi);
        if (!testi) break;
        
        skaicGal(studentai, pasirink);
        isvestis(studentai, pasirink);
    }
    
    cout << "Programa sekmingai uzsidare.";
    return 0;
}

void ivestis(vector<Studentas> &studentai, int &pasirink, bool &testi) {
    int studSk, eiga;
    bool rndPaz = false, rndVard = false;
    cout << "Pasirinkite programos eiga.\n";
    cout << "1. Visus studentu duomenis ivesti ranka.\n";
    cout << "2. Automatiskai generuoti studentu pazymius.\n";
    cout << "3. Automatiskai generuoti studentu vardus, pavardes ir pazymius.\n";
    cout << "4. Baigti darba.\n";
    eiga = validRange(1, 4, "Pasirinkimas: ");
    cout << '\n';
    
    if (eiga == 2) {
        rndPaz = true;    
    }
    else if (eiga == 3) {
        rndPaz = true;
        rndVard = true;
    }
    else if (eiga == 4) {
        testi = false;
        return;
    }
    
    studSk = validInput("Iveskite studentu skaiciu: ");
    cout << '\n';
    
    while (true) {
        for (int i=0; i<studSk; i++) {
            Studentas naujasStud;
            int tarpSk;
            
            if (rndVard) {
                naujasStud.vard = rndVardas(4, 10);
                naujasStud.pav = rndVardas(6, 12);
                cout << "Automatiskai sugeneruoto " << to_string(i + 1) << " is " << to_string(studSk) << " studento vardas ir pavarde:\n";
                cout << left << setw(16) << naujasStud.vard << left << setw(20) << naujasStud.pav << '\n';
            }
            else {
                naujasStud.vard = validLength(15, "Iveskite " + to_string(i + 1) + " is " + to_string(studSk) + " studento varda (iki 15 raidziu): ");
                naujasStud.pav = validLength(20, "Iveskite " + to_string(i + 1) + " is " + to_string(studSk) + " studento pavarde (iki 20 raidziu): ");
            }
    
            if (rndPaz) {
                tarpSk = rand() % 16;
                cout << "Automatiskai sugeneruoti tarpiniai pazymiai ir egzamino rezultatas:\n";
                for (int j=0; j<tarpSk; j++) {
                    int tarpPaz = rand() % 11;
                    naujasStud.tarp.push_back(tarpPaz);
                    cout << tarpPaz << " ";
                }
                
                naujasStud.egz = rand() % 11;
                cout << '\n' << naujasStud.egz << "\n\n";
            }
            else {
                tarpSk = validInput("Iveskite tarpiniu pazymiu skaiciu: ");
                for (int j=0; j<tarpSk; j++) {
                    int tarpPaz = validRange(0, 10, "Iveskite " + to_string(j + 1) + " pazymi is " + to_string(tarpSk) + ": ");
                    naujasStud.tarp.push_back(tarpPaz);
                }
                
                naujasStud.egz = validInput("Iveskite egzamino rezultata: ");
                cout << '\n';
            }
            
            studentai.push_back(naujasStud);
        } 
        
        studSk = validInput("Iveskite papildomu studentu skaiciu (jei nenorite prideti studentu, iveskite 0): ");
        cout << '\n';
        if (studSk == 0) break;
    }
    
    cout << "Pasirinkite galutinio rezultato skaiciavimo buda.\n";
    cout << "1. Naudojant vidurki.\n";
    cout << "2. Naudojant mediana.\n";
    pasirink = validRange(1, 2, "Pasirinkimas: ");
    cout << "\n\n";
}

void isvestis(vector<Studentas> &studentai, int pasirink) {
    string galTekstas;
    
    if (pasirink == 1) {
        galTekstas = "Galutinis (Vid.)";
    }
    else {
        galTekstas = "Galutinis (Med.)";
    }
    
    cout << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << '\n';
    cout << "---------------------------------------------------------" << '\n';
    
    for (auto stud : studentai) {
        cout << left << setw(21) << stud.pav << left << setw(16) << stud.vard << left << setw(20) << fixed << setprecision(2) << stud.gal << '\n';
    
    }
    cout << "\n\n";
}

void skaicGal(vector<Studentas> &studentai, int pasirink) {
    if (pasirink == 1) {
        for (auto &stud : studentai) {
            int suma = 0;
            double vid = 0;
            
            for (int paz : stud.tarp) {
                suma += paz;
            }
            
            if (stud.tarp.size() != 0) {
                vid = (double)suma / stud.tarp.size();   
            }
            stud.gal = vid * 0.4 + (double)stud.egz * 0.6;   
        }
    }
    else if (pasirink == 2) {
        for (auto &stud : studentai) {
            double med = 0;
            
            if (stud.tarp.size() != 0) {
                sort(stud.tarp.begin(),stud.tarp.end());
                
                int medIndex;
                medIndex = stud.tarp.size() / 2;
                if (stud.tarp.size() % 2 == 1) {
                    med = stud.tarp.at(medIndex);
                }
                else {
                    med = (double)(stud.tarp.at(medIndex) + stud.tarp.at(medIndex - 1)) / 2;
                }
            }
            
            stud.gal = med * 0.4 + (double)stud.egz * 0.6;   
        }   
    }
}

bool isInt(string inp) {
    for (int i=0; i<inp.length(); i++) {
        if (!isdigit(inp[i])) {
            return false;   
        }
    }
    
    return inp.length() != 0 && inp.length() <= 4;
}

int validInput(string prompt) {
    string inp;
    
    cout << prompt;
    getline(cin, inp);
    while (!isInt(inp)) {
        cout << "Ivesti duomenys turi buti sveikasis neneigiamas skaicius! Bandykite is naujo.\n" << prompt;
        getline(cin, inp);
    }
    
    return stoi(inp);
}

int validRange(int from, int to, string prompt) {
    int inp = validInput(prompt);
    while (inp < from || inp > to) {
        cout << "Ivestas skaicius turi buti nuo " << from << " iki " << to << "! Bandykite is naujo.\n";
        inp = validInput(prompt);
    }
    
    return inp;
}

string validLength(int maxLength, string prompt) {
    string inp;
    
    cout << prompt;
    getline(cin, inp);
    while (inp.length() > maxLength) {
        cout << "Ivestas tekstas virsija " + to_string(maxLength) + " raidziu limita! Bandykite is naujo.\n";
        cout << prompt;
        getline(cin, inp);    
    }
    
    if (inp.length() == 0) {
        inp = "Nenurodyta";    
    }
    
    return inp;
}

string rndVardas(int from, int to) {
    string vard;
    int raidSk = rand() % (to - from + 1) + from;

    vard += (char)(rand() % 26 + 65);
    for (int i=1; i<raidSk; i++) {
        vard += (char)(rand() % 26 + 97);
    }
    
    return vard;
}
