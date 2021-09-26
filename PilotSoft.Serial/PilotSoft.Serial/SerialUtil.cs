using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Text;
using System.Linq;

namespace PilotSoft.Serial
{
    public class SerialUtil
    {
        private SerialPort serialPort = null;
        public bool IsOpen { get; set; } = false;
        public bool IsFirstSet { get; set; } = false;
        public Action<byte[]> SerialDataReceived;
        public string CurrentMsg { get; set; } = string.Empty;


        /// <summary>
        /// ctor
        /// </summary>
        /// <param name="serialPort"></param>
        public SerialUtil()
        {

        }

        #region set open close
        /// <summary>
        /// set the serial port
        /// </summary>
        /// <param name="serialPort"></param>
        public void SetSerialPort(SerialPort serialPort)
        {
            if (serialPort == null)
                return;

            IsFirstSet = true;
            this.serialPort = serialPort;
            serialPort.DataReceived += ReadData;
        }

        /// <summary>
        /// open the serial port
        /// </summary>
        public void OpenPort()
        {
            try
            {
                if (serialPort == null)
                    return;

                if (serialPort.IsOpen == false)
                {
                    serialPort.Open();
                    IsOpen = true;
                }
            }
            catch
            {
                throw;
            }

        }

        /// <summary>
        /// close the serial port
        /// </summary>
        public void ClosePort()
        {
            try
            {
                if (serialPort == null)
                    return;

                if (serialPort.IsOpen == true)
                {
                    serialPort.Close();
                    IsOpen = false;
                }
            }
            catch
            {
                throw;
            }
        }

        #endregion


        #region read & write
        /// <summary>
        /// read data
        /// </summary>
        /// <returns></returns>
        public void ReadData(object sender, SerialDataReceivedEventArgs e)
        {
            var bytes2read = serialPort.BytesToRead;
            var buffer = new byte[bytes2read];
            serialPort.Read(buffer, 0, bytes2read);
            SerialDataReceived?.Invoke(buffer);
        }

        /// <summary>
        /// send data
        /// </summary>
        /// <param name="msg"></param>
        public void SendData(string msg)
        {
            var bytes = Encoding.UTF8.GetBytes(msg);
            serialPort.Write(bytes, 0, bytes.Length);
        }

        /// <summary>
        /// send hex data
        /// </summary>
        /// <param name="msg"></param>
        public void SendHexData(string msg)
        {
            var bytes = StringToHexBytes(msg, Encoding.UTF8);
            serialPort.Write(bytes, 0, bytes.Length);
        }


        /// <summary>
        /// StringToHexString
        /// </summary>
        /// <param name="s"></param>
        /// <param name="encode"></param>
        /// <returns></returns>
        public string BytesToHexString(byte[] bytes)
        {
            string result = string.Empty;
            bytes.ToList().ForEach(b => result += Convert.ToString(b, 16) + " ");
            return result;
        }

        /// <summary>
        /// HexStringToString
        /// </summary>
        /// <param name="hs"></param>
        /// <param name="encode"></param>
        /// <returns></returns>
        private byte[] StringToHexBytes(string hs, Encoding encode)
        {
            //以%分割字符串，并去掉空字符
            string[] chars = hs.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            byte[] b = new byte[chars.Length];
            //逐个字符变为16进制字节数据
            for (int i = 0; i < chars.Length; i++)
            {
                b[i] = Convert.ToByte(chars[i], 16);
            }
            //按照指定编码将字节数组变为字符串
            return b;
        }

        #endregion

        /// <summary>
        /// search port in the computer
        /// </summary>
        /// <returns></returns>
        public static List<string> SearchPortList()
        {
            return SerialPort.GetPortNames().ToList();
        }
    }
}
