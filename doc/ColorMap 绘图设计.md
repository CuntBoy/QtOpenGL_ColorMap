# Color Map 绘图设计 

## 1、第一步是将数据构造好 并存储副本(或者使用智能指针)到`ColorMap`的类中 

- 需要一个专门存储数据的类
  - 重写此类的拷贝构造函数(不使用智能指针) 

## 2、调用绘制的函数，设置数据给QOpenGLWidget

- 进入OpenGL的初始化

## 3、窗口调用show，进入paint，显示图像





---

# 关于数据类(Data Set)的设计

# `class DataSet` -- Base Class 

## 派生得到 ：

- #### Color Map Data(目前只做这个部分)

- #### Surf Data

- #### ......