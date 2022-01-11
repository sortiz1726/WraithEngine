#ifndef _RecycleTankStrategyCollection
#define _RecycleTankStrategyCollection

#include "RecycleTankToFactoryStrategy.h"

class RecycleTankStrategyCollection
{
private:
	RecycleTankStrategyCollection() = delete;
	RecycleTankStrategyCollection(const RecycleTankStrategyCollection&) = delete;
	RecycleTankStrategyCollection& operator=(const RecycleTankStrategyCollection&) = delete;
	RecycleTankStrategyCollection(RecycleTankStrategyCollection&&) = delete;
	RecycleTankStrategyCollection& operator=(RecycleTankStrategyCollection&&) = delete;
	~RecycleTankStrategyCollection() = delete;

public:
	static RecycleTankToFactoryStrategy RecycleToFactory;
};
#endif // !_RecycleTankStrategyCollection

//-----------------------------------------------------------------------------------------------------------------------------
// RecycleTankStrategyCollection Comment Template
//-----------------------------------------------------------------------------------------------------------------------------