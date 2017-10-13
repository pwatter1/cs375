#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>


using namespace std;


int findLCSBU(string str1, int i, string str2, int j) 
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

int findLCSREC(string str1, int i, string str2, int j)
{
	if (i == 0 || j == 0) return 0;
	if (str1[i] == str2[j]) return 1 + findLCSREC(str1, i-1, str2, j-1);
	else return max(findLCSREC(str1, i, str2, j-1), findLCSREC(str1, i-1, str2, j));
}

// helper
int findLCSRECHelper(string str1, string str2)
{
	int lcs = findLCSREC(str1, str1.length(), str2, str2.length());
	string rt = "O(n^2)";

	// format output
	ofstream out;
	out.open("output2.txt");
	out << lcs << endl;
	out << rt << endl;
	out.close();

	return 0;
}

//helper
int max(int a, int b) 
{
	return (a < b) ? b : a;
}

int findLCSTD(string str1, int i, string str2, int j) 
{



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
	ifstream iny(argv[2]);
	
	if (!inx) {
		cout << "Error: cannot open %s\n" << argv[1];
		return -1;
	}
	if (!iny) {
		cout << "Error: cannot open %s\n" << argv[2];
		return -1;
	}

	inx >> str1;
	iny >> str2;

	if (strcmp(argv[3],"output.txt") == 0) { 
		if (findLCSBU(str1, str1.length(), str2, str2.length()) != 0) {
			cout << "Error: findLCSBU() failed\n";
		}
	} else if (strcmp(argv[3],"output2.txt") == 0) {
		if (findLCSRECHelper(str1, str2) != 0) {
			cout << "Error: findLCSREC() failed\n";
		}
	} else {
		if (findLCSTD(str1, str1.length(), str2, str2.length()) != 0) {
			cout << "Error: findLCSTD() failed\n";
		}
	}
	return 0;
}	
