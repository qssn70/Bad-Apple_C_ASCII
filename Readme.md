# Bad Apple Animation  

## 设计思路：
1.先将Bad Apple视频分离成图像  
2.再将图像转码为ASCII保存到文件中  
3.1 Windows版本使用C++编写代码：读取编码文件，配合延时函数调整显示速度；调用Windows的PlaySound API来播放音频  
3.2 Linux版本使用shell，易上手  
4.最后将C++代码编译成exe文件即可食用  

## 鸣谢：
[FFmpeg](https://ffmpeg.org/)  
[Ascii-image-converter](https://github.com/TheZoraiz/ascii-image-converter)  
[PlaySound](https://learn.microsoft.com/zh-cn/windows/win32/multimedia/using-playsound-to-play-system-sounds)  

骑士斯诺70 2025年3月8日  
