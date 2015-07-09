#include "instro/core/PassImplementation.h"

namespace InstRO {
namespace Selector {

class IdentifyerSelector : public InstRO::Core::PassImplementation {
 protected:
	Pass *filterChannel;
	std::vector<std::string> rules;
	IdentifyerSelector() = delete;
	std::unique_ptr<Core::ConstructSet> output;

 public:
	IdentifyerSelector(std::vector<std::string> matchRules, Pass *filter)
			: PassImplementation(Core::ChannelConfiguration(filter)), filterChannel(filter), rules(matchRules){};
	IdentifyerSelector(std::vector<std::string> matchRules)
			: PassImplementation(Core::ChannelConfiguration()), filterChannel(NULL), rules(matchRules){};
	virtual void init() override;
	virtual void execute() override;
	virtual void finalize() override;
	virtual void releaseOutput() override;
	virtual Core::ConstructSet *getOutput() override;

 protected:
};
}
}