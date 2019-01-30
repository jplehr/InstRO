
#include "instro.h"
#include <iostream>

#ifdef INSTRO_USE_ROSE
#include "lib/RoseTestSupport.h"
#elif INSTRO_USE_CLANG
#include "lib/ClangTestSupport.h"
static llvm::cl::OptionCategory instroTool("InstRO Clang Test");
#endif

#include "instro/utility/Environment.h"
#include "instro/utility/Logger.h"

int main(int argc, char** argv) {
/*
 * We want to use the same binary for both Rose and Clang
 */
  using CTrait = InstRO::Core::ConstructTraitType;
#ifdef INSTRO_USE_ROSE
  using InstrumentorType = RoseTest::RoseTestInstrumentor;
  InstrumentorType instrumentor(argc, argv);
#elif INSTRO_USE_CLANG
  using InstrumentorType = ClangTest::ClangTestInstrumentor;
  InstrumentorType instrumentor(argc, argv, instroTool);
#endif
	auto factory = instrumentor.getFactory();

	std::string filename = InstRO::Utility::getEnvironmentVariable("INSTRO_TEST_INPUT_FILENAME");

	auto funcLvlSelector = factory->createConstructTraitSelector(CTrait::CTFunction);
	auto funcToStmtLvlSelector = factory->createConstructLoweringElevator(funcLvlSelector, CTrait::CTStatement);
	factory->createTestAdapter(funcToStmtLvlSelector, "Func2StmtLevelSelector", filename);

	auto stmtLvlSelector = factory->createConstructTraitSelector(CTrait::CTStatement);
	auto stmtToFuncLvlSelector = factory->createConstructRaisingElevator(stmtLvlSelector, CTrait::CTFunction);
	factory->createTestAdapter(stmtToFuncLvlSelector, "Stmt2FuncLevelSelector", filename);

	auto funcToExprLvlSelector = factory->createConstructLoweringElevator(funcLvlSelector, CTrait::CTExpression);
	factory->createTestAdapter(funcToExprLvlSelector, "Func2ExprLevelSelector", filename);

	auto stmtClassSelector = factory->createConstructTraitSelector(CTrait::CTStatement);
	auto exprClassSelector = factory->createConstructTraitSelector(CTrait::CTExpression);
	auto booleanOrSelector = factory->createBooleanOrSelector(stmtClassSelector, exprClassSelector);

	auto wpToExprStmtSelector =
			factory->createConstructCroppingElevator(booleanOrSelector, CTrait::CTExpression, CTrait::CTStatement);
	auto wpToStmtFuncSelector =
			factory->createConstructCroppingElevator(booleanOrSelector, CTrait::CTStatement, CTrait::CTFunction);

	factory->createTestAdapter(wpToExprStmtSelector, "wpToExprStmtSelector", filename);
	factory->createTestAdapter(wpToStmtFuncSelector, "wpToStmtFuncSelector", filename);

#ifdef CDEBUG
	factory->createConstructPrinterAdapter(funcToExprLvlSelector);
#endif

	instrumentor.apply();

	return instrumentor.testFailed();

}
