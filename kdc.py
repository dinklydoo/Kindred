import os
import sys
import argparse
import platform
import subprocess
from pathlib import Path

def check_object_format():
    host = platform.system()
    if host == "Darwin":
        return "MACHO"
    else:
        return "ELF"

def check_compile_target():
    host = platform.system()
    if host == "Darwin":
        return "ARM"
    else:
        return "X86"

def pre_compilation():
    build_dir = 'build'
    if not os.path.exists(build_dir):
        os.makedirs(build_dir)

    # compile kdc.cpp
    subprocess.run(['cmake', '-S', '.', '-B', build_dir], check=True)
    subprocess.run(['cmake', '--build', '.'], check=True)
    
def get_gcclang_args(obj_format, compile_target):
    if obj_format == "MACHO":
        if compile_target == "X86":
            return ['clang', '-arch', 'x86_64']
        else:
            return ['clang', '-arch', 'arm64']
    else:
        return ['gcc'] # for now just use native gcc if on linux


def compile():
    parser = argparse.ArgumentParser(description='KDC Kindred Language Compiler')
    parser.add_argument('-o','--output',
                        default='a',
                        help='output file name created in the current working directory (default a)')
    parser.add_argument('-p', '--path', required=True,
                        help='the path to .kd file to compile')
    parser.add_argument('-t', '--target',
                        choices=['X86', 'ARM', 'MIPS'],
                        default=None,
                        help='compile target, selected from X86, ARM or MIPS')
    args = parser.parse_args()

    pre_compilation() # compile kdc if it does not exist

    input_path = Path(args.path);
    output_name = args.output

    if not input_path.exists():
        print(f"Error: file {input_path} not found")
        sys.exit(1)
    
    obj_format = check_object_format() # check which object format to use based on host
    
    compile_target = args.target # if no compile target specified target based on host
    if not compile_target:
        compile_target = check_compile_target()
    
    gcclang_args = get_gcclang_args(obj_format, compile_target)
    
    dyn_sys_lib_files = ['closure_gen.c', 'struct_gen.c'] # dynamic lib files, change on each compilation
    sys_lib_files = ['closure.c', 'iofunc.c', 'lists.c', 'math.c', 'mem.c', 'structs.c'] # static lib files

    


if __name__ == "__main__":
    compile();
    
