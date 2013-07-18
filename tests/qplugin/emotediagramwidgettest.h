#ifndef EMOTEDIAGRAMWIDGETTEST_H
#define EMOTEDIAGRAMWIDGETTEST_H

#include <QtTest>
#include <QtTestGui>

#include "qplugin/emotediagramwidget.h"

class EmoteDiagramWidgetTest : public QObject {

    Q_OBJECT

public:
    explicit EmoteDiagramWidgetTest ( QObject* parent = 0 );

private:
    EmoteDiagramWidget * emoteDiagramWidget;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testShouldShowEmoteDiagramWidget();
    void testShouldScaleSvgWidget();
};

#endif // EMOTEDIAGRAMWIDGETTEST_H
