using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;

namespace PilotSoft.Serial.Models
{
    public class SerialNotifiableModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        #region params list
        public virtual List<string> PortList { get; set; } = new List<string>();
        public virtual List<int> BaudList { get; set; } = new List<int>() { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200, 128000, 256000, 460800 };
        public virtual List<string> ParityList { get; set; } = new List<string>() { "Even", "Mark", "None", "Odd" };
        public virtual List<int> DataBitsList { get; set; } = new List<int>() { 5, 6, 7, 8 };
        public virtual List<string> StopBitsList { get; set; } = new List<string>() { "One", "OnePointFive", "Two" };
        #endregion

        #region params
        private string port = string.Empty;
        public virtual string Port
        {
            get { return port; }
            set
            {
                port = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Port"));
            }
        }

        private int baud = 9600;
        public virtual int Baud
        {
            get { return baud; }
            set
            {
                baud = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Baud"));
            }
        }

        private string parity = "None";
        public virtual string Parity
        {
            get { return parity; }
            set
            {
                parity = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Parity"));
            }
        }

        private int dataBits = 8;
        public virtual int DataBits
        {
            get { return dataBits; }
            set
            {
                dataBits = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("DataBits"));
            }
        }

        private string stopBits = "One";
        public virtual string StopBits
        {
            get { return stopBits; }
            set
            {
                stopBits = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("StopBits"));
            }
        }

        private bool hexRead = false;
        public virtual bool HexRead
        {
            get { return hexRead; }
            set
            {
                hexRead = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("HexRead"));
            }
        }

        private bool hexSend = false;
        public virtual bool HexSend
        {
            get { return hexSend; }
            set
            {
                hexSend = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("HexSend"));
            }
        }

        private bool isTimedSend = false;
        public virtual bool IsTimedSend
        {
            get { return isTimedSend; }
            set
            {
                isTimedSend = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("IsTimedSend"));
            }
        }

        private double timeSpan = 1000;
        public virtual double TimeSpan
        {
            get { return timeSpan; }
            set
            {
                timeSpan = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("TimeSpan"));
            }
        }

        private string receivedString = string.Empty;
        public virtual string ReceivedString
        {
            get { return receivedString; }
            set
            {
                receivedString = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("ReceivedString"));
            }
        }

        private string string2Send = string.Empty;
        public virtual string String2Send
        {
            get { return string2Send; }
            set
            {
                string2Send = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("String2Send"));
            }
        }

        private string switchContent = "open";
        public virtual string SwitchContent
        {
            get { return switchContent; }
            set
            {
                switchContent = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("SwitchContent"));
            }
        }
        #endregion
    }
}
