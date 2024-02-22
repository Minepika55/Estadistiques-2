#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

typedef struct Ciberware
{
    char nom[20];
    char instal[20];
    int preu;
    int perdua;
};

int main()
{
    fstream fs;
    vector<Ciberware> ciberwares;
    int opcio;

    cout << "### Benvingut, Tria una Opcio ###" << endl;
    cout << "1. Afegir Cyberware" << endl;
    cout << "2. Mostrar Cyberware" << endl;
    cout << "3. Mostrar Mitjana dels preus" << endl;
    cin >> opcio;

    switch (opcio) {
    case 1:
    {
        Ciberware c;
        cout << "Nom del Cyberware:";
        cin >> c.nom;
        cout << "Local d'instalacio:";
        cin >> c.instal;
        cout << "Preu:";
        cin >> c.preu;
        cout << "Perdua d'Humanitat:";
        cin >> c.perdua;
        ciberwares.push_back(c);
        fs.open("cyberdades.dat", ios::app | ios::binary);
        if (fs.is_open()) {
            fs.write((char*)&ciberwares[0], ciberwares.size() * sizeof(Ciberware));
            fs.close();
        }
        else {
            cout << "Error no s'ha pogut guardar al fitxer." << endl;
        }
        break;
    }
    case 2:
    {
        fs.open("cyberdades.dat", ios::in | ios::binary);
        if (fs.is_open()) {
            Ciberware c;
            while (fs.read((char*)&c, sizeof(Ciberware))) {
                cout << "------------------------" << endl;
                cout << "Nom: " << c.nom << endl;
                cout << "Instalacio: " << c.instal << endl;
                cout << "Preu: " << c.preu << endl;
                cout << "Perdua d'humanitat: " << c.perdua << endl;
                cout << "------------------------" << endl;
            }
            fs.close();
        }
        else {
            cout << "Error no es pot llegir el fitxer." << endl;
        }
        break;
    }
    case  3:
    {
        fs.open("cyberdades.dat", ios::in | ios::binary);
        if (fs.is_open()) {
            Ciberware c;
            int sumaPreus = 0;
            int comptador = 0;
            while (fs.read((char*)&c, sizeof(Ciberware))) {
                sumaPreus += c.preu; 
                comptador++; 
            }
            fs.close();
            if (comptador > 0) {
                double mitjanaPreus = static_cast<double>(sumaPreus) / comptador;
                cout << "La mitjana dels preus dels Cyberware es: " << mitjanaPreus << endl;
            }
            else {
                cout << "No es troben els preus." << endl;
            }
        }
        else {
            cout << "Error no es pot llegir el fitxer." << endl;
        }
        break;
    }

    default:
        cout << "Error torna a introduir una opcio.";
        break;
    }

    return  0;
}

