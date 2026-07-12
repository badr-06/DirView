#pragma once

#include <QSortFilterProxyModel>
#include "FileSystemModel.h"

class SortFilterProxyModel : public QSortFilterProxyModel
{

    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;

public:
    explicit SortFilterProxyModel(QObject *parent = nullptr);
    
};