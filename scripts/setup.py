#!/usr/bin/env python3
import os, sys
import subprocess
from subprocess import check_call

FROM_FILE = os.path.isfile(__file__)
CVMFS_DIRS = ['/cvmfs/sft.cern.ch','/cvmfs/sft.cern.ch/lcg/views/setupViews.sh']
PYTHON_VERSION = 'LCG_97python3'
COMPILER = 'x86_64-centos7-gcc8-opt'
URL_BASE = 'https://github.com/eddieshields/ToyGenerator'
REPO = URL_BASE + '.git'
GIT = 'git'
BRANCH = 'hackathon'
QUIET_SHELL = '>/dev/null 2>&1'

import argparse
parser = argparse.ArgumentParser( 'Hydra setup', formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument('path',help='Path to stack directory',**({'nargs': '?'} if FROM_FILE else {}))
parser.add_argument('--repo',   '-u', default=REPO,   help='Repository URL')
parser.add_argument('--branch', '-b', default=BRANCH, help='Branch')
args = parser.parse_args()

def check_exists(program):
    return not os.system('which {} {}'.format(program,QUIET_SHELL))

def detect_cvmfs():
    check = 0
    if os.path.exists(CVMFS_DIRS[0]):
        print("Detected CVMFS")
        check = os.system('source {} {} {} {}'.format(CVMFS_DIRS[1],PYTHON_VERSION,COMPILER,QUIET_SHELL))
    if ( check ):
        sys.exit('Could not set up correct environment with CVMFS')
    return

def git(*args, **kwargs):
    quiet = ['--quiet']
    cwd = None
    cmd = [GIT] + list(args[:1]) + quiet + list(args[1:])

    check_call(cmd, cwd=cwd, **kwargs)

def build():
    cwd = os.getcwd()
    os.chdir( args.path )
    print('Building...')
    os.mkdir('build')
    command = 'git submodule update --init --recursive; cd build; cmake ..; make -j 4; cd ..'
    process = os.system(command)
    os.system('source setup.sh {}'.format(QUIET_SHELL))
    if not ( process ): print('Built!')
    os.chdir( cwd )
    return

def main():
    # Checkout from git.
    if ( os.path.exists( args.path ) ): sys.exit('{} already exists'.format(args.path))
    print('Fetching repository...')
    git('clone', args.repo, args.path )
    os.chdir(args.path)
    if ( args.branch ):
        git('checkout', args.branch)

    # Build
    if not ( check_exists('cmake') ): sys.exit('CMake is needed and could not be found')
    build()

    # Check build
    os.system('source setup.sh {}'.format(QUIET_SHELL))
    if os.path.exists('build/libHYDRA.so'): print('Successful build!')

    return 

#-------------------------
if __name__ == '__main__':
    main()