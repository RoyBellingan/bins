#include "bins.h"
#include "ui_bins.h"
#include <time.h>

#define null 0

bins::bins(QWidget *parent) :    QMainWindow(parent),    ui(new Ui::bins){

    QShortcut *s1 = new QShortcut(QKeySequence("Ctrl+s"),this);
    QObject::connect(s1, SIGNAL(activated()),this, SLOT(on_salva_bins_clicked()));



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

    editor=new TableEditor("bins");

    ui->setupUi(this);
    ui->salva_bins->hide ();

    make_filter ();
}

void bins::make_filter(){

    QSqlQuery query;
    query.exec("select id,nome,piva,indirizzo from bins");
    QStringList nome,piva,indirizzo;
    while (query.next()) {
        nome.append (query.value(1).toString ());
        piva.append (query.value(2).toString ());
        indirizzo.append (query.value(3).toString ());
    }

    model = new QSqlTableModel(this);
    model->setTable("bins");
    model->select();

    completer_1 = new QCompleter(this);
    completer_1->setModel (model);
    completer_1->setCompletionColumn (1);
    completer_1->setCaseSensitivity(Qt::CaseInsensitive);

    completer_2 = new QCompleter(this);
    completer_2->setModel (model);
    completer_2->setCompletionColumn (2);
    completer_2->setCaseSensitivity(Qt::CaseInsensitive);

    completer_3 = new QCompleter(this);
    completer_3->setModel (model);
    completer_3->setCompletionColumn (3);
    completer_3->setCaseSensitivity(Qt::CaseInsensitive);

    ui->nome_ragione->setCompleter (completer_1);
    ui->p_iva->setCompleter (completer_2);
    ui->indirizzo->setCompleter (completer_3);

    QObject::connect(completer_1, SIGNAL(activated(QModelIndex)),this, SLOT(filt_1(QModelIndex)));
    QObject::connect(completer_2, SIGNAL(activated(QModelIndex)),this, SLOT(filt_2(QModelIndex)));
    QObject::connect(completer_3, SIGNAL(activated(QModelIndex)),this, SLOT(filt_3(QModelIndex)));
}


void bins::filt_1(const QModelIndex &index){
    QAbstractItemModel *completionModel = completer_1->completionModel();
    QAbstractProxyModel *proxy = qobject_cast<QAbstractProxyModel *>(completionModel);
    if (!proxy)
        return;
    QModelIndex sourceIndex = proxy->mapToSource(index);
    compile(sourceIndex.row());

}

void bins::filt_2(const QModelIndex &index){
    QAbstractItemModel *completionModel = completer_2->completionModel();
    QAbstractProxyModel *proxy = qobject_cast<QAbstractProxyModel *>(completionModel);
    if (!proxy)
        return;
    QModelIndex sourceIndex = proxy->mapToSource(index);
    compile(sourceIndex.row());

}

void bins::filt_3(const QModelIndex &index){
    QAbstractItemModel *completionModel = completer_3->completionModel();
    QAbstractProxyModel *proxy = qobject_cast<QAbstractProxyModel *>(completionModel);
    if (!proxy)
        return;
    QModelIndex sourceIndex = proxy->mapToSource(index);
    compile(sourceIndex.row());

}



void bins::compile(const int id){
    id_tab=id;
    ui->nome_ragione->setText (model->record (id).value (1).toString ());
    ui->p_iva->setText (model->record (id).value (2).toString ());
    ui->indirizzo->setText (model->record (id).value (3).toString ());

    ui->contatore_bins->setValue (model->record (id).value (4).toInt ());
    ui->delta_bins->setValue (0);

}

void bins::on_nome_ragione_returnPressed(){

}

bins::~bins(){
    delete ui;
}



void bins::recount(int q){

    ui->contatore_bins->setValue (ui->contatore_bins->value () + q);
}

void bins::on_delta_bins_valueChanged(int a){
    a=a+a;
    if (ui->delta_bins->value ()==0){
        ui->salva_bins->hide ();
    }else{
        ui->salva_bins->show ();
    }
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

    ui->contatore_bins->setValue (ui->contatore_bins->value() + ui->delta_bins->value());
    //model->record (id_tab).value (4).setValue(ui->contatore_bins->value());
    QString qq;
    qq.append ("UPDATE `bins` SET `bins` = " + QString::number (ui->contatore_bins->value()));
    qq.append (" WHERE `id` = ");
    qq.append (model->record (id_tab).value (0).toString ());

    QSqlQuery query;
    query.exec(qq);
    qDebug () << query.lastError ();
    qDebug () << qq.toLatin1 ();

    ui->delta_bins->setValue (0);

    ///@todo refresh del model... con falso submit


    ///fai il commit al db...
}



TableEditor::TableEditor(const QString &tableName, QWidget *parent)	: QWidget(parent) {
    model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(1, Qt::Horizontal, tr("Nome"));
    model->setHeaderData(2, Qt::Horizontal, tr("P.IVA"));
    model->setHeaderData(3, Qt::Horizontal, tr("Indirizzo"));

    view = new QTableView;
    view->setModel(model);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->hideColumn (0);
    view->resizeColumnsToContents();
    view->setSortingEnabled (true);

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
    view->setMinimumSize (620,640);
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    mainLayout->addStretch (0);

    setLayout(mainLayout);
    setWindowTitle(tr("Gestione Clienti"));
    needrow ();
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
    bins* w=bins::get_instance ();
    w->make_filter();

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

void bins::on_actionEsci_triggered(){
    QCoreApplication::exit(0);
}
