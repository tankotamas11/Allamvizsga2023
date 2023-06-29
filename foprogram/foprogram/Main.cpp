#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct Pont{
    int szomszedokszama = 0;
    int elkuldottek = 0;
    int fogadott = 0;
    double csomosodasiegyutthato = 0.0;
};


struct Kapcsolat {
    string nev1;
    string nev2;
    int nap;
    int honap;
    int ev;
};
int honapToInt(string x) {
    string honapok[] = { "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
    auto it = find(begin(honapok), end(honapok), x);
    if (it != end(honapok)) {
        int poz = it - begin(honapok) + 1;
        return poz;
    }

    return 0;
}
int egyutthatoSzamitas(int matrix[][50], int szom[], int sz) {
    int eredmeny = 0;
    for (int i = 0; i < sz - 1; i++) {
        for (int j = i + 1; j < sz; j++) {
            if (matrix[szom[i]][szom[j]] != 0) {
                eredmeny++;
            }
        }
    }
    return eredmeny;
}

int nevsorban(string* nevsor, int meret, string nev) {
    for (int i = 0; i < meret; i++) {
        if (nevsor[i] == nev) {
            return i;
        }
    }
    return -1;
}

bool bennevan(int tomb[], int m, int elem) {
    for (int i = 0; i < m; i++) {
        if (tomb[i] == elem) {
            return true;
        }
    }
    return false;
}
int main() {
    int enronNum = 0;
    do {
        cout << "Kerem adja meg hany szemelybol alljon a graf " << endl;
        cin >> enronNum;
    } while (enronNum > 50 && enronNum < 1);

    ifstream infile("enronosok.txt");
    if (!infile.is_open()) {
        cout << "Hibas fajlmegnyitas!";
        return 1;
    }
    string nevek;
    int size = 0;
    while (getline(infile, nevek)) {
        size++;
    }
    string* osszesnev = new string[size];
    infile.clear();
    infile.seekg(0, ios::beg);
    int i = 0;
    while (getline(infile, nevek)) {
        osszesnev[i] = nevek;
        i++;
    }
    infile.close();//megtortent a beolvasasa a neveknek , most kivalasztjuk a szukseges neveket.
    string* nevsor = new string[enronNum];
    bool helyes = false;
    int kezdet = 0;
    int* idk = new int[enronNum];
    //
    do {
        // kezdet = rand() % size;
        kezdet = 0;
        if (kezdet + enronNum < size) {
            helyes = true;
        }
    } while (!helyes);
    for (int i = kezdet; i < kezdet + enronNum; i++) {
        nevsor[i - kezdet] = osszesnev[i];
        //cout << nevsor[i - kezdet] << endl;
    }
    //
    /*
    for (int i = 0; i < enronNum; i++) {
        helyes = false;
        do {
            seged = rand() % size;
            if (i == 0) {
                helyes = true;
            }
            else {
                if (!bennevan(idk, i, seged)) {
                    helyes = true;
                }
            }
        } while (!helyes);
        idk[i] = seged;
        nevsor[i] = osszesnev[seged];
        cout << nevsor[i] << endl;
    }
    */
    //nevsor megvan
    ifstream f("kapcsolatok.txt");
    if (!f.is_open()) {
        cout << "Hibas fajlmegnyitas!";
        return 2;
    }
    Pont* pontok = new Pont[enronNum];
    string str1, str2, honapStr;
    int nap, honap, ev, segedId1, segedId2;
    //int iranyitott[50][50];
    int iranyitatlan[50][50];
    for (int m = 0; m < 50; m++) {
        for (int n = 0; n < 50; n++) {

            //iranyitott[m][n] = 0;
            iranyitatlan[m][n] = 0;
        }
    }
    Kapcsolat kapcsolatok[10000];
    int db = 0, s;
    while (!f.eof()) {

        f >> str1 >> str2 >> nap >> honapStr >> ev;
        segedId1 = nevsorban(nevsor, enronNum, str1);
        segedId2 = nevsorban(nevsor, enronNum, str2);
        //cout << segedId1 << " "<<segedId2 << endl;
        if (segedId1 >= 0 && segedId2 >= 0 && segedId1 != segedId2) {
            honap = honapToInt(honapStr);

            kapcsolatok[db].nev1 = str1;
            //kapcsolatok[db].id1 = segedId1;
            //kapcsolatok[db].id2 = segedId2;
            kapcsolatok[db].nev2 = str2;
            kapcsolatok[db].nap = nap;
            kapcsolatok[db].honap = honap;
            kapcsolatok[db].ev = ev;
            Kapcsolat jelenlegi = kapcsolatok[db];
            if (db > 0) {
                s = db - 1;
                helyes = false;
                while (s >= 0 && helyes == false) {
                    if (kapcsolatok[s].ev < jelenlegi.ev) {
                        helyes = true;
                    }
                    else {
                        if (kapcsolatok[s].ev == jelenlegi.ev) {
                            if (kapcsolatok[s].honap < jelenlegi.honap) {
                                helyes = true;
                            }
                            else {
                                if (kapcsolatok[s].honap == jelenlegi.honap) {
                                    if (kapcsolatok[s].nap <= jelenlegi.nap) {
                                        helyes = true;
                                    }
                                    else {
                                        kapcsolatok[s + 1] = kapcsolatok[s];
                                        kapcsolatok[s] = jelenlegi;
                                    }
                                }
                                else {
                                    kapcsolatok[s + 1] = kapcsolatok[s];
                                    kapcsolatok[s] = jelenlegi;
                                }
                            }
                        }
                        else {
                            kapcsolatok[s + 1] = kapcsolatok[s];
                            kapcsolatok[s] = jelenlegi;
                        }
                    }
                    s--;
                }
            }
            pontok[segedId1].elkuldottek++;
            pontok[segedId2].fogadott++;
            //iranyitott[segedId1][segedId2]++;
            //iranyitatlan[segedId1][segedId2]++; 
            //iranyitatlan[segedId2][segedId1]++;
            db++;

        }
    }
    cout << db << endl;
    int valasztott;
    cout << "Olvassa be melyik pont csomosodasi egyutthatojanak a fejlodeset mutassuk ki a" << kezdet << "-" << kezdet + enronNum - 1 << "intervallumbol" << endl;
    cin >> valasztott;
    int* szomszedok = new int[enronNum];
    int maximalisbaratsag = 0;
    bool ebbeahonapba = false;
    //rendezve megvannak a kapcsolatok
    for (int c = 0; c < db; c++) {
        //felbontom a elek betolteset kulonbozo idokre
        segedId1 = nevsorban(nevsor, enronNum, kapcsolatok[c].nev1);
        segedId2 = nevsorban(nevsor, enronNum, kapcsolatok[c].nev2);
        iranyitatlan[segedId1][segedId2]++;
        iranyitatlan[segedId2][segedId1]++;

        //csomosodasi egyutthato meghatarozasa
        if (kapcsolatok[c].honap % 6 == 0 && ebbeahonapba == false) {
            ebbeahonapba = true;
            maximalisbaratsag = 0;
            for (int i = 0; i < enronNum; i++) {
                for (int j = 0; j < enronNum; j++) {
                    if (iranyitatlan[i][j] != 0) {
                        szomszedok[pontok[i].szomszedokszama] = j;
                        pontok[i].szomszedokszama++;
                    }
                }
                if (pontok[i].szomszedokszama < 2) {
                    pontok[i].csomosodasiegyutthato = -1;
                }
                else {

                    maximalisbaratsag = (pontok[i].szomszedokszama * (pontok[i].szomszedokszama - 1)) / 2;
                    pontok[i].csomosodasiegyutthato = (double)egyutthatoSzamitas(iranyitatlan, szomszedok, pontok[i].szomszedokszama) / maximalisbaratsag;
                    // cout << egyutthatoSzamitas(iranyitatlan, szomszedok, pontok[i].szomszedokszama) << " //" <<  maximalisbaratsag << endl;
                }
                if (i == valasztott) {
                    cout << "A valasztott pont csomosodasi egyutthatoja " << pontok[i].csomosodasiegyutthato << " valamint szomszedjainak szama " << pontok[i].szomszedokszama << endl;
                }
                
            }
        }
        if (kapcsolatok[c].honap % 6 == 1) {
            ebbeahonapba = false;
        }

    }
    int maxEgyutthato = 0, maxid1 = 0, maxid2 = 0, maxSzom = 0;

    for (int i = 0; i < enronNum; i++) {
        if (pontok[i].szomszedokszama >= (enronNum / 5) && maxEgyutthato < pontok[i].csomosodasiegyutthato) {
            maxEgyutthato = pontok[i].csomosodasiegyutthato;
            maxid1 = i;
        }
        if (maxSzom < pontok[i].szomszedokszama) {
            maxSzom = pontok[i].szomszedokszama;
            maxid2 = i;
        }
    }
    cout << "Legnagyobb egyutthatoval rendelkezo csucs , amelynek legalabb " << enronNum / 5 << " szomszeda van: " << nevsor[maxid1] << " erteke: " << pontok[maxid1].csomosodasiegyutthato << endl;
    cout << endl << "Legtobb szomszeddal rendelkezo szemely email cime " << nevsor[maxid2] << "  es szomszedjainak szama " << maxSzom;
    cout << endl;
}