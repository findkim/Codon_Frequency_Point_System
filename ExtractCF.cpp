//
//  ExtractCF.cpp
//  
//
//  Created by Kim Ngo August 5, 2014.

//  Parses *.fasta.cf files in /afs/crc.nd.edu/user/k/kngo/orig_fasta directory
//	Creates a vector of codon frequency stored in numerical order of the codon's number representation

#include "ExtractCF.h"
#include "CodonNumRep.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

const string DIRECTORY = "/afs/crc.nd.edu/group/NDBL/data/rcclust/ultimate/orig_fasta/";

ExtractCF :: ExtractCF() {

	vector<float> init_v (64,0);
	set_CF(init_v);
	string orf = "NA";
	set_ORF(orf);
}

// Parses cf file to map codon to frequency
ExtractCF :: ExtractCF(const string& filename) {

	vector<float> init_v (64,0);
	set_CF(init_v);
	
	if (validFile(filename)) {
		string extension = ".fasta.cf";
		int length = filename.size() - DIRECTORY.size() - extension.size();
		string orf = filename.substr(DIRECTORY.size(), length);
		set_ORF(orf);
		extract_CF(filename);

	} else {
		string orf = "NA";
		set_ORF(orf);
	}

}

void ExtractCF :: set_CF(const vector<float>& cf) {
	CF = cf;
}
vector<float> ExtractCF :: get_CF() {
	return CF;
}
void ExtractCF :: set_ORF(const string& orf) {
	ORF = orf;
}
string ExtractCF :: get_ORF() {
	return ORF;
}


// Prints Orfeome and it's corresponding codon frequencies
void ExtractCF :: print_CF() {

	cout << get_ORF() << endl;
	vector<float> cf = get_CF();
	for (int i = 0; i < cf.size(); i++) {
		cout << i << "\t" << cf[i] << endl;
	}
}


// Returns T if valid file w/"*.fasta.cf"
bool ExtractCF :: validFile(const string& filename) {
	size_t found = filename.find(".fasta.cf");
	if (found != string::npos) {
		return true;
	} else {
		return false;
	}
}
			

// Returns a vector of elements in string split by a delimiter
vector<string> ExtractCF :: split(const string& str, char delim) {
	stringstream ss(str);
	string item;
	vector<string> elements;
	while (getline(ss, item, delim)) {
		elements.push_back(item);
	}
	return elements;
}

float ExtractCF :: convert_str_float(const string& str) {
	stringstream ss;
	float f;
	ss << str;
	ss >> f;
	return f;
}

void ExtractCF :: extract_CF(const string& filename) {

	ifstream file(filename.c_str());
	string line;
	while (getline(file, line)) {

    vector<string> elements = split(line, '\t');
    for (int i = 0; i < elements.size(); i++) {
    	string codon = elements[i].substr(0,3);
    	CodonNumRep cnp(codon);
    	int codon_num = cnp.get_Codon_Number();
    	size_t end = elements[i].find("(");
    	CF[codon_num] = convert_str_float(elements[i].substr(3,end-5));
    }
	}
}
