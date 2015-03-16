#include "instro/clang/core/PassFactory.h"

InstRO::Pass* InstRO::Clang::PassFactory::createBlackAndWhiteListSelector(
		std::vector<std::string> blacklist, std::vector<std::string> whitelist) {
	InstRO::Clang::Core::ClangPassImplementation *pImpl = new InstRO::Clang::BlackWhitelistSelector(blacklist, whitelist);
	pImpl->setPassExecuter(executer);
	InstRO::Pass *p = new InstRO::Pass(pImpl);
	p->setRequiresInput(false);
	p->setProvidesOutput(true);
	p->setPassName("BlackWhitelist Selector");
	p->setOutputLevel(InstRO::Core::ConstructLevelType::ConstructLevelStatement);
	passManager->registerPass(p);
	return p;
}

InstRO::Pass* InstRO::Clang::PassFactory::createBooleanOrSelector(
		InstRO::Pass* inputA, InstRO::Pass* inputB) {
	return NULL;
}

InstRO::Pass* InstRO::Clang::PassFactory::createFunctionDefinitionSelector() {
	InstRO::Clang::Core::ClangPassImplementation *pImpl = new InstRO::Clang::FunctionDefinitionSelector();
	pImpl->setPassExecuter(executer);
	InstRO::Pass *p = new InstRO::Pass(pImpl);
	p->setRequiresInput(false);
	p->setProvidesOutput(true);
	p->setPassName(std::string("Function Definition Selector"));
	p->setOutputLevel(InstRO::Core::ConstructLevelType::ConstructLevelStatement);
	passManager->registerPass(p);
	return p;
}

InstRO::Pass* InstRO::Clang::PassFactory::createCygProfileAdapter(
		InstRO::Pass* input) {
	InstRO::Clang::Core::ClangPassImplementation *pImpl = new InstRO::Clang::CygProfileAdapter(input, replacements, NULL);
	pImpl->setPassExecuter(executer);
	InstRO::Pass *p = new InstRO::Pass(pImpl);
	p->setRequiresInput(true);
	p->setProvidesOutput(false);
	p->setPassName(std::string("CygProfile Adapter"));
	p->registerInputPass(input, InstRO::Core::ConstructLevelType::ConstructLevelStatement);
	passManager->registerPass(p);
	return p;
}

