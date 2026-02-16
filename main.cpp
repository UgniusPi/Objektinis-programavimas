#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
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

void ivestis(vector<Studentas> &studentai, int &pasirink);
void isvestis(vector<Studentas> &studentai, int pasirink);
void skaicGal(vector<Studentas> &studentai, int pasirink);
bool isInt(string inp);
int validInput(string prompt);
int validRange(int from, int to, string prompt);

int main() {
    vector<Studentas> studentai;
    int pasirink;
    
    ivestis(studentai, pasirink);
    skaicGal(studentai, pasirink);
    isvestis(studentai, pasirink);
    
    return 0;
}

void ivestis(vector<Studentas> &studentai, int &pasirink) {
    string inp;
    int studSk;
    
    studSk = validInput("Iveskite studentu skaiciu: ");
    studentai.reserve(studSk);
    cout << '\n';
    
    for (int i=0; i<studSk; i++) {
        Studentas naujasStud;
        int tarpSk;
        
        cout << "Iveskite studento varda: ";
        getline(cin, inp);
        naujasStud.vard = inp;
        
        cout << "Iveskite studento pavarde: ";
        getline(cin, inp);
        naujasStud.pav = inp;
        
        tarpSk = validInput("Iveskite tarpiniu pazymiu skaiciu: ");
        naujasStud.tarp.reserve(tarpSk);
        for (int j=0; j<tarpSk; j++) {
            int tarpPaz = validRange(0, 10, "Iveskite " + to_string(j + 1) + " pazymi is " + to_string(tarpSk) + ": ");
            naujasStud.tarp.push_back(tarpPaz);
        }
        
        naujasStud.egz = validInput("Iveskite egzamino rezultata: ");
        cout << '\n';
        
        studentai.push_back(naujasStud);
    } 
    
    cout << "Pasirinkite galutinio rezultato skaiciavimo buda.\n";
    cout << "Jeigu norite skaiciuoti naudojant vidurki, iveskite 1.\n";
    cout << "Jeigu norite skaiciuoti naudojant mediana, iveskite 2.\n";
    pasirink = validInput("Pasirinkimas: ");
    cout << '\n';
}

void isvestis(vector<Studentas> &studentai, int pasirink) {
    string galTekstas;
    if (pasirink == 1) {
        galTekstas = "Galutinis (Vid.)";
    }
    else {
        galTekstas = "Galutinis (Med.)";
    }
    cout << left << setw(20) << "Pavarde" << left << setw(15) << "Vardas" << left << setw(20) << galTekstas << '\n';
    cout << "-------------------------------------------------------" << '\n';
    for (auto stud : studentai) {
        cout << left << setw(20) << stud.pav << left << setw(15) << stud.vard << left << setw(20) << fixed << setprecision(2) << stud.gal << '\n';
    }
}

void skaicGal(vector<Studentas> &studentai, int pasirink) {
    if (pasirink == 1) {
        for (auto &stud : studentai) {
            int suma = 0;
            double vid = 0;
            
            for (int paz : stud.tarp) {
                suma += paz;
            }
            
            vid = (double)suma / stud.tarp.size();
            stud.gal = vid * 0.4 + (double)stud.egz * 0.6;   
        }
    }
    else if (pasirink == 2) {
        for (auto &stud : studentai) {
            double med;
            
            sort(stud.tarp.begin(),stud.tarp.end());
            
            int medIndex;
            medIndex = stud.tarp.size() / 2;
            if (stud.tarp.size() % 2 == 1) {
                med = stud.tarp[medIndex];
            }
            else {
                med = (double)(stud.tarp[medIndex] + stud.tarp[medIndex - 1]) / 2;
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
    
    return inp.length() != 0;
}

int validInput(string prompt) {
    string inp;
    
    cout << prompt;
    getline(cin, inp);
    while (!isInt(inp)) {
        cout << "Ivesti duomenys turi buti naturalusis skaicius! Bandykite is naujo.\n" << prompt;
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
