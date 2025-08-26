#!bash

echo "SRCS =" $(find srcs -name '*.c' | cut -c6- | cut -d '.' -f 1 ) > source.mk
