#include <vector>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "strukturos.h"
using namespace std;

int main() {
    ifstream infile("stud100.txt");
    stringstream buffer;
    string line;
    vector<Studentas> vargsiukai, galvociai;

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
            vargsiukai.push_back(studentas);
        }
        else {
            galvociai.push_back(studentas);
        }
    }

    return 0;
}
