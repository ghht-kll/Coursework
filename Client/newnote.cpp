#include "newnote.h"
#include "ui_newnote.h"

NewNote::NewNote(QSqlDatabase *qSqlDatabase, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewNote)
{
    ui->setupUi(this);
    this->setWindowTitle("Новая запись");
    this->qSqlDatabase = qSqlDatabase;
    selectContractId();
    selectNoteId();
}

NewNote::~NewNote()
{
    delete ui;
}

void NewNote::selectContractId()
{
    if(!query.exec("select contractsSet.id_contract from contractsSet"))
        qDebug() << "Error\n";

    QSqlRecord rec = query.record();
    while(query.next())
    {
        this->ui->comboBoxIdContract->addItem(query.value(rec.indexOf("id_contract")).toString());
    }
}

void NewNote::selectNoteId()
{
    if(!query.exec("select notesSet.Id_note from notesSet"))
        qDebug() << "Error\n";

    QSqlRecord rec = query.record();
    while(query.next())
    {
        this->ui->comboBoxId->addItem(query.value(rec.indexOf("Id_note")).toString());
    }
}

void NewNote::on_pushButtonAdd_clicked()
{
    QSqlQuery query;
    query.prepare("insert into notesSet (note, contracts_id_contract) values (:note, :contracts_id_contract)");
    query.bindValue(":note", this->ui->lineEditNote->text());
    query.bindValue(":contracts_id_contract", this->ui->comboBoxIdContract->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}

void NewNote::on_pushButtonChange_clicked()
{
    QSqlQuery query;
    query.prepare("update notesSet set note=:_note, contracts_id_contract=:_contracts_id_contract"
                  " where Id_note=:_Id_note");
    query.bindValue(":_note", this->ui->lineEditNote->text());
    query.bindValue(":_contracts_id_contract", this->ui->comboBoxIdContract->currentText().toInt());
    query.bindValue(":_Id_note", this->ui->comboBoxId->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}

void NewNote::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("delete from notesSet where Id_note=:_Id_note ");
    query.bindValue(":_Id_note", this->ui->comboBoxId->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}
