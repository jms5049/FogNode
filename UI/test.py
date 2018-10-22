import socket
import json

from flask import Flask, render_template, request
app = Flask(__name__)

ipaddr = '192.168.26.128'

@app.route('/')
def index():
   return render_template('index.html')

'''''''''
house setting
'''''''''

houseSettingValue = dict()

@app.route('/houseSetting')localhost
def houseSettingRender():
   return render_template('houseSetting.html')

@app.route('/houseResult',methods = ['POST', 'GET'])
def houserResult():
   if request.method == 'POST':

      houseResult = request.form.to_dict()

      for key, value in houseResult.items():
         print(key,value)

      houseSetting(houseResult)

      for key, value in houseSettingValue.items():
         print(key,value)

      toJSON(houseSettingValue)

      return render_template("houseResult.html",houseResult = houseResult, houseSettingValue = houseSettingValue)

def houseSetting(result):
   fruitCategori = result['fruitCategori']

   global houseSettingValue
   if fruitCategori == 'others':
      houseSettingValue = result
   else:
     defaultHouseSetting(fruitCategori)

def defaultHouseSetting(fruitCategori):

   global houseSettingValue
   if fruitCategori == 'strawberry' :
      houseSettingValue = {'fruitCategori':'strawberry', 'temperature': 25, 'humidity': 20}
   else :
      houseSettingValue = {'fruitCategori':'watermelon', 'temperature': 30, 'humidity': 15}


'''''''''
alarmSetting
'''''''''

alarmSettingValue = dict()

@app.route('/alarmSetting')
def alarmSettingRender():
   return render_template('alarmSetting.html')

@app.route('/alarmResult',methods = ['POST', 'GET'])
def alarmResult():
   if request.method == 'POST':

      alarmResult = request.form.to_dict()

      for key, value in alarmResult.items():
         print(key,value)

      alarmSetting(alarmResult)

      for key, value in alarmSettingValue.items():
         print(key,value)

      toJSON(alarmSettingValue)

      return render_template("alarmResult.html",alarmResult = alarmResult, alarmSettingValue = alarmSettingValue)

def alarmSetting(result):
   global alarmSettingValue
   alarmSettingValue = result

'''''''''
JSON
'''''''''

def toJSON(setting):
   JSONSetting = json.dumps(setting)
   print('json',JSONSetting)
   sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
   sock.connect((ipaddr, 12345))
   sock.sendall(JSONSetting.encode('utf-8'))
   print('send success')




if __name__ == '__main__':
   app.run(host='0.0.0.0')
