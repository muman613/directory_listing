//
// Created by muman on 5/22/18.
//

#include <string>
#include "colordefs.h"

//using namespace std;
#define ESC_ASCII               "\x1b"

namespace color {
    const char *    RESET           = ESC_ASCII"[0m";
    namespace FG {
        const char * BLACK          = ESC_ASCII"[30m";
        const char * RED            = ESC_ASCII"[31m";
        const char * GREEN          = ESC_ASCII"[32m";
        const char * YELLOW         = ESC_ASCII"[33m";
        const char * BLUE           = ESC_ASCII"[34m";
        const char * MAGENTA        = ESC_ASCII"[35m";
        const char * CYAN           = ESC_ASCII"[36m";
        const char * WHITE          = ESC_ASCII"[37m";

        const char * BOLD_BLACK     = ESC_ASCII"[90m";
        const char * BOLD_RED       = ESC_ASCII"[91m";
        const char * BOLD_GREEN     = ESC_ASCII"[92m";
        const char * BOLD_YELLOW    = ESC_ASCII"[93m";
        const char * BOLD_BLUE      = ESC_ASCII"[94m";
        const char * BOLD_MAGENTA   = ESC_ASCII"[95m";
        const char * BOLD_CYAN      = ESC_ASCII"[96m";
        const char * BOLD_WHITE     = ESC_ASCII"[97m";
    }

    namespace BG {
        const char * RED                = ESC_ASCII"[41m";
        const char * GREEN              = ESC_ASCII"[42m";
        const char * YELLOW             = ESC_ASCII"[43m";
        const char * BLACK              = ESC_ASCII"[40m";
        const char * BLUE               = ESC_ASCII"[44m";
        const char * MAGENTA            = ESC_ASCII"[45m";
        const char * CYAN               = ESC_ASCII"[46m";
        const char * WHITE              = ESC_ASCII"[47m";

        const char * BOLD_RED           = ESC_ASCII"[101m";
        const char * BOLD_GREEN         = ESC_ASCII"[102m";
        const char * BOLD_YELLOW        = ESC_ASCII"[103m";
        const char * BOLD_BLUE          = ESC_ASCII"[104m";
        const char * BOLD_BLACK         = ESC_ASCII"[100m";
        const char * BOLD_MAGENTA       = ESC_ASCII"[105m";
        const char * BOLD_CYAN          = ESC_ASCII"[106m";
        const char * BOLD_WHITE         = ESC_ASCII"[107m";
    }

    std::string black(const std::string& msg, bool bold) {
        std::string result = ((bold) ? FG::BOLD_BLACK : FG::BLACK) + msg + RESET;
        return result;
    }
    std::string red(const std::string& msg, bool bold) {
        std::string result = ((bold) ? FG::BOLD_RED : FG::RED) + msg + RESET;
        return result;
    }
    std::string green(const std::string& msg, bool bold) {
        std::string result = ((bold) ? FG::BOLD_GREEN : FG::GREEN) + msg + RESET;
        return result;
    }
    std::string yellow(const std::string& msg, bool bold) {
        std::string result = ((bold) ? FG::BOLD_YELLOW : FG::YELLOW) + msg + RESET;
        return result;
    }
    std::string blue(const std::string& msg, bool bold) {
        std::string result = ((bold) ? FG::BOLD_BLUE : FG::BLUE) + msg + RESET;
        return result;
    }
    std::string magenta(const std::string& msg, bool bold) {
        std::string result = ((bold) ? FG::BOLD_MAGENTA : FG::MAGENTA) + msg + RESET;
        return result;
    }
    std::string cyan(const std::string& msg, bool bold) {
        std::string result = ((bold) ? FG::BOLD_CYAN : FG::CYAN) + msg + RESET;
        return result;
    }
    std::string white(const std::string& msg, bool bold) {
        std::string result = ((bold) ? FG::BOLD_WHITE : FG::WHITE) + msg + RESET;
        return result;
    }
}
