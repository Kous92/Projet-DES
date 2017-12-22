#ifndef DES_H_INCLUDED
#define DES_H_INCLUDED

#include <iostream>
using namespace std;

class DES
{
    private:
    string message;
    char* messageBlock;

    char *result1;
    char *R0;
    char *L0;
    char *result2;
    char* leftKey;
    char* rightKey;
    char* key;
    char* result3;
    char* result4;
    char* result5;
    char* result6;
    char* result7;
    char* L1;
    char* R1;
    char** sBoxCopy;

    public:
    DES(char* messageBlock); // Constructor with 64-bit block message

    // Getters
    char* getResult1();
    char* getResult2();
    char* getResult3();
    char* getResult4();
    char* getResult5();
    char* getResult6();
    char* getResult7();
    char* getLeftKey();
    char* getRightKey();
    char* getL0();
    char* getR0();
    char* getKey();

    // Methods
    char* permutation(char *, char *, long);
    char* splitL0(char *tab);
    char* splitR0(char *tab);
    char* keyLeftShift(char *tab, char *keyshift, int shift);
    char* tableUnion(char *tab1, char *tab2, int length);
    char* xorOperation(char *tab1, char *tab2, int length);
    char* sBoxOperation(char *tabXor, char **sBox, int length); // Step 5
    char* valueResearchBox(char **sBox, char* output, char row, char column, int choice);
    char  generateIntFromBitBlock(char *block, int blocksize);
    char* generateBitBlockFromInt(int outputvalue);
    void displayBitTable(char *, long );
    void displayAsHex(char *, long );

    // Steps for encryption
    void initialPermutation(); // Step 1
    void splitPermutatedMessage(); // Step 2
    void do16rounds(); // Step 2.1
    void expansionRi(int i); // Step 3
    void subKeyGeneration(int i); // Step 3.1
    void xorOperationSubKeyRi(int i); // Step 4
    void permutationSBoxResult(); // Step 6
    void xorOperationSubKeyLi(int i); // Step 7
    void assemblyL16R16(); // Step 8
    void finalPermutation(); // Step 9

    void DESEncryption();
};

#endif // DES_H_INCLUDED
