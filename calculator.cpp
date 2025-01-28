#include "calculator.h"
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QStringList>

Calculator::Calculator(QWidget *parent) : QWidget(parent){
  setupUI();
}

Calculator::~Calculator(){}

void Calculator::setupUI(){
  display = new QLineEdit(this);
  display->setReadOnly(true);
  layout = new QGridLayout(this);
  completedCalcFlag = 0;
  
  // init number buttons 1 through 9
  for (size_t i = 0; i < 9; i++) {
    QPushButton *button = new QPushButton(QString::number(i+1), this);
    layout->addWidget(button, i/3, i%3);
    connect(button, &QPushButton::clicked, this, &Calculator::onDigitButtonClicked);
  }
  
  // init number button 0
  QPushButton *button = new QPushButton(QString::number(0), this);
  layout->addWidget(button,3,1);
  connect(button, &QPushButton::clicked, this, &Calculator::onDigitButtonClicked);

  // init clear button
  QPushButton *clearButton = new QPushButton("C", this);
  layout->addWidget(clearButton,3,0);
  connect(clearButton, &QPushButton::clicked, this, &Calculator::onClearButtonClicked);

  // init equal button
  QPushButton *equalButton = new QPushButton("=", this);
layout->addWidget(equalButton,3,2);
  connect(equalButton, &QPushButton::clicked, this, &Calculator::onEqualButtonClicked);

  // init operator buttons
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
}

// handle behaviour for digit button clicked.
// checks if the current text display holds a previously calculated answer and wipes the screen if true
void Calculator::onDigitButtonClicked(){
  QPushButton *button = qobject_cast<QPushButton*>(sender());
  if (button && completedCalcFlag == 0) {
    display->setText(display->text() + button->text());
  } else {
    display->clear();
    display->setText(display->text()+button->text());
    completedCalcFlag = 0;
  }
}

// handles behaviour for operator button clicked.
void Calculator::onOperatorButtonClicked(){
  QPushButton *button = qobject_cast<QPushButton*>(sender());
  if (button && !display->text().isEmpty()) {
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
  QStringList expressionList = expression.split(' ');
  
  // calc requires at least 3 elements to run (2 nums, 1 operator)
  if(expressionList.size() < 3){
    return;
  }

  int calcTotal = expressionList[0].toInt();
  int operatorCode = 0;
 
  // main logic for calculation, current calculator logic exists as a placeholder for GUI app development learning.
  // more efficient logic to be implemented soon.
  // ideas for calculator logic include: recursive descent parser, infix to postfix conversion (shunting yard)
  for(int i = 1; i < expressionList.size(); i++){
    if(expressionList[i] == '+'){
      operatorCode = 1;
    } else if(expressionList[i] == '-'){
      operatorCode = 2;
    } else if(expressionList[i] == '*'){
      operatorCode = 3;
    } else if(expressionList[i] == '/'){
      operatorCode = 4;
    } else {
      int num = expressionList[i].toInt();
      switch (operatorCode) {
        case 1: 
          calcTotal += num;
          break;
        case 2: 
          calcTotal -= num;
          break;
        case 3: 
          calcTotal *= num;
          break;
        case 4: 
          if(num != 0){
            calcTotal /= num;
          } else {
            display->setText("Error");
            return;
          }
          break;
        }
      }
    }
  display->setText(QString::number(calcTotal));
  completedCalcFlag = 1;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setStyle("Windows");
    Calculator calculator;
    calculator.show();
    return app.exec();
}

