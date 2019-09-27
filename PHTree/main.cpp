#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <bitset>

#include <ctime>
#include <ratio>
#include <chrono>

#include "phtree.h"


using namespace std;
typedef vector<vector<bool>> m_bool;
typedef vector<vector<vector<bool>>> c_bool;


c_bool randM(int c, int f) {
	srand(time(0));
	c_bool rptaP;

	for (int i = 0; i < c; i++) {
		m_bool rpta;
		for (int j = 0; j < f; j++) {
			bitset<16> tem((rand() % 65535));

			vector<bool> tv;
			for (int y = 0; y < 16; y++) {
				tv.push_back(tem[y]);				
			}
			
			rpta.push_back(tv);
		}
		rptaP.push_back(rpta);
	}

	return rptaP;
}


void prv(c_bool &a) {
	for (int c = 0; c < a.size(); c++) {
		for (int i = 0; i < a[0].size(); i++) {
			for (int j = 0; j < a[0][0].size(); j++) {
				cout << a[c][i][j];
			}
			cout << endl;
		}
		cout << "----------" << endl;
	}
}

int main() {

	using namespace std::chrono;

	c_bool a = randM(10000,100);
	cout << "matriz" << endl;

	PHtree arbol(100 ,a[0]);

	cout << "comenzo" << endl;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	
	for (int i = 1; i < a.size(); i++) {
		
		arbol.insert(&a[i]);
	}
	
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "It took me 1 " << time_span.count() << " seconds.";
	

	

	high_resolution_clock::time_point t3 = high_resolution_clock::now();

	arbol.knn(&a[10], 100);

	high_resolution_clock::time_point t4 = high_resolution_clock::now();

	duration<double> time_span2 = duration_cast<duration<double>>(t4 - t3);

	std::cout << "It took me 2" << time_span.count() << " seconds.";
	std::cout << std::endl;



	system("pause");
	return 0;
}