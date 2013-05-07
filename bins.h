#ifndef BINS_H
#define BINS_H

#include <QMainWindow>

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
    void on_nome_triggered();

    void on_add_bins_clicked();

private:
    Ui::bins *ui;
};

#endif // BINS_H
