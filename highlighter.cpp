#include "highlighter.h"


Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
        QStringLiteral("\\blet\\b"), QStringLiteral("\\bfunc\\b"), QStringLiteral("\\bmacro\\b"),
        QStringLiteral("\\binfo\\b"), QStringLiteral("\\bjoin\\b"), QStringLiteral("\\blen\\b"),
        QStringLiteral("\\bprint\\b"), QStringLiteral("\\bexit\\b"), QStringLiteral("\\bexec\\b"),
        QStringLiteral("\\bpush\\b"), QStringLiteral("\\bquote\\b"), QStringLiteral("\\bunquote\\b"),
        QStringLiteral("\\breturn\\b"),
    };

    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression(QStringLiteral("\\bQ[A-Za-z]+\\b"));
    rule.format = classFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression(QStringLiteral("\\bfunc+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.append(rule);

    macroFormat.setFontItalic(true);
    macroFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("\\bmacro+(?=\\()"));
    rule.format = macroFormat;
    highlightingRules.append(rule);

}

void Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

}
