#include "QtTestRunner.h"

QtTestRunnerWindow::QtTestRunnerWindow()
    : centralWidget(new QWidget(this)),
      menubar(new QMenuBar(this)),
      mainLayout(new QGridLayout(centralWidget)),
      runButton(new QPushButton(tr("Run"), this)),
      quitButton(new QPushButton(tr("Quit"), this)),
      tree(new QTreeWidget(this)),
      progressBar(new QProgressBar(this))
{
  setWindowTitle("QtTestRunner");
  resize(640, 480);
  setCentralWidget(centralWidget);
  centralWidget->setLayout(mainLayout);

  setUpMenuBar();
  setMenuBar(menubar);

  connect(runButton, SIGNAL(clicked()), this, SLOT(runTestCase()));
  mainLayout->addWidget(runButton, 0, 0);
  connect(quitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
  mainLayout->addWidget(quitButton, 0, 1);

  QStringList header;
  header << "Test" << "Assertions" << "";
  tree->setHeaderItem(new QTreeWidgetItem(header));
  mainLayout->addWidget(tree, 1, 0, 1, 2);

  mainLayout->addWidget(progressBar, 2, 0, 1, 2);
  progressBar->setValue(0);
  progressBar->setRange(0, 0);
  progressBar->setHidden(true);
}

void QtTestRunnerWindow::setUpMenuBar()
{
  QMenu* fileMenu = new QMenu(tr("Program"), this);

  fileMenu->addSeparator();

  QAction* quitAct = new QAction(tr("&Quit"), this);
  quitAct->setShortcuts(QKeySequence::Close);
  quitAct->setStatusTip(tr("Quit the program"));
  connect(quitAct, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
  fileMenu->addAction(quitAct);

  menubar->addMenu(fileMenu);

  QMenu* runMenu = new QMenu(tr("&Run"), this);

  QAction* runAct = new QAction(tr("&Run test case"), this);
  runAct->setStatusTip(tr("Runs the test case"));
  connect(runAct, SIGNAL(triggered()), this, SLOT(runTestCase()));
  runMenu->addAction(runAct);

  menubar->addMenu(runMenu);
}

void QtTestRunnerWindow::setTestCase(TestCase* testCase)
{
  this->testCase = testCase;
}

void QtTestRunnerWindow::runTestCase()
{
  testCase->run();
  tree->collapseAll();
}

void QtTestRunnerWindow::addResult(std::string name, TestResult& testResult)
{
  QStringList content;
  content << QString(name.c_str()) << QString::number(testResult.successful) + "/" + QString::number(testResult.total) << "";
  QTreeWidgetItem* item = new QTreeWidgetItem(content);
  if(testResult.successful < testResult.total)
    item->setBackground(1, QColor::fromRgb(255, 0, 0));
  tree->addTopLevelItem(item);
  tree->resizeColumnToContents(0);
  addResult(item, testResult);
  progressBar->setMaximum(progressBar->maximum() + testResult.total);
  progressBar->setValue(progressBar->value() + testResult.successful);
  progressBar->setHidden(false);
}

void QtTestRunnerWindow::addResult(QTreeWidgetItem* parent, TestResult& testResult)
{
  std::list<TestResult>::iterator r = testResult.testResults.begin();
  std::list<std::string>::iterator n = testResult.testResultNames.begin();
  for(; r != testResult.testResults.end(); r++, n++)
  {
    QStringList content;
    content << QString(n->c_str()) << QString::number(r->successful) + "/" + QString::number(r->total) << "";
    QTreeWidgetItem* item = new QTreeWidgetItem(content);
    if(r->successful < r->total)
      item->setBackground(0, QColor::fromRgb(255, 0, 0));
    parent->addChild(item);
    addResult(item, *r);
  }
  std::list<AssertResult>::iterator a = testResult.assertResults.begin();
  for(; a != testResult.assertResults.end(); a++)
  {
    QStringList content;
    content << QString(a->success ? "Success" : "Failure") << QString(a->file.c_str()) + QString("(") + QString::number(a->line) + QString(")") << QString(a->assertion.c_str());
    QTreeWidgetItem* item = new QTreeWidgetItem(content);
    if(a->success)
      item->setBackground(0, QColor::fromRgb(0, 255, 0));
    else
      item->setBackground(0, QColor::fromRgb(255, 0, 0));
    parent->addChild(item);
  }
  tree->expandAll();
  tree->resizeColumnToContents(1);
}

QtTestRunner::QtTestRunner(int argc, char** argv) : application(argc, argv)
{}

void QtTestRunner::run(TestCase& testCase)
{
  testCase.testResult.detach(this);
  testCase.testResult.attach(this);
  window.setTestCase(&testCase);
  window.show();
  application.exec();
}

void QtTestRunner::update(Observable* observable)
{
  TestResult& testResult = (TestResult&) *observable;
  std::list<TestResult>::iterator r = testResult.testResults.begin();
  std::list<std::string>::iterator n = testResult.testResultNames.begin();
  for(int i = 0; i < testResult.lastInserted; i++, r++, n++)
    window.addResult(*n, *r);
}
