
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

/**
 * Implicitly tests the Extended Call Graph as this is used as basis within the Callpath-Selector
 */
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

  // From main to all functions
  auto programEntrySelector = factory->createProgramEntrySelector();
  auto functionSelector = factory->createConstructTraitSelector(CTrait::CTFunction);
  auto cpSelector = factory->createCallpathSelector(programEntrySelector, functionSelector);

  factory->createTestAdapter(programEntrySelector, "EntrySelector", filename);
  factory->createTestAdapter(cpSelector, "CallpathSelector", filename);

  // from main to nothing
  auto identifierSelector = factory->createIdentifierMatcherSelector({"foo"});  // should match nothing
  auto cpSelector2 = factory->createCallpathSelector(programEntrySelector, identifierSelector);
  factory->createTestAdapter(cpSelector2, "EmptyCallpathSelector", filename);

  // from main to anything called ::bar
  auto idSelector2 = factory->createIdentifierMatcherSelector({"::bar"});
  auto cpSelector3 = factory->createCallpathSelector(programEntrySelector, idSelector2);
  factory->createTestAdapter(cpSelector3, "PathToBarSelector", filename);

#ifdef INSTRO_USE_CLANG
  std::cerr << "Not yet functional" << std::endl;
  return -1;
#else
  instrumentor.apply();
  return instrumentor.testFailed();
#endif
}
