#include "instro/tooling/ControlFlowGraph.h"
#include "instro/Instrumentor.h"

#include "instro/core/Singleton.h"

using namespace boost;

namespace InstRO {
namespace Tooling {
namespace ControlFlowGraph {

std::set<ControlFlowGraphNode> AbstractControlFlowGraph::getCFGExitSet(InstRO::Core::ConstructSet cs) {
	auto elevator = getInstrumentorInstance()->getAnalysisManager()->getCSElevator();
	InstRO::Core::ConstructSet functions = elevator->raise(cs, InstRO::Core::ConstructTraitType::CTFunction);

	std::set<ControlFlowGraphNode> returnSet;
	for (auto& cfg : cfgs) {
		if (cfg.getStartNode().getAssociatedConstructSet()->intersects(functions)) {
			returnSet.insert(cfg.getStartNode());
		}
	}
	return returnSet;
}

std::set<ControlFlowGraphNode> AbstractControlFlowGraph::getCFGEntrySet(InstRO::Core::ConstructSet cs) {
	auto elevator = getInstrumentorInstance()->getAnalysisManager()->getCSElevator();
	InstRO::Core::ConstructSet functions = elevator->raise(cs, InstRO::Core::ConstructTraitType::CTFunction);

	std::set<ControlFlowGraphNode> returnSet;
	for (auto& cfg : cfgs) {
		if (cfg.getEndNode().getAssociatedConstructSet()->intersects(functions)) {
			returnSet.insert(cfg.getEndNode());
		}
	}
	return returnSet;
}

ControlFlowGraphNode AbstractControlFlowGraph::getCFGEntryNode(ControlFlowGraphNode cfgNode) {
	for (auto cfg : cfgs) {
		if (cfg.contains(cfgNode)) {
			return cfg.getStartNode();
		}
	}
	throw std::string("ControlFlowGraph Error: found no corresponding CFG");
}

ControlFlowGraphNode AbstractControlFlowGraph::getCFGExitNode(ControlFlowGraphNode cfgNode) {
	for (auto cfg : cfgs) {
		if (cfg.contains(cfgNode)) {
			return cfg.getEndNode();
		}
	}
	throw std::string("ControlFlowGraph Error: found no corresponding CFG");
}

std::set<ControlFlowGraphNode> AbstractControlFlowGraph::getCFGNodeSet(InstRO::Core::ConstructSet cs) {
	std::set<ControlFlowGraphNode> returnSet;

	for (auto const& boostCFG : cfgs) {
		Graph::vertex_iterator vertexIter, vertexEnd;
		for (boost::tie(vertexIter, vertexEnd) = vertices(boostCFG.getGraph()); vertexIter != vertexEnd; vertexIter++) {
			ControlFlowGraphNode node = boostCFG.getGraph().graph()[*vertexIter];

			if (node.getAssociatedConstructSet()->intersects(cs)) {
				returnSet.insert(node);
			}
		}
	}
	return returnSet;
}

}	// ControlFlowGraph
}	// Tooling
}	// InstRO
