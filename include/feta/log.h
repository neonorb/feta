#ifndef LOG_H_
#define LOG_H_

#include <feta/string.h>

namespace feta {

enum LogType {
	NORMAL, WARNING, FAULT
};

void log(String message);
void warning(String message);
void fault(String message);
void log_write(LogType, String);

void write_serial(char c);
#ifdef BITS64
void debug(String name, uint64 value);
#endif
void debug(String name, uint32 value);
void debug(String name, void* value);
void debug(String name, uinteger value, uint8 base);
void debug(String message);
void debug(strchar message);
void debugPrint(String message);

void status(String message);
void statusDone();
void statusFail();

void crash(String message);

}

#endif /* LOG_H_ */
