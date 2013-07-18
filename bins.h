#ifndef BINS_H
#define BINS_H

#include <QMainWindow>
#include <QTableView>
#include "tableeditor.h"
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
    void recount(int q);

    void on_salva_bins_clicked();

private:
    QTableView *view;
    Ui::bins *ui;
    TableEditor *editor;
};

#endif // BINS_H
