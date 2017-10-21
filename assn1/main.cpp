#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

int findLCSTD(string str1, int i, string str2, int j);
int findLCSTDHelper(string str1, string str2);

// global
vector<vector<int>> matrixTD;

//helper
int max(int a, int b) 
{
	return (a > b) ? a : b;
}

// top-down (memoized) pays a penalty
// in recursion overhead, but can be faster for problems where a
// reasonable fraction of the subproblems never get examined at all, so
// we can avoid computing them.

// bottom up iterative
int findLCSBU(string str1, int i, string str2, int j) 
{
	int len1 = i;
	int len2 = j;
	int matrix[len1+1][len2+1];

	// zero out whole array in case
	for (int p = 0; p <= len1; p++) {
		for (int q = 0; q <= len2; q++) {
			matrix[p][q] = 0;
		}	
	}

	// bottom up computation
	for (int p = 1; p <= len1; p++) {
		for (int q = 1; q <= len2; q++) {
			if (str1[p] == str2[q]) {
				matrix[p][q] = matrix[p-1][q-1]+1;
			} else if (matrix[p-1][q] >= matrix[p][q-1]){
				matrix[p][q] = matrix[p-1][q];
			} else {
				matrix[p][q] = matrix[p][q-1];
			}
		}
	}

	int lcs = matrix[i][j];

	// format output
	ofstream out;
	out.open("output.txt");

	if (str1.length() > 10 || str2.length() > 10) {
		out << lcs << endl;
	} else {
		// else print whole matrix & lcs
		for (int p = 0; p <= len1; p++) {
			for (int q = 0; q <= len2; q++) {
				out << matrix[p][q];
			}	
			out << endl;
		}
		out << lcs << endl;
	}
	out.close();
	return 0;
}


// recursive
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
	// format output
	ofstream out;
	out.open("output2.txt");
	out << lcs << endl;
	out.close();

	return 0;
}

// memoization (top down)
// running time is O(nm)
//  -we get to the second-to-last line at most n*m times
//  -at most 2nm recursive calls
int findLCSTD(string str1, int i, string str2, int j) 
{	
	int lcs;
	if (i == 0 || j == 0) return 0;
	if (matrixTD[i][j] != -1) return matrixTD[i][j];
	if (str1[i] == str2[j]) lcs = 1 + findLCSTD(str1, i-1, str2, j-1);
	else lcs = max(findLCSTD(str1, i-1, str2, j), findLCSTD(str1, i, str2, j-1)); 
	matrixTD[i][j] = lcs;
	return lcs;
}

int findLCSTDHelper(string str1, string str2)
{
	int len1 = str1.length();
	int len2 = str2.length();
	matrixTD.resize(len1+1, vector<int>(len2+1));
	
	// initialize all values to unknown
	for (int p = 0; p <= len1; p++) {
		for (int q = 1; q <= len2; q++) {
			matrixTD[p][q] = -1;
		}
	}	
	int lcs = findLCSTD(str1, len1, str2, len2);

	// format output
	ofstream out;
	out.open("output3.txt");
	out << lcs << endl;
	out.close();

	return 0;
}

int main(int argc, char **argv) 
{
	if (argc < 4) {
		cout << "Error: format requires 3 arguments -> ./program filex.txt filey.txt output.txt\n";
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

	if (strcmp(argv[3],"output.txt") == 0) 
	{ 
		auto start_time = high_resolution_clock::now();
		if (findLCSBU(str1, str1.length(), str2, str2.length()) != 0) {
			cout << "Error: findLCSBU() failed\n";
		}
		auto end_time = high_resolution_clock::now();
		auto runtime = duration_cast<chrono::nanoseconds>(end_time - start_time).count();

		ofstream out;
		out.open("output.txt", ios_base::app); //append runtime
		out << runtime << " nanoseconds" << endl;
		out.close();
	} 
	else if (strcmp(argv[3],"output2.txt") == 0) 
	{
		auto start_time = high_resolution_clock::now();
		if (findLCSRECHelper(str1, str2) != 0) {
			cout << "Error: findLCSREC() failed\n";
		}
		auto end_time = high_resolution_clock::now();
		auto runtime = duration_cast<chrono::nanoseconds>(end_time - start_time).count();

		ofstream out;
		out.open("output2.txt", ios_base::app); //append runtime
		out << runtime << " nanoseconds" << endl;
		out.close();
	} 
	else 
	{
		auto start_time = high_resolution_clock::now();
		findLCSTDHelper(str1, str2);
		auto end_time = high_resolution_clock::now();
		auto runtime = duration_cast<chrono::nanoseconds>(end_time - start_time).count();

		ofstream out;
		out.open("output3.txt", ios_base::app); //append runtime
		out << runtime << " nanoseconds" << endl;
		out.close();
	}
	return 0;
}	
