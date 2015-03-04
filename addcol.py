#!/usr/bin/python

#
#	Sum numbers in a given column of a text file or pipe
# 
#	Syntax:
#       % addcol [-v] [-c #] [-h] [-t #] [-d char] filename|<stdin>
#
# 	Dean Blevins
# 	Feb 2015
#

import pdb		# Debugger

import argparse		# argv utilities
import sys
import os
import re		# regular expressions

codeversion =	1.0
h =		0
tot =		0

parser = argparse.ArgumentParser()
parser.add_argument("-v", "--verbose", help="verbose output", action="store_true")
parser.add_argument("-c", "--column", type=int, help="column # to sum")
parser.add_argument("-t", "--hdr", type=int, help="# of column headers")
parser.add_argument("-d", "--delim", help="delimiter char for column separator", default=' ')
parser.add_argument("--version", help="version info", action="store_true")
parser.add_argument("source", help="source file(s)...", nargs=argparse.REMAINDER)
args = parser.parse_args()

#pdb.set_trace()	#Turn on debugger

# If just looking at program version, show it and exit
if args.version:
	print os.path.basename(sys.argv[0]), codeversion
	sys.exit(0)

# If no source file given, use <stdin>

if args.source:

	if args.verbose:
		print "Input file: ",  args.source

	fp = open(args.source[0], 'r')

else:

	fp = sys.stdin

	if args.verbose:
		print "Input <stdin>"

if args.verbose:
	if args.hdr > 0:
		print "Skiping ", args.hdr, " header lines..."
	else:
		print "No header lines..."

# Get past the header lines (if any)
if args.hdr:

	for h in range(0, args.hdr):
		fp.readline()
 
# Process rest of sourcefile (or <stdin>

for textline in fp:

	if args.delim == ' ':
		# Assume this means whitespace
		tokline = re.split('\s', textline)
	else :

		# Split by given delimiter (--delim)
		tokline = textline.split(args.delim, args.column)

	# Column we want is one less than where the split stopped, convert to an int
	tot += int(tokline[args.column -1])

print tot

fp.close()
