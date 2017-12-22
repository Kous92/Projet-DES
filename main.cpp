#include <iostream>
#include "DES.h"
#include "data_messages_examples.h"

using namespace std;

int main()
{
    cout << "-> DES ENCRYPTION" << endl << endl;

    DES des(message_02);
    des.DESEncryption();

    return 0;
}
