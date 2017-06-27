'''
#sudo apt-get update
#sudo apt-get install python-pip python-dev ipython
#sudo apt-get install bluetooth libbluetooth-dev
#sudo pip install pybluez

NAO NOMEAR O ARQUIVO COMO BLUETOOTH.PY
'''
import bluetooth, subprocess, os, socket

## Script ##########################
def main():

    ##########  Variaveis

    port = 1         # RFCOMM port
    addr = ''
    passkey = "1234" # passkey of the device you want to connect

    sudoPassword = '131517'

    ###########

    # kill any "bluetooth-agent" process that is already running
    os.system('echo %s|sudo -S %s' % (sudoPassword, "kill -9 `pidof bluetooth-agent`"))

    # Start a new "bluetooth-agent" process where XXXX is the passkey
    # bluetooth-agent lida com pincode. Esse comando determina o pincode usado nas conexoes
    subprocess.call("bluetooth-agent " + passkey + " &",shell=True)
    subprocess.call("rfkill unblock bluetooth",shell=True)

    os.system('echo %s|sudo -S %s' % (sudoPassword, 'hciconfig hci0 up'))

    nearby_devices = bluetooth.discover_devices(lookup_names=True)
    print("found %d devices" % len(nearby_devices))

    #handleBluetooth(addr, port)
    for addr, name in nearby_devices:

        print("  %s - %s" % (addr, name))

        handleBluetooth(addr, port)

## Funcoes ##########################

def handleBluetooth(addr, port):
    # Now, connect in the same way as always with PyBlueZ
    sudoPassword = '131517'
    try:

        #s = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        #s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
        #print(s.connect((addr,port)))

        os.system('echo %s|sudo -S %s' % (sudoPassword, "sudo rfcomm connect hci0 " + addr))

        

        print("Conectado no bluetooth")

        #adicionar timer para sair do loop
        '''
        while True:
            data = s.recv(1024)
            if len(data) > 0:
                print("received [%s]" % data)
                flag = handleTCP(msg)

                if flag == 1:
                    s.send("ok");

                break
        '''

        s.close()
        msg = 'oiiii'
        flag = handleTCP(msg)



    except bluetooth.btcommon.BluetoothError as err:
        # Error handler
        print(err)
        print("\nErro de conexao com bluetooth")



def handleTCP(msg):
    IP = '127.0.0.1'
    PORTA = 5500

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (IP, PORTA)
    print('starting up on %s port %s' % server_address)


    try:
        sock.connect(server_address)
        # Send data
        print('sending "%s"' % msg)
        sock.send(bytes(msg, 'UTF-8'))

        #adicionar timer para sair do loop
        while True:

            data = sock.recv(1024)
            if len(data) > 0:
                print("received [%s]" % data)
                sock.close()
                break


    except:
        print("Erro de conexao com servidor tcp")

if __name__ == "__main__":
    main()
