#ifndef SENTENCES_MODEL_H
#define SENTENCES_MODEL_H

#include <QAbstractListModel>

class Document;

class SentencesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role
    {
        TextRole = Qt::UserRole,
        FirstInParagraphRole,
        DuplicatedRole,
    };
    Q_ENUM(Role)

    explicit SentencesModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Q_INVOKABLE void addSentence();
    Q_INVOKABLE bool removeSentence(int index);
    Q_INVOKABLE bool swapSentence(int index_i, int index_j);

private:
    Document &m_document;
};

#endif // SENTENCES_MODEL_H
