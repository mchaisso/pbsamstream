#ifndef _BLASR_SEQUENCE_INDEX_DATABASE_IMPL_HPP_
#define _BLASR_SEQUENCE_INDEX_DATABASE_IMPL_HPP_

template <typename TSeq>
SequenceIndexDatabase<TSeq>::SequenceIndexDatabase(int final)
{
    nSeqPos = 0;
    if (!final) {
        growableSeqStartPos.push_back(0);
    }
    names = NULL;
    deleteNames = false;
    nameLengths = NULL;
    deleteNameLengths = false;
    seqStartPos = NULL;
    deleteSeqStartPos = false;
    deleteStructures = false;
}

template <typename TSeq>
SequenceIndexDatabase<TSeq>::~SequenceIndexDatabase()
{
    FreeDatabase();
}

template <typename TSeq>
DNALength SequenceIndexDatabase<TSeq>::GetLengthOfSeq(int seqIndex)
{
    assert(seqIndex < nSeqPos - 1);
    return seqStartPos[seqIndex + 1] - seqStartPos[seqIndex] - 1;
}

// Return index of a reference sequence with name "seqName".
template <typename TSeq>
int SequenceIndexDatabase<TSeq>::GetIndexOfSeqName(std::string seqName)
{
    for (int i = 0; i < nSeqPos - 1; i++) {
        if (seqName == std::string(names[i])) {
            return i;
        }
    }
    return -1;
}

template <typename TSeq>
void SequenceIndexDatabase<TSeq>::GetName(int seqIndex, std::string &name)
{
    assert(seqIndex < nSeqPos - 1);
    name = names[seqIndex];
}

template <typename TSeq>
void SequenceIndexDatabase<TSeq>::MakeSAMSQString(std::string &sqString)
{
    std::stringstream st;
    int i;
    for (i = 0; i < nSeqPos - 1; i++) {
        st << "@SQ\tSN:" << names[i] << "\tLN:" << GetLengthOfSeq(i);
        if (md5.size() == nSeqPos - 1) {
            st << "\tM5:" << md5[i];
        }
        st << std::endl;
    }
    sqString = st.str();
}

template <typename TSeq>
DNALength SequenceIndexDatabase<TSeq>::ChromosomePositionToGenome(int chrom, DNALength chromPos)
{
    assert(chrom < nSeqPos);
    return seqStartPos[chrom] + chromPos;
}

template <typename TSeq>
int SequenceIndexDatabase<TSeq>::SearchForIndex(DNALength pos)
{
    // The default behavior for the case
    // that there is just one genome.
    if (nSeqPos == 1) {
        return 0;
    }

    DNALength *seqPosIt = std::upper_bound(seqStartPos + 1, seqStartPos + nSeqPos, pos);

    return seqPosIt - seqStartPos - 1;
}

template <typename TSeq>
std::string SequenceIndexDatabase<TSeq>::GetSpaceDelimitedName(unsigned int index)
{
    int pos;
    assert(index < static_cast<unsigned int>(nSeqPos));
    std::string name;
    for (pos = 0; pos < nameLengths[index]; pos++) {
        if (names[index][pos] == ' ' or names[index][pos] == '\t' or names[index][pos] == '\0') {
            break;
        }
    }
    name.assign(names[index], pos);
    return name;
}

template <typename TSeq>
int SequenceIndexDatabase<TSeq>::SearchForStartBoundary(DNALength pos)
{

    int index = SearchForIndex(pos);
    if (index != -1) {
        return seqStartPos[index];
    } else {
        return -1;
    }
}

template <typename TSeq>
int SequenceIndexDatabase<TSeq>::SearchForEndBoundary(DNALength pos)
{

    int index = SearchForIndex(pos);
    if (index != -1) {
        return seqStartPos[index + 1];
    } else {
        return -1;
    }
}

template <typename TSeq>
DNALength SequenceIndexDatabase<TSeq>::SearchForStartAndEnd(DNALength pos, DNALength &start,
                                                            DNALength &end)
{
    int index = SearchForIndex(pos);
    if (index != -1) {
        start = seqStartPos[index];
        end = seqStartPos[index + 1];
        return 1;
    } else {
        start = end = -1;
        return 0;
    }
}

template <typename TSeq>
void SequenceIndexDatabase<TSeq>::WriteDatabase(std::ofstream &out)
{
    int mn = SEQUENCE_INDEX_DATABASE_MAGIC;
    out.write((char *)&mn, sizeof(int));
    out.write((char *)&nSeqPos, sizeof(int));
    out.write((char *)seqStartPos, sizeof(DNALength) * nSeqPos);
    int nSeq = nSeqPos - 1;
    out.write((char *)nameLengths, sizeof(int) * nSeq);
    int i;
    //
    // The number of sequences is 1 less than the number of positions
    // since the positions include 0 as a boundary.
    //
    char nullchar = '\0';
    for (i = 0; i < nSeq; i++) {
        //
        // nameLengths has space for the null char, so the length of the
        // name = nameLengths[i]-1. Write a nullchar to disk so that it
        // may be read in later with no work.
        //
        out.write((char *)names[i], sizeof(char) * (nameLengths[i] - 1));
        out.write((char *)&nullchar, sizeof(char));
    }
}

template <typename TSeq>
void SequenceIndexDatabase<TSeq>::ReadDatabase(std::ifstream &in)
{
    int mn;
    // Make sure this is a read database, since the binary input
    // is not syntax checked.
    in.read((char *)&mn, sizeof(int));
    if (mn != SEQUENCE_INDEX_DATABASE_MAGIC) {
        std::cout << "ERROR: Sequence index database is corrupt!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    //
    // Read in the boundaries of each sequence.
    //
    deleteStructures = true;

    in.read((char *)&nSeqPos, sizeof(int));
    assert(seqStartPos == NULL);
    seqStartPos = ProtectedNew<DNALength>(nSeqPos);
    deleteSeqStartPos = true;
    in.read((char *)seqStartPos, sizeof(DNALength) * nSeqPos);
    int nSeq = nSeqPos - 1;

    // Get the lengths of the strings to read.
    assert(nameLengths == NULL);
    nameLengths = ProtectedNew<int>(nSeq);
    deleteNameLengths = true;
    in.read((char *)nameLengths, sizeof(int) * nSeq);

    // Get the titles of the sequences.
    assert(names == NULL);  // Otherwise need to delete names;
    names = ProtectedNew<char *>(nSeq);
    deleteNames = true;
    char *namePtr;
    int i;
    for (i = 0; i < nSeq; i++) {
        namePtr = ProtectedNew<char>(nameLengths[i]);
        if (nameLengths[i] > 0) {
            in.read(namePtr, nameLengths[i]);
        }
        namePtr[nameLengths[i] - 1] = '\0';
        names[i] = namePtr;
    }
}

template <typename TSeq>
void SequenceIndexDatabase<TSeq>::SequenceTitleLinesToNames()
{
    int seqIndex;
    std::vector<std::string> tmpNameArray;
    for (seqIndex = 0; seqIndex < nSeqPos - 1; seqIndex++) {
        std::string tmpName;
        AssignUntilFirstSpace(names[seqIndex], nameLengths[seqIndex], tmpName);
        if (names[seqIndex]) {
            delete[] names[seqIndex];
        }
        names[seqIndex] = ProtectedNew<char>(tmpName.size() + 1);
        strcpy(names[seqIndex], tmpName.c_str());
        names[seqIndex][tmpName.size()] = '\0';
        nameLengths[seqIndex] = tmpName.size();
        tmpNameArray.push_back(tmpName);
    }
    // Make sure that reference names are unique.
    sort(tmpNameArray.begin(), tmpNameArray.end());
    for (size_t j = 0; j < tmpNameArray.size() - 1; j++) {
        if (tmpNameArray[j] == tmpNameArray[j + 1]) {
            std::cout << "Error, reference with name \"" << tmpNameArray[j]
                      << "\" in the reference genome is not unique" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

template <typename TSeq>
VectorIndex SequenceIndexDatabase<TSeq>::AddSequence(TSeq &sequence)
{
    int endPos = growableSeqStartPos[growableSeqStartPos.size() - 1];
    //int growableSize = growableSeqStartPos.size();
    growableSeqStartPos.push_back(endPos + sequence.length + 1);
    std::string fastaTitle;
    sequence.GetFASTATitle(fastaTitle);
    growableName.push_back(fastaTitle);
    return growableName.size();
}

template <typename TSeq>
void SequenceIndexDatabase<TSeq>::Finalize()
{
    deleteStructures = true;
    seqStartPos = &growableSeqStartPos[0];
    nSeqPos = growableSeqStartPos.size();
    int nSeq = nSeqPos - 1;

    assert(names == NULL);
    names = ProtectedNew<char *>(nSeq);
    deleteNames = true;
    int i;
    if (nameLengths) {
        delete[] nameLengths;
        nameLengths = NULL;
    }
    nameLengths = ProtectedNew<int>(nSeq);
    deleteNameLengths = true;
    for (i = 0; i < nSeq; i++) {
        names[i] = ProtectedNew<char>(growableName[i].size() + 1);

        memcpy((char *)names[i], (char *)growableName[i].c_str(), growableName[i].size());

        names[i][growableName[i].size()] = '\0';
        nameLengths[i] = growableName[i].size() + 1;
    }
}

template <typename TSeq>
void SequenceIndexDatabase<TSeq>::FreeDatabase()
{
    int i;
    if (deleteStructures == false) {
        return;
    }
    if (names != NULL and deleteNames) {
        int nSeq = nSeqPos - 1;
        for (i = 0; i < nSeq; i++) {
            delete[] names[i];
        }
        delete[] names;
        names = NULL;
    }
    if (nameLengths != NULL and deleteNameLengths) {
        delete[] nameLengths;
        nameLengths = NULL;
    }
    if (seqStartPos != NULL and deleteSeqStartPos) {
        delete[] seqStartPos;
        seqStartPos = NULL;
    }
}

template <typename TSeq>
SeqBoundaryFtr<TSeq>::SeqBoundaryFtr(SequenceIndexDatabase<TSeq> *_seqDB)
{
    seqDB = _seqDB;
}

template <typename TSeq>
int SeqBoundaryFtr<TSeq>::GetIndex(DNALength pos)
{
    return seqDB->SearchForIndex(pos);
}

template <typename TSeq>
int SeqBoundaryFtr<TSeq>::GetStartPos(int index)
{
    assert(index < seqDB->nSeqPos);
    return seqDB->seqStartPos[index];
}

template <typename TSeq>
DNALength SeqBoundaryFtr<TSeq>::operator()(DNALength pos)
{
    return seqDB->SearchForStartBoundary(pos);
}

template <typename TSeq>
DNALength SeqBoundaryFtr<TSeq>::Length(DNALength pos)
{
    DNALength start, end;
    seqDB->SearchForStartAndEnd(pos, start, end);
    return end - start;
}

#endif
