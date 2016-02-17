#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>
#include <string>

#include <modes.h>
#include <aes.h>
#include <filters.h>
#include <sha.h>
#include <hex.h>


using namespace std;
using namespace CryptoPP;

class Encryption
{
public:
    Encryption();
    static string encryption(QString Pass, QString Text, QString Cipher, bool encrypt);
};

#endif // ENCRYPTION_H
