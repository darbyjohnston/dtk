#!/bin/sh

find lib examples -name "*.h" -or -name "*.cpp" | xargs wc -l
find lib examples -name "*.h" -or -name "*.cpp" | wc -l

