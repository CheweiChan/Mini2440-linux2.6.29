ͨ�^�W·���ݔ���Ñ������ܴa,�W���͸�^server�@ȡ�Ñ������ܴa.

�o�B�W퓞�loginTest.html(192.168.2.230/loginTest)
���°��ologin����login.cgi̎�������@ʾ�W�


�޸�boa-0.94.13�ļ����µ�boa.conf�������_�l��etc/boa����Ŀ¼��src��difines.h�ļ���ָ��#define SERVER_ROOT "/etc/boa"��
Port 80
User Ĭ��nobody����Ϊroot


Group Ĭ��nogroup����Ϊroot

ErrorLog Ĭ��/var/log/boa/error_log����Ҫ�ֶ�����/var/log/boaĿ¼


AccessLog Ĭ��/var/log/boa/access_log����Ҫ�ֶ�����/var/log/boaĿ¼


ServerName friendly-arm

DocumentRoot Ĭ��/var/www�����ֶ�����Ŀ¼�������޸ĵ�/www(ݔ��192.168.2.230���B��/www/index.html)
DirectoryIndex Ĭ��index.html


MimeTypes Ĭ��/etc/mime.types���轫������и��ļ�������Ŀ�����ͬ·����(����ubuntu /etc/mime.type�ļ���Ŀ���/etc/boa��)
ScriptAlias Ĭ��/cgi-bin/ /usr/lib/cgi-bin/�����ֶ�����Ŀ¼���޸���/cgi-bin/ /var/boa/cgi-bin(����վ���CGI�ű�λ��)

KeepAliveMax 1000       //һ�������������HTTP�����������������Ŀ
KeepAliveTimeout 10     //HTTP���������з���������������֮��ȴ���ʱ����������Ϊ��λ
DefaultType text/plain  //�ļ���չ��û�л�δ֪�Ļ���ʹ�õ�ȱʡMIME����
CGIPath /bin            //�ṩCGI�����PATH��������ֵ
Alias /doc /usr/doc     //Ϊ·�����ϱ���

�û����Ը����Լ���Ҫ����boa.conf�����޸ģ�������Ҫ��֤�����ĸ����ļ������ñ����boa.conf��������������ȻBoa�Ͳ������������� ������������У����ǻ���Ҫ������־�ļ�����Ŀ¼/var/log/boa������HTML�ĵ�����Ŀ¼/var/www��
��mime.types��inittab��passwd�ļ����κ�һ��linuxϵͳ�е�/etcĿ¼�¿������������ļ�ϵͳ��/etcĿ¼�£�����CGI�ű�����Ŀ¼/var/www/cgi-bin/��mime.types�ļ�����ָ����ͬ�ļ���չ����Ӧ��MIME���ͣ�һ�����ֱ�Ӵ�Linux�����Ͽ���һ�����󲿷�Ҳ������������/etcĿ¼�¡�