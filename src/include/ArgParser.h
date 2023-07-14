#pragma once
#ifndef ARGPARSER_H
#define ARGPARSER_H
#include <regex>
#include <vector>
struct Parameters
{
  int error_value;
  std::string main_name;
  std::string path_name;
  std::vector<std::string> class_names;
  Parameters(int &error_value, std::string &main_name, std::string &path_name, std::vector<std::string> &class_names) :
    error_value(error_value),
    main_name(main_name),
    path_name(path_name),
    class_names(class_names) {}
  Parameters()
  {
    error_value = 0;
    main_name = "main";
    path_name = "./";
  }
  bool operator==(const Parameters& other) const
  {
    return  error_value == other.error_value &&
            main_name == other.main_name &&
            class_names == other.class_names &&
            path_name == other.path_name;
  }
};
struct Switches
{
  bool is_help;
  bool prebuild_script;
  Switches(const bool &prebuild_script) :
    is_help(is_help),
    prebuild_script(prebuild_script) {}
  Switches()
  {
    is_help = false;
    prebuild_script = false;
  }
  bool operator==(const Switches& other) const
  {
    return  is_help == other.is_help &&
            prebuild_script == other.prebuild_script;
  }
};
struct Regex
{
  std::regex help;
  std::regex main;
  std::regex prebuild;
  std::regex class_;
  std::regex directory;
  Regex(const std::regex& help, const std::regex& main, const std::regex &prebuil, const std::regex &class_, std::regex &directory) :
    help(help),
    main(main),
    prebuild(prebuild),
    class_(class_),
    directory(directory) {}
  Regex()
  {
    help =
      std::regex("^-([hH]|-[hH][eE][lL][pP])$");
    main =
      std::regex("^-([mM]|-[mM][aA][iI][nN])$");
    prebuild =
      std::regex("^-([pP]|-[pP][rR][eE][bB][uU][iI][lL][dD])$");
    class_ =
      std::regex("^-([cC]|-[cC][lL][aA][sS][sS])$");
    directory =
      std::regex("^-([dD]|-[dD][iI][rR][eE][cC][tT][oO][rR][yY])$");
  }
  bool IsOption(std::string &option);
};
bool ArgParser(int argc, const char* argv[], Parameters& params, Switches &switches);
bool NextArgTest(int index, const std::vector<std::string>& args);
#endif // !ARGPARSER_H
