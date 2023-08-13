#include "sentencesmodel.h"

#include "../application.h"
#include "../controllers/document.h"
#include "../data/sentence.h"

SentencesModel::SentencesModel(QObject *parent) :
    QAbstractListModel(parent), m_document(APP().document())
{
    connect(&m_document, &Document::sentencesLoaded, this, &SentencesModel::endResetModel);
    connect(&m_document, &Document::sentencesLoaded, this, &SentencesModel::checkDuplicates);
    connect(&m_document, &Document::sentenceDuplicatedChanged, this, &SentencesModel::onSentenceDuplicatedChanged);
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
                checkDuplicates();
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

    checkDuplicates();
}

bool SentencesModel::removeSentence(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    bool success = m_document.removeSentence(index);
    endRemoveRows();

    if (success)
    {
        checkDuplicates();
    }

    return success;
}

bool SentencesModel::swapSentence(int index_i, int index_j)
{
    if (m_document.swapSentences(index_i, index_j))
    {
        emit dataChanged(index(index_i, 0), index(index_i, 0));
        emit dataChanged(index(index_j, 0), index(index_j, 0));

        checkDuplicates();

        return true;
    }

    return false;
}

void SentencesModel::checkDuplicates()
{
    m_duplicates.clear();

    for (int index = 0; index < m_document.sentencesCount(); index++)
    {
        auto sentence = m_document.sentence(index);
        bool group_found = false;

        for (auto &group : m_duplicates)
        {
            auto sentence_grupped = m_document.sentence(group.first());
            if (!sentence_grupped.isNull() && (*sentence_grupped == *sentence))
            {
                sentence_grupped->setDuplicated(true);
                sentence->setDuplicated(true);
                group.append(index);
                group_found = true;
                break;
            }
        }

        if (!group_found)
        {
            m_duplicates.append(QList<int>() << index);
            sentence->setDuplicated(false);
        }
    }
}

bool SentencesModel::duplicated(int index) const
{
    if (const auto &sentence = m_document.sentence(index); !sentence.isNull() && sentence->duplicated())
    {
        return true;
    }

    return false;
}

int SentencesModel::prevDuplicatedIndex(int index) const
{
    for (const auto &group : m_duplicates)
    {
        if (group.contains(index))
        {
            if (group.size() > 1)
            {
                if (group.first() == index)
                {
                    return group.last();
                }
                else
                {
                    for (int i = 1; i < group.size(); i++)
                    {
                        if (group.at(i) == index)
                        {
                            return group.at(i - 1);
                        }
                    }
                }
            }

        }
    }

    return -1;
}

int SentencesModel::nextDuplicatedIndex(int index) const
{
    for (const auto &group : m_duplicates)
    {
        if (group.contains(index))
        {
            if (group.size() > 1)
            {
                if (group.last() == index)
                {
                    return group.first();
                }
                else
                {
                    for (int i = 0; i < group.size(); i++)
                    {
                        if ((group.at(i) == index) && ((i + 1) < group.size()))
                        {
                            return group.at(i + 1);
                        }
                    }
                }
            }
        }
    }

    return -1;
}

void SentencesModel::onSentenceDuplicatedChanged(int index)
{
    emit dataChanged(createIndex(index, 0), createIndex(index, 0), {DuplicatedRole});
}
