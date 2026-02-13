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

struct Studentas {
  string vard;
  string pav;
  vector<int> tarp;
  int egz;
  double gal;
};

int main() {
  vector<Studentas> studentai;
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
    
    int suma = 0;
    double vid = 0;
    for (int j=0; j<tarpSk; j++) {
        cout << "Iveskite " << j + 1 << " pazymi is " << tarpSk << ": ";
        cin >> tempInt;
        naujasStud.tarp.push_back(tempInt);
        suma += tempInt;
    }
    cout << "Iveskite egzamino rezultata: ";
    cin >> tempInt;
    naujasStud.egz = tempInt;
    vid = (double)suma / naujasStud.tarp.size();
    naujasStud.gal = vid * 0.4 + (double)naujasStud.egz * 0.6;
    studentai.push_back(naujasStud);
  }
  
  cout << left << setw(20) << "Pavarde" << left << setw(15) << "Vardas" << left << setw(10) << "Galutinis (Vid.)" << '\n';
  cout << "----------------------------------------------------------------------------" << '\n';
  for (auto stud : studentai) {
    cout << left << setw(20) << stud.pav << left << setw(15) << stud.vard << left << setw(10) << setprecision(2) << stud.gal << '\n';
  }
    
  return 0;
}
