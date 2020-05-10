#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>  
#include <stdlib.h>     
using namespace std;
//citim din fisierul de intrare linie cu linie
//separam continutul prin virgula
//afisam datele modificate in fisierul de intrare
//TEMPLATE INPUT:index, nume, gen, generatie(nivel), anul nasterii, anul decesului, varsta la care s-a produs decesul,
//				 anul casatoriei, varsta casatoriei, tip de personalitate, clan, id sot/sotie, id parinte1, id parinte2,
//				 nodul parinte (chiar nu stiu de la ce vine aici, oricum nu vom folosi toate aceste date)
//TEMPLATE OUTPUT:nume, gen, generatie, anul nasterii, anul decesului, anul casatoriei (-1 daca acesta este invalid),
//				  tip personalitate, nume sot/sotie, nume parinte1, nume parinte2
struct Persoana {
	int generatie, an_nastere, an_deces, an_casatorie, index_parinte1, index_parinte2, index_gagica;
	string nume, gen, personalitate, nume_parinte1, nume_parinte2, nume_sot_sotie;
}persoane[100];

string jobs[] = {"fierar", "tamplar", "cizmar", "armurier", "croitor", "agricultor", "cioban", "fara"};
int n = 8;
ifstream cin("date.in");
ofstream cout("date.out");

int main() {
	//Aici intervine marea carpeala, a trebuit sa iau fiecare linie din fisier sa o tratez separat apoi fiecare linie
	//obtinuta sa o tratez mai departe ca o linie cu delimitator virgula si apoi am citit din fiecare cuvant in parte ce era de retinut
	//Macar merge :)
	map<int, string> myMap;
	string line, csvLine;
	int generatie, an_nastere, an_deces, an_casatorie, index, index_gagica, index_parinte1, index_parinte2;
	string nume, gen, personalitate, nume_parinte1, nume_parinte2, nu_conteaza;
    while (getline(cin, csvLine)) {
        istringstream ss(csvLine);
		getline(ss, line, ',');
		istringstream(line) >> index;
		getline(ss, line, ',');
		istringstream(line) >> nume;
		myMap[index] = nume;
		getline(ss, line, ',');
		istringstream(line) >> gen;
		transform(gen.begin(), gen.end(), gen.begin(), ::tolower); 
		getline(ss, line, ',');
		istringstream(line) >> generatie;
		getline(ss, line, ',');
		istringstream(line) >> an_nastere;
		getline(ss, line, ',');
		istringstream(line) >> an_deces;
		getline(ss, line, ',');
		istringstream(line) >> nu_conteaza;
		getline(ss, line, ',');
		if (line.length() != 0) {
			istringstream(line)>> an_casatorie;
		}
		else {
			an_casatorie = -1;
		}
		getline(ss, line, ',');
		istringstream(line) >> nu_conteaza;
		getline(ss, line, ',');
		istringstream(line) >> personalitate;
		getline(ss, line, ',');
		istringstream(line) >> nu_conteaza;
		getline(ss, line, ',');
		if (line.length() != 0) {
			istringstream(line) >> index_gagica;
		}
		else {
			index_gagica = -1;
		}
		getline(ss, line, ',');
		if (line.length() != 0) {
			istringstream(line) >> index_parinte1;
		}
		else {
			index_parinte1 = -1;
		}
		getline(ss, line, ',');
		if (line.length() != 0) {
			istringstream(line) >> index_parinte2;
		}
		else {
			index_parinte2 = -1;
		}
		persoane[index].an_casatorie = an_casatorie;
		persoane[index].nume = nume;
		persoane[index].an_deces = an_deces;
		persoane[index].an_nastere = an_nastere;
		persoane[index].gen = gen;
		persoane[index].generatie = generatie;
		persoane[index].personalitate = personalitate;
		persoane[index].index_gagica = index_gagica;
		persoane[index].index_parinte1 = index_parinte1;
		persoane[index].index_parinte2 = index_parinte2;
    }
	for (int i = 0; i <= index; i++) {
		cout << "seGasesteInArbore(persoana(\"" << persoane[i].nume << "\", " << persoane[i].gen << ", " << persoane[i].generatie;
		cout << ", \"" << persoane[i].personalitate << "\", "<< persoane[i].an_nastere << ", " << persoane[i].an_deces << "), ";
		if (persoane[i].an_casatorie != -1) {
			cout << "casatorit(\"" << myMap[persoane[i].index_gagica] << "\", "<< persoane[i].an_casatorie <<"), ";
		}
		else {
			cout << "casatorit(\"-\", -1), ";
		}
		if (persoane[i].index_parinte1 != -1) {
			cout << "parinti(\"" << myMap[persoane[i].index_parinte1] << "\", \"" << myMap[persoane[i].index_parinte2] << "\"), ";
		}
		else {
			cout << "parinti(\"-\", \"-\"), ";
		}
		int r = rand() % n;
		cout << jobs[r] << ")." << endl;
	}
	//inchidem fisierele
	cin.close();
	cout.close();
}