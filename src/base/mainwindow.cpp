#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_centerWindow(nullptr)
    , m_fileMenu(nullptr)
    , m_helpMenu(nullptr)
    , m_editMenu(nullptr)
{
    resize(QSize(640, 480));
    setWindowTitle("ColorMap Window");

    MainWindow::initMenuBar();  // 添加菜单
}

MainWindow::~MainWindow()
{
    if (m_centerWindow)
    {
        delete m_centerWindow;
        m_centerWindow = nullptr;
    }
}

void MainWindow::initMenuBar()
{
    // 当前窗口的菜单栏 
    QMenuBar* currentMenuBar = menuBar();

    // file menu
    m_fileMenu = new QMenu("File(&F)", currentMenuBar);
    currentMenuBar->addMenu(m_fileMenu);

    // edit menu
    m_editMenu = new QMenu("Edit(&E)", currentMenuBar);
    currentMenuBar->addMenu(m_editMenu);
    //help menus
    m_helpMenu = new QMenu("Help(&H)", currentMenuBar);
    currentMenuBar->addMenu(m_helpMenu);

}

void MainWindow::initToolBar()
{


}

void MainWindow::initStatusBar()
{

}

