/*
 * Copyright (C) Alneos, s. a r. l. (contact@alneos.fr)
 * Released under the GNU General Public License
 *
 * MeshComponents.cpp
 *
 *  Created on: Nov 4, 2013
 *      Author: devel
 */

#include "MeshComponents.h"
#include "Mesh.h"
#include "Model.h"
#include <string>
#include <initializer_list>
#include <boost/lexical_cast.hpp>
#include <boost/assign.hpp>
#if defined VDEBUG && defined __GNUC__
#include <valgrind/memcheck.h>
#endif

namespace vega {
using boost::assign::list_of;
using boost::lexical_cast;
unordered_map<SpaceDimension::Code, SpaceDimension*, hash<int>> SpaceDimension::dimensionByCode =
		init_map();

SpaceDimension::SpaceDimension(Code code, int medcouplingRelativeMeshDimension) :
		code(code), relativeMeshDimension(medcouplingRelativeMeshDimension) {
#if defined VDEBUG && defined __GNUC__
	VALGRIND_CHECK_VALUE_IS_DEFINED(code);
	VALGRIND_CHECK_VALUE_IS_DEFINED(*this);
	VALGRIND_CHECK_VALUE_IS_DEFINED(SpaceDimension::dimensionByCode);
#endif
	SpaceDimension::dimensionByCode[code] = this;
}

const SpaceDimension SpaceDimension::DIMENSION_0D = SpaceDimension(DIMENSION0D_CODE, -3);
const SpaceDimension SpaceDimension::DIMENSION_1D = SpaceDimension(DIMENSION1D_CODE, -2);
const SpaceDimension SpaceDimension::DIMENSION_2D = SpaceDimension(DIMENSION2D_CODE, -1);
const SpaceDimension SpaceDimension::DIMENSION_3D = SpaceDimension(DIMENSION3D_CODE, 0);

bool SpaceDimension::operator<(const SpaceDimension &other) const {
	return this->code < other.code;
}

bool SpaceDimension::operator==(const SpaceDimension &other) const {
	return this->code == other.code;
}

unordered_map<CellType::Code, CellType*, hash<int>> CellType::typeByCode;

CellType::CellType(CellType::Code code, int numNodes, SpaceDimension dimension,
		const string& description) :
		code(code), numNodes(numNodes), dimension(dimension), description(description) {
	typeByCode.insert(make_pair(code, this));
	specificSize= (numNodes>0);
}

CellType::CellType(const CellType& other) :
		code(other.code), numNodes(other.numNodes), dimension(other.dimension), description(
				other.description), specificSize(other.specificSize) {
}

bool CellType::operator==(const CellType &other) const {
	return this->code == other.code;
}

bool CellType::operator<(const CellType& other) const {
	return this->code < other.code;
}
/*
 const CellType& CellType::operator=(const CellType other) {
 this->code = other.code;
 this->dimension = other.dimension;
 this->numNodes = other.numNodes;
 return *this;
 }
 */
ostream &operator<<(ostream &out, const CellType& cellType) {
	out << "CellType[" << cellType.description << "]";
	return out;
}

string CellType::to_str() const{
	return "CellType[" +this->description + "]";
}

const CellType CellType::POINT1 = CellType(POINT1_CODE, 1, SpaceDimension::DIMENSION_0D, "POINT1");
const CellType CellType::SEG2 = CellType(SEG2_CODE, 2, SpaceDimension::DIMENSION_1D, "SEG2");
const CellType CellType::SEG3 = CellType(SEG3_CODE, 3, SpaceDimension::DIMENSION_1D, "SEG3");
const CellType CellType::SEG4 = CellType(SEG4_CODE, 4, SpaceDimension::DIMENSION_1D, "SEG4");
const CellType CellType::SEG5 = CellType(SEG5_CODE, 5, SpaceDimension::DIMENSION_1D, "SEG5");
//const CellType CellType::POLYL = CellType(POLYL_CODE, -1, SpaceDimension::DIMENSION_1D, "POLYL");
const CellType CellType::TRI3 = CellType(TRI3_CODE, 3, SpaceDimension::DIMENSION_2D, "TRI3");
const CellType CellType::QUAD4 = CellType(QUAD4_CODE, 4, SpaceDimension::DIMENSION_2D, "QUAD4");
//const CellType CellType::POLYGON = CellType(POLYGON_CODE, -1, SpaceDimension::DIMENSION_2D,
//		"POLYGON");
const CellType CellType::TRI6 = CellType(TRI6_CODE, 6, SpaceDimension::DIMENSION_2D, "TRI6");
const CellType CellType::TRI7 = CellType(TRI7_CODE, 7, SpaceDimension::DIMENSION_2D, "TRI7");
const CellType CellType::QUAD8 = CellType(QUAD8_CODE, 8, SpaceDimension::DIMENSION_2D, "QUAD8");
const CellType CellType::QUAD9 = CellType(QUAD9_CODE, 9, SpaceDimension::DIMENSION_2D, "QUAD9");
//const CellType CellType::QPOLYG = CellType(QPOLYG_CODE, -1,
//		SpaceDimension::DIMENSION_2D, "QPOLYG");
const CellType CellType::TETRA4 = CellType(TETRA4_CODE, 4, SpaceDimension::DIMENSION_3D, "TETRA4");
const CellType CellType::PYRA5 = CellType(PYRA5_CODE, 5, SpaceDimension::DIMENSION_3D, "PYRA5");
const CellType CellType::PENTA6 = CellType(PENTA6_CODE, 6, SpaceDimension::DIMENSION_3D, "PENTA6");
const CellType CellType::HEXA8 = CellType(HEXA8_CODE, 8, SpaceDimension::DIMENSION_3D, "HEXA8");
const CellType CellType::TETRA10 = CellType(TETRA10_CODE, 10, SpaceDimension::DIMENSION_3D,
		"TETRA10");
const CellType CellType::HEXGP12 = CellType(HEXGP12_CODE, 12, SpaceDimension::DIMENSION_3D,
		"HEXGP12");
const CellType CellType::PYRA13 = CellType(PYRA13_CODE, 13, SpaceDimension::DIMENSION_3D, "PYRA13");
const CellType CellType::PENTA15 = CellType(PENTA15_CODE, 15, SpaceDimension::DIMENSION_3D,
		"PENTA15");
const CellType CellType::HEXA20 = CellType(HEXA20_CODE, 20, SpaceDimension::DIMENSION_3D, "HEXA20");
const CellType CellType::HEXA27 = CellType(HEXA27_CODE, 27, SpaceDimension::DIMENSION_3D,
		"DIMENSION_3D");
//const CellType CellType::POLYHED = CellType(POLYHED_CODE, -1, SpaceDimension::DIMENSION_3D,
//		"POLYHED");

//TODO: Ugly fix because POLYHED and co are not working yet. We need an element with undefined number of nodes. :/
const CellType CellType::POLY3  = CellType(POLY3_CODE, 3, SpaceDimension::DIMENSION_3D, "POLY3");
const CellType CellType::POLY4  = CellType(POLY4_CODE, 4, SpaceDimension::DIMENSION_3D, "POLY4");
const CellType CellType::POLY5  = CellType(POLY5_CODE, 5, SpaceDimension::DIMENSION_3D, "POLY5");
const CellType CellType::POLY6  = CellType(POLY6_CODE, 6, SpaceDimension::DIMENSION_3D, "POLY6");
const CellType CellType::POLY7  = CellType(POLY7_CODE, 7, SpaceDimension::DIMENSION_3D, "POLY7");
const CellType CellType::POLY8  = CellType(POLY8_CODE, 8, SpaceDimension::DIMENSION_3D, "POLY8");
const CellType CellType::POLY9  = CellType(POLY9_CODE, 9, SpaceDimension::DIMENSION_3D, "POLY9");
const CellType CellType::POLY10 = CellType(POLY10_CODE, 10, SpaceDimension::DIMENSION_3D, "POLY10");
const CellType CellType::POLY11 = CellType(POLY11_CODE, 11, SpaceDimension::DIMENSION_3D, "POLY11");
const CellType CellType::POLY12 = CellType(POLY12_CODE, 12, SpaceDimension::DIMENSION_3D, "POLY12");
const CellType CellType::POLY13 = CellType(POLY13_CODE, 13, SpaceDimension::DIMENSION_3D, "POLY13");
const CellType CellType::POLY14 = CellType(POLY14_CODE, 14, SpaceDimension::DIMENSION_3D, "POLY14");
const CellType CellType::POLY15 = CellType(POLY15_CODE, 15, SpaceDimension::DIMENSION_3D, "POLY15");
const CellType CellType::POLY16 = CellType(POLY16_CODE, 16, SpaceDimension::DIMENSION_3D, "POLY16");
const CellType CellType::POLY17 = CellType(POLY17_CODE, 17, SpaceDimension::DIMENSION_3D, "POLY17");
const CellType CellType::POLY18 = CellType(POLY18_CODE, 18, SpaceDimension::DIMENSION_3D, "POLY18");
const CellType CellType::POLY19 = CellType(POLY19_CODE, 19, SpaceDimension::DIMENSION_3D, "POLY19");
const CellType CellType::POLY20 = CellType(POLY20_CODE, 20, SpaceDimension::DIMENSION_3D, "POLY20");


const CellType* CellType::findByCode(CellType::Code code) {
	return CellType::typeByCode[code];
}

Group::Group(Mesh* mesh, const string& name, Type type, int _id, string comment) :
		Identifiable(_id), mesh(mesh), name(name), type(type), comment(comment) {
}

const string Group::getName() const {
	return this->name;
}

const string Group::getComment() const {
	return this->comment;
}

Group::~Group() {

}
/*******************
 * NodeGroup
 */
NodeGroup::NodeGroup(Mesh* mesh, const string& name, int groupId, const string& comment) :
		Group(mesh, name, NODEGROUP, groupId, comment) {
}

void NodeGroup::addNode(int nodeId) {
	int nodePosition = this->mesh->findOrReserveNode(nodeId);
	_nodePositions.insert(nodePosition);
}

void NodeGroup::addNodeByPosition(int nodePosition) {
	_nodePositions.insert(nodePosition);
}

void NodeGroup::removeNodeByPosition(int nodePosition) {
	if (_nodePositions.find(nodePosition) == _nodePositions.end()) {
		throw logic_error("Node position not present : " + to_string(nodePosition));
	}
	for (auto it = _nodePositions.begin(); it != _nodePositions.end();) {
		if (*it == nodePosition) {
			_nodePositions.erase(it);
			return;
		} else {
			it++;
		}
	}
}

const std::set<int> NodeGroup::nodePositions() const {
	return _nodePositions;
}

const set<int> NodeGroup::getNodeIds() const {
	set<int> nodeIds;
	for (int position : _nodePositions) {
		nodeIds.insert(mesh->nodes.nodeDatas[position].id);
	}
	return nodeIds;
}

CellGroup::CellGroup(Mesh* mesh, const string& name, int groupId, const string& comment ) :
		Group(mesh, name, CELLGROUP, groupId, comment) {

}
/*
 void CellGroup::addCell(const CellPositionInfo* cellPositionInfo) {
 this->cellIds.add(cellPositionInfo);
 }*/

void CellGroup::addCell(int cellId) {
	this->cellIds.insert(cellId);
	if (this->mesh->logLevel >= LogLevel::TRACE) {
		cout << "Group MA :" << this->getName() << ", Added: " << cellId << endl;
	}
}

vector<Cell> CellGroup::getCells() {
	vector<Cell> result;
	for (int cellId : cellIds) {
		int cellPosition = mesh->findCellPosition(cellId);
		result.push_back(mesh->findCell(cellPosition));
	}
	return result;
}

vector<int> CellGroup::cellPositions() {
	vector<int> result;
	for (int cellId : cellIds) {
		result.push_back(mesh->findCellPosition(cellId));
	}
	return result;
}

const set<int> CellGroup::nodePositions() const {
	set<int> result;
	for (int cellId : cellIds) {
		int position = mesh->findCellPosition(cellId);
		Cell cell = mesh->findCell(position);
		result.insert(cell.nodePositions.begin(), cell.nodePositions.end());
	}
	return result;
}

CellGroup::~CellGroup() {
}

///////////////////////////////////////////////////////////////////////////////
/*                  Node                                                     */
///////////////////////////////////////////////////////////////////////////////
int Node::auto_node_id = 9999999;

Node::Node(int id, double lx, double ly, double lz, int position1, DOFS inElement1, int _positionCS, int _displacementCS) :
		id(id), position(position1), lx(lx), ly(ly), lz(lz), dofs(inElement1),
		positionCS(_positionCS), displacementCS(_displacementCS) {
    x=-2.0e+300;
    y=-2.0e+300;
    z=-2.0e+300;
}

const string Node::getMedName() const {
	return string("N") + lexical_cast<string>(position + 1);
}

void Node::buildGlobalXYZ(const Model *model){
    if (positionCS == CoordinateSystem::GLOBAL_COORDINATE_SYSTEM_ID){
        this->x=this->lx;
        this->y=this->ly;
        this->z=this->lz;
    }else{
        if (model == nullptr){
            ostringstream oss;
            oss << "ERROR: Model needed to access Local Coordinate System."<<endl;
            throw logic_error(oss.str());
        }
        shared_ptr<CoordinateSystem> coordSystem = model->getCoordinateSystemByPosition(positionCS);
        if (!coordSystem) {
            ostringstream oss;
            oss << "ERROR: Coordinate System of position " << positionCS << " for Node "<<this->id<<" not found.";
            // We should throw an error... but only in "strict mode".
            // For other, it's too harsh for a regular translation.
            //throw logic_error(oss.str());
            oss <<  " Global Coordinate System used instead."<< endl;
            cerr<< oss.str();
            this->x=this->lx;
            this->y=this->ly;
            this->z=this->lz;
            return;
        }

        VectorialValue gCoord = coordSystem->positionToGlobal(VectorialValue(this->lx,this->ly,this->lz));
        this->x= gCoord.x();
        this->y= gCoord.y();
        this->z= gCoord.z();
    }
}

ostream &operator<<(ostream &out, const Node& node) {
	out << "Node[id:" << node.id << ",x:" << node.x << ",y:" << node.y << ",z:" << node.z << " pos:"
			<< node.position << "]";
	return out;
}

NodeIterator::NodeIterator(const NodeStorage *nodeStorage, int position) :
		nodeStorage(nodeStorage), position(position) {
	this->endPosition = nodeStorage->mesh->countNodes();
}

void NodeIterator::increment() {
	position++;
	if (position > endPosition) {
		throw out_of_range(
				string("Iterator on nodes in position ") + lexical_cast<string>(position)
						+ " after end.");
	}
}

bool NodeIterator::hasNext() const {
	return (position < endPosition);
}

bool NodeIterator::equal(NodeIterator const& other) const {
	//this.mesh == other.mesh
	return this->position == other.position;
}

NodeIterator::~NodeIterator() {

}

NodeIterator& NodeIterator::operator ++() {
	increment();
	return *this;
}

NodeIterator NodeIterator::operator ++(int) {
	increment();
	return *this;
}

bool NodeIterator::operator ==(const NodeIterator& rhs) const {
	return this->position == rhs.position;
}

bool NodeIterator::operator !=(const NodeIterator& rhs) const {
	return this->position != rhs.position;
}

const Node NodeIterator::operator *() {
	return nodeStorage->mesh->findNode(position);
}

const Node NodeIterator::next() {
	Node result(nodeStorage->mesh->findNode(position));
	this->increment();
	return result;
}
///////////////////////////////////////////////////////////////////////////////
/*                             Cells                                         */
///////////////////////////////////////////////////////////////////////////////
int Cell::auto_cell_id = 9999999;

const unordered_map<CellType::Code, vector<vector<int>>, hash<int> > Cell::FACE_BY_CELLTYPE =
		init_faceByCelltype();

// http://www.code-aster.org/outils/med/html/connectivites.html
unordered_map<CellType::Code, vector<vector<int>>, hash<int> > Cell::init_faceByCelltype() {
	vector<vector<int> > hexa8list = list_of<vector<int>>( //
			list_of(1)(2)(3)(4)) //
			(list_of(5)(6)(7)(8)) //
			(list_of(1)(2)(6)(5)) //
			(list_of(2)(3)(7)(6)) //
			(list_of(3)(7)(8)(4)) //
			(list_of(1)(4)(8)(5)); //
	vector<vector<int> > tetra4list = list_of<vector<int>>( //
			list_of(1)(2)(3)) //
			(list_of(1)(4)(2)) //
			(list_of(1)(4)(3)) //
			(list_of(2)(3)(4)); //

	unordered_map<CellType::Code, vector<vector<int>>, hash<int> > result =
			boost::assign::map_list_of(CellType::HEXA8.code, hexa8list) //Hexa8
			(CellType::TETRA4.code, tetra4list); //Tetra4 end
	return result;
}

Cell::Cell(int id, const CellType &type, const std::vector<int> &nodeIds,
		const std::vector<int> &nodePositions, bool isvirtual,
		int cid, int element_id, int cellTypePosition) :
		id(id), hasOrientation(cid!=CoordinateSystem::GLOBAL_COORDINATE_SYSTEM_ID), type(type),
				nodeIds(nodeIds), nodePositions(nodePositions), isvirtual(isvirtual), elementId(
						element_id), cellTypePosition(cellTypePosition), cid(cid) {
}

string Cell::getMedName() const {
	return string("M") + lexical_cast<string>(id);
}

Cell::~Cell() {
}

int Cell::findNodeIdPosition(int node_id2) const {
	//|| cellType == CellType::TETRA10
	size_t node2connectivityPos = 0;
	for (; node2connectivityPos < nodeIds.size(); node2connectivityPos++) {
		if (nodeIds[node2connectivityPos] == node_id2) {
			break;
		}
	}
	if (node2connectivityPos == nodeIds.size()) {
		throw logic_error("node id " + to_string(node_id2) + " not in cell");
	}
	return (int) node2connectivityPos;
}

vector<int> Cell::faceids_from_two_nodes(int nodeId1, int nodeId2) const {
	int node1connectivityPos = findNodeIdPosition(nodeId1);
	int node2connectivityPos = findNodeIdPosition(nodeId2);

	if (type.dimension == SpaceDimension::DIMENSION_2D) {
		return vector<int>(nodeIds.begin(), nodeIds.end());
	}
	vector<int> nodePositions;
	//node2 is on the opposite face
	if (type.code == CellType::TETRA4.code) { //|| cellType == CellType::TETRA10
		vector<vector<int> > faceids = FACE_BY_CELLTYPE.find(CellType::TETRA4.code)->second;
		for (vector<int> faceid : faceids) {
			//0 based
			if (find(faceid.begin(), faceid.end(), node2connectivityPos + 1) == faceid.end()) {
				nodePositions.assign(faceid.begin(), faceid.end());
			}
		}
	} else if (type.code == CellType::HEXA8.code) {
		vector<vector<int> > faceids = FACE_BY_CELLTYPE.find(CellType::HEXA8.code)->second;
		for (vector<int> faceid : faceids) {
			//0 based
			if (find(faceid.begin(), faceid.end(), node2connectivityPos + 1) != faceid.end()
					&& find(faceid.begin(), faceid.end(), node1connectivityPos + 1)
							!= faceid.end()) {
				nodePositions.assign(faceid.begin(), faceid.end());
				break;
			}
		}
	} else {
		throw logic_error("FaceidfromtwoNodes not implemented");
	}
	vector<int> faceConnectivity;
	faceConnectivity.reserve(nodePositions.size());
	for (int nodeNum : nodePositions) {
		faceConnectivity.push_back(nodeIds[nodeNum - 1]);
	}
	return faceConnectivity;
}

ostream &operator<<(ostream &out, const Cell& cell) {
	out << "Cell[id:" << cell.id;
	out << ",type:" << cell.type.code;
	out << ",nodeIds:[";
	for (auto it = cell.nodeIds.begin(); it != cell.nodeIds.end(); ++it) {
		cout << "," << *it;
	}
	out << "]";
	return out;
}

CellIterator::CellIterator(const CellStorage* cellStorage, const CellType &cellType, bool begin) :
		cellStorage(cellStorage), endPosition(cellStorage->mesh->countCells(cellType)), cellType(cellType), position(
				begin ? 0 : endPosition) {
}

CellIterator::~CellIterator() {
}

const Cell CellIterator::next() {
	Cell result = dereference();
	increment(1);
	return result;
}

void CellIterator::increment(int i) {
	position += i;
	//cout << "currentPos " << position << "end " << endPosition << endl;
	if (position > endPosition) {
		throw out_of_range(
				string("Iterator on cells in position ") + lexical_cast<string>(position)
						+ " after end.");
	}
}

CellIterator& CellIterator::operator ++() {
	increment(1);
	return *this;
}

CellIterator CellIterator::operator ++(int) {
	increment(1);
	return *this;
}

bool CellIterator::operator ==(const CellIterator& other) const {
	//cout << "this p " << this->position << "other p:" << other.position << endl;
	return (this->position == other.position) && (cellType.code == other.cellType.code)
			&& (this->endPosition == other.endPosition);
}

bool CellIterator::operator !=(const CellIterator& rhs) const {
	return !(*this == rhs);
}

const Cell CellIterator::dereference() const {
	return cellStorage->mesh->findCell(cellStorage->mesh->cellPositionsByType.find(cellType)->second[position]);
}

const Cell CellIterator::operator *() const {
	return dereference();
}

bool CellIterator::hasNext() const {
	return (position < endPosition);
}

bool CellIterator::equal(CellIterator const &other) const {
	//too slow! (this->cellIds->isEqual(*other.cellIds)
	return (this->position == other.position) && (cellType.code == other.cellType.code)
			&& (this->endPosition == other.endPosition);
}

/*******************
 * Cell container mixin;
 */

CellContainer::CellContainer(shared_ptr<Mesh> mesh) :
		mesh(mesh) {
}

void CellContainer::addCell(int cellId) {
	cellIds.insert(cellId);
}

void CellContainer::addCellGroup(const string& groupName) {
	Group* group = mesh->findGroup(groupName);
	if (group == nullptr) {
		throw logic_error(string("Group name: ") + groupName + "not found.");
	}
	this->groupNames.insert(groupName);
}

void CellContainer::add(const Cell& cell) {
	addCell(cell.id);
}

void CellContainer::add(const CellGroup& cellGroup) {
	this->groupNames.insert(cellGroup.getName());
}

void CellContainer::add(const CellContainer& cellContainer) {
	if (cellContainer.cellIds.size() > 0) {
		this->cellIds.insert(cellContainer.cellIds.begin(), cellContainer.cellIds.end());
	}

	if (cellContainer.groupNames.size() > 0) {
		this->groupNames.insert(cellContainer.groupNames.begin(), cellContainer.groupNames.end());
	}
}

vector<Cell> CellContainer::getCells(bool all) const {
	vector<Cell> cells;
	cells.reserve(cellIds.size());
	for (int cellId : cellIds) {
		int cellPosition = mesh->findCellPosition(cellId);
		cells.push_back(mesh->findCell(cellPosition));
	}
	if (all) {
		for (string groupName : groupNames) {
			CellGroup* group = static_cast<CellGroup *>(mesh->findGroup(groupName));
			if (group != nullptr) {
				vector<Cell> cellsInGroup = group->getCells();
				cells.insert(cells.end(), cellsInGroup.begin(), cellsInGroup.end());
			}
		}
	}
	return cells;
}

vector<int> CellContainer::getCellIds(bool all) const {
	vector<int> cells(cellIds.begin(), cellIds.end());
	if (all) {
		for (string groupName : groupNames) {
			CellGroup* group = static_cast<CellGroup *>(mesh->findGroup(groupName));
			if (group != nullptr) {
				cells.insert(cells.end(), group->cellIds.begin(), group->cellIds.end());
			}
		}
	}
	return cells;
}

set<int> CellContainer::nodePositions() const {
	set<int> result;
	for (Cell cell : getCells(true)) {
		result.insert(cell.nodePositions.begin(), cell.nodePositions.end());
	}
	return result;
}

bool CellContainer::containsCells(CellType cellType, bool all) {
	vector<Cell> cells = getCells(all);
	bool result = false;
	for (Cell cell : cells) {
		if (cell.type.code == cellType.code) {
			result = true;
			break;
		}
	}
	return result;
}

bool CellContainer::empty() const {
	return groupNames.empty() && cellIds.empty();
}

void CellContainer::clear() {
	groupNames.clear();
	cellIds.clear();
}

bool CellContainer::hasCells() const {
	return !cellIds.empty();
}

vector<CellGroup *> CellContainer::getCellGroups() const {
	vector<CellGroup *> cellGroups;
	cellGroups.reserve(groupNames.size());
	for (string groupName : groupNames) {
		CellGroup* group = static_cast<CellGroup *>(mesh->findGroup(groupName));
		if (group == nullptr) {
			throw invalid_argument("Cannot find group with name:" + groupName);
		}
		cellGroups.push_back(group);
	}
	return cellGroups;
}

bool CellContainer::hasCellGroups() const {
	return groupNames.size() > 0;
}

NodeGroup2Families::NodeGroup2Families(int nnodes, const vector<NodeGroup*> nodeGroups) {
	int currentFamilyId = 0;
	unordered_map<int, int> newFamilyByOldfamily;
	unordered_map<int, Family> familyByFamilyId;
	if (nnodes > 0 && nodeGroups.size() > 0) {
		this->nodes.resize(nnodes, 0);
		for (NodeGroup * nodeGroup : nodeGroups) {
			newFamilyByOldfamily.clear();
			for (int nodePosition : nodeGroup->nodePositions()) {
				int oldFamily = nodes[nodePosition];
				auto newFamilyPair = newFamilyByOldfamily.find(oldFamily);
				int newFamilyId;
				if (newFamilyPair == newFamilyByOldfamily.end()) {
					//family not found, create one
					currentFamilyId++;
					Family fam;
					auto oldFamilyPair = familyByFamilyId.find(oldFamily);
					if (oldFamilyPair != familyByFamilyId.end()) {
						Family& oldFamily = oldFamilyPair->second;
						fam.groups.insert(fam.groups.begin(), oldFamily.groups.begin(),
								oldFamily.groups.end());
						fam.name = oldFamily.name + "_" + nodeGroup->getName();
						if (fam.name.length() >= MED_LNAME_SIZE) {
							fam.name = string("Family") + lexical_cast<string>(currentFamilyId);
						}
					} else {
						fam.name = nodeGroup->getName();
					}
					newFamilyId = fam.num = currentFamilyId;
					fam.groups.push_back(nodeGroup);
					newFamilyByOldfamily.insert(make_pair(oldFamily, currentFamilyId));
					familyByFamilyId.insert(make_pair(currentFamilyId, fam));
				} else {
					newFamilyId = newFamilyPair->second;
				}
				nodes[nodePosition] = newFamilyId;
			}
		}
	}
	set<int> familiesInUse(nodes.begin(), nodes.end());
	for (int fam_id : familiesInUse) {
		if (fam_id != 0) {
			families.push_back(familyByFamilyId[fam_id]);
		}
	}
}

vector<Family>& NodeGroup2Families::getFamilies() {
	return this->families;
}

vector<int>& NodeGroup2Families::getFamilyOnNodes() {
	return this->nodes;
}

CellGroup2Families::CellGroup2Families(
		const Mesh* mesh, unordered_map<CellType::Code, int, hash<int>> cellCountByType,
		const vector<CellGroup *>& cellGroups) : mesh(mesh) {
	int currentFamilyId = 0;
	unordered_map<int, int> newFamilyByOldfamily;
	unordered_map<int, Family> familyByFamilyId;
	for (auto cellCountByTypePair : cellCountByType) {
		shared_ptr<vector<int>> cells(new vector<int>());
		cells->resize(cellCountByTypePair.second, 0);
		cellFamiliesByType[cellCountByTypePair.first] = cells;
	}

	for (CellGroup * cellGroup : cellGroups) {
		newFamilyByOldfamily.clear();
		for (auto cellPosition : cellGroup->cellPositions()) {
			const Cell& cell = mesh->findCell(cellPosition);
			shared_ptr<vector<int>> currentCellFamilies = cellFamiliesByType[cell.type.code];
			int oldFamily = currentCellFamilies->at(cell.cellTypePosition);
			auto newFamilyPair = newFamilyByOldfamily.find(oldFamily);
			int newFamilyId;
			if (newFamilyPair == newFamilyByOldfamily.end()) {
				//family not found, create one
				currentFamilyId--;
				Family fam;
				auto oldFamilyPair = familyByFamilyId.find(oldFamily);
				if (oldFamilyPair != familyByFamilyId.end()) {
					Family& oldFamily = oldFamilyPair->second;
					fam.groups.insert(fam.groups.begin(), oldFamily.groups.begin(),
							oldFamily.groups.end());
					fam.name = oldFamily.name + "_" + cellGroup->getName();
					if (fam.name.length() >= MED_LNAME_SIZE) {
						fam.name = string("CELLFamily") + lexical_cast<string>(-currentFamilyId);
					}
				} else {
					fam.name = cellGroup->getName();
				}
				newFamilyId = fam.num = currentFamilyId;
				fam.groups.push_back(cellGroup);
				newFamilyByOldfamily[oldFamily] = currentFamilyId;
				familyByFamilyId[currentFamilyId] = fam;
			} else {
				newFamilyId = newFamilyPair->second;
			}
			currentCellFamilies->at(cell.cellTypePosition) = newFamilyId;
		}
	}

	set<int> familiesInUse;
	for (auto cellFamilyAndTypePair : cellFamiliesByType) {
		familiesInUse.insert(cellFamilyAndTypePair.second->begin(),
				cellFamilyAndTypePair.second->end());
	}
	for (int fam_id : familiesInUse) {
		if (fam_id != 0) {
			families.push_back(familyByFamilyId[fam_id]);
		}
	}
}

vector<Family>& CellGroup2Families::getFamilies() {
	return this->families;
}

unordered_map<CellType::Code, shared_ptr<vector<int>>, hash<int>>& CellGroup2Families::getFamilyOnCells() {
	return this->cellFamiliesByType;
}
} /* namespace vega */

