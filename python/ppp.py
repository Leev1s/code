from re import A
from bs4 import BeautifulSoup
#import re
import urllib.request, urllib.error  # 制定URL，获取网页数据

#pattern=re.compile(r'<a class>(.*)</a>')


def main():
    a=1
    baseurl = "https://movie.douban.com/chart"  #要爬取的网页链接
    datalist = getData(baseurl)
    for i in datalist:
        a=str(a)
        print('No.'+a+' '+i)
        a=int(a)
        a=a+1


def getData(baseurl):
    datalist = []  #用来存储爬取的网页信息
    url = baseurl
    html = askURL(url)  # 保存获取到的网页源码
    soup = BeautifulSoup(html, "html.parser")
    #print(soup.prettify())
    #print(soup.get_text())
    for item in soup.find_all("div",{'class':'box_chart'}):
        title = item.a.string
        otitle = title.replace(" ", "")
        otitle = otitle.replace("\n", "")
        datalist.append(otitle)
    return datalist


def askURL(url):
    # head 用户 代理 爬虫 伪装  告诉豆瓣服务器 是什么类型的 浏览器 且 可以接受 什么类型的 数据
    head = {  # 模拟浏览器头部信息，向豆瓣服务器发送消息
        "User-Agent": "Mozilla / 5.0(Windows NT 10.0; Win64; x64) AppleWebKit / 537.36(KHTML, like Gecko) Chrome / 80.0.3987.122  Safari / 537.36"
    }
    # 将头部信息 封装 给 urllib.request.Request 的 一个 实例化的 类
    req = urllib.request.Request(url,headers=head)
    html=""
 
    try:
        # 对封装好的类进行访问 得到响应
        response = urllib.request.urlopen(req)
        html = response.read().decode("utf-8")
 
    except Exception as e:# 418 404 500
        print("An Exception happen  ",e)
    # except urllib.error.URLError as e:
    #     if hasattr(e,"cedo"):
    #         print(e.code)
    #     if hasattr(e,"reason"):
    #         print(e.reason)
    return html
#------------------------------------------------------------------------------
main()
input("please input any key to exit!")