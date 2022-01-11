#ifndef _RecycleTankStrategy
#define _RecycleTankStrategy

class Tank;

class RecycleTankStrategy
{
public:
	RecycleTankStrategy() = default;
	RecycleTankStrategy(const RecycleTankStrategy&) = default;
	RecycleTankStrategy& operator=(const RecycleTankStrategy&) = default;
	RecycleTankStrategy(RecycleTankStrategy&&) = default;
	RecycleTankStrategy& operator=(RecycleTankStrategy&&) = default;
	virtual ~RecycleTankStrategy() = default;

	virtual void recycle(Tank*) = 0;
};
#endif // !_RecycleTankStrategy

//-----------------------------------------------------------------------------------------------------------------------------
// RecycleTankStrategy Comment Template
//-----------------------------------------------------------------------------------------------------------------------------