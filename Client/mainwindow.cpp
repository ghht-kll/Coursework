#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->setWindowTitle("Главное окно");
    this->auth_window = new Auth_window();
    this->qSqlDatabase = new QSqlDatabase();
    connect(this->auth_window, SIGNAL(login_button_clicked()), this, SLOT(authorizeUser()));
    connect(this->auth_window, SIGNAL(destroyed()), this, SLOT(show()));

    this->auth_window->show();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::authorizeUser()
{
    if(this->createConnection())
        delete this->auth_window;
}

bool MainWindow::createConnection()
{
    std::tuple<QString, QString> userData = this->auth_window->getUserData();

    *this->qSqlDatabase = QSqlDatabase::addDatabase("QODBC3");
    this->qSqlDatabase->setDatabaseName(QString("DRIVER={SQL Server};SERVER=DESKTOP-CTL9SPM;DATABASE=ContractDB;"));
    this->qSqlDatabase->setUserName(std::get<0>(userData));
    this->qSqlDatabase->setPassword(std::get<1>(userData));

    if(!this->qSqlDatabase->open())
    {
        QMessageBox error;
        error.setText(QSqlError(this->qSqlDatabase->lastError()).text());
        return false;
    }
    else return true;
}

void MainWindow::display()
{
    this->auth_window->show();
}

void MainWindow::getQuery(QString queryString)
{
    QSqlQueryModel *model = new QSqlTableModel;
    this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setQuery(queryString);
    if(model->lastError().isValid())
    {
        QMessageBox error;
        error.setText(QSqlError(this->qSqlDatabase->lastError()).text());
        return;
    }
    this->ui->tableView->setModel(model);
    this->ui->tableView->show();
}

void MainWindow::selectContractsSet()
{
    this->getQuery("select id_contract, time_contract, date_contract, currency_contract, contrAgentsSet.compname_contr, "
                   "contrAgentsSet.fullname_contr, objectsSet.name_obj  from contractsSet "
                   "join contrAgentsSet on contrAgentsSet.Id_contr = contragents_Id_contr "
                   "join objectsSet on objectsSet.Id_obj = objects_Id_obj");
}

void MainWindow::selectContrAgentsSet()
{
    this->getQuery("select * from contrAgentsSet");
}

void MainWindow::selectDocumentsSet()
{
    this->getQuery("select documentsSet.Id_doc, documentsSet.name_doc, documentsSet.address_doc, contractsSet.id_contract from documentsSet"
                   " join contractsSet on contractsSet.id_contract = documentsSet.contracts_id_contract");
}

void MainWindow::selectNotesSet()
{
    this->getQuery("select notesSet.Id_note, notesSet.note, contractsSet.id_contract from notesSet"
                   " join contractsSet on contractsSet.id_contract = notesSet.contracts_id_contract");
}

void MainWindow::selectObjectsSet()
{
    this->getQuery("select * from objectsSet");
}

void MainWindow::selectSubjectsSet()
{
    this->getQuery("select * from subjectsSet");
}

void MainWindow::on_comboBoxShowTables_currentIndexChanged(int index)
{
    if(index == 0)
        this->selectContractsSet();
    else if(index == 1)
        this->selectContrAgentsSet();
    else if(index == 2)
        this->selectDocumentsSet();
    else if(index == 3)
        this->selectNotesSet();
    else if(index == 4)
        this->selectObjectsSet();
    else if(index == 5)
        this->selectSubjectsSet();
}

void MainWindow::on_comboBoxAddOrChange_currentIndexChanged(int index)
{
    if(index == 0)
    {
        NewTreaty *newTreaty = new NewTreaty(this->qSqlDatabase); //!!! узнай как лучше
        newTreaty->setAttribute(Qt::WA_DeleteOnClose);
        newTreaty->show();
    }
    else if(index == 1)
    {
        NewContrAgents *newContrAgents = new NewContrAgents(this->qSqlDatabase);
        newContrAgents->setAttribute(Qt::WA_DeleteOnClose);
        newContrAgents->show();
    }
    else if(index == 2)
    {
        NewDocument *newDocument = new NewDocument(this->qSqlDatabase);
        newDocument->setAttribute(Qt::WA_DeleteOnClose);
        newDocument->show();
    }
    else if(index == 3)
    {
        NewNote *newNote = new NewNote(this->qSqlDatabase);
        newNote->setAttribute(Qt::WA_DeleteOnClose);
        newNote->show();
    }
    else if(index == 4)
    {
        NewObject *newObject = new NewObject(this->qSqlDatabase);
        newObject->setAttribute(Qt::WA_DeleteOnClose);
        newObject->show();
    }
    else if(index == 5)
    {
        NewSubjetc *newSubject = new NewSubjetc(this->qSqlDatabase);
        newSubject->setAttribute(Qt::WA_DeleteOnClose);
        newSubject->show();
    }
}

void MainWindow::on_action_triggered()
{
    this->getQuery("SELECT dbo.contrAgentsSet.itn_contr AS ITN, SUM(CASE WHEN dbo.contractsSet.time_contract <"
                   " '2005-05-05' THEN 1 ELSE 0 END) AS Contracts"
                   " FROM     dbo.contractsSet INNER JOIN"
                                     " dbo.contrAgentsSet ON dbo.contractsSet.contragents_Id_contr = dbo.contrAgentsSet.Id_contr"
                   " WHERE dbo.contractsSet.time_contract < '2005-05-05'"
                   " GROUP BY dbo.contrAgentsSet.itn_contr");
}

void MainWindow::on_action_2_triggered()
{
    this->getQuery("select * from view_entity_contragents");
}

void MainWindow::on_action_3_triggered()
{
    this->getQuery("SELECT DISTINCT dbo.contractsSet.id_contract, dbo.contractsSet.time_contract, dbo.contractsSet.date_contract,"
                   " dbo.contractsSet.currency_contract, dbo.contractsSet.objects_Id_obj, dbo.contractsSet.subjects_Id_subj,"
                   " (SELECT fullname_contr"
                   " FROM      dbo.contrAgentsSet, dbo.contractsSet"
                   " WHERE   (dbo.contractsSet.contragents_Id_contr = Id_contr) AND (dbo.contrAgentsSet.compname_contr IS NULL )) AS Agent"
                   " FROM     dbo.contractsSet,"
                   "(SELECT Id_contr, type_contr, compname_contr, fullname_contr, itn_contr, msrn_contr, document_contr, bic_contr, chaccount_contr,"
                   " address_contr, phnumber_contr"
                   " FROM      dbo.contrAgentsSet AS contrAgentsSet_1, dbo.contractsSet"
                   " WHERE   (dbo.contractsSet.contragents_Id_contr = Id_contr) AND (type_contr = 1)) AS Nedeed_agents"
                   " WHERE  (dbo.contractsSet.date_contract ="
                   "(SELECT CAST(GETDATE() AS DATE) AS Today) AND dbo.contractsSet.contragents_Id_contr = Id_contr )");
}

void MainWindow::on_action_1_triggered()
{
    this->getQuery("SELECT dbo.contrAgentsSet.fullname_contr, COUNT(dbo.contractsSet.id_contract) AS Contracts"
                   " FROM   dbo.contractsSet, dbo.contrAgentsSet"
                   " WHERE  dbo.contractsSet.contragents_Id_contr = dbo.contrAgentsSet.Id_contr AND dbo.contrAgentsSet.type_contr = 0"
                   " GROUP BY dbo.contrAgentsSet.fullname_contr"
                   " HAVING (dbo.contrAgentsSet.fullname_contr IS NOT NULL) AND DATEDIFF ( month , date_contract , time_contract ) > 12");
}

void MainWindow::on_action_4_triggered()
{
    this->getQuery("SELECT id_contract, time_contract, date_contract, currency_contract, contragents_Id_contr"
                   " FROM     dbo.contractsSet"
                   " WHERE  (contragents_Id_contr = ANY"
                                         " (SELECT Id_contr"
                                         " FROM      dbo.contrAgentsSet"
                                         " WHERE   (type_contr = 1) AND (fullname_contr IS NOT NULL)))");
}



void MainWindow::on_pushButtonReport_clicked()
{
    this->getQuery("select * from logsSet");
}
