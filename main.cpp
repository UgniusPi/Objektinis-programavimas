#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;

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

int main() {
    vector<Studentas> studentai;
    int pasirink;
    
    ivestis(studentai, pasirink);
    skaicGal(studentai, pasirink);
    isvestis(studentai, pasirink);
    
    return 0;
}

void ivestis(vector<Studentas> &studentai, int &pasirink) {
    int studSk;
    
    cout << "Iveskite studentu skaiciu: ";
    cin >> studSk;
    studentai.reserve(studSk);
    cout << '\n';
    
    for (int i=0; i<studSk; i++) {
        Studentas naujasStud;
        string tempStr;
        int tempInt;
        int tarpSk;
        
        cout << "Iveskite studento varda: ";
        cin >> tempStr;
        naujasStud.vard = tempStr;
        
        cout << "Iveskite studento pavarde: ";
        cin >> tempStr;
        naujasStud.pav = tempStr;
        
        cout << "Iveskite tarpiniu pazymiu skaiciu: ";
        cin >> tarpSk;
        naujasStud.tarp.reserve(tarpSk);
        for (int j=0; j<tarpSk; j++) {
            cout << "Iveskite " << j + 1 << " pazymi is " << tarpSk << ": ";
            cin >> tempInt;
            naujasStud.tarp.push_back(tempInt);
        }
        
        cout << "Iveskite egzamino rezultata: ";
        cin >> tempInt;
        naujasStud.egz = tempInt;
        cout << '\n';
        
        studentai.push_back(naujasStud);
    } 
    
    cout << "Pasirinkite galutinio rezultato skaiciavimo buda.\n";
    cout << "Jeigu norite skaiciuoti naudojant vidurki, iveskite 1.\n";
    cout << "Jeigu norite skaiciuoti naudojant mediana, iveskite 2.\n";
    cout << "Pasirinkimas: ";
    cin >> pasirink;
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
