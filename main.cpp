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

void ivestis(vector<Studentas> &studentai, int &pasirink);
void isvestis(vector<Studentas> &studentai, int pasirink);
void skaicGal(vector<Studentas> &studentai, int pasirink);
bool isInt(string inp);
int validInput(string prompt);
int validRange(int from, int to, string prompt);
string validLength(int maxLength, string prompt);
bool validBool(string prompt);
string strLower(string &word);

int main() {
    srand(time(0));
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
    bool rndPaz;
    
    rndPaz = validBool("Ar norite patys ivesti studentu pazymius? Iveskite 'taip' arba 'ne': ");
    studSk = validInput("Iveskite studentu skaiciu: ");
    studentai.reserve(studSk);
    cout << '\n';
    
    for (int i=0; i<studSk; i++) {
        Studentas naujasStud;
        int tarpSk;
        
        naujasStud.vard = validLength(15, "Iveskite studento varda (iki 15 raidziu): ");
        naujasStud.pav = validLength(20, "Iveskite studento pavarde (iki 20 raidziu): ");
        
        if (rndPaz) {
            tarpSk = rand() % 16;
            cout << "Automatiskai sugeneruoti tarpiniai pazymiai ir egzamino rezultatas:\n";
            naujasStud.tarp.reserve(tarpSk);
            for (int j=0; j<tarpSk; j++) {
                int tarpPaz = rand() % 11;
                naujasStud.tarp.push_back(tarpPaz);
                cout << right << setw(3) << tarpPaz;
            }
            
            naujasStud.egz = rand() % 11;
            cout << '\n' << right << setw(3) << naujasStud.egz << "\n\n";
        }
        else {
            tarpSk = validInput("Iveskite tarpiniu pazymiu skaiciu: ");
            naujasStud.tarp.reserve(tarpSk);
            for (int j=0; j<tarpSk; j++) {
                int tarpPaz = validRange(0, 10, "Iveskite " + to_string(j + 1) + " pazymi is " + to_string(tarpSk) + ": ");
                naujasStud.tarp.push_back(tarpPaz);
            }
            
            naujasStud.egz = validInput("Iveskite egzamino rezultata: ");
            cout << '\n';
        }
        
        studentai.push_back(naujasStud);
    } 
    
    cout << "Pasirinkite galutinio rezultato skaiciavimo buda.\n";
    cout << "Jeigu norite skaiciuoti naudojant vidurki, iveskite 1.\n";
    cout << "Jeigu norite skaiciuoti naudojant mediana, iveskite 2.\n";
    pasirink = validRange(1, 2, "Pasirinkimas: ");
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
    cout << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << '\n';
    cout << "---------------------------------------------------------" << '\n';
    for (auto stud : studentai) {
        cout << left << setw(21) << stud.pav << left << setw(16) << stud.vard << left << setw(20) << fixed << setprecision(2) << stud.gal << '\n';
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
                    med = stud.tarp[medIndex];
                }
                else {
                    med = (double)(stud.tarp[medIndex] + stud.tarp[medIndex - 1]) / 2;
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
    
    return inp.length() != 0;
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

bool validBool(string prompt) {
    string inp;
    
    cout << prompt;
    getline(cin, inp);
    
    while (strLower(inp) != "taip" && strLower(inp) != "ne") {
        cout << "Ivesti duomenys nera nei 'taip', nei 'ne'. Bandykite is naujo.\n";
        cout << prompt;
        getline(cin, inp);
    }
    
    return strLower(inp) == "ne";
}

string strLower(string &word) {
    for (char &c : word) {
        c = tolower(c);
    }

    return word;
}
