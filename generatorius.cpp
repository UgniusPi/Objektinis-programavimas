#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(0));
    ofstream file("stud10000000.txt");
    int studSk = 10000000;

    file << "Vardas                   Pavarde                    ND1       ND2       ND3       ND4       ND5       ND6       ND7       ND8       ND9      ND10      ND11      ND12      ND13      ND14      ND15      Egz.\n";
    for (int i=0; i<studSk; i++) {
        file << left << setw(16) << "Vardas" + to_string(i + 1) << right << setw(16) << "Pavarde" + to_string(i + 1);
        file << setw(20) << " ";
        for (int j=0; j<15; j++) {
            file << right << setw(3) << to_string(rand() % 10 + 1) << setw(7) << " ";
        }
        file << right << setw(3) << to_string(rand() % 10 + 1) << "\n";
    }


    return 0;
}