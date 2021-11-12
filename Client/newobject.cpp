#include "newobject.h"
#include "ui_newobject.h"

NewObject::NewObject(QSqlDatabase *qSqlDatabase, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewObject)
{
    ui->setupUi(this);
    this->setWindowTitle("Новый Объект");
    this->qSqlDatabase = qSqlDatabase;
    seleccObjectId();
}

NewObject::~NewObject()
{
    delete ui;
}

void NewObject::seleccObjectId()
{
    if(!query.exec("select objectsSet.Id_obj from objectsSet"))
        qDebug() << "Error\n";

    QSqlRecord rec = query.record();
    while(query.next())
    {
        this->ui->comboBoxId->addItem(query.value(rec.indexOf("Id_obj")).toString());
    }
}

void NewObject::on_pushButtonAdd_clicked()
{
    QSqlQuery query;
    query.prepare("insert into objectsSet (name_obj) values (:name_obj)");
    query.bindValue(":name_obj", this->ui->lineEdit->text());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}

void NewObject::on_pushButtonChange_clicked()
{
    QSqlQuery query;
    query.prepare("update objectsSet set name_obj=:_name_obj where Id_obj=:_Id_obj");
    query.bindValue(":name_obj", this->ui->lineEdit->text());
    query.bindValue(":_Id_obj", this->ui->comboBoxId->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}

void NewObject::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("delete from objectsSet where Id_obj=:_Id_obj ");
    query.bindValue(":_Id_obj", this->ui->comboBoxId->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}
