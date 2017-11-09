#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <map>
#include "pbdata/utils/SMRTTitle.hpp"
#include "pbbam/BamRecord.h"
#include "pbbam/SamWriter.h"
#include "pbdata/sam/SAMKeywordValuePair.hpp"
#include "pbdata/NucConversion.hpp"
using namespace std;

void StringToUnsigned8Vector(string valueString, vector<uint8_t> &vector) {
	stringstream strm(valueString);
	int n=0;
	while (strm) {
		int val;
		if ( (strm >> val).eof() ) {
			vector.push_back(val);			
			break;
		}
		else {
			vector.push_back((uint8_t)val);
			strm.get();
			n+=1;
		}
	}
}

template <typename t_vect> void StringToVector(string valueString, vector<t_vect> &vector) {
	stringstream strm(valueString);
	int n;
	while (strm) {
		t_vect val;
		if ( (strm >> val).eof() ) {
			vector.push_back(val);
			break;
		}
		else {
			vector.push_back(val);
			strm.get();
			n+=1;
		}
	}
}

int main(int argc, char** argv) {
	if (argc< 2) {
		cout << "usage: pbsamstream [in.sam|-]" << endl;
		cout << " - implies read stdin" <<endl;
		exit(0);
	}
	map<string, int> headerMap;
	int refIndex = 0;
	istream *inPtr;
	ifstream inFile;
	if (string(argv[1]) == "-") {
		inPtr = &cin;
	}
	else {
		inFile.open(argv[1]);
		inPtr = &inFile;
	}
	PacBio::BAM::BamHeader *header;	
	PacBio::BAM::SamWriter *samWriter = NULL;
	

	string headerLines;
	while (*inPtr) {
		string line;
		std::getline(*inPtr, line);
		if (line.size() > 0 and line[0] == '@' ) {
			headerLines += line  + "\n";
			if (line.size() > 3 and line.substr(0,3) == "@SQ") {
				vector<string> values;
				ParseSeparatedList(line, values, '\t');
				if (values.size() < 2) {
					cerr << "Error with @SQ entry" << endl;
					cerr << line <<endl;
					assert(0);
				}
				int v;
				string seqName = "";
				for (v = 0; v < values.size(); v++) {

					if (values[v].size() >3 and values[v].substr(0,2) == "SN") {
						seqName = values[v].substr(3);
						break;
					}
				}
				if (seqName == "") {
					cerr << "Error with seqName in @SQ line" << endl;
					cerr<< line << endl;
					assert(0);
				}
				headerMap[seqName] = refIndex;
				refIndex++;
			}
			//			cout << line << endl;
			continue;
		}
		else {
			if (samWriter == NULL) {
				header = new PacBio::BAM::BamHeader(headerLines);
				samWriter = new PacBio::BAM::SamWriter("-", *header);
			}
		}
			
		
		vector<string> values;
		ParseSeparatedList(line, values, '\t');
		if (values.size() < 11) {
			continue;
		}

		stringstream lineStrm(line);
		int flags;
		int mapqv;

		uint16_t flag = (uint16_t) atoi(values[1].c_str());

		SMRTTitle smrtTitle(values[0]);

		//
		// Populate the bam record.
		//
		if (string(values[2]) == "*") {
			continue;
		}
		PacBio::BAM::BamRecord bamRecord;
		if (smrtTitle.isSMRTTitle) {
			bamRecord.Impl().Name(smrtTitle.ToString());
		} else {
			cout << "ERROR, can not convert non-pacbio reads to pbbam record." << endl;
			exit(-1);
		}
		
    PacBio::BAM::Position pos = atoi(values[3].c_str());
		
    PacBio::BAM::Cigar cigar = PacBio::BAM::Cigar::FromStdString(values[5]);
    PacBio::BAM::Strand strand;
		if (values[10] == "*") {
			values[10] = string(values[9].size(), '5');
		}

		
		if ( (flag & 0x10) ==  0) {
			strand = PacBio::BAM::Strand::FORWARD;
		}
		else {
			strand = PacBio::BAM::Strand::REVERSE;
			//
			// Need to flip qv and seq.
			//
			int i;
			string rc = values[9];
			string rcqual = values[10];
			int l = values[9].size();

			for (i = 0; i < values[9].size(); i++) {
				rc[l-i-1] = ReverseComplementNuc[values[9][i]];
				rcqual[l-i-1] = values[10][i];
			}
			values[9] = rc;
			values[10] = rcqual;
			
		}

		string alignedRef = values[2];
		if (headerMap.find(alignedRef) == headerMap.end()) {
			cerr << "Could not find " << alignedRef << " in the SQ headers." << endl;
			assert(0);
		}
		int headerIndex = headerMap[alignedRef];
		mapqv=atoi(values[4].c_str());
			
		bamRecord.Impl().SetSequenceAndQualities(values[9], values[10]);
		//		bamRecord.Impl().CigarData(cigar);
		bamRecord.Impl().Bin(0);
		bamRecord.Impl().InsertSize(0);
		bamRecord.Impl().MapQuality(0); //static_cast<uint8_t>(atoi(values[4].c_str())));
		bamRecord.Impl().MatePosition(static_cast<PacBio::BAM::Position>(-1));
		bamRecord.Impl().MateReferenceId(static_cast<int32_t>(-1));
		bamRecord.Impl().Position(-1); //pos);
		//		bamRecord.Impl().ReferenceId(static_cast<int32_t>(headerIndex));
    bamRecord.Impl().Flag(static_cast<uint32_t>(flag));


		PacBio::BAM::TagCollection tags;
		int kvi;
		for (kvi = 11; kvi < values.size(); kvi++) {
			string key, kvType, kvValue;
			if (SplitSAMTypedKeyValuePair(values[kvi], key, kvType, kvValue)) {
				if (kvType == "A") {
					tags[key] = kvValue[0];
				}
				else if (kvType == "i") {
					tags[key] = atoi(kvValue.c_str());
				}
				else if (kvType == "f") {
					tags[key] = (float)atof(kvValue.c_str());
				}
				else if (kvType == "Z") {
					tags[key] = kvValue;
				}
				else if (kvType == "H") {
					cerr << "I don't feel like writing this now." << endl;
					assert(0);
				}
				else if (kvType == "B") {
					char arrayType = kvValue[0];
					string arrayString;
					arrayString = kvValue.substr(2); 
					// I don't feel like figuring out how to do this in a fancy way to bind types to a function, so I'm using  a case.
					if (arrayType == 'c') {
						vector<int8_t> v; StringToVector(arrayString, v);
						tags[key] = v;
					}
					if (arrayType == 'C') {
						vector<uint8_t > v; StringToUnsigned8Vector(arrayString, v);
						tags[key] = v;
					}
					if (arrayType == 's') {
						vector<int16_t> v; StringToVector(arrayString, v);
						tags[key] = v;
					}
					if (arrayType == 'S') {
						vector<uint16_t> v; StringToVector(arrayString, v);
						tags[key] = v;
					}
					if (arrayType == 'i') {
						vector<int32_t> v; StringToVector(arrayString, v);
						tags[key] = v;
					}
					if (arrayType == 'I') {
						vector<uint32_t> v; StringToVector(arrayString, v);
						tags[key] = v;
					}
					if (arrayType == 'f') {
						vector<float> v; StringToVector(arrayString, v);
						tags[key] = v;
					}
				}
			}

			
		}
		bamRecord.Impl().Tags(tags);
		
		PacBio::BAM::BamRecord mappedBamRecord = PacBio::BAM::BamRecord::Mapped(bamRecord,
																										 headerIndex,
																										 pos-1,
																										 strand,
																										 cigar,
																										 mapqv);
		
		samWriter->Write(mappedBamRecord);
		
	}

	delete header;
	delete samWriter;

}
