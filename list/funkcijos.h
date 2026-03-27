#include <string>
#include <list>
#include "strukturos.h"

using std::string;
using std::list;

void ivestEkr(list<Studentas> &studentai, bool rndPaz, bool rndVard);
void ivestIsFailo(list<Studentas> &studentai, string failoPav, bool &klaida);
void isvestEkr(const list<Studentas> &studentai, int pasirink);
void isvestIFaila(const list<Studentas> &studentai, int pasirink, string failoPav = "isvestis.txt");
void skaicGal(list<Studentas> &studentai, int pasirink);
bool isInt(string inp);
int validInput(string prompt);
int validRange(int from, int to, string prompt);
string validLength(int maxLength, string prompt);
string rndVardas(int from, int to);
void klauskEigos(bool &testi, Nustatymai &nustatymai);
void rusiuok(list<Studentas> &studentai, int rusBudas);
string klauskFailo(bool &klaida);
void kurkFaila(int studSk, int pazSk);
void skirstyk(int studSk);
void tirk(int studSk, int pazSk);
void tirkSkirstyma(list<Studentas> &studentai);