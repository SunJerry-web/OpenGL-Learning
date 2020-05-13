# Triangle_Fan
## 代码实现
```c++
glBegin(GL_TRIANGLE_FAN);
glVertex3f(0.0f,0.0f,0.0f);
……
glEnd();
```
## 详解
假设给出v1,v2,v3,v4,v5这5个点，那么绘制出的三角形的顶点始终包含v1,另外2个顶点向后依次选取<br>
即绘制出的三角形包括(v1,v2,v3),(v1,v3,v4),(v1,v4,v5)
