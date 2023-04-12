import serial
import pyautogui

# Connect to the serial port
ser = serial.Serial('/dev/cu.usbserial-0001', 115200)

while True:
    # Read the data from the serial port
    data = ser.readline().decode().strip()

    # Split the data into X, Y, and Z values
    
    values = data.split(',')
    
    
    if values[0] == 'L':
        pyautogui.click() # Simulate a left-click
        
    if values[0] == 'R':
        pyautogui.rightClick()
        

    # Check if the data contains 3 values
    if len(values) == 3:
        # Try to convert the values to floats
        try:
            x = float(values[0])
            y = float(values[1])
            z = float(values[2])

            # Move the mouse cursor
            pyautogui.moveRel(x, y, duration=0)

            # Check the orientation of the movement
          #  if z == 1:
           #     pyautogui.click()
            
        
        except ValueError:
           print("Invalid data:", data)
