/**
 * @file        colordefs.h
 */

#ifndef ANSICOLOR_COLORDEFS_H
#define ANSICOLOR_COLORDEFS_H

namespace color {
    extern const std::string RESET;
    namespace FG {
        extern const std::string BLACK;
        extern const std::string RED;
        extern const std::string GREEN;
        extern const std::string YELLOW;
        extern const std::string BLUE;
        extern const std::string MAGENTA;
        extern const std::string CYAN;
        extern const std::string WHITE;

        extern const std::string BOLD_BLACK;
        extern const std::string BOLD_RED;
        extern const std::string BOLD_GREEN;
        extern const std::string BOLD_YELLOW;
        extern const std::string BOLD_BLUE;
        extern const std::string BOLD_MAGENTA;
        extern const std::string BOLD_CYAN;
        extern const std::string BOLD_WHITE;
    }
    namespace BG {
        extern const std::string BLACK;
        extern const std::string RED;
        extern const std::string GREEN;
        extern const std::string YELLOW;
        extern const std::string BLUE;
        extern const std::string MAGENTA;
        extern const std::string CYAN;
        extern const std::string WHITE;

        extern const std::string BOLD_BLACK;
        extern const std::string BOLD_RED;
        extern const std::string BOLD_GREEN;
        extern const std::string BOLD_YELLOW;
        extern const std::string BOLD_BLUE;
        extern const std::string BOLD_MAGENTA;
        extern const std::string BOLD_CYAN;
        extern const std::string BOLD_WHITE;
    }

    extern std::string black(const std::string& msg, bool bold = false);
    extern std::string red(const std::string& msg, bool bold = false);
    extern std::string green(const std::string& msg, bool bold = false);
    extern std::string yellow(const std::string& msg, bool bold = false);
    extern std::string blue(const std::string& msg, bool bold = false);
    extern std::string magenta(const std::string& msg, bool bold = false);
    extern std::string cyan(const std::string& msg, bool bold = false);
    extern std::string white(const std::string& msg, bool bold = false);

}

#endif //ANSICOLOR_COLORDEFS_H
