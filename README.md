# Triceratops Robot
The Triceratops Robot is designed to mimic the walking posture and behavior of the Triceratops, a herbivorous dinosaur that first appeared in the late Maastrichtian stage of the Late Cretaceous period. The robot operates in three modes:

1. **Forward Walking**: The robot can move forward smoothly, replicating the walking motion of a Triceratops.
2. **Head Swaying**: The robot can sway its head from side to side, enhancing the realism of the Triceratops' behavior.
3. **Roaring Sound**: The robot can produce sounds similar to the roaring of a Triceratops, adding a lively and realistic experience.

The design and functionality of the Triceratops Robot are intended not only for display and educational purposes but also to integrate technology and research on dinosaurs with the modern world. This allows people to experience and learn about these ancient creatures in an effective and enjoyable way.
## How to build Triceratops Robot
For building a Triceratops robot, it is divided into three parts. The first part is Mechanics, the second part is Electronics, and the third part is Coding.
### Mechanic
**Triceratops_Mechanic** folder, download all the files in the folder, and then perform 3D printing or laser cutting as appropriate. After that, assemble the parts into a robot according to the image below.

![Assem_Triceratops](https://github.com/kcynn/Triceratops-Robot/assets/154345247/e860123a-ac1d-4964-b252-cbd763943b91)
![Assem_Triceratops_Back](https://github.com/kcynn/Triceratops-Robot/assets/154345247/14602e66-f8ba-4bd8-b64e-f060c3ba7fbb)
![Assem_Triceratops_Left](https://github.com/kcynn/Triceratops-Robot/assets/154345247/970fc20b-5ccf-4c66-a5b0-0ce9ad3976f9)
![Assem_Triceratops_Right](https://github.com/kcynn/Triceratops-Robot/assets/154345247/59bcede5-a343-42cc-b00f-6c5bcc7f1168)
![Assem_Triceratops_Top](https://github.com/kcynn/Triceratops-Robot/assets/154345247/468e26b1-465d-4b2d-8b77-3d083101987e)
![Assem_Triceratops1](https://github.com/kcynn/Triceratops-Robot/assets/154345247/3d3ff8e0-3c7b-4041-93e2-2f688b468ec9)

### Electronics
In the Electronics section, we will discuss various electronic components used, including circuit diagrams.
![Hardware](https://github.com/kcynn/Triceratops-Robot/assets/154345247/c83674f9-aa1c-4b56-9ac9-a466ae43332f)
**Circuit Diagrams**
![Circuit Diagram](https://github.com/kcynn/Triceratops-Robot/assets/154345247/74768352-ca98-4eb2-ba59-f876aa3eb35e)

### Coding
1. Start by downloading the Coppelia Sim EDU program to set the servo ID. You can download the program from this link 

    [Download the Coppelia Sim EDU program](https://drive.google.com/drive/folders/1K7o4vWiYT11PruWJc6WMWG7d1hdri8We?usp=sharing)
2. Afterwards, proceed to assign servo IDs using the Coppelia Sim EDU program as demonstrated in this video link. [Assign servo IDs](https://youtu.be/GX-KO-Zlhtw?si=XaPr_eEYJO_c3Mkw)
3. Then, proceed to set all servos to 0 degrees. Access the **Triceratops_coding** folder, open the **SetZeroMotor.ino** file, adjust the IDs correctly, and run the SetZeroMotor code. Once completed, Servo 0 degrees should align as depicted in the image.

    ![Servo0Degree](https://github.com/kcynn/Triceratops-Robot/assets/154345247/bca507c4-22e9-4424-90d7-b6270cd65639)
5. Next, download the **Triceratops sound.mp3** audio file (.MP3) and insert it into the micro SD card.
6. The next step is to create a GUI window to control the robot's actions. Navigate to the **Triceratops_coding** folder and open the **GuiControl.py** file.
7. Finally, you will find the robot's code in the **Triceratops_coding** folder. Open the **Control_Robot.ino** file to access it.
   
## Steps to run the code
1. Check if the circuit is connected correctly and then Upload the **Control_Robot.ino** code to the Arduino R4 board.
2. Check if the Arduino R4 board is connected to Wi-Fi.
3. Then, run the **GuiControl.py** code.
4. Click on the commands on the GUI screen to instruct the robot to perform tasks.
