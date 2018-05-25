/**
 * @file        colordefs.h
 */

#ifndef ANSICOLOR_COLORDEFS_H
#define ANSICOLOR_COLORDEFS_H

/**
 * @namespace   color
 * @brief       provide a simple way to output ANSI color codes to the console
 */
namespace color {
    extern const char * RESET;
    /**
     * Foreground colors
     */
    namespace FG {
        extern const char * BLACK;
        extern const char * RED;
        extern const char * GREEN;
        extern const char * YELLOW;
        extern const char * BLUE;
        extern const char * MAGENTA;
        extern const char * CYAN;
        extern const char * WHITE;

        extern const char * BOLD_BLACK;
        extern const char * BOLD_RED;
        extern const char * BOLD_GREEN;
        extern const char * BOLD_YELLOW;
        extern const char * BOLD_BLUE;
        extern const char * BOLD_MAGENTA;
        extern const char * BOLD_CYAN;
        extern const char * BOLD_WHITE;
    }
    /**
     * Background colors
     */
    namespace BG {
        extern const char * BLACK;
        extern const char * RED;
        extern const char * GREEN;
        extern const char * YELLOW;
        extern const char * BLUE;
        extern const char * MAGENTA;
        extern const char * CYAN;
        extern const char * WHITE;

        extern const char * BOLD_BLACK;
        extern const char * BOLD_RED;
        extern const char * BOLD_GREEN;
        extern const char * BOLD_YELLOW;
        extern const char * BOLD_BLUE;
        extern const char * BOLD_MAGENTA;
        extern const char * BOLD_CYAN;
        extern const char * BOLD_WHITE;
    }

    extern std::string black(const std::string & msg, bool bold = false);
    extern std::string red(const std::string & msg, bool bold = false);
    extern std::string green(const std::string & msg, bool bold = false);
    extern std::string yellow(const std::string & msg, bool bold = false);
    extern std::string blue(const std::string & msg, bool bold = false);
    extern std::string magenta(const std::string & msg, bool bold = false);
    extern std::string cyan(const std::string & msg, bool bold = false);
    extern std::string white(const std::string & msg, bool bold = false);
}

#endif //ANSICOLOR_COLORDEFS_H
