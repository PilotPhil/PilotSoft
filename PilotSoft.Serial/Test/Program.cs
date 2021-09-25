using System;
using PilotSoft.Serial;

namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
            CreateTest();
            Console.WriteLine("Hello World!");
        }

        static void CreateTest()
        {
            SerialPortFactory factory = new SerialPortFactory();
            var obj1 = factory.QuickCreateSerialPort9600("COM8");
            var obj2 = factory.QuickCreateSerialPort19200("COM8");
            var obj3 = factory.CreateSerialPortNormal("COM8", 9600, "None", 8, "One");
            var obj4 = factory.CreateSerialPortByString("COM8", "9600", "None", "8", "One");

            SerialUtil serialUtil = new SerialUtil(obj4);
            //serialUtil.OpenPort();
            //serialUtil.ClosePort();
        }
    }
}
