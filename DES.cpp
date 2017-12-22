#include <iostream>
#include "DES.h"
#include <cstdlib>
#include "data_tables.h"
#include "math.h"
#include <cstring>

using namespace std;

DES::DES(char* messageBlock)
{
    this->messageBlock = messageBlock;
}

char* DES::getResult1()
{
    return result1;
}

char* DES::getResult2()
{
    return result2;
}

char* DES::getResult3()
{
    return result3;
}

char* DES::getResult4()
{
    return result4;
}

char* DES::getResult5()
{
    return result5;
}

char* DES::getResult6()
{
    return result6;
}

char* DES::getResult7()
{
    return result7;
}

char* DES::getLeftKey()
{
    return leftKey;
}

char* DES::getRightKey()
{
    return rightKey;
}

char* DES::getL0()
{
    return L0;
}

char* DES::getR0()
{
    return R0;
}

char* DES::getKey()
{
    return key;
}

char* DES::permutation(char *table, char *perm_table, long tabsize)
{
    char *result = new char[tabsize];

    for(int i=0; i <tabsize;i++)
    {
        result[i]=table[(int)perm_table[i]-1];
    }

    return result;
}

char* DES::splitL0(char *tab)
{
    char *L0 = new char[32];

    for(int i = 0; i<32; i++)
    {
        L0[i] = tab[i];
    }
    return L0;
}

char* DES::splitR0(char *tab)
{
    char *R0 = new char[32];

    for(int i = 32; i<64; i++)
    {
        R0[i-32] = tab[i];
    }
    return R0;
}

char* DES::keyLeftShift(char *tab, char *keyshift, int shift)
{
    char *table = new char[28];
    for(int i = 0; i<28; i++)
    {
        table[i] = tab[(i+(int)keyshift[shift])%28];
    }
    return table;
}

char* DES::tableUnion(char *tab1, char *tab2, int length)
{
    char *tab = new char[length];

    for (int i = 0; i< (length / 2); i++)
    {
        tab[i] = tab1[i];
    }

    for (int i = (length / 2); i < length; i++)
    {
        tab[i] = tab2[i- (length / 2)];
    }

    return tab;
}

char* DES::xorOperation(char *tab1, char *tab2, int length)
{
    char* tab = new char[length];

    for (int i = 0; i < length; i++)
    {
        if(tab1[i] == tab2[i])
        {
            tab[i] = 0;
        }
        else
        {
            tab[i] = 1;
        }
    }
    return tab;
}

char* DES::sBoxOperation(char *Xor, char **SBox, int length)
{
    char* rowBox = new char[2];
    char* columnBox = new char[4];

    // Output
    char* output1 = new char[4]; //output SBox 4 bits
    char* output2 = new char[4];
    char* output3 = new char[4];
    char* output4 = new char[4];
    char* output5 = new char[4];
    char* output6 = new char[4];
    char* output7 = new char[4];
    char* output8 = new char[4];

    // Splitting XOR operation result in 8 blocks of 6 bits
    // Block 1
    // The first and last bits of each block to determine the SBOX row
    rowBox[0] = Xor[0];
    rowBox[1] = Xor[5];

    // The 4 bits of the middle allows to determine the SBOX column
    columnBox[0] = Xor[1];
    columnBox[1] = Xor[2];
    columnBox[2] = Xor[3];
    columnBox[3] = Xor[4];

    // Retreiving the first 4-bit block
    output1 = valueResearchBox(SBox, output1, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 0);

    // Block 2
    rowBox[0] = Xor[6];
    rowBox[1] = Xor[11];

    columnBox[0] = Xor[7];
    columnBox[1] = Xor[8];
    columnBox[2] = Xor[9];
    columnBox[3] = Xor[10];

    output2 = valueResearchBox(SBox, output2, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 1);

    // Block 3
    rowBox[0] = Xor[12];
    rowBox[1] = Xor[17];

    columnBox[0] = Xor[13];
    columnBox[1] = Xor[14];
    columnBox[2] = Xor[15];
    columnBox[3] = Xor[16];

    output3 = valueResearchBox(SBox, output3, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 2);

    // Block 4
    rowBox[0] = Xor[18];
    rowBox[1] = Xor[23];

    columnBox[0] = Xor[19];
    columnBox[1] = Xor[20];
    columnBox[2] = Xor[21];
    columnBox[3] = Xor[22];

    output4 = valueResearchBox(SBox, output4, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 3);

    // Block 5
    rowBox[0] = Xor[24];
    rowBox[1] = Xor[29];

    columnBox[0] = Xor[25];
    columnBox[1] = Xor[26];
    columnBox[2] = Xor[27];
    columnBox[3] = Xor[28];

    output5 = valueResearchBox(SBox, output5, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 4);

    // Block 6
    rowBox[0] = Xor[30];
    rowBox[1] = Xor[35];

    columnBox[0] = Xor[31];
    columnBox[1] = Xor[32];
    columnBox[2] = Xor[33];
    columnBox[3] = Xor[34];

    output6 = valueResearchBox(SBox, output6, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 5);

    // Block 7
    rowBox[0] = Xor[36];
    rowBox[1] = Xor[41];

    columnBox[0] = Xor[37];
    columnBox[1] = Xor[38];
    columnBox[2] = Xor[39];
    columnBox[3] = Xor[40];

    output7 = valueResearchBox(SBox, output7, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 6);

    // Block 8
    rowBox[0] = Xor[42];
    rowBox[1] = Xor[47];

    columnBox[0] = Xor[43];
    columnBox[1] = Xor[44];
    columnBox[2] = Xor[45];
    columnBox[3] = Xor[46];

    output8 = valueResearchBox(SBox, output8, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 7);

    // Final block -> assembly of the 8 4-bit blocks: Output result
    char* outputBoxResult = new char[32];

    for (int i = 0; i< 32; i++)
    {
        if ((0 <= i) && (i < 4))
        {
            outputBoxResult[i] = output1[i];
        }
        else if ((4 <= i) && (i < 8))
        {
            outputBoxResult[i] = output2[i-4];
        }
        else if ((8 <= i) && (i < 12))
        {
            outputBoxResult[i] = output3[i-8];
        }
        else if ((12 <= i) && (i < 16))
        {
            outputBoxResult[i] = output4[i-12];
        }
        else if ((16 <= i) && (i < 20))
        {
            outputBoxResult[i] = output5[i-16];
        }
        else if ((20 <= i) && (i < 24))
        {
            outputBoxResult[i] = output6[i-20];
        }
        else if ((24 <= i) && (i < 28))
        {
            outputBoxResult[i] = output7[i-24];
        }
        else if ((28 <= i) && (i < 32))
        {
            outputBoxResult[i] = output8[i-28];
        }
    }

    return outputBoxResult;
}

char* DES::valueResearchBox(char **SBox, char* output, char row, char column, int choice)
{
    char value;

    // Line choice: each line matches 16 bits
    if ((int)row == 0)
    {
        // Columns run
        for (int i = 0; i < 16; i++)
        {
            // If the column passed in parameter matches to the loop column, retreive the value in the right sub-SBOX;
            if (i == (int)column)
            {
                // Retreive value in a sub-SBOX
                value = SBox[choice][i];
            }
        }
        // Output value: 4 bits block
        output = generateBitBlockFromInt(value);
    }

    if ((int)row == 1)
    {
        for (int i = 16; i < 32; i++)
        {
            if ((i - 16) == (int)column)
            {
                value = SBox[choice][i];
            }
        }
        output = generateBitBlockFromInt(value);
    }

    if ((int)row == 2)
    {
        for (int i = 32; i < 48; i++)
        {
            if ((i - 32) == (int)column)
            {
                value = SBox[choice][i];
            }

        }
        output = generateBitBlockFromInt(value);
    }

    if ((int)row == 3)
    {
        for(int i = 48; i < 64; i++)
        {
            if ((i - 48) == (int)column)
            {
                value = SBox[choice][i];
            }
        }

        output = generateBitBlockFromInt(value);
    }

    return output;
}

char DES::generateIntFromBitBlock(char *block, int blocksize)
{
    int result=0;

    for(int i=0;i<blocksize;i++)
    {
        result = (2*result+block[i]);
    }

    return result;
}

char* DES::generateBitBlockFromInt(int valueResearchBoxvalue)
{
    char *result = new char[4];

    for (int i = 0; i < 4;i++)
    {
        result[i] = (valueResearchBoxvalue / 8) % 2;
        valueResearchBoxvalue *= 2;
    }

    return result;
}

void DES::displayBitTable(char *table, long tabsize)
{
    for (long i = 0; i < tabsize; i++)
    {
        cout << (int)table[i];

        if (((i+1) % 4) == 0)
        {
            cout << " ";
        }
    }
}

void DES::displayAsHex(char *table, long tabsize)
{
   long hexsize = tabsize / 4;

   char hexcodes[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

   for (long i = 0; i < hexsize; i++)
   {
       long value = 0;

       for (long j = 0; j < 4; j++)
       {
            value = (2 * value) + table[(4 * i) + j];
       }

       cout << hexcodes[value];

        if (((i + 1) % 4) == 0)
        {
            cout << " ";
        }
   }

   cout << endl;
   cout << endl;
}

void DES::initialPermutation()
{
    cout << endl << ">>> Step 1 : Initial message permutation" << endl << endl;
    result1 = permutation(messageBlock, init_perm, 64);
    displayBitTable(result1, 64);
    displayAsHex(result1, 64);
}

void DES::splitPermutatedMessage()
{
    cout<< endl << ">>> Step 2: Splitting permutated message"<<endl <<endl;
    L0 = splitL0(result1);
    R0 = splitR0(result1);

     // L0 status
    cout << "> L0 :";
    displayBitTable(L0, 32);
    cout << endl;
    displayAsHex(L0, 32);

    // R0 status
    cout << "> R0 : ";
    displayBitTable(R0, 32);
    cout << endl;
    displayAsHex(R0, 32);

    // Li+1 and Ri + 1
    L1 = L0;
    R1 = R0;
}

void DES::do16rounds()
{
    // Copy of the SBOX for the SBOX function
    sBoxCopy = new char*[8];

    for (int i = 0; i<8; i++)
    {
        sBoxCopy[i] = new char[64];
    }

    for(int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            sBoxCopy[i][j] = s_boxes[i][j];
        }
    }

    // Step 3 to 7 executed 16 times
    for (int i = 0; i < 16; i++)
    {
        cout << "-> Round " << i+1 << endl;
        expansionRi(i);

        // Step 3.1: subkey generation
        subKeyGeneration(i);

        // Step 4 : XOR operation
        xorOperationSubKeyRi(i);

        // Step 5
        cout << ">>> Step 5 : SBOX operation"<<endl<<endl;
        result5 = sBoxOperation(result4, sBoxCopy, 48);
        cout << "SBOX result : ";
        displayBitTable(result5, 32);
        cout << endl;
        displayAsHex(result5, 32);
        cout << endl;

        // Step 6
        permutationSBoxResult();

        // Step 7
        xorOperationSubKeyLi(i);

        // For the next round, left and right register must be reset
        L1 = R0;
        R0 = R1;

        cout << endl << endl;
    }
}

void DES::expansionRi(int i)
{
    // Step 3: Expansion
    cout<< endl << ">>> Step 3 : R" << i << " expansion" <<endl <<endl;
    result2 = permutation(R1, expansion_table, 48);
    displayBitTable(result2, 48);
    cout << endl;
    displayAsHex(result2, 48);
    cout << endl;
}

void DES::subKeyGeneration(int i)
{
    cout << ">>> Step 3.1 : Subkey generation"<<endl << endl;

    // Splitting encryption key and operation on the 2 subkeys
    leftKey = permutation(mainKey, pc_1_left,32);
    rightKey = permutation(mainKey, pc_1_right,32);

    // Opération de décalage de à droite sur les deux clés obtenues en fonction du round
    leftKey = keyLeftShift(leftKey, keyshift, i);
    rightKey = keyLeftShift(rightKey,keyshift, i);

    //Assemblage des deux sous clés droite et gauche
    key = tableUnion(leftKey, rightKey,56);

    //opération de permutation sur la clé obtenu pour obtenir la subkey
    result3 = permutation(key, pc_2, 48);
    cout << " > Generated subkey : ";
    displayBitTable(result3, 48);
    cout << endl;
    displayAsHex(result3, 48);
    cout << endl;
}

void DES::xorOperationSubKeyRi(int i)
{
    cout << ">>> Step 4 : XOR Operation between R" << i << " after expansion and subkey generation" << endl << endl;
    result4 = xorOperation(result3, result2, 48);
    cout << " > XOR : ";
    displayBitTable(result4, 48);
    cout << endl;
    displayAsHex(result4, 48);
    cout << endl;
    cout << endl;
}

void DES::permutationSBoxResult()
{
    cout<<">>> Step 6 : SBOX result permutation" << endl << endl;
    result5 = permutation(result5, permut_32, 32);
    cout << " -> After permutation : ";
    displayBitTable(result5, 32);
    cout << endl;
    displayAsHex(result5, 32);
    cout << endl;
}

void DES::xorOperationSubKeyLi(int i)
{
    cout<<">>> Step 7 : XOR Operation between SBOX and L" << i << endl << endl;
    R1 = xorOperation(result5, L1, 32);
    cout<<" > XOR : ";
    displayBitTable(R1, 32);
    cout << endl;
    displayAsHex(R1, 32);
    cout << endl;
}

void DES::assemblyL16R16()
{
    cout << ">>> Step 8 : assembly and L16 and R16 " << endl << endl;
    result6 = tableUnion(R1, L1, 64);
    cout << " > L16 + R16 : ";
    displayBitTable(result6, 64);
    cout << endl;
    displayAsHex(result6, 64);
    cout << endl;
}

void DES::finalPermutation()
{
    cout<<">>> Step 9 : final permutation on the assembly " << endl << endl;
    result7 = permutation(result6, reverse_perm, 64);

    cout<<" -> Encrypted 64-bit message block: ";
    displayBitTable(result7, 64);
    cout << endl;
    displayAsHex(result7, 64);
}

void DES::DESEncryption()
{
    //Affichage du message
    cout << ">>> Message block to encrypt: " << endl;
    displayBitTable(messageBlock, 64);
    displayAsHex(messageBlock, 64);

    //Affichage de la clé de chiffrage
    cout << endl <<">>> Encryption Key: "<< endl;
    displayBitTable(mainKey, 64);
    displayAsHex(mainKey, 64);

    system("pause");

    // Step 1
    initialPermutation();

    system("pause");

    // Step 2
    splitPermutatedMessage();

    system("pause");

    // Step 3 - 7
    do16rounds();

    // Step 8
    assemblyL16R16();

    // Step 9
    finalPermutation();
}
