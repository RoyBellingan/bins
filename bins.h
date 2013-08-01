#ifndef BINS_H
#define BINS_H

#include <QMainWindow>
#include <QTableView>
#include "tableeditor.h"
#include <QShortcut>
#include <QDebug>
#include <QtWidgets>
#include <QMainWindow>
#include <QSignalMapper>
#include <QString>
#include <QtWidgets>
#include <QtSql>
#include <QSqlRecord>
#include "tableeditor.h"
#include <QSqlQuery>

#define null 0

QT_BEGIN_NAMESPACE
class QCompleter;
QT_END_NAMESPACE

namespace Ui {
class bins;
}

class bins : public QMainWindow
{
    Q_OBJECT
    
public:

    ~bins();
    static bins* get_instance() {
            if (instance_ptr == null) {
                    instance_ptr = new bins;
            }
            return instance_ptr;
    }
    bool method() { return true; };
    void make_filter();

private slots:
    void on_actionGestione_Clienti_triggered();
    void on_delta_bins_valueChanged(int a);
    void recount(int q);

    void on_salva_bins_clicked();
    void on_nome_ragione_returnPressed();
    void filt_1(const QModelIndex &index);
    void filt_2(const QModelIndex &index);
    void filt_3(const QModelIndex &index);
    void compile(const int id);
    void on_actionEsci_triggered();
    void on_actionSalva_triggered();
    void on_actionCarica_triggered();


private:
    QTableView *view;
    Ui::bins *ui;
    TableEditor *editor;
    QCompleter *completer_1;
    QCompleter *completer_2;
    QCompleter *completer_3;
    QSqlTableModel *model;
    //QAbstractProxyModel *proxy;
    static bins* instance_ptr;
    explicit bins(QWidget *parent = 0);


};

#endif // BINS_H
