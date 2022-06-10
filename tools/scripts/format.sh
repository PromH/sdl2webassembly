#!/bin/bash
find src/cpp -regex '.*\.\(cpp\|h\|hpp\|cc\|cxx\)' -exec clang-format -style=Google -i {} \;
