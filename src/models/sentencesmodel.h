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
    Q_INVOKABLE void checkDuplicates();
    Q_INVOKABLE bool duplicated(int index) const;
    Q_INVOKABLE int prevDuplicatedIndex(int index) const;
    Q_INVOKABLE int nextDuplicatedIndex(int index) const;

private slots:
    void onSentenceDuplicatedChanged(int index);

private:
    Document &m_document;
    QList<QList<int>> m_duplicates;
};

#endif // SENTENCES_MODEL_H
