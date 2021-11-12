#ifndef NEWDOCUMENT_H
#define NEWDOCUMENT_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlRecord>
#include <QMessageBox>

namespace Ui {
class NewDocument;
}

class NewDocument : public QWidget
{
    Q_OBJECT

public:
    explicit NewDocument(QSqlDatabase *qSqlDatabase, QWidget *parent = nullptr);
    ~NewDocument();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void selectContractId();
    void selectDocumentId();
private:

    Ui::NewDocument *ui;
    QSqlDatabase *qSqlDatabase;
    QSqlQuery query;
};

#endif // NEWDOCUMENT_H
