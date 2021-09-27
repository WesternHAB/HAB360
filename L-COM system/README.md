# L-COM
This system is intended to serve as the communications system for high-altitude balloons and other devices in need of wireless communications.

The L-COM device may either be used as an attached radio by sending/receiving messages on the UART interface, or it may be programmed to be used as the sole onboard controller.

A python-based GUI is provided to allow full control over the L-COM device via a laptop, and may be adapted to be used as a groundstation.

## L-COM
![External view of the L-COM module](Images/github_external.jpg?raw=true "External view of the L-COM module")
![Internal view of the L-COM module](Images/github_internal.jpg?raw=true "Internal view of the L-COM module")
![Image of two L-COM boards](Images/good_and_bad_boards.jpg?raw=true "First produced (and working) boards")

## Testing results
Initial testing involved the use of low-range, data-rate maximizing settings, while travelling throughout an urban environment. The L-COM modules behaved as expected, and the results produced were nominal for the environment. Communication was relatively unhindered by most residential buildings, and only encountered issues when blocked by large hills or certain non-residential buildings built with different materials.

Remaining testing involves long-range settings in a rural environment in order to provide a better estimate of how effective it will be for communicating with high-altitude balloons.

![Testing path](Images/testing/path.png?raw=true "Testing path")
![RSSI](Images/testing/RSSI.png?raw=true "RSSI")
![SNR](Images/testing/SNR.png?raw=true "SNR")
![RC_errors](Images/testing/CRC_errors.png?raw=true "RC_errors")
