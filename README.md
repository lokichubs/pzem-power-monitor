# PZEM-004T Power Monitoring Utility
<a href="https://github.com/Purdue-DC-Nanogrid-House-Project">Click here</a> to see the entire project code 
in the Direct Current Nanogrid Repo. This repo only contains the portion of the project I worked on.

## Specifications
| Measurement    | Range           | Accuracy | Resolution |
|----------------|-----------------|----------|------------|
| Voltage (AC)   | 80 - 260        | 0.5%     | 0.1 V      |
| Power Factor   | 0 - 1           | 1%       | 0.01       |
| Frequency (Hz) | 45 - 65         | 0.5%     | 0.1 Hz     |
| Current (A)    | 0 - 100 A       | 0.5%     | 0.001 A    |
| Real Power     | 0.4 W - 23 kW   | 0.5%     | 0.1 W      |
| Energy (kWh)   | 0 - 9999.99 kWh | 0.5 %    | 1 Wh       |

## PZEM Communication ID Modification
Each pzem module has a default Modbus communication address of 0xF8 which it uses to receive and broadcast data. If multiple pzems are used on the same UART bus, this will lead to conflicts and issues processing data. To resolve this issue, the pzem's communication address can be changed.

A critical concern when changing the address is that no more than one pzem may be connected to the device modifying the address to achieve the desired configuration. Otherwise, each connected pzem will receive the updated address, and result in the same initial problem. To enforce the desired custom communication address, connect **one** pzem module to the connected microcontroller, and upload the code with the desired hexadecimal address. Make sure that each pzem's address is an increment of only 0x1 from the last so that the power monitoring routine can identify them sequentially.

[PZEM Custom Address Routine](modify-communication-address/src/main.cpp)
