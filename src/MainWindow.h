#pragma once

#include <QMainWindow>

class QTreeView;
class QLineEdit;
class SortFilterProxyModel;
class QFileSystemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT;

private:
    QTreeView *treeView_;
    QLineEdit *edit_;
    SortFilterProxyModel *proxy_;
    QFileSystemModel *model_;
    QString homePath;

    void setupModel();
    void setupTree();
    void setupEdit();
    void setupProxy();

private slots:
    void onFilterChanged(const QString &str);

public:
    explicit MainWindow(QWidget *parent = nullptr);


    
};