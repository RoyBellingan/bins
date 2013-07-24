#ifndef BINS_H
#define BINS_H

#include <QMainWindow>
#include <QTableView>
#include "tableeditor.h"

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
    explicit bins(QWidget *parent = 0);
    ~bins();
    
private slots:
    void on_actionGestione_Clienti_triggered();
    void on_delta_bins_valueChanged(int a);
    void recount(int q);
    void make_filter();
    void on_salva_bins_clicked();
    void on_nome_ragione_returnPressed();
    void compile(const QModelIndex &index);


private:
    QTableView *view;
    Ui::bins *ui;
    TableEditor *editor;
    QCompleter *completer;
    QSqlTableModel *model;

};

#endif // BINS_H
