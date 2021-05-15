#pragma once

#include "PrecompiledHeaders.h"





//Method on String
std::vector<std::string> getlines(const std::string& fileName);
void savelines(const std::string& fileName, const std::vector<std::string>& lines);
std::string stride(const std::string& origin, const std::string& x);
std::string stride(const std::string& origin, int start, int end);
std::string remove(const std::string& origin, const std::string& x);
std::vector<std::string> split(const std::string& origin, const std::string& x);
bool isCommentLine(const std::string& origin);
//da aggiungere
std::string removeFrontSpace(const std::string& origin);
std::string removeQuotationMarks(const std::string& origin);
bool isInString(const std::string& origin, const std::string& x);
int findInString(const std::string& origin, const std::string& x);
//Method on String