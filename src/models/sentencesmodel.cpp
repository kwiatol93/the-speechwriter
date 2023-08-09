#include "sentencesmodel.h"

#include "../application.h"
#include "../controllers/document.h"
#include "../data/sentence.h"

SentencesModel::SentencesModel(QObject *parent) :
    QAbstractListModel(parent), m_document(APP().document())
{
    connect(&m_document, &Document::sentencesLoaded, this, &SentencesModel::endResetModel);
}

QHash<int, QByteArray> SentencesModel::roleNames() const
{
    static const QHash<int, QByteArray> ROLES = {
        {TextRole, "text"},
        {FirstInParagraphRole, "firstInParagraph"},
        {DuplicatedRole, "duplicated"},
    };
    return ROLES;
}

int SentencesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_document.sentencesCount();
}

QVariant SentencesModel::data(const QModelIndex &index, int role) const
{
    auto sentence = m_document.sentence(index.row());
    if (!sentence.isNull())
    {
        switch (static_cast<Role>(role))
        {
            case TextRole:
                return sentence->text();
            case FirstInParagraphRole:
                return sentence->firstInParagraph();
            case DuplicatedRole:
                return sentence->duplicated();
            default:
                break;
        }
    }

    return QVariant();
}

bool SentencesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto sentence = m_document.sentence(index.row());
    if (!sentence.isNull())
    {
        switch (static_cast<Role>(role))
        {
            case TextRole:
                sentence->setText(value.toString());
                emit dataChanged(index, index, {TextRole});
                return true;
            case FirstInParagraphRole:
                sentence->setFirstInParagraph(value.toBool());
                emit dataChanged(index, index, {FirstInParagraphRole});
                return true;
            case DuplicatedRole:
                sentence->setDuplicated(value.toBool());
                emit dataChanged(index, index, {DuplicatedRole});
                return true;
            default:
                break;
        }
    }

    return false;
}

void SentencesModel::addSentence()
{
    beginInsertRows(QModelIndex(), m_document.sentencesCount(), m_document.sentencesCount());
    m_document.addSentence();
    endInsertRows();
}

bool SentencesModel::removeSentence(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    bool success = m_document.removeSentence(index);
    endRemoveRows();

    return success;
}

bool SentencesModel::swapSentence(int index_i, int index_j)
{
    if (m_document.swapSentences(index_i, index_j))
    {
        emit dataChanged(index(index_i, 0), index(index_i, 0));
        emit dataChanged(index(index_j, 0), index(index_j, 0));

        return true;
    }

    return false;
}
