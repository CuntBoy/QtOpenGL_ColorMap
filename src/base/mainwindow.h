#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "windowcenterwidget.h"
#include <QMainWindow>

// 窗口基类
// 菜单栏
// 工具栏
// center window
// 状态栏

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    MainWindow(const MainWindow &) = delete;
    MainWindow(const MainWindow &&) = delete;
    MainWindow& operator=(const MainWindow &) = delete;
    MainWindow& operator=(const MainWindow &&) = delete;

    ~MainWindow() override;

protected:
    // center window -- OpenGL绘制窗口
    WindowCenterWidget * m_centerWindow;

    QMenu * m_fileMenu;
    QMenu * m_helpMenu;
    QMenu * m_editMenu;

protected:
    virtual void initMenuBar();    // 初始化 菜单栏
    virtual void initToolBar();    // 初始化 工具栏
    virtual void initStatusBar();  // 初始化 状态栏
};
#endif // MAIN_WINDOW_H
