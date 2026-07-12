#pragma once

#include <QMainWindow>

class QTreeView;
class QLineEdit;
class SortFilterProxyModel;
class FileSystemModel;

class MainWindow : public QMainWindow {
  Q_OBJECT;

private:
  QTreeView *treeView_;
  QLineEdit *edit_;
  SortFilterProxyModel *proxy_;
  FileSystemModel *model_;
  QString homePath;

  void setupModel();
  void setupTree(size_t width);
  void setupEdit();
  void setupProxy();

private slots:
  void onFilterChanged(const QString &str);
  void onTreeViewSizeChanged(const QModelIndex &index);

public:
  explicit MainWindow(size_t width, size_t height, QWidget *parent = nullptr);
};