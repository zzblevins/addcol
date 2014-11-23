/*

	addcol.c

	Sum numbers in a given column of a text file

	Syntax:
	% addcol [-v] [-c #] [-h] [-t #] [-d char] [-f filename]

	Dean Blevins
	November 2014
	Updated: Sat Nov 22 13:36:15 CST 2014

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define TRUE		1
#define FALSE		(!TRUE)
#define MAXFILENAME	20
#define MAXLINELENGTH	1024
#define MAXDELIMCHARS	1024

main(int argc, char *argv[])
{

	FILE *fp;

	char filename[MAXFILENAME];
	char textline[MAXLINELENGTH];
	char delim[MAXDELIMCHARS] =	" "; 
	char *ptr;

	int o;
	int fflag =		0;
	int cflag =		0;
	int dflag =		0;
	int tflag =		0;
	int vflag =		0;
	int maxline =		MAXLINELENGTH; 
	int headerlines =	0;
	int h =			0;
	int i =			0;
	int col =		0;
	int sum =		0;

	while ((o = getopt(argc, argv, "vhc:f:t:d:")) != -1) {
		switch (o) {
			case 'v':
				vflag = 1;
				break;
			case 'f':
				fflag = 1;
				strcpy(filename, optarg);
				break;
			case 'd':
				dflag = 1;
				strcpy(delim, optarg);
				break;
			case 't':
				tflag =1;
				headerlines = atoi(optarg);
				break;
			case 'c':
				cflag =1;
				col = atoi(optarg);
				break;
			case 'h':
				printf("Syntax: %s [-v] [-x] [-f filename]\n", argv[0]);
				printf(" -c #: column # to sum\n");
				printf(" -t #: number of header lines output for debug\n");
				printf(" -d char: delimiter (default=<space>|tab)\n");
				printf(" -f filename : textfile to use. Without -f, uses stdin\n");
				printf(" -h : syntax\n");
				printf(" -v : verbose output for debug\n");
				exit(0);
				break;
			case '?':
				if (optopt == 'f') {
					// No filename give after the -f
					exit (-1);
				} else if (isprint(optopt)) {
					exit (-1);
				}
				break;
			default:
				break;
		}
	}

	// Use stdin if no filename provided

	if (fflag == FALSE) {
		fp = stdin;

		if (vflag)
			printf("@filename= stdin\n");

	} else {

		if (vflag)
			printf("@filename= %s\n", filename);

		// Open and work on the source file

		if ( ( fp = fopen(filename, "r") ) == NULL) {
			fprintf(stderr, "Error: Can't read %s\n", filename);
			return (-1);
		}
	}

	if (vflag) {
		printf("@headerlines= %d\n", headerlines);
		printf("@col= %d\n", col);
		printf("@delimiter= %s\n", delim);
	}

	// Get past the header lines
	for (h=0; h<headerlines; h++) {
		fgets(textline, maxline, fp);
	}

	// Process the rest of the text file (or stdin)

	while ( ( fgets(textline, maxline, fp) ) != NULL) {

		ptr = strtok(textline, delim);
		for (i=1; i<col; i++) {

			ptr = strtok(NULL, delim);

			if (ptr == NULL) {
				fprintf(stderr,"Error: Only %d column(s)\n", i);
				exit (-1);
			}
		}

		sum += atoi(ptr);
	}

	printf("%d\n", sum);

	fclose(fp);

	return (0);
}

