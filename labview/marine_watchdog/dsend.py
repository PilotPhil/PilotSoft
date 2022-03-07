from dingtalkchatbot.chatbot import DingtalkChatbot
def dsend(message):
    webhook = 'https://oapi.dingtalk.com/robot/send?access_token=da01d4d79174ee65acc7a99d4614bf90ffb217af4f74afc947a6ec6b7654ff05'
    bot = DingtalkChatbot(webhook)
    bot.send_text(msg=message, is_at_all=True)
if __name__ == '__main__':
    dsend(get_time())
