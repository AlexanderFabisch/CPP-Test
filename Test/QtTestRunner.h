#ifndef QTTESTRUNNER_H
#define QTTESTRUNNER_H

#include "TestRunner.h"

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QGridLayout>
#include <QPushButton>
#include <QTreeWidget>
#include <QProgressBar>

class QtTestRunner;

class QtTestRunnerWindow : public QMainWindow
{
  Q_OBJECT

  friend class QtTestRunner;

  QWidget* centralWidget;
  QMenuBar* menubar;
  QGridLayout* mainLayout;
  QPushButton* runButton;
  QPushButton* quitButton;
  QTreeWidget* tree;
  QProgressBar* progressBar;

  TestCase* testCase;

  void setUpMenuBar();
public:
  QtTestRunnerWindow();
  void setTestCase(TestCase* testCase);
  void addResult(std::string name, TestResult& testResult);
  void addResult(QTreeWidgetItem* parent, TestResult& testResult);
private slots:
  void runTestCase();
};

class QtTestRunner : public TestRunner
{
  QApplication application;
  QtTestRunnerWindow window;
public:
  QtTestRunner(int argc, char** argv);
  ~QtTestRunner();
  virtual void run(TestCase& testCase);
  virtual void update(Observable* observable);
};

#endif // QTTESTRUNNER_H
