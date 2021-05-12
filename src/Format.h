#pragma once

#include "PrecompiledHeaders.h"





//Method on String
std::vector<std::string> getlines(const std::string& fileName);
void savelines(const std::string& fileName, const std::vector<std::string>& lines);
std::string stride(const std::string& origin, const std::string& x);
std::string remove(const std::string& origin, const std::string& x);
std::vector<std::string> split(const std::string& origin, const std::string& x);
bool isCommentLine(const std::string& origin);
//da aggiungere
//std::string removeFrontSpace(const std::string& origin);
bool findInString(const std::string& origin, const std::string& x);
//Method on String