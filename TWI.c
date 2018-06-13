
#include "TWI.h"
#include <avr/io.h>


/*****************************************************/
/*I2c initialization*/
void TWI_init(void)
{
#if TWI_SPEED == 100
	TWBR=32;   // to set the speed 100kb/s  ,,, Speed 400khz TWBR=2;

#elif TWI_SPEED == 400
	TWBR=2;   // to set the speed 100kb/s  ,,, Speed 400khz TWBR=2;
#endif

	TWSR=0;   // TWPS=0; //PreScaler 1:1
	TWCR=(1<<TWEN)|(1<<TWEA); // enable the TWI peripheral
}

/*****************************************************/
/*I2c initialization*/
void TWI_init_slave(unsigned char address)
{

	TWCR = (1 << TWEN); // enable the TWI peripheral
	TWAR = ( (address << 1) & (0xfe)); // address of the slave
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
}


/*****************************************************/
/*I2c recieve*/
unsigned char TWI_recieve()
{

	TWCR = (1 << TWINT) | (1 << TWEN); // enable the TWI peripheral
	while(!(TWCR & (1<<TWINT)) );
	return TWDR;

}

/*****************************************************/
/*I2c listen*/
void TWI_listen()
{

	while(!(TWCR & (1<<TWINT)) );

}



/*****************************************************/
/*Device Address*/
void TWI_address(unsigned char address)
{
	TWAR = ((address<<1)&(0xfe));
}

/*****************************************************/
/*Sending the Address*/
void TWI_send_DeviceAddress_Read(unsigned char address)
{
	TWDR=((address<<1)|(0x01));//Address+ReadBit
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
		while((!(TWCR & (1<<TWINT)))&& ((((TWSR&0xf8)!=0x40))));

}

/*****************************************************/
void TWI_send_DeviceAddress_Write(unsigned char address)
{
	TWDR=((address<<1)&(0xfe));//Address+WriteBit
	TWCR=(1<<TWEN)|(1<<TWINT);
	while((!(TWCR & (1<<TWINT)))&&((TWSR&0xf8)!=0x18));
}

/*****************************************************/
/*Sending a byte of data*/
void TWI_send_data(unsigned char Data)
{
	TWDR=Data;
	TWCR=(1<<TWEN)|(1<<TWINT);
	while((!(TWCR & (1<<TWINT)))&&( (((TWSR&0xf8)!=0x28))||(((TWSR&0xf8)!=0xB8))));
}

/*****************************************************/
/*Sending a stop bit*/
void TWI_stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);


}

/*****************************************************/
/*Receive with ACK*/
unsigned char  TWI_recieve_data_ACK(void)
{
	/*while the TWIF is zero (job not finished) & status register not telling u that you received anything ....wait*/
	
	while(((!(TWCR & (1<<TWINT))))&&((((TWSR&0xf8)!=0x80))||((TWSR&0xf8)!=0x50)));
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	return TWDR;
}
/*****************************************************/
/*Receive with NACK*/
unsigned char  TWI_recieve_data_NACK(void)
{
	while(((!(TWCR & (1<<TWINT))))&&((((TWSR&0xf8)!=0x88))||((TWSR&0xf8)!=0x58)));
	TWCR=(1<<TWEN)|(1<<TWINT);
	return TWDR;
}
/*****************************************************/
