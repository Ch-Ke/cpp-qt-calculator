#include "calculator.h"
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <QRegularExpression>
#include <QVector>
#include <QTextStream>

Calculator::Calculator(QWidget *parent) : QWidget(parent){
  setupUI();
}

Calculator::~Calculator(){}

void Calculator::setupUI(){
  display = new QLineEdit(this);
  display->setReadOnly(true);
  layout = new QGridLayout(this);

  for (size_t i = 0; i < 9; i++) {
    QPushButton *button = new QPushButton(QString::number(i+1), this);
    layout->addWidget(button, i/3, i%3);
    connect(button, &QPushButton::clicked, this, &Calculator::onDigitButtonClicked);
  }

  QPushButton *button = new QPushButton(QString::number(0), this);
  layout->addWidget(button,3,1);
  connect(button, &QPushButton::clicked, this, &Calculator::onDigitButtonClicked);

  QPushButton *clearButton = new QPushButton("C", this);
  layout->addWidget(clearButton,3,0);
  connect(clearButton, &QPushButton::clicked, this, &Calculator::onClearButtonClicked);

  QPushButton *equalButton = new QPushButton("=", this);
  layout->addWidget(equalButton,3,2);
  connect(equalButton, &QPushButton::clicked, this, &Calculator::onEqualButtonClicked);

  QPushButton *plusButton = new QPushButton("+", this);
  layout->addWidget(plusButton,0,3);
  connect(plusButton, &QPushButton::clicked, this, &Calculator::onOperatorButtonClicked);

  QPushButton *minusButton = new QPushButton("-", this);
  layout->addWidget(minusButton,1,3);
  connect(minusButton, &QPushButton::clicked, this, &Calculator::onOperatorButtonClicked);
  
  QPushButton *multiplyButton = new QPushButton("*", this);
  layout->addWidget(multiplyButton,2,3);
  connect(multiplyButton, &QPushButton::clicked, this, &Calculator::onOperatorButtonClicked);
  
  QPushButton *divideButton = new QPushButton("/", this);
  layout->addWidget(divideButton,3,3);
  connect(divideButton, &QPushButton::clicked, this, &Calculator::onOperatorButtonClicked);
  
  setLayout(layout);
  val = 0;
  buffer = 0;
}

void Calculator::onDigitButtonClicked(){
  QPushButton *button = qobject_cast<QPushButton*>(sender());
  if (button) {
    display->setText(display->text() + button->text());
  }
}

void Calculator::onOperatorButtonClicked(){
  QPushButton *button = qobject_cast<QPushButton*>(sender());
  if (button && display->text()!= NULL) {
    display->setText(display->text() + " " + button->text() + " ");
  }
}

void Calculator::onEqualButtonClicked(){
  performCalculation(); 
}

void Calculator::onClearButtonClicked(){
  display->clear();
}

void Calculator::performCalculation(){
  QString expression = display->text();
  QStringList list1 = expression.split(' ');
  int total = list1[0].toInt();
  int op = 0;
  for(int i = 1; i < list1.size(); i++){
    if(list1[i] == '+'){
      op = 1;
    } else if(list1[i] == '-'){
      op = 2;
    } else if(list1[i] == '*'){
      op = 3;
    } else if(list1[i] == '/'){
      op = 4;
    } else {
      switch (op) {
        case 1:
          total += list1[i].toInt();
          break;
        case 2:
          total -= list1[i].toInt();
          break;
        case 3:
          total *= list1[i].toInt();
          break;
        case 4:
          total /= list1[i].toInt();
          break;
        }
      }
    }
  display->setText(QString::number(total));
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setStyle("Windows");
    Calculator calculator;
    QPushButton->setFixedSize();
    calculator.show();
    return app.exec();
}

