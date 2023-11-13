/********************************************************************
H10.Doti divi bināri faili f1 un f2, kuru komponentes ir ieraksti ar struktūru:
atslēga (int), vārds (nepārsniedz 30 simbolus). Failu komponentes sakārtotas
pēc atslēgām dilstošā secībā. Uzrakstīt programmu, kas apvieno failus f1
un f2 failā f3 tā, lai arī f3 komponentes būtu dilstošā secībā (failos nedrīkst
parādīties divas komponentes ar vienādu atslēgu vērtību). Programmu
veidot tā, lai pilns faila saturs netiktu ielādēts operatīvajā atmiņā. Uzrakstīt
arī palīgprogrammas, kas ļauj izveidot failus f1 un f2 un izdrukā failu saturu.
********************************************************************/
///Kristiāns Krūmiņš kk22111
///Programma izstrādāta: 16.05.2023

#include <iostream>
#include <fstream>
#include <map>
#include <cstring>

using namespace std;

//Struktūra, lai turētu atslēgu un vērtību pārus
struct vertibas {
    int key{};
    char name[31]{};
    vertibas() = default;;
    vertibas(const int atslega, const string& vards) {
        this->key = atslega;
        strcpy(this->name, vards.c_str());
    }
};
/*********************************************************
void Izvada(const string& filename)
Funkcija Izvada
Nolasa binārā faila datus un izvada tos
*********************************************************/
void Izvada(const string& filename) {
    ifstream file(filename, ios::binary);
    vertibas it;             // Izveidojiet vertibas tipa mainīgo
    while (file.read((char*)&it, sizeof(vertibas))) {                                      // Lasa datus no faila uz mainīgo it
        cout << "Atslēga: " << it.key << " Vārds: " << it.name << endl;       // un turpiniet ciklu, līdz tiek sasniegts faila beigas
    }
    file.close();
}
/***********************************************************
void ParveidoDilstosi(map<int, string>& objekts, const string& filename)
Funkcija ParveidoDilstosi
Pārvieto failus no STL map uz binārajiem failiem un sakārto
tos dilstošā secībā skatoties uz atslēgas vērtību
***********************************************************/
void ParveidoDilstosi(map<int, string>& objekts, const string& filename) {
    ofstream file(filename, ios::binary);
    for (auto it = objekts.rbegin(); it != objekts.rend(); it++) {               //iet cauri STL map apgrieztā secībā, lai binārajā failā dati būtu dilstošā secībā
        vertibas item(it->first, it->second);
        file.write(reinterpret_cast<char*>(&item), sizeof(vertibas));    // Ierakstiet vertibas objekta saturu binārajā failā
    }                                                                                             // laižot to uz char rādītāju un norādot izmēru
    file.close();
}
/***********************************************************
void ApvienoDilstosi(const string& f1, const string& f2, const string& f3)
Funkcija ApvienoDilstosi
Apvieno failus f1 un f2 dilstošā secība skatoties uz atslēgas
vērtību un ievieto tos failā f3
***********************************************************/
void ApvienoDilstosi(const string& f1, const string& f2, const string& f3) {
    ifstream file1(f1, ios::binary);
    ifstream file2(f2, ios::binary);
    ofstream file3(f3, ios::binary);
    map<int, string> objekts;
    vertibas item;

    while (file1.read((char*)&item, sizeof(vertibas))){            // Lasīt datus no faila1 un ievietot tos objekts kartē
        objekts.insert(make_pair(item.key, item.name));
    }
    while (file2.read((char*)&item, sizeof(vertibas))){               // Lasīt datus no faila2 un ievietot tos objekts kartē
        objekts.insert(make_pair(item.key, item.name));
    }

    for (auto it = objekts.rbegin(); it != objekts.rend(); it++) {
        vertibas vertibas(it->first, it->second);                                           //apgrieztā secība ievada datus fail3 no objekts kartes
        file3.write(reinterpret_cast<char*>(&vertibas), sizeof(vertibas));
    }
    file1.close();
    file2.close();
    file3.close();
}
/*********************************************************
int main()
Funkcija main
Prasa lietotājām ievadīt vērtības priekš f1 un f2 faila,
kā arī nosūta datus uz funkcijām, kur tie tiek apstrādāti
**********************************************************/
int main() {
    int ok;
    do {
        int atslega;
        string vards;
        map<int, string> f1;
        map<int, string> f2;

        cout << "Ievadiet f1 faila vērtības" << endl;
        do {
            cout << "Ievadiet atslēgas vērtību (0, lai beigtu): ";
            cin >> atslega;
            if (atslega != 0) {
                do {
                    cout << "Ievadiet vārdu: ";
                    cin >> vards;
                    if (vards.length() > 30) cout<<"Vārda maksīmālais rakstzīmju skaits ir 30."<<endl;   //pārbauda vai vārda lielums pārsniedz atļauto un
                }while (vards.length() > 30);                                                                                      //ja parsniedz paziņo par to un liek lietotājam
                f1.insert(make_pair(atslega, vards));    //Ievieto datus f1 STL map                              //ievadīt jaunu varda vertību
            }
        } while (atslega != 0);

        cout << "Ievadiet f2 faila vērtības" << endl;
        do {
            cout << "Ievadiet atslēgas vērtību (0, lai beigtu): ";
            cin >> atslega;
            if (atslega != 0) {
                do {
                    cout << "Ievadiet vārdu: ";
                    cin >> vards;
                    if (vards.length() > 30) cout<<"Vārda maksīmālais rakstzīmju skaits ir 30."<<endl;
                }while (vards.length() > 30);
                f2.insert(make_pair(atslega, vards));     //Ievieto datus f2 STL map
            }
        } while (atslega != 0);

        ParveidoDilstosi(f1, "f1.bin");              //Nosūta datus uz funkciju ParveidoDilstosi
        cout << "'f1 faila sastāvs:" << endl;
        Izvada("f1.bin");                                //Nosuta datus uz funkciju Izvada

        ParveidoDilstosi(f2, "f2.bin");
        cout << "'f2 faila sastāvs:" << endl;
        Izvada("f2.bin");

        ApvienoDilstosi("f1.bin", "f2.bin", "f3.bin");     //Nosūta datus uz funkciju ApvienoDilstosi
        cout << "'f3 faila sastāvs:" << endl;
        Izvada("f3.bin");

        cout << "Vai turpināt(1) vai beigt(0)?" << endl;
        cin >> ok;
    } while (ok == 1);
}
/****************************Testa Plāns*************************************
    Ievads failā            Ievads failā            Vēlamais rezultāts failā
           f1                             f2                                    f3
=================================================
  1 alfa                        23 charlie               23 charlie
  14 bravo                   17 delta                  17 delta
                                                                14 bravo
                                                                1 alfa
=================================================
11 aaaaaaaaaa            1 b                    Tiek paziņots par
     aaaaaaaaaa                                     ievades kļūdu
     aaaaaaaaaa
=================================================
 99 apals                   33 tris                     99 apals
  1 aa                         1 aa                        33 tris
                                                                11 aa
*********************************************************************************/
