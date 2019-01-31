
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

int main(int argc, char **argv) {
  /*
   * We want to use the same binary for both Rose and Clang
   */
  try {
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

    auto idSelector = factory->createIdentifierMatcherSelector({"::foo"});
    auto idSelector2 = factory->createIdentifierMatcherSelector({"::f#"});
    auto idSelector3 = factory->createIdentifierMatcherSelector({"#foo"});
    auto idSelector4 = factory->createIdentifierMatcherSelector({"#f#"});

    factory->createTestAdapter(idSelector, "IdSelector-::foo", filename);
    factory->createTestAdapter(idSelector2, "IdSelector-::f#", filename);
    factory->createTestAdapter(idSelector3, "IdSelector-#foo", filename);
    factory->createTestAdapter(idSelector4, "IdSelector-#f#", filename);

#ifdef DEBUG
    factory->createConstructPrinterAdapter(idSelector);
#endif

    instrumentor.apply();

    return instrumentor.testFailed();
  } catch (std::string s) {
    std::cout << s << std::endl;
    return -1;
  }
}
