#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

extern "C" {
#include "../s21_core.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

 private slots:
  void digits_numbers();
  void on_pushButton_clean_clicked();
  void on_pushButton_dot_clicked();
  void on_pushButton_back_clicked();
  void on_pushButton_pi_clicked();
  void on_pushButton_equals_clicked();
  void on_checkBox_3_stateChanged(int arg1);
  void on_pushButton_clicked();
  void on_pushButton_depozit_clicked();
};
#endif  // MAINWINDOW_H
