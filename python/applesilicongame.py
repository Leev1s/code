from re import A
from bs4 import BeautifulSoup
#import re
import urllib.request, urllib.error  # 制定URL，获取网页数据
import xlwt  # 进行excel操作
#pattern=re.compile(r'<a class>(.*)</a>')


def main():
    a=1
    baseurl = "https://applesilicongames.com/games"  #要爬取的网页链接
    datalist = getData(baseurl)
    savepath = "applesilicongames.xls"
    saveData(datalist,savepath)


def getData(baseurl):
    datalist = []  #用来存储爬取的网页信息
    url = baseurl
    html = askURL(url)  # 保存获取到的网页源码
    soup = BeautifulSoup(html, "html.parser")
    #print(soup.prettify())
    #print(soup.get_text())
    #for link in soup.find_all('a'):
        #print(link.string)
    times=1
    data=[]
    for link in soup.find_all('td'):
        if times==1:
            data.append(link.string)
            times=2
            continue
        if times==2:
            data.append(link.string)
            times=3
            continue
        if times==3:
            data.append(link.string)
            times=1
            datalist.append(data)
            data=[]   
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

def saveData(datalist,savepath):
    print("save.......")
    book = xlwt.Workbook(encoding="utf-8",style_compression=0) #创建workbook对象
    sheet = book.add_sheet('applesilicongames', cell_overwrite_ok=True) #创建工作表
    col = ("Title","playable via","is it playable?")
    for i in range(0,3):
        sheet.write(0,i,col[i])  #列名
    times=len(datalist)
    for i in range(0,times):
        # print("第%d条" %(i+1))       #输出语句，用来测试
        data = datalist[i]
        for j in range(0,3):
            sheet.write(i+1,j,data[j])  #数据
    book.save(savepath) #保存
#------------------------------------------------------------------------------
main()
input("please input any key to exit!")
