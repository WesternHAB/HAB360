# Max serial size should actually be 268?


#--------------------------------------------------------------------------\
#								  	Imports					   			   |
#--------------------------------------------------------------------------/


from scapy.all import *
from Serial_packet import *	


#--------------------------------------------------------------------------\
#								  Definitions					   		   |
#--------------------------------------------------------------------------/


# Statuses
CMD_OK						= 0x00
# Add all the RadioLib ones here, then my own after


# Command identifier
SET_LORA_PARAMETERS			= 0x00
SET_UNIX					= 0x01
SET_MODE_MESSAGE			= 0x02

GET_LORA_PARAMETERS			= 0x10
GET_UNIX					= 0x11
GET_MODE_MESSAGE			= 0x12
GET_MODULE_STATUS			= 0x13

RADIO_RESET					= 0x20
SYSTEM_RESET				= 0x21
NEGOTIATE_LORA_PARAMETERS	= 0X22

# Modes
NORMAL_MODE					= 0x00
REPEATER_MODE				= 0x01
stringModeDict 				= {'Normal':NORMAL_MODE, 'Repeater':REPEATER_MODE}

# Messages and commands
MAX_LORA_MESSAGE_LENGTH		= 255

# LoRa parameters
DEFAULT_FREQUENCY 			= 915.0
DEFAULT_BANDWIDTH           = 125.0
DEFAULT_SPREADING_FACTOR    = 9
DEFAULT_CODING_RATE         = 7
DEFAULT_SYNC_WORD           = 0x12                    # (private network)
DEFAULT_POWER        		= 14                      # (max 22 dBm)
DEFAULT_CURRENT_LIMIT       = 60.0                    # (max 140 mA)
DEFAULT_PREAMBLE_LENGTH     = 8
DEFAULT_CURRENT_LIMIT     	= 60.0


#--------------------------------------------------------------------------\
#								   Variables					   		   |
#--------------------------------------------------------------------------/


#--------------------------------------------------------------------------\
#								   Classes						   		   |
#--------------------------------------------------------------------------/

#-------------------------------------------------------\
#Packets------------------------------------------------|
# Status
#class statusPayload(Packet):
#    name = "statusProtocol"
#    fields_desc=[
#		ByteField("loraSet", 0),
#		ByteField("UNIXSet", 0),
#		IntField("uptime", 0),
#		IEEEFloatField("temperature", 0.0),
#		IntField("TOA", 0),
#		IEEEFloatField("dataRate", 0.0)
#	]
	
# Ack
class ackPayload(Packet):
    name = "ackProtocol"
    fields_desc=[
		ShortField("result", CMD_OK),
		StrLenField("data", "")
	]
	
# Message
class messagePayload(Packet):
    name = "messageProtocol"
    fields_desc=[
		IntField("RSSI", 0),
		IntField("SNR", 0),
		ShortField("result", CMD_OK),	# e.g. notifies if there are CRC errors or anything. Keeps it in one packet instead of sending a second ACK packet.
		StrLenField("message", "Default message") # Don't pad this, want to keep the size reduced as much as possible when transmitting
	]	
	
#-------------------------------------------------------\
#Commands-----------------------------------------------|	

#------------Set commands------------#
# Set LoRa parameters command
class setLoRaParametersPayload(Packet):
    name = "setLoRaParametersProtocol"
    fields_desc=[
		ByteField("command", SET_LORA_PARAMETERS),
		IEEEFloatField("frequency", DEFAULT_FREQUENCY),
		IEEEFloatField("bandwidth", DEFAULT_BANDWIDTH),
		ByteField("spreadingFactor", DEFAULT_SPREADING_FACTOR),
		ByteField("codingRate", DEFAULT_CODING_RATE),
		ByteField("syncWord", DEFAULT_SYNC_WORD),
		ByteField("power", DEFAULT_POWER),
		ShortField("preambleLength", DEFAULT_PREAMBLE_LENGTH),
		IEEEFloatField("currentLimit", DEFAULT_CURRENT_LIMIT)
	]
	
# Set UNIX time command
class setUNIXPayload(Packet):
    name = "setUNIXProtocol"
    fields_desc=[
		ByteField("command", SET_UNIX),
		IntField("timestamp", int(time.time()))
	]
	
# Set mode command
class setModeMessagePayload(Packet):
    name = "setModeMessageProtocol"
    fields_desc=[
		ByteField("command", SET_MODE_MESSAGE),
		ByteField("mode", NORMAL_MODE),
		StrLenField("message", "Default message") # Don't pad this, want to keep the size reduced as much as possible
	]
	
	
#------------Get commands------------#		
# Get LoRa parameters command
class getLoRaParametersPayload(Packet):
    name = "getLoRaParametersProtocol"
    fields_desc=[
		ByteField("command", GET_LORA_PARAMETERS)
	]
	
# Get UNIX time command
class getUnixPayload(Packet):
    name = "getUnixProtocol"
    fields_desc=[
		ByteField("command", GET_UNIX)
	]
	
# Get mode command
class getModeMessagePayload(Packet):
    name = "getModeMessageProtocol"
    fields_desc=[
		ByteField("command", GET_MODE_MESSAGE)
	]
	
# Get status command
class getStatusPayload(Packet):
    name = "getStatusProtocol"
    fields_desc=[
		ByteField("command", GET_MODULE_STATUS),
	]
	
	
#-------Miscellaneous commands-------#	
# Radio reset command
class radioResetPayload(Packet):
    name = "radioResetProtocol"
    fields_desc=[
		ByteField("command", RADIO_RESET)
	]
	
# System reset command
class systemResetPayload(Packet):
    name = "systemResetProtocol"
    fields_desc=[
		ByteField("command", SYSTEM_RESET)
	]
	
# Negotiate LoRa parameters command
class negotiateLoRaParametersPayload(Packet):
    name = "negotiateLoRaParametersProtocol"
    fields_desc=[
		ByteField("command", NEGOTIATE_LORA_PARAMETERS)
	]
	

#--------------------------------------------------------------------------\
#								   Functions					   		   |
#--------------------------------------------------------------------------/				


#-------------------------------------------------------\
#Packets------------------------------------------------|
# Status
#def statusPacket(_loraSet, _UNIXSet, _uptime, _temperature, _TOA, dataRate):
#	# Probably have no need to implement this? If needed, do it later.
#
#	# Create the payload
#	payload = statusPayload(
#		loraSet 			= _loraSet,
#		UNIXSet				= _UNIXSet,
#		uptime				= _uptime,
#		temperature			= _temperature,
#		TOA					= _TOA,
#		dataRate			= _dataRate
#	)
#
#	# Create and return the serial packet
#	return createPacket(raw(payload), "status")

# Ack
def ackPacket(_result, _data):
	# Create the payload
	payload = ackPayload(
		result 			= _result,
		data			= _data
	)	

	# Create and return the serial packet
	return createPacket(raw(payload), "ack")

# Message
def messagePacket(_message):
	# Perform validity checks on the parameters
	if (len(_message) > MAX_LORA_MESSAGE_LENGTH or len(_message) <= 0):
		return None

	# Create the payload
	payload = messagePayload()
	
	# Add the message separately so that we cannot end up with a zero-length message (will use the default)
	if(len(_message) > 0):
		payload.message = _message[:MAX_LORA_MESSAGE_LENGTH]
		print(_message)

	# Create and return the serial packet
	return createPacket(raw(payload), "message")
	
#-------------------------------------------------------\
#Commands-----------------------------------------------|	

#------------Set commands------------#
def setLoRaParametersPacket(_frequency, _bandwidth, _spreadingFactor, _codingRate, _syncWord, _power, _preambleLength, _currentLimit):
	# Perform validity checks on the parameters
	if (_frequency < 150.0 or _frequency > 960.0):
		return None
	elif (_bandwidth < 0.0 or _bandwidth > 510.0):
		return None
	elif (_spreadingFactor < 5 or _spreadingFactor > 12):
		return None
	elif (_codingRate < 5 or _codingRate > 8):
		return None
	elif (_syncWord < 0 or _syncWord > 255 or _syncWord == 0x34): # LoRaWAN sync word
		return None
	elif (_power < -17 or _power > 22):
		return None
	elif (_preambleLength < 6 or _preambleLength > 65535):
		return None
	elif (_currentLimit < 0 or _currentLimit > 140):
		return None

	# Create the payload
	payload = setLoRaParametersPayload(
		frequency 			= _frequency,
		bandwidth 			= _bandwidth,
		spreadingFactor 	= _spreadingFactor,
		codingRate 			= _codingRate,
		syncWord 			= _syncWord,
		power 				= _power,
		preambleLength 		= _preambleLength,
		currentLimit 		= _currentLimit
	)	

	# Create and return the serial packet
	return createPacket(raw(payload), "command")
	
def setUNIXPacket(_timestamp):
    # Perform validity checks on the parameters
	if (_timestamp < 0):
		return None

	# Create the payload
	payload = setUNIXPayload(
		timestamp 		= _timestamp
	)	

	# Create and return the serial packet
	return createPacket(raw(payload), "command")
	
def setModeMessagePacket(_mode, _message):
	# Perform validity checks on the parameters
	if (not _mode.get() in stringModeDict):
		return None
	if (len(_message) > MAX_LORA_MESSAGE_LENGTH):
		return None

	# Create the payload
	payload = setModeMessagePayload(
		mode 			= stringModeDict.get(_mode.get())
	)
	
	# Add the message separately so that we cannot end up with a zero-length message (will use the default)
	if(len(_message) > 0):
		payload.message 		= _message[:MAX_LORA_MESSAGE_LENGTH]

	# Create and return the serial packet
	return createPacket(raw(payload), "command")

	
#------------Get commands------------#	
def getLoRaParametersPacket():
	# Create the payload
	payload = getLoRaParametersPayload()	

	# Create and return the serial packet
	return createPacket(raw(payload), "command")

def getUnixPacket():
	# Create the payload
	payload = getUnixPayload()	

	# Create and return the serial packet
	return createPacket(raw(payload), "command")

def getModeMessagePacket():
	# Create the payload
	payload = getModeMessagePayload()	

	# Create and return the serial packet
	return createPacket(raw(payload), "command")

def getModuleStatusPacket():
	# Create the payload
	payload = getStatusPayload()	

	# Create and return the serial packet
	return createPacket(raw(payload), "command")	
	
	
#-------Miscellaneous commands-------#	
def radioResetPacket():
	# Create the payload
	payload = radioResetPayload()	

	# Create and return the serial packet
	return createPacket(raw(payload), "command")	

def systemResetPacket():
	# Create the payload
	payload = systemResetPayload()	

	# Create and return the serial packet
	return createPacket(raw(payload), "command")

def negotiateLoRaParametersPacket():
	# Create the payload
	payload = negotiateLoRaParametersPayload()	

	# Create and return the serial packet
	return createPacket(raw(payload), "command")