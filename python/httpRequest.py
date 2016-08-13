#!/opt/local/bin/python

from lxml import html
import requests

udg_website = "en.wikipedia.org"
udg_page = "https://en.wikipedia.org/wiki/Main_Page"

udg_header = {'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:42.0) Gecko/20100101 Firefox/42.0'}
udg_header_comment = {
	'Host': udg_website,
	'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:42.0) Gecko/20100101 Firefox/42.0',
	'Accept': 'application/json, text/javascript, */*; q=0.01',
	'Accept-Language': 'en-US,en;q=0.5',
	'Accept-Encoding': 'gzip, deflate',
	'X-Requested-With': 'XMLHttpRequest',
	'Connection': 'keep-alive'
}

start_page = requests.get(udg_page, 
				headers=udg_header_comment)
tree = html.fromstring(start_page.text)
count = tree.xpath('//a[@title="Special:Statistics"]/text()')[0]

print count