#include "MainWindow.h"
#include "SortFilterProxyModel.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QLineEdit>
#include <QTreeView>
#include <QVBoxLayout>

MainWindow::MainWindow(int width, int height, QWidget *parent)
    : QMainWindow(parent) {
  homePath = QDir::homePath();

  QWidget *centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);
  QVBoxLayout *layout = new QVBoxLayout(centralWidget);

  setupModel();
  setupEdit();
  setupProxy();
  setupTree(width);

  layout->addWidget(edit_);
  layout->addWidget(treeView_);

  connect(treeView_, &QTreeView::clicked, this,
          &MainWindow::onTreeViewSizeChanged, Qt::DirectConnection);
  connect(edit_, &QLineEdit::textChanged, this, &MainWindow::onFilterChanged,
          Qt::DirectConnection);

  resize(width, height);
  setWindowTitle("Просмотр файлов - " + homePath);
}

void MainWindow::setupModel() {
  model_ = new FileSystemModel(this);
  model_->setRootPath(homePath);
}

void MainWindow::setupEdit() {
  edit_ = new QLineEdit(this);
  edit_->setPlaceholderText("Поле для фильтрации");
  edit_->setFixedSize(400, 25);
}

void MainWindow::setupTree(int width) {
  treeView_ = new QTreeView(this);
  treeView_->setModel(model_);
  treeView_->setRootIndex(model_->index(homePath));
  treeView_->setSortingEnabled(true);
  treeView_->sortByColumn(0, Qt::AscendingOrder);
  treeView_->setColumnWidth(0, 300);
  treeView_->setFocus();
  treeView_->setModel(proxy_);
  treeView_->setRootIndex(proxy_->mapFromSource(model_->index(homePath)));

  int sizeColumn = width / model_->columnCount();

  treeView_->setColumnWidth(0, sizeColumn +
                                   (sizeColumn / 2));
  treeView_->setColumnWidth(1, (sizeColumn / 2) + 
                                   (sizeColumn / 4));
  treeView_->setColumnWidth(2, (sizeColumn / 2) + 
                                   (sizeColumn / 4));
  treeView_->setColumnWidth(2, sizeColumn);
}

void MainWindow::setupProxy() {
  proxy_ = new SortFilterProxyModel(model_);
  proxy_->setSourceModel(model_);
}

void MainWindow::onFilterChanged(const QString &str) {
  proxy_->setFilterFixedString(str);

  QModelIndex proxyRoot = proxy_->mapFromSource(model_->index(homePath));

  if (proxyRoot.isValid())
    treeView_->setRootIndex(proxyRoot);
}

void MainWindow::onTreeViewSizeChanged(const QModelIndex &index) {
  QModelIndex sourceIndex = proxy_->mapToSource(index);

  if (sourceIndex.column() != FileSystemModel::SizeColumn)
    return;

  QModelIndex nameColumnIndex =
      model_->index(sourceIndex.row(), 0, sourceIndex.parent());

  if (!model_->isDir(nameColumnIndex))
    return;

  model_->updateSizeFolder(sourceIndex);
}