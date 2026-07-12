#include "SortFilterProxyModel.h"

SortFilterProxyModel::SortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {
  setRecursiveFilteringEnabled(true);
  setFilterCaseSensitivity(Qt::CaseInsensitive);
}

bool SortFilterProxyModel::lessThan(const QModelIndex &source_left,
                                    const QModelIndex &source_right) const {

  FileSystemModel *fmodel = qobject_cast<FileSystemModel *>(sourceModel());
  if (!fmodel) {
    return QSortFilterProxyModel::lessThan(source_left, source_right);
  }

  bool leftHidden = fmodel->fileInfo(source_left).isHidden();
  bool rightHidden = fmodel->fileInfo(source_right).isHidden();

  if (leftHidden != rightHidden) {
    return rightHidden;
  }

  QString leftSrting = source_left.data().toString();
  QString rightSrting = source_right.data().toString();

  return leftSrting.toLower() < rightSrting.toLower();
}
