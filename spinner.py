import requests
import time
HUE_API ="http://10.108.45.150/api/bM3KTkXTTklZCltjf5K5zGaQxPosTeUh59FsXavY/lights"

xColor=1
yColor=1
max=256
block1=[7,8,12]
block2=[6,10,9,11]
block3=[1,2,3]


def changeLight(num,xColor,yColor,bri):
    requests.put(HUE_API + "/{}/state".format(num), json = {"on":True, "bri":bri, "xy":[xColor,yColor]})
    
def off(num):
    requests.put(HUE_API + "/{}/state".format(num), json = {"on":False})

def allOff():
    for i in range(1):
        off(i+1)

def blockOff(blockNum):
    for i in blockNum:
        off(i)


def spin(times):
    for i in range(times):
        n=i%3
        m=i%4
        changeLight(block1[n],xColor,yColor,max)
        time.sleep(0.1)
        changeLight(block3[n],xColor,yColor,max)
        time.sleep(0.1)
        changeLight(block2[m],xColor,yColor,max)
        off(block1[n])
        off(block2[m])
        off(block3[n])
        time.sleep(0,3)
        
spin(300)
            

