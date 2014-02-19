#include <reg51.h>
#include <intrins.h>

#define LED_PORT P0	 //������ʾ

sbit LSP138A = P2^2;	//λѡ
sbit LSP138B = P2^3;
sbit LSP138C = P2^4;

unsigned int ledNumVal,  ledOut[8];
unsigned char code	dispTab[] = {
~0xC0,~0xF9,~0xA4,~0xB0,~0x99,~0x92,~0x82,~0xF8,~0x80,~0x90,
~0x88,~0x83,~0xC6,~0xA1,~0x86,~0xbf,~0xc7,~0x8c,~0xc1, ~0xff, ~0xf7};
void systemInit()
{
	TMOD = 0x00; //����ģʽ0�� 13λ������,���8192�� C/T = 0�����ڲ�ϵͳ�ṩ�������� -- 12M��12��Ƶ�� ����1us.
	TH0 = (8192 - 1000)/32;
	TL0 = (8192 - 1000)%32; 
	IE = 0x8a; //�����ʱ���ж�
	TR0 = 1; //������ʱ������
}

void delay(unsigned int i)
{
	  char j;
	  for (; i > 0; --i)
	  	for (j = 200; j > 0; --j);
}
int main()
{	 
	systemInit();
	 while (1){
	 	unsigned char i;
		
		ledOut[0] = dispTab[ledNumVal%10000/1000];
		ledOut[1] = dispTab[ledNumVal%1000/100];
		ledOut[2] = dispTab[ledNumVal%100/10];
		ledOut[3] = dispTab[ledNumVal%10];	
		
		for (i = 0; i < 8; ++i)
		{
			LED_PORT = ledOut[i];
			switch(i){
				case 0:LSP138A = 0; LSP138B = 0; LSP138C = 0;break;
				case 1:LSP138A = 1; LSP138B = 0; LSP138C = 0;break;
				case 2:LSP138A = 0; LSP138B = 1; LSP138C = 0;break;
				case 3:LSP138A = 1; LSP138B = 1; LSP138C = 0;break;
				case 4:LSP138A = 0; LSP138B = 0; LSP138C = 1;break;
				case 5:LSP138A = 1; LSP138B = 0; LSP138C = 1;break;
				case 6:LSP138A = 0; LSP138B = 1; LSP138C = 1;break;
				case 7:LSP138A = 1; LSP138B = 1; LSP138C = 1;break;
			}
			delay(150);
		}	
	 }
	 return 0;
}

/*
 *  T0 1ms �ж�
 */
void   T0zd(void) interrupt 1	   /* ���жϺţ�0: �ⲿ�ж�1�� 1: Timer0�ж� 2: �ⲿ�ж�2 3: Timer1�ж� 4: �����ж�*/
{
	 TH0 = (8192 - 1000)/32;
	 TL0 = (8192 - 1000)%32;
	 ++ledNumVal;
}