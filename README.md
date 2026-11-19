# ECE 528/L - Robotics and Embedded Systems with Lab
**CSU Northridge**

**Department of Electrical and Computer Engineering**

## Bluetooth Low Energy (BLE) Lab
The Bluetooth Low Energy (BLE) lab interfaces with the following:

* User LEDs of the TI MSP432 LaunchPad
* Pololu Gearmotor with Encoder - [Product Link](https://www.pololu.com/product/3675)
* Adafruit Bluefruit LE UART Friend - Bluetooth Low Energy (BLE) Module - [Product Link](https://www.adafruit.com/product/2479)


## Pre-Lab

1. Bluetooth Low Energy (BLE) is an alternative to the classic Bluetooth that was developed for use within low-power applications. Both BLE and Bluetooth classic have the same communication range of 10-30 m (1).

2. GAP, which stands for Generic Access Profile, makes the device visible to other devices and control what connections the device can or cannot make. Peripheral devices are small, low-power devices that connect to a more powerful central device. Central devices, like mobile phones or tablets, have far more processing power and memory than peripheral devices (2).

3. GATT defines the way how two BLE devices transfer data back and forth. Services are used to break data up into logical entities, and contain specific chunks of data called characteristics. A profile is a pre-defined collection of services that has been compiled by either the Bluetooth SIG or by the peripheral designers. (2)

4. In BLE, an advertising packet is sent out by a device to notify central devices in range of its existence. It can contain up to 31 bytes of data (2). The types of data it includes are its UUID, service data, local name, flags, TX power level, and service solicitation (3).

5. A UUID is a unique numeric ID used to identify a particular service. 128-bit UUIDs are used because a randomly generated UUID is guaranteed to be unique (2^128 possible values) (4).

6. The bit that determines if the UART data is received or transmitted MSB or LSB first is UCMSB (bit 13) in the UCAxCTLW0 register (eUSCI_Ax Control Word 0). When UCMSB = 0, LSB goes first. When UCMSB = 1, MSB goes first (5).

7. (6)

<table>
  <tr>
    <th>Pin</th>
    <th>Mnemonic</th>
    <th>Input Pin Primary Function</th>
    <th>Output Pin Primary Function</th>
  </tr>
  <tr>
    <td>P2.2</td>
    <td>PM_UCA1RXD / PM_UCA1SOMI</td>
    <td colspan="2">eUSCI_A1 UART RXD (direction controlled by eUSCI – input) / eUSCI_A1 SPI slave out master in (direction controlled by eUSCI)</td>
  </tr>
  <tr>
    <td>P2.3</td>
    <td>PM_UCA1TXD / PM_UCA1SIMO</td>
    <td colspan="2">eUSCI_A1 UART TXD (direction controlled by eUSCI – output) / eUSCI_A1 SPI slave in master out (direction controlled by eUSCI)</td>
  </tr>
  <tr>
    <td>P3.2</td>
    <td>PM_UCA2RXD / PM_UCA2SOMI</td>
    <td colspan="2">eUSCI_A2 UART RXD (direction controlled by eUSCI – input) / eUSCI_A2 SPI slave out master in (direction controlled by eUSCI)</td>
  </tr>
  <tr>
    <td>P3.3</td>
    <td>PM_UCA2TXD / PM_UCA2SIMO</td>
    <td colspan="2">eUSCI_A2 UART TXD (direction controlled by eUSCI – output) / eUSCI_A2 SPI slave in master out (direction controlled by eUSCI)</td>
  </tr>
</table>

8.
````c
void P2_2_and_P2_3_Init() {
    P2->SEL0 |=  0x0C;
    P2->SEL1 &= ~0x0C;
}
````

## References

1. https://www.geeksforgeeks.org/computer-networks/bluetooth-vs-bluetooth-low-energy/

2. https://cdn-learn.adafruit.com/downloads/pdf/introduction-to-bluetooth-low-energy.pdf

3. https://www.bluetooth.com/blog/advertising-works-part-2/

4. https://en.wikipedia.org/wiki/Universally_unique_identifier

5. https://e2e.ti.com/cfs-file/__key/communityserver-discussions-components-files/166/slau356i.pdf (page 943)

6. https://www.ti.com/lit/ds/slas826e/slas826e.pdf (page 126)