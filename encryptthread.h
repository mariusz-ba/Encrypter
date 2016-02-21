#ifndef ENCRYPTTHREAD_H
#define ENCRYPTTHREAD_H

#include <QObject>
#include <QThread>
#include <QFile>
#include "encryption.h"

class EncryptThread : public QThread
{
    Q_OBJECT
public:
    enum DataType{
        TEXT,
        FILE
    };

    EncryptThread(const QString& Password, const QString& Text, const QString& Cipher, bool Encrypt);
    EncryptThread(const QString& Password, const QString& inputFilePath, const QString& outputFilePath, const QString& Cipher, bool encrypt);
    void run();
    QString encryptedText() const;

private:
    QString m_password;
    QString m_text;
    QString m_cipher;
    bool m_encrypt;
    QString m_encryptedText;
    QString m_inputFilePath;
    QString m_outputFilePath;
    DataType type;
};

#endif // ENCRYPTTHREAD_H
