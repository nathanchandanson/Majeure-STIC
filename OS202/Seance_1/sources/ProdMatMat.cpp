#include <algorithm>
#include <cassert>
#include <iostream>
#include <thread>
#if defined(_OPENMP)
#include <omp.h>
#endif
#include "ProdMatMat.hpp"

namespace {
void prodSubBlocks(int iRowBlkA, int iColBlkB, int iColBlkA, int szBlock,
                   const Matrix& A, const Matrix& B, Matrix& C) {
  // for (int i = iRowBlkA; i < std::min(A.nbRows, iRowBlkA + szBlock); ++i)
  //   for (int k = iColBlkA; k < std::min(A.nbCols, iColBlkA + szBlock); k++)
  //     for (int j = iColBlkB; j < std::min(B.nbCols, iColBlkB + szBlock); j++)
  //       C(i, j) += A(i, k) * B(k, j);
  
  // #pragma omp parallel for ///////////////////////// Instruction to say to OpenMP to parallelize the for loop /////////////////////////
  for (int j = iColBlkB; j < std::min(B.nbCols, iColBlkB + szBlock); j++)
    for (int k = iColBlkA; k < std::min(A.nbCols, iColBlkA + szBlock); k++)
      for (int i = iRowBlkA; i < std::min(A.nbRows, iRowBlkA + szBlock); ++i)
        C(i, j) += A(i, k) * B(k, j);
}
const int szBlock = 256;
}  // namespace

Matrix operator*(const Matrix& A, const Matrix& B) {
  Matrix C(A.nbRows, B.nbCols, 0.0);

  /* Classique */
  // prodSubBlocks(0, 0, 0, std::max({A.nbRows, B.nbCols, A.nbCols}), A, B, C);  // Pas fait par bloc ici : le sous bloc est la matrice en entier

  /* Par bloc */
  // Triple boucle sur les indices des blocs
  // Parcours par blocs
  #pragma omp parallel for
  for (int iRowBlkA = 0; iRowBlkA < A.nbRows; iRowBlkA += szBlock) {
    for (int iColBlkB = 0; iColBlkB < B.nbCols; iColBlkB += szBlock) {
      for (int iColBlkA = 0; iColBlkA < A.nbCols; iColBlkA += szBlock) {
        // Multiplie les blocs correspondants
        prodSubBlocks(iRowBlkA, iColBlkB, iColBlkA, szBlock, A, B, C);
      }
    }
  }

  std::cout<<szBlock<<std::endl;


  return C;
}
