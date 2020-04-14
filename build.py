#!/usr/bin/python3

import sys
import os

def printHelp():
    print('build.py app - to build application')
    print('build.py tests - to build tests')
    print('build.py all - builds app with tests')

if len(sys.argv) != 2:
    print('Wrong number of arguments')
    printHelp()
    exit(1)

if sys.argv[1] == 'help':
    printHelp()
    exit(1)

if sys.argv[1] == 'app':
    print('building application')
    os.system('cd Build && cmake .')
    os.system('cd Build && make')
    exit(1)

if sys.argv[1] == 'tests':
    print('building tests')
    os.system('cd Tests && cmake .')
    os.system('cd Tests && make')
    exit(1)

if sys.argv[1] == 'all':
    print('making all')
    os.system('cd Build && cmake .')
    os.system('cd Build && make')
    os.system('cd Tests && cmake .')
    os.system('cd Tests && make')
    exit(1)