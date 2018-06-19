#libraries
import socket, json
import subprocess, sys, shlex, os
import http, http.client, urllib.parse
import threading
import numpy as np
from collections import namedtuple
from time import sleep
import time, math
import base64

# Client Class
class client(object):

############################# Metodos que lidam com a conexao com o servidor  ################################

    def __init__(self, host, port,login, passwd):
        self.host = host
        self.port = port
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.path = ""
        self.finalData = str("")

        noUser = "noUser"
        if (login == "init"):
            return
        if (login == noUser):
            self.noUser = "noUser"
            self.login, self.passwd = createLogin()
        else:
            self.noUser = "User"
            self.login = login
            self.passwd = passwd


    def connect(self): #conecta no servidor e manda msg baseado na entrada de dados do usuario.
                       #alem disso, depois de enviar msg, fica esperando por resposta
        try:
            self.s.connect((self.host, self.port))
            connectionIsOk = 0
        except:
            print("Servidor desligado. Tente novamente")
            return False
        while True:
            if (connectionIsOk == 1):
                userInput = self.getUserCommand()
                if (userInput == 'help'):
                    helpMessage()
                    continue
                else:
                    # interpreta a operacao que o usuario inseriu (mkdir, cd, ls ...) e cria msg em json
                    jsonAux = getOperation(userInput,self.path,self.login,self.s)
                    if jsonAux != "":
                        self.s.sendall(bytes(jsonAux,encoding='utf-8'))
                    else:
                        continue

            else: #operacao de cadastro/login
                if self.noUser == "noUser":
                    self.s.sendall(bytes(autentMessage(self.login, self.passwd, "cadastro"),encoding='utf-8'))
                else:
                    self.s.sendall(bytes(autentMessage(self.login, self.passwd, "login"),encoding='utf-8'))

            data = self.s.recv(2048)
            if data:
                # interpreta msg que o servidor respondeu
                connectionIsOk, auxPath = parseData(json.loads(data.decode("utf-8")),self.s)
                if auxPath != "-1":
                    self.path = auxPath
                if connectionIsOk == -1:
                    self.s.close()
                    return False
            else:
                print("Conexao perdida com servidor")
                self.s.close()
                return False

############################# Pega o input do usuario  ################################

    def getUserCommand(self):
        return input('/'+ self.login + self.path+' >>> ')

############################# Metodos que manipulam string que armazena arquivo muito grande  ################################

    def concatenateString(self, string):

        self.finalData = self.finalData + str(string)

    def determineString(self,string):
        self.finalData = str(string)

    def getString(self):
        return self.finalData


############################# Main + functions ################################

# objeto da classe declarado de forma global
clienteObject = client(0,0,"init","init")

def main():
    if (len(sys.argv) == 5): #autenticacao deve ser feita
        clienteObject = client(sys.argv[1],int(sys.argv[2]),sys.argv[3],sys.argv[4])
        clienteObject.connect()

    elif(len(sys.argv) == 3): #cadastro deve ser feito
        clienteObject = client(sys.argv[1],int(sys.argv[2]),"noUser","noUser")
        clienteObject.connect()

    else:
        print("Execucao invalida. Faça conforme uma das opcoes abaixo\n \
        1) python client.py host 5005 login password\n \
        2) python client.py host 5005")

def autentMessage(login, passwd, operation): # criacao da mensagem de autenticacao serve tanto para login quanto para logout
    msg = json.dumps({
        'operation':operation,
        'params':[login,passwd]
        })
    return msg

def serviceMessage(operation, name1, name2, data): #criacao mensagem json para realizar alguma operacao
    msg = json.dumps({
        'operation': operation,
        'name': [name1, name2], #alguns parametros que devem ser enviados para realizacao correta das operacoes
        'data' : data #dado que contem os arquivos enviados durante operacao de upload
        })
    return msg

def createLogin():
    login = input("Necessário criar login e senha para acessar o servidor\nLogin: ")
    senha = input("Senha: ")
    return login, senha

def helpMessage():
    print("Lista de comandos:\n\
    1) ls: verifica arquivos e pastas do diretorio atual\n\
    2) cd path: muda para o diretorio \'path\'\n\
    3) mv path_file dest_dir: move o arquivo ou diretorio em \'path_file\' para  o diretorio \'dest_dir\' \n\
    4) rm file: remove arquivo ou diretorio de nome \'file'\ \n\
    5) mkdir dir_name: cria um diretorio com nome \'dir_name\'\n\
    6) upload path_file: faz o upload de um arquivo ou diretorio com nome \'path_file\' \n\
    7) download file: faz o download de um arquivo ou diretorio com nome \'file\' \n\
    8) exit: sair do dropbox\n")

############################# Interpreta operacao que o usuario escolheu,
# define parametros que devem ser enviados ao servidor e cria msg em json ################################

def getOperation(userInput,path,login,connection):

    ############################# logout ################################
    if(userInput == "exit"):
        return autentMessage("", "","logout")

    ############################# ls ################################
    elif(userInput == "ls"):
        return serviceMessage(userInput,"",path,"")

    ############################# cd ################################
    stringVec = userInput.split(' ')
    if (stringVec[0] == "cd"):
        if (len(stringVec) == 2):
            if (stringVec[1] == '..' and path == ""):
                print("Operacao invalida")
                return ""
            else:
                return serviceMessage(stringVec[0], stringVec[1], path, "")
        else:
            print("Numero de argumentos invalidos. Execute '\help'\ para mais informacoes")
            return ""
    ############################# mv ################################
    elif (stringVec[0] == "mv"):
        if (len(stringVec) == 3):
            index = stringVec[2].find(login)
            if (index != -1):
                if (stringVec[2][0] != '/'):
                    print("Insira uma '/' antes da sua pasta raiz: /usuario/pasta/pasta")
                    return ""
                stringAux = stringVec[2][index+len(login):len(stringVec[2])]
                stringVec[2] = stringAux
            else:
                stringVec[2] = path + '/' + stringVec[2]
            return serviceMessage(stringVec[0], stringVec[1], stringVec[2], path)
        else:
            print("Numero de argumentos invalidos. Execute '\help'\ para mais informacoes")
            return ""

    ############################# rm ################################
    elif (stringVec[0] == "rm"):
        if (len(stringVec) == 2):
            return serviceMessage(stringVec[0], stringVec[1], path, "")
        else:
            print("Numero de argumentos invalidos. Execute '\help'\ para mais informacoes")
            return ""
    ############################# mkdir ################################
    elif (stringVec[0] == "mkdir"):
        if (len(stringVec) == 2):
            return serviceMessage(stringVec[0], stringVec[1], path, "")
        else:
            print("Numero de argumentos invalidos. Execute '\help'\ para mais informacoes")
            return ""

    ############################# upload de arquivos/pastas ################################
    elif (stringVec[0] == "upload"): #precisa mandar nome do arquivo para o servidor mais o arquivo!
        if (len(stringVec) == 2):
            sendAllFiles(stringVec[1],path,connection) #manda todos arquivos/pastas para o servidor
            return serviceMessage(stringVec[0],stringVec[1],path,"") #ultima msg enviada indicando que terminou o upload
        else:
            print("Numero de argumentos invalidos. Execute '\help'\ para mais informacoes")
            return ""

    ############################# download de arquivos/pastas ################################
    elif (stringVec[0] == "download"): #precisa mandar apenas o nome do arquivo para o servidor!
        if (len(stringVec) == 2):
            return serviceMessage(stringVec[0], stringVec[1], path, "")
        else:
            print("Numero de argumentos invalidos. Execute '\help'\ para mais informacoes")
            return ""

    ############################# comandos invalidos ################################
    else:
        print("Comando invalido. Execute '\help'\ para mais informacoes")
        return ""

############################# Interpreta resposta do servidor ################################
def parseData(jsonMsg,socket):
    if jsonMsg["message"] == "cd_ok":
        return 1, jsonMsg["data"] #mudar variavel path devido a operacao de 'cd', nao imprimindo nada ao usuario!
    else:
        print(jsonMsg["message"]) #imprime msg que o servidor enviou ao usuario

    if(jsonMsg["state"] == 200):  #200 significa que a conexao com servidor deve continuar
        jsonMsgAux = jsonMsg
        flag = 0
        while True:
            #print(jsonMsgAux)
            if(jsonMsgAux["data"] == ""): #caso nao haja nenhuma mensagem em data, sai do loop
                break #entra aqui em todos as operacoes que nao seja download

            #parse do download!
            array = np.array(jsonMsgAux["data"]) #array = [sendMsg, name, isDir, actualDir, sendMsgSize, cont]
            clienteObject.concatenateString(array[0])
            if (int(array[4]) <= 1023 and int(array[5]) == 0): #se for o ultimo pacote de dados do arquivo, entra aqui
                if(array[2] == '0'):
                    createFile(clienteObject.getString(),array[1],array[3])
                else:
                    createDir(array[1],array[3])
                clienteObject.determineString("")

            socket.sendall(b"ok")
            data = socket.recv(2048)
            jsonMsgAux = json.loads(data.decode("utf-8"))

        return 1,"-1"

    elif(jsonMsg["state"] == 404):  #404 significa que é necessario fechar conexao com servidor
        return -1,"-1"

############################# Manda arquivos e pastas para o servidor de forma recursiva ################################

def sendAllFiles(name, path,connection):
    index = name.rfind('/')
    finalName = ""
    retval = os.getcwd()
    newDir = retval

    if (index != -1): #name representa um caminho para o arquivo/diretorio
        finalName = name[index+1:len(name)]
        newDir = name[0:index]
        try:
            os.chdir(newDir)
        except:
            print("Caminho para arquivo/diretorio invalido. Necessario especificar todo o caminho! Lembre-se tambem de inserir uma '/' antes da sua pasta raiz: /home/bruno/Documentos")
    else: #name representa já o nome do arquivo/diretorio
        finalName = name

    FileFound = 0
    for file in os.listdir():
        if file == finalName:
            FileFound = 1
            break
    if (FileFound):
        if os.path.isdir(finalName): #é um Diretorio
            dirName = finalName
            os.chdir(newDir + '/' + dirName)
            data = ["",dirName,1,dirName]
            data = getAllFiles(data, dirName,newDir + '/' + dirName)
            send2client(connection, data, path)

        else: #é um arquivo
            uploadFile = open(finalName,"rb")
            sendMsg = uploadFile.read()
            uploadFile.close()
            compressed_data = base64.encodestring(sendMsg).decode("utf-8")
            data = [compressed_data,finalName,'0','0']
            send2client(connection,data,path)
    else:
        print("Arquivo/diretorio nao existe")

    os.chdir(retval)

############################# pega todos arquivos e diretorios durante operacao de upload ################################
def getAllFiles(data, dirName, actualDir):

    ls = os.listdir()

    #primeiro add todo os arquivos do diretorio
    for file in ls:
        if os.path.isdir(file) == 0:
            downloadFile = open(file,"rb")
            sendMsg = downloadFile.read()
            downloadFile.close()
            compressed_data = base64.encodestring(sendMsg).decode("utf-8")
            data = np.append(data,[compressed_data,file,0,dirName])

    #depois add todos os diretorios de forma recursiva
    for file in ls:
        if os.path.isdir(file) == 1:
            data = np.append(data,["",file,1,dirName])
            os.chdir(actualDir + '/' + file)
            data = getAllFiles(data,dirName + '/'+ file,actualDir + '/' + file)
            os.chdir(actualDir)

    return data

############################# Manda todos os arquivos durante operacao de upload
# Se o arquivo for maior que 1024 bytes, ele é segmentado e enviado em partes ################################
def send2client(connection, data,path):
    i=0
    while i < len(data):
        cont = 0
        sendMsg = ""
        initIdenx = 0
        if (data[i] == ""):  #caso seja a transferencia de um diretorio, esse campo é vazio
            iterations = 1
        else:
            iterations = math.ceil(len(data[i])/1024) #divisao da msg de 1024 em 1024 bytes
        while (cont < iterations):
            if (cont == iterations - 1):
                sendMsg = data[i][initIdenx:len(data[i])]
            else:
                sendMsg = data[i][initIdenx:initIdenx+1024]
                initIdenx += 1024

            dataAux = [sendMsg,data[i+1],data[i+2],data[i+3],len(sendMsg),iterations-cont-1]
            try:
                connection.sendall(bytes(serviceMessage("upload","",path,dataAux),encoding='utf-8'))
            except:
                print('erro')
                raise
            cont+=1
            msg = connection.recv(2048)
            if (msg == b"ok"):
                continue
            else:
                print("erro no upload para servidor")
                break
        i+=4;

############################# Cria arquivo durante operacao de download no diretorio correto ################################

def createFile(msg,name,dirName):
    retval = os.getcwd()
    if (dirName != '0'):
        os.chdir(retval + '/' + dirName)

    downloadFile = open(name,"wb")
    uncompressed_data = base64.decodestring(bytes(msg,encoding='utf-8'))
    downloadFile.write(uncompressed_data)
    downloadFile.close()
    os.chdir(retval)

############################# Cria diretorio durante operacao de download ################################

def createDir(name,dirName):
    retval = os.getcwd()
    if (dirName != name):
        os.chdir(retval+'/'+dirName)
    try:
        os.mkdir(name)
        os.chdir(retval)
    except:  # Python >2.5
        if os.path.isdir(name):
            pass
        else:
            raise
        os.chdir(retval)

# declaracao da main
if __name__ == "__main__":
    main()
