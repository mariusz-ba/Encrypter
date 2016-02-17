#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("About Encrypter");
    this->setWindowIcon(QIcon(":/img/icon.png"));

    QFont font = ui->label_3->font();
    font.setPixelSize(14);
    font.setBold(true);
    ui->label_3->setFont(font);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(accept()));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
