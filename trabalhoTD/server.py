#libraries
import socket, json
import numpy as np
import subprocess, sys, shlex, os, shutil
import http, http.client, urllib.parse
import threading
from collections import namedtuple
from time import sleep
import time, math
import base64

# variavel global que associa o nome do cliente (login) com sua conexao (ip address, socket struct ...)
connectedClients = {0:0}

# Server Class
class server(object):

############################# Metodos que lidam com a conexao com o cliente  ################################

    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.s.bind((self.host, self.port))
        self.finalData = str("")

    def listen(self):
        self.s.listen(10) #10 clientes ao mesmo tempo
        while True:
            connection, client_address = self.s.accept()
            threading.Thread(target = self.handleClient,args = (connection,client_address)).start()

    def handleClient(self, connection, address): #thread alocada para cada cliente
        while True:
            try:
                data = connection.recv(2048)
                if data:
                    response = data.decode("utf-8")
                    print(response)
                    logResponse(response)
                    jsonMsg = json.loads(response)
                    sendAux = parseData(jsonMsg,connection) #interpreta msg vinda do cliente
                    send = bytes(sendAux,encoding='utf-8')
                    connection.sendall(send)

                else:
                    log = connectedClients[connection]+' se desconectou'
                    logResponse(log)
                    print(log)
                    del connectedClients[connection]
                    connection.close()
                    return False
            except:
                try:
                    del connectedClients[connection]
                    connection.close()
                    return False
                except:
                    return False

############################# Metodos que manipulam string que armazena arquivo muito grande  ################################

    def concatenateString(self, string):

        self.finalData = self.finalData + str(string)

    def determineString(self,string):
        self.finalData = str(string)

    def getString(self):
        return self.finalData


############################# Main + functions ################################

serverObject = server('0.0.0.0',5006) #porta de operacao do servidor

def main():
    serverObject.listen()

def logResponse(response):
    autent_file = open('log.txt','a')
    autent_file.write(response + '\n')
    autent_file.close()

# funcao que ja recebe msg em json para interpretá-la, assim como
# a instancia da conexao para possivel troca de msg com cliente
def parseData(jsonMsg, connection):

############################# operacao de autenticacao no servidor ################################

    if(jsonMsg["operation"] == "login"):
        autent_file = open('autenticacao.txt','r')
        for line in autent_file:
            line = line.strip()
            login, passwd = line.split(' ')
            if login == jsonMsg["params"][0]:
                if passwd == jsonMsg["params"][1]:
                    autent_file.close()
                    connectedClients.update({connection:jsonMsg["params"][0]})
                    return createJson(200,  "Bem vindo ao dropbox " + str(jsonMsg["params"][0])
                    + '\nDigite \'help\' para mais informacoes' ,"")
                else:
                    autent_file.close()
                    return createJson(404,  "Senha invalida","")
        autent_file.close()
        return createJson(404,  "Usuario invalido","")

############################# operacao de cadastro no servidor ################################

    elif(jsonMsg["operation"] == "cadastro"):
        autent_file = open('autenticacao.txt','r')
        for line in autent_file:
            line = line.strip()
            login, passwd = line.split(' ')
            if login == jsonMsg["params"][0]:
                autent_file.close()
                return createJson(404,  "Usuario ja existente. Nao foi possivel fazer o cadastro","")

        autent_file.close()
        autent_file = open('autenticacao.txt','a')
        autent_file.write(jsonMsg["params"][0] + ' ' + jsonMsg["params"][1] + '\n')
        autent_file.close()
        connectedClients.update({connection:jsonMsg["params"][0]})
        os.mkdir(jsonMsg["params"][0]) #cria pasta com nome do usuario
        return createJson(200, "Usuario cadastrado com sucesso. Bem vindo ao dropbox " + str(jsonMsg["params"][0])
        + '\nDigite \'help\' para mais informacoes' ,"")

############################# operacao de listagem ################################

    elif(jsonMsg["operation"] == "ls"):
        retval = os.getcwd()
        os.chdir(retval+ '/' +connectedClients[connection] + jsonMsg["name"][1])
        lista = os.listdir()
        os.chdir(retval)
        return createJson(200,  lista, "")

############################# operacao de mudar de diretorio ################################

    elif(jsonMsg["operation"] == "cd"):
        retval = os.getcwd()
        try:
            aux = retval + '/' +  connectedClients[connection] + jsonMsg["name"][1] + '/'
            aux += '' if jsonMsg["name"][0] == '..' else jsonMsg["name"][0]
            os.chdir(aux)
            if jsonMsg["name"][0] == '..':
                os.chdir("..")
            path = os.getcwd()
            index = path.find(connectedClients[connection])
            os.chdir(retval)
            return createJson(200,  "cd_ok", path[index+len(connectedClients[connection]):len(path)])
        except:
            os.chdir(retval)
            return createJson(200,  "Diretorio invalido","")

############################# operacao de mover/renomear pasta/arquivo ################################

    elif(jsonMsg["operation"] == "mv"):
        try:
            retval = os.getcwd()
            currentFilePath = retval + '/' +connectedClients[connection] + jsonMsg["data"]
            os.chdir(currentFilePath)
            destFilePath = retval + '/' +connectedClients[connection] + jsonMsg["name"][1]
            currentFilePath +=  '/' + jsonMsg["name"][0]
            shutil.move(currentFilePath,destFilePath)
            os.chdir(retval)
            return createJson(200,  "", "")
        except:
            os.chdir(retval)
            return createJson(200,  "Arquivo/diretorio invalido","")

############################# operacao de deletar diretorio/arquivo ################################

    elif(jsonMsg["operation"] == "rm"):
        try:
            retval = os.getcwd()
            os.chdir(retval + '/' +connectedClients[connection] + jsonMsg["name"][1])
            if os.path.isdir(jsonMsg["name"][0]):
                shutil.rmtree(jsonMsg["name"][0])
            else:
                os.remove(jsonMsg["name"][0])
            os.chdir(retval)
            return createJson(200,  "", "")
        except:
            os.chdir(retval)
            return createJson(200,  "Arquivo/diretorio invalido","")

############################# operacao de criar diretorio mkdir ################################

    elif(jsonMsg["operation"] == "mkdir"):
        retval = os.getcwd()
        os.chdir(retval+ '/' +connectedClients[connection] + jsonMsg["name"][1])
        try:
            os.mkdir(jsonMsg["name"][0])
        except:
            if os.path.isdir(jsonMsg["name"][0]):
                os.chdir(retval)
                return createJson(200,  "Pasta ja existente", "")
            else:
                os.chdir(retval)
                return createJson(200, "Nao foi possivel criar essa pasta","")
        os.chdir(retval)
        return createJson(200,  "", "")

############################# operacao de upload
# recebe arquivos de forma correta, mesmo que seja enviado em varios segmentos
# e cria diretorios/arquivos ################################

    elif(jsonMsg["operation"] == "upload"):
        if (jsonMsg["data"] == ""): #sinalizacao que terminou o upload
            return createJson(200,  "", "")

        #parse do upload!
        array = np.array(jsonMsg["data"]) #array = [sendMsg, name, isDir, actualDir,sendMsgSize, cont]
        serverObject.concatenateString(array[0])
        #print(array[4])
        if (int(array[4]) > 1023 and int(array[5]) != 0): #se for o ultimo pacote de dados do arquivo, nao entra aqui
            return "ok"

        retval = os.getcwd()
        os.chdir(retval+ '/' +connectedClients[connection] + jsonMsg["name"][1])

        if(array[2] == '0'):
            createFile(serverObject.getString(),array[1],array[3])
        else:
            createDir(array[1],array[3])

        serverObject.determineString("")
        os.chdir(retval)
        return "ok" #retorna 'ok' para o cliente enquanto nao terminar de receber todos arquivos/diretorios


############################# operacao de download
# verifica todos os arquivos e diretorios que devem ser enviados de forma recursiva ################################

    elif(jsonMsg["operation"] == "download"):
        retval = os.getcwd()
        newDir = retval+ '/' +connectedClients[connection] + jsonMsg["name"][1]
        os.chdir(newDir)
        FileFound = 0
        for file in os.listdir():
            if file == jsonMsg["name"][0]:
                FileFound = 1
                break
        if (FileFound):
            if os.path.isdir(jsonMsg["name"][0]): #é um Diretorio
                dirName = jsonMsg["name"][0]
                os.chdir(newDir + '/' + dirName)
                data = ["",dirName,1,dirName]
                data = getAllFiles(data, dirName,newDir + '/' + dirName)
                send2client(connection, data)
            else: #é um arquivo
                downloadFile = open(jsonMsg["name"][0],"rb")
                sendMsg = downloadFile.read()
                downloadFile.close()
                compressed_data = base64.encodestring(sendMsg).decode("utf-8")
                data = [compressed_data,jsonMsg["name"][0],'0','0']
                send2client(connection,data)

            os.chdir(retval)
            return createJson(200,  "", "")
        else:
            os.chdir(retval)
            return createJson(200,  "Arquivo/diretorio invalido", "")

############################# operacao de logout ################################
    else:
        return createJson(404, "Saindo do dropbox...","")

############################# pega todos arquivos e diretorios durante operacao de download ################################
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

############################# Manda todos os arquivos durante operacao de download
# Se o arquivo for maior que 1024 bytes, ele é segmentado e enviado em partes ################################
def send2client(connection, data):
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
                connection.sendall(bytes(createJson(200,"", dataAux),encoding='utf-8'))
            except:
                print('erro')
                raise
            cont+=1
            msg = connection.recv(2048)
            if (msg == b"ok"):
                continue
            else:
                print("erro no download para cliente")
                break
        i+=4;

############################# Cria arquivo durante operacao de upload no diretorio correto ################################
def createFile(msg,name,dirName):
    retval = os.getcwd()
    if (dirName != '0'):
        os.chdir(retval + '/' + dirName)
    downloadFile = open(name,"wb")
    uncompressed_data = base64.decodestring(bytes(msg,encoding='utf-8'))
    downloadFile.write(uncompressed_data)
    downloadFile.close()
    os.chdir(retval)

############################# Cria diretorio durante operacao de upload ################################
def createDir(name,dirName):
    retval = os.getcwd()
    if (dirName != name):
        os.chdir(retval+'/'+dirName)
    try:
        os.mkdir(name)
        os.chdir(retval)
    except:
        if os.path.isdir(name):
            pass
        else:
            raise
        os.chdir(retval)

############################# Cria msg em json contendo resposta para o cliente ################################
def createJson(state, message, data):

    msg = json.dumps({
        'state':state, #estado da conexao com o cliente
        'message':message, #mensagem que deve ser impressa para o usuario
        'data':data  #dado enviado durante operacao de download [sendMsg, name, isDir, actualDir, size, cont]
        })
    return msg

# declaracao da main
if __name__ == "__main__":
    main()
