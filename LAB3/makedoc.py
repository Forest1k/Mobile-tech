# -*- coding: utf-8 -*-

from docxtpl import DocxTemplate
import sys
import math
from importlib import reload
import os

reload(sys)

f = open(sys.argv[1], 'r')

str = f.readline().split(' ')
for i in range(2):
	f.readline()

net = float(str[7])
mobile = float(f.readline().split(' ')[2])





doc = DocxTemplate("template.docx")
num = ["","один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"]
des = ['', '', 'двадцать ', "тридцать ", "сорок ", "пятьдесят ", "шестьдесят ", "семьдесят ", "восемьдесят ", "девяносто ","десять ","одиннадцать ","двенадцать ","тринадцать ","четырнадцать ","пятнадцать ","шестнадцать ","семнадцать ","восемьнадцать ","девятнадцать "]
sto = ["", "сто ", "двести ", "триста ", "четыреста ", "пятьсот ", "шестьсот ", "семсот ", "восемсот ", "девятьсот "]
all = (mobile+net)*20/100+mobile+net

kop, rub = math.modf(all)
rub = int(round(rub))

kop = int(round(kop * 100))

rustext=  ''
if (rub == 0):
	rustext = num[0] + 'руб. '
else:
	rustext += sto[rub // 100]
	if ((rub // 10) == 1):
		if ((rub % 10) != 0):
			rustext += des[rub%10]
		else:
			rustext += "десять руб. "
	else:
		rustext += des[rub // 10]
	rustext += num[rub%10] + ' руб. '
if (kop == 0):
	rustext = num[0] + ' коп.'
else:
	rustext += sto[kop // 100]
	if ((kop // 10) == 1):
		if ((rub % 10) != 0):
			rustext += des[kop%10]
		else:
			rustext += "десять коп."
	else:
		rustext += des[kop // 10]
	rustext += num[kop%10] + ' коп.'
	

context = {"bank":'АО "Стоун банк" Г.МОСКВА',
"bik":'044525703',
'shet1':'30101810200000300',
'inn':'7722737363',
'kpp':'772303001',
'shet2':'40703850100000400',
'receiver':'ООО "Василек"',
'n':'83',
'd':'01',
'm':'июля',
'y':'20',
'fullreceiver':'ООО "Василек", ИНН 7722737363, КПП 772303001, 109052. Москва г Добрынинская ул., дом № 70, корпус 2',
'fullbuyer':'ООО ЛАГУНА, ИНН 7714037338, КПП 777550001, 119361, Москва г, Тульская ул., дом №4, строение 1',
'osnovanie':'№ 20023316 от 22.05.2020',
'product1':'Оплата услуг мобильной связи',
'product2':'Оплата услуг "Интернет"',
'count1':'1',
'ed':'шт',
'price1':mobile,
'price2':net,
'count2':'1',
'sum1':mobile*1,
'sum2':net*1,
'finalsum':mobile+net,
'nds':(mobile+net)*20/100,
'all':all,
'summtext':rustext,
'ruk':'Леевик А.Г.',
'buh':'Леевик А.Г.'}

doc.render(context)
doc.save('otchet.docx')
os.system("libreoffice --convert-to pdf otchet.docx")

