record-play.c功能：
通过麦克录制声音10s，在当前文件夹下保存为sound.wav文件，并在录音完毕后提示是否播放该录音。

编译：
在PC linux shell 输入命令： arm-linux-gnueabihf-gcc record-play.c -o record-play
生成可执行文件：record-play 


运行：
在开发板先打开mic输入通道，命令如下：
amixer sset 'Left PGA Mixer Mic3L' on	  
amixer sset 'Left PGA Mixer Mic3R' on     
amixer sset 'Right PGA Mixer Mic3L' on    
amixer sset 'Right PGA Mixer Mic3R' on 

调节输出音量大小，命令如下：
amixer cset name='PCM Playback Volume' 100%,100%
amixer cset name='HP DAC Playback Volume'  100%,100%   

然后运行record-play程序即可。