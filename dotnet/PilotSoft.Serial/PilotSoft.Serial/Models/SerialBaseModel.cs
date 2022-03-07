using System;
using System.Collections.Generic;
using System.Text;

namespace PilotSoft.Serial.Models
{
    public class SerialBaseModel
    {
        #region params list
        public virtual List<string> PortList { get; set; } = new List<string>();
        public virtual List<int> BaudList { get; set; } = new List<int>() { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200, 128000, 256000, 460800 };
        public virtual List<string> ParityList { get; set; } = new List<string>() { "Even", "Mark", "None", "Odd" };
        public virtual List<int> DataBitsList { get; set; } = new List<int>() { 5, 6, 7, 8 };
        public virtual List<string> StopBitsList { get; set; } = new List<string>() { "One", "OnePointFive", "Two" };
        #endregion

        #region params
        public virtual string Port { get; set; }= string.Empty;
        public virtual int Baud { get; set; } = 9600;
        public virtual string Parity { get; set; } = "None";
        public virtual int DataBits { get; set; } = 8;
        public virtual string StopBits { get; set; } = "One";
        public virtual bool HexRead { get; set; }= false;
        public virtual bool HexSend { get; set; } = false;
        public virtual bool IsTimedSend { get; set; }= false;
        public virtual double TimeSpan { get; set; } = 1000;
        public virtual string ReceivedString { get; set; }= string.Empty;
        public virtual string String2Send { get; set; }= string.Empty;
        public virtual string SwitchContent { get; set; }= "open";
        #endregion
    }
}
