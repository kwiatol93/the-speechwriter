#ifndef SENTENCE_H
#define SENTENCE_H

#include <QObject>

class Sentence : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(bool firstInParagraph READ firstInParagraph WRITE setFirstInParagraph NOTIFY
            firstInParagraphChanged)
    Q_PROPERTY(bool duplicated READ duplicated WRITE setDuplicated NOTIFY duplicatedChanged)

public:
    explicit Sentence(QObject *parent = nullptr);
    explicit Sentence(const QString &text, bool first_in_paragraph, QObject *parent = nullptr);

    QString text() const;
    void setText(const QString &text);
    bool firstInParagraph() const;
    void setFirstInParagraph(bool value);
    bool duplicated() const;
    void setDuplicated(bool value);

signals:
    void textChanged();
    void firstInParagraphChanged();
    void duplicatedChanged();

private:
    QString m_text;
    bool m_first_in_paragraph;
    bool m_duplicated;
};

#endif // SENTENCE_H
