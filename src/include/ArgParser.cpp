#include "ArgParser.h"
#include <vector>
#include <iostream>
bool Regex::IsOption(std::string &option)
{
  return  std::regex_match(option, help) ||
          std::regex_match(option, main) ||
          std::regex_match(option, prebuild) ||
          std::regex_match(option, class_) ||
          std::regex_match(option, directory);
}
bool NextArgTest(int index, const std::vector<std::string>& args)
{
  try
  {
    if ((index + 1) > ((int)args.size() - 1))
    {
      std::string rtmsg = "No argument provided for [";
      rtmsg.append(args[index]);
      rtmsg.append("].\n");
      throw std::runtime_error(rtmsg);
    }
  }
  catch (std::runtime_error& rerr)
  {
    std::cerr << rerr.what();
    return false;
  }
  return true;
}
bool ArgParser(int argc, const char* argv[], Parameters& params, Switches &switches)
{
  Regex regex;
  const std::vector<std::string> args(argv + 1, argv + argc);
  argc--;
  bool skip = false;
  for (int index = 0; index < argc; index++)
  {
    if (skip)
    {
      skip = false;
      continue;
    }
    if (std::regex_match(args[index], regex.help))
    {
      const std::string HELPMESSAGE =
        "\n"
        "CPP Project - Create a custom Linux C++ tree and\n"
        "              files project from the command line.\n"
        "              Customn project style developed by\n"
        "              Ian Pride using a normal (but custom\n"
        "              ) Makefile system (no CMAKE) with a\n"
        "              possible prebuild file to help build\n"
        "              the precompiled header, objects, and\n"
        "              library archive.\n"
        "\n"
        "USAGE:\n"
        "  cppproj [-h | --help] |\n"
        "          [-d | --directory] <DIRECTORY PATH>\n"
        "          [-m | --main] <MAIN FILE NAME>\n"
        "          [-c | --class] <CLASS FILE NAME>\n"
        "          [-p | --prebuild]\n"
        "\n"
        "PARAMETERS:\n"
        "  DIRECTORY PATH:   Parent path to the project.\n"
        "  MAIN FILE NAME:   Name of the main source file\n"
        "                    without the extension.\n"
        "  CLASS FILE NAME:  Create class files by name.\n"
        "                    Each different file name must\n"
        "                    be preceeded by the switch:\n"
        "                    e.g: -c ClassOne -c ClassTwo.\n"
        "\n"
        "Switches:\n"
        "  -h, --help      This help screen.\n"
        "  -d, --directory Project path location.\n"
        "  -m, --main      Main source file name.\n"
        "  -c, --class     Class file name.\n"
        "  -p, --prebuild  Create a prebuild file to build\n"
        "                  precompiled header, object files\n"
        "                  , and library archive file.\n"
        "\n";
      std::cout << HELPMESSAGE;
      switches.is_help = true;
      return true;
    }
    if (std::regex_match(args[index], regex.main))
    {
      bool HASARG = NextArgTest(index, args);
      if (!HASARG)
      {
        params.error_value = 1;
        return false;
      }
      int next_index = index + 1;
      std::string next_arg = args[next_index];
      if (regex.IsOption(next_arg))
      {
        std::string message = "Invalid option for [";
        message.append(args[index]);
        message.append("]\n");
        std::cerr << message;
        params.error_value = 2;
        return false;
      }
      params.main_name = next_arg;
      skip = true;
      continue;
    }
    if (std::regex_match(args[index], regex.class_))
    {
      bool HASARG = NextArgTest(index, args);
      if (!HASARG)
      {
        params.error_value = 3;
        return false;
      }
      int next_index = index + 1;
      std::string next_arg = args[next_index];
      if (regex.IsOption(next_arg))
      {
        std::string message = "Invalid option for [";
        message.append(args[index]);
        message.append("]\n");
        std::cerr << message;
        params.error_value = 4;
        return false;
      }
      params.class_names.push_back(next_arg);
      skip = true;
      continue;
    }
    if (std::regex_match(args[index], regex.directory))
    {
      bool HASARG = NextArgTest(index, args);
      if (!HASARG)
      {
        params.error_value = 5;
        return false;
      }
      int next_index = index + 1;
      std::string next_arg = args[next_index];
      if (regex.IsOption(next_arg))
      {
        std::string message = "Invalid option for [";
        message.append(args[index]);
        message.append("]\n");
        std::cerr << message;
        params.error_value = 6;
        return false;
      }
      params.path_name = next_arg;
      skip = true;
      continue;
    }
    if (std::regex_match(args[index], regex.prebuild))
    {
      switches.prebuild_script = true;
      continue;
    }
  }
  return true;
}
