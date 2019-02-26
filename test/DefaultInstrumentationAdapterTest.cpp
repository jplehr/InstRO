
#include "instro.h"

#if INSTRO_USE_ROSE
#include "lib/RoseTestSupport.h"
#elif INSTRO_USE_CLANG
#include "lib/ClangTestSupport.h"
static llvm::cl::OptionCategory instroTool("InstRO Clang Test");
#endif

int main(int argc, char **argv) {
  using CTrait = InstRO::Core::ConstructTraitType;
#if INSTRO_USE_ROSE
  using InstrumentorType = RoseTest::RoseTestInstrumentor;
  InstrumentorType instrumentor(argc, argv);
#elif INSTRO_USE_CLANG
  using InstrumentorType = ClangTest::ClangTestInstrumentor;
  InstrumentorType instrumentor(argc, argv, instroTool);
#endif

  auto factory = instrumentor.getFactory();

  auto fDefSelector = factory->createConstructTraitSelector(InstRO::Core::ConstructTraitType::CTFunction);
  auto stmtSelector = factory->createConstructTraitSelector(InstRO::Core::ConstructTraitType::CTStatement);

  auto combinedSelector = factory->createBooleanOrSelector(fDefSelector, stmtSelector);

  auto defaultAdapter = factory->createDefaultInstrumentationAdapter(combinedSelector);

  instrumentor.apply();

  return 0;
}
