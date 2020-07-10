using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Serialtool
{
    class dataprocess
    {
        // -----Conf -------
        public ushort slaveid;
        public ushort[] sncode = new ushort[8];
        public string version;
        public float z_sen;
        public float x_sen;
        public float y_sen;
        public float temp_c;
        public ushort wave_interval;
        public float x_angle;
        public ushort baud_rate;
        public ushort stopbit;
        public ushort parity;
        public ushort sp_lowpass;
        public ushort sp_highpass;
        public ushort dp_lowpass;
        public ushort dp_highpass;
        // -------------------
        // ------ Value ------
        public ushort base_freq;
        public float acc_p;
        public float acc_rms;
        public float velocity_rms;
        public float dis_pp;
        public float kurtosis_c;
        public float envelope;
        public float dis_rms;

        // --------------------



        Form1 mainform;
        public dataprocess(Form1 form)
        {
            mainform = form;
        }

        public void Data_ConfAnalysis(ushort[] buf )
        {
            if(buf.Length >= 20 )
            {
                slaveid = buf[0];
                sncode = buf.Skip(1).Take(8).ToArray();
                z_sen = buf[9] / 100.0f;
                x_sen = buf[10] / 100.0f;
                y_sen = buf[11] / 100.0f;
                sp_lowpass = buf[12];
                sp_highpass = buf[13];
                dp_lowpass = buf[14];
                dp_highpass = buf[15];
                temp_c = buf[16] /100.0f;
                wave_interval = buf[17];
                baud_rate = buf[18];
                parity = buf[19];
                stopbit = buf[20];
                x_angle = buf[22];
            }
        }

        public void Data_ValueAnalysis(ushort [] buf)
        {
            if(buf.Length >= 8)
            {
                base_freq = buf[0];
                acc_p = buf[1] / 100.0f;
                acc_rms = buf[2] / 100.0f;
                velocity_rms = buf[3] / 100.0f;
                dis_pp = buf[4] / 100.0f;
                kurtosis_c = buf[5] / 100.0f;
                envelope = buf[6] / 100.0f;
                dis_rms = buf[7] / 100.0f;
            }
        }



    }
}
