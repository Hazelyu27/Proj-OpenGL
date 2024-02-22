# 笔记
## texture
要注意：
```c++
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
```
要显示两张图片混合的效果，要用rgba的形式，才能保证上面那张图片是透明的。读入也是要png格式的。

另外，怎么判断那张图片在上，那张在下？
```c++
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 0); // 手动设置
    ourShader.setInt("texture1", 1); // 或者使用着色器类设置
```
0，1表示了图片的位置。

## glVertexAttribPointer参数含义：

```
void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
eg.
// position数据

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

// texture数据
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
```
index：指定要设置的顶点属性的索引。这个索引对应于顶点着色器中的输入变量。

size：指定每个顶点属性的组成元素数量。例如，对于一个vec3类型的顶点属性，size应该为3。

type：指定顶点属性数据的元素类型。可以使用以下类型之一：GL_BYTE、GL_UNSIGNED_BYTE、GL_SHORT、GL_UNSIGNED_SHORT、GL_INT、GL_UNSIGNED_INT、GL_HALF_FLOAT、GL_FLOAT、GL_DOUBLE等。

normalized：指定是否将非浮点类型的数据标准化到固定的范围。如果设置为GL_TRUE，则数据会被标准化到[-1, 1]（有符号整数类型）或[0, 1]（无符号整数类型）。如果设置为GL_FALSE，则数据会被直接转换为浮点类型。

stride：指定连续顶点属性之间的字节偏移量。如果顶点属性是紧密打包的（即没有间隔），则可以将stride设置为0。如果顶点属性之间有间隔，则需要指定正确的偏移量。

pointer：指定顶点属性数据的起始指针。它可以是缓冲区对象的偏移量，也可以是指向内存中数据的指针。


## glDrawArrays 和glDrawElements的区别
glDrawArrays和glDrawElements是OpenGL中两种常用的绘制函数，用于渲染几何图元。它们之间的区别在于使用的索引数据的形式以及如何指定顶点数据。

glDrawArrays：

索引数据：glDrawArrays函数不使用索引数据。它按照顶点数据数组的顺序绘制图元。
顶点数据指定：使用glVertexAttribPointer函数指定顶点属性数据，并使用glEnableVertexAttribArray启用顶点属性数组。
glDrawElements：

索引数据：glDrawElements函数使用索引数据来确定要绘制的顶点顺序。索引数据存储在一个索引缓冲对象中。
顶点数据指定：使用glVertexAttribPointer函数指定顶点属性数据，并使用glEnableVertexAttribArray启用顶点属性数组。
索引数据指定：使用glBindBuffer将索引缓冲对象绑定到GL_ELEMENT_ARRAY_BUFFER目标，然后使用glBufferData或glBufferSubData等函数指定索引数据。
使用glDrawArrays时，顶点数据按照其出现在顶点数组中的顺序进行渲染。这意味着相邻的顶点将成为渲染的连续顶点。例如，如果有一个三角形，顶点数组中的前三个顶点将被渲染为一个三角形。

而使用glDrawElements时，索引数据确定了顶点的顺序。每个索引值对应于顶点数据数组中的一个顶点。这意味着顶点可以在渲染过程中重复使用，通过使用索引来引用它们。这种使用索引的方式可以减少存储和传输的数据量，尤其在有大量重复顶点的情况下。

总结起来，glDrawArrays适合用于绘制没有顶点重用的简单几何图元，而glDrawElements适合用于绘制具有顶点重用的复杂几何图元。具体选择哪种函数取决于你的应用场景和需要绘制的图元类型。