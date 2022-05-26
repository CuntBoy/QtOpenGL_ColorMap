#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "windowcenterwidget.h"
#include <QMainWindow>

// widget bass class
// menu bar 
// tool bar
// center window
// status bar

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

    MainWindow(const MainWindow&) = delete;
    MainWindow(const MainWindow&&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&&) = delete;

    ~MainWindow() override;

protected:
    // center window -- OpenGL render widget
    WindowCenterWidget* m_centerWindow;

    QMenu* m_fileMenu;
    QMenu* m_helpMenu;
    QMenu* m_editMenu;

protected:
    virtual void initMenuBar();    // init menu bar
    virtual void initToolBar();    // init tool bar
    virtual void initStatusBar();  // init status bar
};
#endif // MAIN_WINDOW_H
