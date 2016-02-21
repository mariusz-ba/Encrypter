#include "encryptthread.h"
#include <QDebug>

EncryptThread::EncryptThread(const QString& Password, const QString& Text, const QString& Cipher, bool Encrypt)
    :m_password(Password), m_text(Text), m_cipher(Cipher), m_encrypt(Encrypt), type(TEXT)
{
}

EncryptThread::EncryptThread(const QString& Password, const QString& inputFilePath, const QString& outputFilePath, const QString& Cipher, bool encrypt)
    : m_password(Password), m_inputFilePath(inputFilePath), m_outputFilePath(outputFilePath), m_cipher(Cipher), m_encrypt(encrypt), type(FILE)
{
}

void EncryptThread::run()
{
    if(type == TEXT)
    {
        qDebug() << "Starting thread";
        m_encryptedText = QString::fromStdString(Encryption::encryption(m_password, m_text, m_cipher, m_encrypt));
        qDebug() << "End of thread";
    }
    else
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

}

QString EncryptThread::encryptedText() const
{
    return m_encryptedText;
}
