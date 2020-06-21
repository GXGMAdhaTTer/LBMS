
# 导入相应库文件

import requests

from lxml import etree

import csv

 

# 创建CSV文件，并写入表头信息

fp = open('booklist.csv','wt',newline='',encoding='utf-8')

writer = csv.writer(fp)

writer.writerow(('250','0','0','250','0','0'))

# 250,0,0,250,0,0

# 构造所有的URL链接

urls = ['https://book.douban.com/top250?start={}'.format(str(i)) for i in range(0,251,25)]

 

# 添加请求头

headers = {

    'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36'

}

 

 

# 循环URL

for url in urls:

    html = requests.get(url,headers=headers)

    selector = etree.HTML(html.text)

    # 取大标签，以此循环

    infos = selector.xpath('//tr[@class="item"]')

 

    for info in infos:

        name = info.xpath('td/div/a/@title')[0]

        #url = info.xpath('td/div/a/@href')[0]

        book_infos = info.xpath('td/p/text()')[0]

        author = book_infos.split('/')[0]

        publisher = book_infos.split('/')[-3]

        #date = book_infos.split('/')[-2]

        #price = book_infos.split('/')[-1]

        #rate = info.xpath('td/div/span[2]/text()')[0]

        #comments = info.xpath('td/p/span/text()')

        #comment = comments[0] if len(comments) != 0 else "空"

 

        # 写入数据

        writer.writerow((name,author,publisher,'isbn000','2000/1/1','key','class','0','0','1','0','nil','2000/1/1','2000/1/1'))

 

# 关闭文件

fp.close()
