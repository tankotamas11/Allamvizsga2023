#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
struct Pontok
{
	int	maxlepes=0;
	int osszlepes=0;
};
//csinalunk egy struturat aminek van egy oszege es egy maximalis tavolsaga.

int utakmeghatarozasa(int m[][9], int st, int fin, int mer, int jart[]) {
	
	
	int lepes = 0, t=-1, mint=-1;
	if (m[st][fin] >0) {
		return 1;
	}
	else {
		jart[st] = 1;
		for (int i = 0; i < mer; i++) {
			if (m[st][i] > 0 && jart[i]<1) {
				//cout << jart[i] << "***" << i+1<<"-"<<fin+1<<"   ";
				t=utakmeghatarozasa(m, i, fin, mer,jart);
				
				if ((mint > t && t>0)||(mint < 0 && t > 0)) { mint = t; }
			}
		}
		if (mint >0 ) {
			return mint + 1; }
		else {
			return -1; }
		
	}
}







int main() {
	int lepes = 0;
	//int jart[9] = { 0,0,0,0,0,0,0,0,0 };

	int matrix[9][9] = {
		{0,0,0,5,0,0,0,0,0},
		{3,0,1,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0},
		{0,0,7,0,0,0,0,0,0},
		{0,6,0,0,0,5,0,2,0},
		{0,0,0,0,0,0,3,0,0},
		{0,0,0,0,1,3,0,0,0},
		{0,0,0,0,0,0,0,0,4},
		{0,0,0,0,0,0,0,4,0}
	};
	Pontok pontok[9];
	//cout << matrix[8][7]<<" ";
	//cout << utakmeghatarozasa(matrix,1, 3, 9,jart);
	auto start = chrono::high_resolution_clock::now();
	int siker, seged1, seged2;
	for (int i = 0; i < 9; i++) {
		
		siker = 0; seged1 = 0; seged2 = 0;
		
		for (int j = 0; j < 9; j++) {
			int jart[9] = {0,0,0,0,0,0,0,0,0};
			if (i != j) {
				lepes = utakmeghatarozasa(matrix, i, j, 9, jart);
				
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
		if (siker == 8) {
			pontok[i].maxlepes = seged1;
			pontok[i].osszlepes = seged2;
			cout << "mindent bejart az " << i + 1<<" maxlepese: "<<pontok[i].maxlepes << endl;
		}
		else {
			pontok[i].maxlepes = 0;
			pontok[i].osszlepes = 0;
			cout << "nem mindent jart be az " << i + 1  << endl;
		}
		//cout << "A " << i + 1 << "  csucs maxlepese: " << pontok[i].maxlepes << endl;
	}
	auto end = std::chrono::high_resolution_clock::now();

	// Futásidő kiszámítása
	std::chrono::duration<double> duration = end - start;
	double seconds = duration.count();
	cout << "A program futásideje: " << seconds << " másodperc." << std::endl;
	


	return 0;
}
