#include "bins.h"
#include "ui_bins.h"
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

bins::bins(QWidget *parent) :    QMainWindow(parent),    ui(new Ui::bins){

QSignalMapper* smap = new QSignalMapper (this) ;

    QShortcut *c1 = new QShortcut(QKeySequence("Ctrl+1"),this);
    QShortcut *c5 = new QShortcut(QKeySequence("Ctrl+5"),this);
    QShortcut *a1 = new QShortcut(QKeySequence("Alt+1"),this);
    QShortcut *a5 = new QShortcut(QKeySequence("Alt+5"),this);
    QObject::connect(c1, SIGNAL(activated()), smap, SLOT(map()));
    QObject::connect(c5, SIGNAL(activated()), smap, SLOT(map()));
    QObject::connect(a1, SIGNAL(activated()), smap, SLOT(map()));
    QObject::connect(a5, SIGNAL(activated()), smap, SLOT(map()));

    smap -> setMapping (c1, 1) ;
    smap -> setMapping (c5, 5) ;
    smap -> setMapping (a1, -1) ;
    smap -> setMapping (a5, -5) ;

    connect (smap, SIGNAL(mapped(int)), this, SLOT(recount(int))) ;

    editor=new TableEditor("person");

    ui->setupUi(this);
    /*
    ui->add_bins->setShortcut(QKeySequence("Ctrl+1"));
    ui->add_bins->setShortcut(QKeySequence("Ctrl+5"));
    ui->remove_bins->setShortcut(QKeySequence("Alt+1"));
    ui->remove_bins->setShortcut(QKeySequence("Alt+5"));
    */

}

bins::~bins(){
    delete ui;
}


void bins::recount(int q){

    ui->contatore_bins->setValue (ui->contatore_bins->value () + q);
}


void bins::on_actionGestione_Clienti_triggered()
{


    editor->show();
    //editor->setAttribute( Qt::WA_DeleteOnClose );


/*
    QWidget *window=new QWidget;
    window->resize(320, 240);


    view = new QTableView;
    //view->setModel(model);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    //view->hideColumn (0);
    view->resizeColumnsToContents();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);
    window->setLayout (mainLayout);


    window->show ();

    window->setAttribute( Qt::WA_DeleteOnClose );
    */


}

void bins::on_salva_bins_clicked(){




///fai il commit al db...
}



TableEditor::TableEditor(const QString &tableName, QWidget *parent)	: QWidget(parent) {
    model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(1, Qt::Horizontal, tr("First name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Last name"));

    needrow ();

    view = new QTableView;
    view->setModel(model);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->hideColumn (0);
    view->resizeColumnsToContents();

    submitButton = new QPushButton(tr("&Submit"));
    submitButton->setDefault(true);
    revertButton = new QPushButton(tr("&Revert"));
    deletaButton = new QPushButton(tr("&Delete"));
    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(deletaButton, QDialogButtonBox::RejectRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(revertButton, SIGNAL(clicked()), this, SLOT(revertAll()));
    connect(deletaButton, SIGNAL(clicked()), this, SLOT(deleta()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(hide()));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    view->setFixedSize (420,640);
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    mainLayout->addStretch (0);

    setLayout(mainLayout);

    setWindowTitle(tr("Cached Table"));

}

void TableEditor::submit() {

    QSqlRecord rec = model->record(model->rowCount ()-1);
    QString str = rec.value (1).toString ();
    if (str.isEmpty ()) {
        model->removeRow (model->rowCount ()-1);
    }

    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
        needrow ();
    } else {
        model->revertAll ();
        needrow ();
        QMessageBox::warning(this, tr("Cached Table"),
                             tr("The database reported an error: %1")
                             .arg(model->lastError().text()));
    }
}

void TableEditor::revertAll() {
    model->revertAll ();
    needrow ();
}

/**
 * @brief TableEditor::needrow
 *Controlla se l'ultima riga è vuota, se non lo è ne mette una.
 *@todo click su una riga e tasto aggiungi sarebbe carino.
 */
void TableEditor::needrow() {
    QSqlRecord rec = model->record(model->rowCount ()-1);
    QString str = rec.value (1).toString ();
    if (!str.isEmpty ()) {
        model->insertRow (model->rowCount ());
    }

}

/**
 * @brief TableEditor::deleta
 *cancella la riga selezionata
 */
void TableEditor::deleta () {
    QModelIndexList indexes = view->selectionModel()->selection().indexes ();
    if (indexes.count ()>0) {
        QModelIndex index = indexes.at(0);
        model->removeRow (index.row ());
        submit();
    }
}
