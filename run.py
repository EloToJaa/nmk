#!/usr/bin/env python3

TESTS_GROUPS = [
    (0, 24),
    (0, 5),
    (6, 11),
    (12, 23)
]

import os
import sys

def run_test(n, output=True):
    os.system(f'./nmk < ./tests/{n}.in > ./out/{n}.out')
    if output:
        with open(f'./out/{n}.out') as f:
            print(f.read())

def run_tests(test_nums):
    first, last = test_nums
    for i in range(first, last+1):
        run_test(i, output=True)

def compile_files():
    os.system('g++ *.cpp -o nmk -std=c++17 -Wall -Wextra -Wunused -Wconversion -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG')

if __name__ == '__main__':
    if len(sys.argv) == 1:
        print('Missing an argument')
        sys.exit(1)

    compile_files()

    arg = sys.argv[1]

    if arg == '-g':
        if len(sys.argv) == 2:
            print('Missing an argument')
            sys.exit(1)
        
        arg = sys.argv[2]
        run_tests(TESTS_GROUPS[int(arg)])

        sys.exit(0)
    elif len(sys.argv) == 3:
        run_tests((int(arg), int(sys.argv[2])))

        sys.exit(0)

    test_num = int(arg)
    
    run_test(test_num)
    
    sys.exit(0)