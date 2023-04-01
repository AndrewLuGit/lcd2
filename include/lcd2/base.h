#ifndef _LCD2_BASE_H_
#define _LCD2_BASE_H_

namespace lcd2 {
struct lcd2_parameters {
    const char** autons;
    int default_auto;
    bool enable_log;
    const char** page_titles;
};
void initialize(lcd2_parameters parameters);
}

#endif