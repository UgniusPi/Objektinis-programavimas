#include <iostream>
#include <vector>
using std::string;
using std::vector;
using std::cout;
using std::cin;

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
    for (int j=0; j<tarpSk; j++) {
        cout << "Iveskite " << j + 1 << " pazymi is " << tarpSk << ": ";
        cin >> tempInt;
        naujasStud.tarp.push_back(tempInt);
    } 
  }
  return 0;
}
