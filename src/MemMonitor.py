#! /usr/bin/python
# -*- coding: UTF8 -*-
##### Bibliotecas Utilizadas #####
##################################
import socket
from Tkinter import *
from threading import Thread
import threading
import time
import serial
import os
from xml.dom import minidom
##################################

"""
createVisualMemory
Funcion encargada de crear los objetos
que representan cada bloque de memoria
del vHeap, en funcion del tamaño de
y de la divison.

@author Fabian A. Solano Madriz
@Param Size tamaño del vHeap
@Param MemDivision tamaño de cada bloque de memoria
"""

def loadXMLParameters():
    global vPORT,vDEBUG,vHARDWARE,vGUI,vUSB
    ruta=os.getcwd()
    rutaFinal=str(ruta)+"/configs.xml"
    xmlDoc = minidom.parse(rutaFinal)


    pPort = xmlDoc.getElementsByTagName('TARGET_PORT')
    pDebug= xmlDoc.getElementsByTagName('vDEBUG')
    pHard = xmlDoc.getElementsByTagName('vHARDWARE')
    pVisual=xmlDoc.getElementsByTagName('vGUI')
    pUSB   =xmlDoc.getElementsByTagName('vUSB')

    load_DEBUG=pDebug[0].attributes['value'].value
    load_HARD=pHard[0].attributes['value'].value
    load_PORT=pPort[0].attributes['value'].value
    load_GUI =pVisual[0].attributes['value'].value
    load_USB =pUSB[0].attributes['value'].value
    if(load_DEBUG == "true"):   #Se define vDEBUG
        vDEBUG = True
    else:
        vDEBUG = False
    if(load_HARD == "true"):    #Se define vHARDWARE
        vHARDWARE = True
    else:
        vHARDWARE = False
    if(load_GUI == "true"):     #Se define vGUI
        vGUI = True
    else:
        vGUI = False
    vPORT = int(load_PORT)      #Se define vPORT
    vUSB  = load_USB            #Se define el puerto USB del Arduino
    
def createVisualMemory(Size,MemDivision):
    global MemoryBlockList,memoryCanvas,numMemoryBlocks
        
    def getMemBlocks(Size,MemDivision):
        result=Size/MemDivision
        if(isinstance(result,int)):
            return int(result)
        else:
            return int(result)+1


    numMemoryBlocks = getMemBlocks(Size,MemDivision) #Cantidad Total de Bloques
    MemoryChunckSize = (numMemoryBlocks*30)          #Cantidad Total de Pixeles para todos los bloques
    HalfMemoryChunckSize = MemoryChunckSize/2        #Mita de la Cantidad total de Pixeles
    scrRegion=(0,0,400,MemoryChunckSize+(MemoryChunckSize*.005))#Region de Scroll
                                                                    #Total de Pixeles + un 0.005
    coordsInfo = [5,5,180,30,numMemoryBlocks]   #Lista con Valores de Coordenadas(Cambian en cada iteracion)
    MemoryBlockList = []                        #Lista de Bloques de Memoria (objetos Canvas)
    print("NUMERO DE BLOQUE DE MEMORIA " + str(numMemoryBlocks))
    print("TAMAÑO DEL CANVAS DE MEMORIA " + str(MemoryChunckSize))
    if(vGUI):   
        memoryCanvas = Canvas(window, width=300, height=600,borderwidth=0,
                              highlightthickness=0,bg="#06072B")

        memoryCanvas.config(scrollregion=scrRegion)
        memoryCanvas.pack(padx=1,pady=0)
        
        


    ##### Ciclo Dibujo de Bloques de Memoria ###################################################
    ############################################################################################
    iterator = 1;
    while coordsInfo[4] != 0:                   #Mientras que la cantidad de bloque sea != 0

        #Crea el bloque en las coordenadas correspondientes
        if(vGUI):
            blockGUI = memoryCanvas.create_rectangle(coordsInfo[0],
                                                     coordsInfo[1],
                                                     coordsInfo[2],
                                                     coordsInfo[3],width=0, fill="white")
            memoryCanvas.create_text(coordsInfo[0]+10, coordsInfo[1]+10, anchor=W,
                                     font="Arial",text="ID: "+str(iterator-1))
        else:
            blockGUI = "null"
        block = [blockGUI,False]
        MemoryBlockList.append(block)   #Añade el bloque creado a la lista
        coordsInfo[1] += 30             #Aumenta las coordenadas en 30
        coordsInfo[3] += 30
        coordsInfo[4] -= 1              #Reduce el numero de elementos crear
        
        porcentajeCompletado = (iterator*100)/numMemoryBlocks
        if(vGUI):
            fillLoadingBars(porcentajeCompletado,MemDivision)
        iterator+=1
    
    ############################################################################################
    ################################# UI Elements ##############################################
    ############################################################################################
    if(vGUI):
        global entry,TotalBar,graphCanvas,actualTIME

        actualTIME = 0
        
        contGraph = Canvas(window, width=530, height=400,borderwidth=0,
                              highlightthickness=0,bg="#06072B")
        contGraph.place(x=620,y=50)
        xGraphCanvas = Canvas(window,width=518, height=388, bg="#FFFFFF")
        xGraphCanvas.place(x=625,y=55)

        graphCanvas = Canvas(window,width=470, height=388, bg="#FFFFFF")
        graphCanvas.place(x=673,y=55)
        
        graphCanvas.config(scrollregion=(0,0,3000, 1000)) 
        
        memoryCanvas.place(x=15,y=3)            #Coloca el canvas en posicion correcta
        hbar=Scrollbar(window,orient=VERTICAL)  #Crea el scrollbar para el canvas
        hbar.pack(side=LEFT,fill=Y)             #Coloca el scrollbar a la izquierda
        hbar.config(command=memoryCanvas.yview) #Añade el canvas al scrollbar
        memoryCanvas.config(yscrollcommand=hbar.set)#Añade el scrollbar al canvas

        xbar=Scrollbar(window,orient=HORIZONTAL)    #Crea el scrollbar para el grafico
        xbar.pack(side=BOTTOM,fill=X)               #Coloca el scrollbar abajo
        xbar.config(command=graphCanvas.xview)      #Añade el canvas al scrollbar
        graphCanvas.config(xscrollcommand=xbar.set) #Añade el scrollbar al canvas

        
        loadScreen.destroy()                    #Destruye la ventana de carga

        
        contenedor.create_text(350, 40, anchor=W, font="Arial",text="Current Memory Usage")
        contenedor.create_text(625, 40, anchor=W, font="Arial",text="Total Memory Usage")
        contenedor2 = Canvas(window,width=250, height=400, bg="#06072B")
        contenedor2.place(x=345,y=50)

        
        
        TotalBar = Canvas(window,width=240, height=390, bg="#FFFFFF")
        TotalBar.place(x=350,y=55)

        
        
        for i in range(0,11):
            TotalBar.create_text(5, 370-(i*35), anchor=W, font="Arial",text=str(i*10)+"%")
            xGraphCanvas.create_text(5, 370-(i*35), anchor=W, font="Arial",text=str(i*10)+"%")
            graphCanvas.create_text(5+(i*45), 382, anchor=W, font="Arial",text=str((i+1)*10))
        
        botonA = Button(window,width=7,height=2,command=lambda: debugMemory(0,"","",""),text="Change",bg="#000000",fg="#FFFFFF")
        botonA.place(x=335,y=550)

        entry = Entry(window)
        entry.place(x=420,y=560)

        startTIMER()
    ############################################################################################
    
def setMemoryGraphicBar():
    global MemoryBlockList,numMemoryBlocks,TotalBar
    blocksUsed = 0
    for i in range(0,len(MemoryBlockList)):
        if(MemoryBlockList[i][1] == True):
            blocksUsed+=1

    porcentajeCompletado = (blocksUsed*100)/numMemoryBlocks #Porcentaje de Memoria
    #print("Porcentaje: " + str(porcentajeCompletado))

    if(vGUI):
        Pos = 370-((porcentajeCompletado*350)/100) #Posicion de la Barra De Memoria
        TotalBar.delete("Bar")
        TotalBar.create_rectangle(75,380,150,Pos,width=0, fill="green",tags="Bar")
    else:
        if(vDEBUG):
            print("Status bar was not painted. Check XML file")
    return porcentajeCompletado

"""
setMemoryBlock
Funcion encargada de actualizar el
valor de n bloques de memoria. Ya sea
que se encuentra algun datos almacenado
o que el bloque se encuentra libre

@author Fabian A. Solano Madriz
@Param pUsageFlag Indica si hay un dato almacenado
@Param pStart posicion inicial de bloque a actualizar
@Param pEnd posicion final de bloque a actualizar
"""
def setMemoryBlock(pUsageFlag,pStart,pEnd):
    global MemoryBlockList,memoryCanvas,entry
    porcentajeCompletado = setMemoryGraphicBar()

    if(pUsageFlag == True):
        for i in range(pStart,pEnd):
            if(vGUI):
                memoryCanvas.itemconfig(MemoryBlockList[i][0],fill="red")
            MemoryBlockList[i][1] = True
    else:
        for i in range(pStart,pEnd):
            if(vGUI):
                memoryCanvas.itemconfig(MemoryBlockList[i][0],fill="white")
            MemoryBlockList[i][1] = False

    if(vHARDWARE):
        setArduinoGraphicBar(porcentajeCompletado)
    else:
        if(vDEBUG):
            print("Did not sent information to Arduino. Check XML file")

def debugMemory(Mode,pSet,pStart,pEnd):
    global MemoryBlockList,memoryCanvas,entry
    if(Mode==0):
        data = entry.get()
        data= data.split("#")
        pStart = int(data[1])
        pEnd = int(data[2])
    else:
        data=pSet+"#"+"Null"
        
        data=data.split("#")

    
    if(data[0] == "True"):
        for i in range(pStart,pEnd):
            if(vGUI):
                memoryCanvas.itemconfig(MemoryBlockList[i][0],fill="red")
            MemoryBlockList[i][1] = True
    else:
        for i in range(pStart,pEnd):
            if(vGUI):
                memoryCanvas.itemconfig(MemoryBlockList[i][0],fill="white")
            MemoryBlockList[i][1] = False
    if(vGUI):
        entry.delete(0, 'end')

    porcentajeCompletado = setMemoryGraphicBar()
    
    if(vHARDWARE):
        setArduinoGraphicBar(porcentajeCompletado)
    else:
        if(vDEBUG):
            print("Did not sent information to Arduino. Check XML file")

def setArduinoGraphicBar(porcentaje):
    redondeo = int(round(porcentaje,-1)//10)
    final = (redondeo)-1
    if(vDEBUG):
        print("Sent to arduino " + str(redondeo)+ "0"+"%")
    if(final < 0): xEncoder.write(b'Z')
    elif(final == 0): xEncoder.write(b'0')
    elif(final == 1): xEncoder.write(b'1')
    elif(final == 2): xEncoder.write(b'2')
    elif(final == 3): xEncoder.write(b'3')
    elif(final == 4): xEncoder.write(b'4')
    elif(final == 5): xEncoder.write(b'5')
    elif(final == 6): xEncoder.write(b'6')
    elif(final == 7): xEncoder.write(b'7')
    elif(final == 8): xEncoder.write(b'8')
    elif(final == 9): xEncoder.write(b'9')
    
def manageData(pData):
    global xStart
    pData = pData.split("#")
    if(xStart == False):
        xStart = True
        if(pData[0] == "xStart"):
            startViewer(int(pData[1]),int(pData[2]))
    if(pData[0] == "true"):
        setMemoryBlock(True,int(pData[1]),int(pData[2]))
def timer():
    global actualTIME
    initX1 = 13
    initX2 = 18
    LPos = [0,0]
    
    while True:
        actualTIME+=1
        time.sleep(1)
        if(actualTIME %10 == 0):
            blocksUsed = 0
            for i in range(0,len(MemoryBlockList)):
                if(MemoryBlockList[i][1] == True):
                    blocksUsed+=1
            ti = actualTIME //10
            porcentaje = (blocksUsed*100)/numMemoryBlocks #Porcentaje de Memoria
            PosY = 379-((porcentaje*350)/100)
            if(ti > 11):
                PosX = 5 + ((ti-1)*45)
                graphCanvas.create_text(PosX, 382, anchor=W, font="Arial",text=str(actualTIME))
                graphCanvas.create_oval(initX1, PosY,initX2, PosY+5, fill="blue")
                graphCanvas.create_line(LPos[0]+2,LPos[1]+2,initX1+2,PosY+2,fill="blue")
            else:
                if(actualTIME == 10):
                    graphCanvas.create_oval(initX1, PosY,initX2, PosY+5, fill="blue")
                else:
                    graphCanvas.create_oval(initX1, PosY,initX2, PosY+5, fill="blue")
                    graphCanvas.create_line(LPos[0]+2,LPos[1]+2,initX1+2,PosY+2,fill="blue")

                    
            LPos[0]=initX1
            LPos[1]=PosY
            initX1+=45
            initX2+=45
            
            
    porcentajeCompletado = (blocksUsed*100)/numMemoryBlocks #Porcentaje de Memoria
def createGUI(Size,MemDivision):
    x= Thread(target=createVisualMemory, args=(Size,MemDivision))
    x.daemon = True
    x.start()
def startTIMER():
    t= Thread(target=timer, args=())
    t.daemon = True
    t.start()
#############################################################################
########################### Socket Comm Setup ###############################
#############################################################################    
def retry_HOST():
    print("Retrying in...")
    for i in range(0,6):
        print(str(6-i))
        time.sleep(1)
    start_HOST()    
def start_HOST():
    global server
    HOST = ""
    PORT = vPORT
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        server.bind(("", PORT))
    except socket.error as msg:
        print ("Unable to connect. Adress already in use")
        retry_HOST()

    server.listen(10)
    print("Now Listening")
    
def listen():
    while True:
        conn, addr = server.accept()
        while True:
            data = conn.recv(4096)
            data = data.decode("utf-8")
            if(data != ""):
                #print(data)
                manageData(data)
            #time.sleep()
    server.close()


def start_loop():
    a= Thread(target=listen, args=())
    a.daemon = True
    a.start()


#############################################################################
####################### Graphical User Interface ############################
#############################################################################


######################## Loading Screen ##############################
def fillLoadingBars(ptr,numMemBlocks):
    #print("PORCENTAJE " + str(ptr))
    bloque = int(ptr*20/100)
    #print("Bloque: " + str(bloque))
    for i in range(0,bloque):
        loadCanvas.itemconfig(loadBar[i],fill="green")
        splashCanvas.itemconfig(txtPercentaje,text=str(int(ptr))+"%")
        if(ptr==100):
            window.deiconify()
def start_LoadBar():
    global loadScreen,splashCanvas
    loadScreen = Toplevel()
    loadScreen.title("Memory Monitor LDMM")
    loadScreen.geometry("500x200+450+250")
    loadScreen.resizable(width=FALSE, height=FALSE)

    splashCanvas = Canvas(loadScreen, width=500, height=200, bg="#FFFFFF")
    splashCanvas.place(x=0,y=0)

    global loadCanvas,loadBar,txtPercentaje

    splashCanvas.create_text(20, 70, anchor=W, font="Arial",text="Percentage:")
    txtPercentaje = splashCanvas.create_text(115, 70, anchor=W, font="Arial",text="0")
    
    loadBar=[]
    loadCanvas = Canvas(splashCanvas, width=400, height=50, bg="#000000")
    loadCanvas.place(x=50,y=90)
    c=[1,1,20,50] #Coordenas de Creacion de Barras de Carga
    for i in range(0,20):
        ob = loadCanvas.create_rectangle(c[0],c[1],c[2],c[3],width=0, fill="white")
        c[0]+=20
        c[2]+=20
        loadBar.append(ob)
    loadScreen.withdraw()
def startViewer(vHeapSize,MemDivision):
    if(vGUI):
        loadScreen.deiconify()
        createGUI(vHeapSize,MemDivision)
        window.withdraw()
    else:
        createGUI(vHeapSize,MemDivision)
        if(vDEBUG):
            print("Loading bar was not loaded. Check XML file")

#################################################################################
############################## Initial Setup ####################################
#################################################################################

loadXMLParameters()
global window,contenedor,xStart,xEncoder
if(vGUI):
    window = Tk()
    window.title("Memory Monitor LDMM")
    window.geometry("1200x600+100+80")
    window.resizable(width=TRUE, height=FALSE)
    xStart = False
    if(vHARDWARE):
        try:
            xEncoder = serial.Serial(vUSB, 9600)
        except:
            print("USB Monitor is not connected")
    contenedor = Canvas(window, width=1200, height=600, bg="#A8A79E")
    contenedor.place(x=0,y=0)
    start_LoadBar()
    start_HOST()
    start_loop()
    window.mainloop()
else:
    window = Tk()
    window.title("Memory Monitor LDMM")
    window.geometry("10x10+100+80")
    window.resizable(width=TRUE, height=FALSE)
    xStart = False
    if(vHARDWARE):
        try:
            xEncoder = serial.Serial(vUSB, 9600)
        except:
            print("USB Monitor is not connected")
    start_HOST()
    start_loop()
    if(vDEBUG):
        print("Graphical User Interface was not loaded. Check XML file")
    window.mainloop()
