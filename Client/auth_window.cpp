#include "auth_window.h"
#include "ui_auth_window.h"

Auth_window::Auth_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Auth_window)
{
    ui->setupUi(this);
    this->setWindowTitle("Авторизация");
}

Auth_window::~Auth_window()
{
    delete ui;
}

std::tuple<QString, QString> Auth_window::getUserData()
{
    return std::make_tuple(this->ui->lineEditLogin->text(), this->ui->lineEditPassword->text());
}

void Auth_window::on_pushButtonAuth_clicked()
{
    emit login_button_clicked();
}
