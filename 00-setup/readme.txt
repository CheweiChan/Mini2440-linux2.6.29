#linux 
1.��ʼ��װ���������½�һ���ļ��У���Ȼ���ļ����Ƶ��½����ļ����� 
���darm-linux-gcc ���s�n (���湤���) 
���dlinux-2.6.32.2 ���s�n (linuxԴ���a) 

 
2.���barm-linux-gcc ���湤��� 
cd�����dĿ� ������� sudo tar xvzf arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz 
��װ��ɺ�����ls������Կ���һ��opt�ļ��� 
 
tar xvzf arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz -C /abc (-C /abc �≺�s��Ŀ�abc) 
 
 
 
3.�޸Ļ����������ѽ����������·�����뵽PATH�� 
��opt/FriendlyARM/toolschain/4.5.1/bin����pwd����鿴��ǰ·���ľ���·�� 
����ݔ��cmd����·�� 
export PATH=$PATH:/home/chewei/desktop_/opt/FriendlyARM/toolschain/4.4.3/bin 
 
��������·�����޸�.bashrc 
/home ~/.bashrc ����.bashrc����������export PATH=$PATH:/home/chewei/desktop_/opt/FriendlyARM/toolschain/4.4.3/bin 
���нű����û���������Ч 
source ~/.bashrc 
 
Ҳ�����޸�/etc/profile �����·�� 
��#Path manipulation�������·��/home/chewei/desktop_/opt/FriendlyARM/toolschain/4.4.3/bin 
���нű����û���������Ч > source /etc/profile 
 
 
 
ݔ��cmd �_�J·����echo $PATH 
ݔ��cmd �_�J���g��: arm-linux-gcc hello.c -o hello(���ghello.c�n) 
ݔ��cmd �_�J�汾: arm-linux-readefl -a hello(�鿴���g�����hello�n) 
 
 
#cp config_mini2440_P43 .config 
#make mini2440_defconfig ;ʹ�� Linux �ٷ��Դ��� mini2440 ���� 
#make menuconfig 
#make zImage (arch/arm/bootĿ¼������linux�ں�ӳ���ļ�) 
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////// 

 
ȱ�� ��build-essential�� ���������ı������⡣ 
 
HOSTCC scripts/basic/fixdep 
scripts/basic/fixdep.c:106:23: fatal error: sys/types.h: No such file or directory 
compilation terminated. 
make[1]: *** [scripts/basic/fixdep] Error 1 
make: *** [scripts_basic] Error 2 
 
����������£� 
apt-get install build-essential  
 
sudo apt-get install build-essential linux-headers-$(uname -r) ���blinux drv �_�l�׼� 

 
///////////////////////////////////////////////////////////////////////////////////////////////////////////// 

 
�����ں˳������´��� 
 
Can't use 'defined(@array)' (Maybe you should just omit the defined()?) at kernel/timeconst.pl line 373. 
 
/root/working/Hi3520D_SDK_V2.0.3.0/osdrv/kernel/linux-3.0.y/kernel/Makefile:140: recipe for target 'kernel/timeconst.h' failed 
 
make[1]: *** [kernel/timeconst.h] Error 255 
 
Makefile:945: recipe for target 'kernel' failed 
 
make: *** [kernel] Error 2 
 
����취�� 
��kernel/timeconst.pl�е�373�е�defined()ȥ��ֻ����@val�Ϳ����� 
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////// 

 
yaffs2 �ļ�ϵͳ ��ֲ���} 
https://blog.csdn.net/baijinglei12/article/details/7686528 
 

///////////////////////////////////////////////////////////////////////////////////////////////////////////// 
Error 1 Makefile:454: recipe for target 'menuconfig' failed make: *** [menuconfig] Error 2  
����취�� 
sudo apt-get install libncurses5-dev 
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////// 
 
�鿴rs232 port 
cmd:dmesg | grep tty 
 

///////////////////////////////////////////////////////////////////////////////////////////////////////////// 
 
linux �� minitool �]���� 
���b--> apt install libqtwebkit4 

 
///////////////////////////////////////////////////////////////////////////////////////////////////////////// 
ִ��make menuconfig���ܿ��������Ĵ��� 
 
*** Unable to find the ncurses libraries or the 
*** required header files. 
*** ��make menuconfig�� requires the ncurses libraries. 
*** 
*** Install ncurses (ncurses-devel) and try again. 
 
����취���£� 
CentOS�� 
yum install -y ncurses-devel 
 
Ubuntu�� 
sudo apt-get install ncurses-dev 
///////////////////////////////////////////////////////////////////////////////////////////////////////////// 

 