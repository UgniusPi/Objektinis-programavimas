#include <iostream>
#include <vector>
#include <iomanip>
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

void ivestis(vector<Studentas> &studentai);
void isvestis(vector<Studentas> &studentai);
void skaicGal(vector<Studentas> &studentai);

int main() {
    vector<Studentas> studentai;
    
    ivestis(studentai);
    skaicGal(studentai);
    isvestis(studentai);
    
    return 0;
}

void ivestis(vector<Studentas> &studentai) {
    int studSk;
    
    cout << "Iveskite studentu skaiciu: ";
    cin >> studSk;
    
    studentai.reserve(studSk);
    
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
        
        studentai.push_back(naujasStud);
    } 
}

void isvestis(vector<Studentas> &studentai) {
    cout << left << setw(20) << "Pavarde" << left << setw(15) << "Vardas" << left << setw(20) << "Galutinis (Vid.)" << '\n';
    cout << "-------------------------------------------------------" << '\n';
    for (auto stud : studentai) {
        cout << left << setw(20) << stud.pav << left << setw(15) << stud.vard << left << setw(20) << fixed << setprecision(2) << stud.gal << '\n';
    }
}

void skaicGal(vector<Studentas> &studentai) {
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
