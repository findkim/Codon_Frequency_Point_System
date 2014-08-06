//
//  ExtractCF.h
//  
//
//  Created by Kim Ngo August 5, 2014.

//  Parses *.fasta.cf files in /afs/crc.nd.edu/user/k/kngo/orig_fasta directory
//	Creates a vector of codon frequency stored in numerical order of the codon's number representation


#ifndef EXTRACTCF_H
#define EXTRACTCF_H

#include <string>
#include <vector>

using namespace std;

class ExtractCF {

	public:
		ExtractCF();
		ExtractCF(const string&);
			// Orf codon freq filename;
			// Parses cf file to map codon to frequency
		vector<float> get_CF();
			// Returns vector of codon frequency
		string get_ORF();
			// Returns Orfeome the CF corresponds with
		void print_CF();
			// Prints Orfeome and it's corresponding codon frequencies
		static bool validFile(const string&);
			// Returns T if valid file w/"*.fasta.cf"

	private:
		vector<float> CF;
			// Vector that codon frequencies ordered by numerical codon num rep
		string ORF;
			// Orfeome the CF corresponds with
		void set_ORF(const string&);
		void set_CF(const vector<float>&);
		void extract_CF(const string&);
		vector<string> split(const string&, char);
		float convert_str_float(const string&);

};

#endif /* defined(____ExtractCF__) */
