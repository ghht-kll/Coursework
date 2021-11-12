#include "newdocument.h"
#include "ui_newdocument.h"

NewDocument::NewDocument(QSqlDatabase *qSqlDatabase, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewDocument)
{
    ui->setupUi(this);
    this->setWindowTitle("Новый Документ");
    this->qSqlDatabase = qSqlDatabase;

    selectContractId();
    selectDocumentId();
}

NewDocument::~NewDocument()
{
    delete ui;
}

void NewDocument::selectContractId()
{
    if(!query.exec("select contractsSet.id_contract from contractsSet"))
        qDebug() << "Error\n";

    QSqlRecord rec = query.record();
    while(query.next())
    {
        this->ui->comboBoxIdContract->addItem(query.value(rec.indexOf("id_contract")).toString());
    }
}

void NewDocument::selectDocumentId()
{
    if(!query.exec("select documentsSet.Id_doc from documentsSet"))
        qDebug() << "Error\n";

    QSqlRecord rec = query.record();
    while(query.next())
    {
        this->ui->comboBoxId->addItem(query.value(rec.indexOf("Id_doc")).toString());
    }
}

void NewDocument::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("insert into documentsSet (name_doc, address_doc, contracts_id_contract) values"
                  " (:name_doc, :address_doc, :contracts_id_contract)");

    query.bindValue(":name_doc", this->ui->lineEditNameDoc->text());
    query.bindValue(":address_doc", this->ui->lineEditAddressDoc->text());
    query.bindValue(":contracts_id_contract", this->ui->comboBoxIdContract->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}

void NewDocument::on_pushButton_2_clicked()
{
    QSqlQuery query;
    query.prepare("update documentsSet set name_doc=:_name_doc, address_doc=:_address_doc,"
                  " contracts_id_contract=:_contracts_id_contract "
                  "where Id_doc=:_Id_doc");

    query.bindValue(":_name_doc", this->ui->lineEditNameDoc->text());
    query.bindValue(":_address_doc", this->ui->lineEditAddressDoc->text());
    query.bindValue(":_contracts_id_contract", this->ui->comboBoxIdContract->currentText().toInt());
    query.bindValue(":_Id_doc", this->ui->comboBoxId->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}

void NewDocument::on_pushButton_3_clicked()
{
    QSqlQuery query;
    query.prepare("delete from documentsSet where Id_doc=:_Id_doc ");
    query.bindValue(":_Id_doc", this->ui->comboBoxId->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}
