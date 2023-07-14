#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H
#include <string>
#include "ArgParser.h"
struct Globals
{
  std::string main_content;
  std::string pch_content;
  std::string prebuild_content;
  std::string makefile_content;
  void pch_content_create(Parameters &params);
  void makefile_content_create(Parameters &params);
  std::string class_header_content_create(std::string class_name);
  std::string class_source_content_create(std::string class_file_name);
  Globals(std::string &main_content) :
    main_content(main_content),
    prebuild_content(prebuild_content) {}
  Globals()
  {
    main_content =
      "#include \"pch.h\""
      "\nint main(int argc, const char *argv[])"
      "\n{"
      "\n    "
      "\n}"
      "\n";
    prebuild_content =
      "#!/usr/bin/env bash"
      "\nif [[ ! -e \"src/include/pch.h.gch\" ]]; then"
      "\n  make pch"
      "\nfi"
      "\nif ! ls src/lib/*.o 1> /dev/null 2>&1; then"
      "\n  make buildlibslinux"
      "\nfi"
      "\nif ! ls src/lib/*.a 1> /dev/null 2>&1; then"
      "\n  make buildlibslinux"
      "\nfi"
      "\n";
  }
  bool operator==(const Globals& other) const
  {
    return  main_content == other.main_content &&
            pch_content == other.pch_content;
  }
};
extern Globals globals;
#endif // GLOBALS_H
