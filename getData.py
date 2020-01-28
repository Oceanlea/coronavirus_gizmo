import requests 
import re
import time
import json

while True:
	URL = "https://3g.dxy.cn/newh5/view/pneumonia?scene=2&clicktime=1579582238&enterid=1579582238&from=singlemessage&isappinstalled=0"
	r = requests.get(URL) 
	china_total = 0

	import bs4
	soup = bs4.BeautifulSoup(r.content, 'html.parser')

	china_data = str(soup.find('script', id='getAreaStat'))

	start_tag = '>try { window.getAreaStat = ';
	end_tag = '}catch(e){}'

	formatted_china = china_data[china_data.find(start_tag) + len(start_tag):china_data.find(end_tag)]

	data = json.loads(formatted_china)

	for i in data:
		china_total += (i["confirmedCount"])

	start_tag = '>try { window.getListByCountryTypeService2 = '

	global_data = str(soup.find('script', id='getListByCountryTypeService2'))

	formatted_china = global_data[global_data.find(start_tag) + len(start_tag):global_data.find(end_tag)]

	data = json.loads(formatted_china)
	global_total = 0;
	for i in data:
		global_total += (i["confirmedCount"])

	print("china total: {0}".format(china_total))
	print("global_total: {0}".format(global_total))
	my_file = open("server/index.html","w")

	my_file.write("{0}".format(global_total + china_total))
	my_file.close()
	time.sleep(120)
