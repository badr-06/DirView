#include <QApplication>
#include <QVBoxLayout>
#include <QTreeView>
#include <QDir>
#include <QLineEdit>
#include <QDebug>
#include "MainWindow.h"
#include "SortFilterProxyModel.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    homePath = QDir::homePath();

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    setupModel();
    setupEdit();
    setupProxy();
    setupTree();
    
    layout->addWidget(edit_);
    layout->addWidget(treeView_);

    connect(edit_, &QLineEdit::textChanged, this, &MainWindow::onFilterChanged, Qt::DirectConnection);

    setWindowTitle("Просмотр файлов - " + homePath);
}

void MainWindow::setupModel()
{
    model_ = new QFileSystemModel(this);
    model_->setRootPath(homePath);
    model_->setFilter(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot);
}

void MainWindow::setupEdit()
{
    edit_ = new QLineEdit(this);
    edit_->setPlaceholderText("Поле для фильтрации");
    edit_->setFixedSize(400, 25);
}

void MainWindow::setupTree()
{
    treeView_ = new QTreeView(this);
    treeView_->setModel(model_);
    treeView_->setRootIndex(model_->index(homePath));
    treeView_->setSortingEnabled(true);
    treeView_->sortByColumn(0, Qt::AscendingOrder);
    treeView_->setColumnWidth(0, 300);
    treeView_->setFocus();
    treeView_->setModel(proxy_);
    treeView_->setRootIndex(proxy_->mapFromSource(model_->index(homePath)));
}

void MainWindow::setupProxy()
{
    proxy_ = new SortFilterProxyModel(model_);
    proxy_->setSourceModel(model_);
}

void MainWindow::onFilterChanged(const QString &str)
{    
    proxy_->setFilterFixedString(str);

    QModelIndex proxyRoot = proxy_->mapFromSource(model_->index(homePath));

    if (proxyRoot.isValid()) 
        treeView_->setRootIndex(proxyRoot); 
}
