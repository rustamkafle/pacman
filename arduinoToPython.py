import time
import serial

# Initialize serial communication
try:
    arduinoData = serial.Serial('COM5', 9600)
    time.sleep(1)
except Exception as e:
    print(f"Error initializing serial communication: {e}")
    exit(1)

# File path
file_path = r"C:\TURBOC3\BIN\ARROW.TXT"


while True:
    while arduinoData.inWaiting() == 0:
        pass  # Wait for data

    # Read and decode the data
    dataPacket = arduinoData.readline().decode('utf-8').strip()
    
    # Print to terminal
    print(dataPacket)

    # Overwrite the file with the latest data
    with open(file_path, "w") as file:
        file.write(dataPacket)
