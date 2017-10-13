#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>


using namespace std;


int findLCS(string str1, int i, string str2, int j) 
{
	int len1 = str1.length();
	int len2 = str2.length();
	int matrix[len1+1][len2+1];

	// initialize first row and col
	for (int p = 1; p <= len1; p++) matrix[p][0] = 0;
	for (int p = 0; p <= len2; p++) matrix[0][p] = 0;

	for (int p = 1; p <= len1; p++) {
		for (int q = 1; q <= len2; q++) {
			if (str1[p] == str2[q]) {
				matrix[p][q] = (matrix[p-1][q-1])+1;
			} else if (matrix[p-1][q] >= matrix[p][q-1]) {
				matrix[p][q] = matrix[p-1][q];
			} else {
				matrix[p][q] = matrix[p][q-1];
			}
		}
	}

	int lcs = matrix[i][j];
	string rt = "O(m n)";

	ofstream out;
	out.open("output.txt");

	// format output
	if (str1.length() > 10 || str2.length() > 10) {
		out << lcs << endl;
		out << rt << endl;
	} else {
		for (int p = 0; p <= len1; p++) {
			for (int q = 1; q <= len2; q++) {
				out << matrix[p][q];
			}	
			out << endl;
		}
		out << lcs << endl;
		out << rt << endl;
	}

	out.close();
	return 0;
}


int main(int argc, char **argv) 
{
	if (argc < 3) {
		cout << "Error: format requires 2 files -> ./program file.txt filey.txt\n";
		return -1;
	}

	string str1, str2;

	ifstream inx(argv[1]);
	if (!inx) 
	{
		cout << "Error: cannot open %s\n" << argv[1];
		return -1;
	}
	inx >> str1;

	ifstream iny(argv[2]);
	if (!iny) 
	{
		cout << "Error: cannot open %s\n" << argv[2];
		return -1;
	}
	iny >> str2;

	findLCS(str1, str1.length(), str2, str2.length());

	return 0;
}	
