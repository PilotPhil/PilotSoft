using System;
using System.IO.Ports;

namespace PilotSoft.Serial
{
    public class SerialPortFactory
    {
        /// <summary>
        /// 快速创建9600波特率串口对象 常用
        /// </summary>
        /// <param name="portName">端口名，如COM12</param>
        /// <returns></returns>
        public SerialPort QuickCreateSerialPort9600(string portName)
        {
            return new SerialPort(portName, 9600, Parity.None, 8, StopBits.One);
        }

        /// <summary>
        /// 快速创建19200波特率串口对象 常用
        /// </summary>
        /// <param name="portName">端口名，如COM12</param>
        /// <returns></returns>
        public SerialPort QuickCreateSerialPort19200(string portName)
        {
            return new SerialPort(portName, 19200, Parity.None, 8, StopBits.One);
        }

        /// <summary>
        /// 快速创建串口对象 常用
        /// </summary>
        /// <param name="portName">端口名，如：COM12</param>
        /// <param name="baudRate">波特率，如：9600</param>
        /// <returns></returns>
        public SerialPort QuickCreateSerialPort19200(string portName, int baudRate)
        {
            return new SerialPort(portName, baudRate, Parity.None, 8, StopBits.One);
        }

        /// <summary>
        /// 通过字符串参数创建串口对象
        /// </summary>
        /// <param name="portName"></param>
        /// <param name="baudrate"></param>
        /// <param name="parity"></param>
        /// <param name="databits"></param>
        /// <param name="stopbits"></param>
        /// <returns></returns>
        public SerialPort CreateSerialPortNormal(string portName,
                                                      int baudrate,
                                                      string parity,
                                                      int databits,
                                                      string stopbits)
        {
            var serialPort = new SerialPort();

            try
            {
                serialPort.PortName = portName;
                serialPort.BaudRate = baudrate;

                serialPort.Parity = new Func<Parity>(() =>
                {
                    if (parity == "None" || parity == "none" || parity == "无")
                        return Parity.None;
                    else if (parity == "Odd" || parity == "odd" || parity == "奇")
                        return Parity.Odd;
                    else if (parity == "Even" || parity == "even" || parity == "偶")
                        return Parity.Even;
                    else if (parity == "Space" || parity == "space" || parity == "0")
                        return Parity.Space;
                    else if (parity == "Mark" || parity == "mark" || parity == "1")
                        return Parity.Mark;
                    else
                        throw new Exception("Parity Param Not Right Exception from pilot.serial");
                }).Invoke();

                serialPort.DataBits = databits;

                serialPort.StopBits = new Func<StopBits>(() =>
                {
                    if (stopbits == "None" || stopbits == "none" || stopbits == "无")
                        return StopBits.None;
                    else if (stopbits == "One" || stopbits == "one" || stopbits == "1")
                        return StopBits.One;
                    else if (stopbits == "Two" || stopbits == "two" || stopbits == "2")
                        return StopBits.Two;
                    else if (stopbits == "OnePointFive" || stopbits == "onepointfive" || stopbits == "1.5")
                        return StopBits.OnePointFive;
                    else
                        throw new Exception("Stopbits Param Not Right Exception from pilot.serial");
                }).Invoke();
            }
            catch
            {
                throw;
            }
            return serialPort;
        }

        /// <summary>
        /// 通过字符串参数创建串口对象
        /// </summary>
        /// <param name="portName"></param>
        /// <param name="baudrate"></param>
        /// <param name="parity"></param>
        /// <param name="databits"></param>
        /// <param name="stopbits"></param>
        /// <returns></returns>
        public SerialPort CreateSerialPortByString(string portName,
                                                        string baudrate,
                                                        string parity,
                                                        string databits,
                                                        string stopbits)
        {
            return CreateSerialPortNormal(portName, int.Parse(baudrate), parity, int.Parse(databits), stopbits);
        }
    }
}
