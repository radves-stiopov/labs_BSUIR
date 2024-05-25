#include <iostream>
#include "..\\l2\Table.h"

int main() {
	Table t("(a>b)|!c");
	std::string result = t.SDNF();
	std::string result2 = t.SKNF();
	t.print();
	std::cout << result << std::endl;
	std::cout << result2 << std::endl;
	std::string dfc = t.DecimalFormConjunction();
	std::string dfd = t.DecimalFormDisjunction();
	std::cout << dfd << std::endl;
	std::cout << dfc << std::endl;
	std::string indexForm = t.IndexForm();
	std::cout << indexForm << std::endl;




}