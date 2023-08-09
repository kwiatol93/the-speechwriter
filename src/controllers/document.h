#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QSharedPointer>

class Sentence;
using SentencePtr = QSharedPointer<Sentence>;

class Document : public QObject
{
    Q_OBJECT
public:
    explicit Document(QObject *parent = nullptr);

    Q_INVOKABLE bool loadSentences(const QString &file_path);
    Q_INVOKABLE bool saveSentences(const QString &file_path);

    int sentencesCount() const;
    void addSentence(const QString &text = QString(), bool first_in_paragraph = false);
    bool removeSentence(int index);
    bool swapSentences(int index_i, int index_j);
    SentencePtr sentence(int index);

signals:
    void sentencesLoaded();

private:
    bool isIndexValid(int index);

    QList<SentencePtr> m_sentences;
};

#endif // DOCUMENT_H
