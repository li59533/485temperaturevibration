using Modbus.Device;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Windows.Forms;


namespace Serialtool
{
    class hal_serial
    {
        public static SerialPort serialport_1;
        public IModbusSerialMaster master;
        public bool current_status;
        Form1 mainform;
        public hal_serial(Form1 form)
        {
            mainform = form;
        }


        public void Serial_Open( string portname ,int baudrate , Parity parity , UInt16 databits , StopBits stopbits )
        {
            if (current_status == true)
            {
                Console.Write("Serial had Open\r\n");
                return;
            }
            else
            {
                serialport_1 = new SerialPort();

                serialport_1.PortName = portname;
                serialport_1.BaudRate = baudrate;
                serialport_1.Parity = parity;
                serialport_1.DataBits = databits;
                serialport_1.StopBits = stopbits;
                //_serialPort.Handshake = ;

                // Set the read/write timeouts
                serialport_1.ReadTimeout = 500;
                serialport_1.WriteTimeout = 500;

                serialport_1.Open();

                master = ModbusSerialMaster.CreateRtu(serialport_1); //创建 Rtu 传输模式、通过串口 port 通信的主站 master
                master.Transport.ReadTimeout = 200;
                master.Transport.Retries = 0;
                master.Transport.WaitToRetryMilliseconds = 50;
                serialport_1.DataReceived += new SerialDataReceivedEventHandler(Serial_DataRev);


                current_status = true;
                Console.Write("Serial Open\r\n");
            }
        }

        public void Serial_Close()
        {
            if (current_status == true)
            {
                current_status = false;
                serialport_1.Close();
                Console.Write("Serial Close\r\n");
            }
            else
            {
                Console.Write("Serial Had Close\r\n");
            }
        }

        private void Serial_DataRev(object sender, SerialDataReceivedEventArgs e)
        {
            System.Threading.Thread.Sleep(100);

            Byte[] revdatabuf = new byte[serialport_1.BytesToRead];
            serialport_1.Read(revdatabuf, 0, revdatabuf.Length);

            for (UInt16 i = 0; i < revdatabuf.Length; i++)
            {
                Console.Write(revdatabuf[i].ToString("X") + " " );
            }
            
            mainform.Invoke(
                (EventHandler)
                (delegate
                    {
                        //mainform.Form_RevData(revdatabuf , (UInt16)revdatabuf.Length);
                    }
                )
                );

            serialport_1.DiscardInBuffer();

        }


        public void Serial_Send( Byte[] buf , UInt16 len)
        {
            serialport_1.Write(buf, 0, len);
        }
    }
}
