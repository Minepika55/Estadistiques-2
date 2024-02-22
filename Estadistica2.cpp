#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef struct Ciberware {//Estructura del Cyberware
    char nom[20];//Nom del Cyberware
    char instal[20];//Local d'instalacio del Cyberware
    int preu;//Preu del Cyberware
    int perdua;//Perdua d'humanitat del Cyberware
};

int main() {
    fstream fs;
    vector < Ciberware > ciberwares;//Vector per guardar l'info del Cyberware
    int opcio;//Opcions del switch
    int opcio2;//Opcio per continuar el bucle del codi

    do {
        //Menu principal del codi
        cout << "### Benvingut, Tria una Opcio ###" << endl;
        cout << "1. Afegir Cyberware" << endl;
        cout << "2. Mostrar Cyberware" << endl;
        cout << "3. Mostrar Mitjana dels preus" << endl;
        cout << "4. Mostrar La Moda de la perdua d'humanitat" << endl;
        cout << "5. Editar un Cyberware ja existent" << endl;
        cout << "6. Esborrar un Cyberware ja existent" << endl;
        cin >> opcio;

        switch (opcio) {
        case 1: {//Cas per crear un nou Cyberware i afegir-lo al fitxer
            Ciberware c;
            cout << "Nom del Cyberware:";
            cin >> c.nom;
            cout << "Local d'instalacio:";
            cin >> c.instal;
            cout << "Preu:";
            cin >> c.preu;
            cout << "Perdua d'Humanitat:";
            cin >> c.perdua;
            ciberwares.push_back(c);//Guardo les dades al vector
            fs.open("cyberdades.dat", ios::app | ios::binary);//Obro el fitxer i afegeixo les dades despres es guarda en binari
            if (fs.is_open()) {
                fs.write((char*)&ciberwares[0], ciberwares.size() * sizeof(Ciberware));
                fs.close();
            }
            else {//Si el fitxer falla salta l'error
                cout << "ERROR no s'ha pogut guardar al fitxer." << endl;
            }
            break;
        }
        case 2: {//Cas que llegeix totes les Cyberparts del fitxer de dades
            fs.open("cyberdades.dat", ios::in | ios::binary);//Obro el fitxer per llegir-lo
            if (fs.is_open()) {
                Ciberware c;
                while (fs.read((char*)&c, sizeof(Ciberware))) {//Es va llegint i mostrant tot el Cyberware del fitxer
                    cout << "-------------------------" << endl;
                    cout << "Nom: " << c.nom << endl;
                    cout << "Instalacio: " << c.instal << endl;
                    cout << "Preu: " << c.preu << endl;
                    cout << "Perdua d'humanitat: " << c.perdua << endl;
                    cout << "-------------------------" << endl;
                }
                fs.close();
            }
            else {//Si el fitxer falla salta l'error
                cout << "ERROR no es pot llegir el fitxer." << endl;
            }
            break;
        }
        case 3: {//Cas que mostra la mitjana de totes les Cyberparts del fitxer
            fs.open("cyberdades.dat", ios::in | ios::binary);//Obro el fitxer per llegir-lo
            if (fs.is_open()) {
                Ciberware c;
                int sumaPreus = 0;//Suma total de tots els preus
                int comptador = 0;//Numero total de Cyberware
                while (fs.read((char*)&c, sizeof(Ciberware))) {//Vaig llegint el fitxer
                    sumaPreus += c.preu;//Vaig guardant i sumant els preus
                    comptador++;//Vaig guardant la quantitat de Cyberware que hi ha
                }
                fs.close();
                if (comptador > 0) {//Quan ja no es detecten mes Cyberparts es passa a calcular la mitjana dels preus
                    double mitjanaPreus = static_cast <double> (sumaPreus) / comptador;//Sumo els preus del Cyberware i el divideixo per el total de Cyberware
                    cout << "La mitjana dels preus dels Cyberware es: " << mitjanaPreus << endl;//Es mostra la mitjana
                }
                else {
                    cout << "ERROR No es troben els preus." << endl;//Si no es troben els preus salta l'error
                }
            }
            else {//Si el fitxer falla salta l'error
                cout << "ERROR no es pot llegir el fitxer." << endl;
            }
            break;

        }
        case 4: {//Cas per calcular la moda de la perdua d'humanitat de tot el Cyberware
            fs.open("cyberdades.dat", ios::in | ios::binary);//Obro el fitxer per llegir-lo
            if (fs.is_open()) {//Mentre el fitxer esta obert es va llegint tot el Cyberware del fitxer
                Ciberware c;
                vector < int > valorsPerdua;//Guardo els valors de la perdua
                vector < int > freqPerdua;//Guardo la frequencia en que la perdua es igual en dos Cyberwares

                while (fs.read((char*)&c, sizeof(Ciberware))) {//Es van llegint els Cyberwares del fitxer
                    valorsPerdua.push_back(c.perdua);
                }
                fs.close();

                for (int i = 0; i < valorsPerdua.size(); ++i) {
                    int freq = std::count(valorsPerdua.begin(), valorsPerdua.end(), valorsPerdua[i]);//Guardem els valors repetits 
                    freqPerdua.push_back(freq);
                }

                int maxFreq = *std::max_element(freqPerdua.begin(), freqPerdua.end());
                int modaPerdua = valorsPerdua[std::distance(freqPerdua.begin(), std::find(freqPerdua.begin(), freqPerdua.end(), maxFreq))];//Ens guardem el valor que s'ha repetit mes

                cout << "La moda de la perdua d'humanitat es: " << modaPerdua << endl;//Mostrem la moda de la perdua d'humanitat
            }
            else {//Si el fitxer falla salta l'error
                cout << "ERROR no es pot llegir el fitxer." << endl;
            }
            break;

        }
        case 5: {//Cas per modificar un Cyberware del fitxer
            char Cyberwaremod[20];//Guardo el Cyberware que es vol modificar
            cout << "Introdueix el nom del Cyberware que vols editar: ";//Demano el nom del Cyberware
            cin.ignore();
            cin.getline(Cyberwaremod, 20);

            fs.open("cyberdades.dat", ios::binary | ios::in);//Obro el fitxer per llegir-lo
            if (!fs.is_open()) {//Si el fitxer falla salta l'error
                cout << "ERROR No es pot obrir el fitxer." << endl;
            }
            else {
                vector<Ciberware> Ciberwaremodificat;//Obro el vector de Cyberware i guardo els que no necessito en un de temporal 
                Ciberware c;
                bool modificat = false;//Faig un boolea per comprovar si s'esta modificant la Cyberpart

                while (fs.read((char*)&c, sizeof(Ciberware))) {//Mentre el fitxer es va llegint demano a l'usuari les noves dades a substituir del Cyberware
                    if (strcmp(Cyberwaremod, c.nom) == 0) {
                        modificat = true;
                        cout << "Modificant el Cyberware: " << c.nom << endl;
                        cout << "Nou nom: ";
                        cin.getline(c.nom, 20);
                        cout << "Nou local d'instalacio: ";
                        cin.getline(c.instal, 20);
                        cout << "Nou preu: ";
                        cin >> c.preu;
                        cout << "Nova perdua d'humanitat: ";
                        cin >> c.perdua;
                        cin.ignore();
                    }
                    Ciberwaremodificat.push_back(c);//Restableixo les altres Cyberparts guardades en el vector temporal
                }
                fs.close();//Tenco el fitxer

                if (!modificat) {//Si el boolean detecta que ha fallat al introduir-se les modificacions salt un error
                    cout << "ERROR el Cyberware no s'ha trobat." << endl;
                }
                else {//Si no hi ha fallos continuem amb la modificacio
                    fs.open("cyberdades.dat", ios::binary | ios::out);//Obro el fitxer per llegir-lo
                    if (!fs.is_open()) {//Si el fitxer falla salta l'error
                        cout << "ERROR No es pot obrir el fitxer." << endl;
                    }
                    else {//Ara sobreescriure el Cyberware antic per el nou
                        for (const auto& c : Ciberwaremodificat) {
                            fs.write((char*)&c, sizeof(Ciberware));
                        }
                        fs.close();//Torno a tencar el fitxer
                        cout << "Cyberware modificat sense problemes." << endl;//Aviso de que la modificacio ha funcionat
                    }
                }
            }
            break;
        }
        case 6: {//Cas per esborrar un Cyberware del fitxer
            char ciberaBorrar[20];//Guardo el nom del Cyberware que s'ha d'esborrar
            cout << "Introdueix el nom del Cyberware que vols esborrar: ";
            cin.ignore();
            cin.getline(ciberaBorrar, 20);

            fs.open("cyberdades.dat", ios::binary | ios::in);//Obro el fitxer per llegir-lo
            if (!fs.is_open()) {//Si el fitxer falla salta l'error
                cout << "ERROR No es pot obrir el fitxer." << endl;
            }
            else {//Si el fitxer no falla en obrir-se s'inicia el borrat
                ios_base::sync_with_stdio(false);
                cin.tie(NULL);
                vector < Ciberware > tempCyberwares;//Obro el vector de Cyberware i guardo els que no necessito en un de temporal
                Ciberware cache;
                bool funciona = false;//Faig un boolea per comprovar si s'esta esborrant be el Cyberware

                while (fs.read((char*)&cache, sizeof(Ciberware))) {//Aqui es va llegint el fitxer
                    if (strcmp(ciberaBorrar, cache.nom) == 0) {
                        funciona = true;
                        cout << "-------------------------" << endl;
                        cout << "Esborrant el Cyberware...." << endl;
                        cout << "Nom: " << cache.nom << endl;
                        cout << "Instalacio: " << cache.instal << endl;
                        cout << "Preu: " << cache.preu << endl;
                        cout << "Perdua d'humanitat: " << cache.perdua << endl;
                        cout << "Eliminant totes les parts... " << endl;
                        cout << "-------------------------" << endl;
                    }
                    else {
                        tempCyberwares.push_back(cache);//Restableixo les altres Cyberparts guardades en el vector temporal
                    }
                }
                fs.close();//Tenco el fitxer

                if (!funciona) {//Si no troba el Cyberware especificat salta l'error
                    cout << "ERROR el Cyberware no s'ha trobat." << endl;
                }
                else {
                    fstream cacheTemp("cacheCyberdades.dat", ios::binary | ios::out);//Faig un fitxer temporal on es guardaran les dades noves
                    if (!cacheTemp.is_open()) {//Si no es pot crear salta un error
                        cout << "No es pot crear el fitxer temporal." << endl;
                        return 0;
                    }
                    for (const auto& c : tempCyberwares) {//Escric les dades noves dins del fitxer
                        cacheTemp.write((char*)&c, sizeof(Ciberware));
                    }
                    cacheTemp.close();//Tenco el fitxer

                    remove("cyberdades.dat");//Esborro el fitxer antic
                    rename("cacheCyberdades.dat", "cyberdades.dat");//Cambio el nom del fitxer temporal al nom de l'original
                    cout << "Cyberware eliminat amb exit." << endl;//Aviso que ha funcionat el codi
                }
            }
        }
              break;


        default:
            cout << "ERROR torna a introduir una opcio.";//Si l'usuari tria una opcio incorrecta salta un error
            break;
        }
        cout << "Vols fer algo mes? 1. Si 2. No" << endl;//Un cop feta una funció es demana a l'usuari si vol fer algo mes
        cin >> opcio2;
    } while (opcio2 == 1);

    return 0;
}