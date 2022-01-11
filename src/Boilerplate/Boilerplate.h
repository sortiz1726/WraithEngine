#ifndef _Boilerplate
#define _Boilerplate

class Boilerplate
{
public:
	Boilerplate();
	Boilerplate(const Boilerplate&);
	Boilerplate& operator=(const Boilerplate&);
	Boilerplate(Boilerplate&&);
	Boilerplate& operator=(Boilerplate&&);
	// Is it a base class? Should it be virtual?
	~Boilerplate();
};
#endif // !_Boilerplate

//-----------------------------------------------------------------------------------------------------------------------------
// Boilerplate Comment Template
//-----------------------------------------------------------------------------------------------------------------------------