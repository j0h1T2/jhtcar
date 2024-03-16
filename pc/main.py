import requests

# ESP8266的IP地址
esp_ip = "192.168.4.1"


# 控制机器人的函数
def control_robot(command):
    url = f"http://{esp_ip}/?State={command}"
    response = requests.get(url)
    print("Response:", response.text)


# 主循环，接受键盘输入并发送相应的命令给ESP8266
while True:
    print("Enter command (W: Forward, X: Backward, A: Left, D: Right, Q: Quit):")
    command = input().upper()

    if command == 'Q':
        break

    if command in ['W', 'Q', 'A', 'Z', 'X', 'C', 'D', 'E', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'S']:
        control_robot(command)
        print('Some changes happened')
    else:
        print("Invalid command. Please enter W,Q,A,Z,X,C,D,E,S,0-9.")
