#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "windowcenterwidget.h"

#include <QMainWindow>

// 窗口基类

// -- 菜单栏
// 工具栏
// center window
// 状态栏

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    // center window
    WindowCenterWidget * center_window;

    QMenu * file_menu;
    QMenu * help_menu;
    QMenu * edit_menu;


private:
    void initMenuBar();    // 初始化 菜单栏
    void initToolBar();    // 初始化 工具栏
    void initStatusBar();  // 初始化 状态栏

signals:

public slots:




};
#endif // MAINWINDOW_H
