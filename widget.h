#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>

#include <QFile>
#include <QTextStream>

#include "encryption.h"
#include "encryptthread.h"
#include "encryptfilethread.h"
#include "aboutdialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    /*
     * Main slots
     */
    void help();                                    //show help information
    void about();                                   //show imformation about app
    void setCurrentPage(QModelIndex);               //sets current window page

    /*
     * Page File_Encrypt slots
     */
    void browseInput();                             //file browser for input_file
    void browseOutput();                            //file browser for output_file
    void browseKey();                               //file browser for key_file
    void checkLines(QString str);                   //check lines in File_encrypt_page. If something is missing disable 'encrypt' button
    void encryptFile();                             //encrypt file in File_encrypt_page.
    void on_radioButton_password_clicked();
    void on_radioButton_file_clicked();
    void fileThreadFinished();

    /*
     * Page Text_Encrypt slots
     */
    void encryptText();                             //encrypt text in Text_encrypt_page.
    void checkTextPageLines();
    void checkTextPageLines(QString);
    void textThreadFinished();

private:
    Ui::Widget *ui;
    QListWidgetItem* menu_text;
    QListWidgetItem* menu_file;

    EncryptThread* textThread;
    EncryptFileThread* fileThread;

    void initializeUi();
};

#endif // WIDGET_H
