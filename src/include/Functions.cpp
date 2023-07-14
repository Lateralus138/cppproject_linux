#include "Functions.h"
#include <iostream>
#include <fstream>
bool PathExists(std::filesystem::path path, Parameters &params, int error_code)
{
  bool path_exists;
  try
  {
    path_exists = std::filesystem::exists(path);
  }
  catch (std::filesystem::filesystem_error ferr)
  {
    std::cout << ferr.what() << '\n';
    params.error_value = error_code;
  }
  return path_exists;
}
void StringAppendIf(bool test, std::string &variable, std::string if_, std::string else_)
{
  if (test) variable.append(if_);
  else variable.append(else_);
}
bool CreateDirectory(std::filesystem::path path, Parameters &params, int error_code)
{
    bool dir_created;
    try
    {
      dir_created = std::filesystem::create_directories(path);
    }
    catch (std::filesystem::filesystem_error ferr)
    {
      std::cerr << ferr.what() << '\n';
      params.error_value = error_code;
    }
    return dir_created;
}
bool CreateFile(std::filesystem::path path, std::string content, Parameters &params, int error_code)
{
  bool file_created = false;
  std::string message;
  std::ofstream out_file_stream(path.native().c_str());
  if (out_file_stream.is_open())
  {
    out_file_stream << content;
    if (out_file_stream.bad())
    {
      message = "Could not write to ";
      message.append(path);
      message.append(".\n");
      std::cerr << message;
      params.error_value = error_code;
      file_created = false;
    }
    else
    {
      message = path;
      message.append(" created successfully.\n");
      std::cerr << message;
      file_created = true;
    }
    out_file_stream.close();
  }
  else
  {
    message = "Could not open ";
    message.append(path);
    message.append(".\n");
    std::cerr << message;
    params.error_value = error_code;
    file_created = false;
  }
  return file_created;
}
int process_directories(std::map<std::string, std::filesystem::path> &dir_paths, Parameters &params)
{
  for (std::pair const [key, value] : dir_paths)
  {
    if (key == "source") continue;
    std::string temp_message = "Checking if ";
    const std::string path = value.native().c_str();
    temp_message.append(path);
    temp_message.append(" exists...\n");
    std::cout << temp_message;
    temp_message.clear();
    const bool dir_exists = PathExists(value, params, 7);
    if (params.error_value > 0)
    {
      return params.error_value;
    }
    temp_message.append(path);
    StringAppendIf(dir_exists, temp_message,
                   " already exists and does not need to be created...\n",
                   " does not exist; attempting to create directory...\n");
    std::cout << temp_message;
    temp_message.clear();
    if (dir_exists) continue;
    const bool dir_created = CreateDirectory(value, params, 8);
    if (params.error_value > 0)
    {
      return params.error_value;
    }
    temp_message.append(path);
    temp_message.append(" was created successfully...\n");
    std::cout << temp_message;
    temp_message.clear();
  }
  return params.error_value;
}
int process_files
(
  std::map<std::string, std::filesystem::path> & file_paths,
  Parameters &params, Globals &globals, Switches & switches
)
{
  for (std::pair const [key, value] : file_paths)
  {
    std::string temp_message = "Checking if ";
    const std::string path = value.native().c_str();
    temp_message.append(path);
    temp_message.append(" exists...\n");
    std::cout << temp_message;
    temp_message.clear();
    const bool file_exists = PathExists(value, params, 9);
    if (params.error_value > 0)
    {
      return params.error_value;
    }
    temp_message.append(path);
    StringAppendIf(file_exists, temp_message,
                   " already exists and does not need to be created...\n",
                   " does not exist; attempting to create file...\n");
    std::cout << temp_message;
    temp_message.clear();
    if (file_exists) continue;
    std::string content;
    if (key == "main")
    {
      content = globals.main_content;
    }
    else if (key == "make")
    {
      content = globals.makefile_content;
    }
    else if (key == "pch_h")
    {
      content = globals.pch_content;
    }
    else if ((switches.prebuild_script) && (key == "prebuild"))
    {
      content = globals.prebuild_content;
    }
    else
    {
      bool delim_found = false;
      size_t delim_pos = key.find('_');
      delim_found = (delim_pos != std::string::npos);
      if (!delim_found)
      {
        continue;
      }
      std::string ext_ = key.substr(delim_pos);
      if (ext_ == "_h")
      {
        content = globals.class_header_content_create(key);
      }
      else
      {
        content = globals.class_source_content_create(value.stem().native().c_str());
      }
    }
    CreateFile(value, content, params, 10);
    if (params.error_value > 0)
    {
      return params.error_value;
    }
  }
  return params.error_value;
}
