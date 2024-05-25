#include <iostream>
#include "DirectCode.h"
#include "ReverseCode.h"
#include "SupplementaryCode.h"
#include "Floats.h"

int main() {
	std::cout << "----------Direct code representation--------------" << std::endl;
	DirectCode d1(120);
	DirectCode d2(13);
	std::cout << d1.Number() << ": " << d1.String() << std::endl;
	std::cout << d2.Number() << ": " << d2.String() << std::endl;

	std::cout << "----------Reverse code representation--------------" << std::endl;
	ReverseCode r1(120);
	ReverseCode r2(13);
	std::cout << r1.Number() << ": " << r1.String() << std::endl;
	std::cout << r2.Number() << ": " << r2.String() << std::endl;

	std::cout << "----------Suplementary code representation--------------" << std::endl;
	SupplementaryCode sc1(12);
	SupplementaryCode sc2(9);
	std::cout << sc1.Number() << ": " << sc1.String() << std::endl;
	std::cout << sc2.Number() << ": " << sc2.String() << std::endl;

	std::cout << "----------Suplementary code add and minus--------------" << std::endl;
	std::cout << (sc1 + sc2).Number() << ": " << (sc1 + sc2).String() << std::endl;
	std::cout << (sc1 - sc2).Number() << ": " << (sc1 - sc2).String() << std::endl;

	std::cout << "----------Direct code division--------------" << std::endl;
	std::cout << (d1 / d2).String() << ": " << (d1 / d2).Number() << std::endl;

	std::cout << "----------Direct code multiplication--------------" << std::endl;
	std::cout << (d1 * d2).String() << ": " << (d1 * d2).Number() << std::endl;

	std::cout << "----------Floating point represenattion--------------" << std::endl;
	Floats fl(0.4f);
	std::cout << fl.Number() << ": " << fl.String() << std::endl;
	Floats fl1(34000.f);
	std::cout << fl1.Number() << ": " << fl1.String() << std::endl;

	std::cout << "----------Floating point add--------------" << std::endl;
	std::cout << (fl + fl).String() << ": " << (fl + fl).Number() << std::endl;
	std::cout << (fl + fl1).String() << ": " << (fl + fl1).Number() << std::endl;
}