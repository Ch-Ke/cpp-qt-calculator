#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    void setupUI();
    void performCalculation();
    QLineEdit *display;
    QGridLayout *layout;
    int completedCalcFlag;

private slots:
    void onDigitButtonClicked();
    void onOperatorButtonClicked();
    void onEqualButtonClicked();
    void onClearButtonClicked();
};

#endif // CALCULATOR_H

