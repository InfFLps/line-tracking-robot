> [!NOTE]
> * Code still not completed for the ``QTR 8RC Array``

## Hardware Used
- TB6612FNG (Motor Driver)
- ESP32
- QTR 8RC Array
- DC Motor (Any)
- Power Supply (MB102)

## Circuit
1. TB6612FNG
   - GND (All three): ESP32 GND
   - VCC: ESP32 3.3V
   - AIN1: GPIO13
   - AIN2: GPIO14
   - PWMA: GPIO25
   - PWMB: GPIO26
   - BIN1: GPIO32
   - BIN2: GPIO33
   - VM: Battery (+)
   - AO1: Left or Right DC motor (+ or -)
   - AO2: Left or Right DC motor (+ or -)
   - BO1: Right or Left DC motor (+ or -)
   - BO2: Right or Left DC motor (+ or -)
2. QTR 8RC Array
   - None for the moment (Still not working for me but ``EVN`` and ``ODD`` should be ``LOW`` or ``HIGH`, it turns the sensors on or off)
3. MB102 Power Supply
   - Battery Positive & Negative to Male Barrel to Female Barrel from the power supply
   - Power Supply USB Female to Male USB connector to Type C connector to ESP32
