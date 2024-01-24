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