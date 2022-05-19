import urllib.request, urllib.error, time
url1 = "http://10.20.10.11/drcom/login?callback=dr1630742058746&DDDDD=202011060006&upass=262823&0MKKey=123456&R1=0&R3=0&R6=0&para=00&v6ip=&_=1630742044877"
url2 = "http://10.20.10.11/drcom/login?callback=dr1630741813639&DDDDD=202011060217&upass=281528&0MKKey=123456&R1=0&R3=0&R6=0&para=00&v6ip=&_=1630741772769"
url3 = "http://10.20.10.11/drcom/login?callback=dr1652273624321&DDDDD=202011060239&upass=169579&0MKKey=123456&R1=0&R3=0&R6=0&para=00&v6ip=&_=1652273615200"
def main():
    while 1:
        askURL(url3)
        print(9)
        time.sleep(0.5)
        askURL(url3)
        print(6)
        time.sleep(0.5)

def askURL(url):
    head = {  # 模拟浏览器头部信息
        "User-Agent": "Mozilla / 5.0(Windows NT 10.0; Win64; x64) AppleWebKit / 537.36(KHTML, like Gecko) Chrome / 80.0.3987.122  Safari / 537.36"
    }
    # 将头部信息 封装 给 urllib.request.Request 的 一个 实例化的 类
    req = urllib.request.Request(url,headers=head)
    #html=""
 
    try:
        # 对封装好的类进行访问 得到响应
        response = urllib.request.urlopen(req,timeout=0.2)
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

if __name__ == '__main__':
    main()
 