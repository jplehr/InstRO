#ifndef INSTRO_CORE_PASSFACTORY_H
#define INSTRO_CORE_PASSFACTORY_H
/*
 * This is our user-level interface. A typical use case in our minds is
 * int main(...){
 *   InstRO myinstro = ROSE::getInstRO();
 *   ROSE::InstROFactory fac = myinstro.getFactory();
 *   Pass *sel = fac.getSelectionPass(myinstro.getPassManager());
 *   Pass *adapter = fac.getAdapterPass(myinstro.getPassManager(), sel);
 *   myinstro.run();
 * }
 */

#include <list>
#include <map>
#include <string>
#include <iostream>
#include <vector>

#include <vector>
#include <string>

#include "instro/core/Pass.h"

namespace InstRO{
namespace Core{
	namespace PassManagement
	{
		class PassManager;
	}
	class Pass;
	/* PassFactory: Interface for the mandatory InstRO Passes. */
	class PassFactory
	{
		public:	
			/* CI: A PassFactory must be initialized with the PassManager. */
			PassFactory(PassManagement::PassManager * refManager):refToGobalPassManager(refManager){};
			virtual ::InstRO::Pass * createBlackAndWhiteListSelector(std::vector<std::string> rules)=0;
			virtual ::InstRO::Pass * createBooleanOrSelector(::InstRO::Pass * inputA,::InstRO::Pass * inputB)=0;
			virtual ::InstRO::Pass * createProgramEntrySelector()=0;
			virtual ::InstRO::Pass * createCygProfileAdapter(::InstRO::Pass * input)=0;
		protected:
			PassManagement::PassManager * refToGobalPassManager;
	};
}// Core
}//InstRO

#endif
