record-play.c���ܣ�
ͨ�����¼������10s���ڵ�ǰ�ļ����±���Ϊsound.wav�ļ�������¼����Ϻ���ʾ�Ƿ񲥷Ÿ�¼����

���룺
��PC linux shell ������� arm-linux-gnueabihf-gcc record-play.c -o record-play
���ɿ�ִ���ļ���record-play 


���У�
�ڿ������ȴ�mic����ͨ�����������£�
amixer sset 'Left PGA Mixer Mic3L' on	  
amixer sset 'Left PGA Mixer Mic3R' on     
amixer sset 'Right PGA Mixer Mic3L' on    
amixer sset 'Right PGA Mixer Mic3R' on 

�������������С���������£�
amixer cset name='PCM Playback Volume' 100%,100%
amixer cset name='HP DAC Playback Volume'  100%,100%   

Ȼ������record-play���򼴿ɡ�