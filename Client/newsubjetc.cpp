#include "newsubjetc.h"
#include "ui_newsubjetc.h"

NewSubjetc::NewSubjetc(QSqlDatabase *qSqlDatabase, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewSubjetc)
{
    ui->setupUi(this);
    this->setWindowTitle("Новый Субъект");
    this->qSqlDatabase = qSqlDatabase;
    selectSubjectId();
}

NewSubjetc::~NewSubjetc()
{
    delete ui;
}

void NewSubjetc::selectSubjectId()
{
    if(!query.exec("select subjectsSet.Id_subj from subjectsSet"))
        qDebug() << "Error\n";

    QSqlRecord rec = query.record();
    while(query.next())
    {
        this->ui->comboBoxId->addItem(query.value(rec.indexOf("Id_subj")).toString());
    }
}

void NewSubjetc::on_pushButtonAdd_clicked()
{
    QSqlQuery query;
    query.prepare("insert into subjectsSet (name_obj) values (:name_obj)");
    query.bindValue(":name_obj", this->ui->lineEditName->text());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}

void NewSubjetc::on_pushButtonChange_clicked()
{
    QSqlQuery query;
    query.prepare("update subjectsSet set name_obj=:_name_obj where Id_subj=:_Id_subj");
    query.bindValue(":name_obj", this->ui->lineEditName->text());
    query.bindValue(":_Id_subj", this->ui->comboBoxId->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}

void NewSubjetc::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("delete from subjectsSet where Id_subj=:_Id_subj");
    query.bindValue(":_Id_subj", this->ui->comboBoxId->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}
