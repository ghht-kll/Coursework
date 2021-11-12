#ifndef NEWSUBJETC_H
#define NEWSUBJETC_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlRecord>
#include <QMessageBox>

namespace Ui {
class NewSubjetc;
}

class NewSubjetc : public QWidget
{
    Q_OBJECT

public:
    explicit NewSubjetc(QSqlDatabase *qSqlDatabase, QWidget *parent = nullptr);
    ~NewSubjetc();

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonChange_clicked();

    void on_pushButton_clicked();

private:
    void selectSubjectId();
private:
    Ui::NewSubjetc *ui;
    QSqlDatabase *qSqlDatabase;
    QSqlQuery query;
};

#endif // NEWSUBJETC_H
