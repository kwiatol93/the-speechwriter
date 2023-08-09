#include "document.h"

#include "../data/sentence.h"

Document::Document(QObject *parent) : QObject(parent)
{
}

int Document::sentencesCount() const
{
    return m_sentences.count();
}

void Document::addSentence(const QString &text, bool first_in_paragraph)
{
    m_sentences.append(SentencePtr(new Sentence(text, first_in_paragraph)));
}

bool Document::removeSentence(int index)
{
    if (isIndexValid(index))
    {
        m_sentences.removeAt(index);

        return true;
    }

    return false;
}

bool Document::swapSentences(int index_a, int index_b)
{
    if (isIndexValid(index_a) && isIndexValid(index_b))
    {
        m_sentences.swapItemsAt(index_a, index_b);

        return true;
    }

    return false;
}

SentencePtr Document::getSentence(int index)
{
    if (isIndexValid(index))
    {
        return m_sentences.at(index);
    }

    return SentencePtr();
}

bool Document::isIndexValid(int index)
{
    return (m_sentences.size() > index);
}
