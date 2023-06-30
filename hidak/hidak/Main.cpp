#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Ut {
    bool van_e=false;
    int utak[50][2]={0};
    int hossz = 0;
};
struct Elek {
    string tipus;
    int nev1Id=0;
    int nev2Id=0;
    double atfedesifoka = 0;
    int koztessegiFok = 0;
};
struct osszEl {
    Elek elek[5000];
    int hossz;
};


int nevsorban(string* nevsor, int meret, string nev) {
    for (int i = 0; i < meret; i++) {
        if (nevsor[i] == nev) {
            return i;
        }
    }
    return -1;
}
double atfedes(int matrix[][50], int elso, int masodik, int mer) {
    double osszes = 0, kozos=1;
    bool volt = false;
    for (int i = 0; i < mer; i++) {
        volt = false;
        if (matrix[elso][i] != 0 && i != masodik) {
            osszes++;
            volt == true;
        }
        if (matrix[masodik][i] != 0 && i != elso ) {
            osszes++;
            if (volt) {
                kozos++;
                osszes--;
           }
        }       
    }
    if (kozos == 0) { return 0;}
    else { return kozos/osszes ;}
}
int utakmeghatarozasa(int m[][50], int st, int fin, int mer, int jart[]) {


    int  t = -1, mint = -1;
    if (m[st][fin] > 0) {
        return 1;
    }
    else {
        jart[st] = 1;
        for (int i = 0; i < mer; i++) {
            if (m[st][i] > 0 && jart[i] < 1) {
                t = utakmeghatarozasa(m, i, fin, mer, jart);

               
                if ((mint > t && t > 0) || (mint < 0 && t > 0)) { mint = t; }
            }
        }
        if (mint > 0) {
            return mint + 1;
        }
        else {
            return -1;
        }

    }
}

Ut  pontosut(int matrix[][50], int m, int st, int fin,int jart[]) {
    Ut ut, segedUt;
     
    if (matrix[st][fin] > 0) {
        ut.utak[ut.hossz][0] = st;
        ut.utak[ut.hossz][1] = fin;
        ut.van_e = true;
        ut.hossz = 1;
        return ut;
    }
    else {
        jart[st] = 1;
        int aktualis = 0;
        for (int i = 0; i < m; i++) {
            if (matrix[st][i] > 0 && jart[i] < 1) {
                ut = pontosut(matrix, m, i, fin,  jart);
                if (segedUt.van_e == false && ut.van_e == true) {
                    segedUt.van_e = true;
                    segedUt.hossz = ut.hossz;
                    for (int i = 0; i < ut.hossz; i++) {
                        segedUt.utak[i][0] = ut.utak[i][0];
                        segedUt.utak[i][1] = ut.utak[i][1];
                        aktualis = i;
                    }
                }
                if (segedUt.van_e == true && ut.van_e == true && segedUt.hossz > ut.hossz) {
                    segedUt.hossz = ut.hossz;
                    for (int i = 0; i < ut.hossz; i++) {
                        segedUt.utak[i][0] = ut.utak[i][0];
                        segedUt.utak[i][1] = ut.utak[i][1];
                        aktualis = i;
                    }
                }
            }
        }
        if (segedUt.hossz> 0) {
            segedUt.utak[segedUt.hossz][0] = st;
            segedUt.utak[segedUt.hossz][1] = aktualis;
            segedUt.hossz++;
            return segedUt;
        }
        else {
            Ut s;
            return s;
        }
    }
}
int legkisebbEl(int matrix[][50], Elek elek[], int elszam) {
    int min = 20000, minId=0;
    for (int i = 0; i < elszam; i++) {
        if (matrix[elek[i].nev1Id][elek[i].nev2Id] < min && matrix[elek[i].nev1Id][elek[i].nev2Id] != 0) {
            minId = i;
            min = matrix[elek[i].nev1Id][elek[i].nev2Id];
        }
    }
    return minId;
}
int legnagyobbEl2(int matrix[][50], Elek elek[], int elszam) {
    int max = 0, maxId = 0;
    for (int i = 0; i < elszam; i++) {
        if (matrix[elek[i].nev1Id][elek[i].nev2Id] > max && matrix[elek[i].nev1Id][elek[i].nev2Id] != 0) {
            maxId = i;
            max = matrix[elek[i].nev1Id][elek[i].nev2Id];
        }
    }
    return maxId;
}
int legnagyobbEl(int matrix[][50], Elek elek[], int elszam) {
    int max = -1, minId = 0;
    for (int i = 0; i < elszam; i++) {
        if (elek[i].koztessegiFok > max && matrix[elek[i].nev1Id][elek[i].nev2Id] != 0) {
            minId = i;
            max = elek[i].koztessegiFok;
        }
    }
    return minId;
}

int ElIndex(Elek elek[], int size, int elso, int masodik) {
    for (int i = 0; i < size; i++) {
        if ((elek[i].nev1Id == elso && elek[i].nev2Id == masodik) || (elek[i].nev2Id == elso && elek[i].nev1Id == masodik)) {
            return i;
        }
    }
}
osszEl koztessegifokszamolas(int enronNum, int matrix[][50], Elek elek[], int elekszama) {
    Elek* el = new Elek[elekszama];
    for (int i = 0; i < elekszama; i++) {
        el[i].atfedesifoka = elek[i].atfedesifoka;
        el[i].nev1Id = elek[i].nev1Id;
        el[i].nev2Id = elek[i].nev2Id;
        el[i].koztessegiFok = elek[i].koztessegiFok;
        el[i].tipus = elek[i].tipus;
    }
    int s = 0;
    for (int i = 0; i < enronNum - 1; i++) {
        for (int j = i + 1; j < enronNum; j++) {
            int jart[50] = { 0 };
            Ut ut = pontosut(matrix, enronNum, i, j, jart);
            if (ut.van_e) {
                for (int k = 0; k < ut.hossz; k++) {
                    s = ElIndex(el, elekszama, ut.utak[k][0], ut.utak[k][1]);
                    el[s].koztessegiFok++;
                }
            }
        }
    }
    osszEl eredmeny;
    for (int i = 0; i < elekszama; i++) {
        eredmeny.elek[i].atfedesifoka = el[i].atfedesifoka;
        eredmeny.elek[i].nev1Id = el[i].nev1Id;
        eredmeny.elek[i].nev2Id = el[i].nev2Id;
        eredmeny.elek[i].koztessegiFok = el[i].koztessegiFok;
        eredmeny.elek[i].tipus = el[i].tipus;
    }
    eredmeny.hossz = elekszama;

    return eredmeny;
}

int komponensekSzama(int matrix[][50], int meret,int jart[]) {
    int i = 0, bejart = 0, komp = 0;
    int hasznalt[50] = { 0 };
    while (i < meret && bejart < meret) {
        if (hasznalt[i] == 0) {
            hasznalt[i] =  1;
            bejart++;

            for (int j = 0; j < meret; j++) {
                if (utakmeghatarozasa(matrix, i, j, meret, hasznalt) >0 && hasznalt[j] == 0) {
                    hasznalt[j] =  1;
                    bejart++;
                }
            }
            komp++;
            i++;
        }
        else {
            i++;
        }
    }
    return komp;
}

int main(){
	int enronNum;
    do {
        cout << "Kerem adja meg hany szemelybol alljon a graf (1-50 kozotti erteket)" << endl;
        cin >> enronNum;
    } while (enronNum > 50 && enronNum < 1);
    ifstream f("enronosok.txt");
    if (!f.is_open()) {
        cout << "Hibas fajlmegnyitas!";
        return 1;
    }
    string nevek;
    int size = 0;
    while (getline(f, nevek)) {
        size++;
    }
    string* osszesnev = new string[size];
    f.clear();
    f.seekg(0, ios::beg);
    int i = 0;
    while (getline(f, nevek)) {
        osszesnev[i] = nevek;
        i++;
    }
    f.close();//megtortent a beolvasasa a neveknek , most kivalasztjuk a szukseges neveket.
    string* nevsor = new string[enronNum];
    bool helyes = false;
    int kezdet = 0;
    int* idk = new int[enronNum];
    //
    do {
        // kezdet = rand() % size;
        kezdet = 1000;
        if (kezdet + enronNum < size) {
            helyes = true;
        }
    } while (!helyes);
    for (int i = kezdet; i < kezdet + enronNum; i++) {
        nevsor[i - kezdet] = osszesnev[i];
        //cout << nevsor[i - kezdet] << endl;
    }
    ifstream g("kapcsolatok.txt");
    if (!g.is_open()) {
        cout << "Hibas fajlmegnyitas!";
        return 2;
    }
    
    string str1, str2, honapStr;
    int nap, honap, ev, segedId1, segedId2;
    
    int matrix[50][50];
    for (int m = 0; m < 50; m++) {
        for (int n = 0; n < 50; n++) {

            
            matrix[m][n] = 0;
        }
    }
    int db = 0, t = 0;
    while (!g.eof()) {
        g >> str1 >> str2 >> nap >> honapStr >> ev;
        segedId1 = nevsorban(nevsor, enronNum, str1);
        segedId2 = nevsorban(nevsor, enronNum, str2);
        if (segedId1 >= 0 && segedId2 >= 0 && segedId1 != segedId2) {
            db++;
            if (matrix[segedId1][segedId2] == 0) {
                t++;
            }
            matrix[segedId1][segedId2]++;
            matrix[segedId2][segedId1]++;

        }
    }
    cout << db << " : " << t << endl;
    Elek* elek = new Elek[t];
    int elekszama = t;
    t = 0;
    int p = 0;
    int uthossz=0;
    
    for (int i = 0; i < enronNum-1; i++) {
        for (int j = i + 1; j < enronNum; j++) {
            
            if (matrix[i][j] != 0) {
                int jart[50] = { 0 };
                p = matrix[i][j];
                matrix[i][j] = 0;
                matrix[j][i] = 0;
                elek[t].nev1Id = i;
                elek[t].nev2Id = j;
                uthossz = utakmeghatarozasa(matrix, i, j, enronNum, jart);  
                if (uthossz < 0) {
                    elek[t].tipus = (string)"hid";
                    elek[t].atfedesifoka = 0;
                }
                else {
                    if (uthossz > 2) {
                        elek[t].tipus =(string)"lokalishid";
                        elek[t].atfedesifoka = atfedes(matrix, i, j, enronNum);
                    }
                    else {
                        elek[t].tipus = (string)"el";
                        elek[t].atfedesifoka = atfedes(matrix, i, j, enronNum);
                    }
                }
               
                cout << "A(z) " << i << "-" << j << "  tipusa: " << elek[t].tipus << " es szomszedsag atfedesi foka:  "<< elek[t].atfedesifoka <<endl;
                matrix[i][j] = p;
                matrix[j][i] = p;
                t++;
            }
        }
    }
    //koztessegifok meghatarozasa
    int s = 0;
    for (int i = 0; i < enronNum-1; i++) {
        for (int j = i + 1; j < enronNum; j++) {
            int jart[50] = { 0 };
            Ut ut = pontosut(matrix, enronNum, i, j, jart);
            for (int k = 0; k < ut.hossz; k++) {
                s = ElIndex(elek, elekszama, ut.utak[k][0], ut.utak[k][1]);
                elek[s].koztessegiFok++;
            }
        }
    }
    for (int i = 0; i < elekszama; i++) {
        cout << elek[i].nev1Id << "-" << elek[i].nev2Id << " el koztessegi-foka: " << elek[i].koztessegiFok << endl;
    }
    

    //ellenorizzuk hogy ha a legkissebb sulyu elet toroljuk a grafbol akkor szetesik e az es ha igen hany alkalommal kell ezt eljatszodni az elso szetesesig.
    int szamlalo = 1, sorszam = 0, szetesesSzamlalo = 0;
    bool szetesett = false;
    int matrix2[50][50] = { 0 };
    int girvan[50][50] = { 0 };
    for (int i = 0; i < enronNum; i++) {
        for (int j = 0; j < enronNum; j++) {
            matrix2[i][j] = matrix[i][j];
            girvan[i][j] = matrix[i][j];
            
        }
    }
    ///
    ofstream v("sulyokszerintnovekvo.txt");
    v << elekszama << endl;
    for (int i = 0; i < elekszama; i++) {
        v << elek[i].nev1Id << " " << elek[i].nev2Id << endl;
    }

    int* sulyokkal = new int[elekszama];
    int segedSzam = elekszama;
    int kompSzam=0;

    while (!szetesett) {
        int jart[50] = { 0 };
        sorszam = legkisebbEl(matrix, elek, elekszama);
        for (int i = 0; i < elekszama; i++) {
            if (matrix[elek[sorszam].nev1Id][elek[sorszam].nev2Id] == matrix[elek[i].nev1Id][elek[i].nev2Id]) {
                v << szetesesSzamlalo << " " << elek[i].nev1Id << " " << elek[i].nev2Id << endl;
                matrix[elek[i].nev1Id][elek[i].nev2Id] = 0;
                matrix[elek[i].nev2Id][elek[i].nev1Id] = 0;
            }
        }
        int jart2[50] = { 0 };
        if (utakmeghatarozasa(matrix, elek[sorszam].nev1Id, elek[sorszam].nev2Id, enronNum, jart) == -1) {
            //int jart2[50] = {0};
            kompSzam = komponensekSzama(matrix, enronNum, jart2);
            //cout << "654654::" << kompSzam << endl;
            if (szetesesSzamlalo != 0) {
                if (sulyokkal[szetesesSzamlalo - 1] != kompSzam) {
                    sulyokkal[szetesesSzamlalo] = kompSzam;
                    szetesesSzamlalo++;
                    //cout << szetesesSzamlalo - 1 << " /*- " << kompSzam << endl;
                }
            }
            else {
                sulyokkal[szetesesSzamlalo] = kompSzam;
                szetesesSzamlalo++;
                

            }
        }
        else
        {
            szamlalo++;
        }
        if (kompSzam == enronNum) {
            szetesett = true;
        }

    }
    ///
   
    ofstream outF("sulyszerintitorles.txt");
    outF << szetesesSzamlalo << endl;
    for (int i = 0; i < szetesesSzamlalo; i++) {
        outF << sulyokkal[i] << endl;
        cout << i << " -> " << sulyokkal[i] << endl;
    }
    //csokkenobe
    ofstream v2("sulyokszerintcsokeno.txt");
    v2 << elekszama << endl;
    for (int i = 0; i < elekszama; i++) {
        v2 << elek[i].nev1Id << " " << elek[i].nev2Id << endl;
    }
    int* sulyokkal2 = new int[elekszama];
    segedSzam = elekszama;
    kompSzam = 0;
    szetesesSzamlalo = 0;
    szetesett = false;

    while (!szetesett) {
        int jart[50] = { 0 };
        sorszam = legnagyobbEl2(matrix2, elek, elekszama);
        for (int i = 0; i < elekszama; i++) {
            if (matrix2[elek[sorszam].nev1Id][elek[sorszam].nev2Id] == matrix2[elek[i].nev1Id][elek[i].nev2Id] && matrix2[elek[sorszam].nev1Id][elek[sorszam].nev2Id]!=0) {
                v2 << szetesesSzamlalo << " " << elek[i].nev1Id << " " << elek[i].nev2Id << endl;
                matrix2[elek[i].nev1Id][elek[i].nev2Id] = 0;
                matrix2[elek[i].nev2Id][elek[i].nev1Id] = 0;
                
            }
        }
        int jart2[50] = { 0 };
        if (utakmeghatarozasa(matrix2, elek[sorszam].nev1Id, elek[sorszam].nev2Id, enronNum, jart) == -1) {
            
            kompSzam = komponensekSzama(matrix2, enronNum, jart2);
            
            if (szetesesSzamlalo != 0) {
                if (sulyokkal2[szetesesSzamlalo - 1] < kompSzam ) {
                    sulyokkal2[szetesesSzamlalo] = kompSzam;
                    szetesesSzamlalo++;
                    
                }
            }
            else {
                sulyokkal2[szetesesSzamlalo] = kompSzam;
                szetesesSzamlalo++;

            }
        }
        else{
            szamlalo++;
        }
        if (kompSzam == enronNum) {
            szetesett = true;
        }
    }
    v.close();
    v2.close();
    outF << szetesesSzamlalo << endl;
    for (int i = 0; i < szetesesSzamlalo; i++) {
        outF << sulyokkal2[i] << endl;
        cout << i << "* -> " << sulyokkal2[i] << endl;
    }
    outF.close();

    ofstream viz("girvanvizualizalas.txt");
    viz << elekszama<<endl;
    for (int i = 0; i < elekszama; i++) {
        viz << elek[i].nev1Id<<" "<< elek[i].nev2Id << endl;
    }


    //Girwan-Newman modszer alapjan 
    szetesett = false;
    szamlalo = 0;
    int meglevoElekSzama = elekszama;
    int* komponensek = new int[enronNum];
    while (meglevoElekSzama > 0) {
        osszEl osszesel;
        osszesel = koztessegifokszamolas(enronNum, matrix, elek, elekszama);
        for (int i = 0; i < elekszama; i++) {
            elek[i].koztessegiFok = osszesel.elek[i].koztessegiFok;
        }
        szetesett = false;

        while (!szetesett) {
            int jart[50] = { 0 };
            sorszam = legnagyobbEl(girvan, elek, elekszama);
            for (int i = 0; i < elekszama; i++) {
                if (elek[i].koztessegiFok == elek[sorszam].koztessegiFok) {
                    meglevoElekSzama--;
                    viz<<szamlalo<<" "<< elek[i].nev1Id << " " << elek[i].nev2Id << endl;
                    girvan[elek[i].nev1Id][elek[i].nev2Id] = 0;
                    girvan[elek[i].nev2Id][elek[i].nev1Id] = 0;
                    if (utakmeghatarozasa(girvan, elek[sorszam].nev1Id, elek[sorszam].nev2Id, enronNum, jart) == -1) {
                        szetesett = true;
                        int jart2[50] = { 0 };
                        int kompszama = komponensekSzama(girvan, enronNum, jart2);
                        if (szamlalo == 0) {
                            komponensek[szamlalo] = kompszama;

                            szamlalo++;
                        }
                        if (komponensek[szamlalo - 1] != kompszama) {
                            komponensek[szamlalo] = kompszama;
                            szamlalo++;
                        }                       
                    }                    
                }
            }       
        }
    }
    viz.close();
    cout << "A Girvan-Newman modszer eseteben minden el " << szamlalo << ". alkalommal elvegzett koztessegifok szamitas utan torlodott ki. " << endl;
    ofstream out2("girvanmodszerrel.txt");
    out2 << szamlalo<<endl;
    for (int i = 0; i < szamlalo; i++) {
        cout << i+1 << ".dik torlesnel komponensek szama: " << komponensek[i]<<endl;
        out2<< komponensek[i] << endl;
     }
}