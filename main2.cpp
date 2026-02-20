#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using std::string;
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
using std::sort;

struct Studentas {
    string vard;
    string pav;
    int* tarp;
    int tarpSk;
    int egz;
    double gal;
};

void ivestis(Studentas* &studentai, int &studSk, int &pasirink, bool &testi);
void isvestis(Studentas* studentai, int studSk, int pasirink);
void skaicGal(Studentas* studentai, int studSk, int pasirink);
bool isInt(string inp);
int validInput(string prompt);
int validRange(int from, int to, string prompt);
string validLength(int maxLength, string prompt);
string rndVardas(int from, int to);
void istrint(Studentas* studentai, int studSk);

int main() {
    srand(time(0));
    bool testi = true;
    
    while (true) {
        Studentas* studentai = nullptr;
        int studSk = 0, pasirink;
        
        ivestis(studentai, studSk, pasirink, testi);
        if (!testi) break;
        
        skaicGal(studentai, studSk, pasirink);
        isvestis(studentai, studSk, pasirink);
        istrint(studentai, studSk);
    }
    
    cout << "Programa sekmingai uzsidare.";
    return 0;
}

void ivestis(Studentas* &studentai, int &studSk, int &pasirink, bool &testi) {
    int tempStudSk, eiga;
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
    
    tempStudSk = validInput("Iveskite studentu skaiciu: ");
    cout << '\n';
    
    while (true) {
        Studentas* tempStudentai = new Studentas[studSk + tempStudSk];
        for (int i=0; i<studSk; i++) {
            tempStudentai[i] = studentai[i];
            tempStudentai[i].tarp = new int[studentai[i].tarpSk];
            for (int j=0; j<studentai[i].tarpSk; j++) {
                tempStudentai[i].tarp[j] = studentai[i].tarp[j];
            }
        }
        istrint(studentai, studSk); 
        
        for (int i=studSk; i<studSk+tempStudSk; i++) {
            Studentas naujasStud;
            int tarpSk;
            
            if (rndVard) {
                naujasStud.vard = rndVardas(4, 10);
                naujasStud.pav = rndVardas(6, 12);
                cout << "Automatiskai sugeneruoto " << to_string(i + 1 - studSk) << " is " << to_string(tempStudSk) << " studento vardas ir pavarde:\n";
                cout << left << setw(16) << naujasStud.vard << left << setw(20) << naujasStud.pav << '\n';
            }
            else {
                naujasStud.vard = validLength(15, "Iveskite " + to_string(i + 1 - studSk) + " is " + to_string(tempStudSk) + " studento varda (iki 15 raidziu): ");
                naujasStud.pav = validLength(20, "Iveskite " + to_string(i + 1 - studSk) + " is " + to_string(tempStudSk) + " studento pavarde (iki 20 raidziu): ");
            }
    
            if (rndPaz) {
                tarpSk = rand() % 16;
                naujasStud.tarp = new int[tarpSk];
                cout << "Automatiskai sugeneruoti tarpiniai pazymiai ir egzamino rezultatas:\n";
                for (int j=0; j<tarpSk; j++) {
                    int tarpPaz = rand() % 11;
                    naujasStud.tarp[j] = tarpPaz;
                    cout << tarpPaz << " ";
                }
                
                naujasStud.egz = rand() % 11;
                cout << '\n' << naujasStud.egz << "\n\n";
            }
            else {
                tarpSk = validInput("Iveskite tarpiniu pazymiu skaiciu: ");
                naujasStud.tarp = new int[tarpSk];
                for (int j=0; j<tarpSk; j++) {
                    int tarpPaz = validRange(0, 10, "Iveskite " + to_string(j + 1) + " pazymi is " + to_string(tarpSk) + ": ");
                    naujasStud.tarp[j] = tarpPaz;
                }
                
                naujasStud.egz = validInput("Iveskite egzamino rezultata: ");
                cout << '\n';
            }
            naujasStud.tarpSk = tarpSk;
            
            tempStudentai[i] = naujasStud;
        } 
        studSk += tempStudSk;
        studentai = tempStudentai;
        
        tempStudSk = validInput("Iveskite papildomu studentu skaiciu (jei nenorite prideti studentu, iveskite 0): ");
        cout << '\n';
        if (tempStudSk == 0) break;
    }
    
    cout << "Pasirinkite galutinio rezultato skaiciavimo buda.\n";
    cout << "1. Naudojant vidurki.\n";
    cout << "2. Naudojant mediana.\n";
    pasirink = validRange(1, 2, "Pasirinkimas: ");
    cout << "\n\n";
}

void isvestis(Studentas* studentai, int studSk, int pasirink) {
    string galTekstas;
    
    if (pasirink == 1) {
        galTekstas = "Galutinis (Vid.)";
    }
    else {
        galTekstas = "Galutinis (Med.)";
    }
    
    cout << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << '\n';
    cout << "---------------------------------------------------------" << '\n';
    
    for (int i=0; i<studSk; i++) {
        cout << left << setw(21) << studentai[i].pav << left << setw(16) << studentai[i].vard << left << setw(20) << fixed << setprecision(2) << studentai[i].gal << '\n';
    }
    cout << "\n\n";
}

void skaicGal(Studentas* studentai, int studSk, int pasirink) {
    if (pasirink == 1) {
        for (int i=0; i<studSk; i++) {
            int suma = 0;
            double vid = 0;
            
            for (int j=0; j<studentai[i].tarpSk; j++) {
                suma += studentai[i].tarp[j];
            }
            
            if (studentai[i].tarpSk != 0) {
                vid = (double)suma / studentai[i].tarpSk;   
            }
            studentai[i].gal = vid * 0.4 + (double)studentai[i].egz * 0.6;   
        }
    }
    else if (pasirink == 2) {
        for (int i=0; i<studSk; i++) {
            double med = 0;
            
            if (studentai[i].tarpSk != 0) {
                sort(studentai[i].tarp, studentai[i].tarp + studentai[i].tarpSk);
                
                int medIndex;
                medIndex = studentai[i].tarpSk / 2;
                if (studentai[i].tarpSk % 2 == 1) {
                    med = studentai[i].tarp[medIndex];
                }
                else {
                    med = (double)(studentai[i].tarp[medIndex] + studentai[i].tarp[medIndex - 1]) / 2;
                }
            }
            
            studentai[i].gal = med * 0.4 + (double)studentai[i].egz * 0.6;   
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

void istrint(Studentas* studentai, int studSk) {
    for (int i=0; i<studSk; i++) {
        delete[] studentai[i].tarp;    
    }
    delete[] studentai;
}
