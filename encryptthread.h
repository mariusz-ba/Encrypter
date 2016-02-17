#ifndef ENCRYPTTHREAD_H
#define ENCRYPTTHREAD_H

#include <QObject>
#include <QThread>
#include "encryption.h"

class EncryptThread : public QThread
{
    Q_OBJECT
public:
    EncryptThread(const QString& Password, const QString& Text, const QString& Cipher, bool Encrypt);
    void run();
    QString encryptedText() const;

private:
    QString m_password;
    QString m_text;
    QString m_cipher;
    bool m_encrypt;
    QString m_encryptedText;
};

#endif // ENCRYPTTHREAD_H
