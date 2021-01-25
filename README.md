参考https://github.com/jackdent/cs265-lsm-tree

把定长int型键值对改成分离式kv,其中key为定长8字节，value长度无限制。
改写了merge中的next方法。

需要boost库支持

使用方法参照test-lsm.cpp
本地生成文件见config.h中BASEDIR

多线程

key = 8 Byte
value = 128 Byte
