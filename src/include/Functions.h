#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "ArgParser.h"
#include "Globals.h"
#include <filesystem>
bool PathExists(std::filesystem::path path, Parameters &params, int error_code);
void StringAppendIf(bool test, std::string &variable, std::string if_, std::string else_);
bool CreateDirectory(std::filesystem::path path, Parameters &params, int error_code);
bool CreateFile(std::filesystem::path path, std::string content, Parameters &params, int error_code);
int process_directories(std::map<std::string, std::filesystem::path> &dir_paths, Parameters &params);
int process_files
(
  std::map<std::string, std::filesystem::path> & file_paths,
  Parameters &params, Globals &globals, Switches & switches
);
#endif // FUNCTIONS_H
