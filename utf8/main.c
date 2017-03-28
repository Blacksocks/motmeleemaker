#include <stdio.h>
#include <stdlib.h>

int nbOfBytesInChar(unsigned char val)
{
    if (val < 128) return 1;
    if (val < 224) return 2;
    if (val < 240) return 3;
    return 4;
}

int main(void)
{
    FILE *fin;
    FILE *fout;
    char c;
    fin = fopen("in.txt", "r");
    fout = fopen("out.txt","w");
    while( (c = fgetc(fin)) != EOF)
	{
        for (int i = 0; i < nbOfBytesInChar(c) - 1; i++)
		{
            putchar(c);
            fprintf(fout, "%c", c);
            c = fgetc(fin);
        }
        putchar(c);
        fprintf(fout, "%c", c);
    }
    fclose(fin);
    fclose(fout);
    printf("\nFile has been created...\n");
    return 0;
}
