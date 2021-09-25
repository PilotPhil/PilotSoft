using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Text;

namespace PilotSoft.Serial
{
    public class SerialUtil
    {
        private readonly SerialPort serialPort;
        public bool IsOpen { get; set; } = false;

        /// <summary>
        /// 获取可用串口名
        /// </summary>
        /// <returns></returns>
        public static string[] GetPortNameList()
        {
            return SerialPort.GetPortNames();
        }

        /// <summary>
        /// ctor
        /// </summary>
        /// <param name="serialPort"></param>
        public SerialUtil(SerialPort serialPort)
        {
            this.serialPort = serialPort;
        }

        /// <summary>
        /// 打开串口
        /// </summary>
        /// <returns>操作是否成功</returns>
        public bool OpenPort()
        {
            try
            {
                if (serialPort.IsOpen == true)
                {
                    serialPort.Close();
                }
                serialPort.Open();
                IsOpen = true;
            }
            catch
            {
                IsOpen = false;
                throw;
            }
            return IsOpen;
        }

        /// <summary>
        /// 关闭串口
        /// </summary>
        public void ClosePort()
        {
            if(serialPort.IsOpen==true)
            {
                serialPort.Close();
            }
        }


    }
}
