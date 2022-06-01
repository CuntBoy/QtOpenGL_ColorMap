//
// Created by RanLH on 6/1/2022.
//

#ifndef COLORMAP_RENDERTHREAD_H
#define COLORMAP_RENDERTHREAD_H

#include <QObject>
#include <QOpenGLFunctions_4_5_Core>

class RenderThread:public QObject,protected  QOpenGLFunctions_4_5_Core
{
    RenderThread()
    {

    }
    ~RenderThread()
    {

    }


};


#endif //COLORMAP_RENDERTHREAD_H
