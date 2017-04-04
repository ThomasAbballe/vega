/*
 * Copyright (C) Alneos, s. a r. l. (contact@alneos.fr) 
 * This file is part of Vega.
 *
 *   Vega is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   Vega is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Vega.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ConfigurationParameters.h
 *
 *  Created on: Aug 30, 2013
 *      Author: devel
 */

#ifndef CONFIGURATIONPARAMETERS_H_
#define CONFIGURATIONPARAMETERS_H_

#define BOOST_SYSTEM_NO_DEPRECATED 1
#include <string>
#ifdef __GNUC__
// Avoid tons of warnings with the following code
#pragma GCC system_header
#endif
#include <boost/filesystem.hpp>
#include <boost/bimap.hpp>

namespace vega {

namespace fs = boost::filesystem;

enum SolverName {
    CODE_ASTER = 2,
    NASTRAN = 3,
    SYSTUS = 5
};

enum LogLevel {
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE
};

class Solver {
private:
    friend std::ostream &operator<<(std::ostream &out, const Solver& solver); //output
    SolverName solverName;
    const static boost::bimap<SolverName, std::string> SOLVERNAME_BY_SOLVER;
    public:
    Solver(SolverName name);
    SolverName getSolverName() const;
    static Solver fromString(std::string solverTypeName);
    ~Solver();
};
/**
 * Contains configuration of model operations most of them done during finish()
 * method.
 */
class ModelConfiguration {
public:
    ModelConfiguration(bool virtualDiscrets = true, LogLevel logLevel = LogLevel::INFO,
            bool createSkin = true, bool emulateLocalDisplacement = true,
            bool displayHomogeneousConstraint = false, bool emulateAdditionalMass = true,
            bool replaceCombinedLoadSets = true, bool removeIneffectives = true,
            bool partitionModel = false, bool replaceDirectMatrices = true,
            bool removeRedundantSpcs = true,
            bool makeCellsFromDirectMatrices = false);
    virtual ~ModelConfiguration() {
    }

    const bool virtualDiscrets;
    LogLevel logLevel;
    const bool createSkin;
    const bool emulateLocalDisplacement;
    const bool displayHomogeneousConstraint;
    const bool emulateAdditionalMass;
    const bool replaceCombinedLoadSets;
    const bool removeIneffectives;
    /**
     * Create a partition of materials and elements in the model, so that
     * materials are assigned to elements.
     * This is necessary for output languages such as Nastran.
     * TODO: this is unimplemented at the moment.
     */
    const bool partitionModel;
    const bool replaceDirectMatrices;
    const bool removeRedundantSpcs;
    /**
     *  ElementSets of Direct Matrices (DISCRETE_0D, DISCRETE_1D, STIFFNESS_MATRIX, MASS_MATRIX, DAMPING_MATRIX)
     *  generally don't have associated cells/cellgroup. This may causes problems in generic element writer,
     *  such as in SYSTUS.
     *  This bool commands the use of Model::makeCellsFromDirectMatrices() in Model::finish(), which creates the
     *  needed cells.
     */
    const bool makeCellsFromDirectMatrices;
};
// TODO: THe Configuration Parameters should be much more generalized. With this,
// it's a pain in the keyboard to add options!!
class ConfigurationParameters {
public:
    enum TranslationMode {
        BEST_EFFORT = 0, // 
        MESH_AT_LEAST = 1, //
        MODE_STRICT = 2 //
    };

    ConfigurationParameters(std::string inputFile, Solver outputSolver, std::string solverVersion =
            "", std::string outputFile = "vega", std::string outputPath = ".", LogLevel logLevel =
            LogLevel::INFO, TranslationMode translationMode = BEST_EFFORT, fs::path resultFile = "",
            double testTolerance = 0.02, bool runSolver = false, std::string solverServer = "",
            std::string solverCommand = "",
            std::string systusRBE2TranslationMode = "lagrangian", double systusRBE2Rigidity= 0.0,
            std::string systusOptionAnalysis="auto", std::string systusOutputProduct="systus",
            std::vector< std::vector<int> > systusSubcases = {});
    const ModelConfiguration getModelConfiguration() const;
    virtual ~ConfigurationParameters();

    const std::string inputFile;
    const Solver outputSolver;
    const std::string solverVersion;
    std::string outputFile;
    std::string outputPath;
    const LogLevel logLevel;
    const TranslationMode translationMode;
    const fs::path resultFile;
    const double testTolerance;
    const bool runSolver;
    const std::string solverServer;
    const std::string solverCommand;
    const std::string systusRBE2TranslationMode;
    const double systusRBE2Rigidity;
    const std::string systusOptionAnalysis;
    const std::string systusOutputProduct;
    const std::vector< std::vector<int> > systusSubcases;
};

}
#endif /* CONFIGURATIONPARAMETERS_H_ */
