#include <memory>
#include "instro/core/Helper.h"
#include "instro/core/ConstructSet.h"
#include "instro/tooling/AnalysisInterface.h"
#include "instro/tooling/NamedConstructAccess.h"
#include "instro/tooling/ControlFlowGraph.h"
#include "instro/example/ExampleNamedConstructAccess.h"
#include "instro/example/ExampleConstructSet.h"

namespace InstRO {
namespace Example {
namespace Tooling {

/*
namespace NamedConstructAccess
{
	class ExampleNamedConstructAccess :public InstRO::Tooling :: NamedConstructAccess::NamedConstructAccess{
		InstRO::Core::ConstructSet getConstructsByIdentifyerName(InstRO::Tooling::NamedConstructAccess::Matcher &){ return
InstRO::Core::ConstructSet(); }
		// b) contents of strings
		InstRO::Core::ConstructSet getConstructsByUserTextStringMatch(InstRO::Tooling::NamedConstructAccess::Matcher &){
return InstRO::Core::ConstructSet(); };
	};
}*/

class ExampleControlFlowGraph : public InstRO::Tooling::ControlFlowGraph::ControlFlowGraph {
protected:

	InstRO::Core::ConstructSet * cs;
public:
	virtual InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode getCFGEntryNode(std::string name, bool useFullQualification) {
		throw std::string("ExampleControlFlowGraph: Not Implemented");
		return InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode(cs, InstRO::Tooling::ControlFlowGraph::CFGNodeType::FUNC_ENTRY);
	};

        virtual InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode getCFGExitNode (std::string name, bool useFullQualification) {
		throw std::string("ExampleControlFlowGraph: Not Implemented");
		return InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode(cs, InstRO::Tooling::ControlFlowGraph::CFGNodeType::FUNC_EXIT);
	};

        
	// helpers for Constru
        virtual InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode getCFGEntryNode(InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode){
		throw std::string("ExampleControlFlowGraph: Not Implemented");
		return InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode(cs, InstRO::Tooling::ControlFlowGraph::CFGNodeType::FUNC_ENTRY);
	};

        virtual InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode getCFGExitNode (InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode){
		throw std::string("ExampleControlFlowGraph: Not Implemented");
		return InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode(cs, InstRO::Tooling::ControlFlowGraph::CFGNodeType::FUNC_EXIT);
	};

   /*     // This function can only be called from the raw interface of the compiler, as the tooling interface only provides construct sets ...
        virtual InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode getCFGEntryNode(InstRO::Core::Construct &) {
		throw std::string("ExampleControlFlowGraph: Not Implemented");
		return InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode(cs, InstRO::Tooling::ControlFlowGraph::CFGNodeType::FUNC_ENTRY);
	};

        virtual InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode getCFGExityNode(InstRO::Core::Construct) {
		throw std::string("ExampleControlFlowGraph: Not Implemented");
		return InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode(cs, InstRO::Tooling::ControlFlowGraph::CFGNodeType::FUNC_EXIT);
	};*/


        // Get a set of entry/exit nodes for the functions represented by the cs-nodes.
        // If a construct in the CS is File or Global-Class no entries are returned for those respecitve constucts
        virtual std::set<InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode> getCFGEntrySet(InstRO::Core::ConstructSet cs){
		throw std::string("ExampleControlFlowGraph: Not Implemented");
		return std::set<InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode>();		
	};

        virtual std::set<InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode> getCFGExitSet(InstRO::Core::ConstructSet cs){
		throw std::string("ExampleControlFlowGraph: Not Implemented");
		return std::set<InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode>();		
	};

        // Find, if possible, the corresponding CFG nodes. Since the CS is a set of nodes, we return a set of nodes ...
	virtual std::set<InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode> getCFGNodeSet(InstRO::Core::ConstructSet cs){
		throw std::string("ExampleControlFlowGraph: Not Implemented");
		return std::set<InstRO::Tooling::ControlFlowGraph::ControlFlowGraphNode>();		
	};
};

/* CI: The ConstructSet class is intended to be specialized for each compiler interface. It provides the basic
 * mechanisms to specify what construct level are contained. */
class ExampleConstructElevator : public InstRO::Tooling::ConstructElevator::ConstructElevator {
	public:
		// This is the implicit way, that the PassManager will allways apply
		virtual InstRO::Core::ConstructSet raise(const InstRO::Core::ConstructSet &input, InstRO::Core::ConstructTraitType cl) override {
			InstRO::InfracstructureInterface::ReadOnlyConstructSetCompilerInterface inputCSCI(&input);
			auto outputCS=std::make_unique<InstRO::Core::ConstructSet>();
			InstRO::InfracstructureInterface::ConstructSetCompilerInterface outputCSCI(outputCS.get());
			//		for (auto construct : inputCSCI)	{
			//			auto traits=construct->getTraits();
			//			if (!traits.is(cl))	{


			//			}

			//		}
			//	throw std::string("ExampleConstructElevator::raise : Not Implemented");
			return *outputCS;
		}
		// This is an explicit function used in very rare circumstances by e.g. a specialized selection pass (if at all)
		virtual InstRO::Core::ConstructSet lower(const InstRO::Core::ConstructSet &input,
				InstRO::Core::ConstructTraitType cl) {
			throw std::string("ExampleConstructElevator::lower : Not Implemented");
			return input;
		}
};

class ExampleGrammarInterface : public InstRO::Tooling::GrammarInterface::GrammarInterface {
	public:
		// class ConstructSetToGrammarTypeMapper
		virtual std::list<InstRO::Tooling::GrammarInterface::GrammarTypesType> getGrammerTypes(
				const InstRO::Core::ConstructSet &cs) {
		throw std::string("ExampleGrammarInterface::getGrammerTypes : Not Implemented");
		return std::list<InstRO::Tooling::GrammarInterface::GrammarTypesType>();
	}

	// class RequestCSByGrammarTypeInterface
	virtual std::unique_ptr<InstRO::Core::ConstructSet> getConstructsByType(
			const InstRO::Tooling::GrammarInterface::GrammarTypesType &types) override {
		throw std::string("ExampleGrammarInterface::getConstructsByType : Not Implemented");
		return std::make_unique<InstRO::Core::ConstructSet>(InstRO::Core::ConstructSet());
	};
};

class ExampleExtendedCallGraph : public InstRO::Tooling::ExtendedCallGraph::ExtendedCallGraph {
 public:
	std::set<InstRO::Tooling::ExtendedCallGraph::ExtendedCallGraphNode *> getECGNodes(
			InstRO::Core::ConstructSet *cs) override {
		return std::set<InstRO::Tooling::ExtendedCallGraph::ExtendedCallGraphNode *>();
	};
	// std::vector<ExtendedCallGraphNode*> findNodes(GrammarInterface::GrammerTypes type);
};

class ExampleAnalysisManager : public InstRO::Tooling::AnalysisManager {
 protected:
	ExampleExtendedCallGraph *ecg;
	ExampleConstructElevator *ce;
	ExampleControlFlowGraph *cfg;
	NamedConstructAccess::ExampleNamedConstructAccess *nca;

 public:
	ExampleAnalysisManager() : ecg(NULL), ce(NULL), cfg(NULL), nca(NULL){};

	ExampleExtendedCallGraph *getECG() {
		if (ecg == NULL)
			ecg = new ExampleExtendedCallGraph();
		return ecg;
	};
	ExampleControlFlowGraph *getCFG() { return new ExampleControlFlowGraph(); };
	ExampleConstructElevator *getCSElevator() { return new ExampleConstructElevator(); }
	ExampleGrammarInterface *getGrammarInterface() { return new ExampleGrammarInterface(); }
	InstRO::Tooling::NamedConstructAccess::NamedConstructAccess *getNamedConstructAccessFacility() {
		if (nca == NULL)
			nca = new NamedConstructAccess::ExampleNamedConstructAccess();
		return nca;
	};
};
}
}
}
