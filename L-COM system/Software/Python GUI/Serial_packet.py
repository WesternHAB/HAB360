#--------------------------------------------------------------------------\
#								  	Imports					   			   |
#--------------------------------------------------------------------------/


from scapy.all import *
import time


#--------------------------------------------------------------------------\
#								  Definitions					   		   |
#--------------------------------------------------------------------------/


# Signify the beginning and end of the packet
START_FLAG					= 0x7E
END_FLAG					= 0x7F

# Packet, header, and payload lengths
PKT_MAX_LEN					= 274
PKT_HEADER_LEN				= 9 # This includes the 1 byte trailer
PKT_MAX_DATA_PAYLOAD_LEN	= 265 # PKT_MAX_LEN - PKT_HEADER_LEN

# Field locations
TYPE_CYCLIC_FIELD_INDEX		= 1
LENGTH_INDEX				= 2
UNIX_TIME_INDEX				= 4
PAYLOAD_INDEX				= 8

# Packet type (Most-significant 3 bits identify type, last 5 bits are for cyclic frame count)
#STATUS_PACKET 				= 0b00000000
ACK_PACKET 					= 0b00000000
COMMAND_PACKET 				= 0b00100000
MESSAGE_PACKET 				= 0b01000000


#--------------------------------------------------------------------------\
#								   Variables					   		   |
#--------------------------------------------------------------------------/


_cyclicID = -1


#--------------------------------------------------------------------------\
#								  Packet class					   		   |
#--------------------------------------------------------------------------/


# The packet class; defines the fields and default values
class Packet(Packet):
    name = "commandProtocol"
    fields_desc=[
		ByteField("startFlag", START_FLAG),		
		ByteField("packet_typeCyclic", (ACK_PACKET | _cyclicID)),
		ShortField("packetLength", 0),
		IntField("UNIXTime", int(time.time())),
		StrLenField("payloadData", None),
		#PadField(StrLenField("payloadData", ""), PKT_MAX_DATA_PAYLOAD_LEN),
		ByteField("endFlag", END_FLAG)
	]


#--------------------------------------------------------------------------\
#								   Functions					   		   |
#--------------------------------------------------------------------------/				


def createPacket(_payload, _type):
	# Declare the global variables
	global _cyclicID
	
	# Variables
	currentTime = int(time.time()) 					# Get the current time

	# Increment the cyclic frame count
	_cyclicID = (_cyclicID + 1) % 32	
	
	# Create the packet identifier byte
	if _type == "ack":
		packetType = ACK_PACKET
	elif _type == "command":
		packetType = COMMAND_PACKET
	elif _type == "message":
		packetType = MESSAGE_PACKET
	#elif _type == "status":
	#	packetType = STATUS_PACKET
	else:
		return

	_packetIdentifier = (packetType & 0b11100000) | (_cyclicID & 0b00011111)
	
	# Create the packet
	packet = Packet(
		packet_typeCyclic 	= _packetIdentifier,	
		packetLength 		= 0,
		UNIXTime 			= currentTime,
		payloadData 		= _payload[:PKT_MAX_DATA_PAYLOAD_LEN],
	)

	# Add the frame length
	packet.packetLength = len(packet)

	# Return the finished packet
	return packet