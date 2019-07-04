# 一个代码书生成器（做模板用）

## 运行&开发环境

- win10可以（我也只验证了win10）

- python3

- TexLive 2019

- VS Code LaTeX Workshop

我写了下面两篇拙记，解释了我是如何开始的。

[Latex 傻瓜式入门](https://www.cnblogs.com/tieway59/p/11123628.html)

[LaTeX 傻瓜式起步](https://www.cnblogs.com/tieway59/p/11125628.html)

## 使用方法

1. 把你所有需要的代码都丢到templates文件夹里。
2. 运行build.exe。
3. 自己想办法编译：\buildUtils\LaTeX\context.tex
4. context.pdf 就是结果了。

## 已知好处

- win10可用。（因为···懒得配linux···）
- 方便修改和完善的板子，你代码随时可以改，重新构建也很简单。
- 减少排版和复制粘贴的压力。
- 文件目录即是内容目录。

## 已知缺陷

- 标题只能分到LaTeX默认的三级。
- 一些奇怪的路径可能导致出错。
- 可能会因为编码的一些问题导致显示异常。
- 小部分排版折行的效果不太理想。
- 你在cpp文件里写不符合语法的东西会展现出不符合语法的样式。

## 鸣谢&参考

[**ACM-template**](https://github.com/Strive-for-excellence/ACM-template) 本项目的模板来自于这个大佬的仓库，也是因为他的模板我win上面运行不了，所以才有了我这个项目。

[**C++遍历目录和文件夹**](https://www.cnblogs.com/tinaluo/p/6824674.html) 我的build.cpp的代码主要学习了这篇博客的写法，虽然我写的很丑就是了。希望以后还会有改进的机会QAQ。