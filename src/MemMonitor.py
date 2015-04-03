
##### Bibliotecas Utilizadas #####
##################################
import socket
from tkinter import *
from threading import Thread
import threading
import time
import serial
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

    print("NUMERO DE BLOQUE DE MEMORIA " + str(numMemoryBlocks))
    print("TAMAÑO DEL CANVAS DE MEMORIA " + str(MemoryChunckSize))
    
    memoryCanvas = Canvas(window, width=300, height=600,borderwidth=0,
                          highlightthickness=0,bg="#06072B")

    memoryCanvas.config(scrollregion=scrRegion)
    memoryCanvas.pack(padx=1,pady=0)
    
    coordsInfo = [5,5,180,30,numMemoryBlocks]   #Lista con Valores de Coordenadas(Cambian en cada iteracion)
    MemoryBlockList = []                        #Lista de Bloques de Memoria (objetos Canvas)


    ##### Ciclo Dibujo de Bloques de Memoria ###################################################
    ############################################################################################
    iterator = 1;
    while coordsInfo[4] != 0:                   #Mientras que la cantidad de bloque sea != 0

        #Crea el bloque en las coordenadas correspondientes
        blockGUI = memoryCanvas.create_rectangle(coordsInfo[0],
                                              coordsInfo[1],
                                              coordsInfo[2],
                                              coordsInfo[3],width=0, fill="white")
        block = [blockGUI,False]
        MemoryBlockList.append(block)   #Añade el bloque creado a la lista
        coordsInfo[1] += 30             #Aumenta las coordenadas en 30
        coordsInfo[3] += 30
        coordsInfo[4] -= 1              #Reduce el numero de elementos crear
        
        porcentajeCompletado = (iterator*100)/numMemoryBlocks
        fillLoadingBars(porcentajeCompletado,MemDivision)
        iterator+=1
    
    ############################################################################################
    ################################# UI Elements ##############################################
    ############################################################################################
    memoryCanvas.place(x=15,y=3)            #Coloca el canvas en posicion correcta
    hbar=Scrollbar(window,orient=VERTICAL)  #Crea el scrollbar para el canvas
    hbar.pack(side=LEFT,fill=Y)             #Coloca el scrollbar a la izquierda
    hbar.config(command=memoryCanvas.yview) #Añade el canvas al scrollbar
    memoryCanvas.config(yscrollcommand=hbar.set)#Añade el scrollbar al canvas
    loadScreen.destroy()                    #Destruye la ventana de carga

    global entry,TotalBar
    contenedor.create_text(505, 40, anchor=W, font="Arial",text="Memory Usage")
    contenedor2 = Canvas(window,width=250, height=400, bg="#06072B")
    contenedor2.place(x=500,y=50)
    
    TotalBar = Canvas(window,width=240, height=390, bg="#FFFFFF")
    TotalBar.place(x=505,y=55)

    for i in range(0,11):
        TotalBar.create_text(5, 370-(i*35), anchor=W, font="Arial",text=str(i*10)+"%")

    botonA = Button(window,width=7,height=2,command=debugSetMemoryBlock,text="Change",bg="#000000",fg="#FFFFFF")
    botonA.place(x=335,y=550)

    entry = Entry(window)
    entry.place(x=420,y=560)
    ############################################################################################
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
    if(pUsageFlag == True):
        for i in range(pStart,pEnd):
            memoryCanvas.itemconfig(MemoryBlockList[i][0],fill="red")
            MemoryBlockList[i][1] = True
    else:
        for i in range(pStart,pEnd):
            memoryCanvas.itemconfig(MemoryBlockList[i][0],fill="white")
            MemoryBlockList[i][1] = False

    porcentajeCompletado = setMemoryGraphicBar()
    setArduinoGraphicBar(porcentajeCompletado)

def debugSetMemoryBlock():
    global MemoryBlockList,memoryCanvas,entry
    data = entry.get()
    data= data.split("#")
    pStart = int(data[1])
    pEnd = int(data[2])
    
    if(data[0] == "True"):
        for i in range(pStart,pEnd):
            memoryCanvas.itemconfig(MemoryBlockList[i][0],fill="red")
            MemoryBlockList[i][1] = True
    else:
        for i in range(pStart,pEnd):
            memoryCanvas.itemconfig(MemoryBlockList[i][0],fill="white")
            MemoryBlockList[i][1] = False
    entry.delete(0, 'end')

    porcentajeCompletado = setMemoryGraphicBar()
    setArduinoGraphicBar(porcentajeCompletado)

 
def setMemoryGraphicBar():
    
    global MemoryBlockList,numMemoryBlocks,TotalBar
    blocksUsed = 0
    for i in range(0,len(MemoryBlockList)):
        if(MemoryBlockList[i][1] == True):
            blocksUsed+=1
            
    porcentajeCompletado = (blocksUsed*100)/numMemoryBlocks #Porcentaje de Memoria
    #print("Porcentaje: " + str(porcentajeCompletado))

    Pos = 370-((porcentajeCompletado*350)/100) #Posicion de la Barra De Memoria
    TotalBar.delete("Bar")
    TotalBar.create_rectangle(75,380,150,Pos,width=0, fill="green",tags="Bar")
    return porcentajeCompletado

def setArduinoGraphicBar(porcentaje):
    redondeo = int(round(porcentaje,-1)//10)
    final = (redondeo)-1
    print("Arduino " + str(redondeo))
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
    
def createGUI(Size,MemDivision):
    x= Thread(target=createVisualMemory, args=(Size,MemDivision))
    x.daemon = True
    x.start()
    
def manageData(pData):
    global xStart
    pData = pData.split("#")
    if(xStart == False):
        xStart = True
        if(pData[0] == "xStart"):
            startViewer(int(pData[1]),int(pData[2]))
    if(pData[0] == "true"):
        setMemoryBlock(True,int(pData[1]),int(pData[2]))
    
#############################################################################
########################### Socket Comm Setup ###############################
#############################################################################    
def retry_HOST():
    print("Retrying in...")
    for i in range(0,6):
        print(str(6-i))
    start_HOST()    
def start_HOST():
    global server
    HOST = ""
    PORT = 7070
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
    loadScreen.deiconify()
    createGUI(vHeapSize,MemDivision)
    window.withdraw()

#################################################################################
############################## Initial Setup ####################################
#################################################################################

global window,contenedor,xStart,xEncoder
window = Tk()
window.title("Memory Monitor LDMM")
window.geometry("800x600+250+100")
window.resizable(width=TRUE, height=FALSE)

xStart = False
#xEncoder = serial.Serial('/dev/ttyACM1', 9600)
xmlDoc = minidom.parse("config.xml")

contenedor = Canvas(window, width=800, height=600, bg="#A8A79E")
contenedor.place(x=0,y=0)

start_LoadBar()
start_HOST()
start_loop()
window.mainloop()
