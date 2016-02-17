#include "encryptthread.h"
#include <QDebug>

EncryptThread::EncryptThread(const QString& Password, const QString& Text, const QString& Cipher, bool Encrypt)
    :m_password(Password), m_text(Text), m_cipher(Cipher), m_encrypt(Encrypt)
{
}

void EncryptThread::run()
{
    qDebug() << "Starting thread";
    m_encryptedText = QString::fromStdString(Encryption::encryption(m_password, m_text, m_cipher, m_encrypt));
    qDebug() << "End of thread";
}

QString EncryptThread::encryptedText() const
{
    return m_encryptedText;
}
