#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H

#include <QWidget>
#include <tuple>
#include <QMessageBox>
namespace Ui {
class Auth_window;
}

class Auth_window : public QWidget
{
    Q_OBJECT

public:
    explicit Auth_window(QWidget *parent = nullptr);
    std::tuple<QString, QString> getUserData();
    ~Auth_window();
signals:
    void login_button_clicked();

private slots:
    void on_pushButtonAuth_clicked();

private:
    Ui::Auth_window *ui;
};

#endif // AUTH_WINDOW_H
