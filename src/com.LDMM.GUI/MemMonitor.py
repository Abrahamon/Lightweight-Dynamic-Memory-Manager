import socket
from tkinter import *
from threading import Thread
import threading
import time

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
            data = data.split("#")
            print("READ: "+data[0]+" "+data[1]+" "+data[2])
            print(data[0] + " " + data[1] + " " + data[2])
            if(data[0] == "rectangle"):
                figura = contenedor.create_rectangle(1,1 ,50 ,50, width=0, fill="#FF0000")
                contenedor.move(figura,data[1],data[2])
            elif(data[0] == "circle"):
                figura = contenedor.create_oval(1, 1, 50,50, fill="blue")
                contenedor.move(figura,data[1],data[2])
            contenedor.update()
            #time.sleep()
    server.close()


def start_loop():
    a= Thread(target=listen, args=())
    a.daemon = True
    a.start()

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

    print("num " + str(numMemoryBlocks))
    print("chuck size " + str(MemoryChunckSize))
    
    memoryCanvas = Canvas(window, width=300, height=600,borderwidth=0,
                          highlightthickness=0,bg="#0155FF")

    memoryCanvas.config(scrollregion=scrRegion)
    memoryCanvas.pack(padx=1,pady=0)
    
    ls = [5,5,180,30,numMemoryBlocks]   #Lista con Valores de Coordenadas(Cambian en cada iteracion)
    MemoryBlockList=[]                  #Lista de Bloques de Memoria (objetos Canvas)
    
    while ls[4] != 0:                   #Mientras que la cantidad de bloque sea != 0
        block = memoryCanvas.create_rectangle(ls[0],ls[1],ls[2],ls[3],width=0, fill="white")
        MemoryBlockList.append(block)   #Añade el bloque creado a la lista
        ls[1] += 30                     #Aumenta las coordenadas en 30
        ls[3] += 30
        ls[4] -= 1                      #Reduce el numero de elementos crear
    
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
    
window = Tk()
window.title("Memory Monitor LDMM")
window.geometry("800x600+250+150")
window.resizable(width=FALSE, height=FALSE)


global contenedor
contenedor = Canvas(window, width=800, height=600, bg="#01FFFF")
contenedor.place(x=0,y=0)

botonA = Button(window,width=7,height=2,command=lambda: setMemoryBlock(True,10),text="Change",bg="#000000",fg="#FFFFFF")
botonA.place(x=335,y=350)
global entry
entry = Entry(window)
entry.place(x=335,y=200)


    
createVisualMemory(200,32)
#start_HOST()
#start_loop()
window.mainloop()
