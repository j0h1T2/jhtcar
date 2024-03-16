import requests

# ESP8266的IP地址
esp_ip = "192.168.4.1"


# 控制机器人的函数
def control_robot(command):
    url = f"http://{esp_ip}/?State={command}"
    response = requests.get(url)
    # 检查响应的状态码
    if response.status_code == 200:
        print("Request successful")
        # 打印响应头和内容
        print("Response Headers:")
        print(response.headers)
        print("Response Body:")
        print(response.text)
    else:
        print("Request failed with status code:", response.status_code)


# 主循环，接受键盘输入并发送相应的命令给ESP8266
while True:
    print("Enter command (W: Forward, X: Backward, A: Left, D: Right, S: Quit):")
    command = input().upper()

    if command in ['W', 'Q', 'A', 'Z', 'G', 'C', 'D', 'E', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'S']:
        control_robot(command)
        print('Some changes happened')
    if command == 'G':
        break
    else:
        print("Invalid command. Please enter W,Q,A,Z,G,C,D,E,S,0-9.")
