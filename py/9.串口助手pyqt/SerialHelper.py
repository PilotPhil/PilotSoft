import sys
import numpy as np
from matplotlib import pyplot as plt
from UI_SerialPanel import Ui_window
from PyQt5.QtWidgets import QApplication,QWidget
from PyQt5.QtSerialPort import QSerialPort,QSerialPortInfo

# 串口类
class SerialHelper(QWidget): # 传入UI文件Ui_window

    def __init__(self,parent=None):
        super(QWidget,self).__init__(parent) # 用super非显式的调用父类构造函数

        self.ui = Ui_window()
        self.ui.setupUi(self) # 设置UI
        self.setWindowTitle("串口助手-Pilot.Phil") # 设置窗口标题

        self.findPorts()

        self.openPort()



    def findPorts(self):
        com_list = QSerialPortInfo.availablePorts()
        for com in com_list:
            self.ui.cb_serialPortName.addItem(str(com.portName())) #
            print(com.portName()) # 可用端口名
            print(com.description()) # 硬件描述
            # print(com.productIdentifier()) # 返回设备编号
            # print(com.standardBaudRates()) # 返回设备的支持波特率列表


    def openPort(self):
        # 1.设置端口号
        myCom=QSerialPort()
        com=self.ui.cb_serialPortName.currentText()
        myCom.setPortName(com)

        # 2.设置波特率
        bradu=self.ui.cb_bradrate.currentText()
        myCom.setBaudRate(int(bradu))

        # 3.设置数据位
        databit=self.ui.cb_dataBits.currentText()
        myCom.setDataBits(int(databit))

        # 4.设置校验位
        # parity=self.ui.cb_parity.currentText()
        # myCom.setParity(parity)

        # 5.设置停止位
        stopbit=self.ui.cb_stopBits.currentText()
        myCom.setStopBits()









if __name__=="__main__":
    app=QApplication(sys.argv)
    w=SerialHelper() # 实例化一个窗口对象SerialHelper
    w.show()
    sys.exit(app.exec_()) # 进入消息循环