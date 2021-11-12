#ifndef NEWTREATY_H
#define NEWTREATY_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlRecord>
#include <QMap>
#include <QMessageBox>

namespace Ui {
class NewTreaty;
}

class NewTreaty : public QWidget
{
    Q_OBJECT

public:
    explicit NewTreaty(QSqlDatabase *qSqlDatabase, QWidget *parent = nullptr);
    ~NewTreaty();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void selectContragentsIdContr();
    void selectObjectsIdObj();
    void selectSubjectsIdSubj();
    void selectCurrencyContract();
    void selectTreatyId();

    int getKeyFromMap(QMap<int, QString> &map, QString value);
private:
    Ui::NewTreaty *ui;
    QSqlDatabase *qSqlDatabase;
    QSqlQuery query;
    QMap<int,QString> contragentsIdContr;
    QMap<int,QString> objectsIdObj;
    QMap<int,QString> subjectsIdSubj;
};

#endif // NEWTREATY_H
