using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using PilotSoft.Serial;
using PilotSoft.Serial.Models;
using System;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Timers;
using System.Windows;

namespace SerialTest.ViewModel
{
    public class MainViewModel : ViewModelBase
    {
        /// <summary>
        /// ctor
        /// </summary>
        public MainViewModel()
        {
            SerialNotifiableModel.PortList = SerialUtil.SearchPortList();
            timer.Elapsed += (s, e) => { SendData(SerialNotifiableModel.String2Send); };
            serialUtil.SerialDataReceived += ReadData;
        }

        private void ReadData(byte[] bytes)
        {
            var msg = "";
            if (serialNotifiableModel.HexRead == true)
            {
                msg = serialUtil.BytesToHexString(bytes);
            }
            else
            {
                msg = Encoding.UTF8.GetString(bytes);
            }

            SerialNotifiableModel.ReceivedString += msg + "\n";
        }

        private void SendData(String msg)
        {
            if (serialUtil == null || serialUtil.IsOpen == false)
            {
                MessageBox.Show("串口未打开");
                return;
            }

            if (msg == String.Empty || msg == "")
                return;

            if (SerialNotifiableModel.HexSend == true)
            {
                serialUtil.SendHexData(msg);
            }
            else
            {
                serialUtil.SendData(msg);
            }
        }

        #region property
        private SerialUtil serialUtil = new();
        private readonly Timer timer = new();

        private SerialNotifiableModel serialNotifiableModel = new();
        /// <summary>
        /// SerialNotifiableModel
        /// </summary>
        public SerialNotifiableModel SerialNotifiableModel
        {
            get { return serialNotifiableModel; }
            set
            {
                if (serialNotifiableModel == value) { return; }
                serialNotifiableModel = value;
                RaisePropertyChanged(() => SerialNotifiableModel);
            }
        }

        private RelayCommand<object> _myCommand1;
        /// <summary>
        /// open 的命令
        /// </summary>
        public RelayCommand<object> OpenCommand
        {
            get
            {
                return _myCommand1 ?? (_myCommand1 = new RelayCommand<object>(Open));
            }
        }
        private void Open(object param)
        {
            try
            {
                var newPort = SerialPortFactory.CreateSerialPortNormal(SerialNotifiableModel.Port,
                                                                             SerialNotifiableModel.Baud,
                                                                             SerialNotifiableModel.Parity,
                                                                             SerialNotifiableModel.DataBits,
                                                                             SerialNotifiableModel.StopBits);
                if (serialUtil.IsOpen == true)
                {
                    serialUtil.ClosePort();
                }
                else
                {
                    serialUtil.SetSerialPort(newPort);
                    serialUtil.OpenPort();
                }
                SerialNotifiableModel.SwitchContent = serialUtil.IsOpen ? "close" : "open";
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        private RelayCommand<object> _myCommand2;
        /// <summary>
        /// ClearReceived 的命令
        /// </summary>
        public RelayCommand<object> ClearReceivedCommand
        {
            get
            {
                return _myCommand2 ?? (_myCommand2 = new RelayCommand<object>(ClearReceived));
            }
        }
        private void ClearReceived(object param)
        {
            SerialNotifiableModel.ReceivedString = string.Empty;
        }

        private RelayCommand<object> _myCommand3;
        /// <summary>
        /// ClearMsg2Send 的命令
        /// </summary>
        public RelayCommand<object> ClearMsg2SendCommand
        {
            get
            {
                return _myCommand3 ?? (_myCommand3 = new RelayCommand<object>(ClearMsg2Send));
            }
        }
        private void ClearMsg2Send(object param)
        {
            SerialNotifiableModel.String2Send = string.Empty;
        }

        private RelayCommand<object> _myCommand4;
        /// <summary>
        /// SendData 的命令
        /// </summary>
        public RelayCommand<object> SendDataCommand
        {
            get
            {
                return _myCommand4 ?? (_myCommand4 = new RelayCommand<object>(SendData));
            }
        }
        private void SendData(object param)
        {
            SendData(SerialNotifiableModel.String2Send);
        }

        private RelayCommand<object> _myCommand5;
        /// <summary>
        /// SetTimedsending 的命令
        /// </summary>
        public RelayCommand<object> SetTimedsendingCommand
        {
            get
            {
                return _myCommand5 ?? (_myCommand5 = new RelayCommand<object>(SetTimedsending));
            }
        }
        private void SetTimedsending(object param)
        {
            if (SerialNotifiableModel.IsTimedSend == true)
            {
                timer.Stop();
                timer.Interval = SerialNotifiableModel.TimeSpan;
                timer.Start();
            }
            else
            {
                timer.Stop();
            }
        }

        #endregion
    }
}