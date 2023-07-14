#include "Directories.h"
void Directories::set(std::map<std::string, std::string> map)
{
  for (std::pair const &[key, value] : map)
  {
    paths.insert({key, std::filesystem::path(value)});
  }
}
void Directories::setNewPath(std::string key, std::string value)
{
  paths.insert({key, std::filesystem::path(value)});
}
std::filesystem::path Directories::getPath(std::string key)
{
  return paths[key];
}
std::map<std::string, std::filesystem::path> Directories::getPaths()
{
  return paths;
}
void Directories::append(std::string key, std::string append_value)
{
  paths[key] /= append_value;
}
Directories directories;
