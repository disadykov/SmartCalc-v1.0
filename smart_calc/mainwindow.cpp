#include "mainwindow.h"

#include <QLineEdit>
#include <QVector>

#include "credit_calc.h"
#include "depozit_calc.h"
#include "ui_mainwindow.h"

extern "C" {
#include "../s21_core.h"
#include "../s21_err_base.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_zero, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_one, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_two, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_three, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_four, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_five, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_six, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_seven, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_eight, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_nine, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_left, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_right, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  ui->textEdit_input->setText(ui->textEdit_input->toPlainText() +
                              button->text());
  ui->textEdit_input->setAlignment(Qt::AlignRight);
}

void MainWindow::on_pushButton_clean_clicked() {
  ui->textEdit_input->clear();
  ui->textEdit_input->setAlignment(Qt::AlignRight);
  ui->lineEdit_x->setText("0.0");
}

void MainWindow::on_pushButton_dot_clicked() {
  ui->textEdit_input->setText(ui->textEdit_input->toPlainText() + '.');
  ui->textEdit_input->setAlignment(Qt::AlignRight);
}

void MainWindow::on_pushButton_back_clicked() {
  QLineEdit tmp_str;
  tmp_str.setText(ui->textEdit_input->toPlainText());
  tmp_str.backspace();
  ui->textEdit_input->setText(tmp_str.text());
  ui->textEdit_input->setAlignment(Qt::AlignRight);
}

void MainWindow::on_pushButton_pi_clicked() {
  ui->textEdit_input->setText(ui->textEdit_input->toPlainText() +
                              "3.14159265358979323846");
  ui->textEdit_input->setAlignment(Qt::AlignRight);
}

void MainWindow::on_pushButton_equals_clicked() {
  setlocale(LC_NUMERIC, "C");
  ui->widget->removeGraph(0);
  QString tmp_x;
  tmp_x = ui->lineEdit_x->text();
  const QByteArray stringData = tmp_x.toUtf8();
  char x[256];
  x[qMin(255, stringData.size())] = '\0';
  std::copy(stringData.constBegin(),
            stringData.constBegin() + qMin(255, stringData.size()), x);

  QString tmp_exp;
  tmp_exp = ui->textEdit_input->toPlainText();
  const QByteArray stringData_exp = tmp_exp.toUtf8();
  char expression[1024] = "";
  expression[qMin(1023, stringData_exp.size())] = '\0';
  std::copy(stringData_exp.constBegin(),
            stringData_exp.constBegin() + qMin(1023, stringData_exp.size()),
            expression);

  double result = NAN;
  char result_str[1024];
  int error_code;

  result = s21_calculation(expression, x, &error_code);
  strcpy(result_str, "");
  if (error_code != ERROR_NO) {
    strncpy(result_str, s21_strerror(error_code),
            strlen(s21_strerror(error_code)) + 1);
    ui->textEdit_input->setText(result_str);
  } else {
    if (ui->checkBox_2->isChecked()) {
      double minX, maxX, minY, maxY;
      QVector<double> xx, yy;

      minX = ui->doubleSpinBox_minX->value();
      maxX = ui->doubleSpinBox_maxX->value();
      minY = ui->doubleSpinBox_minY->value();
      maxY = ui->doubleSpinBox_maxY->value();

      double X = minX;
      double step = (maxX - minX) / 10000;
      double min = 1000000;
      double max = -10000000;
      double result_graf;
      QString tmp_expression;
      tmp_expression = ui->textEdit_input->toPlainText();

      while (X < maxX) {
        xx.push_back(X);
        char graf_x[256] = "";
        sprintf(graf_x, "%lf", X);

        const QByteArray stringData_expression = tmp_expression.toUtf8();
        char expression_grf[1024] = "";
        expression_grf[qMin(1023, stringData_expression.size())] = '\0';
        std::copy(stringData_expression.constBegin(),
                  stringData_expression.constBegin() +
                      qMin(1023, stringData_expression.size()),
                  expression_grf);

        result_graf = s21_calculation(expression_grf, graf_x, &error_code);
        yy.push_back(result_graf);

        if (min > result_graf && !isinf(result_graf)) min = result_graf;
        if (max < result_graf && !isinf(result_graf)) max = result_graf;
        X += step;
      }

      if (min < -1000000) min = -1000000;
      if (max > 1000000) max = 1000000;

      ui->widget->xAxis->setRange(minX * 1.005, maxX * 1.005);
      ui->widget->yAxis->setRange(minY * 1.005, maxY * 1.005);

      if (ui->checkBox_3->isChecked()) {
        ui->widget->yAxis->setRange(min * 1.005, max * 1.005);
        ui->doubleSpinBox_maxY->setValue(max * 1.005);
        ui->doubleSpinBox_minY->setValue(min * 1.005);
      } else {
        ui->doubleSpinBox_maxY->update();
        ui->doubleSpinBox_minY->update();
        ui->widget->yAxis->setRange(minY * 1.005, maxY * 1.005);
      }

      ui->widget->addGraph();
      ui->widget->graph(0)->addData(xx, yy);
      ui->widget->replot();

    } else {
      if (ui->checkBox->isChecked()) {
        sprintf(result_str, "%.7lf", result);
      } else {
        sprintf(result_str, "%.15lf", result);
      }
      ui->textEdit_input->setText(result_str);
    }
  }
  ui->textEdit_input->setAlignment(Qt::AlignRight);
}

void MainWindow::on_checkBox_3_stateChanged(int arg1) {
  if (arg1) {
    ui->doubleSpinBox_maxY->setEnabled(false);
    ui->doubleSpinBox_minY->setEnabled(false);
  } else {
    ui->doubleSpinBox_maxY->setEnabled(true);
    ui->doubleSpinBox_minY->setEnabled(true);
  }
}

void MainWindow::on_pushButton_clicked() {
  credit_calc credit_window;
  credit_window.setModal(true);
  credit_window.exec();
}

void MainWindow::on_pushButton_depozit_clicked() {
  depozit_calc depozit_window;
  depozit_window.setModal(true);
  depozit_window.exec();
}
