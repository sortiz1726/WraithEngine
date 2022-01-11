#ifndef _SpriteStrategyCollection
#define _SpriteStrategyCollection

#include "SpriteNullModifierStrategy.h"
#include "SpriteWorldModifierStrategy.h"

class SpriteStrategyCollection
{
private:
	SpriteStrategyCollection() = delete;
	SpriteStrategyCollection(const SpriteStrategyCollection&) = delete;
	SpriteStrategyCollection& operator=(const SpriteStrategyCollection&) = delete;
	SpriteStrategyCollection(SpriteStrategyCollection&&) = delete;
	SpriteStrategyCollection& operator=(SpriteStrategyCollection&&) = delete;
	~SpriteStrategyCollection() = delete;

public:
	static SpriteNullModifierStrategy nullModifier;
	static SpriteWorldModifierStrategy worldModifier;
};
#endif // !_SpriteStrategyCollection

//-----------------------------------------------------------------------------------------------------------------------------
// SpriteStrategyCollection Comment Template
//-----------------------------------------------------------------------------------------------------------------------------