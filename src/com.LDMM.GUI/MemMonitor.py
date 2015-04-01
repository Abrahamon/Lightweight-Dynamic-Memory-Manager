import socket
from tkinter import *
from threading import Thread
import threading
import time
import json


def createVisualMemory(Size,MemDivision):
    global MemoryBlockList,memoryCanvas
    
    def getMemBlocks(Size,MemDivision):
        result=Size/MemDivision
        if(isinstance(result,int)):
            return int(result)
        else:
            return int(result)+1


    numMemoryBlocks = getMemBlocks(Size,MemDivision) #Cantidad Total de Bloques
    MemoryChunckSize = (numMemoryBlocks*30)  #Cantidad Total de Pixeles para todos los bloques
    HalfMemoryChunckSize = MemoryChunckSize/2#Mita de la Cantidad total de Pixeles
    scrRegion=(0,0,400,MemoryChunckSize+(MemoryChunckSize*.005))#Region de Scroll
                                                                #Total de Pixeles + un 0.005

    print("NUMERO DE BLOQUE DE MEMORIA " + str(numMemoryBlocks))
    print("TAMAÑO DEL CANVAS DE MEMORIA " + str(MemoryChunckSize))
    
    memoryCanvas = Canvas(window, width=300, height=600,borderwidth=0,
                          highlightthickness=0,bg="#0155FF")

    memoryCanvas.config(scrollregion=scrRegion)
    memoryCanvas.pack(padx=1,pady=0)
    
    ls = [5,5,180,30,numMemoryBlocks]   #Lista con Valores de Coordenadas(Cambian en cada iteracion)
    MemoryBlockList=[]                  #Lista de Bloques de Memoria (objetos Canvas)

    i = 1;
    while ls[4] != 0:                   #Mientras que la cantidad de bloque sea != 0
        
        block = memoryCanvas.create_rectangle(ls[0],ls[1],ls[2],ls[3],width=0, fill="white")
        MemoryBlockList.append(block)   #Añade el bloque creado a la lista
        ls[1] += 30                     #Aumenta las coordenadas en 30
        ls[3] += 30
        ls[4] -= 1                      #Reduce el numero de elementos crear
        
        porcentajeCompletado = (i*100)/numMemoryBlocks
        fillLoadingBars(porcentajeCompletado,MemDivision)
        i+=1
    #memoryCanvas.itemconfig(MemoryBlockList[24],fill="blue")
    memoryCanvas.place(x=15,y=3)
    hbar=Scrollbar(window,orient=VERTICAL)
    hbar.pack(side=LEFT,fill=Y)
    hbar.config(command=memoryCanvas.yview)
    memoryCanvas.config(yscrollcommand=hbar.set)

def setMemoryBlock(pUsageFlag,MemoryPosition):
    global MemoryBlockList,memoryCanvas,entry
    MemoryPosition=int(entry.get())
    if(pUsageFlag == True):
        memoryCanvas.itemconfig(MemoryBlockList[MemoryPosition],fill="red")
    else:
        memoryCanvas.itemconfig(MemoryBlockList[MemoryPosition],fill="white")

def createGUI(Size,MemDivision):
    x= Thread(target=createVisualMemory, args=(Size,MemDivision))
    x.daemon = True
    x.start()

def start_HOST():
    global server
    HOST = ""
    PORT = 7070
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        server.bind(("", PORT))
    except socket.error as msg:
        print (('Failed to create socket. Error code: ' + str(msg[0]) +
                 ' , Error message : ' + msg[1]))

    server.listen(10)
    print("Now Listening")
    
def listen():
    while True:
        conn, addr = server.accept()
        while True:
            data = conn.recv(4096)
            #data = data.split("#")
            data = data.decode("utf-8")
            if(data != ""):
                #print(data)
                if(data == "xStart"):
                    go()
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
def go():
    loadScreen.deiconify()
    window.withdraw()
    createGUI(100000,32)
global window
window = Tk()
window.title("Memory Monitor LDMM")
window.geometry("800x600+250+100")
window.resizable(width=FALSE, height=FALSE)


global contenedor
contenedor = Canvas(window, width=800, height=600, bg="#01FFFF")
contenedor.place(x=0,y=0)

botonA = Button(window,width=7,height=2,command=lambda: setMemoryBlock(True,10),text="Change",bg="#000000",fg="#FFFFFF")
botonA.place(x=335,y=350)

global entry
entry = Entry(window)
entry.place(x=335,y=200)



start_LoadBar()
start_HOST()
start_loop()
window.mainloop()
