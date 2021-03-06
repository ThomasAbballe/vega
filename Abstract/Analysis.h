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
 * Analysis.h
 *
 *  Created on: Sep 4, 2013
 *      Author: devel
 */

#ifndef ANALYSIS_H_
#define ANALYSIS_H_

#include <climits>

#include <map>
#include <set>
#include <utility>
#include <list>
#include <set>
#include "MeshComponents.h"
#include "Loading.h"
#include "Constraint.h"
#include "Objective.h"
#include "Value.h"
#include "Object.h"

namespace vega {

using namespace std;
class Model;
class ModelConfiguration;

/**
 * Responsible of keeping options to use in a finite element calculation
 */
class Analysis: public Identifiable<Analysis> {
private:
    friend ostream &operator<<(ostream &out, const Analysis& analysis);    //output
    std::map<int, char> boundaryDOFSByNodePosition;
    const string label;         /**< User defined label for this instance of Analysis. **/
public:
    enum Type {
        LINEAR_MECA_STAT,
        LINEAR_MODAL,
        LINEAR_DYNA_MODAL_FREQ,
        NONLINEAR_MECA_STAT,
        UNKNOWN,
    };
protected:
    list<std::shared_ptr<Reference<LoadSet>>>loadSet_references;
    list<std::shared_ptr<Reference<ConstraintSet>>> constraintSet_references;
    list<std::shared_ptr<Reference<Objective>>> assertion_references;

public:
    Model& model;
    const Type type;
    static const string name;     /**< String conversion of the object, i.e "Analysis" **/
    static const map<Type,string> stringByType;
    std::shared_ptr<Analysis> previousAnalysis;

    Analysis(Model& model, const Type Type, const string original_label = "", const int original_id = NO_ORIGINAL_ID);

    void add(const Reference<LoadSet>&);
    void add(const Reference<ConstraintSet>&);
    void add(const Reference<Objective>&);

    bool contains(const Reference<LoadSet>) const;
    bool contains(const Reference<ConstraintSet>) const;
    bool contains(const Reference<Objective>) const;

    void remove(const Reference<LoadSet>);
    void remove(const Reference<ConstraintSet>);
    void remove(const Reference<Objective>);

    const string getLabel() const {return label;}  /**< Getter for the label variable **/

    /**
     * retrieve the ConstraintSets specific to this analysis
     * plus eventually the common ConstraintSet of all analyzes of the model
     */
    const vector<std::shared_ptr<ConstraintSet>> getConstraintSets() const;

    /**
     * retrieve the LoadSets specific to this analysis
     * plus eventually the common LoadSet of all analyzes of the model
     */
    const vector<std::shared_ptr<LoadSet>> getLoadSets() const;
    const vector<std::shared_ptr<BoundaryCondition>> getBoundaryConditions() const;
    const vector<std::shared_ptr<Assertion>> getAssertions() const;

    /**
     * Return true if the analysis has at least one SPC (or equivalent SPCD, MPCD, etc)
     * ConstraintSet or Constraint. Check both common and specific ConstraintSet.
     */
    bool hasSPC() const;

    void removeSPCNodeDofs(SinglePointConstraint& spc, int nodePosition, const DOFS dofs);
    void addBoundaryDOFS(int nodePosition, const DOFS dofs);
    const DOFS findBoundaryDOFS(int nodePosition) const;
    const set<int> boundaryNodePositions() const;

    virtual std::shared_ptr<Analysis> clone() const =0;
    bool validate() const override;

    virtual ~Analysis();

};

class LinearMecaStat: public Analysis {
public:
    LinearMecaStat(Model& model, const string original_label = "", const int original_id = NO_ORIGINAL_ID);
    std::shared_ptr<Analysis> clone() const;
};

class NonLinearMecaStat: public Analysis {
public:
    Reference<Objective> strategy_reference;
    NonLinearMecaStat(Model& model, const NonLinearStrategy& strategy, const string original_label = "",
            const int original_id = NO_ORIGINAL_ID);
    NonLinearMecaStat(Model& model, const int strategy_original_id, const string original_label = "",
            const int original_id = NO_ORIGINAL_ID);
    std::shared_ptr<Analysis> clone() const;
    bool validate() const override;
};

class LinearModal: public Analysis {
protected:
    Reference<Objective> frequency_band_reference;
public:
    LinearModal(Model& model, const FrequencyBand& frequency_band, const string original_label = "",
            const int original_id = NO_ORIGINAL_ID, const Type type = LINEAR_MODAL);
    LinearModal(Model& model, const int frequency_band_original_id, const string original_label = "",
            const int original_id = NO_ORIGINAL_ID, const Type type = LINEAR_MODAL);
    std::shared_ptr<FrequencyBand> getFrequencyBand() const;
    std::shared_ptr<Analysis> clone() const;
    bool validate() const override;
};

class LinearDynaModalFreq: public LinearModal {
protected:
    Reference<Objective> modal_damping_reference;
    Reference<Objective> frequency_values_reference;
public:
    LinearDynaModalFreq(Model& model, const FrequencyBand& frequency_band,
            const ModalDamping& modal_damping, const FrequencyValues& frequency_values,
            const bool residual_vector = false,
            const string original_label = "", const int original_id = NO_ORIGINAL_ID);
    LinearDynaModalFreq(Model& model, const int frequency_band_original_id,
            const int modal_damping_original_id, const int frequency_value_original_id,
            const bool residual_vector = false,
            const string original_label = "", const int original_id = NO_ORIGINAL_ID);
    const bool residual_vector;
    std::shared_ptr<ModalDamping> getModalDamping() const;
    std::shared_ptr<FrequencyValues> getFrequencyValues() const;
    std::shared_ptr<Analysis> clone() const;
    bool validate() const override;
};

} /* namespace vega */
#endif /* ANALYSIS_H_ */

