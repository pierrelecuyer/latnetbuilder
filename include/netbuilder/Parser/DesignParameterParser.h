// This file is part of Lattice Builder.
//
// Copyright (C) 2012-2016  Pierre L'Ecuyer and Universite de Montreal
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

#ifndef NETBUILDER__PARSER__DESIGN_PARAMETER_PARSER_H
#define NETBUILDER__PARSER__DESIGN_PARAMETER_PARSER_H

#include "latbuilder/Parser/Common.h"
#include "netbuilder/Types.h"
#include "netbuilder/Util.h"

namespace NetBuilder { namespace Parser {
namespace lbp = LatBuilder::Parser;
/**
 * Exception thrown when trying to parse an invalid size parameter.
 */
class BadDesignParameter : public lbp::ParserError {
public:
   BadDesignParameter(const std::string& message):
      lbp::ParserError("cannot parse design parameter string: " + message)
   {}
};

/**
 * Parser for construction parameters.
 */
template<NetConstruction NC, PointSetType PST>
struct DesignParameterParser {};

template<PointSetType PST>
struct DesignParameterParser<NetConstruction::SOBOL, PST>
{
   typedef typename NetConstructionTraits<NetConstruction::SOBOL>::DesignParameter result_type;

   static result_type parse(Parser::CommandLine<NetConstruction::SOBOL, PST>& commandLine)
   {
         return commandLine.m_sizeParam.log2NumPoints();
   }
};

template<PointSetType PST>
struct DesignParameterParser<NetConstruction::POLYNOMIAL, PST>
{
   typedef typename NetConstructionTraits<NetConstruction::POLYNOMIAL>::DesignParameter result_type;

   static result_type parse(Parser::CommandLine<NetConstruction::POLYNOMIAL, PST>& commandLine)
   {
         return polynomialParserHelper(commandLine.s_designParameter);
   }
};

}}

#endif
