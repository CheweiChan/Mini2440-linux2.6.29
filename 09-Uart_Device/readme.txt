1.define struct of uart_driver variable and initial
2.use uart_register_driver() to register uart driver
3.initial struct of uart_port and struct of uart_ops function table
4.use uart_add_one_port() to add uart_port




linux-2.6.32.2\drivers\serial
s3c2400.c �ж��x s3c2400_serial_init()�K���]�� platform_driver_register()���F��uart_platform_driver
samsung.c �ж��x s3c24xx_serial_probe()�K�Ҷ��x��struct of s3c24xx_uart_port,struct of uart_driver variable
s3c24xx_serial_probe()���{��uart_add_one_port()�]����uart device driver