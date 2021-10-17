#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(QSize(640,480));
    setWindowTitle("ColorMap Window");

    // center winodw
    //center_window = new WindowCenterWidget(this);
    //center_window->setAutoFillBackground(true);  // 自动填充背景
    //setCentralWidget(center_window);

    initMenuBar();  // 添加菜单
    initToolBar();
    initStatusBar();

    // init
    center_window = nullptr;
}

MainWindow::~MainWindow()
{
    if(center_window)
    {
        delete center_window;
        center_window = nullptr;

    }
}

void MainWindow::initMenuBar()
{
    QMenuBar * currentMenuBar = menuBar();

    // file menu
    file_menu = new QMenu("File(&F)",currentMenuBar);
    currentMenuBar->addMenu(file_menu);

    // edit menu
    edit_menu = new QMenu("Edit(&E)",currentMenuBar);
    currentMenuBar->addMenu(edit_menu);
    //help menus
    help_menu = new QMenu("Help(&H)",currentMenuBar);
    currentMenuBar->addMenu(help_menu);

}

void MainWindow::initToolBar()
{


}

void MainWindow::initStatusBar()
{

}

