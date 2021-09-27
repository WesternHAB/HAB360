# Max serial size should actually be 268?

#-----------------------------------------------------------------------------------------------------------\
#                                                    Imports                                                |
#-----------------------------------------------------------------------------------------------------------/


import socket
import tkinter as tk
import _thread
import time
import queue
import serial
#import winsound

from Commands import *


#-----------------------------------------------------------------------------------------------------------\
#                                                   Variables                                               |
#-----------------------------------------------------------------------------------------------------------/


request_queue = queue.Queue()
result_queue = queue.Queue()


#-----------------------------------------------------------------------------------------------------------\
#                                                   Variables                                               |
#-----------------------------------------------------------------------------------------------------------/


# Queues
request_queue = queue.Queue()
result_queue = queue.Queue()

# Fonts
headerFont = 'Calibri 18 bold'
labelFont = 'Calibri 8'
sectionFont = 'Calibri 14 bold'

# Backgrounds
sectionBg = '#cccccc'
disabledBg = '#f2f2f2'
fieldBg = 'white'
invalidFieldBg = 'orange'

# Mode option menu
OPTIONS = ["Normal", "Repeater"]
optionVar = None


#--------------------------------------------------------------------------\
#								  	 Setup					   		 	   |
#--------------------------------------------------------------------------/


print('Windows: COM#')
print('Linux: /dev/ttyUSB#')
#port = input("Enter COM port:")
port = 'COM7'
baud = 115200 # We can't go any higher without synchronous UART. But we need to connect a clock line which I can't to my laptop.

# Open the serial port
ser = serial.Serial(port, baud, timeout=15)
if ser.isOpen():
	print(ser.name + ' is open...')
	ser.reset_input_buffer()
	ser.reset_output_buffer()

packetBytes = b''
packetLength = 0


#-----------------------------------------------------------------------------------------------------------\
#                                              GUI thread functions                                         |
#-----------------------------------------------------------------------------------------------------------/


def submit_to_tkinter(callable, *args, **kwargs):
    request_queue.put((callable, args, kwargs))
    return result_queue.get()

t = None
def threadmain():
    global t
    global optionVar

    def timertick():
        try:
            callable, args, kwargs = request_queue.get_nowait()
        except queue.Empty:
            pass
        else:
            print("something in queue")
            retval = callable(*args, **kwargs)
            result_queue.put(retval)

        t.after(700, timertick)

    t = tk.Tk()
    t.configure(width=1420, height=800)
    t.title("L-COM communication module")
    try:
        t.iconbitmap('icon.ico')
    except Exception as e:
        logging.error(traceback.format_exc())
		
	
	#-----------------------------------------------------------------------------------------------------------------------------------------\
	# Telemetry and info frame----------------------------------------------------------------------------------------------------------------|
    # Create the frame
    TI_frame = tk.Frame(highlightbackground="black", highlightthickness=1, bg=sectionBg)
    TI_frame.place(relx=0.01, rely=0.01, relwidth=0.98, relheight=0.30)

    # Text label
    TI_headerLabel = tk.Label(TI_frame, text="Telemetry data", font=headerFont, bg=sectionBg)
    TI_headerLabel.place(relx=0.01, rely=0.01)

	
	# General telemetry frame--------------------------------------------------
    TI_general_frame = tk.Frame(TI_frame, highlightbackground="black", highlightthickness=1)
    TI_general_frame.place(relx=0.01, rely=0.17, relwidth=0.2, relheight=0.75)
	
	# Text label
    TI_general_headerLabel = tk.Label(TI_general_frame, text="General", font=sectionFont)
    TI_general_headerLabel.place(relx=0.08, rely=0.01)
    
    # Uptime label and textbox
    uptimeLabel = tk.Label(TI_general_frame, text="Uptime (s)", font=labelFont)
    uptimeLabel.place(relx=0.05, rely=0.15)	
    uptimeBox = tk.Label(TI_general_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='uptimeBox')
    uptimeBox.place(relx=0.05, rely=0.25)
	
    # LoRa set label and textbox
    lsetLabel = tk.Label(TI_general_frame, text="LoRa parameters set", font=labelFont)
    lsetLabel.place(relx=0.05, rely=0.40)	
    lsetBox = tk.Label(TI_general_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='lsetBox')
    lsetBox.place(relx=0.05, rely=0.50)
    #t.children["lsetBox"].configure(text=("Not set"))
	# Set Bg red
	
	# TOA label and textbox
    TOALabel = tk.Label(TI_general_frame, text="TOA (s)", font=labelFont)
    TOALabel.place(relx=0.05, rely=0.65)	
    toaBox = tk.Label(TI_general_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='toaBox')
    toaBox.place(relx=0.05, rely=0.75)
    #t.children["lsetBox"].configure(text=("Not set"))
	# Set Bg red
	
	# UNIX time label and textbox
    utimeLabel = tk.Label(TI_general_frame, text="UNIX time (s)", font=labelFont)
    utimeLabel.place(relx=0.53, rely=0.15)	
    utimeBox = tk.Label(TI_general_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='utimeBox')
    utimeBox.place(relx=0.53, rely=0.25)
	#t.children["usetBox"].configure(text=("Not set"))
	# Set Bg red
	
	# UNIX set label and textbox
    usetLabel = tk.Label(TI_general_frame, text="UNIX time set", font=labelFont)
    usetLabel.place(relx=0.53, rely=0.40)	
    usetBox = tk.Label(TI_general_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='usetBox')
    usetBox.place(relx=0.53, rely=0.50)
	#t.children["usetBox"].configure(text=("Not set"))
	# Set Bg red
	
	# Temperature label and textbox
    temperatureLabel = tk.Label(TI_general_frame, text="Temperature (°C)", font=labelFont)
    temperatureLabel.place(relx=0.53, rely=0.65)	
    temperatureBox = tk.Label(TI_general_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='temperatureBox')
    temperatureBox.place(relx=0.53, rely=0.75)

	
	# LoRa frame---------------------------------------------------------------
    TI_LoRa_frame = tk.Frame(TI_frame, highlightbackground="black", highlightthickness=1)
    TI_LoRa_frame.place(relx=0.22, rely=0.17, relwidth=0.77, relheight=0.35)
	
	# Text label
    TI_LoRa_headerLabel = tk.Label(TI_LoRa_frame, text="LoRa", font=sectionFont)
    TI_LoRa_headerLabel.place(relx=0.01, rely=0.01)
    
    # Frequency label and textbox
    frLabel = tk.Label(TI_LoRa_frame, text="Frequency (MHz)", font=labelFont)
    frLabel.place(relx=0.01, rely=0.30)	
    frBox = tk.Label(TI_LoRa_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='frBox')
    frBox.place(relx=0.01, rely=0.50)
	
	# Bandwidth label and textbox
    bwLabel = tk.Label(TI_LoRa_frame, text="Bandwidth (kbps?)", font=labelFont)
    bwLabel.place(relx=0.13, rely=0.30)	
    bwBox = tk.Label(TI_LoRa_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='bwBox')
    bwBox.place(relx=0.13, rely=0.50)
	
	# Spreading factor label and textbox
    sfLabel = tk.Label(TI_LoRa_frame, text="Spreading factor", font=labelFont)
    sfLabel.place(relx=0.25, rely=0.30)	
    sfBox = tk.Label(TI_LoRa_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='sfBox')
    sfBox.place(relx=0.25, rely=0.50)
	
	# Coding rate label and textbox
    crLabel = tk.Label(TI_LoRa_frame, text="Coding rate", font=labelFont)
    crLabel.place(relx=0.37, rely=0.30)	
    crBox = tk.Label(TI_LoRa_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='crBox')
    crBox.place(relx=0.37, rely=0.50)
	
	# Sync word label and textbox
    swLabel = tk.Label(TI_LoRa_frame, text="Sync word", font=labelFont)
    swLabel.place(relx=0.49, rely=0.30)	
    swBox = tk.Label(TI_LoRa_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='swBox')
    swBox.place(relx=0.49, rely=0.50)
	
	# Power label and textbox
    pwrLabel = tk.Label(TI_LoRa_frame, text="Transmit power (dBm)", font=labelFont)
    pwrLabel.place(relx=0.61, rely=0.30)	
    pwrBox = tk.Label(TI_LoRa_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='pwrBox')
    pwrBox.place(relx=0.61, rely=0.50)
	
	# Preamble length label and textbox
    plLabel = tk.Label(TI_LoRa_frame, text="Preamble length", font=labelFont)
    plLabel.place(relx=0.73, rely=0.30)	
    plBox = tk.Label(TI_LoRa_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='plBox')
    plBox.place(relx=0.73, rely=0.50)
	
	# Current limit label and textbox
    clLabel = tk.Label(TI_LoRa_frame, text="Current limit", font=labelFont)
    clLabel.place(relx=0.85, rely=0.30)	
    clBox = tk.Label(TI_LoRa_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='clBox')
    clBox.place(relx=0.85, rely=0.50)
	
	
	# Mode frame---------------------------------------------------------------
    TI_mode_frame = tk.Frame(TI_frame, highlightbackground="black", highlightthickness=1)
    TI_mode_frame.place(relx=0.22, rely=0.57, relwidth=0.77, relheight=0.35)
	
	# Text label
    TI_mode_headerLabel = tk.Label(TI_mode_frame, text="Mode", font=sectionFont)
    TI_mode_headerLabel.place(relx=0.01, rely=0.01)
    
    # Mode label and textbox
    modeLabel = tk.Label(TI_mode_frame, text="Mode", font=labelFont)
    modeLabel.place(relx=0.01, rely=0.30)	
    modeBox = tk.Label(TI_mode_frame, height=1, width=15, bg=disabledBg, borderwidth=2, relief="groove", name='modeBox')
    modeBox.place(relx=0.01, rely=0.50)
	
	# Message label and textbox
    messageLabel = tk.Label(TI_mode_frame, text="Message", font=labelFont)
    messageLabel.place(relx=0.15, rely=0.30)	
    messageBox = tk.Label(TI_mode_frame, height=1, width=122, bg=disabledBg, borderwidth=2, relief="groove", name='messageBox')
    messageBox.place(relx=0.15, rely=0.50)
	

	#-----------------------------------------------------------------------------------------------------------------------------------------\
	# Commands frame--------------------------------------------------------------------------------------------------------------------------|
    # Create the frame
    CMD_frame = tk.Frame(highlightbackground="black", highlightthickness=1, bg=sectionBg)
    #CMD_frame.place(relx=0.01, rely=0.31, relwidth=0.98, relheight=0.30)
    CMD_frame.place(relx=0.01, rely=0.33, relwidth=0.98, relheight=0.45)

    # Text label
    CMD_headerLabel = tk.Label(CMD_frame, text="Commands", font=headerFont, bg=sectionBg)
    CMD_headerLabel.place(relx=0.01, rely=0.01)

	
	# UNIX frame---------------------------------------------------------------
    CMD_general_frame = tk.Frame(CMD_frame, highlightbackground="black", highlightthickness=1)
    CMD_general_frame.place(relx=0.01, rely=0.12, relwidth=0.1, relheight=0.54)
	
	# Text label
    CMD_UNIX_headerLabel = tk.Label(CMD_general_frame, text="UNIX", font=sectionFont)
    CMD_UNIX_headerLabel.place(relx=0.08, rely=0.01)
    
    # UNIX timestamp set label and textbox
    setUNIXLabel = tk.Label(CMD_general_frame, text="UNIX timestamp", font=labelFont)
    setUNIXLabel.place(relx=0.1, rely=0.15)	
    setUNIXEntry = tk.Entry(CMD_general_frame, width=17, bg=fieldBg, borderwidth=2, relief="groove", name='setUNIXEntry')
    setUNIXEntry.place(relx=0.1, rely=0.25)
	
	# Get system UNIX button
    getSysUNIXButton = tk.Button(CMD_general_frame, width=13, bg="blue", fg="white", relief="groove", bd=5, text="Get system UNIX", command=getSystemUNIX)
    getSysUNIXButton.place(relx=0.12, rely=0.50)

	# UNIX timestamp set button
    setUNIXButton = tk.Button(CMD_general_frame, width=13, bg="green", fg="white", relief="groove", bd=5, text="Send command", command=setUNIXCommand)
    setUNIXButton.place(relx=0.12, rely=0.75)
	
	
	# LoRa frame---------------------------------------------------------------
    CMD_LoRa_frame = tk.Frame(CMD_frame, highlightbackground="black", highlightthickness=1)
    CMD_LoRa_frame.place(relx=0.12, rely=0.12, relwidth=0.87, relheight=0.25)
	
	# Text label
    CMD_LoRa_headerLabel = tk.Label(CMD_LoRa_frame, text="LoRa", font=sectionFont)
    CMD_LoRa_headerLabel.place(relx=0.01, rely=0.01)
    
    # Frequency label and textbox
    frLabel = tk.Label(CMD_LoRa_frame, text="Frequency (MHz)", font=labelFont)
    frLabel.place(relx=0.01, rely=0.30)	
    frEntry = tk.Entry(CMD_LoRa_frame, width=17, bg=fieldBg, borderwidth=2, relief="groove", name='frEntry')
    frEntry.place(relx=0.01, rely=0.50)
	
	# Bandwidth label and textbox
    bwLabel = tk.Label(CMD_LoRa_frame, text="Bandwidth (kbps?)", font=labelFont)
    bwLabel.place(relx=0.12, rely=0.30)	
    bwEntry = tk.Entry(CMD_LoRa_frame, width=17, bg=fieldBg, borderwidth=2, relief="groove", name='bwEntry')
    bwEntry.place(relx=0.12, rely=0.50)
	
	# Spreading factor label and textbox
    sfLabel = tk.Label(CMD_LoRa_frame, text="Spreading factor", font=labelFont)
    sfLabel.place(relx=0.23, rely=0.30)	
    sfEntry = tk.Entry(CMD_LoRa_frame, width=17, bg=fieldBg, borderwidth=2, relief="groove", name='sfEntry')
    sfEntry.place(relx=0.23, rely=0.50)
	
	# Coding rate label and textbox
    crLabel = tk.Label(CMD_LoRa_frame, text="Coding rate", font=labelFont)
    crLabel.place(relx=0.34, rely=0.30)	
    crEntry = tk.Entry(CMD_LoRa_frame, width=17, bg=fieldBg, borderwidth=2, relief="groove", name='crEntry')
    crEntry.place(relx=0.34, rely=0.50)
	
	# Sync word label and textbox
    swLabel = tk.Label(CMD_LoRa_frame, text="Sync word (decimal)", font=labelFont)
    swLabel.place(relx=0.45, rely=0.30)	
    swEntry = tk.Entry(CMD_LoRa_frame, width=17, bg=fieldBg, borderwidth=2, relief="groove", name='swEntry')
    swEntry.place(relx=0.45, rely=0.50)
	
	# Power label and textbox
    pwrLabel = tk.Label(CMD_LoRa_frame, text="Transmit power (dBm)", font=labelFont)
    pwrLabel.place(relx=0.56, rely=0.30)	
    pwrEntry = tk.Entry(CMD_LoRa_frame, width=17, bg=fieldBg, borderwidth=2, relief="groove", name='pwrEntry')
    pwrEntry.place(relx=0.56, rely=0.50)
	
	# Preamble length label and textbox
    plLabel = tk.Label(CMD_LoRa_frame, text="Preamble length", font=labelFont)
    plLabel.place(relx=0.67, rely=0.30)	
    plEntry = tk.Entry(CMD_LoRa_frame, width=17, bg=fieldBg, borderwidth=2, relief="groove", name='plEntry')
    plEntry.place(relx=0.67, rely=0.50)
	
	# Current limit label and textbox
    clLabel = tk.Label(CMD_LoRa_frame, text="Current limit", font=labelFont)
    clLabel.place(relx=0.78, rely=0.30)	
    clEntry = tk.Entry(CMD_LoRa_frame, width=17, bg=fieldBg, borderwidth=2, relief="groove", name='clEntry')
    clEntry.place(relx=0.78, rely=0.50)
	
	# LoRa set button
    setLoRaButton = tk.Button(CMD_LoRa_frame, width=13, bg="green", fg="white", relief="groove", bd=5, text="Send command", command=setLoRaCommand)
    setLoRaButton.place(relx=0.89, rely=0.40)
	
	
	# Mode frame---------------------------------------------------------------
    CMD_mode_frame = tk.Frame(CMD_frame, highlightbackground="black", highlightthickness=1)
    CMD_mode_frame.place(relx=0.12, rely=0.41, relwidth=0.87, relheight=0.25)
	
	# Text label
    CMD_mode_headerLabel = tk.Label(CMD_mode_frame, text="Mode", font=sectionFont)
    CMD_mode_headerLabel.place(relx=0.01, rely=0.01)
    
    # Mode label and option menu
    modeLabel = tk.Label(CMD_mode_frame, text="Mode", font=labelFont)
    modeLabel.place(relx=0.01, rely=0.30)	
    optionVar = tk.StringVar(CMD_mode_frame)
    optionVar.set(OPTIONS[0]) # default value
    modeOption = tk.OptionMenu(CMD_mode_frame, optionVar, *OPTIONS)
    modeOption.place(relx=0.01, rely=0.50)
    modeOption.config(width=10)
	
	# Message label and textbox
    messageLabel = tk.Label(CMD_mode_frame, text="Message", font=labelFont)
    messageLabel.place(relx=0.12, rely=0.30)	
    messageEntry = tk.Entry(CMD_mode_frame, width=129, bg=fieldBg, borderwidth=2, relief="groove", name='messageEntry')
    messageEntry.place(relx=0.12, rely=0.50)
	
	# Mode set button
    setLoRaButton = tk.Button(CMD_mode_frame, width=13, bg="green", fg="white", relief="groove", bd=5, text="Send command", command=setModeMessageCommand)
    setLoRaButton.place(relx=0.89, rely=0.40)
	
	
	# System reset frame-------------------------------------------------------
    CMD_SYSRST_frame = tk.Frame(CMD_frame, highlightbackground="black", highlightthickness=1)
    CMD_SYSRST_frame.place(relx=0.01, rely=0.70, relwidth=0.1, relheight=0.25)
	
	# Text label
    CMD_SYSRST_headerLabel = tk.Label(CMD_SYSRST_frame, text="System reset", font=sectionFont)
    CMD_SYSRST_headerLabel.place(relx=0.12, rely=0.01)
    
    # System reset button
    sysRstButton = tk.Button(CMD_SYSRST_frame, width=13, bg="red", fg="white", relief="groove", bd=5, text="Send command", command=sysRstCommand)
    sysRstButton.place(relx=0.12, rely=0.45)
	
	
	# Radio reset frame--------------------------------------------------------
    CMD_RADIORST_frame = tk.Frame(CMD_frame, highlightbackground="black", highlightthickness=1)
    CMD_RADIORST_frame.place(relx=0.12, rely=0.70, relwidth=0.1, relheight=0.25)
	
	# Text label
    CMD_RADIORST_headerLabel = tk.Label(CMD_RADIORST_frame, text="Radio reset", font=sectionFont)
    CMD_RADIORST_headerLabel.place(relx=0.16, rely=0.01)
    
    # System reset button
    radioRstButton = tk.Button(CMD_RADIORST_frame, width=13, bg="red", fg="white", relief="groove", bd=5, text="Send command", command=radioRstCommand)
    radioRstButton.place(relx=0.12, rely=0.45)
	
	
	# Custom command frame------------------------------------------
    CMD_cust_frame = tk.Frame(CMD_frame, highlightbackground="black", highlightthickness=1)
    CMD_cust_frame.place(relx=0.23, rely=0.70, relwidth=0.76, relheight=0.25) # (relx=0.23, rely=0.70, relwidth=0.1, relheight=0.25)
	
	# Text label
    CMD_cust_headerLabel = tk.Label(CMD_cust_frame, text="Send message", font=sectionFont)
    CMD_cust_headerLabel.place(relx=0.02, rely=0.01)
	
	# Message label and textbox
    custLabel = tk.Label(CMD_cust_frame, text="Message", font=labelFont)
    custLabel.place(relx=0.02, rely=0.30)	
    custEntry = tk.Entry(CMD_cust_frame, width=125, bg=fieldBg, borderwidth=2, relief="groove", name='custEntry')
    custEntry.place(relx=0.02, rely=0.50)	
    
    # Custom button
    custButton = tk.Button(CMD_cust_frame, width=13, bg="green", fg="white", relief="groove", bd=5, text="Send message", command=customCommand) #, state='disabled'
    custButton.place(relx=0.875, rely=0.45)

	
    #Start the GUI loop
    timertick()
    t.mainloop()
	

#-----------------------------------------------------------------------------------------------------------\
#                                                Command handlers                                           |
#-----------------------------------------------------------------------------------------------------------/


def getSystemUNIX():
     # Get the Entry field
    UNIXEntry = t.children['!frame2'].children['!frame'].children['setUNIXEntry']
    UNIXEntry.delete(0,tk.END)
    UNIXEntry.insert(0,str(int(time.time())))
		
def setUNIXCommand():
    # Used to check if the entered values are valid
    valid = True
	
	# Get the Entry field
    UNIXEntry = t.children['!frame2'].children['!frame'].children['setUNIXEntry']
	
	# Check the validity of the field
    if(verifyField(UNIXEntry, 0, None)): setValidField(UNIXEntry)
    else: valid = setInvalidField(UNIXEntry)
	
	# If not valid then return
    if(not valid): return
	
	# Get the field data
    timestamp = int(UNIXEntry.get())
	
	# Create the packet
    packet = setUNIXPacket(timestamp)
    if(packet == None):
        print("Field value error")
        return
	
	# Clear the Entry field
    UNIXEntry.delete(0,tk.END)
	
	# Transmit the packet to the L-COM
    sendPacket(packet)
	
def setLoRaCommand():
    # Used to check if the entered values are valid
    valid = True

    # Get the Entry fields
    frameRoot = t.children['!frame2'].children['!frame2']
    frEntry = frameRoot.children['frEntry']
    bwEntry = frameRoot.children['bwEntry']
    sfEntry = frameRoot.children['sfEntry']
    crEntry = frameRoot.children['crEntry']
    swEntry = frameRoot.children['swEntry']
    pwrEntry = frameRoot.children['pwrEntry']
    plEntry = frameRoot.children['plEntry']
    clEntry = frameRoot.children['clEntry']

	# Check the validity of all fields
    if(verifyField(frEntry, 150.0, 960.0)): setValidField(frEntry)
    else: valid = setInvalidField(frEntry)
    if(verifyField(bwEntry, 0.0, 510.0)): setValidField(bwEntry)
    else: valid = setInvalidField(bwEntry)
    if(verifyField(sfEntry, 5, 12)): setValidField(sfEntry)
    else: valid = setInvalidField(sfEntry)
    if(verifyField(crEntry, 5, 8)): setValidField(crEntry)
    else: valid = setInvalidField(crEntry)
    if(verifyField(swEntry, None, None, 0x34)): setValidField(swEntry)
    else: valid = setInvalidField(swEntry)
    if(verifyField(pwrEntry, -17, 22)): setValidField(pwrEntry)
    else: valid = setInvalidField(pwrEntry)
    if(verifyField(plEntry, 6, 65535)): setValidField(plEntry)
    else: valid = setInvalidField(plEntry)
    if(verifyField(clEntry, 0, 140)): setValidField(clEntry)
    else: valid = setInvalidField(clEntry)
	
	# If not valid then return
    if(not valid): return

	# Get the field data
    frequency 		= float(frEntry.get())
    bandwidth 		= float(bwEntry.get())
    spreadingFactor = int(sfEntry.get())
    codingRate 		= int(crEntry.get())
    syncWord 		= int(swEntry.get())
    power 			= int(pwrEntry.get())
    preambleLength 	= int(plEntry.get())
    currentLimit 	= float(clEntry.get())

	# Create the packet
    packet = setLoRaParametersPacket(frequency, bandwidth, spreadingFactor, codingRate, syncWord, power, preambleLength, currentLimit)
    if(packet == None):
        print("Field value error")
        return

    # Clear the Entry fields
    frEntry.delete(0,tk.END)
    bwEntry.delete(0,tk.END)
    sfEntry.delete(0,tk.END)
    crEntry.delete(0,tk.END)
    swEntry.delete(0,tk.END)
    pwrEntry.delete(0,tk.END)
    plEntry.delete(0,tk.END)
    clEntry.delete(0,tk.END)

	# Transmit the packet to the L-COM
    sendPacket(packet)
	
def setModeMessageCommand():
    # Used to check if the entered values are valid
    valid = True
	
	# Get the Entry fields
    messageEntry = t.children['!frame2'].children['!frame3'].children['messageEntry']
	
	# Check the validity of the field
    if(len(messageEntry.get()) <= MAX_LORA_MESSAGE_LENGTH): setValidField(messageEntry)
    else: valid = setInvalidField(messageEntry)

	# If not valid then return
    if(not valid): return
	
	# Get the field data
    message = messageEntry.get()
	
	# Create the packet
    packet = setModeMessagePacket(optionVar, message)
    if(packet == None):
        print("Field value error")
        return
	
	# Clear the Entry field
    messageEntry.delete(0,tk.END)
	
	# Transmit the packet to the L-COM
    sendPacket(packet)
	
def sysRstCommand():
    # Create the packet
    packet = systemResetPacket()
    if(packet == None):
        print("Field value error")
        return

	# Transmit the packet to the L-COM
    sendPacket(packet)	

def radioRstCommand():
    # Create the packet
    packet = radioResetPacket()
    if(packet == None):
        print("Field value error")
        return

	# Transmit the packet to the L-COM
    sendPacket(packet)	

def customCommand():

    # Used to check if the entered values are valid
    valid = True
	
	# Get the Entry fields
    custEntry = t.children['!frame2'].children['!frame6'].children['custEntry']
	
	# Check the validity of the field
    if(len(custEntry.get()) <= MAX_LORA_MESSAGE_LENGTH): setValidField(custEntry)
    else: valid = setInvalidField(custEntry)

	# If not valid then return
    if(not valid): return
	
	# Get the field data
    message = custEntry.get()
	
	# Create the packet
    #packet = negotiateLoRaParametersPacket()
    #packet = getModuleStatusPacket()
    #packet = getLoRaParametersPacket()
    #packet = getModeMessagePacket()
    #packet = getUnixPacket()
    #packet = messagePacket("Test message")
    #packet = ackPacket(1, "444")		
    packet = messagePacket(message)
    if(packet == None):
        print("Field value error")
        return
	
	# Clear the Entry field
    custEntry.delete(0,tk.END)

	# Transmit the packet to the L-COM
    sendPacket(packet)	


#-----------------------------------------------------------------------------------------------------------\
#                                                Helper functions                                           |
#-----------------------------------------------------------------------------------------------------------/	
	
	
def setInvalidField(entryObject):
    entryObject.configure(bg=invalidFieldBg)
    return False
		
def setValidField(entryObject):
    entryObject.configure(bg=fieldBg)
    return True
		
def verifyField(entryObject, lowerVal, upperVal, specificVal=''):
    # First ensure it is not empty
    if(entryObject.get() == ''): return False

	# Then ensure it is numeric
    if(not entryObject.get().replace('.','',1).replace('-','',1).isnumeric()):
        print('Failed numeric')
        return False
		
	# Ensure any negative signs are at the start
    if(entryObject.get().rfind('-') > 0): return False   
	
	# If a specific value (integer only) was given, check against that first
    if(not specificVal == ''):
        if(int(entryObject.get()) == specificVal): return False
		
	# Finally check it against the bounds (if given)
    fieldValue = float(entryObject.get()) # Float will cover the integer case
    if(not lowerVal == None and fieldValue < lowerVal): return False
    if(not upperVal == None and fieldValue > upperVal): return False

	# Return true if it passes otherwise
    return True
	
def sendPacket(_pkt):	
    #print(_pkt)
    _pkt.show()
    pktBytes = bytes(raw(_pkt))
    for i in pktBytes:
        ser.write(chr(i).encode('latin_1'))
        time.sleep(0.03)
		
def readSerial():
    if ser.in_waiting > 0:
        # Read in the next byte
        byte = ser.read()
        print(byte.decode('latin_1'), end='')
		
		# If Ack,
		# Maybe the Ack return data should include the command ID?
		# Or after sending data, wait for a moment?
		# How exactly do we know which Ack is for what command, and what the exact Ack return data contents are?
		# So maybe an ID field for the command would be best...


#-----------------------------------------------------------------------------------------------------------\
#                                                  Program run                                              |
#-----------------------------------------------------------------------------------------------------------/  


if __name__ == '__main__':
    #If the files do not currently exist, create them
    #eventFile = open("eventLog.txt", "a")
    #eventFile.write("############################################\n#               Server start               #\n############################################\n")
    #eventFile.close()

    #Starts the GUI
    _thread.start_new_thread(threadmain, ())

    #Enters the main loop
    while True:
        #Send a heart-beat every second
        #if(remote_address != '' and remote_port != '' and (time.time() - last_beat) >= beat_delay):
        #    last_beat = time.time()
        #    message = bytes("GROUNDSTATION,HBT\0", 'utf-8')
        #    remoteSocket.sendto(message, (str(remote_address), int(remote_port)))

	    # Run serial stuff here
        readSerial()