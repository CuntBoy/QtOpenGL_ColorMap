//
// Created by RanLH on 6/1/2022.
//

#include "RenderThread.h"

using std::make_unique;

RenderThread::RenderThread(std::shared_ptr<QSurface> surface, QOpenGLContext *mainContext, QObject *parent)
    : QThread(parent)
    , m_surface(surface)  // 使用下面创建的上下文 将结果渲染到这个虚拟的平面上
    , m_mainContext(mainContext)
{
    m_renderContext =make_unique<QOpenGLContext>();
    m_renderContext->setFormat(m_mainContext->format());
    m_renderContext->setShareContext(m_mainContext);
    m_renderContext->create();
    m_renderContext->moveToThread(this);

}

RenderThread::~RenderThread()
{
    m_running = false;
    wait();

}

void RenderThread::run()
{
    m_renderContext->makeCurrent(m_surface.get());
    while (m_running)   // 一直更新渲染的内容  
    {
        int width = 0;
        int height = 0;
        {
            QMutexLocker lock(&m_mutex);
            width = m_width;
            height = m_height;
        }

        // 调用一次渲染
        // TODO
        // 更新共享的纹理
        // TODO

        // emit imageReady();
    }
}
