#include "encryption.h"

Encryption::Encryption()
{

}

string Encryption::encryption(QString Pass, QString Text, QString Cipher, bool encrypt)
{
    string pass = Pass.toStdString();
    string text = Text.toStdString();
    string CipherText, RecoveredText;

    if(Cipher == "AES")
    {
        byte key[AES::DEFAULT_KEYLENGTH], iv[AES::BLOCKSIZE];
        StringSource(reinterpret_cast<const char*>(pass.c_str()), true, new HashFilter(*(new SHA256), new ArraySink(key, AES::DEFAULT_KEYLENGTH)));
        memset(iv, 0x00, AES::BLOCKSIZE);

        if(encrypt)
        {
            CBC_Mode<AES>::Encryption Encryptor(key, sizeof(key), iv);
            StringSource(text, true, new StreamTransformationFilter(Encryptor, new HexEncoder(new StringSink(CipherText))));
        }
        else
        {
            try
            {
                CBC_Mode<AES>::Decryption Decryptor(key, sizeof(key), iv);
                StringSource(text, true, new HexDecoder(new StreamTransformationFilter(Decryptor, new StringSink(RecoveredText))));
            }
            catch(Exception& e)
            {
                return e.what();
            }
            catch(...)
            {
                return "Unknown error";
            }
        }
    }

    if(encrypt)
        return CipherText;
    return RecoveredText;
}

