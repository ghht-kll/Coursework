#ifndef NEWNOTE_H
#define NEWNOTE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlRecord>
#include <QMessageBox>

namespace Ui {
class NewNote;
}

class NewNote : public QWidget
{
    Q_OBJECT

public:
    explicit NewNote(QSqlDatabase *qSqlDatabase, QWidget *parent = nullptr);
    ~NewNote();

private slots:
    void on_pushButtonAdd_clicked();
    void selectNoteId();
    void selectContractId();

    void on_pushButtonChange_clicked();

    void on_pushButton_clicked();

private:
    Ui::NewNote *ui;
    QSqlDatabase *qSqlDatabase;
    QSqlQuery query;
};

#endif // NEWNOTE_H
