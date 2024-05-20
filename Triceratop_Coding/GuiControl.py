from tkinter import *
import paho.mqtt.publish as publish

# สร้างหน้าต่างหลัก
root = Tk()
root.title("Control Triceratops")
root.geometry("290x180+600+280")  # กำหนดขนาดหน้าต่าง


broker_address = "broker.hivemq.com"  # ตรวจสอบว่าโฮสต์นี้สามารถเข้าถึงได้
port = 1883  # พอร์ตสำหรับ MQTT
topic = "Triceratops"

def move_forward():
    message = "forward"
    try:
        # ส่งข้อความ
        publish.single(topic, message, hostname=broker_address, port=port)
        print("Message published successfully")
    except Exception as e:
        print(f"Failed to publish message: {e}")

def shake_head():
    message = "shakehead"
    try:
        # ส่งข้อความ
        publish.single(topic, message, hostname=broker_address, port=port)
        print("Message published successfully")
    except Exception as e:
        print(f"Failed to publish message: {e}")

def make_sound():
        message = "playsound"
        try:
            # ส่งข้อความ
            publish.single(topic, message, hostname=broker_address, port=port)
            print("Message published successfully")
        except Exception as e:
            print(f"Failed to publish message: {e}")

def stop():
    message = "stop"
    try:
        # ส่งข้อความ
        publish.single(topic, message, hostname=broker_address, port=port)
        print("Message published successfully")
    except Exception as e:
        print(f"Failed to publish message: {e}")

label = Label(root, text="Triceratops Mode", font=("Lamoon", 13),bg="#696969",fg="white").place(x = 80 , y = 30)
# สร้างปุ่มสำหรับการเคลื่อนที่ข้างหน้า
btn_forward = Button(root, text="Forward", background="#9999FF", foreground='black',fg="black" , font=("Lamoon", 10), command=move_forward).place(x = 30 , y = 80)
# สร้างปุ่มสำหรับการสั่นหัว
btn_shake_head = Button(root, text="Shake a Head", background="#9999FF", foreground='black',fg="black", font=("Lamoon", 10), command=shake_head).place(x = 102 , y = 80)
# สร้างปุ่มสำหรับการเล่นเสียง
btn_sound = Button(root, text="Sound", background="#9999FF", foreground='black',fg="black", font=("Lamoon", 10), command=make_sound).place(x = 210 , y = 80)
# สร้างปุ่มสำหรับหยุดทุกอย่าง
btn_stop = Button(root, text="Stop", background="#FF9999", foreground='black',fg="black", font=("Lamoon", 10), command= stop).place(x = 130 , y = 130)


# ตั้งค่าพื้นหลังของหน้าต่างเป็นสีเขียว
root.configure(bg="#696969")

# แสดงหน้าต่าง GUI
root.mainloop()
