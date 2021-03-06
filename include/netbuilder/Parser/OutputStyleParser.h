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

#ifndef NETBUILDER__PARSER__OUTPUT_STYLE_PARSER_H
#define NETBUILDER__PARSER__OUTPUT_STYLE_PARSER_H

#include "netbuilder/Types.h"

namespace NetBuilder { namespace Parser {


/**
 * Parser for output style.
 */
template <NetConstruction NC>
struct OutputStyleParser {};

template<>
struct OutputStyleParser<NetConstruction::SOBOL>
{
   typedef NetBuilder::OutputStyle result_type;

   static result_type parse(const std::string& str)
   {
      if (str == "sobol")
      {
        return NetBuilder::OutputStyle::SOBOL;
      }
      else if (str == "soboljk")
      {
        return NetBuilder::OutputStyle::SOBOLJK;
      }
      else if (str == "net")
      {
        return NetBuilder::OutputStyle::NET;
      }
      else if (str == "")
      {
        return NetBuilder::OutputStyle::SOBOL;
      }
      else
      {
        std::cout << "WARNING: cannot parse output style string. Default output style: SOBOL" << std::endl;
        return NetBuilder::OutputStyle::SOBOL;
      }
   }
};

template<>
struct OutputStyleParser<NetConstruction::POLYNOMIAL>
{
   typedef NetBuilder::OutputStyle result_type;

   static result_type parse(const std::string& str)
   {
      if (str == "lattice")
      {
        return NetBuilder::OutputStyle::LATTICE;
      }
      else if (str == "net")
      {
        return NetBuilder::OutputStyle::NET;
      }
      else if (str == "")
      {
        return NetBuilder::OutputStyle::LATTICE;
      }
      else
      {
        std::cout << "WARNING: cannot parse output style string. Default output style: LATTICE" << std::endl;
        return NetBuilder::OutputStyle::LATTICE;
      }
   }
};

template<>
struct OutputStyleParser<NetConstruction::EXPLICIT>
{
   typedef NetBuilder::OutputStyle result_type;

   static result_type parse(const std::string& str)
   {
      if (str == "net")
      {
        return NetBuilder::OutputStyle::NET;
      }
      else if (str == "")
      {
        return NetBuilder::OutputStyle::NET;
      }
      else
      {
        std::cout << "WARNING: cannot parse output style string. Default output style: NET" << std::endl;
        return NetBuilder::OutputStyle::NET;
      }
   }
};

template<>
struct OutputStyleParser<NetConstruction::LMS>
{
   typedef NetBuilder::OutputStyle result_type;

   static result_type parse(const std::string& str)
   {
      if (str == "net")
      {
        return NetBuilder::OutputStyle::NET;
      }
      else if (str == "randomized")
      {
        return NetBuilder::OutputStyle::RANDOMIZED_NET;
      }
      else if (str == "")
      {
        return NetBuilder::OutputStyle::RANDOMIZED_NET;
      }
      else
      {
        std::cout << "WARNING: cannot parse output style string. Default output style: RANDOMIZED" << std::endl;
        return NetBuilder::OutputStyle::RANDOMIZED_NET;
      }
   }
};

}}
#endif
