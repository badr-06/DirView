#include "FileSystemModel.h"
#include <QDirIterator>
#include <QFileIconProvider>
#include <QLocale>
#include <QMimeDatabase>

FileSystemModel::FileSystemModel(QObject *parent) : QFileSystemModel(parent) {
  setFilter(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot);
}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    switch (section) {
    case NameColumn:
      return "Имя";
    case SizeColumn:
      return "Размер";
    case TypeColumn:
      return "Тип";
    case DateColumn:
      return "Последнее изменение";
    default:
      return QVariant();
    }
  }
  return QFileSystemModel::headerData(section, orientation, role);
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  QString path = filePath(index);
  QFileInfo info(path);

  if (role == Qt::DisplayRole) {

    if (index.column() == SizeColumn) {

      auto formatDataSize = [](qint64 size) -> QString {
        return QLocale().formattedDataSize(size, 2,
                                           QLocale::DataSizeTraditionalFormat);
      };

      if (info.isDir()) {
        if (CacheSizes.contains(path)) {
          qint64 bytes = CacheSizes[path];
          return formatDataSize(bytes);
        }

        return "[Обновить размер]";
      }

      return formatDataSize(info.size());
    }

    else if (index.column() == TypeColumn) {
      if (info.isDir()) {
        return "каталог";
      }
      QMimeDatabase db;
      QMimeType mime = db.mimeTypeForFile(path, QMimeDatabase::MatchExtension);

      if (!mime.isValid())
        return QVariant();

      return mime.comment();
    }
  }

  return QFileSystemModel::data(index, role);
}

void FileSystemModel::updateSizeFolder(const QModelIndex &index) {
  QString path = filePath(index);

  qint64 size = calculateSize(path);

  CacheSizes[path] = size;

  emit dataChanged(index, index);
}

qint64 FileSystemModel::calculateSize(const QString &path) {
  QDirIterator it(path, QDir::Files, QDirIterator::Subdirectories);
  qint64 totalSize = 0;

  while (it.hasNext()) {
    QFileInfo info(it.next());
    totalSize += info.size();
  }

  return totalSize;
}
