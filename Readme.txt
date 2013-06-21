适用环境：Linux

配置环境：
安装boost 到 /usr/local/lib, /usr/local/include
将libNLPIR.so 放入/usr/lib文件夹下或者/usr/local/lib下
	如果放在/usr/local/lib下，可能无法搜索到
	需要创建或打开etc/id.so.conf 添加/usr/local/lib 保存 然后运行ldconfig
安装mysql并启动mysql service
	/lib所有文件加入到/usr/local/lib下 /include下的h文件move到/usr/local/include下

现在mysql中创建数据库 名称叫做：interninfo
将interninfo.sql导入mysql数据库中

运行：
编译：make
清理：make clean
./web_extractor -options ...
