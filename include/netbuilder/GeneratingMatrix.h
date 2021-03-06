// This file is part of LatNet Builder.
//
// Copyright (C) 2012-2021  The LatNet Builder author's, supervised by Pierre L'Ecuyer, Universite de Montreal.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * \file
 * This file contains the definition of generating matrices in base 2
 */ 

#ifndef NETBUILDER__GENERATING_MATRIX_H
#define NETBUILDER__GENERATING_MATRIX_H

#include <boost/dynamic_bitset.hpp> 
#include <iostream>
#include <string>
#include <algorithm>

#include "latbuilder/LFSR258.h"
#include "latbuilder/UniformUIntDistribution.h"


namespace NetBuilder {

/** This class implements a generating matrix of a digital net in base 2.
 * 
 * Internally, a matrix is represented as a <code>std::vector</code> of rows implemented by
 * <code>boost::dynamic_bitset</code>. This internal representation allows to work with
 * arbitrarly large matrices. The choice of representing the matrix by its rows and not its columns
 * comes from the rank computation algorithm, which is the most complicated algorithm handling matrices in the software.
 * 
 * For now, the computation of the points from the matrices is done in latbuilder/Storage-SIMPLE-DIGITAL.h.
 * TODO: add more explanation on this. The basic idea is that we do not need to explicitely compute the points anywhere 
 * in LatNet Builder, but map a matrix to a permutation of {0, 1/n, ...,  1}.
 */ 
class GeneratingMatrix {

    public:

        /// Type for the rows of the matrices.
        typedef boost::dynamic_bitset<> Row; 

        /// Type for references to rows.
        typedef Row::reference reference;

        /// Type for unsigned long.
        typedef unsigned long uInteger;

        /** Constructs a generating matrix with all entries set to zero.
         * @param nRows Number of rows.
         * @param nCols Number of columns.
         */  
        GeneratingMatrix(unsigned int nRows = 0, unsigned int nCols = 0);

        /** Constructs a generating matrix with rows initialized 
         * using the given integers. The elements of a row
         * are the binary digits of the corresponding integer, 
         * with the least significant bit on the left.
         * @param nRows Number of rows.
         * @param nCols Number of columns.
         * @param init  Vector of uInteger of length nRows
         */  
        GeneratingMatrix(unsigned int nRows, unsigned int nCols, std::vector<uInteger> init);

        /** Returns the number of columns of the matrix. */
        unsigned int nCols() const;

        /** Returns the number of rows of the matrix. */
        unsigned int nRows() const;

        /** Resizes the matrix to the given shape. Potential new elements are set to zero.
         * @param nRows is the new number of rows of the matrix
         * @param nCols is the new number of columns of the matrix
         */ 
        void resize(unsigned int nRows, unsigned int nCols);

        /** Returns the element at position \c i, \c j of the matrix.
         * @param i Row index.
         * @param j Column index.
         */ 
        bool operator()(unsigned int i, unsigned j) const;

        /** Returns a reference to the element at position \c i, \c j of the matrix.
         * @param i Row index.
         * @param j Column index.
         */ 
        reference operator()(unsigned int i, unsigned int j);

        /** Flip the element at at position \c i, \c j of the matrix.
         * @param i Row index.
         * @param j Column index.
         */ 
        void flip(unsigned int i, unsigned int j);
         

        /** Returns the row at position \c i of the matrix.
         * @param i Position of the row.
         */ 
        Row operator[](unsigned int i) const;

        /** Returns a reference to the row at position \c i of the matrix.
         * @param i Position of the row.
         */ 
        Row& operator[](unsigned int i);

        /** Returns the upper-left submatrix with \c nRows rows and \c nCols columns.
         * @param nRows Number of rows.
         * @param nCols Number of columns.
         * @return A copy of the submatrix.
         */ 
        GeneratingMatrix upperLeftSubMatrix(unsigned int nRows, unsigned int nCols) const;

        /** Returns the submatrix with upper-left corner at position \c startingRow, \c startingCol
         * with \c nRows rows and \c nCols columns.
         * @param startingRow Row position of the upper-left corner.
         * @param startingCol Column position of the upper-left corner.
         * @param nRows Number of rows.
         * @param nCols Number of columns.
         * @return A copy of the submatrix.
         */ 
        GeneratingMatrix subMatrix(unsigned int startingRow, unsigned int startingCol, unsigned nRows, unsigned nCols) const;

        /**
         * Computes the product of the matrix by matrix \c m.
         * @param m Right multiplier.
         */ 
        GeneratingMatrix operator*(const GeneratingMatrix& m) const;

        /** Swap the rows at position i1 and i2 of the matrix.
         * @param i1 Position of the first row.
         * @param i2 Position of the second row.
         */
        void swapRows(unsigned int i1, unsigned int i2);

        /**
         * Extends the matrix by stacking on the right the matrix \c block.
         * @param block The matrix to stack. Should have the same number of rows as the base matrix.
         */ 
        void stackRight(const GeneratingMatrix& block);

        /**
         * Extends the matrix by stacking below the matrix \c block.
         * @param block The matrix to stack. Should have the same number of columns as the base matrix.
         */ 
        void stackBelow(GeneratingMatrix block);

        /** Overloads of << operator to print matrices. */
        friend std::ostream& operator<<(std::ostream& os, const GeneratingMatrix& mat);

        std::string formatToColumnsReverse(unsigned int nBits = 31) const;

        /** Returns an integer representation of the columns of the matrix. A column is read as a bit string
         * with highest bit in first position. This function is used to generate the points from the digital net.
         */ 
        std::vector<unsigned long> getColsReverse() const;

        /** Creates a matrix from its reversed column representation.
         * @param nInputRows Number of bits in the integer representation of the columns. Typically equals 31.
         * @param nOutputRows Number of rows of the matrix returned by the function. Rows below are ignored. Typically equals the number of columns.
         * @param columns Integer representation of the columns of the matrix.
         */ 
        static GeneratingMatrix fromColsReverse(unsigned int nInputBits, unsigned int nOutputRows, std::vector<unsigned long> columns);

        /**
         * Creates a matrix with ones on the main diagonal, random bits below the main diagonal, and zeros above.
         * TODO: give the maximum values for nRows and nCols for this to work.
         * @param nRows Number of rows of the matrix.
         * @param nCols Number of columns of the matrix.
         * @param randomGen Random Number Generator. By default it is the <tt>LFSR258</tt> generator by L'Ecuyer \cite rLEC99a.
         */ 
        template<typename RAND>
        static GeneratingMatrix createRandomLowerTriangularMatrix(unsigned int nRows, unsigned int nCols, RAND& randomGen) {
            std::vector<GeneratingMatrix::uInteger> res(nRows, 0);
            unsigned long diagonalCoeff = 1 << (nCols);
            LatBuilder::UniformUIntDistribution<unsigned long, LatBuilder::LFSR258> m_unif(0, diagonalCoeff - 1);
            for(unsigned int i = 0; i < std::min(nCols, nRows); ++i)
            {
                res[i] = ((diagonalCoeff + m_unif(randomGen)) >> (nCols-i));
            }
            for(unsigned int i = nCols; i < nRows; ++i)
            {
                res[i] = m_unif(randomGen);
            }
            return GeneratingMatrix(nRows, nCols, res);
        };

    private:
        std::vector<boost::dynamic_bitset<>> m_data; // data internal representantion
        unsigned int m_nRows; // number of rows of the matrix
        unsigned int m_nCols; // number of columns of the matrix
};

}
#endif