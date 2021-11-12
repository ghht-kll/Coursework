#ifndef NEWOBJECT_H
#define NEWOBJECT_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlRecord>
#include <QMessageBox>

namespace Ui {
class NewObject;
}

class NewObject : public QWidget
{
    Q_OBJECT

public:
    explicit NewObject(QSqlDatabase *qSqlDatabase, QWidget *parent = nullptr);
    ~NewObject();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonChange_clicked();
    void seleccObjectId();
    void on_pushButton_clicked();

private:
    Ui::NewObject *ui;
    QSqlDatabase *qSqlDatabase;
    QSqlQuery query;
};

#endif // NEWOBJECT_H
