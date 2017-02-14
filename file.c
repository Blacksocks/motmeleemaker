#include "file.h"

int getNbLines(FILE * f)
{
	char c;
	int nlf = 0;
	int nbLines = 0;
	// get number of line
	while ((c = getc(f)) != EOF)
		if(c != '\n')
			nlf = 1;
		else if(nlf == 1)
		{
			nbLines++;
			nlf = 0;
		}
	return nbLines;
}
