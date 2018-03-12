#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
#include "../Types.h"
#include "../utils.hpp"
#include "FlatMatrix.hpp"

template <typename T>
void CreateFlatMatrix(int rows, int cols, std::vector<T> &matrix)
{
    matrix.resize(rows * cols);
}

template <typename T>
void PrintFlatMatrix(std::vector<T> &matrix, int rows, int cols, std::ostream &out, int width)
{
    PrintFlatMatrix((const T *)&matrix[0], rows, cols, out, width);
}

template <typename T>
void PrintFlatMatrix(const T *matrix, int rows, int cols, std::ostream &out, int width)
{
    int r, c, i;
    i = 0;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            out.width(width);
            out << matrix[i] << " ";
            i++;
        }
        out << std::endl;
    }
}

template <typename T>
int FlatMatrix2D<T>::RC2Index(int row, int col)
{
    return row * nCols + col;
}

template <typename T>
T *FlatMatrix2D<T>::operator[](int row)
{
    return &matrix[row * nCols];
}

template <typename T>
T FlatMatrix2D<T>::operator()(int row, int col)
{
    int index = RC2Index(row, col);
    return matrix[index];
}

template <typename T>
FlatMatrix2D<T>::FlatMatrix2D()
{
    matrix = NULL;
    nRows = nCols = totalSize = 0;
}

template <typename T>
unsigned int FlatMatrix2D<T>::Size()
{
    return nRows * nCols;
}

template <typename T>
void FlatMatrix2D<T>::Resize(unsigned int _totalSize)
{
    if (matrix != NULL) {
        delete[] matrix;
    }
    matrix = ProtectedNew<T>(_totalSize);
    totalSize = _totalSize;
}

template <typename T>
FlatMatrix2D<T>::FlatMatrix2D(int _nRows, int _nCols)
{
    totalSize = 0;
    matrix = NULL;
    //		assert(_nRows > 0);
    //		assert(_nCols > 0);
    if (_nRows == 0 or _nCols == 0) {
        nRows = _nRows;
        nCols = _nCols;
        return;
    } else {
        Grow(_nRows, _nCols);
    }
}
template <typename T>
void FlatMatrix2D<T>::Grow(int _nRows, int _nCols)
{
    nRows = _nRows;
    nCols = _nCols;
    if (nRows * nCols > totalSize) {
        if (totalSize != 0 && matrix) delete[] matrix;
        totalSize = nRows * nCols;
        matrix = ProtectedNew<T>(totalSize);
    }
}

template <typename T>
T FlatMatrix2D<T>::Get(int r, int c)
{
    return matrix[r * nCols + c];
}

template <typename T>
T FlatMatrix2D<T>::Set(int r, int c, T v)
{
    return matrix[r * nCols + c] = v;
}

template <typename T>
int FlatMatrix2D<T>::Index(int r, int c)
{
    return r * nCols + c;
}

template <typename T>
void FlatMatrix2D<T>::Print(std::ostream &out)
{
    PrintFlatMatrix(matrix, nRows, nCols, out);
}

template <typename T>
void FlatMatrix2D<T>::Allocate(UInt _nRows, UInt _nCols)
{
    nRows = _nRows;
    nCols = _nCols;
    matrix = ProtectedNew<T>(nRows * nCols);
}

template <typename T>
void FlatMatrix2D<T>::Initialize(T value)
{
    T *matPtr, *matEnd;
    matEnd = &matrix[nRows * nCols];
    for (matPtr = &matrix[0]; matPtr != matEnd; ++matPtr) {
        *matPtr = value;
    }
}

template <typename T>
FlatMatrix2D<T>::~FlatMatrix2D()
{
    if (matrix != NULL) {
        delete[] matrix;
        matrix = NULL;
    }
}

template <typename T>
FlatMatrix3D<T>::FlatMatrix3D()
{
    nx = 0, ny = 0, nz = 0;
    xy = 0;
    totalSize = 0;
    matrix = NULL;
}

template <typename T>
FlatMatrix3D<T>::FlatMatrix3D(int _nx, int _ny, int _nz)
{
    totalSize = 0;
    matrix = NULL;
    assert(_nx > 0);
    assert(_ny > 0);
    assert(_nz > 0);
    Grow(_nx, _ny, _nz);
}

template <typename T>
void FlatMatrix3D<T>::Grow(int _nx, int _ny, int _nz)
{
    nx = _nx;
    ny = _ny;
    nz = _nz;
    if (nx * ny * nz > totalSize) {
        if (matrix != NULL) {
            delete[] matrix;
        }
        totalSize = nx * ny * nz;
        matrix = ProtectedNew<T>(totalSize);
    }
    xy = nx * ny;
}

template <typename T>
int FlatMatrix3D<T>::Index(int x, int y, int z)
{
    return z * xy + y * nx + x;
}

template <typename T>
T FlatMatrix3D<T>::Get(int x, int y, int z)
{
    return matrix[Index(x, y, z)];
}

template <typename T>
T FlatMatrix3D<T>::Set(int x, int y, int z, T v)
{
    return matrix[Index(x, y, z)] = v;
}

template <typename T>
FlatMatrix3D<T>::~FlatMatrix3D()
{
    if (matrix != NULL) {
        delete[] matrix;
        matrix = NULL;
    }
}
