//
//  CodonNumRep.cpp
//  
//
//  Created by Kim Ngo August 5, 2014.

//  Converts codons to numerical representations 0-63
//	Using binary system for codons: xx-xx-xx
//	A = 00
//	C = 01
//	G = 10
//	T = 11

#include "CodonNumRep.h"

#include <string>
#include <iostream>

using namespace std;

CodonNumRep :: CodonNumRep () {
	string codon_binary = "empty";
	int codon_num = -1;
	set_Codon_Binary(codon_binary);
	set_Codon_Number(codon_num);
}


CodonNumRep :: CodonNumRep (string& codon) {

	if (codon.size() == 3) {
		set_Codon(codon);
		Codon_Binary = Convert_String_Binary(codon);
		Codon_Number = Convert_Binary_Number(get_Codon_Binary());

	} else {
		string codon = "empty";
		int num = -1;
		set_Codon(codon);
		set_Codon_Binary(codon);
		set_Codon_Number(num);
	}
}

int CodonNumRep :: convert_codon_str_to_codon_num(const string& codon) {
	string binary = Convert_String_Binary(codon);
	int num = Convert_Binary_Number(binary);
	return num;
}

void CodonNumRep :: set_Codon(string& codon) {
	Codon = codon;
}
string CodonNumRep :: get_Codon() {
	return Codon;
}


void CodonNumRep :: set_Codon_Binary(string& binary) {
	Codon_Binary = binary;
}
string CodonNumRep :: get_Codon_Binary() {
	return Codon_Binary;
}

void CodonNumRep :: set_Codon_Number(int& num) {
	Codon_Number = num;
}
int CodonNumRep :: get_Codon_Number() {
	return Codon_Number;
}

void CodonNumRep :: print_Codon_Number() {
	cout << get_Codon() << "\t" << get_Codon_Binary() << "\t" << get_Codon_Number() << endl;
}

string CodonNumRep :: Convert_String_Binary(const string& codon) {

	string binary = "";
	for (int i = 0; i < codon.size(); i++) {
		if (codon[i] == 'A') binary += "00";
		else if (codon[i] == 'C') binary += "01";
		else if (codon[i] == 'G') binary += "10";
		else if (codon[i] == 'T') binary += "11";
	}
	return binary;
}


int CodonNumRep :: Convert_Binary_Number(const string& binary) {

// 100000 -> 32
// 010000 -> 16

// 001000 -> 8
// 000100 -> 4

// 000010 -> 2
// 000001 -> 1

	int num = 0;
	int i = 0;
	
// ##-XX-XX
	if (binary[i] == '0' && binary[i+1] == '0') num += 0;
	else if (binary[i] == '0' && binary[i+1] == '1') num += 16;
	else if (binary[i] == '1' && binary[i+1] == '0') num += 32;
	else if (binary[i] == '1' && binary[i+1] == '1') num += 48;
	
// XX-##-XX
	i += 2;
	if (binary[i] == '0' && binary[i+1] == '0') num += 0;
	else if (binary[i] == '0' && binary[i+1] == '1') num += 4;
	else if (binary[i] == '1' && binary[i+1] == '0') num += 8;
	else if (binary[i] == '1' && binary[i+1] == '1') num += 12;

// XX-XX-##
	i += 2;
	if (binary[i] == '0' && binary[i+1] == '0') num += 0;
	else if (binary[i] == '0' && binary[i+1] == '1') num += 1;
	else if (binary[i] == '1' && binary[i+1] == '0') num += 2;
	else if (binary[i] == '1' && binary[i+1] == '1') num += 3;
	
	return num;
}
