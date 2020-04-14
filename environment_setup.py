#!/usr/bin/python

import os
import pip
import subprocess
import sys
import wget

boost_version = '1_72_0'

extra_libraries_directory = "./3rdParty"
boost_url = "https://dl.bintray.com/boostorg/release/1.72.0/source/boost_"+ boost_version +".tar.gz"

def checkBoostExistance():
    boost_dir_existance = os.path.isdir('./3rdParty/boost')
    if boost_dir_existance == True:
        print('Boost library already exist with version= '+ boost_version)
        return True
    else:
        return False

def install_boost_library():
    wget.download(boost_url, extra_libraries_directory)
    os.system('cd 3rdParty && tar -xvf boost_'+ boost_version +'.tar.gz')
    os.system('mv ./3rdParty/boost_'+ boost_version +' ./3rdParty/boost')
    os.system('cd 3rdParty/boost/ && ./bootstrap.sh')
    os.system('cd 3rdParty/boost && ./b2 install')
    os.system('cd 3rdParty/ && rm boost_'+ boost_version +'.tar.gz')

def create_3rdParty_directory():
    extra_libraries_dir_existance = os.path.isdir(extra_libraries_directory)
    if extra_libraries_dir_existance == False:
        try:
            os.mkdir(extra_libraries_directory)
        except OSError:
            print ("Creation of the directory %s failed" % extra_libraries_directory)
            return False
        else:
            print ("Successfully created the directory %s " % extra_libraries_directory)
            return True
    else:
        print ("Extra libraries directory already exists")
        return True

if __name__ == "__main__":
    if create_3rdParty_directory():
        if checkBoostExistance() == False:
            install_boost_library()