set -e

gcc -g ./prog/find_discontinuities.c -o find_discontinuities
gcc -g ./prog/extract_range.c -o extract_range 
gcc -g ./prog/example.c -o example
