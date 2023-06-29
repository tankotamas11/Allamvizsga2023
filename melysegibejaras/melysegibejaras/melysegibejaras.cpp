// melysegibejaras.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

// A gráf osztály definíciója
class Graph {
public:
    Graph(int n) : n(n), adj(n, vector<int>()) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        //adj[v].push_back(u);
    }

    void dfs(int u, vector<bool>& visited, vector<int>& component) {
        visited[u] = true;
        component.push_back(u);
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v, visited, component);
            }
        }
    }

    int count_connected_components(vector<vector<int>>& components) {
        vector<bool> visited(n, false);
        for (int u = 0; u < n; u++) {
            if (!visited[u]) {
                vector<int> component;
                dfs(u, visited, component);
                components.push_back(component);
            }
        }
        return components.size();
    }

private:
    int n;
    vector<vector<int>> adj;
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

int nevsorban(string* nevsor,int meret, string nev) {
    for (int i = 0; i < meret; i++) {
        if (nevsor[i] == nev) {
            return i;
        }
    }
    return -1;
}
struct Pontok
{
    int	maxlepes = 0;
    int osszlepes = 0;
};

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

int main()
{

    ifstream infile("enronosok.txt");
    if (!infile.is_open()) {
        cout << "Hiba a fajl megnyitasakor!";
        return 1;
    }

    string nevek;
    int size = 0;
    while (getline(infile, nevek)) {
        size++;
    }
    string* nevsor = new string[size];
    infile.clear();
    infile.seekg(0, ios::beg);
    int i = 0;
    while (getline(infile, nevek)) {
        nevsor[i] = nevek;
        i++;
    }
    infile.close();
    int namelistsize = i;
    int matrix[50][50];
    for (int m = 0; m < 50; m++) {
        for (int n = 0; n < 50; n++) {
            
                matrix[m][n] = 0;
            
            

        }
        
    }

    //eddig beolvastam a nevsort
    //johet a kapcsolatok tarolasa es a graf felepitese

    ifstream f("kapcsolatok.txt");
    if (!f.is_open()) {

        cerr << "Hiba a masodik fajl megnyitasakor!";
        return 1;
    }
    string str1, str2, honapString;
    int nap, ev;
    Kapcsolat kapcsolatok[10000];//88975
    i = 0;
    int j = 0;
    Graph g(size);
    int seged1, seged2;
    //while (f >> str1 >> str2 >> nap >> honapString >> ev) // soronkénti beolvasás
    while (i < 80000) {
        f >> str1 >> str2 >> nap >> honapString >> ev; // soronkénti beolvasás

        kapcsolatok[j].nev1 = str1;
        kapcsolatok[j].nev2 = str2;
        kapcsolatok[j].nap = nap;
        kapcsolatok[j].honap = honapToInt(honapString);
        kapcsolatok[j].ev = ev;
        seged1 = nevsorban(nevsor, size, kapcsolatok[j].nev1);
        seged2 = nevsorban(nevsor, size, kapcsolatok[j].nev2);
        if (seged1 >= 0 && seged2 >= 0) {
            g.add_edge(seged1, seged2);
            //cout << matrix[seged1][seged2]<<" ";
            matrix[seged1][seged2]++;
            

            j++;
        }
        i++;
    }
    //88 975 adat

    //Graph g(5);
    //g.add_edge(0, 1);


    vector<vector<int>> components;
    int num_components = g.count_connected_components(components);

    // Eredmények kiírása
    cout << "Number of connected components: " << num_components << endl;
    for (int i = 0; i < num_components; i++) {
        cout << "Component " << i + 1 << " vertices: ";
        for (int v : components[i]) {
            cout << v << " ";  
        }
        cout << endl;
    }

    cout << endl;
    auto start = chrono::high_resolution_clock::now();
    Pontok pontok[50];
    int lepes = 0;
    int siker = 0;
    for (int i = 0; i < namelistsize; i++) {
        siker = 0; seged1 = 0; seged2 = 0;
        for (int j = 0; j < namelistsize; j++) {
            int jart[50] = {0};
            if (i != j) {
                lepes = utakmeghatarozasa(matrix, i, j, namelistsize, jart);

                if (lepes >= 0) {
                    siker++;
                    if (lepes > seged1) {
                        seged1 = lepes;
                    }
                    seged2 = seged2 + lepes;
                }
            }
        }
        cout << endl;
        if (siker == namelistsize-20) {
            pontok[i].maxlepes = seged1;
            pontok[i].osszlepes = seged2;
            cout << "mindent bejart a(z) " << i + 1 << " maxlepese: " << pontok[i].maxlepes << endl;
        }
        else {
            pontok[i].maxlepes = 0;
            pontok[i].osszlepes = 0;
            cout << "nem mindent jart be a(z) " << i + 1 << "sikeresbejarasa:"<<siker<<endl;
        }        
    }
    auto end = chrono::high_resolution_clock::now();

    // Futásidő kiszámítása
    chrono::duration<double> duration = end - start;
    double seconds = duration.count();
    cout << "A program futasideje: " << seconds << " másodperc." <<endl;

    for (int m = 0; m < namelistsize; m++) {
        for (int n = 0; n < namelistsize ; n++){
            cout << matrix[m][n]<<" ";
           
        }
        cout << endl;
    }
    cout << endl;


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
