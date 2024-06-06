#include "FirstStep.h"

#include <algorithm>
#include <iostream>

FirstStep::FirstStep(VariableForm form, bool isSKNF) : formResult(false) {
	while (form.GetGlued()) {
	}
	formResult = form;
}
