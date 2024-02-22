#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef struct Ciberware {
    char nom[20];
    char instal[20];
    int preu;
    int perdua;
};

int main() {
    fstream fs;
    vector < Ciberware > ciberwares;
    int opcio;
    int opcio2;

    do {

        cout << "### Benvingut, Tria una Opcio ###" << endl;
        cout << "1. Afegir Cyberware" << endl;
        cout << "2. Mostrar Cyberware" << endl;
        cout << "3. Mostrar Mitjana dels preus" << endl;
        cout << "4. Mostrar La Moda de la perdua d'humanitat" << endl;
        cout << "5. Esborrar un Cyberware" << endl;
        cin >> opcio;

        switch (opcio) {
        case 1: {
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
        case 2: {
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
        case 3: {
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
                    double mitjanaPreus = static_cast <double> (sumaPreus) / comptador;
                    cout << "La mitjana dels preus dels Cyberware es: " << mitjanaPreus << endl;
                }
                else {
                    cout << "ERROR No es troben els preus." << endl;
                }
            }
            else {
                cout << "ERROR no es pot llegir el fitxer." << endl;
            }
            break;

        }
        case 4: {
            fs.open("cyberdades.dat", ios::in | ios::binary);
            if (fs.is_open()) {
                Ciberware c;
                vector < int > valorsPerdua;
                vector < int > freqPerdua;

                while (fs.read((char*)&c, sizeof(Ciberware))) {
                    valorsPerdua.push_back(c.perdua);
                }
                fs.close();

                for (int i = 0; i < valorsPerdua.size(); ++i) {
                    int freq = std::count(valorsPerdua.begin(), valorsPerdua.end(), valorsPerdua[i]);
                    freqPerdua.push_back(freq);
                }

                int maxFreq = *std::max_element(freqPerdua.begin(), freqPerdua.end());
                int modaPerdua = valorsPerdua[std::distance(freqPerdua.begin(), std::find(freqPerdua.begin(), freqPerdua.end(), maxFreq))];

                cout << "La moda de la perdua d'humanitat es: " << modaPerdua << endl;
            }
            else {
                cout << "ERROR no es pot llegir el fitxer." << endl;
            }
            break;

        }
        case 5: {
            char ciberaBorrar[20];
            cout << "Introdueix el nom del Cyberware que vols esborrar: ";
            cin.ignore();
            cin.getline(ciberaBorrar, 20);

            fs.open("cyberdades.dat", ios::binary | ios::in);
            if (!fs.is_open()) {
                cout << "ERROR No es pot obrir el fitxer." << endl;
            }
            else {
                ios_base::sync_with_stdio(false);
                cin.tie(NULL);
                vector < Ciberware > tempCyberwares;
                Ciberware cache;
                bool funciona = false;

                while (fs.read((char*)&cache, sizeof(Ciberware))) {
                    if (strcmp(ciberaBorrar, cache.nom) == 0) {
                        funciona = true;
                        cout << "------------------------" << endl;
                        cout << "Esborrant el Cyberware...." << endl;
                        cout << "Nom: " << cache.nom << endl;
                        cout << "Instalacio: " << cache.instal << endl;
                        cout << "Preu: " << cache.preu << endl;
                        cout << "Perdua d'humanitat: " << cache.perdua << endl;
                        cout << "Eliminant... " << endl;
                        cout << "------------------------" << endl;
                    }
                    else {
                        tempCyberwares.push_back(cache);
                    }
                }
                fs.close();

                if (!funciona) {
                    cout << "ERROR el Cyberware no s'hatrobat." << endl;
                }
                else {
                    fstream cacheTemp("cacheCyberdades.dat", ios::binary | ios::out);
                    if (!cacheTemp.is_open()) {
                        cout << "No es pot crear el fitxer temporal." << endl;
                        return 0;
                    }
                    for (const auto& c : tempCyberwares) {
                        cacheTemp.write((char*)&c, sizeof(Ciberware));
                    }
                    cacheTemp.close();

                    remove("cyberdades.dat");
                    rename("cacheCyberdades.dat", "cyberdades.dat");
                    cout << "Cyberware eliminat amb exit." << endl;
                }
            }
        }
              break;
        default:
            cout << "ERROR torna a introduir una opcio.";
            break;
        }
        cout << "Vols fer algo mes? 1. Si 2. No" << endl;
        cin >> opcio2;
    } while (opcio2 == 1);

    return 0;
}