#pragma once

#include <QSortFilterProxyModel>
#include <QFileSystemModel>

class SortFilterProxyModel : public QSortFilterProxyModel
{

    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;

public:
    explicit SortFilterProxyModel(QObject *parent = nullptr);
    
};