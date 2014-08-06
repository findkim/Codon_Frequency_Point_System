//
//  CFPS.h
//  
//
//  Created by Kim Ngo August 5, 2014.

//  Calculates 9 codon window point system

#ifndef CFPS_H
#define CFPS_H

#include <vector>
#include <string>
#include <map>

using namespace std;

class CFPS {

	public:
		CFPS();
		CFPS(const vector<string>&, const map<string, vector<float> >&);
			// Sequences in homolog group, map of Orfeome & its codon frequencies
			// Calculates point system
		map<string, vector<float> > get_Seq_CF();
			// Returns sequences of codon freqs for homolog group
		map<string, vector<int> > get_CFPS();
			// Returns sequences of points for homolog group

	private:
		map<string, vector<float> > seq_cf;
			// Sequences of codon freqs for homolog group
		map<string, vector<int> > cfps;
			// Sequences of points for homolog group
		string get_ORF_from_seqID(const string&);
			// Returns the orfeome that the sequence belongs to
		string get_ORF_Sequence(const string&);
			// Returns nucleotide sequence for sequence in homolog group
		void create_CF_Sequence(const string&, const string&, const map<string, vector<float> >&);
			// SEQID, nucleotide sequence, map of orfeomes & its cf
		void codon_frequency_point_system(const map<string, vector<float> >&);
};

#endif /* defined(____CFPS__) */
