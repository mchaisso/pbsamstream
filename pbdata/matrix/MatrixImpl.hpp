#ifndef _BLASR_MATRIX_IMPL_HPP
#define _BLASR_MATRIX_IMPL_HPP
#include <cstdint>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include "../Types.h"
#include "../utils.hpp"

template <typename T>
void CreateMatrix(VectorIndex rows, int cols, std::vector<T *> matrix)
{
    matrix.resize(rows);
    if (matrix[0]) {
        delete[] matrix[0];
        matrix[0] = NULL;
    }
    matrix[0] = ProtectedNew<T>(rows * cols);
    VectorIndex r = 1;
    for (r = 1; r < rows; r++) {
        matrix[r] = &matrix[cols * r];
    }
}

template <typename T>
Matrix<T>::Matrix()
{
    nRows = 0;
    rowsBufferSize = 0;
    nCols = 0;
    matrixBufferSize = 0;
    matrix = NULL;
}

template <typename T>
unsigned int Matrix<T>::size()
{
    return nRows * nCols;
}

template <typename T>
unsigned int Matrix<T>::GetNCols()
{
    return nCols;
}

template <typename T>
unsigned int Matrix<T>::GetNRows()
{
    return nRows;
}

template <typename T>
void Matrix<T>::Resize(VectorIndex nRowsP, VectorIndex nColsP)
{

    nRows = nRowsP;
    nCols = nColsP;
    matrixSize = nRows * nCols;
    if (nRows * nCols > matrixBufferSize) {
        matrixBufferSize = nRows * nCols;
        if (nRows > rowsBufferSize) {
            if (matrix != NULL) {
                delete[] matrix;
                matrix = NULL;
            }
        }
        if (matrix == NULL) {
            matrix = ProtectedNew<T *>(nRows);
        } else {
            if (matrix[0] != NULL) {
                delete[] matrix[0];
                matrix[0] = NULL;
            }
        }
        matrix[0] = ProtectedNew<T>(matrixBufferSize);
        VectorIndex rowIndex;
        for (rowIndex = 1; rowIndex < nRows; rowIndex++) {
            matrix[rowIndex] = &matrix[0][nCols * rowIndex];
        }
    }
}

template <typename T>
Matrix<T>::Matrix(VectorIndex nRowsP, VectorIndex nColsP)
{
    Resize(nRowsP, nColsP);
}

template <typename T>
void Matrix<T>::Reference(Matrix<T> &rhs)
{
    matrix = rhs.matrix;
}

template <typename T>
void Matrix<T>::Initialize(T value)
{
    std::fill(&matrix[0][0], &matrix[0][matrixSize], value);
}

template <typename T>
T *Matrix<T>::operator[](VectorIndex rowIndex)
{
    assert(rowIndex < nRows);
    return matrix[rowIndex];
}

template <typename T>
void Matrix<T>::Free()
{
    if (matrix != NULL) {
        if (matrix[0] != NULL) {
            delete[] matrix[0];
        }
        delete[] matrix;
    }
    matrix = NULL;
}

template <typename T>
void Matrix<T>::Print(std::ofstream &out)
{
    VectorIndex i;
    VectorIndex j;
    for (i = 0; i < nRows; i++) {
        for (j = 0; j < nCols; j++) {
            out << matrix[i][j] << " ";
        }
        out << std::endl;
    }
}
#endif
