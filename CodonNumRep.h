//
//  CodonNumRep.h
//  
//
//  Created by Kim Ngo August 5, 2014.

//  Converts codons to numerical representations 0-63
//	Using binary system for codons: xx-xx-xx
//	A = 00
//	C = 01
//	G = 10
//	T = 11

#ifndef CODONNUMREP_H
#define CODONNUMREP_H

#include <string>

using namespace std;

class CodonNumRep {

	public:
		CodonNumRep();
		CodonNumRep(string&);		// Codon string
			// Converts codon string and converts to numerical reppresentation 0-63
		string get_Codon();
			// Returns codon string
		string get_Codon_Binary();
			// Returns binary rep of codon
		int get_Codon_Number();
			// Returns number that represents codon
		void print_Codon_Number();
			// Prints codon and it's number
		static int convert_codon_str_to_codon_num(const string&);

	private:
		int Codon_Number;
		string Codon_Binary;
		string Codon;
		void set_Codon(string&);
		void set_Codon_Binary(string&);
		void set_Codon_Number(int&);
		static string Convert_String_Binary(const string&);
		static int Convert_Binary_Number(const string&);
};

#endif /* defined(____CodonNumRep__) */
