# -*- coding: utf-8 -*-
"""
-------------------------------------------------
   文件名：      sent2ding
   描述：       发送消息给钉钉机器人
   作者：       Pilot.Phil
   日期：       Wed Aug 12 00:04:20 2020
-------------------------------------------------

----------------------使用-----------------------
sent2ding(tex) # 发送消息给钉钉机器人

-------------------------------------------------
"""

import json
import requests

#-----------------发送消息给钉钉机器人-----------------#
def sent2ding(tex):
    # 请求的URL，WebHook地址
    webhook = "https://oapi.dingtalk.com/robot/send?access_token=02159fd1df3c9dda7ae3c39cd7afcc3b881fac5a8891bf98bff4bc03e441f51b"
    header = {"Content-Type": "application/json","Charset": "UTF-8"}              # 构建请求头部
    message ={"msgtype": "text","text": {"content": tex},"at": {"isAtAll": True}} # 构建请求数据
    message_json = json.dumps(message)                                            # 对请求的数据进行json封装
    info = requests.post(url=webhook,data=message_json,headers=header)            # 发送请求
    print(info.text)                                                              # 打印返回的结果
    
    
if __name__ == "__main__":
    tex="testabcdef发送消息给钉钉机器人，。,.%&*#$@!~`+=-_【】{}[]:;'?/|\<>"
    sent2ding(tex)