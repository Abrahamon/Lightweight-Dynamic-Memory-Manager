import xml.etree.ElementTree as XML
import os

ruta=os.getcwd()
rutaFinal=str(ruta)+"/configs.xml"
tree = XML.parse(rutaFinal)
root = tree.getroot()


def setHARDWARE():
    pHard=raw_input("Set vHardware: ")
    if(pHard == "true"):
        for vHARDWARE in root.iter("vHARDWARE"):
            vHARDWARE.set("value","true")
        setUSB()
    elif(pHard == "false"):
        for vHARDWARE in root.iter("vHARDWARE"):
            vHARDWARE.set("value","false")
    else:
	print("Check your input!!")
        setHARDWARE()

def setGUI():
    pGUI=raw_input("Set vGUI: ")
    if(pGUI == "true"):
        for vGUI in root.iter("vGUI"):
            vGUI.set("value","true")
    elif(pGUI == "false"):
        for vGUI in root.iter("vGUI"):
            vGUI.set("value","false")
    else:
	print("Check your input!!")
        setGUI()  
  
def setDEBUG():
    pDEBUG=raw_input("Set vDEBUG: ")
    if(pDEBUG == "true"):
        for vDEBUG in root.iter("vDEBUG"):
            vDEBUG.set("value","true")
    elif(pDEBUG == "false"):
        for vDEBUG in root.iter("vDEBUG"):
            vDEBUG.set("value","false")
    else:
	print("Check your input!!")
        setDEBUG()  

def setUSB():
    pUSB=raw_input("Set vUSB: ")
    if(pUSB == "0"):
        for vUSB in root.iter("vUSB"):
            vUSB.set("value","/dev/ttyACM0")
    elif(pUSB == "1"):
        for vUSB in root.iter("vDEBUG"):
            vUSB.set("value","/dev/ttyACM1")
    else:
	print("Check your input!!")
        setUSB()

def setPORT():
    pPORT=raw_input("Enter PORT: ")
    pStr = pPORT.strip()
    for TARGET_PORT in root.iter("TARGET_PORT"):
        TARGET_PORT.set("value",pStr)

def setIP():
    pIP=raw_input("Enter current IP: ")
    pStr = pIP.strip()
    for TARGET_IP in root.iter("TARGET_IP"):
        TARGET_IP.set("value",pStr)

mode = raw_input("Please enter configuration mode: ")
if(mode == "run"):
    print("")
elif(mode == "user"):
    print("***** User Mode *****")
    setDEBUG()
    setGUI()
    setHARDWARE()
elif(mode == "admin"):
    print("***** Admin Mode *****")
    setPORT()
    setIP()
    setGUI()
    setDEBUG()
    setHARDWARE()

tree.write(rutaFinal)
