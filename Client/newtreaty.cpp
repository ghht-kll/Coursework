#include "newtreaty.h"
#include "ui_newtreaty.h"

NewTreaty::NewTreaty(QSqlDatabase *qSqlDatabase, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewTreaty)
{
    ui->setupUi(this);
    this->setWindowTitle("Новый договор");
    this->qSqlDatabase = qSqlDatabase;

    selectCurrencyContract();
    selectContragentsIdContr();
    selectObjectsIdObj();
    selectSubjectsIdSubj();
    selectTreatyId();
}

void NewTreaty::selectCurrencyContract()
{
    if(!query.exec("select distinct currency_contract from contractsSet "))
        qDebug() << "Error\n";

    QSqlRecord rec = query.record();
    while(query.next())
    {
        this->ui->comboBoxCurrencyContract->addItem(query.value(rec.indexOf("currency_contract")).toString());
    }
}

void NewTreaty::selectContragentsIdContr()
{
    if(!query.exec("select contrAgentsSet.Id_contr, concat(contrAgentsSet.compname_contr,"
                   " contrAgentsSet.fullname_contr)"
                   " as ContrAgents from contrAgentsSet"))
        qDebug() << "Error\n";

    QSqlRecord rec = query.record();
    while(query.next())
    {
        this->contragentsIdContr.insert(query.value(rec.indexOf("Id_contr")).toInt(), query.value(rec.indexOf("ContrAgents")).toString());
        this->ui->comboBoxContragentsIdContr->addItem(query.value(rec.indexOf("ContrAgents")).toString());
    }
}

void NewTreaty::selectObjectsIdObj()
{
    if(!query.exec("select * from objectsSet"))
        qDebug() << "Error\n";

    QSqlRecord rec = query.record();
    while(query.next())
    {
        this->objectsIdObj.insert(query.value(rec.indexOf("Id_obj")).toInt(), query.value(rec.indexOf("name_obj")).toString());
        this->ui->comboBoxObjectsIdObj->addItem(query.value(rec.indexOf("name_obj")).toString());
    }
}

void NewTreaty::selectSubjectsIdSubj()
{
    if(!query.exec("select * from subjectsSet"))
        qDebug() << "Error\n";

    QSqlRecord rec = query.record();
    while(query.next())
    {
        this->subjectsIdSubj.insert(query.value(rec.indexOf("Id_subj")).toInt(), query.value(rec.indexOf("name_obj")).toString());
        this->ui->comboBoxSubjectsIdSubj->addItem(query.value(rec.indexOf("name_obj")).toString());
    }
}

void NewTreaty::selectTreatyId()
{
    if(!query.exec("select id_contract from contractsSet"))
        qDebug() << "Error\n";

    QSqlRecord rec = query.record();
    while(query.next())
    {
        this->ui->comboBoxId->addItem(query.value(rec.indexOf("id_contract")).toString());
    }
}

int NewTreaty::getKeyFromMap(QMap<int, QString> &map, QString value)
{
    for(QMap<int,QString>::Iterator it = map.begin(); it != map.end(); it++)
    {
        if(it.value() == value)
            return it.key();
    }
    return -1;
}

NewTreaty::~NewTreaty()
{
    delete ui;
}

void NewTreaty::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("insert into contractsSet (time_contract, date_contract, currency_contract, contragents_Id_contr, "
                  " subjects_Id_subj, objects_Id_obj ) values (:time_contract, :date_contract, :currency_contract, :contragents_Id_contr"
                  " ,:subjects_Id_subj, :objects_Id_obj)");
    query.bindValue(":time_contract",this->ui->dateEdit->date().toString((Qt::ISODate)));
    query.bindValue(":date_contract",this->ui->dateEdit_2->date().toString((Qt::ISODate)));
    query.bindValue(":currency_contract",this->ui->comboBoxCurrencyContract->currentText());
    query.bindValue(":contragents_Id_contr",this->getKeyFromMap(this->contragentsIdContr, this->ui->comboBoxContragentsIdContr->currentText()));
    query.bindValue(":subjects_Id_subj",this->getKeyFromMap(this->subjectsIdSubj, this->ui->comboBoxSubjectsIdSubj->currentText()));
    query.bindValue(":objects_Id_obj",this->getKeyFromMap(this->objectsIdObj, this->ui->comboBoxObjectsIdObj->currentText()));

    if(!query.exec())
        qDebug() << "Error" << "\n";

}

void NewTreaty::on_pushButton_2_clicked()
{
    QSqlQuery query;
    query.prepare("update contractsSet set time_contract=:_time_contract, date_contract=:_date_contract, currency_contract=:_currency_contract,"
                  " contragents_Id_contr=:_contragents_Id_contr, subjects_Id_subj=:_subjects_Id_subj,objects_Id_obj=:_objects_Id_obj"
                  " where id_contract=:_id_contract");
    query.bindValue(":_time_contract",this->ui->dateEdit->date().toString((Qt::ISODate)));
    query.bindValue(":_date_contract",this->ui->dateEdit_2->date().toString((Qt::ISODate)));
    query.bindValue(":_currency_contract",this->ui->comboBoxCurrencyContract->currentText());
    query.bindValue(":_contragents_Id_contr",this->getKeyFromMap(this->contragentsIdContr, this->ui->comboBoxContragentsIdContr->currentText()));
    query.bindValue(":_subjects_Id_subj",this->getKeyFromMap(this->subjectsIdSubj, this->ui->comboBoxSubjectsIdSubj->currentText()));
    query.bindValue(":_objects_Id_obj",this->getKeyFromMap(this->objectsIdObj, this->ui->comboBoxObjectsIdObj->currentText()));
    query.bindValue(":_id_contract", this->ui->comboBoxId->currentText().toInt());
    if(!query.exec())
        qDebug() << "Error" << "\n";
}

void NewTreaty::on_pushButton_3_clicked()
{
    QSqlQuery query;
    query.prepare("delete from contractsSet  where id_contract=:_id_contract");
    query.bindValue(":_id_contract", this->ui->comboBoxId->currentText().toInt());

    if(!query.exec())
        qDebug() << "Error" << "\n";
    this->close();
}
