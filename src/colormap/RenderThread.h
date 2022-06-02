//
// Created by RanLH on 6/1/2022.
//

#ifndef COLORMAP_RENDERTHREAD_H
#define COLORMAP_RENDERTHREAD_H

#include <QThread>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLContext>
#include <memory>
#include <QSurface>
#include <QMutex>

class RenderThread :public QThread, protected  QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    RenderThread(std::shared_ptr<QSurface> surface, QOpenGLContext* mainContext, QObject* parent);

    ~RenderThread() override;
    void run() override;


private:
    std::unique_ptr<QOpenGLContext> m_renderContext{ nullptr };
    QOpenGLContext* m_mainContext{ nullptr };
    std::shared_ptr<QSurface> m_surface;

    bool m_running{ true };
    QMutex m_mutex;
    int m_width{ 1000 };
    int m_height{ 800 };

signals:
    void  imageReady();


};


#endif //COLORMAP_RENDERTHREAD_H
