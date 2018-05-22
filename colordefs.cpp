//
// Created by muman on 5/22/18.
//

#include <string>
#include "colordefs.h"

using namespace std;

namespace color {
    const std::string   ESC         = string("\x1b");
    const std::string   RESET       = ESC + "[0m";
    namespace FG {
        const std::string BLACK     = ESC + "[30m";
        const std::string RED       = ESC + "[31m";
        const std::string GREEN     = ESC + "[32m";
        const std::string YELLOW    = ESC + "[33m";
        const std::string BLUE      = ESC + "[34m";
        const std::string MAGENTA   = ESC + "[35m";
        const std::string CYAN      = ESC + "[36m";
        const std::string WHITE     = ESC + "[37m";

        const std::string BOLD_BLACK    = ESC + "[90m";
        const std::string BOLD_RED      = ESC + "[91m";
        const std::string BOLD_GREEN    = ESC + "[92m";
        const std::string BOLD_YELLOW   = ESC + "[93m";
        const std::string BOLD_BLUE     = ESC + "[94m";
        const std::string BOLD_MAGENTA  = ESC + "[95m";
        const std::string BOLD_CYAN     = ESC + "[96m";
        const std::string BOLD_WHITE    = ESC + "[97m";
    }

    namespace BG {
        const std::string BLACK     = ESC + "[40m";
        const std::string RED       = ESC + "[41m";
        const std::string GREEN     = ESC + "[42m";
        const std::string YELLOW    = ESC + "[43m";
        const std::string BLUE      = ESC + "[44m";
        const std::string MAGENTA   = ESC + "[45m";
        const std::string CYAN      = ESC + "[46m";
        const std::string WHITE     = ESC + "[47m";

        const std::string BOLD_BLACK    = ESC + "[100m";
        const std::string BOLD_RED      = ESC + "[101m";
        const std::string BOLD_GREEN    = ESC + "[102m";
        const std::string BOLD_YELLOW   = ESC + "[103m";
        const std::string BOLD_BLUE     = ESC + "[104m";
        const std::string BOLD_MAGENTA  = ESC + "[105m";
        const std::string BOLD_CYAN     = ESC + "[106m";
        const std::string BOLD_WHITE    = ESC + "[107m";
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
