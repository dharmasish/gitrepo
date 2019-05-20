# -*- coding: utf-8 -*-
"""
Created on Fri Jun  1 22:41:55 2018

@author: dharma
"""


#ws= websocket.Websocket()

#ws.connect("")
import websocket
import pandas as pd
t1=pd.Timestamp.now()
i=0
a=''
data=[]
tym=[]
    
def timeout():
    t2=pd.Timestamp.now()
    ty=(t2-t1)
    tym.insert(len(tym),ty.components.milliseconds)
    t=ty.seconds
    
    if(t>=10):
        df=pd.DataFrame(columns=['value'])
        df.value=data
        df.plot()
        df.to_csv('8.csv', sep=',',index=False)
        del df
        ws.close()
    
def on_message(ws, message):
    global i
    global a
    global data
    #print(message)
    a=message
    i=i+1
    ws.send("# "+str(i))
    timeout()
    
    if(a[0]=='#'):
       a=a.split(' ')
       a=a[2][:-1]
       a = [int(e) for e in a.split(';')]
       data=data+a
    

def on_error(ws, error):
    print(error)

def on_close(ws):
    print("### closed ###")

def on_open(ws):
    result=ws.recv()
    print(result)
    ws.send("# 1")


if __name__ == "__main__":
    websocket.enableTrace(True)
    ws = websocket.WebSocketApp("ws://192.168.43.173:81"+ "/",
                              on_message = on_message,
                              on_error = on_error,
                              on_close = on_close)
    ws.on_open = on_open
    ws.run_forever()