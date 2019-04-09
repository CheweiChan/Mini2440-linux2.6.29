/*mini-2440 input device test*/
#include <linux/input.h>
#include <linux/module.h>
#include <linux/init.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <mach/regs-gpio.h>
#include <mach/hardware.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
 
static struct input_dev *button_dev;
static irqreturn_t buttons_interrupt(int irq, void *dummy);
static int button_open(struct input_dev *dev);
static void button_close(struct input_dev *dev);
struct button_irq_desc {   //���尴���жϵĽṹ��
    int irq;     //�жϺ� 
    int pin;     //��������
    int pin_setting;    // �����������ã�����Ϊ�жϣ�
    int number;            //�������
    char *name;     //�������� 
};
/*���ýṹ��struct button_irq_desc ����6����������Ϣ���Ѱ�������Դ��������֯*/
static struct button_irq_desc button_irqs [] = {
    {IRQ_EINT8 , S3C2410_GPG0 ,  S3C2410_GPG0_EINT8  , 1, "KEY1"},
    {IRQ_EINT11, S3C2410_GPG3 ,  S3C2410_GPG3_EINT11 , 2, "KEY2"},
    {IRQ_EINT13, S3C2410_GPG5 ,  S3C2410_GPG5_EINT13 , 3, "KEY3"},
    {IRQ_EINT14, S3C2410_GPG6 ,  S3C2410_GPG6_EINT14 , 4, "KEY4"},
    {IRQ_EINT15, S3C2410_GPG7 ,  S3C2410_GPG7_EINT15 , 5, "KEY5"},
    {IRQ_EINT19, S3C2410_GPG11,  S3C2410_GPG11_EINT19, 6, "KEY6"},
};
/*���尴��open������Ҳ���Խ�open���������ݷŵ�init������ȥ��*/
static int button_open(struct input_dev *dev)
{
    int i;
    int err = 0;
    
    /*������������������Ӧ���ж�Ϊ˫�ش������������غ��½��ض��ᴥ���ж�*/
    set_irq_type(IRQ_EINT8, IRQ_TYPE_EDGE_BOTH);  
    set_irq_type(IRQ_EINT11, IRQ_TYPE_EDGE_BOTH);  
    set_irq_type(IRQ_EINT13, IRQ_TYPE_EDGE_BOTH);  
    set_irq_type(IRQ_EINT14, IRQ_TYPE_EDGE_BOTH);  
    set_irq_type(IRQ_EINT15, IRQ_TYPE_EDGE_BOTH);  
    set_irq_type(IRQ_EINT19, IRQ_TYPE_EDGE_BOTH);
    
    for (i = 0; i < sizeof(button_irqs)/sizeof(button_irqs[0]); i++)
    {
        if (button_irqs[i].irq < 0) 
            continue; 
 /*���������жϣ������������ж����ͱ�ʶΪIRQF_SAMPLE_RANDOM��
 IRQF_SAMPLE_RANDOM��ʾ�豸���Ա��������¼�����ķ���Դ
 request_irq�������������ֱ����жϺţ��жϴ��������豸�������һ������Ϊdev_id,
 �����ж�ʱʹ�ã�����Ψһ����ÿ���ṹ�����ʼ��ַ����ʾ�ܹ���֤id��Ψһ�ԡ�
 */
        err = request_irq(button_irqs[i].irq, buttons_interrupt, IRQF_SAMPLE_RANDOM, 
                          button_irqs[i].name, (void *)&button_irqs[i]);
        if (err)
            break;
    }
    /*��������ֹ�жϲ��ͷ��жϺ�*/
    if (err) 
    {
         i--;
         for (; i >= 0; i--)
         {
             if (button_irqs[i].irq < 0) 
             {
                continue;
             }
             disable_irq(button_irqs[i].irq);
             free_irq(button_irqs[i].irq, (void *)&button_irqs[i]);
         }
            return -EBUSY;
    }
        return 0;
}



static void button_close(struct input_dev *dev)
{
    int i;
     
    /*��ֹ�жϲ��ͷ��жϺ�*/
    for (i = 0; i < sizeof(button_irqs)/sizeof(button_irqs[0]); i++)
    {
         if (button_irqs[i].irq < 0)
         {
             continue;
         }
        disable_irq(button_irqs[i].irq);
        free_irq(button_irqs[i].irq, (void *)&button_irqs[i]);
    }
}

static irqreturn_t buttons_interrupt(int irq, void *dummy)
{
 /*���жϷ���ʱ���ϱ�����������״̬��������������ʱ��ֵ��0�����ڱ������ð�������ʱ��ʾ��ֵΪ  1���ʽ���gpio�˿ڻ�õ�ֵȡ����ע�⣺������������Ҫ�ϱ��������ｫ������֧�ֵİ����� �ϱ�����
�ڶ������������ź͵�����������ֵ���Ӿ����GPIO�˿�ȥȡ������ֵ���������������Ӷ�����
 �������ϵ�Ӳ�������������ܹ���ϵͳ�ν�������input_sync������֪ϵͳ���Ѿ��ϱ����*/
     input_report_key(button_dev, KEY_ESC, !s3c2410_gpio_getpin(S3C2410_GPG0));
     input_report_key(button_dev, KEY_1, !s3c2410_gpio_getpin(S3C2410_GPG3));
     input_report_key(button_dev, KEY_2, !s3c2410_gpio_getpin(S3C2410_GPG5));
     input_report_key(button_dev, KEY_3, !s3c2410_gpio_getpin(S3C2410_GPG6));
     input_report_key(button_dev, KEY_4, !s3c2410_gpio_getpin(S3C2410_GPG7));
     input_report_key(button_dev, KEY_5, !s3c2410_gpio_getpin(S3C2410_GPG11));
     input_sync(button_dev);
     return IRQ_HANDLED;
}
static int __init button_init(void)
{
    int error;
    struct input_dev *input_dev; 
    printk("s3c2440 my_keyboard module start/n");     
     /*��input_dev����ṹ��ָ�����ռ�*/
     input_dev = input_allocate_device();  
     if(!input_dev)  
     {  
      printk(KERN_ERR "Unable to allocate the input device!!/n");  
      return -ENOMEM;  
     }  
     button_dev = input_dev;  
 
 /*���ð��������ͺ���֧�ֵļ���EV_KEYΪ�������ͣ�KEY_ESC��KEY_1-5Ϊ��֧�ֵļ���������ϣ���ҵİ���
 ȡ1-6����include/linux/input.h�в�ѯ��صĺ����֪����ѡ��֧�ֵļ�Ϊ1-6����Ȼ��Ҳ����ѡ�����Լ�ϲ
 ���ļ�ֵ�������ѡ��Ĳ���1-6��Ӧ�ó���ȡ�õİ�����ev_key.codeҲ�����������ö��ı�*/
     set_bit(EV_KEY, button_dev->evbit);
     set_bit(KEY_ESC, button_dev->keybit);
     set_bit(KEY_1, button_dev->keybit);
     set_bit(KEY_2, button_dev->keybit);
     set_bit(KEY_3, button_dev->keybit);
     set_bit(KEY_4, button_dev->keybit);
     set_bit(KEY_5, button_dev->keybit);
 
 /*����豸�����֣����ô����ֿ������û���ѯ���豸����;�������ֽ�������input/event*Ŀ¼�µ�name
 �У�cat name������ʾ�����õ�����*/
     button_dev->name = "buttons_yzx";
 /*�����ҵ�input��ϵͳ�����֣�����ģ���/sys/class/inputĿ¼�½������������õ�����*/
     button_dev->dev.init_name = "input_yzx";
 
 /*���ýṹ���еĻص�����*/
     button_dev->open = button_open;
     button_dev->close = button_close;
 
    printk("input device has allocated/n");
 
 /*ע���豸*/
    error = input_register_device(button_dev);
    if (error)     
    {
         printk(KERN_ERR "button.c: Failed to register device\n");
         input_free_device(button_dev);
         
         return error;
    }
 
    printk("register device has success\n");
 
    return 0;
}
static void __exit button_exit(void)
{
        /*ɾ���豸*/
    input_unregister_device(button_dev); 
}
module_init(button_init);
module_exit(button_exit);
MODULE_LICENSE("GPL");









































