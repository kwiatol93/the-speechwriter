#include "sentence.h"

Sentence::Sentence(QObject *parent) : Sentence(QString(), false, parent)
{
}

Sentence::Sentence(const QString &text, bool first_in_paragraph, QObject *parent) :
    QObject(parent), m_text(text), m_first_in_paragraph(first_in_paragraph), m_duplicated(false)
{
}

bool Sentence::operator==(const Sentence &other) const
{
    return (m_text.simplified().trimmed() == other.m_text.simplified().trimmed());
}

QString Sentence::text() const
{
    return m_text;
}

void Sentence::setText(const QString &text)
{
    if (m_text != text)
    {
        m_text = text;
        emit textChanged();
    }
}

bool Sentence::firstInParagraph() const
{
    return m_first_in_paragraph;
}

void Sentence::setFirstInParagraph(bool value)
{
    if (m_first_in_paragraph != value)
    {
        m_first_in_paragraph = value;
        emit firstInParagraphChanged();
    }
}

bool Sentence::duplicated() const
{
    return m_duplicated;
}

void Sentence::setDuplicated(bool value)
{
    if (m_duplicated != value)
    {
        m_duplicated = value;
        emit duplicatedChanged();
    }
}
