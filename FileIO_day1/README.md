# Linux IO Day 1

## 学习内容

Linux 文件 IO 基础系统调用：

- open()
- read()
- write()
- close()

## 实践项目

### file_copy

使用 Linux 系统调用实现文件复制。

实现流程：

1. 使用 open() 打开源文件
2. 使用 open() 创建目标文件
3. 使用 read() 循环读取数据
4. 使用 write() 将数据写入目标文件
5. 使用 close() 关闭文件描述符

## 编译运行

```bash
g++ -std=c++17 -Wall -Wextra -g file_copy.cpp -o file_copy

./file_copy source.txt target.txt