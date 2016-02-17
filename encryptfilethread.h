#ifndef ENCRYPTFILETHREAD_H
#define ENCRYPTFILETHREAD_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include "encryption.h"

class EncryptFileThread : public QThread
{
public:
    EncryptFileThread(QString Password, QString inputFilePath, QString outputFilePath, QString Cipher, bool encrypt);
    void run();

private:
    QString m_password;
    QString m_inputFilePath;
    QString m_outputFilePath;
    QString m_cipher;
    bool m_encrypt;
};

#endif // ENCRYPTFILETHREAD_H
