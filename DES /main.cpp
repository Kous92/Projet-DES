#include <iostream>
#include "permutations.h"
#include "bit_tables.h"
#include "data_tables.h"
#include "data_messages_examples.h"

using namespace std;

int main()
{

    //Déclaration des variables
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

    //Affichage du message
    cout<<"Message a crypter"<<endl << endl;
    displayBitTable(message_03,64);
    displayAsHex(message_03,64);

    //Affichage de la clé de chiffrage
    cout<< endl <<"Cle de chiffrage"<<endl << endl;
    displayBitTable(mainKey, 64);
    displayAsHex(mainKey,64);

    //Première étape : permutation du message initial
    cout<< endl << "Premiere etape : permutation du message initial"<<endl <<endl;
    result1=permute(message_03,init_perm,64);
    displayBitTable(result1,64);
    displayAsHex(result1,64);

    //Deuxième étape : séparation en deux du message permuté
    cout<< endl << "Deuxieme etape : separation en deux du message permute"<<endl <<endl;
    L0=splitToL0(result1);
    R0=splitToR0(result1);

    // Affichage de LO
    cout<<"L0 :";
    displayBitTable(L0, 32);
    cout << endl;
    displayAsHex(L0,32);

    // Affichage de RO
    cout<<"R0 : ";
    displayBitTable(R0, 32);
    cout << endl;
    displayAsHex(R0,32);

    //Variable li+1 et ri+1
    char *L1 = L0;
    char *R1 = R0;


    //copie de la sBox pour le passage en paramètre de la fonction sBox
    char** copytab = new char*[8];
    for(int i = 0; i<8; i++)
    {
        copytab[i] = new char[64];
    }

    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<64; j++)
        {
            copytab[i][j] = s_boxes[i][j];
        }
    }

    for(int i = 0;i<16;i++)
    {
        cout<<"Round "<<i+1<<endl;
        // Troisième étape : réalisation de l'opération d'expansion sur Ri
        cout<< endl << "Troisième etape : operation d'expansion sur Ri"<<endl <<endl;
        result2=permute(R1, expansion_table, 48);
        displayBitTable(result2, 48);
        cout << endl;
        displayAsHex(result2,48);
        cout << endl;

        //Etape parallèle : génération de la sub key
        cout<<"Etape parallele : generation de la subkey"<<endl << endl;

        //Séparation de la clé de chiffrage et opération sur les deux sous clés
        leftKey = permute(mainKey, pc_1_left,32);
        rightKey = permute(mainKey, pc_1_right,32);


        //Opération de décalage de à droite sur les deux clés obtenues en fonction du round
        leftKey = keyLeftShift(leftKey, keyshift, i);
        rightKey = keyLeftShift(rightKey,keyshift, i);

        //Assemblage des deux sous clés droite et gauche
        key = Union(leftKey, rightKey,56);

        //opération de permutation sur la clé obtenu pour obtenir la subkey
        result3 = permute(key, pc_2, 48);
        cout<<"Subkey : ";
        displayBitTable(result3, 48);
        cout<<endl;
        displayAsHex(result3,48);
        cout<<endl;

        // Quatrieme étape : opération XOr entre Ro après expansion et la subkey
        cout<<"Quatrieme etape : operation Xor entre Ri apres expansion et la subkey"<<endl<<endl;
        result4 = Xor(result3, result2, 48);
        cout<<"Xor : ";
        displayBitTable(result4, 48);
        cout<<endl;
        displayAsHex(result4,48);
        cout<<endl;

        cout<<endl;
        //Cinquieme étape : opération de la sBOX
        cout<<"Cinquieme etape : operation de la sBOX"<<endl<<endl;
        result5 = sBoxOperation(result4, copytab, 48);
        cout<<"Resultat de la sbox : ";
        displayBitTable(result5,32);
        cout<<endl;
        displayAsHex(result5,32);
        cout<<endl;

        //Sixieme étape : permutation sur le resultat de la sBox
        cout<<"Sixieme etape : permutation sur le resultat de la sBox"<<endl<<endl;
        result5 = permute(result5, permut_32, 32);
        cout<<"Apres Permutation : ";
        displayBitTable(result5,32);
        cout<<endl;
        displayAsHex(result5,32);
        cout<<endl;


        //Septieme etape : opération Xor entre la sBox et Li
        cout<<"Septieme etape : operation Xor entre la sBox et Li"<<endl <<endl;
        R1 = Xor(result5,L1, 32);
        cout<<"Xor : ";
        displayBitTable(R1, 32);
        cout<<endl;
        displayAsHex(R1,32);
        cout<<endl;


        //reinitialisation des varialbes pour le prochain round
        L1 = R0;
        R0 = R1;
        cout<<endl<<endl;
    }

    //Huitieme etape : assemblage de L16 et R16
    cout<<"Huitieme etape : assemblage de L16 et R16 "<<endl <<endl;
    result6 = Union(R1, L1, 64);
    cout<<"L16 + R16 : ";
    displayBitTable(result6, 64);
    cout<<endl;
    displayAsHex(result6,64);
    cout<<endl;


    //Neuvieme etape : permutation finale sur l'assemblage
    cout<<"Neuvieme etape : permutation finale sur l'assemblage "<<endl <<endl;
    result7 = permute(result6, reverse_perm, 64);
    cout<<"Message crypte: ";
    displayBitTable(result7, 64);
    cout<<endl;
    displayAsHex(result7,64);
}
