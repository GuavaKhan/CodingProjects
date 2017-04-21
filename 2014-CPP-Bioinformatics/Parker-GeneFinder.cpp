//Parker Temple, SID: 997223534
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define START_CODON "AUG"
#define STOP '\0'
#define CODON_LEN 3
using namespace std;

class Strand{
	public:
	string strand;
	
	//strands are assumed to be passed 5' => 3'
	Strand(){
		this->strand = "";
	}//Strand()
	Strand(string strand){
		this->strand = strand;
	}//Strand(string)
	virtual ~Strand(){
	}//~Strand()

	virtual string toString(){
		return "5\'" + strand + "3\'";
	}//toString()

	virtual char complementBase(char base){
		switch(base){
			case 'A': return 'T'; break;
			case 'T': return 'A'; break;
			case 'G': return 'C'; break;
			case 'C': return 'G'; break;
			//IUPAC
			case 'Y': return 'R'; break; //pYrimidine (C T) complement is puRine
			case 'R': return 'Y'; break; //puRine (A G) complement is pYrimidine
			case 'S': return 'S'; break; //Strong (G C) complement is Strong
			case 'W': return 'W'; break; //Weak (A T) complement is Weak
			case 'K': return 'M'; break; //Keto (T/U G) complement is aMino 
			case 'M': return 'K'; break; //aMino (A C) complement is Keto
			case 'B': return 'V'; break; //not A (C G T) complement is not T/U (A C G)
			case 'V': return 'B'; break; //not T/U (A C G) complement is not T/U (C G T)
			case 'D': return 'H'; break; //not C (A G T) complement is not G (A C T)
			case 'H': return 'D'; break; //not G (A C T) complement is not C (A G T)
			case 'N': return 'N'; break; //any base complement is any base
			default: return base;
		}//switch(base);
	}//complementBase(char)

	string complement(){
		string comp = "";
		for(unsigned int i = 0; i < strand.length(); i++){
			comp += complementBase(strand[i]);
		}//for i
		return comp;
	}//complement()
};//class Strand

class DNA : public Strand{
	public:
	DNA(string strand) : Strand(strand){
	}//DNA()

	string toRNA(){
		string mRNA = "";
		for(unsigned int i = 0; i < strand.length(); i++){
			char cBase = complementBase(strand[i]);
			cBase == 'T' ? cBase = 'U' : 0;
			mRNA += cBase;
		}//for i
		return mRNA;
	}//toRNA()
};//class DNA

class RNA : public Strand{
	public:
	RNA(string strand) : Strand(strand){
	}//RNA()

	char complementBase(char base){
		switch(base){
			case 'A': return 'U'; break;
			case 'U': return 'A'; break;
			case 'G': return 'C'; break;
			case 'C': return 'G'; break;
			//IUPAC
			case 'Y': return 'R'; break; //pYrimidine (C T) complement is puRine
			case 'R': return 'Y'; break; //puRine (A G) complement is pYrimidine
			case 'S': return 'S'; break; //Strong (G C) complement is Strong
			case 'W': return 'W'; break; //Weak (A T) complement is Weak
			case 'K': return 'M'; break; //Keto (T/U G) complement is aMino 
			case 'M': return 'K'; break; //aMino (A C) complement is Keto
			case 'B': return 'V'; break; //not A (C G T) complement is not T/U (A C G)
			case 'V': return 'B'; break; //not T/U (A C G) complement is not T/U (C G T)
			case 'D': return 'H'; break; //not C (A G T) complement is not G (A C T)
			case 'H': return 'D'; break; //not G (A C T) complement is not C (A G T)
			case 'N': return 'N'; break; //any base complement is any base
			default: return base;
		}//switch(base);
	}//complementBase(char)
	
	string getCodon(int i){
		return strand.substr(i, 3);
	}//getCodon(int)

	int findStart(){
		for(unsigned int i = 0; i < strand.length() - 2; i++){
			string codon = getCodon(i);
			if(!codon.compare(START_CODON))
				return i;
		}//for int
		return -1;
	}//findStart(int)

	bool isAmino(string codon, string *list, int len){
		for(int i = 0; i < len; i++){
			if(!codon.compare(list[i]))
				return 1;
		}//for i in list
		return 0;
	}//isAmino(string *)

	char findAmino(string codon){
		string phenylalanine[3] = {"UUU", "UUC", "UUY"};
		string leucine[8] = {"UUA", "UUG", "CUU", "CUC", "CUA", "CUG", "YUR", "CUN"};
		string isoleucine[4] = {"AUU", "AUC", "AUA", "AUH"};
		string methionine[1] = {"AUG"};
		string valine[5] = {"GUU", "GUC", "GUA", "GUG", "GUN"};
		string serine[8] = {"UCU", "UCC", "UCA", "UCG", "AGU", "AGC", "UCN", "AGY"};
		string proline[5] = {"CCU", "CCC", "CCA", "CCG", "CCN"};
		string threonine[5] = {"ACU", "ACC", "ACA", "ACG", "ACN"};
		string alanine[5] = {"GCU", "GCC", "GCA", "GCG", "GCN"};
		string tyrosine[3] = {"UAU", "UAC", "UAY"};
		string stop[5] = {"UAA", "UAG", "UGA", "UAR", "URA"};
		string histidine[3] = {"CAU", "CAC", "CAY"};
		string glutamine[3] = {"CAA", "CAG", "CAR"};
		string asparagine[3] = {"AAU", "AAC", "AAY"};
		string lysine[3] = {"AAA", "AAG", "AAR"};
		string asparticAcid[3] = {"GAU", "GAC", "GAY"};
		string glutamicAcid[3] = {"GAA", "GAG", "GAR"};
		string cysteine[3] = {"UGU", "UGC", "UGY"};
		string tryptophan[1] = {"UGG"};
		string arginine[8] = {"CGU", "CGC", "CGA", "CGG", "AGA", "AGG", "CGN", "MGR"};
		string glycine[5] = {"GGU", "GGC", "GGA", "GGG", "GGN"};

		if(isAmino(codon, phenylalanine, 3))
			return 'F';
		else if(isAmino(codon, leucine, 8))
			return 'L';
		else if(isAmino(codon, isoleucine, 4))
			return 'I';
		else if(isAmino(codon, methionine, 1))
			return 'M';
		else if(isAmino(codon, valine, 5))
			return 'V';
		else if(isAmino(codon, serine, 8))
			return 'S';
		else if(isAmino(codon, proline, 5))
			return 'P';
		else if(isAmino(codon, threonine, 5))
			return 'T';
		else if(isAmino(codon, alanine, 5))
			return 'A';
		else if(isAmino(codon, tyrosine, 3))
			return 'Y';
		else if(isAmino(codon, stop, 5))
			return STOP;
		else if(isAmino(codon, histidine, 3))
			return 'H';
		else if(isAmino(codon, glutamine, 3))
			return 'Q';
		else if(isAmino(codon, asparagine, 3))
			return 'N';
		else if(isAmino(codon, lysine, 3))
			return 'K';
		else if(isAmino(codon, asparticAcid, 3))
			return 'D';
		else if(isAmino(codon, glutamicAcid, 3))
			return 'E';
		else if(isAmino(codon, cysteine, 3))
			return 'C';
		else if(isAmino(codon, tryptophan, 1))
			return 'W';
		else if(isAmino(codon, arginine, 8))
			return 'R';
		else if(isAmino(codon, glycine, 5))
			return 'G';
		return '?';
	}//findAmino(string)

	string getProtein(int start){
		string protein = "";
		for(unsigned int i = start; i < strand.length() - 2; i += CODON_LEN){
			string codon = getCodon(i);
			char amino = findAmino(codon);
			if(amino != '?')
				protein += amino;
			if(amino == STOP)
				return protein;
		}//for i til end of strand
		return protein;
	}//getProtein(int)

	string toProtein(){
		if(!strand.compare(""))
			return "";
		//int start = findStart();
		//return getProtein(start);
		return getProtein(0);
	}//toProtein()

	string toDNA(){
		string oDNA = "";
		for(unsigned int i = 0; i < strand.length(); i++){
			char cBase = complementBase(strand[i]);
			cBase == 'U' ? cBase = 'T' : 0;
			oDNA += cBase;
		}//for i
		return oDNA;
	}//toDNA()

	string exon(){
		string exon = "";
		bool start_found = false;
		for(unsigned int i = 0; i < strand.length() - 2; i += CODON_LEN){
			string codon = getCodon(i);
			char amino = findAmino(codon);
			if(amino == 'M' && !start_found){
				start_found = true;
			}//if start found, and wasn't before
			if(amino == STOP && start_found){
				exon += codon;
				return exon;
			}//stop codon found
			if(start_found)
				exon += codon;
		}//for i til end of strand
		return exon;
	}//exon(RNA)
};//class RNA 

class Protein : public Strand{
	public:
	Protein(string strand) : Strand(strand){}
	string toString(){
		return strand;
	}//toString()
};//class Protein

RNA* longest(RNA** list, unsigned int len){
	unsigned int max = 0;
	unsigned int max_pos = 0;
	unsigned int currentLen = 0;
	RNA *current = NULL;

	for(unsigned int i = 0; i < len; i++){
		current = list[i];
		currentLen = current->strand.length();
		if(currentLen > max){
			max = currentLen;
			max_pos = i;
		}//if current RNA bigger than prev. max
	}//for all in list
	return list[max_pos];
}//longest(RNA**, unsigned int)

int main(int argc, char *argv[]){
	if(argc < 2){
		cerr << "ERROR: No input file given. Format: ./executeable input_file. Exiting..." << endl;
		exit(1);
	}//if no input file given

	ifstream input_file(argv[1]);
	string strand = "";
	input_file >> strand;
	cout << "Input DNA Strand:\t5\'" << strand << "3\'" << endl;
	input_file.close();

	//DNA *original = new DNA("TCAATGTAACGCGCTACCCGGAGCTCTGGGCCCAAATTTCATCCACT");
	DNA *original = new DNA(strand);
	RNA *mRNA = new RNA(original->toRNA());
	RNA *mRNA1 = new RNA(mRNA->strand.substr(1));
	RNA *mRNA2 = new RNA(mRNA->strand.substr(2));
	RNA *mRNAExon0 = new RNA(mRNA->exon());
	RNA *mRNAExon1 = new RNA(mRNA1->exon());
	RNA *mRNAExon2 = new RNA(mRNA2->exon());

	DNA *cDNA = new DNA(original->complement());
	RNA *cmRNA = new RNA(cDNA->toRNA());
	RNA *cmRNA1 = new RNA(cmRNA->strand.substr(1));
	RNA *cmRNA2 = new RNA(cmRNA->strand.substr(2));
	RNA *cmRNAExon0 = new RNA(cmRNA->exon());
	RNA *cmRNAExon1 = new RNA(cmRNA1->exon());
	RNA *cmRNAExon2 = new RNA(cmRNA2->exon());

	RNA *mRNAExons[6] = {mRNAExon0, mRNAExon1, mRNAExon2, cmRNAExon0, 
		cmRNAExon1, cmRNAExon2}; 								//exons for all possible reading frames: 3 from original, 3 from complement.
	RNA *longestExon = longest(mRNAExons, 6); //find longest exon.
	Protein *protein = new Protein(longestExon->toProtein());

	cout << "cDNA:\t\t\t" << cDNA->toString() << endl;
	cout << "mRNA:\t\t\t" << mRNA->toString() << endl;
	cout << "cmRNA:\t\t\t" << cmRNA->toString() << endl;
	cout << "Longest mRNA Exon:\t" << longestExon->toString() << endl;
	cout << "Longest Protein:\t" << protein->toString() << endl; 

	delete original;
	delete mRNA;
	delete mRNA1;
	delete mRNA2;
	delete mRNAExon0;
	delete mRNAExon1;
	delete mRNAExon2;
	delete cDNA;
	delete cmRNA;
	delete cmRNA1;
	delete cmRNA2;
	delete cmRNAExon0;
	delete cmRNAExon1;
	delete cmRNAExon2;
	delete protein;
	return 0;
}//main()
