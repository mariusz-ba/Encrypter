#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initializeUi();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initializeUi()
{
    // SETUP MAIN WINDOW
    this->setWindowTitle("Encrypter");
    this->setWindowIcon(QIcon(":/img/icon.png"));

    menu_text = new QListWidgetItem(QIcon(":/img/encrypt.png"), tr("Encrypt text"));
    menu_file = new QListWidgetItem(QIcon(":/img/Lock.png"), tr("Encrypt file"));

    ui->listWidget->addItem(menu_text);
    ui->listWidget->addItem(menu_file);
    ui->listWidget->setIconSize(QSize(36,36));

    connect(ui->listWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(setCurrentPage(QModelIndex)));
    connect(ui->pushButton_help, SIGNAL(clicked()), this, SLOT(help()));
    connect(ui->pushButton_about, SIGNAL(clicked()), this, SLOT(about()));

    // SETUP FILE ENCRYPT PAGE

    connect(ui->pushButton_browseInput, SIGNAL(clicked()), this, SLOT(browseInput()));
    connect(ui->pushButton_browseOutput, SIGNAL(clicked()), this, SLOT(browseOutput()));
    connect(ui->pushButton_browseKey, SIGNAL(clicked()), this, SLOT(browseKey()));
    connect(ui->pushButton_encrypt, SIGNAL(clicked()), this, SLOT(encryptFile()));

    connect(ui->lineEdit_input, SIGNAL(textChanged(QString)), this, SLOT(checkLines(QString)));
    connect(ui->lineEdit_output, SIGNAL(textChanged(QString)), this, SLOT(checkLines(QString)));
    connect(ui->lineEdit_keyfile, SIGNAL(textChanged(QString)), this, SLOT(checkLines(QString)));
    connect(ui->lineEdit_password, SIGNAL(textChanged(QString)), this, SLOT(checkLines(QString)));
    connect(ui->lineEdit_verify, SIGNAL(textChanged(QString)), this, SLOT(checkLines(QString)));

    ui->pushButton_encrypt->setEnabled(false);

    //Setup TEXT PAGE
    connect(ui->textPageEncryptButton, SIGNAL(clicked()), this, SLOT(encryptText()));
    connect(ui->textPageInput, SIGNAL(textChanged()), this, SLOT(checkTextPageLines()));
    connect(ui->textPagePassword, SIGNAL(textChanged(QString)), this, SLOT(checkTextPageLines(QString)));

    ui->textPageEncryptButton->setEnabled(false);
}

// MAIN WINDOW SLOTS

void Widget::help()
{
    //show help dialog
}

void Widget::about()
{
    //show about dialog
    AboutDialog dl(this);
    dl.setFixedSize(dl.size());
    dl.exec();
}

void Widget::setCurrentPage(QModelIndex index)
{
    ui->menuPageWidget->setCurrentIndex(index.row());
}

// FILE ENCRYPT PAGE SLOTS

void Widget::on_radioButton_password_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->lineEdit_keyfile->clear();
}

void Widget::on_radioButton_file_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_password->clear();
    ui->lineEdit_verify->clear();
}

void Widget::browseInput()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Chose file to encrypt", QDir::homePath());
    ui->lineEdit_input->setText(filePath);
}

void Widget::browseOutput()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Chose output file", QDir::homePath());
    ui->lineEdit_output->setText(filePath);
}

void Widget::browseKey()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Chose key file", QDir::homePath());
    ui->lineEdit_keyfile->setText(filePath);
}

void Widget::encryptFile()
{
    // encrypt/decrypt file and save output file.

    bool enc_dec = ui->radioButton_encrypt->isChecked();
    QString password;

    if(ui->radioButton_password->isChecked())
    {
        password = ui->lineEdit_password->text();
    }
    else
    {
        {
            QFile fileOpen(ui->lineEdit_keyfile->text());
            if(!fileOpen.open(QFile::ReadOnly | QFile::Text))
                return;

            QTextStream in(&fileOpen);
            password = in.readAll();
        }
    }

    thread = new EncryptThread(password, ui->lineEdit_input->text(), ui->lineEdit_output->text(), "AES", enc_dec);
    connect(thread, SIGNAL(finished()), this, SLOT(fileThreadFinished()));

    ui->lineEdit_output->setEnabled(false);
    ui->lineEdit_input->setEnabled(false);
    ui->pushButton_encrypt->setEnabled(false);

    thread->start();
}

void Widget::fileThreadFinished()
{
    ui->lineEdit_output->setEnabled(true);
    ui->lineEdit_input->setEnabled(true);
    ui->pushButton_encrypt->setEnabled(true);
    delete thread;
}

void Widget::checkLines(QString str)
{
    if(ui->lineEdit_input->text().isEmpty() || ui->lineEdit_output->text().isEmpty()) {
        ui->pushButton_encrypt->setEnabled(false);
        return;
    }

    if(ui->radioButton_file->isChecked()) {
        if(ui->lineEdit_keyfile->text().isEmpty()) {
            ui->pushButton_encrypt->setEnabled(false);
            return;
        }
    }

    if(ui->radioButton_password->isChecked()) {
        if(ui->lineEdit_password->text().isEmpty() || ui->lineEdit_verify->text().isEmpty() ||
                ui->lineEdit_password->text() != ui->lineEdit_verify->text())
        {
            ui->pushButton_encrypt->setEnabled(false);
            return;
        }
    }

    ui->pushButton_encrypt->setEnabled(true);
}

// TEXT ENCRYPT SLOTS

void Widget::encryptText()
{
    bool enc_dec = ui->textPageRadioEncrypt->isChecked();
    thread = new EncryptThread(ui->textPagePassword->text(), ui->textPageInput->toPlainText(), "AES", enc_dec);
    connect(thread, SIGNAL(finished()), this, SLOT(textThreadFinished()));
    thread->start();
    ui->textPageEncryptButton->setEnabled(false);
}

void Widget::checkTextPageLines()
{
    if(ui->textPageInput->toPlainText().isEmpty() || ui->textPagePassword->text().isEmpty())
        ui->textPageEncryptButton->setEnabled(false);
    else
        ui->textPageEncryptButton->setEnabled(true);
}

void Widget::checkTextPageLines(QString)
{
    if(ui->textPageInput->toPlainText().isEmpty() || ui->textPagePassword->text().isEmpty())
        ui->textPageEncryptButton->setEnabled(false);
    else
        ui->textPageEncryptButton->setEnabled(true);
}

void Widget::textThreadFinished()
{
    ui->textPageOutput->setText(thread->encryptedText());
    ui->textPageEncryptButton->setEnabled(true);
    delete thread;
}
