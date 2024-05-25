#include "FirstStep.h"

#include <algorithm>
#include <iostream>

FirstStep::FirstStep(VariableForm form, bool isSKNF) : formResult(false) {
	std::cout << "First step\n" << std::endl;
	std::cout << form.ToString() << std::endl;
	while (form.GetGlued()){}
	//std::cout << form.ToString() << "\n" << std::endl;
	std::cout << "final after glued" << std::endl;
	std::cout << form.ToString() << std::endl;
	formResult = form;
}
