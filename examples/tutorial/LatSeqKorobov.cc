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

#include "latbuilder/SizeParam.h"
#include "latbuilder/LatSeq/Korobov.h"
#include "latbuilder/GenSeq/GeneratingValues.h"
#include "latbuilder/TextStream.h"

#include "Path.h"

#include <iostream>

using namespace LatBuilder;
using TextStream::operator<<;

//! [main]
template<LatticeType LA>
void test(typename LatticeTraits<LA>::Modulus modulus){
   SizeParam<LA, EmbeddingType::UNILEVEL> size(modulus);
   Dimension dim = 3;

   typedef GenSeq::GeneratingValues<LA, Compress::NONE> Coprime;

   //! [latSeq]
   auto latSeq = LatSeq::korobov(size, Coprime(size), dim);
   //! [latSeq]

   std::cout << latSeq << std::endl;
}
//! [main]

int main()
{
   SET_PATH_TO_LATNETBUILDER_FOR_EXAMPLES();
   //! [output]
   test<LatticeType::ORDINARY>(7);
   test<LatticeType::POLYNOMIAL>(PolynomialFromInt(7));
   //! [output]

   return 0;
}
