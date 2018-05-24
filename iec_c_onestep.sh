#!/bin/bash

if [ -n "$1" ]; then
	./iec_compiler "$1"
else
	echo "未指定输入文件，默认编译test/test_robotv3.txt!"
	./iec_compiler ./test/test_robotv3.txt
fi

./translator code.txt
cp exec.obj ../../../wenjie/Robot-Controller/
echo "exec.obj文件已生成，拷贝至/home/ychj/wenjie/Robot-Controller/目录下"
