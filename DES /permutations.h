#ifndef PERMUTATIONS_H_INCLUDED
#define PERMUTATIONS_H_INCLUDED

char* permute(char *, char *, long);
char* splitToL0(char *tab);
char* splitToR0(char *tab);
char* keyLeftShift(char *tab, char *keyshift, int shift);
char* Union(char *tab1, char *tab2, int length);
char* Xor(char *tab1, char *tab2, int length);
char* sBoxOperation(char *tab, char **sBox, int length);
char* valueResearchBox(char **sBox, char* output, char row, char column, int choice);
char  generateIntFromBitBlock(char *block, int blocksize);
char* generateBitBlockFromInt(int outputvalue);
#endif // PERMUTATIONS_H_INCLUDED
