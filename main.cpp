


#include "ExtractCF.h"
#include "CodonNumRep.h"
#include "CFPS.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <dirent.h>	// Traverse directory
#include <algorithm> // Sort
#include <ctime>

using namespace std;

const string DIRECTORY = "/afs/crc.nd.edu/group/NDBL/data/rcclust/ultimate/orig_fasta/";

// Checks if provided directory exists
bool directory_exists(const char* pzPath) {
	if(pzPath == NULL) return false;
	
	DIR *pDir;
	bool bExists = false;
	
	pDir = opendir(pzPath);
	
	if(pDir != NULL) {
		bExists = true;
		(void) closedir (pDir);
	}
	return bExists;
}


// Traverses directory and creates a vector of filenames
vector<string> traverse_directory(const string& directory) {

	vector<string> co_occ_files;
	DIR *dpdf;
	struct dirent *epdf;
	dpdf = opendir(directory.c_str());
	if (dpdf) {
		while(true) {
			epdf = readdir(dpdf);
			if (epdf == NULL) break;
			string file = directory;
			file.append(string(epdf->d_name));	// Absolute path
			co_occ_files.push_back(file);
		}
		closedir(dpdf);
		sort(co_occ_files.begin(), co_occ_files.end());
	}
	return co_occ_files;
}

vector<string> get_homolog_group (const string& filename) {

	string header;
	ifstream file(filename.c_str());
	getline(file,header);
	header = header.substr(1); // Removes leading # from string
	
	stringstream ss(header);
	string seq;
	vector<string> homolog_group;
	while (getline(ss, seq, '\t')) {
		homolog_group.push_back(seq);
	}
//	for (int i = 0; i < homolog_group.size(); i++)
//		cout << homolog_group[i] << endl;
	return homolog_group;
}


int main() {

	map<string,vector<float> > ORF_CF;
	vector<string> cf_files;
	
	if (directory_exists(DIRECTORY.c_str()) ) {
	
		cf_files = traverse_directory(DIRECTORY);
		vector<string>::const_iterator cf_files_it = cf_files.begin();
		for ( ; cf_files_it != cf_files.end(); ++cf_files_it) {
			if (ExtractCF::validFile(*cf_files_it)) {
				ExtractCF CF(*cf_files_it);
				string orf = CF.get_ORF();
				vector<float> cf = CF.get_CF();
				ORF_CF.insert( pair<string,vector<float> >(orf,cf) );
			}
		}
		cout << ORF_CF.size() << endl;
		
		
		
		string filename = "/afs/crc.nd.edu/group/NDBL/data/rcclust/ultimate/ult_mm_splice_ordered/ultimateORFS13888.fasta.mm_spliced_ordered";
		vector<string> homolog_group = get_homolog_group(filename);
		CFPS test(homolog_group, ORF_CF);

	}
}
