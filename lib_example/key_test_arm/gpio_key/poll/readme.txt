test: gpio_key测试程序及可执行文件

evb335xII_3.14_emmc_gpio_key_poll_config： gpio-key轮询方式内核配置，使用时将其复制到内核源码根目录，并改名为：.config

uImage：evb335xII_3.14_emmc_gpio_key_poll_config内核配置编译出的内核镜像

evb335x-ii-emmc.dts：以gpio1_16模拟gpio按键dts文件，将其复制到内核源码目录：arch/arm/boot/dts/目录下即可

evb335x-ii-emmc.dtb：evb335x-ii-emmc.dts编译出的二进制文件


【测试：】

输入命令：mount /dev/mmcblk0p1 /mnt/

将evb335x-ii-emmc.dtb和uImage复制到 /mnt目录下，将keybutton-poll复制到开发板

输入命令：sync

重启系统

输入命令：./keybutton-poll 

(注：将开发板CN21的第20引脚接3.3V时，模拟按键按下)

