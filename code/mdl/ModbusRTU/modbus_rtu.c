/**
 **************************************************************************************************
 * @file        modbus_rtu.c
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "modbus_rtu.h"


/**
 * @addtogroup    XXX 
 * @{  
 */
#include "system_param.h"
#include "refresh_task.h"
#include "app_lnprotocol.h"
#include "modbus_task.h"
#include "hal_task.h"
/**
 * @addtogroup    modbus_rtu_Modules 
 * @{  
 */

/**
 * @defgroup      modbus_rtu_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_rtu_Macros_Defines 
 * @brief         
 * @{  
 */
 
#define MB_REG_COILS_STARTADDR    		0 
#define MB_REG_DISCRETEINPUT_STARTADDR	0
#define MB_REG_HOLDING_STARTADDR		0
#define MB_REG_INPOUT_STARTADDR			0

/**
 * @}
 */

/**
 * @defgroup      modbus_rtu_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_rtu_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_rtu_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_rtu_Public_Variables 
 * @brief         
 * @{  
 */
 
/*
#define MBREGISTERCOILS 			0
#define MBREGISTERDISCRETEINPUT    	1
#define MBREGISTERHOLDING  			2
#define MBREGISTERINPUT  			3

#define MB_REG_COILS_COUNT          1
#define MB_REG_DISCRETEINPUT_COUNT	1
#define MB_REG_HOLDING_COUNT		6500
#define MB_REG_INPUT_COUNT 			100 
*/ 
 
static uint16_t mb_regcoil_space[MB_REG_COILS_COUNT];
static uint16_t mb_regdiscreteinput_space[MB_REG_DISCRETEINPUT_COUNT]; 
static uint16_t mb_regholding_space[MB_REG_HOLDING_COUNT];
static uint16_t mb_reginput_space[MB_REG_INPUT_COUNT];
 
RingArray Modbus;
SlaveStruct_t Slave;
/**
 * @}
 */

/**
 * @defgroup      modbus_rtu_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void MBFunction_03(void); 
static void MBFunction_04(void);
static void MBFunction_05(void);
static void MBFunction_06(void);


static int8_t mb_writeReg_coil(uint16_t addr , uint16_t data);
static int8_t mb_writeReg_discreteinput(uint16_t addr , uint16_t data);
static int8_t mb_writeReg_holding(uint16_t addr , uint16_t data);
static int8_t mb_writeReg_input(uint16_t addr , uint16_t data);

static int8_t mb_readReg_coil(uint16_t addr , uint16_t *data);
static int8_t mb_readReg_discreteinput(uint16_t addr , uint16_t *data);
static int8_t mb_readReg_holding(uint16_t addr , uint16_t *data);
static int8_t mb_readReg_input(uint16_t addr , uint16_t *data);

/**
 * @}
 */

/**
 * @defgroup      modbus_rtu_Functions 
 * @brief         
 * @{  
 */
 
void ModbusSlaveInit(void) //Slave ID startaddr endaddr init
{
	Slave.Reg_coil.Addr.DataI = mb_regcoil_space;
	Slave.Reg_coil.startAddr = MB_REG_COILS_STARTADDR;
	Slave.Reg_coil.endAddr = MB_REG_COILS_STARTADDR + MB_REG_COILS_COUNT;
	
	Slave.Reg_discreteinput.Addr.DataI = mb_regdiscreteinput_space;
	Slave.Reg_discreteinput.startAddr = MB_REG_DISCRETEINPUT_STARTADDR;
	Slave.Reg_discreteinput.endAddr = MB_REG_DISCRETEINPUT_STARTADDR + MB_REG_DISCRETEINPUT_COUNT;
	
	Slave.Reg_holding.Addr.DataI = mb_regholding_space;
	Slave.Reg_holding.startAddr = MB_REG_HOLDING_STARTADDR;
	Slave.Reg_holding.endAddr = MB_REG_HOLDING_STARTADDR + MB_REG_HOLDING_COUNT;
	
	Slave.Reg_input.Addr.DataI = mb_reginput_space;
	Slave.Reg_input.startAddr = MB_REG_INPOUT_STARTADDR;
	Slave.Reg_input.endAddr = MB_REG_INPOUT_STARTADDR + MB_REG_INPUT_COUNT;
	
    Slave.ID = g_SystemParam_Config.MB_Slave_ID;
} 

void ModbusRingBufInit(void)    //RingBuf init
{
	Modbus.RingCount=0;
	Modbus.RingIn=0;
	Modbus.RingOut=0;
	Modbus.RingSize=5;
}
void rBufToRing(void)   
{
	if(Uart2RBuf_Ptr > 0)
	{
		memcpy(Modbus.RingData[Modbus.RingIn].Buf,Uart2RBuf,Uart2RBuf_Ptr);
		Modbus.RingData[Modbus.RingIn].Len=Uart2RBuf_Ptr;
		Uart2RBuf_Ptr=0;
		Modbus.RingIn++;
		Modbus.RingIn%=Modbus.RingSize;
		Modbus.RingCount++;
		Modbus.RingCount%=10;		
	}
}

void ModbusDataProcess(void)
{
	if(Modbus.RingCount>0)              //if ringbuf has data
	{
        if (Modbus.RingData[Modbus.RingOut].Buf[0] == Slave.ID)     //if askdata is slaveID
        {           
            if (checkCRC(Modbus.RingData[Modbus.RingOut].Buf, Modbus.RingData[Modbus.RingOut].Len) == 0x0000) //check CRC
            {
				
				// ---485en------ 
				Modbus_485en_T();
				// ----------
				
               switch (Modbus.RingData[Modbus.RingOut].Buf[1])  //choose function
               {
                   case 0x03:MBFunction_03(); break;
                   case 0x04:MBFunction_04(); break;     
                   case 0x05:MBFunction_05(); break;
                   case 0x06:MBFunction_06(); break;
                   default:break;
               }
            }
        }
		else
		{
			APP_Lnprotocol_Process(Modbus.RingData[Modbus.RingOut].Buf , Modbus.RingData[Modbus.RingOut].Len );
		}
        
        Modbus.RingOut++;                           //deal with ringbuf
        Modbus.RingOut %= Modbus.RingSize;
        Modbus.RingCount--;
	}
	
	if(Modbus.RingCount>0)
	{
		Modbus_Task_Event_Start(MODBUS_TASK_DATAPROCESS_EVENT, EVENT_FROM_TASK);
	}
}

int8_t MB_WirteRegister(uint8_t Register, uint16_t Addr,uint16_t Data)       //Slave wirte register
{
	int8_t return_temp = 0 ; 
	switch(Register)
	{
		case MBREGISTERCOILS:			return_temp = mb_writeReg_coil(Addr , Data);break;
		case MBREGISTERDISCRETEINPUT : 	return_temp = mb_writeReg_discreteinput(Addr , Data);break;
		case MBREGISTERHOLDING:			return_temp = mb_writeReg_holding(Addr , Data);break;
		case MBREGISTERINPUT:			return_temp = mb_writeReg_input(Addr , Data);break;
		default:break;
	}
	
	return return_temp;
}

static int8_t mb_writeReg_coil(uint16_t addr , uint16_t data)
{
	if(addr >= Slave.Reg_coil.startAddr && addr < Slave.Reg_coil.endAddr)
	{
		Slave.Reg_coil.Addr.DataI[addr] = data;
		
		return 1;
	}
	else
	{
		return -1;
	}
}
static int8_t mb_writeReg_discreteinput(uint16_t addr , uint16_t data)
{
	if(addr >= Slave.Reg_discreteinput.startAddr && addr < Slave.Reg_discreteinput.endAddr)
	{
		Slave.Reg_discreteinput.Addr.DataI[addr] = data;
		
		return 1;
	}
	else
	{
		return -1;
	}
	
}
static int8_t mb_writeReg_holding(uint16_t addr , uint16_t data)
{
	if(addr >= Slave.Reg_holding.startAddr && addr < Slave.Reg_holding.endAddr)
	{
		Slave.Reg_holding.Addr.DataI[addr] = data;
		
		return 1;
	}
	else
	{
		return -1;
	}	
}
static int8_t mb_writeReg_input(uint16_t addr , uint16_t data)
{
	if(addr >= Slave.Reg_input.startAddr && addr < Slave.Reg_input.endAddr)
	{
		Slave.Reg_input.Addr.DataI[addr] = data;
		
		return 1;
	}
	else
	{
		return -1;
	}	
}

uint16_t MB_ReadRegister(uint8_t Register, uint16_t Addr ,uint16_t *Data)                   //Slave read register
{
	int8_t return_temp = 0 ; 
	switch(Register)
	{
		case MBREGISTERCOILS:			return_temp = mb_readReg_coil(Addr , Data);break;
		case MBREGISTERDISCRETEINPUT : 	return_temp = mb_readReg_discreteinput(Addr , Data);break;
		case MBREGISTERHOLDING:			return_temp = mb_readReg_holding(Addr , Data);break;
		case MBREGISTERINPUT:			return_temp = mb_readReg_input(Addr , Data);break;
		default:break;
	}
	
	return return_temp;
}

static int8_t mb_readReg_coil(uint16_t addr , uint16_t *data)
{
	if(addr >= Slave.Reg_coil.startAddr && addr < Slave.Reg_coil.endAddr)
	{
		*data = Slave.Reg_coil.Addr.DataI[addr];
		return 1;
	}
	else
	{
		* data = 0x0000;
		return -1;
	}	
}
static int8_t mb_readReg_discreteinput(uint16_t addr , uint16_t *data)
{
	if(addr >= Slave.Reg_discreteinput.startAddr && addr < Slave.Reg_discreteinput.endAddr)
	{
		* data = Slave.Reg_discreteinput.Addr.DataI[addr] ;
		return 1;
	}
	else
	{
		* data = 0x0000;
		return -1;
	}	
}
static int8_t mb_readReg_holding(uint16_t addr , uint16_t *data)
{
	if(addr >= Slave.Reg_holding.startAddr && addr < Slave.Reg_holding.endAddr)
	{
		* data = Slave.Reg_holding.Addr.DataI[addr] ;
		return 1;
	}
	else
	{
		* data = 0x0000;
		return -1;
	}		
}
static int8_t mb_readReg_input(uint16_t addr , uint16_t *data)
{
	if(addr >= Slave.Reg_input.startAddr && addr < Slave.Reg_input.endAddr)
	{
		* data = Slave.Reg_input.Addr.DataI[addr] ;
		return 1;
	}
	else
	{
		* data = 0x0000;
		return -1;
	}	
}
// ------------------ Func Code ----------------

static void MBFunction_03(void)
{
    uint16_t addr = 0;
    uint8_t ask_data_count = 0;
    uint8_t modbus_send_buf[300];
    uint8_t i = 0;
    uint16_t crctemp = 0;
	uint16_t temp_1 = 0;
	
    addr = (uint16_t)(Modbus.RingData[Modbus.RingOut].Buf[2] * 256 + Modbus.RingData[Modbus.RingOut].Buf[3]);
    ask_data_count =  (uint16_t)(Modbus.RingData[Modbus.RingOut].Buf[4] * 256 + Modbus.RingData[Modbus.RingOut].Buf[5]);
	if(ask_data_count > 128)
	{
		return;
	}
	
    if ((addr >= Slave.Reg_holding.startAddr) && (addr + ask_data_count <= Slave.Reg_holding.endAddr))
    {
        for (i = 0; (i < ask_data_count) ; i++)
        {
			if(MB_ReadRegister(MBREGISTERHOLDING, addr+i , &temp_1 ) == 1 )
			{
				modbus_send_buf[3+i*2]= temp_1 >> 8;           
				modbus_send_buf[3+i*2+1]= temp_1 & 0x00ff;				
			}
			else
			{
				return ;
			}
        }
		
        modbus_send_buf[0] = Slave.ID;
        modbus_send_buf[1] = Modbus.RingData[Modbus.RingOut].Buf[1];
        modbus_send_buf[2] = ask_data_count*2;
        crctemp = ModbusCRC(modbus_send_buf,ask_data_count*2+3);
        modbus_send_buf[ask_data_count*2+3] = crctemp >> 8;
        modbus_send_buf[ask_data_count*2+3+1] = (uint8_t)(crctemp & 0x00ff);
		
		
		
		
        ModbusSend(modbus_send_buf,ask_data_count * 2 + 3 + 2);
    }
}

static void MBFunction_04(void)
{
    uint16_t addr = 0;
    uint8_t ask_data_count = 0;
    uint8_t modbus_send_buf[300];
    uint8_t i = 0;
    uint16_t crctemp = 0;
	uint16_t temp_1 = 0;
    addr = (uint16_t)(Modbus.RingData[Modbus.RingOut].Buf[2]*256 + Modbus.RingData[Modbus.RingOut].Buf[3]);
    ask_data_count =  (uint16_t)(Modbus.RingData[Modbus.RingOut].Buf[4] * 256 + Modbus.RingData[Modbus.RingOut].Buf[5]);

	if(ask_data_count > 128)
	{
		return;
	}	

    if ((addr >= Slave.Reg_input.startAddr) && (addr + ask_data_count <= Slave.Reg_input.endAddr))
    {
        for (i = 0; (i < ask_data_count) ; i++)
        {
			if(MB_ReadRegister(MBREGISTERINPUT, addr+i , &temp_1 ) == 1 )
			{
				modbus_send_buf[3+i*2]= temp_1 >> 8;           
				modbus_send_buf[3+i*2+1]= temp_1 & 0x00ff;				
			}
			else
			{
				return ;
			}			
        }
		
        modbus_send_buf[0] = Slave.ID;
        modbus_send_buf[1] = Modbus.RingData[Modbus.RingOut].Buf[1];
        modbus_send_buf[2] = ask_data_count*2;
        crctemp = ModbusCRC(modbus_send_buf,ask_data_count*2+3);
        modbus_send_buf[ask_data_count*2+3]=crctemp>>8;
        modbus_send_buf[ask_data_count*2+3+1]=(uint8_t)(crctemp&0x00ff);
        ModbusSend(modbus_send_buf,ask_data_count * 2 + 3 + 2);
    }
}

static void MBFunction_05(void)
{
    uint16_t addr=0;
    uint16_t crctemp=0;
    uint16_t data=0;
    uint8_t modbus_send_buf[300];
	uint16_t temp_1 = 0;
    addr = (uint16_t)(Modbus.RingData[Modbus.RingOut].Buf[2] * 256 + Modbus.RingData[Modbus.RingOut].Buf[3]);
    data = Modbus.RingData[Modbus.RingOut].Buf[4] * 256 + Modbus.RingData[Modbus.RingOut].Buf[5] ;

	if( MB_WirteRegister(MBREGISTERCOILS, addr, data) == 1 )     //Slave wirte register
	{
		
	}
	else
	{
		return ; 
	}
	

    modbus_send_buf[0] = Slave.ID;
    modbus_send_buf[1] = Modbus.RingData[Modbus.RingOut].Buf[1];
    modbus_send_buf[2] = (addr & 0xff00)>>8;
    modbus_send_buf[3] = (uint8_t)(addr & 0x00ff);
	
	MB_ReadRegister(MBREGISTERCOILS, addr , &temp_1 );
	
    modbus_send_buf[4] = temp_1>>8; 
    modbus_send_buf[5] = (uint8_t)(temp_1&0x00ff);

    crctemp = ModbusCRC(modbus_send_buf,6);
    modbus_send_buf[6]=crctemp>>8;
    modbus_send_buf[7]=(uint8_t)(crctemp&0x00ff);

    ModbusSend(modbus_send_buf,8);
}

static void MBFunction_06(void)
{
    uint16_t addr=0;
    uint16_t crctemp=0;
    uint16_t data=0;
    uint8_t modbus_send_buf[300];
	uint16_t temp_1 = 0 ;
    addr = (uint16_t)(Modbus.RingData[Modbus.RingOut].Buf[2]*256 + Modbus.RingData[Modbus.RingOut].Buf[3]);
    data = Modbus.RingData[Modbus.RingOut].Buf[4]*256 + Modbus.RingData[Modbus.RingOut].Buf[5] ;

	if( MB_WirteRegister(MBREGISTERHOLDING, addr, data) == 1 )     //Slave wirte register
	{
		
	}
	else
	{
		return ; 
	}
	
    modbus_send_buf[0] = Slave.ID;
    modbus_send_buf[1] = Modbus.RingData[Modbus.RingOut].Buf[1];
    modbus_send_buf[2] = (addr & 0xff00)>>8;
    modbus_send_buf[3] = (uint8_t)(addr & 0x00ff);
	
	MB_ReadRegister(MBREGISTERHOLDING, addr , &temp_1 );
	
    modbus_send_buf[4] = temp_1 >> 8; 
    modbus_send_buf[5] = (uint8_t)(temp_1 & 0x00ff);;

    crctemp = ModbusCRC(modbus_send_buf,6);
    modbus_send_buf[6]=crctemp>>8;
    modbus_send_buf[7]=(uint8_t)(crctemp&0x00ff);

    ModbusSend(modbus_send_buf,8);

	
	Refresh_Task_Event_Start(REFRESH_TASK_MBTOSYS_EVENT, EVENT_FROM_TASK);
	//Hal_Task_Event_Start(HAL_TASK_SAVE_SYS_EVENT , EVENT_FROM_TASK);
    //BSP_Pro_Info_UpData();
    //Slave.ID=MB_ReadRegister(MBREGISTERHOLDING, 5);
}





/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

