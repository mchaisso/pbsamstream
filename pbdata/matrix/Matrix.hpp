#ifndef _BLASR_MATRIX_HPP_
#define _BLASR_MATRIX_HPP_

#include <vector>
#include "../Types.h"

template <typename T>
void CreateMatrix(int rows, int cols, std::vector<T*> matrix);

/*
 *	Implement a matrix as an array into a large allocated buffer of size
 *	nRows * nCols.
 */

template <typename T>
class Matrix
{
private:
    VectorIndex nRows;
    VectorIndex nCols;
    T** matrix;
    VectorIndex matrixBufferSize;
    VectorIndex matrixSize;
    VectorIndex rowsBufferSize;

public:
    Matrix();

    unsigned int size();

    unsigned int GetNCols();

    unsigned int GetNRows();

    void Resize(VectorIndex nRowsP, VectorIndex nColsP);

    Matrix(VectorIndex nRowsP, VectorIndex nColsP);

    void Reference(Matrix<T>& rhs);

    void Initialize(T value);

    T* operator[](VectorIndex rowIndex);

    void Free();

    void Print(std::ofstream& out);
};

#include "MatrixImpl.hpp"

#endif  // _BLASR_MATRIX_HPP_
