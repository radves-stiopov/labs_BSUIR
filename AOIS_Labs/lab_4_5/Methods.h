#pragma once
#include <string>
#include "Table.h"

std::string MinimizeSKNFChisl(std::string input);

std::string MinimizeSDNFChisl(std::string input);

std::string MinimizeSKNFTable(std::string input);

std::string MinimizeSDNFTable(std::string input);

std::string MinimizeSKNFKarno(std::string input);

std::string MinimizeSDNFKarno(std::string input);

void PrintMinus();

void Print2();

void Triggers();