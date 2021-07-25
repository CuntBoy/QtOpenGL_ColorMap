# Color Map
- draw color map use OpenGL(`VAO VBO EBO`)

<p style="color:red">一个使用Qt+OpenGL的绘图库</p> 

_展示均匀数据与非均匀数据_

---

### List:

- [x] 总体设计,不仅限于Colormap(后期的扩展)

---

- [x] 窗口基类 -- `MainWindow`
  - [x] 菜单栏 
  - [x] 工具栏
  - [x] 状态栏
- [ ] 中心窗口基类 -- `CenterWidget(QtOPenGLWidget)`
  - [ ] 初始化
  - [ ] 着色器的创建
- [ ] `class ColorScale`
  - [ ] 显示的信息
  - [ ] 指数显示 
  - [ ] 区域颜色更改(随之更新图形)

- [x]  `class DrawData`
  - [ ] class Color Map Data
- [ ] 离屏渲染 -- 将渲染的结果显示到窗口上









