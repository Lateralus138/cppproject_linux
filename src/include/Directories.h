#pragma once
#ifndef DIRECTORIES_H
#define DIRECTORIES_H
#include <filesystem>
#include <map>
#include <string>
class Directories
{
public:
  void set(std::map<std::string, std::string> map);
  std::map<std::string, std::filesystem::path> getPaths();
  std::filesystem::path getPath(std::string key);
  void setNewPath(std::string key, std::string value);
  void append(std::string key, std::string append_value);

protected:
private:
  std::map<std::string, std::filesystem::path> paths;
};
extern Directories directories;
#endif // DIRECTORIES_H
