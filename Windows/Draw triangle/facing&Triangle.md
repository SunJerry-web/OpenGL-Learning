# 本文为对facing.cpp代码的解读
## 我们先来了解一下怎么绘制三角形的。
```cpp
  glBegin(GL_TRIANGLES);
  glColor4ub(255, 230, 18, 255);
  glVertex3f(0.0f, 0.0f, -10.0f);
  glColor4ub(29, 40, 238, 255);
  glVertex3f(-5.0f, 0.0f, -10.0f);
  glColor4ub(180, 20, 100, 255);
  glVertex3f(0.0, 4.0f, -10.0f);
  glEnd();
```
上述代码描述了如何绘制一个简单三角形，我们需要在`glBegin(GL_TRIANGLES)`和`glEnd()`中间输入3个点或者3n个点，每3个点，绘制一个三角形
<br>
## 面剔除问题
### 前言
面剔除(Face Culling)可以用来提升性能。<br>
在特定的硬件上渲染的三角面片是有限的，所以，可以通过减少不必要的三角形面片，来提升性能。<br>
假如说有一个立方体，正常情况下，我们最多只能看到3个面（在不透明的情况下），那么后面看不到的面就可以使用面剔除的方式剔除。<br>

### 如何进行面剔除
在进行面剔除时，我们应该知道哪些面属于前面的面(Front face)，哪些面属于后面的面(Back face)，然后决定丢弃前面的面，还是后面的面。OpenGL中通过判断顶点连接的顺序(Winding Order)来判断这个面是Front face还是Back face。<br>

在前面的绘制三角形的代码中，我们输入了3个点的坐标(0.0,0.0)，(-5.0,0.0)，(0.0,4.0)（这里用不到z轴的坐标，所以先忽略z轴的存在）。OpenGL在绘制三角形的时候，3个顶点一定有一个顺序，可能是顺时针也可能是逆时针。我们可以看到这里3个顶点的顺序是`顺时针`的，这里我们并没有开启面剔除的状态，开启之后，你就有1/2的概率看不到这个三角形了。<br>
#### 如何开启面剔除：glEnable(GL_CULL_FACE)，默认情况下为glDisable(GL_CULL_FACE);
`OpenGL中默认Front face 为逆时针，Back face为顺时针`<br>
可以看出上面绘制三角形的代码是在后面（Back Face）的。<br>
运行facing.cpp，我们可以看到剔除背面的效果（facing.cpp只是在Tiangle.cpp的基础上增加了glEnable(GL_CULL_FACE)这一句代码，即开启面剔除，这里会默认剔除掉背面）<br>
我们可以使用glCullFace函数来选择要剔除哪一面
```cpp
  glCullFace(GL_BACK);
  glCullFace(GL_FRONT);
  glCullFace(GL_FRONT_AND_BACK);
```
默认逆时针是正面，我们也可以使用glFrontFace来设置正面是顺时针还是逆时针：
```cpp
 glFrontFace(GL_CCW); //逆时针是正面
 glFrontFace(GL_CW);  //顺时针是正面
```

转载自CSDN@RalfNick的[博客](https://blog.csdn.net/u011371324/article/details/77915663)
 
