#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace sfh {
    namespace debug {
        template <typename... Args>
        void log(Args... args) {
            // Print to console
            (std::cout << ... << args) << "\n";
        }
    }
}