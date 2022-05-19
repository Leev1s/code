import urllib.request, urllib.error, time
import csv
import datetime, random

ac = "/Users/lev1s/Desktop/python/ac.csv"

with open(ac) as f:
    ac_list = [i for i in csv.reader(f)]

random.shuffle(ac_list)
Pointer=random.randint(0,len(ac_list)-1)
print("名单共计"+str(len(ac_list))+"人，顺序已打乱，今天幸运数字是"+str(Pointer)+"\n")

url1 = "http://10.20.10.11/drcom/login?callback=dr1630741978564&DDDDD="
url2 = "&upass="
url3 = "&0MKKey=123456&R1=0&R3=0&R6=0&para=00&v6ip=&_=1630741961177"

def askAC(url1,url2,url3):
    ac1=ac_list[Pointer][0]
    ac2=ac_list[Pointer][1]
    URL=url1+ac1+url2+ac2[-6:]+url3
    return URL

def main():
    global Pointer
    while 1:
        if isNetOK() == False:
            print("被断开！正在重新连接\n")
            if Pointer < len(ac_list):
                Net=askURL(askAC(url1,url2,url3))
                doubleCheck(Net)
            else:
                Pointer=0
                Net=askURL(askAC(url1,url2,url3))
                doubleCheck(Net)
        else:
            print(datetime.datetime.now())
            print("已稳定联网(当前为第"+str(Pointer)+"组)\n")
        time.sleep(5)

def askURL(url):
    head = {  # 模拟浏览器头部信息
        "User-Agent": "Mozilla / 5.0(Windows NT 10.0; Win64; x64) AppleWebKit / 537.36(KHTML, like Gecko) Chrome / 80.0.3987.122  Safari / 537.36"
    }
    # 将头部信息 封装 给 urllib.request.Request 的 一个 实例化的 类
    req = urllib.request.Request(url,headers=head)
    #html=""
 
    try:
        # 对封装好的类进行访问 得到响应
        response = urllib.request.urlopen(req,timeout=0.5)
        #html = response.read().decode("utf-8")
        return True
 
    except Exception as e:# 418 404 500
        #print("An Exception happen  ",e)
    # except urllib.error.URLError as e:
    #     if hasattr(e,"cedo"):
    #         print(e.code)
    #     if hasattr(e,"reason"):
    #         print(e.reason)
        return False

def isNetOK():
    Net=askURL("https://www.baidu.com/")
    return Net

def doubleCheck(Net):#登陆后再次判断是否联网
    global Pointer
    if Net == False:
        print("第"+str(Pointer+1)+"组已失效，已切换下一组\n")
        if Pointer == len(ac_list)-1:
            Pointer=0
        else:
            Pointer=Pointer+1
        askURL(askAC(url1,url2,url3))
    else:
        print("第"+str(Pointer+1)+"组成功登录\n")
        Pointer=Pointer+1


if __name__ == '__main__':
    main()
