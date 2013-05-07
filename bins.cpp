#include "bins.h"
#include "ui_bins.h"
#include <QShortcut>
#include <QDebug>




bins::bins(QWidget *parent) :    QMainWindow(parent),    ui(new Ui::bins){
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+O"),this);
    QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(on_nome_triggered()));

    ui->setupUi(this);
    ui->add_bins->setShortcut(QKeySequence("Ctrl+1"));
}

bins::~bins(){
    delete ui;
}

void bins::on_nome_triggered(){
    ui->nome_ragione->setFocus(Qt::OtherFocusReason);
}

void bins::on_add_bins_clicked()
{
    qDebug("cliccato mi hai");
}
