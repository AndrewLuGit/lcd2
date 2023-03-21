#ifndef _LCD2_H_
#define _LCD2_H_

namespace lcd2 {
void initialize();

bool printf(int line, const char* fmt, ...);
bool print(int line, const char* text);

extern char auton[];
}

#endif