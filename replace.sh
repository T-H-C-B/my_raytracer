#!/bin/bash

find . -type f -iname "*.cpp" -o -iname "*.hpp" -o -iname "*.h" | while read file; do
  sed -i '/#include <libconfig.h++>/d' "$file"
done
