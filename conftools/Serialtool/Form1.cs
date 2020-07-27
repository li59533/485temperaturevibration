using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.VisualBasic;

namespace Serialtool
{
    public partial class Form1 : Form
    {
        hal_serial serial_1;
        dataprocess dataprocess_func;
        float x_acc_rms;
        float y_acc_rms;
        float z_acc_rms;



        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            serial_1 = new hal_serial(this);
            dataprocess_func = new dataprocess(this);

            foreach (string s in SerialPort.GetPortNames())
            {
                Console.WriteLine("   {0}", s);
                cbx_comx.Items.Add(s);
            }
            if (cbx_comx.Items.Count > 0)
            {
                cbx_comx.SelectedIndex = 0;
            }

            if (serial_1.current_status == true)
            {
                btn_serial_sw.Text = "Close";
            }
            else
            {
                btn_serial_sw.Text = "Open";
            }





        }



        private void btn_serial_sw_Click(object sender, EventArgs e)
        {
            string portname;
            int baudrate;
            Parity parity;
            UInt16 databits;
            StopBits stopbits;



            if (serial_1.current_status == true)
            {
                serial_1.Serial_Close();
                btn_serial_sw.Text = "Open";
                tmr_getconf.Enabled = false;
                tmr_getvalue.Enabled = false;
            }
            else
            {
                portname = cbx_comx.SelectedItem.ToString();
                baudrate = 9600;
                parity = (Parity)Enum.Parse(typeof(Parity), "None", true);
                databits = 8;
                stopbits = (StopBits)Enum.Parse(typeof(StopBits), "1", true);

                serial_1.Serial_Open(portname, baudrate , parity, databits , stopbits);
                btn_serial_sw.Text = "Close";

            }
        }



        private void btn_getversion_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Console.WriteLine("Get some Conf Value\r\n");
            tmr_getconf.Interval = 3000;
            if (tbx_mbslaveid.TextLength > 0)
            {

                byte slaveid = Convert.ToByte(tbx_mbslaveid.Text.Trim());
                
                try
                {
                    ushort[] buf = serial_1.master.ReadHoldingRegisters(slaveid, 0, 30);

                    if (buf.Length == 30)
                    {
                        Console.WriteLine(buf.Length);

                        dataprocess_func.Data_ConfAnalysis(buf);
                        tbx_slaveid.Text = dataprocess_func.slaveid.ToString();

                        tbx_sncode.Text = "";
                        for(byte i = 0; i < 8; i ++)
                        {

                            tbx_sncode.Text += dataprocess_func.sncode[i].ToString("X");
                        }
                        //tbx_sncode.Text = dataprocess_func.sncode.ToString();
                        tbx_z_sen.Text = dataprocess_func.z_sen.ToString();
                        tbx_x_sen.Text = dataprocess_func.x_sen.ToString();
                        tbx_y_sen.Text = dataprocess_func.y_sen.ToString();
                        tbx_sp_lowpass.Text = dataprocess_func.sp_lowpass.ToString();
                        tbx_sp_highpass.Text = dataprocess_func.sp_highpass.ToString();
                        tbx_dp_lowpass.Text = dataprocess_func.dp_lowpass.ToString();
                        tbx_dp_highpass.Text = dataprocess_func.dp_highpass.ToString();
                        tbx_tem_c.Text = dataprocess_func.temp_c.ToString();
                        tbx_waveinterval.Text = dataprocess_func.wave_interval.ToString();
                        tbx_baudrate.Text = dataprocess_func.baud_rate.ToString();
                        tbx_parity.Text = dataprocess_func.parity.ToString();
                        tbx_stopbit.Text = dataprocess_func.stopbit.ToString();
                        tbx_x_angle.Text = dataprocess_func.x_angle.ToString();
                    }
                }
                catch
                {

                }


            }
            else
            {
                
            }

        }

        private void btn_clockslaveid_Click(object sender, EventArgs e)
        {
            if (tbx_mbslaveid.TextLength > 0)
            {

                byte slaveid = Convert.ToByte(tbx_mbslaveid.Text.Trim());

                try
                {
                    ushort[] buf = serial_1.master.ReadInputRegisters(slaveid, 97, 3);
                    if (buf.Length == 3)
                    {
                        tbx_version.Text = buf[0].ToString() + "." + buf[1].ToString() + "." + buf[2].ToString();

                        MessageBox.Show("Succeed");
                        tmr_getconf.Enabled = true;
                    }
                    else
                    {
                        tmr_getconf.Enabled = false;
                        MessageBox.Show("Failed");
                    }
                }
                catch
                {
                    tmr_getconf.Enabled = false;
                    MessageBox.Show("Failed");
                }
            }
        }

        private void tbx_mbslaveid_TextChanged(object sender, EventArgs e)
        {
            tmr_getconf.Enabled = false;
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(tabControl1.SelectedIndex == 0)
            {
                tmr_getconf.Enabled = true;
                tmr_getvalue.Enabled = false;
                Console.WriteLine("index: 0");
            }else if(tabControl1.SelectedIndex == 1)
            {
                tmr_getvalue.Enabled = false;
                tmr_getconf.Enabled = false;
                Console.WriteLine("index: 1");
            }
            else if(tabControl1.SelectedIndex == 2)
            {
                tmr_getvalue.Enabled = true;
                tmr_getconf.Enabled = false;
                Console.WriteLine("index: 2");
            }
            
        }


        public static void Delay(int milliSecond)
        {
            int start = Environment.TickCount;
            while (Math.Abs(Environment.TickCount - start) < milliSecond)//毫秒
            {
                Application.DoEvents();//可执行某无聊的操作
            }
        }


        public UInt32 getcount = 0;
        public UInt32 errcount = 0;
        private void tmr_getvalue_Tick(object sender, EventArgs e)
        {
            if (tbx_mbslaveid.TextLength > 0)
            {

                byte slaveid = Convert.ToByte(tbx_mbslaveid.Text.Trim());

                try
                {
                    getcount ++;

                    ushort[] buf_z = serial_1.master.ReadInputRegisters(slaveid, 0, 10);
                    Delay(100);
                    ushort[] buf_x = serial_1.master.ReadInputRegisters(slaveid, 10, 10);
                    Delay(100);
                    ushort[] buf_y = serial_1.master.ReadInputRegisters(slaveid, 20, 10);
                    Delay(100);
                    ushort[] temp = serial_1.master.ReadInputRegisters(slaveid, 30, 1);
                    
                    lvw_mbvalue.Items.Clear();

                    if (buf_z.Length == 10 && buf_x.Length == 10 && buf_y.Length == 10 && temp.Length == 1)
                    {
                        dataprocess channel_z = new dataprocess(this);
                        dataprocess channel_x = new dataprocess(this);
                        dataprocess channel_y = new dataprocess(this);
                        channel_z.Data_ValueAnalysis(buf_z);
                        channel_x.Data_ValueAnalysis(buf_x);
                        channel_y.Data_ValueAnalysis(buf_y);

                        ListViewItem lvw_base = new ListViewItem("基频");
                        lvw_base.SubItems.Add(channel_z.base_freq.ToString());
                        lvw_base.SubItems.Add(channel_x.base_freq.ToString());
                        lvw_base.SubItems.Add(channel_y.base_freq.ToString());
                        lvw_mbvalue.Items.Add(lvw_base);
                        lvw_mbvalue.Items[lvw_mbvalue.Items.Count - 1].EnsureVisible();

                        ListViewItem lvw_acc_p = new ListViewItem("加速度峰值");
                        lvw_acc_p.SubItems.Add(channel_z.acc_p.ToString());
                        lvw_acc_p.SubItems.Add(channel_x.acc_p.ToString());
                        lvw_acc_p.SubItems.Add(channel_y.acc_p.ToString());
                        lvw_mbvalue.Items.Add(lvw_acc_p);
                        lvw_mbvalue.Items[lvw_mbvalue.Items.Count - 1].EnsureVisible();

                        ListViewItem lvw_acc_rms = new ListViewItem("加速度有效值");
                        lvw_acc_rms.SubItems.Add(channel_z.acc_rms.ToString());
                        lvw_acc_rms.SubItems.Add(channel_x.acc_rms.ToString());
                        lvw_acc_rms.SubItems.Add(channel_y.acc_rms.ToString());
                        lvw_mbvalue.Items.Add(lvw_acc_rms);
                        lvw_mbvalue.Items[lvw_mbvalue.Items.Count - 1].EnsureVisible();

                        // ----------------
                        x_acc_rms = channel_x.acc_rms;
                        y_acc_rms = channel_y.acc_rms;
                        z_acc_rms = channel_z.acc_rms;
                        // ----------------

                        ListViewItem lvw_velocity_rms = new ListViewItem("速度有效值");
                        lvw_velocity_rms.SubItems.Add(channel_z.velocity_rms.ToString());
                        lvw_velocity_rms.SubItems.Add(channel_x.velocity_rms.ToString());
                        lvw_velocity_rms.SubItems.Add(channel_y.velocity_rms.ToString());
                        lvw_mbvalue.Items.Add(lvw_velocity_rms);
                        lvw_mbvalue.Items[lvw_mbvalue.Items.Count - 1].EnsureVisible();

                        ListViewItem lvw_dis_pp = new ListViewItem("位移峰峰值");
                        lvw_dis_pp.SubItems.Add(channel_z.dis_pp.ToString());
                        lvw_dis_pp.SubItems.Add(channel_x.dis_pp.ToString());
                        lvw_dis_pp.SubItems.Add(channel_y.dis_pp.ToString());
                        lvw_mbvalue.Items.Add(lvw_dis_pp);
                        lvw_mbvalue.Items[lvw_mbvalue.Items.Count - 1].EnsureVisible();

                        ListViewItem lvw_kur = new ListViewItem("峭度系数");
                        lvw_kur.SubItems.Add(channel_z.kurtosis_c.ToString());
                        lvw_kur.SubItems.Add(channel_x.kurtosis_c.ToString());
                        lvw_kur.SubItems.Add(channel_y.kurtosis_c.ToString());
                        lvw_mbvalue.Items.Add(lvw_kur);
                        lvw_mbvalue.Items[lvw_mbvalue.Items.Count - 1].EnsureVisible();

                        ListViewItem lvw_envelop = new ListViewItem("包络");
                        lvw_envelop.SubItems.Add(channel_z.kurtosis_c.ToString());
                        lvw_envelop.SubItems.Add(channel_x.kurtosis_c.ToString());
                        lvw_envelop.SubItems.Add(channel_y.kurtosis_c.ToString());
                        lvw_mbvalue.Items.Add(lvw_envelop);
                        lvw_mbvalue.Items[lvw_mbvalue.Items.Count - 1].EnsureVisible();


                        ListViewItem lvw_dis_rms = new ListViewItem("位移有效值");
                        lvw_dis_rms.SubItems.Add(channel_z.dis_rms.ToString());
                        lvw_dis_rms.SubItems.Add(channel_x.dis_rms.ToString());
                        lvw_dis_rms.SubItems.Add(channel_y.dis_rms.ToString());
                        lvw_mbvalue.Items.Add(lvw_dis_rms);
                        lvw_mbvalue.Items[lvw_mbvalue.Items.Count - 1].EnsureVisible();

                        float temperature = temp[0] / 100.0f;
                        ListViewItem lvw_temp = new ListViewItem("温度");
                        lvw_temp.SubItems.Add(temperature.ToString());
 
                        lvw_mbvalue.Items.Add(lvw_temp);
                        lvw_mbvalue.Items[lvw_mbvalue.Items.Count - 1].EnsureVisible();

                    }
                }
                catch
                {
                    errcount ++;



                }


                lab_errcount.Text = errcount.ToString();
                lab_getcount.Text = getcount.ToString();
                float prob;
                if(getcount > 0)
                {
                    prob = (float)((float)errcount / (float)getcount) * 100.0f;
                    lab_prob.Text = prob.ToString("F3") + "%";
                }
                else
                {
                    lab_prob.Text = "--";
                }
                
            }
            else
            {

            }
        }

        private void btn_zselcal_Click(object sender, EventArgs e)
        {
            float dif_value;

            dif_value = System.Math.Abs(z_acc_rms - 9.8f);

            if (dif_value > 2.0f)
            {
                MessageBox.Show("当前有效值和9.8差的太远了，还是手动校准吧！");
                return;
            }

            if (tbx_mbslaveid.TextLength > 0)
            {
                byte slaveid = Convert.ToByte(tbx_mbslaveid.Text.Trim());

                try
                {
                    serial_1.master.WriteSingleRegister(slaveid, 23, 0x0001);
                }
                catch
                {
                    MessageBox.Show("Failed");
                }
            }
            else
            {
                MessageBox.Show("No Slave ID");
            }


        }

        private void btn_xselcal_Click(object sender, EventArgs e)
        {
            float dif_value;
            dif_value = System.Math.Abs(x_acc_rms - 9.8f);

            if (dif_value > 2.0f)
            {
                MessageBox.Show("当前有效值和9.8差的太远了，还是手动校准吧！");
                return;
            }

            if (tbx_mbslaveid.TextLength > 0)
            {

                byte slaveid = Convert.ToByte(tbx_mbslaveid.Text.Trim());

                try
                {
                    serial_1.master.WriteSingleRegister(slaveid, 24, 0x0001);
                }
                catch
                {
                    MessageBox.Show("Failed");
                }
            }
            else
            {
                MessageBox.Show("No Slave ID");
            }
        }

        private void btn_yselcal_Click(object sender, EventArgs e)
        {
            float dif_value;
            dif_value = System.Math.Abs(y_acc_rms - 9.8f);

            if (dif_value > 2.0f)
            {
                MessageBox.Show("当前有效值和9.8差的太远了，还是手动校准吧！");
                return;
            }


            if (tbx_mbslaveid.TextLength > 0)
            {

                byte slaveid = Convert.ToByte(tbx_mbslaveid.Text.Trim());

                try
                {
                    serial_1.master.WriteSingleRegister(slaveid, 25, 0x0001);
                }
                catch
                {
                    MessageBox.Show("Failed");
                }
            }
            else
            {
                MessageBox.Show("No Slave ID");
            }
        }

        private void btn_refresh_sen_Click(object sender, EventArgs e)
        {
            if (tbx_mbslaveid.TextLength > 0)
            {
                byte slaveid = Convert.ToByte(tbx_mbslaveid.Text.Trim());
                try
                {
                    ushort[] buf = serial_1.master.ReadHoldingRegisters(slaveid, 9, 3);
                    float cur_zsen;
                    float cur_xsen;
                    float cur_ysen;

                    cur_zsen = buf[0] / 100.0f;
                    cur_xsen = buf[1] / 100.0f;
                    cur_ysen = buf[2] / 100.0f;

                    tbx_cur_zsen.Text = cur_zsen.ToString();
                    tbx_cur_xsen.Text = cur_xsen.ToString();
                    tbx_cur_ysen.Text = cur_ysen.ToString();

                    if(buf.Length == 3)
                    {
                        MessageBox.Show("刷新成功");
                    }
                    else
                    {
                        MessageBox.Show("刷新失败");
                    }
                }
                catch
                {
                    MessageBox.Show("Failed");
                }
            }
            else
            {
                MessageBox.Show("No Slave ID");
            }
        }

        private void btn_change_zsen_Click(object sender, EventArgs e)
        {
            
            
            if (tbx_mbslaveid.TextLength > 0)
            {
                byte slaveid = Convert.ToByte(tbx_mbslaveid.Text.Trim());

                try
                {
                    string value_str = Interaction.InputBox("修改值", "输入", "", -1, -1);
                    float value = Convert.ToSingle(value_str.Trim());
                    if(value > 0)
                    {
                        if (value > 655)
                        {
                            MessageBox.Show("值不能 > 655");
                            return;
                        }
                        ushort change_value = (ushort)(value * 100);

                        serial_1.master.WriteSingleRegister(slaveid, 9, change_value);
                    }
                    
                }
                catch
                {
                    MessageBox.Show("Failed");
                }
            }
            else
            {
                MessageBox.Show("No Slave ID");
            }
            
        }

        private void btn_change_xsen_Click(object sender, EventArgs e)
        {
            if (tbx_mbslaveid.TextLength > 0)
            {
                byte slaveid = Convert.ToByte(tbx_mbslaveid.Text.Trim());

                try
                {
                    string value_str = Interaction.InputBox("修改值", "输入", "", -1, -1);
                    float value = Convert.ToSingle(value_str.Trim());
                    if (value > 0)
                    {
                        if (value > 655)
                        {
                            MessageBox.Show("值不能 > 655");
                            return;
                        }
                        ushort change_value = (ushort)(value * 100);

                        serial_1.master.WriteSingleRegister(slaveid, 10, change_value);
                    }

                }
                catch
                {
                    MessageBox.Show("Failed");
                }
            }
            else
            {
                MessageBox.Show("No Slave ID");
            }
        }

        private void btn_change_ysen_Click(object sender, EventArgs e)
        {
            if (tbx_mbslaveid.TextLength > 0)
            {
                byte slaveid = Convert.ToByte(tbx_mbslaveid.Text.Trim());

                try
                {
                    string value_str = Interaction.InputBox("修改值", "输入", "", -1, -1);
                    float value = Convert.ToSingle(value_str.Trim());
                    if (value > 0)
                    {
                        if (value > 655)
                        {
                            MessageBox.Show("值不能 > 655");
                            return;
                        }
                        ushort change_value = (ushort)(value * 100);

                        serial_1.master.WriteSingleRegister(slaveid, 11, change_value);
                    }

                }
                catch
                {
                    MessageBox.Show("Failed");
                }
            }
            else
            {
                MessageBox.Show("No Slave ID");
            }
        }

        private void btn_rest_Click(object sender, EventArgs e)
        {

            if (tbx_mbslaveid.TextLength > 0)
            {
                byte slaveid = Convert.ToByte(tbx_mbslaveid.Text.Trim());

                try
                {
                    serial_1.master.WriteSingleRegister(slaveid, 21, 0x0001);
                    MessageBox.Show("命令已下发");
                }
                catch
                {
                    MessageBox.Show("Failed");
                }
            }
            else
            {
                MessageBox.Show("No Slave ID");
            }
        }

        private void btn_errclear_Click(object sender, EventArgs e)
        {
            lab_prob.Text = "--";
            lab_errcount.Text = "--";
            lab_getcount.Text = "--";
            getcount = 0;
            errcount = 0;
        }

        private void btn_getcom_Click(object sender, EventArgs e)
        {
            cbx_comx.Items.Clear();
            foreach (string s in SerialPort.GetPortNames())
            {
                Console.WriteLine("   {0}", s);
                cbx_comx.Items.Add(s);
            }
            if (cbx_comx.Items.Count > 0)
            {
                cbx_comx.SelectedIndex = 0;
            }
        }

        private void btn_changeslaveid_Click(object sender, EventArgs e)
        {
            if (tbx_mbslaveid.TextLength > 0)
            {
                byte slaveid = Convert.ToByte(tbx_mbslaveid.Text.Trim());

                try
                {
                    string value_str = Interaction.InputBox("修改值", "输入", "", -1, -1);
                    byte value = Convert.ToByte(value_str.Trim());
                    if (value > 0)
                    {
                        if (value >= 256)
                        {
                            MessageBox.Show("值不能 > 655");
                            return;
                        }
                        ushort change_value = (ushort)(value);

                        serial_1.master.WriteSingleRegister(slaveid, 0, change_value);
                    }

                }
                catch
                {
                    MessageBox.Show("Failed");
                }
            }
            else
            {
                MessageBox.Show("No Slave ID");
            }
        }
    }
}
