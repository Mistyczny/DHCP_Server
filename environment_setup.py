#!/usr/bin/python

import os
import pip
import subprocess
import sys
import wget

extra_libraries_directory = "./3rdParty"
boost_url = "https://dl.bintray.com/boostorg/release/1.72.0/source/boost_1_72_0.tar.gz"

try:
    os.mkdir(extra_libraries_directory)
except OSError:
    print ("Creation of the directory %s failed" % extra_libraries_directory)
else:
    print ("Successfully created the directory %s " % extra_libraries_directory)
    wget.download(boost_url, extra_libraries_directory)