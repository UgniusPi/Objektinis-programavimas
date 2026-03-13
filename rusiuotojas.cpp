#include <vector>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "strukturos.h"
using namespace std;

void isveskIFaila(const Studentas &studentas, ofstream &failas);

int main() {
    ifstream infile("stud100.txt");
    ofstream outfile1("vargsiukai.txt");
    ofstream outfile2("galvociai.txt");
    stringstream buffer;
    string line;

    string galTekstas = "Galutinis (Vid.)";
    outfile1 << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << "\n";
    outfile1 << "---------------------------------------------------------";
    outfile2 << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << "\n";
    outfile2 << "---------------------------------------------------------";

    

    buffer << infile.rdbuf();  

    getline(buffer, line);
    while (getline(buffer, line)) {
        stringstream ss(line);
        Studentas studentas;
        ss >> studentas.vard;
        ss >> studentas.pav;
        string tmp;
        while (ss >> tmp) {
            studentas.tarp.push_back(stoi(tmp));
        }

        studentas.egz = studentas.tarp.back();
        studentas.tarp.pop_back();

        int suma = 0;
        double vid = 0;
        
        for (int paz : studentas.tarp) {
            suma += paz;
        }
        
        if (studentas.tarp.size() != 0) {
            vid = (double)suma / studentas.tarp.size();   
        }
        studentas.gal = vid * 0.4 + (double)studentas.egz * 0.6; 

        if (studentas.gal < 5) {
            isveskIFaila(studentas, outfile1);
        }
        else {
            isveskIFaila(studentas, outfile2);
        }
    }


    return 0;
}

void isveskIFaila(const Studentas &studentas, ofstream &failas) {

    failas << "\n" << left << setw(21) << studentas.pav << left << setw(16) << studentas.vard << left << setw(20) << fixed << setprecision(2) << studentas.gal;
}
