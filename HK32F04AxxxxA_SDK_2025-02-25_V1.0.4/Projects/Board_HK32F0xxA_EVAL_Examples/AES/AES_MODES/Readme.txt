/*
* @file name: Readme
* @author: AE Team
*/

V1.0.0/2023-10-19
1.首次发布

******************************例程详细描述*****************************
功能描述:
这个示例描述了如何使用AES硬件加速器在所有秘钥长度（128\192\256）下，
加解密数据的配置流程和功能使用

---- -加密
通过将PlainText[AES_TEXT_SIZE]与密钥Encryption128Key[16] / Encryption192Key
/ Encryption256Key进行加密产生密文Encryptedtext[AES_TEXT_SIZE]，
并通过串口打印出来。
----解密
通过将密文CipherText[AES_TEXT_SIZE]与解密密钥Encryption128Key[16]
/ Encryption192Key / Encryption256Key进行解密操作,
得到解密数据Decryptedtext[AES_TEXT_SIZE],
并通过串口打印出来。

时钟配置:
本例程采用HSI56MHz作为系统时钟，用户如果需要更改系统时钟配置，
需要配置修改SYSCLK_SOURCE宏定义的。
关于系统时钟如何配置，请参考对应用户手册或者RCC库函数及RCC相关例程。

适用芯片:
HK32F04AxxA

涉及外设:
USART1

涉及管脚:
PA9
PA10

注意事项:
1. 推荐使用MDK5.00及其以上版本编译本工程（MDK - ARM）
或者IAR8.22及其以上版本编译本工程(EWARM);
2. 使用之前检测电源VCC、GND等是否正常。
如何使用:
1. 直接编译程序下载到评估版，重启评估版;
2. 通过与Expected_Results.txt中的值比对，判断结果是否正确。
***********************************************************************
