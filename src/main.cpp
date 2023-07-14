#include "cppproj.h"
int main(int argc, const char *argv[])
{
  set_signal_handlers(sighandler);
  Parameters params;
  Switches switches;
  bool ARGSPARSEDNOERROR = true;
  if (argc > 1)
  {
    ARGSPARSEDNOERROR = ArgParser(argc, argv, params, switches);
  }
  if (switches.is_help)
  {
    return EXIT_SUCCESS;
  }
  if (!ARGSPARSEDNOERROR)
  {
    return params.error_value;
  }
  std::string PARENTPATH = params.path_name;
  const std::map<std::string, std::string> DIRECTORIESMAP =
  {{"source", "src"}, {"include", "src/include"}, {"library", "src/lib"}};
  for (auto const &[key, value] : DIRECTORIESMAP)
  {
    directories.setNewPath(key, PARENTPATH);
    directories.append(key, value);
  }
  std::map<std::string, std::filesystem::path> dir_paths = directories.getPaths();
  const std::string MAINFILE = [&dir_paths, params]()
  {
    std::string mainfile = dir_paths["source"].native().c_str();
    mainfile.push_back('/');
    mainfile.append(params.main_name);
    mainfile.append(".cpp");
    return mainfile;
  }
  ();
  files.setNewPath("main", MAINFILE);
  auto class_file = [&dir_paths](std::string class_name, std::string extension)
  {
    std::string classfile = dir_paths["include"].native().c_str();
    classfile.push_back('/');
    classfile.append(class_name);
    classfile.push_back('.');
    classfile.append(extension);
    return classfile;
  };
  params.class_names.push_back("pch");
  for (const std::string class_name : params.class_names)
  {
    std::string class_name_h    = class_name;
    std::string class_name_cpp  = class_name_h;
    class_name_h.append("_h");
    class_name_cpp.append("_cpp");
    files.setNewPath(class_name_h, class_file(class_name, "h"));
    files.setNewPath(class_name_cpp, class_file(class_name, "cpp"));
  }
  files.setNewPath("make", PARENTPATH);
  files.append("make", "Makefile");
  if (switches.prebuild_script)
  {
    files.setNewPath("prebuild", PARENTPATH);
    files.append("prebuild", "prebuild");
  }
  std::map<std::string, std::filesystem::path> file_paths = files.getPaths();
  globals.pch_content_create(params);
  globals.makefile_content_create(params);
  const int dir_create_result = process_directories(dir_paths, params);
  if (dir_create_result > 0)
  {
    return params.error_value;
  }
  const int file_create_result = process_files(file_paths, params, globals, switches);
  return params.error_value;
}
