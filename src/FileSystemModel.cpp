#include "FileSystemModel.h"
#include <QMimeDatabase>
#include <QLocale>

FileSystemModel::FileSystemModel(QObject *parent) : QFileSystemModel(parent)
{
    setFilter(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot);
}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case NameColumn: return "Имя";
            case SizeColumn: return "Размер";
            case TypeColumn: return "Тип";
            case DateColumn: return "Последнее изменение";
            default: return QVariant();
        }
    }
    return QFileSystemModel::headerData(section, orientation, role);
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    QString path = filePath(index);
    QFileInfo info(path);
    
    if (role == Qt::DisplayRole) {
        if(index.column() == NameColumn){
            return info.fileName();
        }

        else if(index.column() == SizeColumn){

            auto formatDataSize = [](int size) -> QString
            {
                return QLocale().formattedDataSize(size, 2, QLocale::DataSizeTraditionalFormat);
            };

            if(info.isDir()){
                if (CacheSizes.contains(path))
                {
                    int bytes = CacheSizes[path];
                    return formatDataSize(bytes);
                }

                return "[Обновить]";
            }

            return formatDataSize(info.size());
        }

        else if(index.column() == TypeColumn){
            if(info.isDir()){
                return "каталог";
            }
            QMimeDatabase db;
            QMimeType mime = db.mimeTypeForFile(path, QMimeDatabase::MatchContent);
            
            if(!mime.isValid()) return QVariant();

            return mime.comment();
        }
    }
    
    return QFileSystemModel::data(index, role);
}

void FileSystemModel::updateSizeFolder(const QModelIndex &index)
{
}
