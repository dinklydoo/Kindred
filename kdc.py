import os
import sys
import argparse







if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='KDC Kindred Language Compiler')
    parser.add_argument('-o','--output', metavar='output', required=False,
                        help='output file name created in the current working directory')
    parser.add_argument('-p', '--path', metavar='path', required=True,
                        help='the path to .kd file to compile')
    parser.add_argument('-t', '--target', metavar='target', required=False,
                        help='compile target, selected from X86, ARM or MIPS')
    args = parser.parse_args()
