//
//  CFPS.cpp
//  
//
//  Created by Kim Ngo August 5, 2014.

//  Calculates 9 codon window point system

#include "CFPS.h"
#include "CodonNumRep.h"

#include <map>
#include <string>
#include <iostream>
#include <fstream>

CFPS :: CFPS () {
}

CFPS :: CFPS (const vector<string>& homolog_group, const map<string, vector<float> >& ORF_CF) {

	vector<string>::const_iterator seq = homolog_group.begin();
	for (seq; seq != homolog_group.end(); ++seq) {
		string DNA = get_ORF_Sequence(*seq);
		if (DNA.length() % 3 == 0) {
			create_CF_Sequence(*seq, DNA, ORF_CF);
//			cout << *seq << endl << DNA << endl << endl;
		}
	}
}


// Returns sequences of codon freqs for homolog group
map<string, vector<float> > CFPS :: get_Seq_CF() {
	return seq_cf;
}
// Returns sequence of points for homolog group()
map<string, vector<int> > CFPS :: get_CFPS() {
	return cfps;
}


// Returns the orfeome that the sequence belongs to
string CFPS :: get_ORF_from_seqID (const string& seqID) {
	// format: >Drer|1001
	size_t end = seqID.find("|");
	string ORF = seqID.substr(1, end - 1); // Accounts for leading '>'
//	cout << ORF << endl << seqID << " " << seqID.size() << " " << end << endl;
	return ORF;
}


// Returns nucleotide sequence for sequence in homolog group
string CFPS :: get_ORF_Sequence (const string& seqID) {

	string ORF = get_ORF_from_seqID(seqID);
	string filename = "/afs/crc.nd.edu/group/NDBL/data/rcclust/ultimate/orig_fasta/" + ORF + ".fasta";
	
	string line;
	string DNA;
	ifstream file(filename.c_str());
	while (getline(file, line)) {
		if (line == seqID) {
			getline(file, DNA);
			break;
		}
	}
	return DNA;
}


// SEQID, nucleotide sequence, map of orfeomes & its cf
void CFPS :: create_CF_Sequence(const string& seqID, const string& DNA, const map<string, vector<float> >& ORF_CF) {

	string orf = get_ORF_from_seqID(seqID);

	if (ORF_CF.find(orf) != ORF_CF.end()) {
//		cout << orf << endl;
	
		vector<float> orf_cf = ORF_CF.find(orf)->second;
		vector<float> cf (DNA.size()/3.0,0);
		vector<float>::iterator cf_it = cf.begin();
		for (int i = 0; i < DNA.size(); i += 3, ++cf_it) {
			string codon = DNA.substr(i, 3);
			int codon_num = CodonNumRep::convert_codon_str_to_codon_num(codon);
			*cf_it = orf_cf[codon_num];
//			cout << codon << " " << codon_num << " " << orf_cf[codon_num] << "\t";
		}
//		cout << endl;
//		for (int i = 0; i < cf.size(); i++)
//			cout << cf[i] << " ";
//		cout << endl << endl;
		seq_cf.insert(pair<string, vector<float> >(seqID, cf));
	}
}


// Calculates points for 9 codon windows and places in a parallel vector
void CFPS :: codon_frequency_point_system (const map<string, vector<float> >& seq_cf) {

	map<string, vector<int> > seq_pts;
	
	cfps = seq_pts;
}
			
