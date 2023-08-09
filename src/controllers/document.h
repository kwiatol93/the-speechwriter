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

    int sentencesCount() const;
    void addSentence(const QString &text = QString(), bool first_in_paragraph = false);
    bool removeSentence(int index);
    bool swapSentences(int index_a, int index_b);
    SentencePtr getSentence(int index);

signals:

private:
    bool isIndexValid(int index);

    QList<SentencePtr> m_sentences;
};

#endif // DOCUMENT_H
