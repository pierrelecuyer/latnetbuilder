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

#include "netbuilder/Types.h"
#include "netbuilder/Util.h"
#include "netbuilder/DigitalNet.h"


#include "netbuilder/Task/CBCSearch.h"
#include "netbuilder/Task/RandomCBCExplorer.h"
#include "netbuilder/Task/FullCBCExplorer.h"
#include "netbuilder/Task/MixedCBCExplorer.h"

#include "netbuilder/Task/ExhaustiveSearch.h"
#include "netbuilder/Task/RandomSearch.h"

#include "netbuilder/FigureOfMerit/FigureOfMerit.h"
#include "netbuilder/FigureOfMerit/WeightedFigureOfMerit.h"
#include "netbuilder/FigureOfMerit/TValueProjMerit.h"
#include "netbuilder/FigureOfMerit/CombinedFigureOfMerit.h"

#include "latcommon/Weights.h"
#include "latcommon/UniformWeights.h"

#include <iostream>
#include <limits>

using namespace NetBuilder;
using namespace FigureOfMerit;

int main(int argc, const char *argv[])
{
    unsigned int s = 5;
    unsigned int m = 20;

    unsigned int r = 1000;
    auto weights = std::make_unique<LatCommon::UniformWeights>(1);

    auto projDep = std::make_unique<TValueProjMerit<PointSetType::UNILEVEL>>(2);

    auto fig = std::make_unique<WeightedFigureOfMerit<TValueProjMerit<PointSetType::UNILEVEL>>>(1, std::move(weights), std::move(projDep));

    // auto explorer = std::make_unique<Task::RandomCBCExplorer<NetConstruction::SOBOL>>(s,m,r);
    // auto search = Task::CBCSearch<NetConstruction::SOBOL,Task::RandomCBCExplorer>(s,m,std::move(fig),std::move(explorer));

    // auto explorer = std::make_unique<Task::FullCBCExplorer<NetConstruction::SOBOL>>(s,m);
    // auto search = Task::CBCSearch<NetConstruction::SOBOL,Task::FullCBCExplorer>(s,m,std::move(fig),std::move(explorer));

    // auto explorer = std::make_unique<Task::MixedCBCExplorer<NetConstruction::SOBOL>>(s, m, 5, r);
    // auto search = Task::CBCSearch<NetConstruction::SOBOL,Task::MixedCBCExplorer>(s,m,std::move(fig),std::move(explorer));

    // auto search = Task::ExhaustiveSearch<NetConstruction::SOBOL>(s,m,std::move(fig));

    auto search = Task::RandomSearch<NetConstruction::SOBOL>(s,m,std::move(fig),r*s);
    
    std::cout << search.designParameter() << std::endl;

    search.onNetSelected().connect( [] (const Task::Search<NetConstruction::SOBOL>& s) { std::cout << "Finished." << std::endl;} );
    search.onFailedSearch().connect( [] (const Task::Search<NetConstruction::SOBOL>& s) { std::cout << "Search failed." <<  std::endl;} );
    search.execute();
    std::cout << search.netOutput() << std::endl;
    for( unsigned int dim = 1; dim <=s; ++dim)
    {
        std::cout << search.netOutput().generatingMatrix(dim) << std::endl;
    }
    std::cout << search.meritValueOutput() << std::endl;

    return 0;
}
