# Mini-Word
a text editor
## 说明
- 文件
打开程序后自动新建文件，可直接对此文件进行编辑。 可通过菜单栏-->文件进行 新建文件 打开文件 保存 另存为 退出文件 
- 编辑
可通过菜单栏-->编辑进行查找及替换 可以通过鼠标按键定位光标 可通过方向键控制光标 定位光标后按键即可输入 支持中文以及英文的输入  支持删除键 delete键 回车键等按键。
块操作及热键
按住鼠标拖动可框选区域进行块操作，支持块删除和替换。可以用快捷键CTRL+C 、CTRL+V 进行块复制粘贴操作。
支持热键Home End PageUp PageDown
同时也支持其他热键CTRL+N 新建 ，CTRL+O 打开，CTRL+S 保存，CTRL+W关闭，CTRL+F查找，CTRL+H替换。
（新建CTRL+N 打开等文件快捷键是调用QT自带的快捷键设置功能实现   复制粘贴的热键 通过判断CTRL键是否按下已经与C V的组合来进行判断）
- 查找字符/串：提示用户输入要查找的字符串，从当前光标处向后定位，找到时光标置于首字符之前。
- 替换字符/串：提示用户输入原字符串和新字符串，从当前光标处向后定位，找到时光标置于首字符之前，由用户对是否替换进行确认。

## 展示
![image](https://user-images.githubusercontent.com/34685742/158107717-0ed8dba9-81eb-493c-a204-296acf1276e7.png)
