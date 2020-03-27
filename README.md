# 大华摄像头驱动节点



## description
大华的驱动写的ros node，使用sensor_msgs, 图片分辨率为4k

include包含所有头文件，denpends是链接库

pub一共需要20~35ms，sub需要6ms


## Usage

1. 在CMakeList.txt 162 target_link_libraries中
- 修改libImageConvert.so，libMVSDK.so，libVideoRender.so为本机中的路径
- 若出现cv::waitkey,cv::imshow等函数未定义，则删除最后一行，添加上本机opencv的链接路径

2. 使用catkin_make 编译
```
$catkin_make --pkg dahua_cam 
```

3. 运行节点
```
$rosrun dahua_cam dahua_cam
```

4. 检测节点消息
```
$rostopic list 
/camera/leftRaw
/camera/leftRaw/compressed
/camera/leftRaw/compressed/parameter_descriptions
/camera/leftRaw/compressed/parameter_updates
/camera/leftRaw/compressedDepth
/camera/leftRaw/compressedDepth/parameter_descriptions
/camera/leftRaw/compressedDepth/parameter_updates
/camera/leftRaw/theora
/camera/leftRaw/theora/parameter_descriptions
/camera/leftRaw/theora/parameter_updates
/rosout
/rosout_agg
```

5. 订阅节点
订阅 "/camera/leftRaw"或"/camera/rightRaw"节点

6. 关闭节点
Ctrl+Z

## 添加预处理

在main里，大华提供了40多个函数，可以设置触发源，修改白平衡，曝光和伽马值，目前只是加了自动曝光，如果要修改，
将对应函数加在main.cpp 的1502行开始的位置

## test （不使用catkin_make,使用cmake测试）

1. 注销掉与ros有关的语句

2. 在makefile中添加 cv 的链接路径
LINKLIBS += cv的path

3. make

4. 使用 ./test 或runTest.sh测试