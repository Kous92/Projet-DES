#include "permutations.h"
#include "math.h"
#include <iostream>
using namespace std;


char* permute(char *table, char *perm_table, long tabsize)
{
    char *result = new char[tabsize];

    for(int i=0; i <tabsize;i++)
    {
        result[i]=table[(int)perm_table[i]-1];
    }

    return result;
}

/// Fonctions de séparation du message initial de 64 bits en deux blocks de 32 bits
char* splitToL0(char *tab)
{
    char *L0 = new char[32];

    for(int i = 0; i<32; i++)
    {
        L0[i] = tab[i];
    }
    return L0;
}

char* splitToR0(char *tab)
{
    char *R0 = new char[32];

    for(int i = 32; i<64; i++)
    {
        R0[i-32] = tab[i];
    }
    return R0;
}

/// Fonction de décalage de bit vers la gauche en fonction du round
char* keyLeftShift(char *tab, char *keyshift, int shift)
{
    char *table = new char[28];
    for(int i = 0; i<28; i++)
    {
        table[i] = tab[(i+(int)keyshift[shift])%28];
    }
    return table;
}

/// Fonction qui unit deux blocks
char* Union(char *tab1, char *tab2, int length)
{
    char *tab = new char[length];

    for(int i = 0; i<(length/2); i++)
    {
        tab[i] = tab1[i];
    }
    for(int i = (length/2); i<length; i++)
    {
        tab[i] = tab2[i-(length/2)];
    }

    return tab;
}

/// Fonction de l'opération Xor (parité)
char* Xor(char* tab1, char* tab2, int length)
{
    char* tab = new char[length];
    for(int i = 0; i<length;i++)
    {
        if(tab1[i] == tab2[i])
            tab[i] = 0;
        else
            tab[i] = 1;
    }
    return tab;
}

char generateIntFromBitBlock(char *block, int blocksize)
{
    int result=0;

    for(int i=0;i<blocksize;i++)
    {
        result = (2*result+block[i]);
    }

    return result;
}

char *generateBitBlockFromInt(int valueResearchBoxvalue)
{
    char *result = new char[4];

    for (int i=0;i<4;i++)
    {
        result[i]=(valueResearchBoxvalue/8)%2;
        valueResearchBoxvalue *=2;
    }

    return result;
}

/// Fonction de recherche de valeur dans la sBox
char* valueResearchBox(char **sBox, char *output, char row, char column, int choice)
{
    char value;

    // Choix de la ligne
    if ((int)row == 0)
    {
        // Parcours des colonnes
        for(int i = 0; i < 16; i++)
        {
            // Si la colonne passée en paramètre correspond à la colonne de la boucle on récupère la valeur dans la bonne sous sBox
            if (i == (int)column)

                // récupération de la valeur dans la sous sBox
                value = sBox[choice][i];
        }
        // on retourne la valeur sous la forme d'un block de 4 bits
        output = generateBitBlockFromInt(value);
    }

    if ((int)row == 1)
    {
        for(int i = 16; i < 32; i++)
        {
            if (i-16 == (int)column)
            {
                value = sBox[choice][i];
            }
        }
        output = generateBitBlockFromInt(value);
    }

    if ((int)row == 2)
    {
        for(int i = 32; i < 48; i++)
        {
            if (i -32 == (int)column)
            {
                value = sBox[choice][i];
            }

        }
        output = generateBitBlockFromInt(value);
    }
    if ((int)row == 3)
    {
        for(int i = 48; i < 64;i++)
        {
            if (i-48 == (int)column)
                value = sBox[choice][i];
        }
        output = generateBitBlockFromInt(value);
    }
    return output;
}

/// Fonction de la sBox
char* sBoxOperation(char *tabXor, char **sBox, int length)
{
    char* rowBox = new char[2];
    char* columnBox = new char[4];

    /// Output
    char* output1 = new char[4]; //output sBox 4 bits
    char* output2 = new char[4];
    char* output3 = new char[4];
    char* output4 = new char[4];
    char* output5 = new char[4];
    char* output6 = new char[4];
    char* output7 = new char[4];
    char* output8 = new char[4];

    // Découpage du résultat de l'opération Xor en 8 blocks de 6 bits

    /// Block 1
    // premier et dernier bits de chaque block permet de déterminer la ligne de la sBox
    rowBox[0] = tabXor[0];
    rowBox[1] = tabXor[5];

    // les 4 bits du milieu permettent de déterminer la colonne de la sbox
    columnBox[0] = tabXor[1];
    columnBox[1] = tabXor[2];
    columnBox[2] = tabXor[3];
    columnBox[3] = tabXor[4];

    // Récuperation du premier block de 4 bits
    output1 = valueResearchBox(sBox, output1, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 0);

    /// Block 2
    rowBox[0] = tabXor[6];
    rowBox[1] = tabXor[11];

    columnBox[0] = tabXor[7];
    columnBox[1] = tabXor[8];
    columnBox[2] = tabXor[9];
    columnBox[3] = tabXor[10];

    output2 = valueResearchBox(sBox, output2, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 1);

    /// Block 3
    rowBox[0] = tabXor[12];
    rowBox[1] = tabXor[17];

    columnBox[0] = tabXor[13];
    columnBox[1] = tabXor[14];
    columnBox[2] = tabXor[15];
    columnBox[3] = tabXor[16];

    output3 = valueResearchBox(sBox, output3, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 2);

    /// Block 4
    rowBox[0] = tabXor[18];
    rowBox[1] = tabXor[23];

    columnBox[0] = tabXor[19];
    columnBox[1] = tabXor[20];
    columnBox[2] = tabXor[21];
    columnBox[3] = tabXor[22];

    output4 = valueResearchBox(sBox, output4, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 3);

    /// Block 5
    rowBox[0] = tabXor[24];
    rowBox[1] = tabXor[29];

    columnBox[0] = tabXor[25];
    columnBox[1] = tabXor[26];
    columnBox[2] = tabXor[27];
    columnBox[3] = tabXor[28];

    output5 = valueResearchBox(sBox, output5, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 4);

    /// Block 6
    rowBox[0] = tabXor[30];
    rowBox[1] = tabXor[35];

    columnBox[0] = tabXor[31];
    columnBox[1] = tabXor[32];
    columnBox[2] = tabXor[33];
    columnBox[3] = tabXor[34];

    output6 = valueResearchBox(sBox, output6, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 5);

    /// Block 7
    rowBox[0] = tabXor[36];
    rowBox[1] = tabXor[41];

    columnBox[0] = tabXor[37];
    columnBox[1] = tabXor[38];
    columnBox[2] = tabXor[39];
    columnBox[3] = tabXor[40];

    output7 = valueResearchBox(sBox, output7, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 6);

    /// Block 8
    rowBox[0] = tabXor[42];
    rowBox[1] = tabXor[47];

    columnBox[0] = tabXor[43];
    columnBox[1] = tabXor[44];
    columnBox[2] = tabXor[45];
    columnBox[3] = tabXor[46];

    output8 = valueResearchBox(sBox, output8, generateIntFromBitBlock(rowBox, 2), generateIntFromBitBlock(columnBox,4), 7);

    /// Block final -> assemblage des 8 blocks de 4 bits
    char* outputBox = new char[32];

    for(int i = 0; i<32;i++)
    {
        if( 0 <= i && i < 4)
            outputBox[i] = output1[i];
        else if(4 <= i && i < 8)
            outputBox[i] = output2[i-4];
        else if(8 <= i && i < 12)
            outputBox[i] = output3[i-8];
        else if(12 <= i && i < 16)
            outputBox[i] = output4[i-12];
        else if(16 <= i && i < 20)
            outputBox[i] = output5[i-16];
        else if(20 <= i && i < 24)
            outputBox[i] = output6[i-20];
        else if(24 <= i && i < 28)
            outputBox[i] = output7[i-24];
        else if(28 <= i && i < 32)
            outputBox[i] = output8[i-28];
    }

    return outputBox;
}



