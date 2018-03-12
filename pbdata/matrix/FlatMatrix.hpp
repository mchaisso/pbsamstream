#ifndef _BLASR_FLAT_MATRIX_HPP_
#define _BLASR_FLAT_MATRIX_HPP_

#define rc2index(r, c, rowSize) ((r) * (rowSize) + c)
#include <fstream>
#include <iosfwd>
#include <vector>
#include "../Types.h"  // UInt

template <typename T>
void CreateFlatMatrix(int rows, int cols, std::vector<T> &matrix);

template <typename T>
void PrintFlatMatrix(std::vector<T> &matrix, int rows, int cols, std::ostream &out, int width = 6);

template <typename T>
void PrintFlatMatrix(const T *matrix, int rows, int cols, std::ostream &out, int width = 6);

template <typename T>
class FlatMatrix2D
{
public:
    T *matrix;
    int nRows, nCols;
    int totalSize;
    int RC2Index(int row, int col);

    FlatMatrix2D();

    ~FlatMatrix2D();

    T *operator[](int row);

    T operator()(int row, int col);

    unsigned int Size();

    void Fill(T value) { std::fill(matrix, &matrix[totalSize], value); }

    void Resize(int _nRows, int _nCols) { Grow(_nRows, _nCols); }

    void Resize(unsigned int totalSize);

    FlatMatrix2D(int _nRows, int _nCols);

    void Clear()
    {
        if (matrix) {
            delete[] matrix;
        }
        matrix = NULL;
        nRows = nCols = 0;
        totalSize = 0;
    }

    void Grow(int _nRows, int _nCols);

    T Get(int r, int c);

    T Set(int r, int c, T v);

    int Index(int r, int c);

    void Print(std::ostream &out);

    void Allocate(UInt _nRows, UInt _nCols);

    void Initialize(T value);
};

template <typename T>
class FlatMatrix3D
{
public:
    T *matrix;
    //
    // For some reason it makes sense to go from rows,cols to x,y,z
    // for referencing coordinates.
    //
    int nx, ny, nz;
    int xy;
    int totalSize;

    FlatMatrix3D();

    FlatMatrix3D(int _nx, int _ny, int _nz);

    void Grow(int _nx, int _ny, int _nz);

    int Index(int x, int y, int z);

    T Get(int x, int y, int z);

    T Set(int x, int y, int z, T v);

    ~FlatMatrix3D();
};

#include "FlatMatrixImpl.hpp"

#endif  // _BLASR_FLAT_MATRIX_HPP_
