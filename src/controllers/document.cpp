#include "document.h"

#include <QFile>
#include <QTextStream>

#include "../data/sentence.h"

Document::Document(QObject *parent) : QObject(parent)
{
}

bool Document::loadSentences(const QString &file_path)
{
    static constexpr int NUMBER_OF_SIGNS_TO_READ{1};

    QFile file(file_path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QList<SentencePtr> sentences;
        QTextStream stream(&file);
        QString text;

        while (!stream.atEnd())
        {
            auto sign = stream.read(NUMBER_OF_SIGNS_TO_READ);
            if (sign != "\n")
            {
                text += sign;
            }

            if (text.endsWith(".") || text.endsWith("?") || text.endsWith("!"))
            {
                bool first_in_paragraph = text.startsWith("\t");
                text = text.trimmed();

                sentences.append(SentencePtr(new Sentence(text, first_in_paragraph)));
                text.clear();
            }
        }
        file.close();

        if (!text.isEmpty())
        {
            text.append(".");
            sentences.append(SentencePtr(new Sentence(text, text.startsWith("\t"))));
            text.clear();
        }

        if (!sentences.isEmpty())
        {
            m_sentences = sentences;
            for (const auto &sentence : m_sentences)
            {
                connect(sentence.get(), &Sentence::duplicatedChanged, this, &Document::onSentenceDuplicatedChanged);
            }

            emit sentencesLoaded();

            return true;
        }
    }

    return false;
}

bool Document::saveSentences(const QString &file_path)
{
    QFile file(file_path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&file);

        for (auto it = m_sentences.begin(); it != m_sentences.end(); ++it)
        {
            if ((*it)->firstInParagraph())
            {
                if (it != m_sentences.begin())
                {
                    stream << "\n";
                }

                stream << "\t";
            }

            stream << (*it)->text();

            if (it != m_sentences.end())
            {
                stream << "\n";
            }
        }

        return true;
    }

    return false;
}

int Document::sentencesCount() const
{
    return m_sentences.count();
}

void Document::addSentence(const QString &text, bool first_in_paragraph)
{
    auto sentence = SentencePtr(new Sentence(text, first_in_paragraph));
    m_sentences.append(sentence);

    connect(sentence.get(), &Sentence::duplicatedChanged, this, &Document::onSentenceDuplicatedChanged);
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

bool Document::swapSentences(int index_i, int index_j)
{
    if (isIndexValid(index_i) && isIndexValid(index_j))
    {
        m_sentences.swapItemsAt(index_i, index_j);

        return true;
    }

    return false;
}

SentencePtr Document::sentence(int index)
{
    if (isIndexValid(index))
    {
        return m_sentences.at(index);
    }

    return SentencePtr();
}

void Document::onSentenceDuplicatedChanged()
{
    auto sentence = dynamic_cast<Sentence*>(sender());
    int index = m_sentences.indexOf(sentence);

    emit sentenceDuplicatedChanged(index);
}

bool Document::isIndexValid(int index)
{
    return (m_sentences.size() > index);
}
