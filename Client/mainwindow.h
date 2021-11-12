#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <tuple>
#include <QSqlTableModel>
#include <QtSql>
#include <QMessageBox>
#include <memory>
#include "auth_window.h"
#include "newtreaty.h"
#include "newcontragents.h"
#include "newobject.h"
#include "newdocument.h"
#include "newnote.h"
#include "newsubjetc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void display();
    bool createConnection();
    ~MainWindow();

private slots:
    void authorizeUser();
    void on_comboBoxShowTables_currentIndexChanged(int index);
    void on_comboBoxAddOrChange_currentIndexChanged(int index);

    void on_action_triggered();

    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_action_1_triggered();
    void on_action_4_triggered();

    void on_pushButtonReport_clicked();

    void selectContractsSet();
    void selectContrAgentsSet();
    void selectDocumentsSet();
    void selectNotesSet();
    void selectObjectsSet();
    void selectSubjectsSet();

private:
    void getQuery(QString queryString);

private:
    Ui::MainWindow *ui;
    Auth_window *auth_window;
    QSqlDatabase *qSqlDatabase;
};
#endif // MAINWINDOW_H
