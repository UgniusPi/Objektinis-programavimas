#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include "funkcijos.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;
using std::ofstream;
using std::to_string;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

void isvestEkr(const vector<Studentas> &studentai, int pasirink) {
    string galTekstas = (pasirink == 1) ? "Galutinis (Vid.)" : "Galutinis (Med.)";
    
    cout << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << "\n";
    cout << "---------------------------------------------------------" << "\n";
    
    for (auto stud : studentai) {
        cout << left << setw(21) << stud.pav << left << setw(16) << stud.vard << left << setw(20) << fixed << setprecision(2) << stud.gal << "\n";
    }
    cout << "\n\n";
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
                    med = stud.tarp.at(medIndex);
                }
                else {
                    med = (double)(stud.tarp.at(medIndex) + stud.tarp.at(medIndex - 1)) / 2;
                }
            }
            
            stud.gal = med * 0.4 + (double)stud.egz * 0.6;   
        }   
    }
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

void isvestIFaila(const vector<Studentas> &studentai, int pasirink, string failoPav) {
    ofstream file(failoPav);
    string galTekstas = (pasirink == 1) ? "Galutinis (Vid.)" : "Galutinis (Med.)";

    file << left << setw(21) << "Pavarde" << left << setw(16) << "Vardas" << left << setw(20) << galTekstas << "\n";
    file << "---------------------------------------------------------";
    
    for (auto stud : studentai) {
        file << "\n" << left << setw(21) << stud.pav << left << setw(16) << stud.vard << left << setw(20) << fixed << setprecision(2) << stud.gal;
    }
}

void rusiuok(vector<Studentas> &studentai, int rusBudas) {
    auto start = high_resolution_clock::now();
    if (rusBudas == 1) {
        sort(studentai.begin(), studentai.end(),
            [](const Studentas &a, const Studentas &b) { return a.vard < b.vard; });
    }
    else if (rusBudas == 2) {
        sort(studentai.begin(), studentai.end(),
            [](const Studentas &a, const Studentas &b) { return a.pav < b.pav; });
    }
    else {
        sort(studentai.begin(), studentai.end(),
            [](const Studentas &a, const Studentas &b) { return a.gal > b.gal; });
    }
    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    cout << "Vector konteinerio duomenu rusiavimas uztruko: " << elapsed.count() << "\n";
}

string kurkFaila(int studSk, int pazSk) {
    auto start = high_resolution_clock::now();
    string failoPav = "stud" + to_string(studSk) + ".txt";
    string failoKelias = "ivestis/" + failoPav;
    ofstream file(failoKelias);

    file << left << setw(16) << "Vardas" << right << setw(16) << "Pavarde" << setw(13) << " ";
    for (int i=0; i<pazSk; i++) {
        file << right << setw(10) << "ND" + to_string(i + 1);
    }
    file << right << setw(10) << "Egz." << "\n"; 

    for (int i=0; i<studSk; i++) {
        file << left << setw(16) << "Vardas" + to_string(i + 1) << right << setw(16) << "Pavarde" + to_string(i + 1);
        file << setw(13) << " ";
        for (int j=0; j<pazSk; j++) {
            file << right << setw(10) << to_string(rand() % 10 + 1);
        }
        file << right << setw(10) << to_string(rand() % 10 + 1) << "\n";
    }
    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    cout << to_string(studSk) << " irasu faila sukurti uztruko: " << elapsed.count() << "\n";

    return failoKelias;
}

void skirstyk(const vector<Studentas> &studentai, vector<Studentas> &vargsiukai, vector<Studentas> &galvociai) {
    auto start = high_resolution_clock::now();
    for (const auto &stud : studentai) {
        if (stud.gal < 5) {
            vargsiukai.push_back(stud);
        }
        else {
            galvociai.push_back(stud);
        }
    }
    auto end = high_resolution_clock::now();
    auto elapsed = end - start;
    cout << "Irasu skirstymas i dvi grupes uztruko: " << elapsed.count() << "\n";
}