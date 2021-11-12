#include "newcontragents.h"
#include "ui_newcontragents.h"

NewContrAgents::NewContrAgents(QSqlDatabase *qSqlDatabase, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewContrAgents)
{
    ui->setupUi(this);
    this->setWindowTitle("Новый Агент/Контрагент");
    this->qSqlDatabase = qSqlDatabase;
    selectContrAgentsId();
}

void NewContrAgents::selectContrAgentsId()
{
    if(!query.exec("select contrAgentsSet.Id_contr from contrAgentsSet"))
        qDebug() << "Error\n";

    QSqlRecord rec = query.record();
    while(query.next())
    {
        this->ui->comboBoxId->addItem(query.value(rec.indexOf("Id_contr")).toString());
    }
}

NewContrAgents::~NewContrAgents()
{
    delete ui;
}

void NewContrAgents::on_pushButton_clicked()
{
    QSqlQuery query;
    if(this->ui->radioButtonUr->isChecked())
    {
        query.prepare("insert into contrAgentsSet (type_contr, compname_contr, itn_contr, msrn_contr,"
                      " document_contr, bic_contr, chaccount_contr, address_contr, phnumber_contr)"
                      " values (:type_contr, :compname_contr, :itn_contr, :msrn_contr, :document_contr,"
                      " :bic_contr, :chaccount_contr, :address_contr, :phnumber_contr)");
        query.bindValue(":type_contr", 0);
        query.bindValue(":compname_contr", this->ui->lineEditContr->text());
    }
    else if(this->ui->radioButtonFi->isChecked())
    {
        query.prepare("insert into contrAgentsSet (type_contr, fullname_contr, itn_contr, msrn_contr,"
                      " document_contr, bic_contr, chaccount_contr,address_contr, phnumber_contr)"
                      " values (:type_contr, :fullname_contr, :itn_contr, :msrn_contr, :document_contr,"
                      " :bic_contr, :chaccount_contr, :address_contr, :phnumber_contr)");
        query.bindValue(":fullname_contr", this->ui->lineEditContr->text());
        query.bindValue(":type_contr", 1);
    }
    else return;
    query.bindValue(":itn_contr", this->ui->lineEditInn->text());
    query.bindValue(":msrn_contr", this->ui->lineEditMcrn->text());
    query.bindValue(":document_contr", this->ui->lineEditDoc->text());
    query.bindValue(":bic_contr", this->ui->lineEditBik->text());
    query.bindValue(":chaccount_contr", this->ui->lineEditRS->text());
    query.bindValue(":address_contr", this->ui->lineEditAd->text());
    query.bindValue(":phnumber_contr", this->ui->lineEditTel->text());

    if(!query.exec())
        qDebug() << "Error" << "\n";
}

void NewContrAgents::on_pushButton_2_clicked()
{
    QSqlQuery query;
    if(this->ui->radioButtonUr->isChecked())
    {
        query.prepare("update contrAgentsSet set type_contr=:_type_contr, compname_contr:=_compname_contr, itn_contr:=_itn_contr,"
                      " msrn_contr:=_msrn_contr, document_contr:=_document_contr, bic_contr:=_bic_contr, chaccount_contr:=_chaccount_contr"
                      " address_contr:=_address_contr, address_contr:=_address_contr, phnumber_contr:=_phnumber_contr"
                      " where id_contract=:_id_contract");

        query.bindValue(":_type_contr", 0);
        query.bindValue(":_compname_contr", this->ui->lineEditContr->text());
    }
    else if(this->ui->radioButtonFi->isChecked())
    {
        query.prepare("update contrAgentsSet set type_contr=:_type_contr, fullname_contr:=_fullname_contr, itn_contr:=_itn_contr,"
                      " msrn_contr:=_msrn_contr, document_contr:=_document_contr, bic_contr:=_bic_contr, chaccount_contr:=_chaccount_contr"
                      " address_contr:=_address_contr, address_contr:=_address_contr, phnumber_contr:=_phnumber_contr"
                      " where id_contract=:_id_contract");

        query.bindValue(":_fullname_contr", this->ui->lineEditContr->text());
        query.bindValue(":_type_contr", 1);
    }
    else return;
    query.bindValue(":_itn_contr", this->ui->lineEditInn->text());
    query.bindValue(":_msrn_contr", this->ui->lineEditMcrn->text());
    query.bindValue(":_document_contr", this->ui->lineEditDoc->text());
    query.bindValue(":_bic_contr", this->ui->lineEditBik->text());
    query.bindValue(":_chaccount_contr", this->ui->lineEditRS->text());
    query.bindValue(":_address_contr", this->ui->lineEditAd->text());
    query.bindValue(":_phnumber_contr", this->ui->lineEditTel->text());
    query.bindValue(":_id_contract", this->ui->comboBoxId->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
}

void NewContrAgents::on_pushButton_3_clicked()
{
    QSqlQuery query;
    query.prepare("delete from contrAgentsSet where id_contract=:_id_contract ");
    query.bindValue(":_id_contract", this->ui->comboBoxId->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}
