#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H
extern void sighandler(int signum);
extern void set_signal_handlers(void (&signal_handler)(int));
#endif // SIGNALHANDLER_H
