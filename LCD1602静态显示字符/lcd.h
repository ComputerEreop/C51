#ifndef __LCD_H_
#define __LCD_H_
/**********************************
��ʹ�õ���4λ���ݴ����ʱ���壬
ʹ��8λȡ���������
**********************************/
#define LCD1602_4PINS

/**********************************
����ͷ�ļ�
**********************************/
#include<reg51.h>

//---�ض���ؼ���---//
#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef uint16 
#define uint16 unsigned int
#endif

/**********************************
PIN�ڶ���
**********************************/
#define lcd1602_port P0
sbit LCD1602_EN=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

/**********************************
��������
**********************************/
/*��51��Ƭ��12MHZʱ���µ���ʱ����*/
void lcd1602_delayMs(uint16 c);   //��� 0us
/*LCD1602д��8λ�����Ӻ���*/
void lcd1602_wcmd(uint8 com);
/*LCD1602д��8λ�����Ӻ���*/	
void lcd1602_wdata(uint8 dat);
/*LCD1602��ʼ���ӳ���*/		
void lcd1602_init();						  

#endif
