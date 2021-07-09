#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(QSize(640,480));
    setWindowTitle("ColorMap Window");

    // center winodw
    center_window = new ColorMapWidget(this);
    center_window->setAutoFillBackground(true);  // 自动填充背景
    setCentralWidget(center_window);

    initMenuBar();  // 添加菜单
    initToolBar();
    initStatusBar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initMenuBar()
{
    QMenuBar * currentMenuBar = menuBar();

    // file menu
    file_menu = new QMenu("File(&F)",currentMenuBar);
    currentMenuBar->addMenu(file_menu);


}

void MainWindow::initToolBar()
{


}

void MainWindow::initStatusBar()
{

}

