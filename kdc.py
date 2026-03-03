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

def compile_flags(debug):
    if debug:
        return ['-c', '-g', '-o']
    return ['-c', '-o']

def compile_library(lib_files, args, flags):
    lib_path = ".sys_lib"
    if not os.path.exists(lib_path):
        os.makedirs(lib_path)

    for lib_file in lib_files:
        source_path = 'sys_lib/'+lib_file+'.c'
        object_path = lib_path+'/'+lib_file+'.o'
        subprocess.run(args + flags + [object_path, source_path])

def library_obj(lib_files, dlib_files):
    out = []
    for file in lib_files:
        out.append('.sys_lib/'+file+'.o')
    for file in dlib_files:
        out.append('.sys_lib/'+file+'.o')
    return out

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
    parser.add_argument('-d', '--debug',
                        action="store_true",
                        help='set debug flags in the ASM file')
    args = parser.parse_args()

    pre_compilation() # compile kdc if it does not exist

    input_path = Path(args.path);

    output_name = args.output
    object_name = output_name+'.o'
    asm_name = output_name+'.s'

    if not input_path.exists():
        print(f"Error: file {input_path} not found")
        sys.exit(1)
    
    obj_format = check_object_format() # check which object format to use based on host
    
    compile_target = args.target # if no compile target specified target based on host
    if not compile_target:
        compile_target = check_compile_target()
    
    gcclang_args = get_gcclang_args(obj_format, compile_target)
    
    dyn_sys_lib_files = ['closure_gen', 'struct_gen'] # dynamic lib files, change on each compilation
    sys_lib_files = ['closure', 'iofunc', 'lists', 'math', 'mem', 'structs'] # static lib files
    
    flags = compile_flags(args.debug)

    compile_library(sys_lib_files, gcclang_args, flags)

    with open(input_path, "rb") as f:
        kdc_run = subprocess.run(
            ['./kdc', compile_target, obj_format, output_name],
            stdin=f,
            capture_output=True,
        )

    compile_library(dyn_sys_lib_files, gcclang_args, flags)
    subprocess.run(gcclang_args + flags + [object_name, asm_name]) # generate otuput file
    subprocess.run(gcclang_args + ['-o', output_name, object_name] + library_obj(sys_lib_files, dyn_sys_lib_files))


if __name__ == "__main__":
    compile();