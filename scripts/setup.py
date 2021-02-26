#!/usr/bin/env python3
import os, sys
from subprocess import check_call

FROM_FILE = os.path.isfile(__file__)
CVMFS_DIRS = ['/cvmfs/sft.cern.ch','/cvmfs/sft.cern.ch/lcg/views/setupViews.sh']
PYTHON_VERSION = 'LCG_97python3'
COMPILER = 'x86_64-centos7-gcc8-opt'
URL_BASE = 'https://github.com/eddieshields/ToyGenerator'
REPO = URL_BASE + '.git'
GIT = 'git'
BRANCH = 'hackathon'
QUIET_SHELL = ''>/dev/null 2>&1'

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
        check = os.system('source {} {} {} {}'}.format(CVMFS_DIRS[1],PYTHON_VERSION,COMPILER,QUIET_SHELL))
    if ( check ):
        sys.exit('Could not set up correct environment with CVMFS')
    return

def git(*args, **kwargs):
    quiet = '--quiet'
    cwd = utils_dir if args[0] != 'clone' else None
    cmd = [GIT] + list(args[:1]) + quiet + list(args[1:])

    check_call(cmd, cwd=cwd, **kwargs)

def build():
    os.mkdir('build')
    commands = '''
    cd buiild
    cmake ..
    make
    cd ..
    '''
    process = subprocess.Popen('/bin/bash', stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    out, err = process.communicate(commands)
    print out
    return

def main():
    # Checkout from git.
    git('clone', args.repo, )
    if ( args.branch ):
        get('checkout', args.branch)

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