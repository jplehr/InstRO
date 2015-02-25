#ifndef INSTRO_CORE_CONSTRUCTSETMANAGEMENT_H
#define INSTRO_CORE_CONSTRUCTSETMANAGEMENT_H
#include "instro/core/ConstructSet.h"
#include <hash_map>
namespace InstRO
{
namespace Core
{
class PassConstructSetManagement
	{
	public:
		PassConstructSetManagement(){output=NULL;};		
		void setOutput(ConstructSet * output);
		ConstructSet* getOutput();
		ConstructSet* getInput(PassConstructSetManagement * from);
		void overrideInput(PassConstructSetManagement * from, ConstructSet* overrideSet);

	private:
		std::hash_map<PassConstructSetManagement*,ConstructSet*> inputOverride;
		ConstructSet * output;

	public:
		
	
	//protected:
		// Internal Interface used by the derived passes	
//		ConstructSet* registerInput(int maxConstructLevel,std::string name);
		//ConstructSet* registerInput(int maxConstructLevel);
//		ConstructSetContainer * getInputConstructSets();
//		ConstructSet* registerOutput(int minConstructLevel);
//	private:
//		std::vector<ConstructSet*> inputSets;
//		std::vector<ConstructSet*> outputSets;
	};

}
}
#endif