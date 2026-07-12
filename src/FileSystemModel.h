#pragma once

#include <QFileSystemModel>
#include <QHash>

class FileSystemModel : public QFileSystemModel {
  Q_OBJECT;

  QHash<QString, qint64> CacheSizes;

public:
  enum Columns { NameColumn = 0, SizeColumn, TypeColumn, DateColumn };

  explicit FileSystemModel(QObject *parent = nullptr);

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  void updateSizeFolder(const QModelIndex &index);
  qint64 calculateSize(const QString &path);
};