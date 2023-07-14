#include "SignalHandler.h"
#include <csignal>
#include <iostream>
#include <map>
#include <vector>
void sighandler(int signum)
{
  std::map<int, std::string> SIGNALMAP =
  {
    {2, "Cancelled by the user."},
    {4, "Invalid program instruction."},
    {6, "Abnormal program termination."},
    {8, "Erroneous arithmetic operation."},
    {11, "Invalid memory access (segmentation fault)."},
    {15, "Termination request, sent to the program."}
  };
  std::cerr << '\n' << SIGNALMAP[signum] << '\n';
  std::exit(signum);
}
void set_signal_handlers(void (&signal_handler)(int))
{
  const std::vector<int> SIGNALS =
  {SIGINT, SIGTERM, SIGABRT, SIGFPE, SIGILL, SIGSEGV};
  for (const int signal : SIGNALS)
    std::signal(signal, sighandler);
}
