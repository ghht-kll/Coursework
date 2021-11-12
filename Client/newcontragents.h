#ifndef NEWCONTRAGENTS_H
#define NEWCONTRAGENTS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlRecord>
#include <QMap>
#include <exception>
#include <QMessageBox>

namespace Ui {
class NewContrAgents;
}

class NewContrAgents : public QWidget
{
    Q_OBJECT

public:
    explicit NewContrAgents(QSqlDatabase *qSqlDatabase, QWidget *parent = nullptr);
    ~NewContrAgents();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void addNewContragent();
    void updateContragent();
    void selectContrAgentsId();

private:
    Ui::NewContrAgents *ui;
    QSqlDatabase *qSqlDatabase;
    QSqlQuery query;
};

#endif // NEWCONTRAGENTS_H
