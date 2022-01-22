## LocalEvaluationTool2.0

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/77c9e9eb4f054fd2ac833987a0e83ab2)](https://www.codacy.com/gh/FZ-c/LocalEvaluationTool2.0/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=FZ-c/LocalEvaluationTool2.0&amp;utm_campaign=Badge_Grade)

This is a **没啥卵用的** 的本地评测姬。

1.0写得太丑所以重构了一个2.0出来~

如果使用的系统没有装G++，将不能使用评测和运行功能。（那就真的啥都做不了了.jpg）

命令：

| 命令                                    | 功能描述                                       |
| --------------------------------------- | ---------------------------------------------- |
| help                                    | 帮助说明                                       |
| set [path]                              | 设置目录（设置后将自动扫描刷新代码和数据文件） |
| recheck                                 | 重新检查必要组件（这里指G++，后续可能会增加）  |
| run [codeFile] [inputFile OutputFile]   | 运行代码文件                                   |
| changeMode [-ACM/-OI]                   | 更改评测模式                                   |
| judge [codeFile] [inputFile OutputFile] | 评测代码                                       |
| flush [-all/-code/-data]                | 重新扫描刷新代码文件/数据文件                  |
| show [-all/-code/-data]                 | 显示当前的代码文件/数据文件                    |
| ...                                     |                                                |

计划：

* 增加加密文件处理
* 多线程处理
* 增加内存消耗判断
* 增加指定限时限制
* 增加指定限内存限制
* 延伸至cf，实现本地验样例、提交等相关功能【遇到困难】
* etc...
