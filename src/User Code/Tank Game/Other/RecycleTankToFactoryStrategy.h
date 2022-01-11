#ifndef _RecycleTankToFactoryStrategy
#define _RecycleTankToFactoryStrategy

#include "RecycleTankStrategy.h"

class RecycleTankToFactoryStrategy : public RecycleTankStrategy
{
public:
	RecycleTankToFactoryStrategy() = default;
	RecycleTankToFactoryStrategy(const RecycleTankToFactoryStrategy&) = default;
	RecycleTankToFactoryStrategy& operator=(const RecycleTankToFactoryStrategy&) = default;
	RecycleTankToFactoryStrategy(RecycleTankToFactoryStrategy&&) = default;
	RecycleTankToFactoryStrategy& operator=(RecycleTankToFactoryStrategy&&) = default;
	~RecycleTankToFactoryStrategy() = default;

	// Inherited via RecycleTankStrategy
	virtual void recycle(Tank*) override;
};

#endif // !_RecycleTankToFactoryStrategy

//-----------------------------------------------------------------------------------------------------------------------------
// RecycleTankToFactoryStrategy Comment Template
//-----------------------------------------------------------------------------------------------------------------------------