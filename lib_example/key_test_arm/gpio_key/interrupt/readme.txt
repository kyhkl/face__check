test: gpio_key���Գ��򼰿�ִ���ļ�

evb335xII_3.14_emmc_gpio_key_interrupt_config�� gpio-key�жϷ�ʽ�ں����ã�ʹ��ʱ���临�Ƶ��ں�Դ���Ŀ¼��������Ϊ��.config

uImage��evb335xII_3.14_emmc_gpio_key_interrupt_config�ں����ñ�������ں˾���

evb335x-ii-emmc.dts����gpio1_16ģ��gpio����dts�ļ������临�Ƶ��ں�Դ��Ŀ¼��arch/arm/boot/dts/Ŀ¼�¼���

evb335x-ii-emmc.dtb��evb335x-ii-emmc.dts������Ķ������ļ�


�����ԣ���

�������mount /dev/mmcblk0p1 /mnt/

��evb335x-ii-emmc.dtb��uImage���Ƶ� /mntĿ¼�£���keybutton-interrupt���Ƶ�������

�������sync

����ϵͳ

�������./keybutton-interrupt   

(ע����������CN21�ĵ�20���Ž�3.3Vʱ��ģ�ⰴ������)