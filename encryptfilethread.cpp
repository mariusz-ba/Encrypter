#include "encryptfilethread.h"
#include <QDebug>

EncryptFileThread::EncryptFileThread(QString Password, QString inputFilePath, QString outputFilePath, QString Cipher, bool encrypt)
    : m_password(Password), m_inputFilePath(inputFilePath), m_outputFilePath(outputFilePath), m_cipher(Cipher), m_encrypt(encrypt)
{
}

void EncryptFileThread::run()
{
    QFile inputFile(m_inputFilePath);
    if(!inputFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Invalid input file.";
        return;
    }

    QFile outputFile(m_outputFilePath);
    if(!outputFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Invalid output file.";
        return;
    }

    QTextStream in(&inputFile);
    QTextStream out(&outputFile);

    while(!in.atEnd())
    {
        QString text = in.readLine();
        QString encryptedText = QString::fromStdString(Encryption::encryption(m_password, text, m_cipher, m_encrypt));
        out <<  encryptedText << "\n";
    }

    outputFile.flush();
    inputFile.close();
    outputFile.close();
}

