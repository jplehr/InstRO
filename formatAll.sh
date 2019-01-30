#!/bin/sh
find ./lib -regex '.*\.\(h\|cpp\)' -exec clang-format -i {} \;
