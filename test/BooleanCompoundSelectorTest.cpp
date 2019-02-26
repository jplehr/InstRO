
#include "instro.h"
#include <iostream>

#if INSTRO_USE_ROSE
#include "lib/RoseTestSupport.h"
#elif INSTRO_USE_CLANG
#include "lib/ClangTestSupport.h"
static llvm::cl::OptionCategory instroTool("InstRO Clang Test");
#endif

#include "instro/utility/Environment.h"
#include "instro/utility/Logger.h"

int main(int argc, char **argv) {
  /*
   * We want to use the same binary for both Rose and Clang
   */

  using CTrait = InstRO::Core::ConstructTraitType;
#if INSTRO_USE_ROSE
  using InstrumentorType = RoseTest::RoseTestInstrumentor;
  InstrumentorType instrumentor(argc, argv);
#elif INSTRO_USE_CLANG
  using InstrumentorType = ClangTest::ClangTestInstrumentor;
  InstrumentorType instrumentor(argc, argv, instroTool);
  instrumentor.setNonModifying();
#endif

  auto factory = instrumentor.getFactory();

  std::string filename = InstRO::Utility::getEnvironmentVariable("INSTRO_TEST_INPUT_FILENAME");

  auto selA = factory->createConstructTraitSelector(CTrait::CTFunction);
  auto selB = factory->createConstructTraitSelector(CTrait::CTStatement);

  auto andSelector = factory->createBooleanAndSelector(selA, selB);
  auto orSelector = factory->createBooleanOrSelector(selA, selB);

  factory->createTestAdapter(andSelector, "FunctionAndStatementSelector", filename);
  factory->createTestAdapter(orSelector, "FunctionOrStatementSelector", filename);

  instrumentor.apply();

  return instrumentor.testFailed();
}
